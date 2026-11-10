#include <pg_query.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include "protobuf/pg_query.upb.h"

/*
 * Tests the Protobuf output of pg_query_parse_plpgsql_protobuf. What it
 * contains is tested through the JSON output (test/parse_plpgsql.c), which is
 * generated from the same definitions, so this tests that it can be decoded,
 * has the same functions as the JSON output, and returns errors the same way.
 */

static bool
expect_error(const char *input, const char *expected_message)
{
	PgQueryPlpgsqlProtobufParseResult result = pg_query_parse_plpgsql_protobuf(input);
	bool success = result.error != NULL &&
		strcmp(result.error->message, expected_message) == 0;

	if (!success)
	{
		printf("Expected error: %s\n", expected_message);
		printf("Actual error: %s\n",
			result.error == NULL ? "(none)" : result.error->message);
	}

	pg_query_free_plpgsql_protobuf_parse_result(result);
	return success;
}

/* Returns the number of functions in the JSON output */
static size_t
json_funcs_count(const char *input)
{
	PgQueryPlpgsqlParseResult result = pg_query_parse_plpgsql(input);
	size_t count = 0;
	const char *p;

	for (p = result.plpgsql_funcs; p != NULL && (p = strstr(p, "{\"PLpgSQL_function\":")) != NULL; p++)
		count++;

	pg_query_free_plpgsql_parse_result(result);
	return count;
}

static bool
expect_same_funcs_as_json(const char *input)
{
	PgQueryPlpgsqlProtobufParseResult result = pg_query_parse_plpgsql_protobuf(input);
	upb_Arena *arena = upb_Arena_New();
	pg_query_PlpgsqlParseResult *parse_result;
	size_t n_funcs = 0;
	bool success = false;

	if (result.error)
	{
		printf("ERROR: %s\n", result.error->message);
	}
	else if ((parse_result = pg_query_PlpgsqlParseResult_parse(result.plpgsql_funcs.data, result.plpgsql_funcs.len, arena)) == NULL)
	{
		printf("INVALID result: could not decode PL/pgSQL protobuf output\n");
	}
	else
	{
		pg_query_PlpgsqlParseResult_plpgsql_funcs(parse_result, &n_funcs);
		success = pg_query_PlpgsqlParseResult_version(parse_result) == PG_VERSION_NUM &&
			n_funcs == json_funcs_count(input);
		if (!success)
			printf("INVALID result: version %d, %zu functions, expected %d and %zu functions\n",
				   pg_query_PlpgsqlParseResult_version(parse_result), n_funcs,
				   PG_VERSION_NUM, json_funcs_count(input));
	}

	upb_Arena_Free(arena);
	pg_query_free_plpgsql_protobuf_parse_result(result);
	return success;
}

/* Spot-checks the decoded output for a function that returns a variable */
static bool
expect_return_variable(void)
{
	PgQueryPlpgsqlProtobufParseResult result = pg_query_parse_plpgsql_protobuf(
		"CREATE FUNCTION f() RETURNS int AS $$ DECLARE v int := 1; BEGIN RETURN v; END $$ LANGUAGE plpgsql;");
	upb_Arena *arena = upb_Arena_New();
	pg_query_PlpgsqlParseResult *parse_result = NULL;
	const pg_query_PLpgSQL_function *const *funcs;
	const pg_query_PLpgSQL_datum *const *datums;
	const pg_query_PLpgSQL_stmt *const *body;
	const pg_query_PLpgSQL_var *var;
	size_t n_funcs = 0, n_datums = 0, n_body = 0;
	bool success = false;

	if (result.error == NULL)
		parse_result = pg_query_PlpgsqlParseResult_parse(result.plpgsql_funcs.data, result.plpgsql_funcs.len, arena);

	if (parse_result != NULL)
	{
		funcs = pg_query_PlpgsqlParseResult_plpgsql_funcs(parse_result, &n_funcs);
		if (n_funcs == 1)
		{
			datums = pg_query_PLpgSQL_function_datums(funcs[0], &n_datums);
			body = pg_query_PLpgSQL_stmt_block_body(pg_query_PLpgSQL_function_action(funcs[0]), &n_body);
			if (n_datums == 2 && pg_query_PLpgSQL_datum_has_plpgsql_var(datums[1]) && n_body == 1 &&
				pg_query_PLpgSQL_stmt_has_plpgsql_stmt_return(body[0]))
			{
				var = pg_query_PLpgSQL_datum_plpgsql_var(datums[1]);
				success = upb_StringView_IsEqual(pg_query_PLpgSQL_var_refname(var), upb_StringView_FromString("v")) &&
					pg_query_PLpgSQL_var_dno(var) == 1 &&
					pg_query_PLpgSQL_expr_parse_mode(pg_query_PLpgSQL_var_default_val(var)) == pg_query_RAW_PARSE_PLPGSQL_EXPR &&
					pg_query_PLpgSQL_stmt_return_retvarno(pg_query_PLpgSQL_stmt_plpgsql_stmt_return(body[0])) == 1;
			}
		}
	}

	if (!success)
		printf("INVALID result for a function that returns a variable\n");

	upb_Arena_Free(arena);
	pg_query_free_plpgsql_protobuf_parse_result(result);
	return success;
}

int main() {
	bool ret_code = EXIT_SUCCESS;
	char *sample_buffer;
	struct stat sample_stat;
	int fd;

	fd = open("test/plpgsql_samples.sql", O_RDONLY);
	if (fd < 0) {
		printf("Could not read samples file\n");
		return EXIT_FAILURE;
	}

	fstat(fd, &sample_stat);

	sample_buffer = malloc(sample_stat.st_size + 1);
	read(fd, sample_buffer, sample_stat.st_size);
	sample_buffer[sample_stat.st_size] = 0;
	close(fd);

	if (!expect_same_funcs_as_json(sample_buffer))
		ret_code = EXIT_FAILURE;

	free(sample_buffer);

	if (!expect_same_funcs_as_json("SELECT 1;"))
		ret_code = EXIT_FAILURE;

	if (!expect_same_funcs_as_json("CREATE FUNCTION f() RETURNS int LANGUAGE sql RETURN 1;"))
		ret_code = EXIT_FAILURE;

	if (!expect_return_variable())
		ret_code = EXIT_FAILURE;

	if (!expect_error("CREATE FUNCTION f() RETURNS void LANGUAGE plpgsql;",
				  "no function body specified"))
		ret_code = EXIT_FAILURE;

	if (!expect_error("DO LANGUAGE plpgsql;",
				  "no inline code specified"))
		ret_code = EXIT_FAILURE;

	if (!expect_error("SELECT * FROM",
				  "syntax error at end of input"))
		ret_code = EXIT_FAILURE;

	pg_query_exit();

	return ret_code;
}
