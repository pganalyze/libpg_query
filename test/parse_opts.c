#include <pg_query.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "parse_opts_tests.c"

int main() {
  size_t i;
  bool ret_code = 0;

  for (i = 0; i < testsLength; i += 3) {
    PgQueryParseMode mode = atoi(tests[i+1]);
    PgQueryParseResult result = pg_query_parse_opts(tests[i], mode);

		if (result.error) {
			ret_code = -1;
			printf("%s\n", result.error->message);
		} else if (strcmp(result.parse_tree, tests[i + 2]) == 0) {
      printf(".");
    } else {
      ret_code = -1;
      printf("INVALID result for \"%s\" with %d mode\nexpected: %s\n  actual:  %s\n", tests[i], mode, tests[i + 2], result.parse_tree);
    }

    pg_query_free_parse_result(result);
  }

  printf("\n");

  pg_query_exit();

  return ret_code;
}
