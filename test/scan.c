#include <pg_query.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "scan_tests.c"

#include "protobuf/pg_query.upb.h"

// Regression test: decoding a scan result with the upb API outside of a
// libpg_query call must work no matter where the last libpg_query call
// happened. The upb decoder checks the stack depth against the reference
// point libpg_query measures at the start of each call, which is cleared
// again when the call exits. A stale reference point from a deep call site
// would otherwise make a shallow decode look like it exceeds the stack budget.
//
// Runs on a pthread with a known stack size, so it is skipped on MSVC (which
// has no pthreads), like test/concurrency.
#ifndef _MSC_VER
#include <pthread.h>

#define STALE_BASE_THREAD_STACK (4 * 1024 * 1024)
#define STALE_BASE_FRAME_SIZE (64 * 1024)
#define STALE_BASE_FRAMES 48 // ~3 MB of the 4 MB thread stack

static PgQueryScanResult scan_deep_in_stack(int frames) {
  volatile char pad[STALE_BASE_FRAME_SIZE];
  PgQueryScanResult result;

  pad[0] = (char) frames;
  pad[STALE_BASE_FRAME_SIZE - 1] = (char) frames;

  if (frames > 0)
    result = scan_deep_in_stack(frames - 1);
  else
    result = pg_query_scan("SELECT 1");

  pad[0] += pad[STALE_BASE_FRAME_SIZE - 1]; // keep the frame from being optimized away

  return result;
}

static void *stale_base_runner(void *arg) {
  bool *ok = arg;
  PgQueryScanResult result = scan_deep_in_stack(STALE_BASE_FRAMES);
  upb_Arena *arena = upb_Arena_New();
  pg_query_ScanResult *scan_result;
  size_t n_tokens = 0;

  *ok = false;
  if (result.error) {
    printf("INVALID result for scan from a deep stack: %s\n", result.error->message);
  } else {
    scan_result = pg_query_ScanResult_parse(result.pbuf.data, result.pbuf.len, arena);
    if (scan_result == NULL) {
      printf("INVALID result: could not decode scan result outside a libpg_query call, after a call from a deep stack\n");
    } else {
      pg_query_ScanResult_tokens(scan_result, &n_tokens);
      if (n_tokens == 2)
        *ok = true;
      else
        printf("INVALID result: expected 2 tokens after decoding, got %zu\n", n_tokens);
    }
  }

  upb_Arena_Free(arena);
  pg_query_free_scan_result(result);

  return NULL;
}

static bool test_decode_after_deep_call(void) {
  pthread_t thread;
  pthread_attr_t attr;
  bool ok = false;

  pthread_attr_init(&attr);
  pthread_attr_setstacksize(&attr, STALE_BASE_THREAD_STACK);
  if (pthread_create(&thread, &attr, stale_base_runner, &ok) != 0) {
    printf("INVALID result: could not create thread\n");
    return false;
  }
  pthread_join(thread, NULL);
  pthread_attr_destroy(&attr);

  return ok;
}
#endif

int main() {
  size_t i;
  int j;
  bool ret_code = 0;
  pg_query_ScanResult *scan_result;
  const pg_query_ScanToken *scan_token;
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
      upb_Arena *arena = upb_Arena_New();
      size_t n_tokens = 0;
      const pg_query_ScanToken *const *tokens;
      scan_result = pg_query_ScanResult_parse(result.pbuf.data, result.pbuf.len, arena);
      if (scan_result == NULL) {
        ret_code = -1;
        printf("INVALID result for \"%s\": could not decode scan result\n", tests[i]);
        upb_Arena_Free(arena);
        pg_query_free_scan_result(result);
        continue;
      }
      tokens = pg_query_ScanResult_tokens(scan_result, &n_tokens);

      for (j = 0; j < n_tokens; j++) {
        char buffer2[1024];
        int32_t start, end;
        scan_token = tokens[j];
        token_kind = pg_query_token_name(pg_query_ScanToken_token(scan_token));
        keyword_kind = pg_query_keyword_kind_name(pg_query_ScanToken_keyword_kind(scan_token));
        if (token_kind == NULL) {
          ret_code = -1;
          printf("INVALID result for \"%s\": scan_result token %d token_kind == NULL\n", tests[i], j);
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

  // The plain C token array API must return the same tokens as the protobuf one
  for (i = 0; i < testsCount * 2; i += 2) {
    char buffer[1024];
    buffer[0] = '\0';

    tokens_result = pg_query_scan_tokens(tests[i]);

    if (tokens_result.error) {
      ret_code = -1;
      printf("%s\n", tokens_result.error->message);
    } else {
      for (j = 0; j < tokens_result.n_tokens; j++) {
        char buffer2[1024];
        PgQueryScanToken token = tokens_result.tokens[j];
        token_kind = pg_query_token_name(token.token);
        keyword_kind = pg_query_keyword_kind_name(token.keyword_kind);
        if (token_kind == NULL) {
          ret_code = -1;
          printf("INVALID result for \"%s\": scan_tokens token %d token_kind == NULL\n", tests[i], j);
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

  // Scanner errors are reported as errors, and must not leak the partially
  // built scan result (checked when running under Valgrind)
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

#ifndef _MSC_VER
  if (test_decode_after_deep_call()) {
    printf(".");
  } else {
    ret_code = -1;
  }
#endif

  printf("\n");

  pg_query_exit();

  return ret_code;
}
