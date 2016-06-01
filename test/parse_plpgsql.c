#include <pg_query.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parse_plpgsql_tests.c"

int main() {
  size_t i;
  bool ret_code = 0;

  pg_query_init();

  for (i = 0; i < testsLength; i += 2) {
    PgQueryPlpgsqlParseResult result = pg_query_parse_plpgsql(tests[i]);

    if (strcmp(result.plpgsql_func, tests[i + 1]) == 0) {
      printf(".");
    } else {
      if (result.error) {
        printf("ERROR: %s\n", result.error->message);
        printf("CONTEXT: %s\n", result.error->context);
        printf("LOCATION: %s, %s:%d\n\n", result.error->funcname, result.error->filename, result.error->lineno);
      }
      if (result.stderr_buffer && strlen(result.stderr_buffer) > 0) {
        printf("STDERR: %s\n\n", result.stderr_buffer);
      }
      ret_code = -1;
      printf("INVALID result for \"%s\"\nexpected: %s\nactual: %s\n", tests[i], tests[i + 1], result.plpgsql_func);
    }

    pg_query_free_plpgsql_parse_result(result);
  }

  printf("\n");

  return ret_code;
}
