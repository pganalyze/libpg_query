#include <pg_query.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
	char *new_str = (char *)malloc(size+1);
	if (new_str == NULL){
        return 0;
	}
	memcpy(new_str, data, size);
	new_str[size] = '\0';

	PgQueryProtobufParseResult protobuf_result = pg_query_parse_protobuf(new_str);
	if (protobuf_result.error == NULL) {
		PgQueryDeparseResult deparse_result = pg_query_deparse_protobuf(protobuf_result.parse_tree);
		pg_query_free_deparse_result(deparse_result);
	}
	pg_query_free_protobuf_parse_result(protobuf_result);

	PgQueryFingerprintResult fingerprint_result = pg_query_fingerprint(new_str);
	pg_query_free_fingerprint_result(fingerprint_result);

	PgQueryNormalizeResult normalize_result = pg_query_normalize(new_str);
	pg_query_free_normalize_result(normalize_result);

	PgQueryScanResult scan_result = pg_query_scan(new_str);
	pg_query_free_scan_result(scan_result);

	free(new_str);
	return 0;
}
