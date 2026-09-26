#include <pg_query.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Regression test for stack overflows when walking deeply nested parse trees.
//
// A deeply nested expression like "SELECT 1%1%1%...%1" parses into a very deep
// A_Expr tree, and "SELECT 1 UNION SELECT 1 UNION ..." into a very deep
// SelectStmt tree. Recursively serializing or walking that tree (JSON/protobuf
// output, deparsing, normalizing, ...) could overflow the C stack and crash,
// these tests verify we return an error instead, like Postgres does.

static char *build_deep_query(const char *repeated, int depth)
{
	// "SELECT 1" followed by `repeated` `depth` times
	size_t len = strlen("SELECT 1") + (size_t) depth * strlen(repeated);
	char *query = malloc(len + 1);
	char *p = query;

	p += sprintf(p, "SELECT 1");
	for (int i = 0; i < depth; i++)
		p += sprintf(p, "%s", repeated);

	return query;
}

static bool is_clean(const PgQueryError *error)
{
	if (error == NULL)
		return true;
	return strstr(error->message, "stack depth limit exceeded") != NULL;
}

static bool run_tests(const char *repeated)
{
	bool ret_code = 0;
	char *query = build_deep_query(repeated, 100000);

	// JSON output (pg_query_parse)
	{
		PgQueryParseResult result = pg_query_parse(query);
		if (is_clean(result.error)) {
			printf(".");
		} else {
			ret_code = -1;
			printf("INVALID parse result, expected clean error, got: %s\n",
				   result.error ? result.error->message : "(success)");
		}
		pg_query_free_parse_result(result);
	}

	// Protobuf output (pg_query_parse_protobuf)
	{
		PgQueryProtobufParseResult result = pg_query_parse_protobuf(query);
		if (is_clean(result.error)) {
			printf(".");
		} else {
			ret_code = -1;
			printf("INVALID protobuf parse result, expected clean error, got: %s\n",
				   result.error->message);
		}
		pg_query_free_protobuf_parse_result(result);
	}

	// Normalize (const_record_walker / raw_expression_tree_walker)
	{
		PgQueryNormalizeResult result = pg_query_normalize(query);
		if (is_clean(result.error)) {
			printf(".");
		} else {
			ret_code = -1;
			printf("INVALID normalize result, expected clean error, got: %s\n",
				   result.error->message);
		}
		pg_query_free_normalize_result(result);
	}

	// Fingerprint
	{
		PgQueryFingerprintResult result = pg_query_fingerprint(query);
		if (is_clean(result.error)) {
			printf(".");
		} else {
			ret_code = -1;
			printf("INVALID fingerprint result, expected clean error, got: %s\n",
				   result.error->message);
		}
		pg_query_free_fingerprint_result(result);
	}

	// Summary
	{
		PgQuerySummaryParseResult result = pg_query_summary(query, PG_QUERY_PARSE_DEFAULT, -1);
		if (is_clean(result.error)) {
			printf(".");
		} else {
			ret_code = -1;
			printf("INVALID summary result, expected clean error, got: %s\n",
				   result.error->message);
		}
		pg_query_free_summary_parse_result(result);
	}

	// Deparse (deparseExpr) - exercise via a protobuf round-trip at a depth that
	// serializes successfully, so deparsing actually walks a deep tree.
	{
		char *shallow = build_deep_query(repeated, 100);
		PgQueryProtobufParseResult parsed = pg_query_parse_protobuf(shallow);
		if (parsed.error) {
			ret_code = -1;
			printf("INVALID: could not produce protobuf for deparse test: %s\n", parsed.error->message);
		} else {
			PgQueryDeparseResult result = pg_query_deparse_protobuf(parsed.parse_tree);
			if (is_clean(result.error)) {
				printf(".");
			} else {
				ret_code = -1;
				printf("INVALID deparse result, expected clean error, got: %s\n",
					   result.error->message);
			}
			pg_query_free_deparse_result(result);
		}
		pg_query_free_protobuf_parse_result(parsed);
		free(shallow);
	}

	free(query);

	return ret_code;
}

int main()
{
	bool ret_code = 0;

	// Deeply nested expressions go through the generic node dispatchers
	// (_outNode, _readNode, deparseExpr, ...)
	ret_code |= run_tests("%1");

	// Set operations recurse into the SelectStmt-specific functions directly
	ret_code |= run_tests(" UNION SELECT 1");

	printf("\n");

	pg_query_exit();

	return ret_code;
}
