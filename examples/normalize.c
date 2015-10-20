#include <pg_query.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  PgQueryNormalizeResult result;

  pg_query_init();

  result = pg_query_normalize("SELECT 1");

  if (result.error) {
    printf("error: %s at %d\n", result.error->message, result.error->cursorpos);
    free(result.error->message);
    free(result.error);
  } else {
    printf("%s\n", result.normalized_query);
  }

  free(result.normalized_query);

  return 0;
}
