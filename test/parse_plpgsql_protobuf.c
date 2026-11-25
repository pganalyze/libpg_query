#include <pg_query.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "protobuf/pg_query.upb.h"

/* The files in test/sql/plpgsql_regress (copied from the Postgres source by "make extract_source") */
static const char *regress_files[] = {
	"plpgsql_array.sql",
	"plpgsql_cache.sql",
	"plpgsql_call.sql",
	"plpgsql_control.sql",
	"plpgsql_copy.sql",
	"plpgsql_domain.sql",
	"plpgsql_misc.sql",
	"plpgsql_record.sql",
	"plpgsql_simple.sql",
	"plpgsql_transaction.sql",
	"plpgsql_trap.sql",
	"plpgsql_trigger.sql",
	"plpgsql_varprops.sql",
};

/*
 * The JSON output (checked against test/plpgsql_samples.expected.json by
 * test/parse_plpgsql) and the Protobuf output are generated from the same
 * definitions, so this only verifies the Protobuf path itself: that it fails
 * exactly when the JSON path fails, and that its output decodes to the same
 * number of functions.
 */

static char *
read_file(const char *path)
{
	FILE	   *f = fopen(path, "rb");
	char	   *buf;
	long		len;

	if (f == NULL)
		return NULL;

	fseek(f, 0, SEEK_END);
	len = ftell(f);
	fseek(f, 0, SEEK_SET);

	buf = malloc(len + 1);
	if (fread(buf, 1, len, f) != (size_t) len)
	{
		free(buf);
		fclose(f);
		return NULL;
	}
	buf[len] = '\0';
	fclose(f);

	return buf;
}

/*
 * Number of entries in the "functions" array of the JSON output: objects that
 * start at nesting depth 3 ({"version":...,"functions":[{...},{...}]})
 */
static int
count_json_functions(const char *json)
{
	int			depth = 0;
	int			count = 0;
	bool		in_string = false;
	const char *p;

	for (p = json; *p != '\0'; p++)
	{
		if (in_string)
		{
			if (*p == '\\' && p[1] != '\0')
				p++;
			else if (*p == '"')
				in_string = false;
		}
		else if (*p == '"')
			in_string = true;
		else if (*p == '{' || *p == '[')
		{
			depth++;
			if (*p == '{' && depth == 3)
				count++;
		}
		else if (*p == '}' || *p == ']')
			depth--;
	}

	return count;
}

static bool
check(const char *name, const char *input)
{
	PgQueryPlpgsqlParseResult json_result = pg_query_parse_plpgsql(input);
	PgQueryPlpgsqlProtobufParseResult pb_result = pg_query_parse_plpgsql_protobuf(input);
	bool		ok = true;

	if ((json_result.error == NULL) != (pb_result.error == NULL))
	{
		printf("%s: JSON %s, but Protobuf %s\n", name,
			   json_result.error ? "failed" : "succeeded",
			   pb_result.error ? "failed" : "succeeded");
		ok = false;
	}
	else if (json_result.error != NULL)
	{
		if (strcmp(json_result.error->message, pb_result.error->message) != 0)
		{
			printf("%s: JSON error \"%s\", but Protobuf error \"%s\"\n", name,
				   json_result.error->message, pb_result.error->message);
			ok = false;
		}
	}
	else
	{
		upb_Arena  *arena = upb_Arena_New();
		pg_query_PLpgSQLParseResult *result;
		size_t		n_functions = 0;
		int			n_json_functions = count_json_functions(json_result.plpgsql_funcs);

		result = pg_query_PLpgSQLParseResult_parse(pb_result.parse_tree.data, pb_result.parse_tree.len, arena);
		if (result == NULL)
		{
			printf("%s: could not decode Protobuf output\n", name);
			ok = false;
		}
		else
		{
			pg_query_PLpgSQLParseResult_functions(result, &n_functions);

			if (pg_query_PLpgSQLParseResult_version(result) != PG_VERSION_NUM)
			{
				printf("%s: unexpected version %d\n", name, pg_query_PLpgSQLParseResult_version(result));
				ok = false;
			}
			if ((int) n_functions != n_json_functions)
			{
				printf("%s: %d functions in JSON, but %d in Protobuf\n", name,
					   n_json_functions, (int) n_functions);
				ok = false;
			}
		}
		upb_Arena_Free(arena);
	}

	pg_query_free_plpgsql_parse_result(json_result);
	pg_query_free_plpgsql_protobuf_parse_result(pb_result);

	return ok;
}

static bool
check_file(const char *path)
{
	char	   *input = read_file(path);
	bool		ok;

	if (input == NULL)
	{
		printf("could not read %s\n", path);
		return false;
	}

	ok = check(path, input);
	free(input);

	return ok;
}

int
main()
{
	int			ret_code = EXIT_SUCCESS;
	size_t		i;

	if (!check_file("test/plpgsql_samples.sql"))
		ret_code = EXIT_FAILURE;

	/* The regression tests contain intentional errors, which both outputs must agree on */
	for (i = 0; i < sizeof(regress_files) / sizeof(regress_files[0]); i++)
	{
		char		path[256];

		snprintf(path, sizeof(path), "test/sql/plpgsql_regress/%s", regress_files[i]);
		if (!check_file(path))
			ret_code = EXIT_FAILURE;
	}

	if (!check("empty", ""))
		ret_code = EXIT_FAILURE;
	if (!check("no functions", "SELECT 1;"))
		ret_code = EXIT_FAILURE;
	if (!check("syntax error", "CREATE FUNCTION f() RETURNS int AS $$ BEGIN RETURN; END $$ LANGUAGE plpgsql; SELECT"))
		ret_code = EXIT_FAILURE;
	if (!check("compile error", "CREATE FUNCTION f() RETURNS void LANGUAGE plpgsql;"))
		ret_code = EXIT_FAILURE;

	pg_query_exit();

	return ret_code;
}
