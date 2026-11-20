#include <pg_query.h>

#include <assert.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parse_tests.c"

#ifdef USE_VALGRIND
#define THREAD_COUNT 50
#else
#define THREAD_COUNT 500
#endif

/* More threads than glibc (1024) or macOS (512) has thread-specific keys */
#define SEQUENTIAL_THREAD_COUNT 1100

void* test_runner(void*);
void* parse_once(void*);
void* parse_and_exit(void*);

int main() {
  size_t i;
  int ret;
  pthread_t threads[THREAD_COUNT];

  for (i = 0; i < THREAD_COUNT; i += 1) {
    ret = pthread_create(&threads[i], NULL, test_runner, NULL);
    if (ret) {
      perror("ERROR creating pthread");
      return 1;
    }
  }

  for (i = 0; i < THREAD_COUNT; i += 1) {
    pthread_join(threads[i], NULL);
  }

  printf("\n");

  /* Each thread that parses must not use up a thread-specific key */
  for (i = 0; i < SEQUENTIAL_THREAD_COUNT; i += 1) {
    pthread_t thread;
    ret = pthread_create(&thread, NULL, parse_once, NULL);
    if (ret) {
      perror("ERROR creating pthread");
      return 1;
    }
    pthread_join(thread, NULL);
  }

  pthread_key_t key;
  ret = pthread_key_create(&key, NULL);
  if (ret) {
    printf("ERROR creating a pthread key after %d parsing threads: %s\n", SEQUENTIAL_THREAD_COUNT, strerror(ret));
    return 1;
  }
  pthread_key_delete(key);

  /* A thread that cleans up with pg_query_exit() must not have the thread-exit
     destructor free the same memory context again when it exits */
  pthread_t exit_thread;
  ret = pthread_create(&exit_thread, NULL, parse_and_exit, NULL);
  if (ret) {
    perror("ERROR creating pthread");
    return 1;
  }
  pthread_join(exit_thread, NULL);

  return 0;
}

void* parse_once(void* unused_pthread_arg) {
  assert(unused_pthread_arg == NULL);
  PgQueryParseResult result = pg_query_parse("SELECT 1");
  pg_query_free_parse_result(result);
  return NULL;
}

void* parse_and_exit(void* unused_pthread_arg) {
  assert(unused_pthread_arg == NULL);
  PgQueryParseResult result = pg_query_parse("SELECT 1");
  pg_query_free_parse_result(result);
  pg_query_exit();
  return NULL;
}

void* test_runner(void* unused_pthread_arg) {
  assert(unused_pthread_arg == NULL);
  size_t i;

  for (i = 0; tests[i]; i += 2) {
    PgQueryParseResult result = pg_query_parse(tests[i]);

		if (result.error) {
			printf("%s\n", result.error->message);
		} else if (strcmp(result.parse_tree, tests[i + 1]) == 0) {
      printf(".");
    } else {
      printf("INVALID result for \"%s\"\nexpected: %s\nactual: %s\n", tests[i], tests[i + 1], result.parse_tree);
    }

    pg_query_free_parse_result(result);
  }

  return NULL;
}
