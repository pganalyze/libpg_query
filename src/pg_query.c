#include "pg_query.h"
#include "pg_query_internal.h"

#include <mb/pg_wchar.h>
#include <miscadmin.h>
#include <tcop/tcopprot.h>

/* goosedb fork: protobuf-c nesting counter (see protobuf-c.c) */
extern __thread unsigned protobuf_c_unpack_nesting;
#include <utils/memutils.h>
#include <utils/memdebug.h>
#include "protobuf-c/protobuf-c.h"
#include <utils/guc_hooks.h>

/*
 * pthread is needed unconditionally by pg_query_arm_stack_guard() (it asks
 * the running thread for its stack size), not just by the thread-exit hook.
 */
#include <pthread.h>

#include <signal.h>

const char* progname = "pg_query";

__thread sig_atomic_t pg_query_initialized = 0;

#ifdef HAVE_PTHREAD
static pthread_key_t pg_query_thread_exit_key;
static void pg_query_thread_exit(void *key);
#endif

void pg_query_init(void)
{
	if (pg_query_initialized != 0) return;
	pg_query_initialized = 1;

	MemoryContextInit();
	SetDatabaseEncoding(PG_UTF8);

#ifdef HAVE_PTHREAD
	pthread_key_create(&pg_query_thread_exit_key, pg_query_thread_exit);
	pthread_setspecific(pg_query_thread_exit_key, TopMemoryContext);
#endif
}

void pg_query_free_top_memory_context(MemoryContext context)
{
	Assert(MemoryContextIsValid(context));

	/*
	 * After this, no memory contexts are valid anymore, so ensure that
	 * the current context is the top-level context.
	 */
	Assert(TopMemoryContext == CurrentMemoryContext);

	MemoryContextDeleteChildren(context);

	/* Clean up the aset.c freelist, to leave no unused context behind */
	AllocSetDeleteFreeList();

	context->methods->delete_context(context);

	VALGRIND_DESTROY_MEMPOOL(context);

	/* Without this, Valgrind will complain */
	free(context);

	/* Reset pointers */
	TopMemoryContext = NULL;
	CurrentMemoryContext = NULL;
	ErrorContext = NULL;
}

#ifdef HAVE_PTHREAD
static void pg_query_thread_exit(void *key)
{
	MemoryContext context = (MemoryContext) key;
	pg_query_free_top_memory_context(context);
}
#endif

void pg_query_exit(void)
{
	pg_query_free_top_memory_context(TopMemoryContext);
}

/*
 * pg_query_arm_stack_guard: make check_stack_depth() usable on this thread.
 *
 * Two things have to be true before check_stack_depth() can fire:
 *
 *   1. stack_base_ptr must be non-NULL -- stack_is_too_deep() returns false
 *      unconditionally while it is NULL. set_stack_base() sets it.
 *   2. max_stack_depth_bytes must be a limit that actually fits below the
 *      running thread's stack. The compile-time default is 100kB, which is
 *      *smaller* than what ordinary queries legitimately use in the deparse
 *      walker (~1kB of C stack per nesting level), so leaving it alone would
 *      reject valid input.
 *
 * Both are __thread, and a caller may invoke us from any thread (Go's cgo
 * calls run on the OS thread backing the current M, which changes over time),
 * so we re-arm on every entry. The cost is one frame-address read plus, on
 * the first call for a thread, one pthread attribute query.
 *
 * The limit is derived from the thread's *actual* stack size rather than
 * hardcoded: the same statement that is safe on an 8MB thread overflows a
 * 512kB one, so a fixed number is wrong on some platform by construction.
 * We allow the recursion to use half of the thread stack. PostgreSQL makes
 * the same kind of check in reverse -- check_max_stack_depth() refuses a
 * max_stack_depth that leaves less than STACK_DEPTH_SLOP below the kernel
 * limit -- but it can read getrlimit() because it owns the main thread; we
 * have to ask the thread itself.
 */
static __thread int pg_query_stack_limit_kb = 0;

static void
pg_query_arm_stack_guard(void)
{
	set_stack_base();

	if (pg_query_stack_limit_kb == 0)
	{
		size_t		stack_bytes = 0;

#if defined(__APPLE__)
		stack_bytes = pthread_get_stacksize_np(pthread_self());
#elif defined(HAVE_PTHREAD) && defined(__GLIBC__)
		{
			pthread_attr_t attr;

			if (pthread_getattr_np(pthread_self(), &attr) == 0)
			{
				void	   *addr;
				size_t		size = 0;

				if (pthread_attr_getstack(&attr, &addr, &size) == 0)
					stack_bytes = size;
				pthread_attr_destroy(&attr);
			}
		}
#endif

		/*
		 * Fall back to PostgreSQL's own default when the platform will not
		 * tell us. 2MB is what postgresql.conf ships, and it is small enough
		 * to sit inside the 8MB stacks that both glibc and macOS give threads
		 * by default.
		 */
		if (stack_bytes == 0)
			pg_query_stack_limit_kb = 2048;
		else
		{
			size_t		limit_kb = (stack_bytes / 2) / 1024;

			/*
			 * Clamp: never below 64kB (a limit that small would reject
			 * trivial statements and is a sign the query failed), never
			 * above 1GB (max_stack_depth is an int in kB).
			 */
			if (limit_kb < 64)
				limit_kb = 64;
			else if (limit_kb > 1024 * 1024)
				limit_kb = 1024 * 1024;

			pg_query_stack_limit_kb = (int) limit_kb;
		}
	}

	/*
	 * Reset the protobuf-c unpack nesting counter. A longjmp out of an
	 * enclosing PostgreSQL walker (check_stack_depth's ereport, a syntax
	 * error) skips protobuf-c's own decrement, so without this reset the
	 * counter would creep up and eventually reject valid input on this thread.
	 */
	protobuf_c_unpack_nesting = 0;

	max_stack_depth = pg_query_stack_limit_kb;
	assign_max_stack_depth(pg_query_stack_limit_kb, NULL);
}

/*
 * NOTE (goosedb fork): a palloc-backed allocator for protobuf-c.
 *
 * libpg_query passed NULL (protobuf-c's malloc/free default) to every
 * unpack call. That made the unpack recursion impossible to guard: the only
 * stack-accurate check we have is check_stack_depth(), which raises via
 * ereport()/longjmp, and a longjmp out of protobuf-c would abandon every
 * submessage it had malloc'ed -- an unbounded leak on a path untrusted input
 * controls, which is a worse bug than the one being fixed.
 *
 * With palloc the unwind is free: the surrounding pg_query memory context is
 * deleted on the way out (pg_query_exit_memory_context), so a rejected
 * message leaks nothing. protobuf-c supports exactly this through
 * ProtobufCAllocator, so no protobuf-c change is needed for the allocation
 * side.
 *
 * 🚨 The matching free_unpacked() calls must pass the same allocator (or be
 * dropped); freeing palloc'ed memory with free() would corrupt the heap.
 */
static void *
pg_query_protobuf_alloc(void *allocator_data, size_t size)
{
	(void) allocator_data;
	return palloc(size);
}

static void
pg_query_protobuf_free(void *allocator_data, void *data)
{
	(void) allocator_data;
	pfree(data);
}

ProtobufCAllocator pg_query_protobuf_allocator = {
	pg_query_protobuf_alloc,
	pg_query_protobuf_free,
	NULL
};

MemoryContext pg_query_enter_memory_context()
{
	MemoryContext ctx = NULL;

	pg_query_init();

	/*
	 * Every public entry point funnels through here, so this is the one place
	 * that has to arm the guard. Doing it per entry (rather than once per
	 * thread) also keeps the base at the outermost frame of *this* call.
	 */
	pg_query_arm_stack_guard();

	Assert(CurrentMemoryContext == TopMemoryContext);
	ctx = AllocSetContextCreate(TopMemoryContext,
								"pg_query",
								ALLOCSET_DEFAULT_SIZES);
	MemoryContextSwitchTo(ctx);

	return ctx;
}

void pg_query_exit_memory_context(MemoryContext ctx)
{
	// Return to previous PostgreSQL memory context
	MemoryContextSwitchTo(TopMemoryContext);

	MemoryContextDelete(ctx);
	ctx = NULL;
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
