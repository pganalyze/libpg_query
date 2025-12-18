#include <pg_query.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "test/framework/main.h"

struct LastResult {
	bool has_result;
	PgQueryIsUtilityResult result;
};
static struct LastResult last_result = {false, {0}};

static PgQueryIsUtilityResult
is_utility_stmt(const char *msg)
{
	last_result.has_result = true;
	last_result.result = pg_query_is_utility_stmt(msg);

	return last_result.result;
}

void cleanup()
{
	if (!last_result.has_result)
		return;

	last_result.has_result = false;
	pg_query_free_is_utility_result(last_result.result);
}

#define assert_result_equal(actual, expected_len, expected) assert_result_equal_impl(test_state, #actual, actual, expected_len, expected)
static void
assert_result_equal_impl(TestState * test_state, char *actual_str, PgQueryIsUtilityResult actual, size_t expected_len, bool expected[])
{
	bool all_match = (actual.length == expected_len);

	for (size_t i = 0; (i < expected_len) && (i < actual.length) && all_match; i++) {
		if (actual.items[i] != expected[i])
			all_match = false;
	}

	if (all_match)
		TEST_PASS();
	else {
		TEST_FAIL("Expected `actual` to equal `expected`, where\n");
		printf("      actual: ");
		for (size_t i = 0; i < actual.length; i++)
			printf("%s ", actual.items[i] ? "true " : "false");

		printf("\n    expected: ");
		for (size_t i = 0; i < expected_len; i++)
			printf("%s ", expected[i] ? "true " : "false");

		puts("\n");
	}
}

static void select_test(TestState* test_state)
{
	TEST_INIT();

	assert_result_equal(is_utility_stmt("SELECT 1"), 1, (bool[]){false});
}

static void insert_test(TestState* test_state)
{
	TEST_INIT();

	assert_result_equal(is_utility_stmt("INSERT INTO my_table VALUES(123)"), 1, (bool[]){false});
}

static void update_test(TestState* test_state)
{
	TEST_INIT();
	assert_result_equal(is_utility_stmt("UPDATE my_table SET foo = 123"), 1, (bool[]){false});
}

static void delete_test(TestState* test_state)
{
	TEST_INIT();
	assert_result_equal(is_utility_stmt("DELETE FROM my_table"), 1, (bool[]){false});
}

static void show_test(TestState* test_state)
{
	TEST_INIT();
	assert_result_equal(is_utility_stmt("SHOW fsync"), 1, (bool[]){true});
}

static void set_test(TestState* test_state)
{
	TEST_INIT();
	assert_result_equal(is_utility_stmt("SET fsync = off"), 1, (bool[]){true});
}

static void select2_test(TestState* test_state)
{
	TEST_INIT();
	assert_result_equal(is_utility_stmt("SELECT 1; SELECT 2;"), 2, ((bool[]){false, false}));
}

static void select_show_test(TestState* test_state)
{
	TEST_INIT();
	assert_result_equal(is_utility_stmt("SELECT 1; SHOW fsync;"), 2, ((bool[]){false, true}));
}

int
main(int argc, char *argv[])
{
	TestFn	   *tests[] = {
		&select_test,
		&insert_test,
		&update_test,
		&delete_test,
		&show_test,
		&set_test,
		&select2_test,
		&select_show_test,
		NULL
	};

	return test_run(argc, argv, tests, &cleanup);
}
