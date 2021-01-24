#include <pg_query.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "deparse_tests.c"

int main() {
    size_t i;
    bool ret_code = 0;

    for (i = 0; i < testsLength; i += 1) {
        PgQueryProtobufParseResult parse_result = pg_query_parse_protobuf(tests[i]);

        if (parse_result.error) {
            ret_code = -1;
            printf("\nERROR for \"%s\"\n  %s\n", tests[i], parse_result.error->message);
            pg_query_free_protobuf_parse_result(parse_result);
            continue;
        }

        PgQueryDeparseResult deparse_result = pg_query_deparse_protobuf(parse_result.parse_tree);
        if (deparse_result.error) {
            ret_code = -1;
            printf("\nERROR for \"%s\"\n  %s\n", tests[i], deparse_result.error->message);
            PgQueryParseResult result = pg_query_parse(tests[i]);
            printf("  parsetree: %s\n", result.parse_tree);
            pg_query_free_parse_result(result);
        } else if (strcmp(deparse_result.query, tests[i]) == 0) {
            printf(".");
        } else {
            ret_code = -1;
            printf("\nINVALID result\n  expected: \"%s\"\n    actual: \"%s\"\n", tests[i], deparse_result.query);
        }

        pg_query_free_protobuf_parse_result(parse_result);
        pg_query_free_deparse_result(deparse_result);
    }

    printf("\n");

    pg_query_exit();

    return ret_code;
}
