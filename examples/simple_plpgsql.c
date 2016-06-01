#include <pg_query.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  PgQueryPlpgsqlParseResult result;

  pg_query_init();

  result = pg_query_parse_plpgsql("BEGIN \nIF v_version IS NULL THEN \nRETURN v_name;\nEND IF; \nRETURN v_name || '/' || v_version; \nEND;");

  if (result.error) {
    printf("error: %s at %d\n", result.error->message, result.error->cursorpos);
  } else {
    printf("%s\n", result.plpgsql_func);
  }

  pg_query_free_plpgsql_parse_result(result);

  return 0;
}
