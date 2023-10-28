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
    PgQueryProtobufParseResult result = pg_query_parse_protobuf_opts(tests[i], mode);

    if (result.error) {
      ret_code = -1;
      printf("%s\n", result.error->message);
    } else {
      printf(".");
    }

    pg_query_free_protobuf_parse_result(result);
  }

  printf("\n");

  pg_query_exit();

  return ret_code;
}
