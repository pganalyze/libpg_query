#include <pg_query.h>

#include <errno.h>
#include <signal.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(__APPLE__) || defined(__linux__)
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#endif

/*
 * Regression test for protobuf arena out-of-memory handling.
 *
 * The generated upb message setters write through the message pointer without
 * checking it, so an arena allocation that fails by returning NULL makes the
 * encoder crash instead of raising an error. The fix (pg_query_upb_alloc in
 * src/pg_query.c) turns every arena allocation failure into a PostgreSQL
 * "out of memory" error that the callers' PG_CATCH blocks report normally.
 * Without that fix the capped scan below segfaults.
 *
 * Raising RLIMIT_AS is the obvious way to trigger this, but macOS ignores
 * RLIMIT_AS/RLIMIT_DATA for malloc (setrlimit even fails with EINVAL), so the
 * cap is enforced in userspace instead: this binary defines its own
 * malloc/calloc/realloc/free, forwards them to the real allocator, and fails
 * allocations of ARENA_OOM_FAIL_MIN_SIZE or more once ARENA_OOM_CAP bytes are
 * outstanding. That models "the heap ran out of memory" deterministically on
 * every platform.
 *
 * Allocations below ARENA_OOM_FAIL_MIN_SIZE always succeed so that PostgreSQL
 * can still report the error: CopyErrorData and the malloc/strdup of the
 * PgQueryError in the PG_CATCH blocks happen while the heap is still at the
 * cap. Arena block requests at OOM time are far above that threshold, so the
 * protobuf arena is what trips the cap.
 *
 * Each case runs in a forked child because the unpatched failure mode is a
 * segfault, and because the cap state is process-global. A child killed by a
 * signal is reported as the pre-fix crash.
 */

#if defined(__APPLE__)

#include <malloc/malloc.h>

#define real_malloc(size) malloc_zone_malloc(malloc_default_zone(), (size))
#define real_calloc(n, size) malloc_zone_calloc(malloc_default_zone(), (n), (size))
#define real_realloc(ptr, size) malloc_zone_realloc(malloc_default_zone(), (ptr), (size))
#define real_free(ptr) malloc_zone_free(malloc_default_zone(), (ptr))
#define alloc_usable_size(ptr) malloc_size(ptr)

#elif defined(__linux__)

#include <malloc.h>

extern void *__libc_malloc(size_t size);
extern void *__libc_calloc(size_t nmemb, size_t size);
extern void *__libc_realloc(void *ptr, size_t size);
extern void __libc_free(void *ptr);

#define real_malloc(size) __libc_malloc(size)
#define real_calloc(n, size) __libc_calloc((n), (size))
#define real_realloc(ptr, size) __libc_realloc((ptr), (size))
#define real_free(ptr) __libc_free(ptr)
#define alloc_usable_size(ptr) malloc_usable_size(ptr)

#endif

#if defined(__APPLE__) || defined(__linux__)

/*
 * The capped workload ("SELECT 1,1,...,1" with ITEMS pairs) peaks at roughly
 * 115 MB before the protobuf arena starts growing (input string, palloc'd
 * token array plus its repalloc transient), and needs roughly 115-160 MB more
 * to finish (the arena holds the message plus the serialized copy). The cap
 * sits inside that window so the arena trips it mid-build. Tune by rerunning
 * with ARENA_OOM_DEBUG=1, which prints each child's high-water mark.
 */
#ifndef ARENA_OOM_CAP
#define ARENA_OOM_CAP (192UL * 1024 * 1024)
#endif

#define ARENA_OOM_FAIL_MIN_SIZE (64UL * 1024)

#define SCAN_ITEMS 2000000 /* ~4 MB query, ~4M tokens */

/* Child exit statuses, mapped to messages by the parent. */
#define STATUS_OK 0
#define STATUS_UNEXPECTED_ERROR 1
#define STATUS_NO_OOM 2  /* cap never tripped, so the case proved nothing */
#define STATUS_WRONG_ERROR 3

/*
 * Crash-prone children can wedge in crash reporting (sandboxes, CI images
 * with crash handlers), so the parent polls instead of blocking forever:
 * the suite must fail, not stall. 120s is far above the uncapped control
 * case even on slow CI machines.
 */
#define CHILD_TIMEOUT_SECS 120

static size_t outstanding_bytes;
static size_t highwater_bytes;
static bool cap_enabled;

static bool over_cap(size_t size)
{
	/*
	 * The comparison avoids overflow for absurd sizes: anything larger than
	 * the cap can never fit.
	 */
	if (size >= ARENA_OOM_CAP)
		return true;
	return outstanding_bytes + size > ARENA_OOM_CAP;
}

void *
malloc(size_t size)
{
	void *p;

	if (cap_enabled && size >= ARENA_OOM_FAIL_MIN_SIZE && over_cap(size))
	{
		errno = ENOMEM;
		return NULL;
	}

	p = real_malloc(size);
	if (p != NULL)
	{
		outstanding_bytes += alloc_usable_size(p);
		if (outstanding_bytes > highwater_bytes)
			highwater_bytes = outstanding_bytes;
	}
	return p;
}

void *
calloc(size_t nmemb, size_t size)
{
	void *p;
	size_t total = nmemb * size;

	if (nmemb != 0 && size != 0 && total / size != nmemb)
		total = SIZE_MAX;

	if (cap_enabled && total >= ARENA_OOM_FAIL_MIN_SIZE && over_cap(total))
	{
		errno = ENOMEM;
		return NULL;
	}

	p = real_calloc(nmemb, size);
	if (p != NULL)
	{
		outstanding_bytes += alloc_usable_size(p);
		if (outstanding_bytes > highwater_bytes)
			highwater_bytes = outstanding_bytes;
	}
	return p;
}

void *
realloc(void *ptr, size_t size)
{
	size_t old_size;
	void *p;

	if (ptr == NULL)
		return malloc(size);

	if (cap_enabled && size >= ARENA_OOM_FAIL_MIN_SIZE && over_cap(size))
	{
		errno = ENOMEM;
		return NULL;
	}

	old_size = alloc_usable_size(ptr);
	p = real_realloc(ptr, size);
	if (p != NULL)
	{
		size_t new_size = alloc_usable_size(p);

		if (new_size >= old_size)
			outstanding_bytes += new_size - old_size;
		else
			outstanding_bytes -= old_size - new_size;
		if (outstanding_bytes > highwater_bytes)
			highwater_bytes = outstanding_bytes;
	}
	return p;
}

void
free(void *ptr)
{
	size_t size;

	if (ptr == NULL)
		return;

	size = alloc_usable_size(ptr);
	real_free(ptr);
	outstanding_bytes = size > outstanding_bytes ? 0 : outstanding_bytes - size;
}

static void
debug_report(const char *what)
{
	if (getenv("ARENA_OOM_DEBUG") != NULL)
		fprintf(stderr, "arena_oom: %s: outstanding %zu MB, high-water %zu MB\n",
				what, outstanding_bytes / (1024 * 1024), highwater_bytes / (1024 * 1024));
	fflush(stderr);
}

static char *
build_wide_query(void)
{
	static const char prefix[] = "SELECT 1";
	static const char item[] = ",1";
	size_t len = sizeof(prefix) - 1 + (size_t) SCAN_ITEMS * (sizeof(item) - 1) + 1;
	char *query = malloc(len);
	char *p = query;

	p += sprintf(p, "%s", prefix);
	for (int i = 0; i < SCAN_ITEMS; i++)
		p += sprintf(p, "%s", item);
	return query;
}

/*
 * Control case: without the cap the same workload must succeed, so that the
 * capped case failing with "out of memory" can only be the cap doing its job.
 */
static int
child_control(void)
{
	char *query = build_wide_query();
	PgQueryScanResult result = pg_query_scan(query);

	if (result.error != NULL)
	{
		fprintf(stderr, "arena_oom: uncapped scan failed: %s\n", result.error->message);
		pg_query_free_scan_result(result);
		free(query);
		return STATUS_UNEXPECTED_ERROR;
	}

	debug_report("control");
	pg_query_free_scan_result(result);
	free(query);
	return STATUS_OK;
}

/*
 * The regression case: with the heap capped mid-scan, the arena cannot grow
 * past the cap. A build without pg_query_upb_alloc crashes here (the generated
 * setters write through the NULL message that a failing arena allocation
 * yields); a fixed build returns the usual "out of memory" error result.
 */
static int
child_capped(void)
{
	char *query = build_wide_query();
	PgQueryScanResult result;

	pg_query_init();
	cap_enabled = true;

	result = pg_query_scan(query);

	if (result.error == NULL)
	{
		fprintf(stderr, "arena_oom: capped scan succeeded; raise ARENA_OOM_CAP or SCAN_ITEMS\n");
		pg_query_free_scan_result(result);
		free(query);
		return STATUS_NO_OOM;
	}

	if (strstr(result.error->message, "out of memory") == NULL)
	{
		fprintf(stderr, "arena_oom: capped scan failed with unexpected error: %s\n",
				result.error->message);
		pg_query_free_scan_result(result);
		free(query);
		return STATUS_WRONG_ERROR;
	}

	debug_report("capped");
	pg_query_free_scan_result(result);
	free(query);
	return STATUS_OK;
}

static int
run_child(int (*child_main)(void), const char *label)
{
	pid_t pid;
	int status;

	fflush(NULL);

	pid = fork();
	if (pid < 0)
	{
		perror("arena_oom: fork");
		return -1;
	}

	if (pid == 0)
		_exit(child_main());

	int elapsed = 0;
	for (;;)
	{
		pid_t reaped = waitpid(pid, &status, WNOHANG);

		if (reaped == pid)
			break;
		if (reaped < 0 && errno != EINTR)
		{
			perror("arena_oom: waitpid");
			return -1;
		}
		if (elapsed++ >= CHILD_TIMEOUT_SECS)
		{
			kill(pid, SIGKILL);
			while (waitpid(pid, &status, 0) < 0 && errno == EINTR)
				;
			printf("INVALID %s: child timed out after %ds (hang or wedged"
				   " crash handler)\n", label, CHILD_TIMEOUT_SECS);
			return -1;
		}
		sleep(1);
	}

	if (WIFSIGNALED(status))
	{
		printf("INVALID %s: child killed by signal %d - the protobuf arena OOM"
			   " crashed instead of raising an error\n",
			   label, WTERMSIG(status));
		return -1;
	}

	switch (WEXITSTATUS(status))
	{
		case STATUS_OK:
			printf(".");
			return 0;
		case STATUS_UNEXPECTED_ERROR:
			printf("INVALID %s: control scan failed (see stderr above)\n", label);
			return -1;
		case STATUS_NO_OOM:
			printf("INVALID %s: heap cap never tripped (ARENA_OOM_CAP too high,"
				   " see stderr above)\n", label);
			return -1;
		case STATUS_WRONG_ERROR:
			printf("INVALID %s: expected an out of memory error (see stderr above)\n", label);
			return -1;
		default:
			printf("INVALID %s: child exited with status %d\n", label, WEXITSTATUS(status));
			return -1;
	}
}

int
main(void)
{
	int failures = 0;

	/* The workload must fit below the cap when unlimited, then fail on it. */
	failures += run_child(child_control, "arena oom control") < 0;
	failures += run_child(child_capped, "arena oom capped scan") < 0;

	printf("\n");
	printf("test result: %s\n", failures == 0 ? "ok" : "FAILED");
	return failures == 0 ? 0 : 1;
}

#else /* !__APPLE__ && !__linux__ */

int
main(void)
{
	printf(".\n");
	printf("test result: ok (arena_oom skipped: no malloc override for this platform)\n");
	return 0;
}

#endif
