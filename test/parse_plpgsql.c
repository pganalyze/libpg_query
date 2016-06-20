#include <pg_query.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <libgen.h>
#include <assert.h>

#include <pg_query_internal.h>
#include <nodes/parsenodes.h>
#include <nodes/nodeFuncs.h>

typedef struct createFunctionStmts
{
	CreateFunctionStmt *stmts;
    int stmts_buf_size;
    int stmts_count;
} createFunctionStmts;

static bool create_function_stmts_walker(Node *node, createFunctionStmts *state)
{
	bool result;

	if (node == NULL) return false;

	if (IsA(node, CreateFunctionStmt))
	{
		if (state->stmts_count >= state->stmts_buf_size)
		{
			state->stmts_buf_size *= 2;
			state->stmts = (CreateFunctionStmt*) repalloc(state->stmts, state->stmts_buf_size * sizeof(CreateFunctionStmt));
		}
		state->stmts[state->stmts_count] = *((CreateFunctionStmt *) node);
		state->stmts_count++;
	}

	PG_TRY();
	{
		result = raw_expression_tree_walker(node, create_function_stmts_walker, (void*) state);
	}
	PG_CATCH();
	{
		FlushErrorState();
		result = false;
	}
	PG_END_TRY();

	return result;
}

int main() {
	size_t i;
	bool ret_code = EXIT_SUCCESS;
	char *sample_buffer;
	struct stat sample_stat;
    createFunctionStmts statements;
    int fd;
    FILE* f_out;

	pg_query_init();

	fd = open("test/plpgsql_samples.sql", O_RDONLY);
	if (fd < 0) {
        printf("Could not read samples file\n");
        return EXIT_FAILURE;
    }

	fstat(fd, &sample_stat);
	sample_buffer = mmap(0, sample_stat.st_size, PROT_READ, MAP_PRIVATE, fd, 0);

	if (sample_buffer != (void *) - 1)
	{
        PgQueryInternalParsetreeAndError result = pg_query_raw_parse(sample_buffer);
        munmap(sample_buffer, sample_stat.st_size);

        if (result.error) {
            printf("Parse ERROR in samples file: %s\n", result.error->message);
            pg_query_free_error(result.error);
            return EXIT_FAILURE;
        }

        statements.stmts_buf_size = 100;
		statements.stmts = (CreateFunctionStmt*) palloc(statements.stmts_buf_size * sizeof(CreateFunctionStmt));
		statements.stmts_count = 0;

        create_function_stmts_walker((Node*) result.tree, &statements);
    } else {
        printf("Could not mmap samples file\n");
        return EXIT_FAILURE;
    }

    f_out = fopen("test/plpgsql_samples.actual.json", "w");

    for (i = 0; i < statements.stmts_count; i++) {
        const ListCell *lc;
        CreateFunctionStmt stmt;

        stmt = statements.stmts[i];
        fprintf(f_out, "// %s\n", strVal(linitial(stmt.funcname)));

        foreach(lc, stmt.options)
        {
            DefElem* elem = (DefElem*) lfirst(lc);

            if (strcmp(elem->defname, "as") == 0) {
                const ListCell *lc2;

                assert(IsA(elem->arg, List));

                foreach(lc2, (List*) elem->arg)
                {
                    PgQueryPlpgsqlParseResult result = pg_query_parse_plpgsql(strVal(lfirst(lc2)));

                    if (result.error) {
                         printf("ERROR: %s\n", result.error->message);
                         printf("CONTEXT: %s\n", result.error->context);
                         printf("LOCATION: %s, %s:%d\n\n", result.error->funcname, result.error->filename, result.error->lineno);
                    }
                    if (result.stderr_buffer && strlen(result.stderr_buffer) > 0) {
                        printf("STDERR: %s\n\n", result.stderr_buffer);
                    }

                    fprintf(f_out, "%s\n", result.plpgsql_func);

                    pg_query_free_plpgsql_parse_result(result);
                }
            }
        }
    }

    close(fd);

	return ret_code;
}
