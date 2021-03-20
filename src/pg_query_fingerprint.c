// Ensure we have asprintf's definition on glibc-based platforms to avoid compiler warnings
#define _GNU_SOURCE
#include <stdio.h>

#include "pg_query.h"
#include "pg_query_internal.h"
#include "pg_query_fingerprint.h"

#include "postgres.h"
#include "xxhash/xxhash.h"
#include "lib/ilist.h"

#include "parser/parser.h"
#include "parser/scanner.h"
#include "parser/scansup.h"

#include "nodes/parsenodes.h"
#include "nodes/value.h"

#include <unistd.h>
#include <fcntl.h>

// Definitions

typedef struct FingerprintContext
{
	XXH3_state_t *xxh_state;

	bool write_tokens;
	dlist_head tokens;
} FingerprintContext;

typedef struct FingerprintListContext
{
	XXH64_hash_t hash;
	size_t list_pos;
} FingerprintListContext;

typedef struct FingerprintToken
{
	char *str;
	dlist_node list_node;
} FingerprintToken;

static void _fingerprintNode(FingerprintContext *ctx, const void *obj, const void *parent, char *parent_field_name, unsigned int depth);
static void _fingerprintInitContext(FingerprintContext *ctx, bool write_tokens);
static void _fingerprintFreeContext(FingerprintContext *ctx);

#define PG_QUERY_FINGERPRINT_VERSION 3

// Implementations

static void
_fingerprintString(FingerprintContext *ctx, const char *str)
{
	if (ctx->xxh_state != NULL) {
		XXH3_64bits_update(ctx->xxh_state, str, strlen(str));
	}

	if (ctx->write_tokens) {
		FingerprintToken *token = palloc0(sizeof(FingerprintToken));
		token->str = pstrdup(str);
		dlist_push_tail(&ctx->tokens, &token->list_node);
	}
}

static void
_fingerprintInteger(FingerprintContext *ctx, const Value *node)
{
	if (node->val.ival != 0) {
		_fingerprintString(ctx, "Integer");
		_fingerprintString(ctx, "ival");
		char buffer[50];
		sprintf(buffer, "%d", node->val.ival);
		_fingerprintString(ctx, buffer);
	}
}

static void
_fingerprintFloat(FingerprintContext *ctx, const Value *node)
{
	if (node->val.str != NULL) {
		_fingerprintString(ctx, "Float");
		_fingerprintString(ctx, "str");
		_fingerprintString(ctx, node->val.str);
	}
}

static void
_fingerprintBitString(FingerprintContext *ctx, const Value *node)
{
	if (node->val.str != NULL) {
		_fingerprintString(ctx, "BitString");
		_fingerprintString(ctx, "str");
		_fingerprintString(ctx, node->val.str);
	}
}

static int compareFingerprintListContext(const void *a, const void *b)
{
	FingerprintListContext *ca = *(FingerprintListContext**) a;
	FingerprintListContext *cb = *(FingerprintListContext**) b;
	if (ca->hash > cb->hash)
		return 1;
	else if (ca->hash < cb->hash)
		return -1;
	return 0;
}

static void
_fingerprintList(FingerprintContext *ctx, const List *node, const void *parent, char *field_name, unsigned int depth)
{
	if (field_name != NULL && (strcmp(field_name, "fromClause") == 0 || strcmp(field_name, "targetList") == 0 ||
			strcmp(field_name, "cols") == 0 || strcmp(field_name, "rexpr") == 0 || strcmp(field_name, "valuesLists") == 0 ||
			strcmp(field_name, "args") == 0)) {

		FingerprintListContext** listCtxArr = palloc0(node->length * sizeof(FingerprintListContext*));
		size_t listCtxCount = 0;
		const ListCell *lc;

		foreach(lc, node)
		{
			FingerprintContext subCtx;
			FingerprintListContext* listCtx = palloc0(sizeof(FingerprintListContext));

			_fingerprintInitContext(&subCtx, false);
			_fingerprintNode(&subCtx, lfirst(lc), parent, field_name, depth + 1);
			listCtx->hash = XXH3_64bits_digest(subCtx.xxh_state);
			listCtx->list_pos = listCtxCount;
			_fingerprintFreeContext(&subCtx);

			listCtxArr[listCtxCount] = listCtx;
			listCtxCount += 1;
		}

		pg_qsort(listCtxArr, listCtxCount, sizeof(FingerprintListContext*), compareFingerprintListContext);

		for (size_t i = 0; i < listCtxCount; i++)
		{
			if (i > 0 && listCtxArr[i - 1]->hash == listCtxArr[i]->hash)
				continue; // Ignore duplicates

			_fingerprintNode(ctx, lfirst(list_nth_cell(node, listCtxArr[i]->list_pos)), parent, field_name, depth + 1);
		}
	} else {
		const ListCell *lc;

		foreach(lc, node)
		{
			_fingerprintNode(ctx, lfirst(lc), parent, field_name, depth + 1);

			lnext(node, lc);
		}
	}
}

static void
_fingerprintInitContext(FingerprintContext *ctx, bool write_tokens) {
	ctx->xxh_state = XXH3_createState();
	if (ctx->xxh_state == NULL) abort();
	if (XXH3_64bits_reset_withSeed(ctx->xxh_state, PG_QUERY_FINGERPRINT_VERSION) == XXH_ERROR) abort();

	if (write_tokens) {
		ctx->write_tokens = true;
		dlist_init(&ctx->tokens);
	} else {
		ctx->write_tokens = false;
	}
}

static void
_fingerprintFreeContext(FingerprintContext *ctx) {
	XXH3_freeState(ctx->xxh_state);
}

#include "pg_query_enum_defs.c"
#include "pg_query_fingerprint_defs.c"

void
_fingerprintNode(FingerprintContext *ctx, const void *obj, const void *parent, char *field_name, unsigned int depth)
{
	// Some queries are overly complex in their parsetree - lets consistently cut them off at 100 nodes deep
	if (depth >= 100) {
		return;
	}

	if (obj == NULL)
	{
		return; // Ignore
	}

	switch (nodeTag(obj))
	{
		case T_List:
			_fingerprintList(ctx, obj, parent, field_name, depth);
			break;
		case T_Integer:
			_fingerprintInteger(ctx, obj);
			break;
		case T_Float:
			_fingerprintFloat(ctx, obj);
			break;
		case T_String:
			_fingerprintString(ctx, "String");
			_fingerprintString(ctx, "str");
			_fingerprintString(ctx, ((Value*) obj)->val.str);
			break;
		case T_BitString:
			_fingerprintBitString(ctx, obj);
			break;

		#include "pg_query_fingerprint_conds.c"

		default:
			elog(WARNING, "could not fingerprint unrecognized node type: %d",
					(int) nodeTag(obj));

			return;
	}
}

PgQueryFingerprintResult pg_query_fingerprint_with_opts(const char* input, bool printTokens)
{
	MemoryContext ctx = NULL;
	PgQueryInternalParsetreeAndError parsetree_and_error;
	PgQueryFingerprintResult result = {0};

	ctx = pg_query_enter_memory_context();

	parsetree_and_error = pg_query_raw_parse(input);

	// These are all malloc-ed and will survive exiting the memory context, the caller is responsible to free them now
	result.stderr_buffer = parsetree_and_error.stderr_buffer;
	result.error = parsetree_and_error.error;

	if (parsetree_and_error.tree != NULL || result.error == NULL) {
		FingerprintContext ctx;
		XXH64_canonical_t chash;

		_fingerprintInitContext(&ctx, printTokens);

		if (parsetree_and_error.tree != NULL) {
			_fingerprintNode(&ctx, parsetree_and_error.tree, NULL, NULL, 0);
		}

		if (printTokens) {
			dlist_iter iter;

			printf("[");

			dlist_foreach(iter, &ctx.tokens)
			{
				FingerprintToken *token = dlist_container(FingerprintToken, list_node, iter.cur);

				printf("\"%s\", ", token->str);
			}

			printf("]\n");
		}

		result.fingerprint = XXH3_64bits_digest(ctx.xxh_state);
		_fingerprintFreeContext(&ctx);

		XXH64_canonicalFromHash(&chash, result.fingerprint);
		int err = asprintf(&result.fingerprint_str, "%02x%02x%02x%02x%02x%02x%02x%02x",
						   chash.digest[0], chash.digest[1], chash.digest[2], chash.digest[3],
						   chash.digest[4], chash.digest[5], chash.digest[6], chash.digest[7]);
		if (err == -1) {
			PgQueryError* error = malloc(sizeof(PgQueryError));
			error->message = strdup("Failed to output fingerprint string due to asprintf failure");
			result.error = error;
		}
	}

	pg_query_exit_memory_context(ctx);

	return result;
}

PgQueryFingerprintResult pg_query_fingerprint(const char* input)
{
	return pg_query_fingerprint_with_opts(input, false);
}

void pg_query_free_fingerprint_result(PgQueryFingerprintResult result)
{
	if (result.error) {
		free(result.error->message);
		free(result.error->filename);
		free(result.error);
	}

	free(result.fingerprint_str);
	free(result.stderr_buffer);
}
