#include <pg_query.h>

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
 * Tests how protobuf encoding and decoding handle deeply nested parse trees.
 * Nesting is bounded both by a fixed limit (PG_QUERY_PROTOBUF_MAX_DEPTH, 10,000
 * message levels) and by the stack depth limit, which depends on the stack
 * available and the stack used per level (which varies a lot between compilers
 * and optimization levels). So only moderately nested queries are expected to
 * always succeed; for deeper ones the tests check that they either succeed or
 * fail with a clean error, but never crash or return an empty result:
 *
 * - moderately nested expressions (each costs two protobuf message levels)
 *   round-trip through pg_query_parse_protobuf and pg_query_deparse_protobuf
 * - very deeply nested queries return an error (not an empty parse tree)
 * - the deepest tree we can encode deparses, or fails with a clean error
 * - protobuf input nested deeper than the fixed limit fails to decode
 */

/*
 * Up to 100 terms (~200 message levels): above upb's own default decode limit
 * (100 levels), which used to reject such queries, but small enough to fit the
 * stack depth limit even in unoptimized builds on a 1 MB stack.
 */
static const int roundtrip_terms[] = {10, 50, 100};

/* Deeper than either limit allows */
#define TOO_DEEP_TERMS 100000

/* Upper bound for finding the deepest query that still encodes */
#define ENCODE_LIMIT_SEARCH_MAX_TERMS 20000

/* Deeper than PG_QUERY_PROTOBUF_MAX_DEPTH (10,000 message levels) */
#define TOO_DEEP_PROTOBUF_NESTINGS 20000

/*
 * Builds "SELECT ((1 + 1) + 1) + ... + 1" with the given number of terms (at
 * least 2), each nesting one expression level deeper. The explicit parentheses
 * match the deparser's output, so the result can be compared exactly.
 */
static char *
make_nested_query(int terms)
{
	char	   *query = malloc(strlen("SELECT 1 + 1") + (terms - 2) * strlen("() + 1") + 1);
	char	   *p = query;

	p += sprintf(p, "SELECT ");
	for (int i = 2; i < terms; i++)
		*p++ = '(';
	p += sprintf(p, "1 + 1");
	for (int i = 2; i < terms; i++)
		p += sprintf(p, ") + 1");

	return query;
}

static bool
test_roundtrip(int terms)
{
	bool		ok = false;
	char	   *query = make_nested_query(terms);
	PgQueryProtobufParseResult parse_result = pg_query_parse_protobuf(query);

	if (parse_result.error)
	{
		printf("\nparse failed for %d terms: %s\n", terms, parse_result.error->message);
	}
	else
	{
		PgQueryDeparseResult deparse_result = pg_query_deparse_protobuf(parse_result.parse_tree);

		if (deparse_result.error)
			printf("\ndeparse failed for %d terms: %s\n", terms, deparse_result.error->message);
		else if (strcmp(deparse_result.query, query) != 0)
			printf("\ndeparse mismatch for %d terms\n", terms);
		else
			ok = true;

		pg_query_free_deparse_result(deparse_result);
	}

	pg_query_free_protobuf_parse_result(parse_result);
	free(query);

	return ok;
}

static bool
parses_to_protobuf(int terms)
{
	char	   *query = make_nested_query(terms);
	PgQueryProtobufParseResult parse_result = pg_query_parse_protobuf(query);
	bool		ok = parse_result.error == NULL;

	pg_query_free_protobuf_parse_result(parse_result);
	free(query);

	return ok;
}

/* A query too deep to encode returns an error, and no (empty) parse tree */
static bool
test_too_deep_query(void)
{
	bool		ok = false;
	char	   *query = make_nested_query(TOO_DEEP_TERMS);
	PgQueryProtobufParseResult parse_result = pg_query_parse_protobuf(query);

	if (parse_result.error == NULL)
		printf("\nexpected an error for %d terms, got success\n", TOO_DEEP_TERMS);
	else if (parse_result.parse_tree.data != NULL || parse_result.parse_tree.len != 0)
		printf("\nexpected no parse tree for %d terms\n", TOO_DEEP_TERMS);
	else
		ok = true;

	pg_query_free_protobuf_parse_result(parse_result);
	free(query);

	return ok;
}

/*
 * Finds the deepest query that still encodes, and checks that deparsing it
 * either succeeds or fails with a clean error. Decoding and deparsing use more
 * stack per level than encoding, so this is where a missing stack depth check
 * would crash.
 */
static bool
test_deepest_encodable_query(void)
{
	int			lo = 2;
	int			hi = ENCODE_LIMIT_SEARCH_MAX_TERMS;
	char	   *query;
	PgQueryProtobufParseResult parse_result;
	PgQueryDeparseResult deparse_result;
	bool		ok = true;

	if (parses_to_protobuf(hi))
	{
		printf("\nexpected %d terms to exceed the protobuf depth limit\n", hi);
		return false;
	}

	while (lo < hi)
	{
		int			mid = lo + (hi - lo + 1) / 2;

		if (parses_to_protobuf(mid))
			lo = mid;
		else
			hi = mid - 1;
	}

	query = make_nested_query(lo);
	parse_result = pg_query_parse_protobuf(query);
	if (parse_result.error)
	{
		/*
		 * The encode limit is (partly) stack-based, so a query that encoded
		 * when probed above could in theory fail here from a different frame
		 * depth. Don't silently skip the deparse in that case.
		 */
		printf("\nparse failed for the deepest encodable query (%d terms): %s\n", lo, parse_result.error->message);
		ok = false;
	}
	else
	{
		deparse_result = pg_query_deparse_protobuf(parse_result.parse_tree);
		if (deparse_result.error == NULL && strcmp(deparse_result.query, query) != 0)
		{
			printf("\ndeparse mismatch for the deepest encodable query (%d terms)\n", lo);
			ok = false;
		}
		pg_query_free_deparse_result(deparse_result);
	}
	pg_query_free_protobuf_parse_result(parse_result);
	free(query);

	return ok;
}

/* Protobuf wire format helpers, used to build input our encoder won't produce */

static uint8_t *
prepend_varint(uint8_t *p, uint64_t value)
{
	uint8_t		tmp[10];
	int			n = 0;

	do
	{
		tmp[n++] = (value & 0x7f) | (value > 0x7f ? 0x80 : 0);
		value >>= 7;
	} while (value);

	p -= n;
	memcpy(p, tmp, n);
	return p;
}

/* Wraps the bytes in [p, end) as a length-delimited field */
static uint8_t *
prepend_submessage(uint8_t *p, uint8_t *end, uint32_t field)
{
	p = prepend_varint(p, end - p);
	return prepend_varint(p, (field << 3) | 2);
}

/*
 * Builds a ParseResult protobuf whose single statement is a Node wrapping a
 * List, whose single item is a Node wrapping a List, and so on, nested the
 * given number of times (each nesting adds two message levels).
 */
static PgQueryProtobuf
make_nested_protobuf(int nestings)
{
	size_t		cap = (size_t) nestings * 16 + 64;
	uint8_t    *buf = malloc(cap);
	uint8_t    *end = buf + cap;
	uint8_t    *p = end;
	PgQueryProtobuf protobuf;

	for (int i = 0; i < nestings; i++)
	{
		p = prepend_submessage(p, end, 1);	/* List.items (repeated Node) */
		p = prepend_submessage(p, end, 268);	/* Node.list (List) */
	}
	p = prepend_submessage(p, end, 1);	/* RawStmt.stmt (Node) */
	p = prepend_submessage(p, end, 2);	/* ParseResult.stmts (RawStmt) */
	p = prepend_varint(p, PG_VERSION_NUM);
	p = prepend_varint(p, (1 << 3) | 0);	/* ParseResult.version */

	protobuf.len = end - p;
	protobuf.data = malloc(protobuf.len);
	memcpy(protobuf.data, p, protobuf.len);
	free(buf);

	return protobuf;
}

static bool
test_decode_limit(void)
{
	bool		ok = false;
	PgQueryProtobuf protobuf = make_nested_protobuf(TOO_DEEP_PROTOBUF_NESTINGS);
	PgQueryDeparseResult deparse_result = pg_query_deparse_protobuf(protobuf);

	if (deparse_result.error == NULL)
		printf("\nexpected deparse error for too deeply nested protobuf, got success\n");
	else if (strcmp(deparse_result.error->message, "could not parse protobuf") != 0)
		printf("\nunexpected deparse error for too deeply nested protobuf: %s\n", deparse_result.error->message);
	else
		ok = true;

	pg_query_free_deparse_result(deparse_result);
	free(protobuf.data);

	return ok;
}

int
main()
{
	bool		ret_code = 0;

	for (size_t i = 0; i < sizeof(roundtrip_terms) / sizeof(roundtrip_terms[0]); i++)
	{
		if (test_roundtrip(roundtrip_terms[i]))
			printf(".");
		else
			ret_code = -1;
	}

	if (test_too_deep_query())
		printf(".");
	else
		ret_code = -1;

	if (test_deepest_encodable_query())
		printf(".");
	else
		ret_code = -1;

	if (test_decode_limit())
		printf(".");
	else
		ret_code = -1;

	printf("\n");

	pg_query_exit();

	return ret_code;
}
