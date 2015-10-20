#include <pg_query.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  PgQueryParseResult result;

  pg_query_init();

  result = pg_query_parse("INSERT FROM DOES NOT WORK");

  if (result.error) {
    printf("error: %s at %d\n", result.error->message, result.error->cursorpos);
    free(result.error->message);
    free(result.error);
  } else {
    printf("%s\n", result.parse_tree);
  }

  free(result.parse_tree);
  free(result.stderr_buffer);

  return 0;
}
