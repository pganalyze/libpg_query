#include <pg_query.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include "deparse_tests.c"

// Removes the location values from the JSON parse tree string, replacing them with nothing
// (we don't use any special replacement value to avoid increasing the string size)
void remove_node_locations(char *parse_tree_json)
{
	char *tokstart;
	char *p;
	size_t remaining_len;

	p = parse_tree_json;
	while ((p = strstr(p, "\"location\":")) != NULL)
	{
		tokstart = p;
		if (*(tokstart - 1) == ',')
			tokstart--;
		p += strlen("\"location\":");
		if (*p == '-')
			p++;
		while (*p >= '0' && *p <= '9')
			p++;
		remaining_len = strlen(p);
		memmove(tokstart, p, remaining_len);
		p = tokstart;
		*(p + remaining_len) = '\0';
	}
}

int run_test(const char *query, bool compare_query_text) {
	PgQueryProtobufParseResult parse_result = pg_query_parse_protobuf(query);

	if (parse_result.error) {
		printf("\nERROR for \"%s\"\n  %s\n", query, parse_result.error->message);
		pg_query_free_protobuf_parse_result(parse_result);
		return EXIT_FAILURE;
	}

	PgQueryDeparseResult deparse_result = pg_query_deparse_protobuf(parse_result.parse_tree);
	if (deparse_result.error) {
		printf("\nERROR for \"%s\"\n  %s\n", query, deparse_result.error->message);
		PgQueryParseResult result = pg_query_parse(query);
		printf("  parsetree: %s\n", result.parse_tree);
		pg_query_free_parse_result(result);
		pg_query_free_protobuf_parse_result(parse_result);
		pg_query_free_deparse_result(deparse_result);
		return EXIT_FAILURE;
	} else if (compare_query_text && strcmp(deparse_result.query, query) != 0) {
		printf("\nQUERY TEXT MISMATCH for \"%s\"\n  actual: \"%s\"\n", query, deparse_result.query);
		pg_query_free_protobuf_parse_result(parse_result);
		pg_query_free_deparse_result(deparse_result);
		return EXIT_FAILURE;
	}

	// Compare the original and the deparsed parse tree, whilst ignoring location data
	int ret_code = EXIT_SUCCESS;
	PgQueryParseResult parse_result_original = pg_query_parse(query);
	PgQueryParseResult parse_result_deparse = pg_query_parse(deparse_result.query);
	if (parse_result_original.error) {
		ret_code = EXIT_FAILURE;
		printf("\nERROR for parsing \"%s\"\n  error: %s\n", query, parse_result_original.error->message);
	} else if (parse_result_deparse.error) {
		ret_code = EXIT_FAILURE;
		printf("\nERROR for parsing deparse of \"%s\"\n  deparsed sql: %s\n  error: %s\n", query, deparse_result.query, parse_result_deparse.error->message);
	} else {
		remove_node_locations(parse_result_original.parse_tree);
		remove_node_locations(parse_result_deparse.parse_tree);

		if (strcmp(parse_result_original.parse_tree, parse_result_deparse.parse_tree) != 0) {
			ret_code = EXIT_FAILURE;
			printf("\nPARSETREE MISMATCH for parsing deparse of \"%s\"\n  deparsed sql: %s\n  original parsetree: %s\n  deparsed parsetree: %s\n",
				   query,
				   deparse_result.query,
				   parse_result_original.parse_tree,
				   parse_result_deparse.parse_tree);
		} else {
			printf(".");
		}
	}

	pg_query_free_protobuf_parse_result(parse_result);
	pg_query_free_parse_result(parse_result_original);
	pg_query_free_parse_result(parse_result_deparse);
	pg_query_free_deparse_result(deparse_result);

	return ret_code;
}

int run_tests_from_file(const char * filename) {
	char *sample_buffer;
	struct stat sample_stat;
	int fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0) {
		printf("\nERROR opening regression test file: %s\n", filename);
		return EXIT_FAILURE;
	}
	fstat(fd, &sample_stat);
	sample_buffer = mmap(0, sample_stat.st_size, PROT_READ, MAP_PRIVATE, fd, 0);

	if (sample_buffer == (void *) -1)
	{
		printf("Could not mmap samples file\n");
		close(fd);
		return EXIT_FAILURE;
	}

	int ret_code = EXIT_SUCCESS;

	PgQuerySplitResult split_result = pg_query_split(sample_buffer);

	for (int i; i < split_result.n_stmts; ++i)
	{
		char *query = strndup(sample_buffer + split_result.stmts[i]->stmt_location, split_result.stmts[i]->stmt_len);
		int test_ret_code = run_test(query, false);
		if (test_ret_code != EXIT_SUCCESS)
			ret_code = test_ret_code;

		free(query);
	}

	pg_query_free_split_result(split_result);

	munmap(sample_buffer, sample_stat.st_size);
	close(fd);

	return ret_code;
}

const char* regressFilenames[] = {
	"select_distinct_on.sql",
	"select_distinct.sql",
	"select_having.sql",
	"select_implicit.sql",
	"select_into.sql",
	"select_parallel.sql",
	"select_views.sql",
	"select.sql"
};
size_t regressFilenameCount = 8;

int main() {
	size_t i;
	bool ret_code = EXIT_SUCCESS;
	int test_ret_code;

	for (i = 0; i < testsLength; i += 1) {
		test_ret_code = run_test(tests[i], true);
		if (test_ret_code != EXIT_SUCCESS)
			ret_code = test_ret_code;
	}

	for (i = 0; i < regressFilenameCount; i += 1) {
		char *filename = malloc(sizeof(char) * strlen("test/sql/postgres_regress/") + strlen(regressFilenames[i]) + 1);
		strcpy(filename, "test/sql/postgres_regress/");
		strcat(filename, regressFilenames[i]);
		test_ret_code = run_tests_from_file(filename);
		free(filename);
		if (test_ret_code != EXIT_SUCCESS)
			ret_code = test_ret_code;
	}

	printf("\n");

	pg_query_exit();

	return ret_code;
}
