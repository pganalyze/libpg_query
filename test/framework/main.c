#include <pg_query.h>
#include "src/pg_query_internal.h"
#include "test/framework/main.h"
#include <string.h>

/*
 * ARBITRARY_LENGTH_LIMIT is purely arbitrary to avoid unbounded strcmp() usage.
 * Using strcmp() means bugs an cause infinite loops, which is hard to debug.
 * If it causes a problem, make the number bigger.
 * -@duckinator
 */
const size_t ARBITRARY_LENGTH_LIMIT = 500;

int
TEST_BOUNDED_STRCMP(char *s1, char *s2)
{
	/*
	 * strncmp() can not handle being given NULL. so, if either are NULL, we
	 * test whether they're *both* NULL.
	 */
	if (s1 == NULL || s2 == NULL)
		return (s1 == s2) ? 0 : -1;

	return strncmp(s1, s2, ARBITRARY_LENGTH_LIMIT);
}

/*
 * Assert that `actual` is a string containing the same text as `expected`.
 * (This is wrapped by the TEST_ASSERT_STR_EQUAL macro.)
 */
void
TEST_ASSERT_STR_EQUAL_impl(TestState * test_state, char *actual_str, char *actual, char *expected)
{
	if (TEST_BOUNDED_STRCMP(actual, expected) == 0)
		test_state->passed++;
	else
	{
		printf("  FAIL: expected %s to be '%s', but got '%s'\n\n", actual_str, expected, actual);
		test_state->failed++;
	}
}

/*
 * Assert that `lst` contains `expected_len` items.
 * (This is wrapped by the TEST_ASSERT_LIST_LENGTH macro.)
 */
void
TEST_ASSERT_LIST_LENGTH_impl(TestState * test_state, char *lst_str, List *lst, size_t expected_len)
{
	size_t		actual_len = list_length(lst);

	if (actual_len == expected_len)
	{
		test_state->passed++;
	}
	else
	{
		printf("  FAIL: expected %s to have length %li\n", lst_str, expected_len);
		printf("        actual length is %li\n\n", actual_len);
		test_state->failed++;
	}
}

/*
 * Given an array of char*, and the length of the array, return a string representation.
 * Please remember to free the returned pointer when you're done.
 */
static char *
str_list_to_buf(char **list, size_t list_len)
{
	size_t		len = 3;

	/* leading and trailing brackets, and null terminator */
	len += 2 * list_len;
	/* quotes around each item */
	len += 2 * (list_len - 1);
	/* commas and spaces between items */

	for (int i = 0; i < list_len; i++)
		len += strlen(list[i]);

	char	   *buf = malloc(sizeof(char) * len);
	size_t		offset = snprintf(buf, len, "[");

	for (int i = 0; i < list_len; i++)
	{
		offset += snprintf(buf + offset, len - offset, "\"%s\"", list[i]);
		if (i < (list_len - 1))
			offset += snprintf(buf + offset, len - offset, ", ");
	}
	offset += snprintf(buf + offset, len - offset, "]");
	return buf;
}

/*
 * Assert that `actual` and `expected` should contain the same items, but may be in a different order.
 * (This is wrapped by the TEST_ASSERT_LIST_EQUAL macro.)
 */
void
TEST_ASSERT_LIST_EQUAL_impl(TestState * test_state, char *actual_str, List *actual, List *expected)
{
	size_t		actual_len = list_length(actual);
	size_t		expected_len = list_length(expected);

	char	  **act_ary = malloc(sizeof(char *) * actual_len);
	char	  **exp_ary = malloc(sizeof(char *) * expected_len);

	ListCell   *lc = NULL;

	foreach(lc, actual)
	{
		size_t		i = foreach_current_index(lc);

		act_ary[i] = lfirst(lc);
	}
	foreach(lc, expected)
	{
		size_t		i = foreach_current_index(lc);

		exp_ary[i] = lfirst(lc);
	}

	qsort(act_ary, actual_len, sizeof(char *), pg_qsort_strcmp);
	qsort(exp_ary, expected_len, sizeof(char *), pg_qsort_strcmp);

	int			failed = 0;

	if (actual_len != expected_len)
	{
		failed = 1;
	}

	if (failed == 0)
	{
		for (size_t i = 0; i < actual_len; i++)
		{
			if (strcmp(act_ary[i], exp_ary[i]) != 0)
			{
				failed = 1;
				break;
			}
		}
	}

	if (failed)
	{
		test_state->failed++;
		printf("  FAIL: Expected `actual` and `expected` to be equivalent.\n");

		char	   *act_str = str_list_to_buf(act_ary, actual_len);

		printf("      actual: %s\n", act_str);
		free(act_str);

		char	   *exp_str = str_list_to_buf(exp_ary, expected_len);

		printf("    expected: %s\n\n", exp_str);
		free(exp_str);
	}
	else
		test_state->passed++;

	free(act_ary);
	free(exp_ary);
}

int
test_run(TestFn * tests[], TestCleanupFn * test_cleanup)
{
	TestState	test_state = {0};

	pg_query_init();

	for (size_t i = 0; tests[i] != NULL; i++)
	{
		tests[i] (&test_state);
		if (test_cleanup != NULL)
			test_cleanup();
	}

	bool		failed = (test_state.failed > 0);

	printf("\ntest result: %s. %li passed; %li failed; %li skipped\n", failed ? "FAILED" : "ok", test_state.passed, test_state.failed, test_state.skipped);

	pg_query_exit();

	return failed ? EXIT_FAILURE : EXIT_SUCCESS;
}

int
test_run_with_mcxt(TestFn * tests[], TestCleanupFn * test_cleanup)
{
	TestState	test_state = {0};

	pg_query_init();

	for (size_t i = 0; tests[i] != NULL; i++)
	{
		MemoryContext ctx = pg_query_enter_memory_context();
		tests[i] (&test_state);
		if (test_cleanup != NULL)
			test_cleanup();
		pg_query_exit_memory_context(ctx);
	}

	bool		failed = (test_state.failed > 0);

	printf("\ntest result: %s. %li passed; %li failed; %li skipped\n", failed ? "FAILED" : "ok", test_state.passed, test_state.failed, test_state.skipped);

	pg_query_exit();

	return failed ? EXIT_FAILURE : EXIT_SUCCESS;
}
