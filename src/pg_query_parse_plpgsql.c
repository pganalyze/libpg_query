#include "pg_query.h"
#include "pg_query_internal.h"
#include "pg_query_json_plpgsql.h"

typedef struct {
  PLpgSQL_function *func;
  char* stderr_buffer;
  PgQueryError* error;
} PgQueryInternalPlpgsqlFuncAndError;

static PgQueryInternalPlpgsqlFuncAndError pg_query_raw_parse_plpgsql(const char*);

PgQueryInternalPlpgsqlFuncAndError pg_query_raw_parse_plpgsql(const char* input)
{
	PgQueryInternalPlpgsqlFuncAndError result = {0};
	MemoryContext parse_context = CurrentMemoryContext;

	char stderr_buffer[STDERR_BUFFER_LEN + 1] = {0};
#ifndef DEBUG
	int stderr_global;
	int stderr_pipe[2];
#endif

#ifndef DEBUG
	// Setup pipe for stderr redirection
	if (pipe(stderr_pipe) != 0) {
		PgQueryError* error = malloc(sizeof(PgQueryError));

		error->message = strdup("Failed to open pipe, too many open file descriptors")

		result.error = error;

		return result;
	}

	fcntl(stderr_pipe[0], F_SETFL, fcntl(stderr_pipe[0], F_GETFL) | O_NONBLOCK);

	// Redirect stderr to the pipe
	stderr_global = dup(STDERR_FILENO);
	dup2(stderr_pipe[1], STDERR_FILENO);
	close(stderr_pipe[1]);
#endif

	PG_TRY();
	{
    result.func = plpgsql_compile_inline((char*) input);

#ifndef DEBUG
		// Save stderr for result
		read(stderr_pipe[0], stderr_buffer, STDERR_BUFFER_LEN);
#endif

		result.stderr_buffer = strdup(stderr_buffer);
	}
	PG_CATCH();
	{
		ErrorData* error_data;
		PgQueryError* error;

		MemoryContextSwitchTo(parse_context);
		error_data = CopyErrorData();

		// Note: This is intentionally malloc so exiting the memory context doesn't free this
		error = malloc(sizeof(PgQueryError));
		error->message   = strdup(error_data->message);
		error->filename  = strdup(error_data->filename);
		error->funcname  = strdup(error_data->funcname);
		error->context   = strdup(error_data->context);
		error->lineno    = error_data->lineno;
		error->cursorpos = error_data->cursorpos;

		result.error = error;
		FlushErrorState();
	}
	PG_END_TRY();

#ifndef DEBUG
	// Restore stderr, close pipe
	dup2(stderr_global, STDERR_FILENO);
	close(stderr_pipe[0]);
	close(stderr_global);
#endif

	return result;
}

PgQueryPlpgsqlParseResult pg_query_parse_plpgsql(const char* input)
{
	MemoryContext ctx = NULL;
	PgQueryInternalPlpgsqlFuncAndError func_and_error;
	PgQueryPlpgsqlParseResult result = {0};

	ctx = pg_query_enter_memory_context("pg_query_parse_plpgsql");

	func_and_error = pg_query_raw_parse_plpgsql(input);

	// These are all malloc-ed and will survive exiting the memory context, the caller is responsible to free them now
	result.stderr_buffer = func_and_error.stderr_buffer;
	result.error = func_and_error.error;

	if (func_and_error.func != NULL) {
		char *func_json;

		func_json = plpgsqlToJSON(func_and_error.func);
    plpgsql_free_function_memory(func_and_error.func);

		result.plpgsql_func = strdup(func_json);
		pfree(func_json);
	} else {
		result.plpgsql_func = strdup("[]");
	}

	pg_query_exit_memory_context(ctx);

	return result;
}

void pg_query_free_plpgsql_parse_result(PgQueryPlpgsqlParseResult result)
{
  if (result.error) {
		pg_query_free_error(result.error);
  }

  free(result.plpgsql_func);
  free(result.stderr_buffer);
}
