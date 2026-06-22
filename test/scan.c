#include <pg_query.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "scan_tests.c"

#include "protobuf/pg_query.upb.h"
#include "protobuf/pg_query.enum_names.h"
#include "upb/mem/arena.h"

int main() {
  size_t i;
  size_t j;
  bool ret_code = 0;
  pg_query_ScanResult *scan_result;
  const pg_query_ScanToken *scan_token;
  const char *token_kind;
  const char *keyword_kind;
  PgQueryScanResult result;

  // tests contains pairs of strings
  assert(testsCount % 2 == 0);

  for (i = 0; i < testsCount * 2; i += 2) {
    char buffer[1024];
    buffer[0] = '\0';

    result = pg_query_scan(tests[i]);

    if (result.error) {
      ret_code = -1;
      printf("%s\n", result.error->message);
    } else {
      upb_Arena *arena = upb_Arena_New();
      size_t n_tokens = 0;
      const pg_query_ScanToken *const *tokens;
      scan_result = pg_query_ScanResult_parse(result.pbuf.data, result.pbuf.len, arena);
      tokens = pg_query_ScanResult_tokens(scan_result, &n_tokens);

      for (j = 0; j < n_tokens; j++) {
        char buffer2[1024];
        int32_t start, end;
        scan_token = tokens[j];
        token_kind = pg_query_token_name(pg_query_ScanToken_token(scan_token));
        keyword_kind = pg_query_keyword_kind_name(pg_query_ScanToken_keyword_kind(scan_token));
        if (token_kind == NULL) {
          ret_code = -1;
          printf("INVALID result for \"%s\": scan_result token %zu token_kind == NULL\n", tests[i], j);
          break;
        }
        start = pg_query_ScanToken_start(scan_token);
        end = pg_query_ScanToken_end(scan_token);
        sprintf(buffer2, "%.*s = %s, %s\n", end - start, &(tests[i][start]), token_kind, keyword_kind);
        strcat(buffer, buffer2);
      }

      upb_Arena_Free(arena);

      if (strcmp(buffer, tests[i + 1]) == 0) {
        printf(".");
      } else {
        ret_code = -1;
        printf("INVALID result for \"%s\"\nexpected:\n%s\nactual:\n%s\n", tests[i], tests[i + 1], buffer);
      }
    }

    pg_query_free_scan_result(result);
  }

  printf("\n");

  pg_query_exit();

  return ret_code;
}
