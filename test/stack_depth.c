/*
 * Deeply nested input must come back as "stack depth limit exceeded", never
 * kill the process. A regression here shows up as a crash of this program
 * rather than as a failed assertion, which is still a test failure.
 *
 * The limit is derived from the running thread's stack, so whether a given
 * depth is rejected depends on how large that stack is. The checks that
 * require a rejection therefore run on a thread this program creates with a
 * 1MB stack. The main thread's stack is not ours to know -- GNU make 3.81, for
 * one, raises RLIMIT_STACK for the commands it runs -- so there the same
 * inputs only have to either succeed or fail with the stack error.
 */

#include <pg_query.h>

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <pthread.h>
#endif

#define STACK_ERROR "stack depth limit exceeded"
#define THREAD_STACK_SIZE (1024 * 1024)

/* Far deeper than a 1MB stack allows on any walker. */
#define DEEP 100000

/* Raised when a protobuf message nests past protobuf-c's level counter. */
#define NESTING_ERROR "could not decode parse tree"

static int failures = 0;

static char *
repeat(const char *head, const char *tail, int n)
{
	size_t		head_len = strlen(head);
	size_t		tail_len = strlen(tail);
	char	   *s = malloc(head_len + tail_len * (size_t) n + 1);
	char	   *p = s;
	int			i;

	memcpy(p, head, head_len);
	p += head_len;
	for (i = 0; i < n; i++)
	{
		memcpy(p, tail, tail_len);
		p += tail_len;
	}
	*p = '\0';
	return s;
}

static void
fail(const char *where, const char *what, const char *detail)
{
	printf("\nFAIL [%s] %s: %s\n", where, what, detail);
	failures++;
}

/*
 * strict: the input must be rejected with the stack error.
 * Otherwise it may also succeed; any other error is still a failure.
 */
static void
expect_stack_error(const char *where, const char *what, PgQueryError *error, bool strict)
{
	if (error == NULL)
	{
		if (strict)
			fail(where, what, "succeeded, expected \"" STACK_ERROR "\"");
		else
			printf(".");
	}
	else if (strcmp(error->message, STACK_ERROR) != 0)
		fail(where, what, error->message);
	else
		printf(".");
}

static void
expect_no_error(const char *where, const char *what, PgQueryError *error)
{
	if (error != NULL)
		fail(where, what, error->message);
	else
		printf(".");
}

static void
run_checks(const char *where, bool strict)
{
	char	   *deep_expr = repeat("SELECT 1", "+1", DEEP);
	char	   *deep_union = repeat("SELECT 1", " UNION ALL SELECT 1", DEEP);
	char	   *deep_after_sibling = repeat("SELECT 1, 1", "+1", DEEP);
	char	   *wide_or = repeat("SELECT x FROM t WHERE x = 1", " OR x = 1", 20000);
	char	   *shallow_union = repeat("SELECT 1", " UNION ALL SELECT 1", 50);
	char	   *shallow_expr = repeat("SELECT 1", "+1", 50);

	/* Each entry point, on input deep enough to hit the limit. */
	{
		PgQueryParseResult r = pg_query_parse(deep_expr);

		expect_stack_error(where, "pg_query_parse", r.error, strict);
		pg_query_free_parse_result(r);
	}
	{
		PgQueryProtobufParseResult r = pg_query_parse_protobuf(deep_expr);

		expect_stack_error(where, "pg_query_parse_protobuf", r.error, strict);
		pg_query_free_protobuf_parse_result(r);
	}
	{
		PgQuerySummaryParseResult r = pg_query_summary(deep_expr, 0, -1);

		expect_stack_error(where, "pg_query_summary", r.error, strict);
		pg_query_free_summary_parse_result(r);
	}
	{
		/*
		 * Normalize has three distinct shapes: an expression chain, a UNION
		 * chain (SelectStmt recurses into the walker directly), and a deep
		 * clause after a sibling that was walked to completion.
		 */
		PgQueryNormalizeResult r = pg_query_normalize(deep_expr);

		expect_stack_error(where, "pg_query_normalize (expression)", r.error, strict);
		pg_query_free_normalize_result(r);

		r = pg_query_normalize(deep_union);
		expect_stack_error(where, "pg_query_normalize (UNION)", r.error, strict);
		pg_query_free_normalize_result(r);

		r = pg_query_normalize(deep_after_sibling);
		expect_stack_error(where, "pg_query_normalize (after sibling)", r.error, strict);
		pg_query_free_normalize_result(r);
	}
	{
		/*
		 * Deparse uses more stack per level than the parser, so there is a
		 * range of depths the parser accepts and deparse must reject. Where
		 * exactly depends on the platform; the requirement is only that each
		 * depth either round-trips or fails cleanly -- with the stack error,
		 * or on a large stack with protobuf-c's level counter.
		 */
		int			depths[] = {1000, 3000, 10000, 30000};
		size_t		i;

		for (i = 0; i < sizeof(depths) / sizeof(depths[0]); i++)
		{
			char	   *sql = repeat("SELECT 1", "+1", depths[i]);
			PgQueryProtobufParseResult parsed = pg_query_parse_protobuf(sql);

			if (parsed.error == NULL)
			{
				PgQueryDeparseResult d = pg_query_deparse_protobuf(parsed.parse_tree);

				if (d.error != NULL && strcmp(d.error->message, STACK_ERROR) != 0 &&
					strcmp(d.error->message, NESTING_ERROR) != 0)
					fail(where, "pg_query_deparse_protobuf", d.error->message);
				else
					printf(".");
				pg_query_free_deparse_result(d);
			}
			else if (strcmp(parsed.error->message, STACK_ERROR) != 0)
				fail(where, "pg_query_parse_protobuf (for deparse)", parsed.error->message);
			pg_query_free_protobuf_parse_result(parsed);
			free(sql);
		}
	}

	/* Large but shallow input, and small nested input, must keep working. */
	{
		PgQueryParseResult r = pg_query_parse(wide_or);

		expect_no_error(where, "pg_query_parse (wide OR list)", r.error);
		pg_query_free_parse_result(r);
	}
	{
		PgQueryNormalizeResult r = pg_query_normalize(shallow_union);

		expect_no_error(where, "pg_query_normalize (shallow UNION)", r.error);
		if (r.error == NULL && strstr(r.normalized_query, "SELECT 1") != NULL)
			fail(where, "pg_query_normalize (shallow UNION)", "a constant was left in place");
		pg_query_free_normalize_result(r);
	}
	{
		PgQueryProtobufParseResult parsed = pg_query_parse_protobuf(shallow_expr);

		expect_no_error(where, "pg_query_parse_protobuf (shallow)", parsed.error);
		if (parsed.error == NULL)
		{
			PgQueryDeparseResult d = pg_query_deparse_protobuf(parsed.parse_tree);

			expect_no_error(where, "pg_query_deparse_protobuf (shallow)", d.error);
			pg_query_free_deparse_result(d);
		}
		pg_query_free_protobuf_parse_result(parsed);
	}

	free(deep_expr);
	free(deep_union);
	free(deep_after_sibling);
	free(wide_or);
	free(shallow_union);
	free(shallow_expr);
}

#ifdef _WIN32
static DWORD WINAPI
thread_main(LPVOID arg)
{
	(void) arg;
	run_checks("1MB thread", true);
	return 0;
}
#else
static void *
thread_main(void *arg)
{
	(void) arg;
	run_checks("1MB thread", true);
	return NULL;
}
#endif

int
main(void)
{
	/* Unbuffered, so a crash still shows which check was running. */
	setvbuf(stdout, NULL, _IONBF, 0);

	run_checks("main thread", false);

#ifdef _WIN32
	{
		HANDLE		thread = CreateThread(NULL, THREAD_STACK_SIZE, thread_main, NULL,
										  STACK_SIZE_PARAM_IS_A_RESERVATION, NULL);

		if (thread == NULL)
		{
			printf("\nCreateThread failed\n");
			return 1;
		}
		WaitForSingleObject(thread, INFINITE);
		CloseHandle(thread);
	}
#else
	{
		pthread_attr_t attr;
		pthread_t	thread;

		pthread_attr_init(&attr);
		pthread_attr_setstacksize(&attr, THREAD_STACK_SIZE);
		if (pthread_create(&thread, &attr, thread_main, NULL) != 0)
		{
			printf("\npthread_create failed\n");
			return 1;
		}
		pthread_join(thread, NULL);
		pthread_attr_destroy(&attr);
	}
#endif

	printf("\n");

	pg_query_exit();

	return failures == 0 ? 0 : 1;
}
