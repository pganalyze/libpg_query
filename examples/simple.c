// Welcome to the easiest way to parse an SQL query :-)
// Compile the file like this:
//
// cc -I../ -L../ -lpg_query simple.c

#include <pg_query.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  PgQueryParseResult result;

  pg_query_init();

  result = pg_query_parse("SELECT 1");

  if (result.error) {
    printf("error: %s at %d\n", result.error->message, result.error->cursorpos);
  } else {
    printf("%s\n", result.parse_tree);
  }

  pg_query_free_parse_result(result);

  return 0;
}
