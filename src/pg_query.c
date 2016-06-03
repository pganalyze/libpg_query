#include "pg_query.h"
#include "pg_query_internal.h"
#include <mb/pg_wchar.h>

const char* progname = "pg_query";

void pg_query_init(void)
{
	MemoryContextInit();
	SetDatabaseEncoding(PG_UTF8);
}

void pg_query_free_error(PgQueryError *error)
{
	free(error->message);
	free(error->funcname);
	free(error->filename);

	if (error->context) {
		free(error->context);
	}

	free(error);
}
