#include <pg_query.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "scan_tests.c"

#include "protobuf/pg_query.pb-c.h"

int main() {
  size_t i;
  size_t j;
  bool ret_code = 0;
  PgQuery__ScanResult *scan_result;
  PgQuery__ScanToken *scan_token;
  const char *token_kind;
  const char *keyword_kind;
  PgQueryScanResult result;
  PgQueryScanTokensResult tokens_result;

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
      scan_result = pg_query__scan_result__unpack(NULL, result.pbuf.len, (void*) result.pbuf.data);

      for (j = 0; j < scan_result->n_tokens; j++) {
        char buffer2[1024];
        scan_token = scan_result->tokens[j];
        token_kind = pg_query_token_name((PgQueryToken) scan_token->token);
        keyword_kind = pg_query_keyword_kind_name((PgQueryKeywordKind) scan_token->keyword_kind);
        if (token_kind == NULL) {
          ret_code = -1;
          printf("INVALID result for \"%s\": scan_result token %zu token_kind == NULL\n", tests[i], j);
          break;
        }
        sprintf(buffer2, "%.*s = %s, %s\n", scan_token->end - scan_token->start, &(tests[i][scan_token->start]), token_kind, keyword_kind);
        strcat(buffer, buffer2);
      }

      pg_query__scan_result__free_unpacked(scan_result, NULL);

      if (strcmp(buffer, tests[i + 1]) == 0) {
        printf(".");
      } else {
        ret_code = -1;
        printf("INVALID result for \"%s\"\nexpected:\n%s\nactual:\n%s\n", tests[i], tests[i + 1], buffer);
      }
    }

    pg_query_free_scan_result(result);
  }

  // The plain C token array API must return the same tokens as the protobuf one
  for (i = 0; i < testsCount * 2; i += 2) {
    char buffer[1024];
    buffer[0] = '\0';

    tokens_result = pg_query_scan_tokens(tests[i]);

    if (tokens_result.error) {
      ret_code = -1;
      printf("%s\n", tokens_result.error->message);
    } else {
      for (int k = 0; k < tokens_result.n_tokens; k++) {
        char buffer2[1024];
        PgQueryScanToken token = tokens_result.tokens[k];
        token_kind = pg_query_token_name(token.token);
        keyword_kind = pg_query_keyword_kind_name(token.keyword_kind);
        if (token_kind == NULL) {
          ret_code = -1;
          printf("INVALID result for \"%s\": scan_tokens token %d token_kind == NULL\n", tests[i], k);
          break;
        }
        sprintf(buffer2, "%.*s = %s, %s\n", token.end - token.start, &(tests[i][token.start]), token_kind, keyword_kind);
        strcat(buffer, buffer2);
      }

      if (strcmp(buffer, tests[i + 1]) == 0) {
        printf(".");
      } else {
        ret_code = -1;
        printf("INVALID scan_tokens result for \"%s\"\nexpected:\n%s\nactual:\n%s\n", tests[i], tests[i + 1], buffer);
      }
    }

    pg_query_free_scan_tokens_result(tokens_result);
  }

  // Scanner errors are reported as errors
  result = pg_query_scan("SELECT 'unterminated");
  if (result.error == NULL) {
    ret_code = -1;
    printf("INVALID result for unterminated string: expected an error\n");
  } else {
    printf(".");
  }
  pg_query_free_scan_result(result);

  tokens_result = pg_query_scan_tokens("SELECT 'unterminated");
  if (tokens_result.error == NULL) {
    ret_code = -1;
    printf("INVALID scan_tokens result for unterminated string: expected an error\n");
  } else {
    printf(".");
  }
  pg_query_free_scan_tokens_result(tokens_result);

  // Empty input yields no tokens and no error
  tokens_result = pg_query_scan_tokens("");
  if (tokens_result.error != NULL || tokens_result.n_tokens != 0) {
    ret_code = -1;
    printf("INVALID scan_tokens result for empty input: expected no tokens and no error\n");
  } else {
    printf(".");
  }
  pg_query_free_scan_tokens_result(tokens_result);

  printf("\n");

  pg_query_exit();

  return ret_code;
}
