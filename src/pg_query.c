#if defined(__linux__) && !defined(_GNU_SOURCE)
/* Allow using pthread_getattr_np on glibc/musl. Must precede any includes. */
#define _GNU_SOURCE
#endif

#include "pg_query.h"
#include "pg_query_internal.h"

#include <miscadmin.h>
#include <mb/pg_wchar.h>
#include <utils/memutils.h>
#include <utils/memdebug.h>
#include <utils/guc_hooks.h>

#ifdef HAVE_PTHREAD
#include <pthread.h>
#endif

#if defined(HAVE_PTHREAD) && (defined(__FreeBSD__) || defined(__NetBSD__))
/* For pthread_attr_get_np() */
#include <pthread_np.h>
#endif

#if defined(_WIN32)
/* For GetCurrentThreadStackLimits(); port/win32.h already sets _WIN32_WINNT. */
#include <windows.h>
#endif

#include <signal.h>

const char* progname = "pg_query";

__thread sig_atomic_t pg_query_initialized = 0;

#ifdef HAVE_PTHREAD
static pthread_key_t pg_query_thread_exit_key;
static void pg_query_thread_exit(void *key);
#endif

static __thread char *pg_query_lowest_stackaddr = NULL;
static char *get_lowest_stackaddr(void);
static void set_max_stack_depth(void);

void pg_query_init(void)
{
	/*
	 * Set the reference point for stack depth checking, similiar to how
	 * Postgres does in its main() function. We have to re-do this on every
	 * execution since we may be called from different parts in our host
	 * program.
	 *
	 * The check_stack_depth() function called by recursive tree walkers
	 * measures the current stack depth against this base and raises a
	 * "stack depth limit exceeded" error before we overflow and crash.
	 */
	set_stack_base();

	/*
	 * Size the budget to this thread's actual stack; must follow
	 * set_stack_base() so both measure from the same point.
	 */
	set_max_stack_depth();

	/*
	 * Later parts of initialization don't have to re-run if we execute again
	 * in the same thread, since they are not affected by the calling location.
	 */
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

MemoryContext pg_query_enter_memory_context()
{
	MemoryContext ctx = NULL;

	pg_query_init();

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

/*
 * Get this thread's lowest addressable stack address and cache it for
 * subsequent calls. Returns NULL if address can't be determined.
 */
static char *get_lowest_stackaddr(void)
{
	if (pg_query_lowest_stackaddr)
		return pg_query_lowest_stackaddr;

#if defined(_WIN32)
	{
		ULONG_PTR	low, high;

		GetCurrentThreadStackLimits(&low, &high);

		if (low == 0)
			return NULL;

		pg_query_lowest_stackaddr = (char *) low;
	}
#elif defined(HAVE_PTHREAD) && defined(__linux__)
	{
		pthread_attr_t attr;
		void	   *stack_addr = NULL;
		size_t		stack_size = 0;

		if (pthread_getattr_np(pthread_self(), &attr) != 0)
			return NULL;

		if (pthread_attr_getstack(&attr, &stack_addr, &stack_size) == 0 && stack_addr != NULL)
			pg_query_lowest_stackaddr = (char *) stack_addr;

		pthread_attr_destroy(&attr);
	}
#elif defined(HAVE_PTHREAD) && defined(__APPLE__)
	{
		char	   *stack_high = (char *) pthread_get_stackaddr_np(pthread_self());
		size_t		stack_size = pthread_get_stacksize_np(pthread_self());

		if (stack_size == 0)
			return NULL;

		pg_query_lowest_stackaddr = stack_high - stack_size;
	}
#elif defined(HAVE_PTHREAD) && (defined(__FreeBSD__) || defined(__NetBSD__))
	{
		pthread_attr_t attr;
		void	   *stack_addr = NULL;
		size_t		stack_size = 0;

		if (pthread_attr_init(&attr) != 0)
			return NULL;

		if (pthread_attr_get_np(pthread_self(), &attr) == 0 &&
			pthread_attr_getstack(&attr, &stack_addr, &stack_size) == 0 &&
			stack_addr != NULL)
		{
			pg_query_lowest_stackaddr = (char *) stack_addr;
		}

		pthread_attr_destroy(&attr);
	}
#endif

	return pg_query_lowest_stackaddr;
}

/*
 * Raise max_stack_depth to fit the headroom on the calling thread's stack,
 * capped at 2MB, similar to how InitializeGUCOptionsFromEnvironment sets
 * max_stack_depth.
 *
 * Re-evaluated for each call, since libpg_query gets embedded into other
 * programs, so we have to be conscious of our place in the stack, and measure
 * the remaining stack space we can use below the current address.
 */
static void set_max_stack_depth(void)
{
	char		stack_here;
	char*		lowest_stackaddr = get_lowest_stackaddr();
	ssize_t		usable_stack_depth;
	ssize_t		new_limit;

	if (lowest_stackaddr == NULL)
		return;

	usable_stack_depth = (ssize_t) (&stack_here - lowest_stackaddr);
	if (usable_stack_depth < 0)
		return;

	/*
	 * Determine new limit keeping a similar padding to Postgres via
	 * STACK_DEPTH_SLOP (512 kB) to account for error handling and places
	 * where we don't check stack depth frequently.
	 */
	new_limit = (usable_stack_depth - STACK_DEPTH_SLOP) / 1024;

	/*
	 * In case the new limit would put us below 100 kB, ignore it, since that
	 * is our required minimum and the default of the setting.
	 */
	if (new_limit <= 100)
		return;

	/* Clamp at 2MB, like Postgres auto-detection logic. */
	if (new_limit > 2048)
		new_limit = 2048;

	max_stack_depth = (int) new_limit;
	assign_max_stack_depth((int) new_limit, NULL);
}
