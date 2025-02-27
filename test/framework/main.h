#ifndef PG_QUERY_TEST_FRAMEWORK_H
#define PG_QUERY_TEST_FRAMEWORK_H

/*
 * This is a test framework that is specialized for pg_query.
 * There is some macro magic, but the API can be treated as:
 *
 *    TEST_INIT()
 *    TEST_ASSERT_EQUAL_STR(char* actual, char* expected)
 *    TEST_ASSERT_EQUAL_LIST(List* actual, List* expected)
 *    TEST_ASSERT_LIST_LENGTH(List* lst, size_t len)
 *    TEST_PASS()
 *    TEST_FAIL(...) // Args are passed directly to printf.
 *    test_run(TestFn* tests[], TestCleanupFn* test_cleanup)
 *
 *  Basic usage:
 *
 *     static void it_goes_moo(TestState* test_state) {
 *         TEST_INIT();
 *         TEST_ASSERT_EQUAL_STR(cow_noises(), "moo");
 *     }
 *
 *     void test_cleanup(void) {
 *         // Do any between-test cleanup here.
 *     }
 *
 *     int main(int argc, char* argv[]) {
 *         TestFn* tests[] = {&it_goes_moo, NULL};
 *         return test_run(tests, &test_cleanup);
 *     }
 */


#include <stdio.h>
#include <stdlib.h>

#include "postgres.h"			/* Needed for `nodes/pg_list.h` to not cause
								 * compile errors. */
#include "nodes/pg_list.h"		/* For `List` type. */

typedef struct
{
	size_t		passed;
	size_t		failed;
	size_t		skipped;
}			TestState;

typedef void (TestFn) (TestState * test_state);

typedef void (TestCleanupFn) (void);

/* Functions defined in framework/main.c */
int			TEST_BOUNDED_STRCMP(char *s1, char *s2);
void		TEST_ASSERT_LIST_EQUAL_impl(TestState * test_state, char *actual_str, List *actual, List *expected);
void		TEST_ASSERT_LIST_LENGTH_impl(TestState * test_state, char *lst_str, List *lst, size_t expected_len);
void		TEST_ASSERT_STR_EQUAL_impl(TestState * test_state, char *actual_str, char *actual, char *expected);

/* Everything below here is the actual user-facing API. */

#define TEST_PASS() (test_state->passed++)
#define TEST_FAIL(...) (printf(__VA_ARGS__), test_state->failed++)
#define TEST_SKIP(...) (printf("  SKIP: " __VA_ARGS__), test_state->skipped++)

/* Prints the name of the test and the line number. */
#define TEST_INIT() printf("%s (line %i)\n", __func__, __LINE__)

/* Assert that `actual` and `expected` should contain the same items, but may be in a different order. */
#define TEST_ASSERT_LIST_EQUAL(actual, expected) TEST_ASSERT_LIST_EQUAL_impl(test_state, #actual, actual, expected)

/* Assert that `lst` contains `len` items. */
#define TEST_ASSERT_LIST_LENGTH(lst, len) TEST_ASSERT_LIST_LENGTH_impl(test_state, #lst, lst, len)

/* Assert that `actual` is a string containing the same text as `expected`. */
#define TEST_ASSERT_STR_EQUAL(actual, expected) TEST_ASSERT_STR_EQUAL_impl(test_state, #actual, actual, expected)

/* Run each test in order, passing the same TestState object. */
/* `test_cleanup()` is run between each test if it is not NULL. */
int			test_run(TestFn * tests[], TestCleanupFn * test_cleanup);
int			test_run_with_mcxt(TestFn * tests[], TestCleanupFn * test_cleanup);

#define TEST_LIST_MAKE6(a,b,c,d,e,f) lappend(list_make5(a,b,c,d,e), f)
#define TEST_LIST_MAKE7(a,b,c,d,e,f,g) lappend(TEST_LIST_MAKE6(a,b,c,d,e,f), g)
#define TEST_LIST_MAKE8(a,b,c,d,e,f,g,h) lappend(TEST_LIST_MAKE7(a,b,c,d,e,f,g), h)
#define TEST_LIST_MAKE9(a,b,c,d,e,f,g,h,i) lappend(TEST_LIST_MAKE8(a,b,c,d,e,f,g,h), i)

#endif
