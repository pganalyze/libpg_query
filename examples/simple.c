// Welcome to the easiest way to parse an SQL query :-)
// Compile the file like this:
//
// cc -I../ -L../ -lpg_query simple.c

#include <pg_query.h>
#include <stdio.h>

int main() {
  PgQueryParseResult result;

  pg_query_init();

  result = pg_query_parse("SELECT 1");

  printf("%s\n", result.parse_tree);

  return 0;
}
