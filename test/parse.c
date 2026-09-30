#include <pg_query.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "parse_tests.c"

int main() {
  size_t i;
  bool ret_code = 0;

  for (i = 0; tests[i]; i += 2) {
    PgQueryParseResult result = pg_query_parse(tests[i]);

		if (result.error) {
			ret_code = -1;
			printf("%s\n", result.error->message);
		} else if (strcmp(result.parse_tree, tests[i + 1]) == 0) {
      printf(".");
    } else {
      ret_code = -1;
      printf("INVALID result for \"%s\"\nexpected: %s\n  actual:  %s\n", tests[i], tests[i + 1], result.parse_tree);
    }

    pg_query_free_parse_result(result);
  }

  for (i = 0; error_tests[i]; i += 2) {
    PgQueryParseResult result = pg_query_parse(error_tests[i]);

    if (!result.error) {
      ret_code = -1;
      printf("UNEXPECTED success for \"%s\"\n  expected error: %s\n", error_tests[i], error_tests[i + 1]);
    } else if (strcmp(result.error->message, error_tests[i + 1]) == 0) {
      printf(".");
    } else {
      ret_code = -1;
      printf("INVALID error for \"%s\"\nexpected: %s\n  actual:  %s\n", error_tests[i], error_tests[i + 1], result.error->message);
    }

    pg_query_free_parse_result(result);
  }

  printf("\n");

  pg_query_exit();

  return ret_code;
}
