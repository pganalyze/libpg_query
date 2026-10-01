#include <pg_query.h>
#include <stdio.h>
#include <stdlib.h>

#include "protobuf/pg_query.upb.h"

int main() {
  PgQueryPlpgsqlProtobufParseResult result;

  result = pg_query_parse_plpgsql_protobuf(" \
  CREATE OR REPLACE FUNCTION cs_fmt_browser_version(v_name varchar, \
                                                  v_version varchar) \
RETURNS varchar AS $$ \
BEGIN \
    IF v_version IS NULL THEN \
        RETURN v_name; \
    END IF; \
    RETURN v_name || '/' || v_version; \
END; \
$$ LANGUAGE plpgsql;");

  if (result.error) {
    printf("error: %s at %d\n", result.error->message, result.error->cursorpos);
  } else {
    // The result is a serialized PLpgSQLParseResult message (see protobuf/pg_query.proto),
    // here decoded with upb; any other protobuf library works just as well
    upb_Arena *arena = upb_Arena_New();
    pg_query_PLpgSQLParseResult *parse_result;
    size_t n_functions = 0;
    const pg_query_PLpgSQL_function* const *functions;

    parse_result = pg_query_PLpgSQLParseResult_parse(result.parse_tree.data, result.parse_tree.len, arena);
    functions = pg_query_PLpgSQLParseResult_functions(parse_result, &n_functions);

    printf("%zu bytes, %zu function(s)\n", result.parse_tree.len, n_functions);
    for (size_t i = 0; i < n_functions; i++) {
      size_t n_datums = 0;
      pg_query_PLpgSQL_function_datums(functions[i], &n_datums);
      printf("function %zu: %zu datums, %u statements\n", i, n_datums,
             pg_query_PLpgSQL_function_nstatements(functions[i]));
    }

    upb_Arena_Free(arena);
  }

  pg_query_free_plpgsql_protobuf_parse_result(result);

  // Optional, this ensures all memory is freed upon program exit (useful when running Valgrind)
  pg_query_exit();

  return 0;
}
