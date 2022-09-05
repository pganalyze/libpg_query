/*--------------------------------------------------------------------
 * Symbols referenced in this file:
 * - pgStatSessionEndCause
 *--------------------------------------------------------------------
 */

/* ----------
 * pgstat.c
 *
 *	All the statistics collector stuff hacked up in one big, ugly file.
 *
 *	TODO:	- Separate collector, postmaster and backend stuff
 *			  into different files.
 *
 *			- Add some automatic call for pgstat vacuuming.
 *
 *			- Add a pgstat config column to pg_database, so this
 *			  entire thing can be enabled/disabled on a per db basis.
 *
 *	Copyright (c) 2001-2021, PostgreSQL Global Development Group
 *
 *	src/backend/postmaster/pgstat.c
 * ----------
 */
#include "postgres.h"

#include <unistd.h>
#include <fcntl.h>
#include <sys/param.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <time.h>
#ifdef HAVE_SYS_SELECT_H
#include <sys/select.h>
#endif

#include "access/heapam.h"
#include "access/htup_details.h"
#include "access/tableam.h"
#include "access/transam.h"
#include "access/twophase_rmgr.h"
#include "access/xact.h"
#include "catalog/pg_database.h"
#include "catalog/pg_proc.h"
#include "common/ip.h"
#include "executor/instrument.h"
#include "libpq/libpq.h"
#include "libpq/pqsignal.h"
#include "mb/pg_wchar.h"
#include "miscadmin.h"
#include "pgstat.h"
#include "postmaster/autovacuum.h"
#include "postmaster/fork_process.h"
#include "postmaster/interrupt.h"
#include "postmaster/postmaster.h"
#include "replication/slot.h"
#include "replication/walsender.h"
#include "storage/backendid.h"
#include "storage/dsm.h"
#include "storage/fd.h"
#include "storage/ipc.h"
#include "storage/latch.h"
#include "storage/lmgr.h"
#include "storage/pg_shmem.h"
#include "storage/proc.h"
#include "storage/procsignal.h"
#include "utils/builtins.h"
#include "utils/guc.h"
#include "utils/memutils.h"
#include "utils/ps_status.h"
#include "utils/rel.h"
#include "utils/snapmgr.h"
#include "utils/timestamp.h"

/* ----------
 * Timer definitions.
 * ----------
 */
#define PGSTAT_STAT_INTERVAL	500 /* Minimum time between stats file
									 * updates; in milliseconds. */

#define PGSTAT_RETRY_DELAY		10	/* How long to wait between checks for a
									 * new file; in milliseconds. */

#define PGSTAT_MAX_WAIT_TIME	10000	/* Maximum time to wait for a stats
										 * file update; in milliseconds. */

#define PGSTAT_INQ_INTERVAL		640 /* How often to ping the collector for a
									 * new file; in milliseconds. */

#define PGSTAT_RESTART_INTERVAL 60	/* How often to attempt to restart a
									 * failed statistics collector; in
									 * seconds. */

#define PGSTAT_POLL_LOOP_COUNT	(PGSTAT_MAX_WAIT_TIME / PGSTAT_RETRY_DELAY)
#define PGSTAT_INQ_LOOP_COUNT	(PGSTAT_INQ_INTERVAL / PGSTAT_RETRY_DELAY)

/* Minimum receive buffer size for the collector's socket. */
#define PGSTAT_MIN_RCVBUF		(100 * 1024)


/* ----------
 * The initial size hints for the hash tables used in the collector.
 * ----------
 */
#define PGSTAT_DB_HASH_SIZE		16
#define PGSTAT_TAB_HASH_SIZE	512
#define PGSTAT_FUNCTION_HASH_SIZE	512
#define PGSTAT_REPLSLOT_HASH_SIZE	32


/* ----------
 * GUC parameters
 * ----------
 */



/* ----------
 * Built from GUC parameter
 * ----------
 */




/*
 * BgWriter and WAL global statistics counters.
 * Stored directly in a stats message structure so they can be sent
 * without needing to copy things around.  We assume these init to zeroes.
 */



/*
 * WAL usage counters saved from pgWALUsage at the previous call to
 * pgstat_send_wal(). This is used to calculate how much WAL usage
 * happens between pgstat_send_wal() calls, by substracting
 * the previous counters from the current ones.
 */


/*
 * List of SLRU names that we keep stats for.  There is no central registry of
 * SLRUs, so we use this fixed list instead.  The "other" entry is used for
 * all SLRUs without an explicit entry (e.g. SLRUs in extensions).
 */


#define SLRU_NUM_ELEMENTS	lengthof(slru_names)

/*
 * SLRU statistics counts waiting to be sent to the collector.  These are
 * stored directly in stats message format so they can be sent without needing
 * to copy things around.  We assume this variable inits to zeroes.  Entries
 * are one-to-one with slru_names[].
 */


/* ----------
 * Local data
 * ----------
 */








/*
 * Structures in which backends store per-table info that's waiting to be
 * sent to the collector.
 *
 * NOTE: once allocated, TabStatusArray structures are never moved or deleted
 * for the life of the backend.  Also, we zero out the t_id fields of the
 * contained PgStat_TableStatus structs whenever they are not actively in use.
 * This allows relcache pgstat_info pointers to be treated as long-lived data,
 * avoiding repeated searches in pgstat_initstats() when a relation is
 * repeatedly opened during a transaction.
 */
#define TABSTAT_QUANTUM		100 /* we alloc this many at a time */

typedef struct TabStatusArray
{
	struct TabStatusArray *tsa_next;	/* link to next array, if any */
	int			tsa_used;		/* # entries currently used */
	PgStat_TableStatus tsa_entries[TABSTAT_QUANTUM];	/* per-table data */
} TabStatusArray;



/*
 * pgStatTabHash entry: map from relation OID to PgStat_TableStatus pointer
 */
typedef struct TabStatHashEntry
{
	Oid			t_id;
	PgStat_TableStatus *tsa_entry;
} TabStatHashEntry;

/*
 * Hash table for O(1) t_id -> tsa_entry lookup
 */


/*
 * Backends store per-function info that's waiting to be sent to the collector
 * in this hash table (indexed by function OID).
 */


/*
 * Indicates if backend has some function stats that it hasn't yet
 * sent to the collector.
 */


/*
 * Tuple insertion/deletion counts for an open transaction can't be propagated
 * into PgStat_TableStatus counters until we know if it is going to commit
 * or abort.  Hence, we keep these counts in per-subxact structs that live
 * in TopTransactionContext.  This data structure is designed on the assumption
 * that subxacts won't usually modify very many tables.
 */
typedef struct PgStat_SubXactStatus
{
	int			nest_level;		/* subtransaction nest level */
	struct PgStat_SubXactStatus *prev;	/* higher-level subxact if any */
	PgStat_TableXactStatus *first;	/* head of list for this subxact */
} PgStat_SubXactStatus;










__thread SessionEndType pgStatSessionEndCause = DISCONNECT_NORMAL;


/* Record that's written to 2PC state file when pgstat state is persisted */
typedef struct TwoPhasePgStatRecord
{
	PgStat_Counter tuples_inserted; /* tuples inserted in xact */
	PgStat_Counter tuples_updated;	/* tuples updated in xact */
	PgStat_Counter tuples_deleted;	/* tuples deleted in xact */
	PgStat_Counter inserted_pre_trunc;	/* tuples inserted prior to truncate */
	PgStat_Counter updated_pre_trunc;	/* tuples updated prior to truncate */
	PgStat_Counter deleted_pre_trunc;	/* tuples deleted prior to truncate */
	Oid			t_id;			/* table's OID */
	bool		t_shared;		/* is it a shared catalog? */
	bool		t_truncated;	/* was the relation truncated? */
} TwoPhasePgStatRecord;

/*
 * Info about current "snapshot" of stats file
 */



/*
 * Cluster wide statistics, kept in the stats collector.
 * Contains statistics that are not collected per database
 * or per table.
 */






/*
 * List of OIDs of databases we need to write out.  If an entry is InvalidOid,
 * it means to write only the shared-catalog stats ("DB 0"); otherwise, we
 * will write both that DB's data and the shared stats.
 */


/*
 * Total time charged to functions so far in the current backend.
 * We use this to help separate "self" and "other" time charges.
 * (We assume this initializes to zero.)
 */



/* ----------
 * Local function forward declarations
 * ----------
 */
#ifdef EXEC_BACKEND
static pid_t pgstat_forkexec(void);
#endif

NON_EXEC_STATIC void PgstatCollectorMain(int argc, char *argv[]) pg_attribute_noreturn();

static PgStat_StatDBEntry *pgstat_get_db_entry(Oid databaseid, bool create);
static PgStat_StatTabEntry *pgstat_get_tab_entry(PgStat_StatDBEntry *dbentry,
												 Oid tableoid, bool create);
static void pgstat_write_statsfiles(bool permanent, bool allDbs);
static void pgstat_write_db_statsfile(PgStat_StatDBEntry *dbentry, bool permanent);
static HTAB *pgstat_read_statsfiles(Oid onlydb, bool permanent, bool deep);
static void pgstat_read_db_statsfile(Oid databaseid, HTAB *tabhash, HTAB *funchash, bool permanent);
static void backend_read_statsfile(void);

static bool pgstat_write_statsfile_needed(void);
static bool pgstat_db_requested(Oid databaseid);

static PgStat_StatReplSlotEntry *pgstat_get_replslot_entry(NameData name, bool create_it);
static void pgstat_reset_replslot(PgStat_StatReplSlotEntry *slotstats, TimestampTz ts);

static void pgstat_send_tabstat(PgStat_MsgTabstat *tsmsg, TimestampTz now);
static void pgstat_send_funcstats(void);
static void pgstat_send_slru(void);
static HTAB *pgstat_collect_oids(Oid catalogid, AttrNumber anum_oid);
static bool pgstat_should_report_connstat(void);
static void pgstat_report_disconnect(Oid dboid);

static PgStat_TableStatus *get_tabstat_entry(Oid rel_id, bool isshared);

static void pgstat_setup_memcxt(void);

static void pgstat_setheader(PgStat_MsgHdr *hdr, StatMsgType mtype);
static void pgstat_send(void *msg, int len);

static void pgstat_recv_inquiry(PgStat_MsgInquiry *msg, int len);
static void pgstat_recv_tabstat(PgStat_MsgTabstat *msg, int len);
static void pgstat_recv_tabpurge(PgStat_MsgTabpurge *msg, int len);
static void pgstat_recv_dropdb(PgStat_MsgDropdb *msg, int len);
static void pgstat_recv_resetcounter(PgStat_MsgResetcounter *msg, int len);
static void pgstat_recv_resetsharedcounter(PgStat_MsgResetsharedcounter *msg, int len);
static void pgstat_recv_resetsinglecounter(PgStat_MsgResetsinglecounter *msg, int len);
static void pgstat_recv_resetslrucounter(PgStat_MsgResetslrucounter *msg, int len);
static void pgstat_recv_resetreplslotcounter(PgStat_MsgResetreplslotcounter *msg, int len);
static void pgstat_recv_autovac(PgStat_MsgAutovacStart *msg, int len);
static void pgstat_recv_vacuum(PgStat_MsgVacuum *msg, int len);
static void pgstat_recv_analyze(PgStat_MsgAnalyze *msg, int len);
static void pgstat_recv_archiver(PgStat_MsgArchiver *msg, int len);
static void pgstat_recv_bgwriter(PgStat_MsgBgWriter *msg, int len);
static void pgstat_recv_wal(PgStat_MsgWal *msg, int len);
static void pgstat_recv_slru(PgStat_MsgSLRU *msg, int len);
static void pgstat_recv_funcstat(PgStat_MsgFuncstat *msg, int len);
static void pgstat_recv_funcpurge(PgStat_MsgFuncpurge *msg, int len);
static void pgstat_recv_recoveryconflict(PgStat_MsgRecoveryConflict *msg, int len);
static void pgstat_recv_deadlock(PgStat_MsgDeadlock *msg, int len);
static void pgstat_recv_checksum_failure(PgStat_MsgChecksumFailure *msg, int len);
static void pgstat_recv_connect(PgStat_MsgConnect *msg, int len);
static void pgstat_recv_disconnect(PgStat_MsgDisconnect *msg, int len);
static void pgstat_recv_replslot(PgStat_MsgReplSlot *msg, int len);
static void pgstat_recv_tempfile(PgStat_MsgTempFile *msg, int len);

/* ------------------------------------------------------------
 * Public functions called from postmaster follow
 * ------------------------------------------------------------
 */

/* ----------
 * pgstat_init() -
 *
 *	Called from postmaster at startup. Create the resources required
 *	by the statistics collector process.  If unable to do so, do not
 *	fail --- better to let the postmaster start with stats collection
 *	disabled.
 * ----------
 */
#define TESTBYTEVAL ((char) 199)
#ifdef HAVE_UNIX_SOCKETS
#endif

/*
 * subroutine for pgstat_reset_all
 */


/*
 * pgstat_reset_all() -
 *
 * Remove the stats files.  This is currently used only if WAL
 * recovery is needed after a crash.
 */


#ifdef EXEC_BACKEND

/*
 * pgstat_forkexec() -
 *
 * Format up the arglist for, then fork and exec, statistics collector process
 */
static pid_t
pgstat_forkexec(void)
{
	char	   *av[10];
	int			ac = 0;

	av[ac++] = "postgres";
	av[ac++] = "--forkcol";
	av[ac++] = NULL;			/* filled in by postmaster_forkexec */

	av[ac] = NULL;
	Assert(ac < lengthof(av));

	return postmaster_forkexec(ac, av);
}
#endif							/* EXEC_BACKEND */


/*
 * pgstat_start() -
 *
 *	Called from postmaster at startup or after an existing collector
 *	died.  Attempt to fire up a fresh statistics collector.
 *
 *	Returns PID of child process, or 0 if fail.
 *
 *	Note: if fail, we will be called again from the postmaster main loop.
 */
#ifdef EXEC_BACKEND
#else
#endif
#ifndef EXEC_BACKEND
#endif



/* ------------------------------------------------------------
 * Public functions used by backends follow
 *------------------------------------------------------------
 */


/* ----------
 * pgstat_report_stat() -
 *
 *	Must be called by processes that performs DML: tcop/postgres.c, logical
 *	receiver processes, SPI worker, etc. to send the so far collected
 *	per-table and function usage statistics to the collector.  Note that this
 *	is called only when not within a transaction, so it is fair to use
 *	transaction stop time as an approximation of current time.
 *
 *	"disconnect" is "true" only for the last call before the backend
 *	exits.  This makes sure that no data is lost and that interrupted
 *	sessions are reported correctly.
 * ----------
 */


/*
 * Subroutine for pgstat_report_stat: finish and send a tabstat message
 */


/*
 * Subroutine for pgstat_report_stat: populate and send a function stat message
 */



/* ----------
 * pgstat_vacuum_stat() -
 *
 *	Will tell the collector about objects he can get rid of.
 * ----------
 */



/* ----------
 * pgstat_collect_oids() -
 *
 *	Collect the OIDs of all objects listed in the specified system catalog
 *	into a temporary hash table.  Caller should hash_destroy the result
 *	when done with it.  (However, we make the table in CurrentMemoryContext
 *	so that it will be freed properly in event of an error.)
 * ----------
 */



/* ----------
 * pgstat_drop_database() -
 *
 *	Tell the collector that we just dropped a database.
 *	(If the message gets lost, we will still clean the dead DB eventually
 *	via future invocations of pgstat_vacuum_stat().)
 * ----------
 */



/* ----------
 * pgstat_drop_relation() -
 *
 *	Tell the collector that we just dropped a relation.
 *	(If the message gets lost, we will still clean the dead entry eventually
 *	via future invocations of pgstat_vacuum_stat().)
 *
 *	Currently not used for lack of any good place to call it; we rely
 *	entirely on pgstat_vacuum_stat() to clean out stats for dead rels.
 * ----------
 */
#ifdef NOT_USED
void
pgstat_drop_relation(Oid relid)
{
	PgStat_MsgTabpurge msg;
	int			len;

	if (pgStatSock == PGINVALID_SOCKET)
		return;

	msg.m_tableid[0] = relid;
	msg.m_nentries = 1;

	len = offsetof(PgStat_MsgTabpurge, m_tableid[0]) + sizeof(Oid);

	pgstat_setheader(&msg.m_hdr, PGSTAT_MTYPE_TABPURGE);
	msg.m_databaseid = MyDatabaseId;
	pgstat_send(&msg, len);
}
#endif							/* NOT_USED */

/* ----------
 * pgstat_reset_counters() -
 *
 *	Tell the statistics collector to reset counters for our database.
 *
 *	Permission checking for this function is managed through the normal
 *	GRANT system.
 * ----------
 */


/* ----------
 * pgstat_reset_shared_counters() -
 *
 *	Tell the statistics collector to reset cluster-wide shared counters.
 *
 *	Permission checking for this function is managed through the normal
 *	GRANT system.
 * ----------
 */


/* ----------
 * pgstat_reset_single_counter() -
 *
 *	Tell the statistics collector to reset a single counter.
 *
 *	Permission checking for this function is managed through the normal
 *	GRANT system.
 * ----------
 */


/* ----------
 * pgstat_reset_slru_counter() -
 *
 *	Tell the statistics collector to reset a single SLRU counter, or all
 *	SLRU counters (when name is null).
 *
 *	Permission checking for this function is managed through the normal
 *	GRANT system.
 * ----------
 */


/* ----------
 * pgstat_reset_replslot_counter() -
 *
 *	Tell the statistics collector to reset a single replication slot
 *	counter, or all replication slots counters (when name is null).
 *
 *	Permission checking for this function is managed through the normal
 *	GRANT system.
 * ----------
 */


/* ----------
 * pgstat_report_autovac() -
 *
 *	Called from autovacuum.c to report startup of an autovacuum process.
 *	We are called before InitPostgres is done, so can't rely on MyDatabaseId;
 *	the db OID must be passed in, instead.
 * ----------
 */



/* ---------
 * pgstat_report_vacuum() -
 *
 *	Tell the collector about the table we just vacuumed.
 * ---------
 */


/* --------
 * pgstat_report_analyze() -
 *
 *	Tell the collector about the table we just analyzed.
 *
 * Caller must provide new live- and dead-tuples estimates, as well as a
 * flag indicating whether to reset the changes_since_analyze counter.
 * --------
 */


/* --------
 * pgstat_report_recovery_conflict() -
 *
 *	Tell the collector about a Hot Standby recovery conflict.
 * --------
 */


/* --------
 * pgstat_report_deadlock() -
 *
 *	Tell the collector about a deadlock detected.
 * --------
 */




/* --------
 * pgstat_report_checksum_failures_in_db() -
 *
 *	Tell the collector about one or more checksum failures.
 * --------
 */


/* --------
 * pgstat_report_checksum_failure() -
 *
 *	Tell the collector about a checksum failure.
 * --------
 */


/* --------
 * pgstat_report_tempfile() -
 *
 *	Tell the collector about a temporary file.
 * --------
 */


/* --------
 * pgstat_report_connect() -
 *
 *	Tell the collector about a new connection.
 * --------
 */


/* --------
 * pgstat_report_disconnect() -
 *
 *	Tell the collector about a disconnect.
 * --------
 */


/* --------
 * pgstat_should_report_connstats() -
 *
 *	We report session statistics only for normal backend processes.  Parallel
 *	workers run in parallel, so they don't contribute to session times, even
 *	though they use CPU time. Walsender processes could be considered here,
 *	but they have different session characteristics from normal backends (for
 *	example, they are always "active"), so they would skew session statistics.
 * ----------
 */


/* ----------
 * pgstat_report_replslot() -
 *
 *	Tell the collector about replication slot statistics.
 * ----------
 */


/* ----------
 * pgstat_report_replslot_create() -
 *
 *	Tell the collector about creating the replication slot.
 * ----------
 */


/* ----------
 * pgstat_report_replslot_drop() -
 *
 *	Tell the collector about dropping the replication slot.
 * ----------
 */


/* ----------
 * pgstat_ping() -
 *
 *	Send some junk data to the collector to increase traffic.
 * ----------
 */


/* ----------
 * pgstat_send_inquiry() -
 *
 *	Notify collector that we need fresh data.
 * ----------
 */



/*
 * Initialize function call usage data.
 * Called by the executor before invoking a function.
 */


/*
 * find_funcstat_entry - find any existing PgStat_BackendFunctionEntry entry
 *		for specified function
 *
 * If no entry, return NULL, don't create a new one
 */


/*
 * Calculate function call usage and update stat counters.
 * Called by the executor after invoking a function.
 *
 * In the case of a set-returning function that runs in value-per-call mode,
 * we will see multiple pgstat_init_function_usage/pgstat_end_function_usage
 * calls for what the user considers a single call of the function.  The
 * finalize flag should be TRUE on the last call.
 */



/* ----------
 * pgstat_initstats() -
 *
 *	Initialize a relcache entry to count access statistics.
 *	Called whenever a relation is opened.
 *
 *	We assume that a relcache entry's pgstat_info field is zeroed by
 *	relcache.c when the relcache entry is made; thereafter it is long-lived
 *	data.  We can avoid repeated searches of the TabStatus arrays when the
 *	same relation is touched repeatedly within a transaction.
 * ----------
 */


/*
 * get_tabstat_entry - find or create a PgStat_TableStatus entry for rel
 */


/*
 * find_tabstat_entry - find any existing PgStat_TableStatus entry for rel
 *
 * If no entry, return NULL, don't create a new one
 *
 * Note: if we got an error in the most recent execution of pgstat_report_stat,
 * it's possible that an entry exists but there's no hashtable entry for it.
 * That's okay, we'll treat this case as "doesn't exist".
 */


/*
 * get_tabstat_stack_level - add a new (sub)transaction stack entry if needed
 */


/*
 * add_tabstat_xact_level - add a new (sub)transaction state record
 */


/*
 * pgstat_count_heap_insert - count a tuple insertion of n tuples
 */


/*
 * pgstat_count_heap_update - count a tuple update
 */


/*
 * pgstat_count_heap_delete - count a tuple deletion
 */


/*
 * pgstat_truncate_save_counters
 *
 * Whenever a table is truncated, we save its i/u/d counters so that they can
 * be cleared, and if the (sub)xact that executed the truncate later aborts,
 * the counters can be restored to the saved (pre-truncate) values.  Note we do
 * this on the first truncate in any particular subxact level only.
 */


/*
 * pgstat_truncate_restore_counters - restore counters when a truncate aborts
 */


/*
 * pgstat_count_truncate - update tuple counters due to truncate
 */


/*
 * pgstat_update_heap_dead_tuples - update dead-tuples count
 *
 * The semantics of this are that we are reporting the nontransactional
 * recovery of "delta" dead tuples; so t_delta_dead_tuples decreases
 * rather than increasing, and the change goes straight into the per-table
 * counter, not into transactional state.
 */



/* ----------
 * AtEOXact_PgStat
 *
 *	Called from access/transam/xact.c at top-level transaction commit/abort.
 * ----------
 */


/* ----------
 * AtEOSubXact_PgStat
 *
 *	Called from access/transam/xact.c at subtransaction commit/abort.
 * ----------
 */



/*
 * AtPrepare_PgStat
 *		Save the transactional stats state at 2PC transaction prepare.
 *
 * In this phase we just generate 2PC records for all the pending
 * transaction-dependent stats work.
 */


/*
 * PostPrepare_PgStat
 *		Clean up after successful PREPARE.
 *
 * All we need do here is unlink the transaction stats state from the
 * nontransactional state.  The nontransactional action counts will be
 * reported to the stats collector immediately, while the effects on live
 * and dead tuple counts are preserved in the 2PC state file.
 *
 * Note: AtEOXact_PgStat is not called during PREPARE.
 */


/*
 * 2PC processing routine for COMMIT PREPARED case.
 *
 * Load the saved counts into our local pgstats state.
 */


/*
 * 2PC processing routine for ROLLBACK PREPARED case.
 *
 * Load the saved counts into our local pgstats state, but treat them
 * as aborted.
 */



/* ----------
 * pgstat_fetch_stat_dbentry() -
 *
 *	Support function for the SQL-callable pgstat* functions. Returns
 *	the collected statistics for one database or NULL. NULL doesn't mean
 *	that the database doesn't exist, it is just not yet known by the
 *	collector, so the caller is better off to report ZERO instead.
 * ----------
 */



/* ----------
 * pgstat_fetch_stat_tabentry() -
 *
 *	Support function for the SQL-callable pgstat* functions. Returns
 *	the collected statistics for one table or NULL. NULL doesn't mean
 *	that the table doesn't exist, it is just not yet known by the
 *	collector, so the caller is better off to report ZERO instead.
 * ----------
 */



/* ----------
 * pgstat_fetch_stat_funcentry() -
 *
 *	Support function for the SQL-callable pgstat* functions. Returns
 *	the collected statistics for one function or NULL.
 * ----------
 */



/*
 * ---------
 * pgstat_fetch_stat_archiver() -
 *
 *	Support function for the SQL-callable pgstat* functions. Returns
 *	a pointer to the archiver statistics struct.
 * ---------
 */



/*
 * ---------
 * pgstat_fetch_global() -
 *
 *	Support function for the SQL-callable pgstat* functions. Returns
 *	a pointer to the global statistics struct.
 * ---------
 */


/*
 * ---------
 * pgstat_fetch_stat_wal() -
 *
 *	Support function for the SQL-callable pgstat* functions. Returns
 *	a pointer to the WAL statistics struct.
 * ---------
 */


/*
 * ---------
 * pgstat_fetch_slru() -
 *
 *	Support function for the SQL-callable pgstat* functions. Returns
 *	a pointer to the slru statistics struct.
 * ---------
 */


/*
 * ---------
 * pgstat_fetch_replslot() -
 *
 *	Support function for the SQL-callable pgstat* functions. Returns
 *	a pointer to the replication slot statistics struct.
 * ---------
 */


/*
 * Shut down a single backend's statistics reporting at process exit.
 *
 * Flush any remaining statistics counts out to the collector.
 * Without this, operations triggered during backend exit (such as
 * temp table deletions) won't be counted.
 */


/* ----------
 * pgstat_initialize() -
 *
 *	Initialize pgstats state, and set up our on-proc-exit hook.
 *	Called from InitPostgres and AuxiliaryProcessMain.
 *
 *	NOTE: MyDatabaseId isn't set yet; so the shutdown hook has to be careful.
 * ----------
 */


/* ------------------------------------------------------------
 * Local support functions follow
 * ------------------------------------------------------------
 */


/* ----------
 * pgstat_setheader() -
 *
 *		Set common header fields in a statistics message
 * ----------
 */



/* ----------
 * pgstat_send() -
 *
 *		Send out one statistics message to the collector
 * ----------
 */
#ifdef USE_ASSERT_CHECKING
#endif

/* ----------
 * pgstat_send_archiver() -
 *
 *	Tell the collector about the WAL file that we successfully
 *	archived or failed to archive.
 * ----------
 */


/* ----------
 * pgstat_send_bgwriter() -
 *
 *		Send bgwriter statistics to the collector
 * ----------
 */


/* ----------
 * pgstat_send_wal() -
 *
 *	Send WAL statistics to the collector.
 *
 * If 'force' is not set, WAL stats message is only sent if enough time has
 * passed since last one was sent to reach PGSTAT_STAT_INTERVAL.
 * ----------
 */


/* ----------
 * pgstat_send_slru() -
 *
 *		Send SLRU statistics to the collector
 * ----------
 */



/* ----------
 * PgstatCollectorMain() -
 *
 *	Start up the statistics collector process.  This is the body of the
 *	postmaster child process.
 *
 *	The argc/argv parameters are valid only in EXEC_BACKEND case.
 * ----------
 */
#ifdef WIN32
#endif
#ifdef WIN32
#endif
#ifndef WIN32
#else
#endif

/*
 * Subroutine to clear stats in a database entry
 *
 * Tables and functions hashes are initialized to empty.
 */


/*
 * Lookup the hash table entry for the specified database. If no hash
 * table entry exists, initialize it, if the create parameter is true.
 * Else, return NULL.
 */



/*
 * Lookup the hash table entry for the specified table. If no hash
 * table entry exists, initialize it, if the create parameter is true.
 * Else, return NULL.
 */



/* ----------
 * pgstat_write_statsfiles() -
 *		Write the global statistics file, as well as requested DB files.
 *
 *	'permanent' specifies writing to the permanent files not temporary ones.
 *	When true (happens only when the collector is shutting down), also remove
 *	the temporary files so that backends starting up under a new postmaster
 *	can't read old data before the new collector is ready.
 *
 *	When 'allDbs' is false, only the requested databases (listed in
 *	pending_write_requests) will be written; otherwise, all databases
 *	will be written.
 * ----------
 */


/*
 * return the filename for a DB stat file; filename is the output buffer,
 * of length len.
 */


/* ----------
 * pgstat_write_db_statsfile() -
 *		Write the stat file for a single database.
 *
 *	If writing to the permanent file (happens when the collector is
 *	shutting down only), remove the temporary file so that backends
 *	starting up under a new postmaster can't read the old data before
 *	the new collector is ready.
 * ----------
 */


/* ----------
 * pgstat_read_statsfiles() -
 *
 *	Reads in some existing statistics collector files and returns the
 *	databases hash table that is the top level of the data.
 *
 *	If 'onlydb' is not InvalidOid, it means we only want data for that DB
 *	plus the shared catalogs ("DB 0").  We'll still populate the DB hash
 *	table for all databases, but we don't bother even creating table/function
 *	hash tables for other databases.
 *
 *	'permanent' specifies reading from the permanent files not temporary ones.
 *	When true (happens only when the collector is starting up), remove the
 *	files after reading; the in-memory status is now authoritative, and the
 *	files would be out of date in case somebody else reads them.
 *
 *	If a 'deep' read is requested, table/function stats are read, otherwise
 *	the table/function hash tables remain empty.
 * ----------
 */



/* ----------
 * pgstat_read_db_statsfile() -
 *
 *	Reads in the existing statistics collector file for the given database,
 *	filling the passed-in tables and functions hash tables.
 *
 *	As in pgstat_read_statsfiles, if the permanent file is requested, it is
 *	removed after reading.
 *
 *	Note: this code has the ability to skip storing per-table or per-function
 *	data, if NULL is passed for the corresponding hashtable.  That's not used
 *	at the moment though.
 * ----------
 */


/* ----------
 * pgstat_read_db_statsfile_timestamp() -
 *
 *	Attempt to determine the timestamp of the last db statfile write.
 *	Returns true if successful; the timestamp is stored in *ts. The caller must
 *	rely on timestamp stored in *ts iff the function returns true.
 *
 *	This needs to be careful about handling databases for which no stats file
 *	exists, such as databases without a stat entry or those not yet written:
 *
 *	- if there's a database entry in the global file, return the corresponding
 *	stats_timestamp value.
 *
 *	- if there's no db stat entry (e.g. for a new or inactive database),
 *	there's no stats_timestamp value, but also nothing to write so we return
 *	the timestamp of the global statfile.
 * ----------
 */


/*
 * If not already done, read the statistics collector stats file into
 * some hash tables.  The results will be kept until pgstat_clear_snapshot()
 * is called (typically, at end of transaction).
 */



/* ----------
 * pgstat_setup_memcxt() -
 *
 *	Create pgStatLocalContext, if not already done.
 * ----------
 */



/* ----------
 * pgstat_clear_snapshot() -
 *
 *	Discard any data collected in the current transaction.  Any subsequent
 *	request will cause new snapshots to be read.
 *
 *	This is also invoked during transaction commit or abort to discard
 *	the no-longer-wanted snapshot.
 * ----------
 */



/* ----------
 * pgstat_recv_inquiry() -
 *
 *	Process stat inquiry requests.
 * ----------
 */



/* ----------
 * pgstat_recv_tabstat() -
 *
 *	Count what the backend has done.
 * ----------
 */



/* ----------
 * pgstat_recv_tabpurge() -
 *
 *	Arrange for dead table removal.
 * ----------
 */



/* ----------
 * pgstat_recv_dropdb() -
 *
 *	Arrange for dead database removal
 * ----------
 */



/* ----------
 * pgstat_recv_resetcounter() -
 *
 *	Reset the statistics for the specified database.
 * ----------
 */


/* ----------
 * pgstat_recv_resetsharedcounter() -
 *
 *	Reset some shared statistics of the cluster.
 * ----------
 */


/* ----------
 * pgstat_recv_resetsinglecounter() -
 *
 *	Reset a statistics for a single object
 * ----------
 */


/* ----------
 * pgstat_recv_resetslrucounter() -
 *
 *	Reset some SLRU statistics of the cluster.
 * ----------
 */


/* ----------
 * pgstat_recv_resetreplslotcounter() -
 *
 *	Reset some replication slot statistics of the cluster.
 * ----------
 */



/* ----------
 * pgstat_recv_autovac() -
 *
 *	Process an autovacuum signaling message.
 * ----------
 */


/* ----------
 * pgstat_recv_vacuum() -
 *
 *	Process a VACUUM message.
 * ----------
 */


/* ----------
 * pgstat_recv_analyze() -
 *
 *	Process an ANALYZE message.
 * ----------
 */



/* ----------
 * pgstat_recv_archiver() -
 *
 *	Process a ARCHIVER message.
 * ----------
 */


/* ----------
 * pgstat_recv_bgwriter() -
 *
 *	Process a BGWRITER message.
 * ----------
 */


/* ----------
 * pgstat_recv_wal() -
 *
 *	Process a WAL message.
 * ----------
 */


/* ----------
 * pgstat_recv_slru() -
 *
 *	Process a SLRU message.
 * ----------
 */


/* ----------
 * pgstat_recv_recoveryconflict() -
 *
 *	Process a RECOVERYCONFLICT message.
 * ----------
 */


/* ----------
 * pgstat_recv_deadlock() -
 *
 *	Process a DEADLOCK message.
 * ----------
 */


/* ----------
 * pgstat_recv_checksum_failure() -
 *
 *	Process a CHECKSUMFAILURE message.
 * ----------
 */


/* ----------
 * pgstat_recv_replslot() -
 *
 *	Process a REPLSLOT message.
 * ----------
 */


/* ----------
 * pgstat_recv_connect() -
 *
 *	Process a CONNECT message.
 * ----------
 */


/* ----------
 * pgstat_recv_disconnect() -
 *
 *	Process a DISCONNECT message.
 * ----------
 */


/* ----------
 * pgstat_recv_tempfile() -
 *
 *	Process a TEMPFILE message.
 * ----------
 */


/* ----------
 * pgstat_recv_funcstat() -
 *
 *	Count what the backend has done.
 * ----------
 */


/* ----------
 * pgstat_recv_funcpurge() -
 *
 *	Arrange for dead function removal.
 * ----------
 */


/* ----------
 * pgstat_write_statsfile_needed() -
 *
 *	Do we need to write out any stats files?
 * ----------
 */


/* ----------
 * pgstat_db_requested() -
 *
 *	Checks whether stats for a particular DB need to be written to a file.
 * ----------
 */


/* ----------
 * pgstat_replslot_entry
 *
 * Return the entry of replication slot stats with the given name. Return
 * NULL if not found and the caller didn't request to create it.
 *
 * create tells whether to create the new slot entry if it is not found.
 * ----------
 */


/* ----------
 * pgstat_reset_replslot
 *
 * Reset the given replication slot stats.
 * ----------
 */


/*
 * pgstat_slru_index
 *
 * Determine index of entry for a SLRU with a given name. If there's no exact
 * match, returns index of the last "other" entry used for SLRUs defined in
 * external projects.
 */


/*
 * pgstat_slru_name
 *
 * Returns SLRU name for an index. The index may be above SLRU_NUM_ELEMENTS,
 * in which case this returns NULL. This allows writing code that does not
 * know the number of entries in advance.
 */


/*
 * slru_entry
 *
 * Returns pointer to entry with counters for given SLRU (based on the name
 * stored in SlruCtl as lwlock tranche name).
 */


/*
 * SLRU statistics count accumulation functions --- called from slru.c
 */














