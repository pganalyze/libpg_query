#include <pg_query.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fingerprint_tests.c"

int main() {
  size_t i;
  bool ret_code = 0;

  pg_query_init();

  for (i = 0; i < testCount; i += 2) {
    PgQueryFingerprintResult result = pg_query_fingerprint(tests[i]);

    if (strcmp(result.hexdigest, tests[i + 1]) == 0) {
      printf(".");
    } else {
      ret_code = -1;
      printf("INVALID (%s needs to be %s, SQL was: %s)\n", result.hexdigest, tests[i + 1], tests[i]);
      pg_query_fingerprint_with_opts(tests[i], true);
    }

    pg_query_free_fingerprint_result(result);
  }

  printf("\n");

  return ret_code;
}
