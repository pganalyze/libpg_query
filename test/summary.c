#include <pg_query.h>
#include "src/pg_query_summary.h"

#include <stdio.h>
#include <stdlib.h>

#include "test/framework/main.h"

static void
test_cleanup(void)
{
}

static PgQuerySummaryParseResultInternal summary_internal(char *query, int parser_options, int truncate_limit)
{
	PgQuerySummaryParseResultInternal parse_result = pg_query_summary_internal(query, parser_options, truncate_limit);

	return parse_result;
}

static Summary summary(char *query, int parser_options, int truncate_limit)
{
	PgQuerySummaryParseResultInternal parse_result = pg_query_summary_internal(query, parser_options, truncate_limit);

	if (parse_result.error != NULL)
	{
		printf("  ERROR: %s\n", parse_result.error->message);
		exit(1);
	}

	/*
	 * This is (roughly) equivalent to the Rust tests that assert
	 * `result.warnings` is empty.
	 */
	if (parse_result.stderr_buffer &&
		strstr(parse_result.stderr_buffer, "WARNING"))
	{
		printf("  ERROR: stderr_buffer contained a warning:\n%s\n", parse_result.stderr_buffer);
		exit(1);
	}

	Summary		summary = parse_result.summary;

	/* We no longer have a use for parts using the system allocator. */
	pg_query_free_summary_parse_result_internal(parse_result);

	return summary;
}

static char *
ctx_to_str(ContextType ctx)
{
	switch (ctx)
	{
		case CONTEXT_NONE:
			return "CONTEXT_NONE";
		case CONTEXT_SELECT:
			return "CONTEXT_SELECT";
		case CONTEXT_DML:
			return "CONTEXT_DML";
		case CONTEXT_DDL:
			return "CONTEXT_DDL";
		case CONTEXT_CALL:
			return "CONTEXT_CALL";
		default:
			return "<INVALID -- THIS SHOULD NEVER HAPPEN -- THIS IS A BUG>";
	}
}

/* Assert that `aliases` contains an alias with the key `key` and value `val`. */
#define TEST_SUMMARY_ASSERT_ALIAS(aliases, key, val) TEST_SUMMARY_ASSERT_ALIAS_impl(test_state, aliases, #key, key, val)
void
TEST_SUMMARY_ASSERT_ALIAS_impl(TestState * test_state, List *aliases, char *expected_key_str, char *expected_key, char *expected_val)
{
	ListCell   *lc = NULL;

	foreach(lc, aliases)
	{
		SummaryAlias *alias = lfirst(lc);

		if (TEST_BOUNDED_STRCMP(alias->key, expected_key) == 0)
		{
			TEST_ASSERT_STR_EQUAL(alias->value, expected_val);
			return;
		}
	}

	/* If we get here, we didn't find a match. */
	TEST_FAIL("  FAIL: Expected an alias with key '%s', but it doesn't exist\n", expected_key_str);
}

/* Assert that `filter_columns` contains an alias with the key `key` and value `val`. */
#define TEST_SUMMARY_ASSERT_FILTER_COLUMN(filter_columns, schema, table, column) TEST_SUMMARY_ASSERT_FILTER_COLUMN_impl(test_state, filter_columns, schema, table, column)
void
TEST_SUMMARY_ASSERT_FILTER_COLUMN_impl(TestState * test_state,
									   List *filter_columns, char *schema_name, char *table_name, char *column)
{
	ListCell   *lc = NULL;
	int			found = 0;

	foreach(lc, filter_columns)
	{
		FilterColumn *fc = lfirst(lc);

		if ((TEST_BOUNDED_STRCMP(fc->schema_name, schema_name) == 0) &&
			(TEST_BOUNDED_STRCMP(fc->table_name, table_name) == 0) &&
			(TEST_BOUNDED_STRCMP(fc->column, column) == 0))
		{
			found = 1;
			return;
		}
	}

	if (found)
		TEST_PASS();
	else
		TEST_FAIL("  FAIL: Expected to find a filter column where schema_name=%s, table_name=%s, column=%s\n", schema_name, table_name, column);
}

/* Assert that `functions` contains functions with matching names. */
#define TEST_SUMMARY_ASSERT_FUNCTIONS(functions, names) TEST_SUMMARY_ASSERT_FUNCTIONS_impl(test_state, functions, names)
void
TEST_SUMMARY_ASSERT_FUNCTIONS_impl(TestState * test_state, List *functions, char *names[])
{
	for (size_t i = 0; names[i]; i++)
	{
		int			found = 0;
		ListCell   *lc = NULL;

		foreach(lc, functions)
		{
			SummaryFunction *fn = lfirst(lc);

			if (TEST_BOUNDED_STRCMP(fn->name, names[i]) == 0)
			{
				found = 1;
				break;
			}
		}

		if (found)
			TEST_PASS();
		else
			TEST_FAIL("  FAIL: Expected to find a function where name=%s\n", names[i]);
	}
}

/* Assert that `functions` contains functions with matching names. */
#define TEST_SUMMARY_ASSERT_FUNCTIONS_WITH_CTX(functions, ctx, names) TEST_SUMMARY_ASSERT_FUNCTIONS_WITH_CTX_impl(test_state, functions, ctx, names)
void
TEST_SUMMARY_ASSERT_FUNCTIONS_WITH_CTX_impl(TestState * test_state, List *functions, ContextType ctx, char *names[])
{
	for (size_t i = 0; names[i]; i++)
	{
		int			found = 0;
		ContextType actual_ctx = CONTEXT_NONE;
		ListCell   *lc = NULL;

		foreach(lc, functions)
		{
			SummaryFunction *fn = lfirst(lc);

			if (TEST_BOUNDED_STRCMP(fn->name, names[i]) == 0)
			{
				found = 1;
				actual_ctx = fn->context;
				break;
			}
		}

		if (found)
		{
			if (ctx == actual_ctx)
				TEST_PASS();
			else
				TEST_FAIL("  FAIL: Expected function with name=%s to have context=%s, but it has context=%s\n", names[i], ctx_to_str(ctx), ctx_to_str(actual_ctx));
		}
		else
			TEST_FAIL("  FAIL: Expected to find a function where name=%s\n", names[i]);
	}
}

/* Assert that `tables` contains tables with matching names, schema_name, table_name, and context. */
#define TEST_SUMMARY_ASSERT_TABLES(tables, names) TEST_SUMMARY_ASSERT_TABLES_impl(test_state, tables, names)
void
TEST_SUMMARY_ASSERT_TABLES_impl(TestState * test_state, List *tables, char *names[])
{
	for (size_t i = 0; names[i]; i++)
	{
		int			found = 0;
		ListCell   *lc = NULL;

		foreach(lc, tables)
		{
			SummaryTable *table = lfirst(lc);

			if (TEST_BOUNDED_STRCMP(table->name, names[i]) == 0)
			{
				found = 1;
				break;
			}
		}

		if (found)
			TEST_PASS();
		else
			TEST_FAIL("  FAIL: Expected to find a table where name=%s\n", names[i]);
	}
}

/* Assert that `tables` contains tables with matching names, schema_name, table_name, and context. */
#define TEST_SUMMARY_ASSERT_TABLES_WITH_CTX(tables, ctx, names) TEST_SUMMARY_ASSERT_TABLES_WITH_CTX_impl(test_state, tables, ctx, names)
void
TEST_SUMMARY_ASSERT_TABLES_WITH_CTX_impl(TestState * test_state, List *tables, ContextType ctx, char *names[])
{
	for (size_t i = 0; names[i]; i++)
	{
		int			found = 0;
		ContextType actual_ctx = CONTEXT_NONE;
		ListCell   *lc = NULL;

		foreach(lc, tables)
		{
			SummaryTable *table = lfirst(lc);

			if (TEST_BOUNDED_STRCMP(table->name, names[i]) == 0)
			{
				found = 1;
				actual_ctx = table->context;
				break;
			}
		}

		if (found)
		{
			if (ctx == actual_ctx)
				TEST_PASS();
			else
				TEST_FAIL("  FAIL: Expected table with name=%s to have context=%s, but it has context=%s\n", names[i], ctx_to_str(ctx), ctx_to_str(actual_ctx));
		}
		else
			TEST_FAIL("  FAIL: Expected to find a table where name=%s\n", names[i]);
	}
}

#include "summary_tests.c"

int
main(int argc, char *argv[])
{
	TestFn	   *tests[] = {
#include "summary_tests_list.c"
		NULL
	};

	return test_run_with_mcxt(tests, &test_cleanup);
}
