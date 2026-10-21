#include <pg_query.h>

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
	if (size == 0 || size > 64 * 1024) {
		return 0;
	}

	char *query = malloc(size + 1);
	if (query == NULL) {
		return 0;
	}
	memcpy(query, data, size);
	query[size] = '\0';

	PgQueryProtobufParseResult parse_result = pg_query_parse_protobuf(query);
	if (parse_result.error == NULL) {
		PgQueryDeparseCommentsResult comments_result = pg_query_deparse_comments_for_query(query);
		if (comments_result.error == NULL) {
			PostgresDeparseOpts opts = {0};
			opts.comments = comments_result.comments;
			opts.comment_count = comments_result.comment_count;
			opts.indent_size = 1 + data[0] % 8;
			opts.max_line_length = 20 + data[size / 2] % 101;
			opts.trailing_newline = (data[size - 1] & 1) != 0;
			opts.commas_start_of_line = (data[0] & 1) != 0;

			for (int mode = 0; mode < 2; mode++) {
				opts.pretty_print = mode != 0;
				PgQueryDeparseResult deparse_result = pg_query_deparse_protobuf_opts(parse_result.parse_tree, opts);
				if (deparse_result.error == NULL && deparse_result.query != NULL) {
					PgQueryProtobufParseResult reparse_result = pg_query_parse_protobuf(deparse_result.query);
					pg_query_free_protobuf_parse_result(reparse_result);
				}
				pg_query_free_deparse_result(deparse_result);
			}
		} else {
			PgQueryScanResult scan_error = {0};
			scan_error.error = comments_result.error;
			pg_query_free_scan_result(scan_error);
			comments_result.error = NULL;
		}
		pg_query_free_deparse_comments_result(comments_result);
	}
	pg_query_free_protobuf_parse_result(parse_result);
	free(query);
	return 0;
}