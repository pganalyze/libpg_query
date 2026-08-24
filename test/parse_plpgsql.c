#include <pg_query.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <assert.h>

static bool
expect_error(const char *input, const char *expected_message)
{
	PgQueryPlpgsqlParseResult result = pg_query_parse_plpgsql(input);
	bool success = result.error != NULL &&
		strcmp(result.error->message, expected_message) == 0;

	if (!success)
	{
		printf("Expected error: %s\n", expected_message);
		printf("Actual error: %s\n",
			result.error == NULL ? "(none)" : result.error->message);
	}

	pg_query_free_plpgsql_parse_result(result);
	return success;
}

int main() {
	bool ret_code = EXIT_SUCCESS;
	char *sample_buffer;
	struct stat sample_stat;
	int fd;
	FILE* f_out;
	PgQueryPlpgsqlParseResult result;

	fd = open("test/plpgsql_samples.sql", O_RDONLY);
	if (fd < 0) {
		printf("Could not read samples file\n");
		return EXIT_FAILURE;
    }

	fstat(fd, &sample_stat);

	sample_buffer = malloc(sample_stat.st_size + 1);
	read(fd, sample_buffer, sample_stat.st_size);
	sample_buffer[sample_stat.st_size] = 0;

	if (sample_buffer != (void *) - 1)
	{
		result = pg_query_parse_plpgsql(sample_buffer);
		free(sample_buffer);
		close(fd);
	} else {
		printf("Could not read samples file\n");
		close(fd);
		return EXIT_FAILURE;
	}

	if (result.error) {
		printf("ERROR: %s\n", result.error->message);
		printf("CONTEXT: %s\n", result.error->context);
		printf("LOCATION: %s, %s:%d\n\n", result.error->funcname, result.error->filename, result.error->lineno);

		pg_query_free_plpgsql_parse_result(result);
		return EXIT_FAILURE;
	}

	f_out = fopen("test/plpgsql_samples.actual.json", "w");
	fprintf(f_out, "%s\n", result.plpgsql_funcs);
	fclose(f_out);

	pg_query_free_plpgsql_parse_result(result);

	if (!expect_error("CREATE FUNCTION f() RETURNS void LANGUAGE plpgsql;",
				  "no function body specified"))
		ret_code = EXIT_FAILURE;

	if (!expect_error("DO LANGUAGE plpgsql;",
				  "no inline code specified"))
		ret_code = EXIT_FAILURE;

	pg_query_exit();

	return ret_code;
}
