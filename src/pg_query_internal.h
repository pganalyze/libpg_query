#ifndef PG_QUERY_INTERNAL_H
#define PG_QUERY_INTERNAL_H

#include "postgres.h"
#include "utils/memutils.h"
#include "nodes/pg_list.h"

#define STDERR_BUFFER_LEN 4096

/*
 * Maximum protobuf message nesting depth, used for both encoding
 * (pg_query_nodes_to_protobuf) and decoding (pg_query_protobuf_to_nodes).
 *
 * Every expression level costs two message levels (the Node wrapper plus the
 * node message itself), so this allows roughly 5,000 levels of nested
 * expressions (e.g. "a || b || c ..."), far more than upb's default of 100.
 *
 * This is only a sanity cap: what actually prevents stack overflows is the
 * stack depth limit (max_stack_depth, sized per call to the available stack),
 * which upb's encoder and decoder also check (see
 * vendor/upb/patches/0003-stack-depth-check.patch), just like our recursive
 * tree walkers do via check_stack_depth(). Depending on the available stack
 * and the stack used per level, that limit may be reached first.
 */
#define PG_QUERY_PROTOBUF_MAX_DEPTH 10000

typedef struct
{
	List	   *tree;
	char	   *stderr_buffer;
	PgQueryError *error;
}			PgQueryInternalParsetreeAndError;

PgQueryInternalParsetreeAndError pg_query_raw_parse(const char *input, int parser_options);

void		pg_query_free_error(PgQueryError * error);

MemoryContext pg_query_enter_memory_context();
void		pg_query_exit_memory_context(MemoryContext ctx);

/*
 * Opt-in stderr capture around calls that can write to fd 2 (see
 * pg_query_stderr_capture_begin in src/pg_query.c for why this is off by
 * default). When enabled, fd 2 is pointed at a pipe for the duration of the
 * call and the captured text becomes the result's stderr_buffer. The
 * redirection is process-wide, so only one call captures at a time; a
 * concurrent call comes back uncaptured with an empty stderr_buffer.
 *
 * Usage: begin before the work, then on the success path only drain before
 * strduping the buffer, and end after the error handling (idempotent, also
 * correct after a skipped or failed begin).
 */
typedef enum PgQueryStderrCaptureStatus
{
	PG_QUERY_STDERR_CAPTURED,	/* fd 2 redirected; end must run */
	PG_QUERY_STDERR_SKIPPED,	/* capture disabled or contended */
	PG_QUERY_STDERR_PIPE_FAILED	/* no pipe; caller should fail the call */
} PgQueryStderrCaptureStatus;

typedef struct PgQueryStderrCapture
{
	bool		capturing;
	int			read_fd;
	int			saved_stderr_fd;
} PgQueryStderrCapture;

PgQueryStderrCaptureStatus pg_query_stderr_capture_begin(PgQueryStderrCapture *cap);
void		pg_query_stderr_capture_drain(PgQueryStderrCapture *cap, char *buffer, size_t buffer_len);
void		pg_query_stderr_capture_end(PgQueryStderrCapture *cap);

#endif
