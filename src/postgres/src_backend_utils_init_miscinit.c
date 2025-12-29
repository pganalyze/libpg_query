/*--------------------------------------------------------------------
 * Symbols referenced in this file:
 * - GetUserId
 *--------------------------------------------------------------------
 */

/*-------------------------------------------------------------------------
 *
 * miscinit.c
 *	  miscellaneous initialization support stuff
 *
 * Portions Copyright (c) 1996-2025, PostgreSQL Global Development Group
 * Portions Copyright (c) 1994, Regents of the University of California
 *
 *
 * IDENTIFICATION
 *	  src/backend/utils/init/miscinit.c
 *
 *-------------------------------------------------------------------------
 */
#include "postgres.h"

#include <sys/param.h>
#include <signal.h>
#include <time.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>
#include <grp.h>
#include <pwd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <utime.h>

#include "access/htup_details.h"
#include "access/parallel.h"
#include "catalog/pg_authid.h"
#include "common/file_perm.h"
#include "libpq/libpq.h"
#include "libpq/pqsignal.h"
#include "mb/pg_wchar.h"
#include "miscadmin.h"
#include "pgstat.h"
#include "postmaster/autovacuum.h"
#include "postmaster/interrupt.h"
#include "postmaster/postmaster.h"
#include "replication/slotsync.h"
#include "storage/fd.h"
#include "storage/ipc.h"
#include "storage/latch.h"
#include "storage/pg_shmem.h"
#include "storage/pmsignal.h"
#include "storage/proc.h"
#include "storage/procarray.h"
#include "utils/builtins.h"
#include "utils/guc.h"
#include "utils/inval.h"
#include "utils/memutils.h"
#include "utils/pidfile.h"
#include "utils/syscache.h"
#include "utils/varlena.h"


#define DIRECTORY_LOCK_FILE		"postmaster.pid"





/* List of lock files to be removed at proc exit */




/* ----------------------------------------------------------------
 *		ignoring system indexes support stuff
 *
 * NOTE: "ignoring system indexes" means we do not use the system indexes
 * for lookups (either in hardwired catalog accesses or in planner-generated
 * plans).  We do, however, still update the indexes when a catalog
 * modification is made.
 * ----------------------------------------------------------------
 */




/* ----------------------------------------------------------------
 *	common process startup code
 * ----------------------------------------------------------------
 */

/*
 * Initialize the basic environment for a postmaster child
 *
 * Should be called as early as possible after the child's startup. However,
 * on EXEC_BACKEND builds it does need to be after read_backend_variables().
 */
#ifdef WIN32
#endif
#ifdef WIN32
#endif
#ifdef EXEC_BACKEND
#endif
#ifdef HAVE_SETSID
#endif
#ifndef WIN32
#endif

/*
 * Initialize the basic environment for a standalone process.
 *
 * argv0 has to be suitable to find the program's executable.
 */
#ifdef WIN32
#endif







/*
 * Return a human-readable string representation of a BackendType.
 *
 * The string is not localized here, but we mark the strings for translation
 * so that callers can invoke _() on the result.
 */


/* ----------------------------------------------------------------
 *				database path / name support stuff
 * ----------------------------------------------------------------
 */



/*
 * Validate the proposed data directory.
 *
 * Also initialize file and directory create modes and mode mask.
 */
#if !defined(WIN32) && !defined(__CYGWIN__)
#endif
#if !defined(WIN32) && !defined(__CYGWIN__)
#endif
#if !defined(WIN32) && !defined(__CYGWIN__)
#endif

/*
 * Set data directory, but make sure it's an absolute path.  Use this,
 * never set DataDir directly.
 */


/*
 * Change working directory to DataDir.  Most of the postmaster and backend
 * code assumes that we are in DataDir so it can use relative paths to access
 * stuff in and under the data directory.  For convenience during path
 * setup, however, we don't force the chdir to occur during SetDataDir.
 */



/* ----------------------------------------------------------------
 *	User ID state
 *
 * We have to track several different values associated with the concept
 * of "user ID".
 *
 * AuthenticatedUserId is determined at connection start and never changes.
 *
 * SessionUserId is initially the same as AuthenticatedUserId, but can be
 * changed by SET SESSION AUTHORIZATION (if AuthenticatedUserId is a
 * superuser).  This is the ID reported by the SESSION_USER SQL function.
 *
 * OuterUserId is the current user ID in effect at the "outer level" (outside
 * any transaction or function).  This is initially the same as SessionUserId,
 * but can be changed by SET ROLE to any role that SessionUserId is a
 * member of.  (XXX rename to something like CurrentRoleId?)
 *
 * CurrentUserId is the current effective user ID; this is the one to use
 * for all normal permissions-checking purposes.  At outer level this will
 * be the same as OuterUserId, but it changes during calls to SECURITY
 * DEFINER functions, as well as locally in some specialized commands.
 *
 * SecurityRestrictionContext holds flags indicating reason(s) for changing
 * CurrentUserId.  In some cases we need to lock down operations that are
 * not directly controlled by privilege settings, and this provides a
 * convenient way to do it.
 * ----------------------------------------------------------------
 */






/* We also have to remember the superuser state of the session user */




/* We also remember if a SET ROLE is currently active */


/*
 * GetUserId - get the current effective user ID.
 *
 * Note: there's no SetUserId() anymore; use SetUserIdAndSecContext().
 */

Oid
GetUserId(void)
{
return InvalidOid;}


/*
 * GetOuterUserId/SetOuterUserId - get/set the outer-level user ID.
 */






/*
 * GetSessionUserId/SetSessionUserId - get/set the session user ID.
 */






/*
 * Return the system user representing the authenticated identity.
 * It is defined in InitializeSystemUser() as auth_method:authn_id.
 */


/*
 * GetAuthenticatedUserId/SetAuthenticatedUserId - get/set the authenticated
 * user ID
 */





/*
 * GetUserIdAndSecContext/SetUserIdAndSecContext - get/set the current user ID
 * and the SecurityRestrictionContext flags.
 *
 * Currently there are three valid bits in SecurityRestrictionContext:
 *
 * SECURITY_LOCAL_USERID_CHANGE indicates that we are inside an operation
 * that is temporarily changing CurrentUserId via these functions.  This is
 * needed to indicate that the actual value of CurrentUserId is not in sync
 * with guc.c's internal state, so SET ROLE has to be disallowed.
 *
 * SECURITY_RESTRICTED_OPERATION indicates that we are inside an operation
 * that does not wish to trust called user-defined functions at all.  The
 * policy is to use this before operations, e.g. autovacuum and REINDEX, that
 * enumerate relations of a database or schema and run functions associated
 * with each found relation.  The relation owner is the new user ID.  Set this
 * as soon as possible after locking the relation.  Restore the old user ID as
 * late as possible before closing the relation; restoring it shortly after
 * close is also tolerable.  If a command has both relation-enumerating and
 * non-enumerating modes, e.g. ANALYZE, both modes set this bit.  This bit
 * prevents not only SET ROLE, but various other changes of session state that
 * normally is unprotected but might possibly be used to subvert the calling
 * session later.  An example is replacing an existing prepared statement with
 * new code, which will then be executed with the outer session's permissions
 * when the prepared statement is next used.  These restrictions are fairly
 * draconian, but the functions called in relation-enumerating operations are
 * really supposed to be side-effect-free anyway.
 *
 * SECURITY_NOFORCE_RLS indicates that we are inside an operation which should
 * ignore the FORCE ROW LEVEL SECURITY per-table indication.  This is used to
 * ensure that FORCE RLS does not mistakenly break referential integrity
 * checks.  Note that this is intentionally only checked when running as the
 * owner of the table (which should always be the case for referential
 * integrity checks).
 *
 * Unlike GetUserId, GetUserIdAndSecContext does *not* Assert that the current
 * value of CurrentUserId is valid; nor does SetUserIdAndSecContext require
 * the new value to be valid.  In fact, these routines had better not
 * ever throw any kind of error.  This is because they are used by
 * StartTransaction and AbortTransaction to save/restore the settings,
 * and during the first transaction within a backend, the value to be saved
 * and perhaps restored is indeed invalid.  We have to be able to get
 * through AbortTransaction without asserting in case InitPostgres fails.
 */





/*
 * InLocalUserIdChange - are we inside a local change of CurrentUserId?
 */


/*
 * InSecurityRestrictedOperation - are we inside a security-restricted command?
 */


/*
 * InNoForceRLSOperation - are we ignoring FORCE ROW LEVEL SECURITY ?
 */



/*
 * These are obsolete versions of Get/SetUserIdAndSecContext that are
 * only provided for bug-compatibility with some rather dubious code in
 * pljava.  We allow the userid to be set, but only when not inside a
 * security restriction context.
 */





/*
 * Check whether specified role has explicit REPLICATION privilege
 */


/*
 * Initialize user identity during normal backend startup
 */



/*
 * Initialize user identity during special backend startup
 */


/*
 * Initialize the system user.
 *
 * This is built as auth_method:authn_id.
 */


/*
 * SQL-function SYSTEM_USER
 */


/*
 * Change session auth ID while running
 *
 * The SQL standard says that SET SESSION AUTHORIZATION implies SET ROLE NONE.
 * We mechanize that at higher levels not here, because this is the GUC
 * assign hook for "session_authorization", and it must be commutative with
 * SetCurrentRoleId (the hook for "role") because guc.c provides no guarantees
 * which will run first during cases such as transaction rollback.  Therefore,
 * we update derived state (OuterUserId/CurrentUserId/is_superuser) only if
 * !SetRoleIsActive.
 */


/*
 * Report current role id
 *		This follows the semantics of SET ROLE, ie return the outer-level ID
 *		not the current effective ID, and return InvalidOid when the setting
 *		is logically SET ROLE NONE.
 */


/*
 * Change Role ID while running (SET ROLE)
 *
 * If roleid is InvalidOid, we are doing SET ROLE NONE: revert to the
 * session user authorization.  In this case the is_superuser argument
 * is ignored.
 *
 * When roleid is not InvalidOid, the caller must have checked whether
 * the session user has permission to become that role.  (We cannot check
 * here because this routine must be able to execute in a failed transaction
 * to restore a prior value of the ROLE GUC variable.)
 */



/*
 * Get user name from user oid, returns NULL for nonexistent roleid if noerr
 * is true.
 */


/* ------------------------------------------------------------------------
 *				Client connection state shared with parallel workers
 *
 * ClientConnectionInfo contains pieces of information about the client that
 * need to be synced to parallel workers when they initialize.
 *-------------------------------------------------------------------------
 */



/*
 * Intermediate representation of ClientConnectionInfo for easier
 * serialization.  Variable-length fields are allocated right after this
 * header.
 */
typedef struct SerializedClientConnectionInfo
{
	int32		authn_id_len;	/* strlen(authn_id), or -1 if NULL */
	UserAuth	auth_method;
} SerializedClientConnectionInfo;

/*
 * Calculate the space needed to serialize MyClientConnectionInfo.
 */


/*
 * Serialize MyClientConnectionInfo for use by parallel workers.
 */


/*
 * Restore MyClientConnectionInfo from its serialized representation.
 */



/*-------------------------------------------------------------------------
 *				Interlock-file support
 *
 * These routines are used to create both a data-directory lockfile
 * ($DATADIR/postmaster.pid) and Unix-socket-file lockfiles ($SOCKFILE.lock).
 * Both kinds of files contain the same info initially, although we can add
 * more information to a data-directory lockfile after it's created, using
 * AddToDataDirLockFile().  See pidfile.h for documentation of the contents
 * of these lockfiles.
 *
 * On successful lockfile creation, a proc_exit callback to remove the
 * lockfile is automatically created.
 *-------------------------------------------------------------------------
 */

/*
 * proc_exit callback to remove lockfiles.
 */


/*
 * Create a lockfile.
 *
 * filename is the path name of the lockfile to create.
 * amPostmaster is used to determine how to encode the output PID.
 * socketDir is the Unix socket directory path to include (possibly empty).
 * isDDLock and refName are used to determine what error message to produce.
 */
#ifndef WIN32
#else
#endif

/*
 * Create the data directory lockfile.
 *
 * When this is called, we must have already switched the working
 * directory to DataDir, so we can just use a relative path.  This
 * helps ensure that we are locking the directory we should be.
 *
 * Note that the socket directory path line is initially written as empty.
 * postmaster.c will rewrite it upon creating the first Unix socket.
 */


/*
 * Create a lockfile for the specified Unix socket file.
 */


/*
 * TouchSocketLockFiles -- mark socket lock files as recently accessed
 *
 * This routine should be called every so often to ensure that the socket
 * lock files have a recent mod or access date.  That saves them
 * from being removed by overenthusiastic /tmp-directory-cleaner daemons.
 * (Another reason we should never have put the socket file in /tmp...)
 */



/*
 * Add (or replace) a line in the data directory lock file.
 * The given string should not include a trailing newline.
 *
 * Note: because we don't truncate the file, if we were to rewrite a line
 * with less data than it had before, there would be garbage after the last
 * line.  While we could fix that by adding a truncate call, that would make
 * the file update non-atomic, which we'd rather avoid.  Therefore, callers
 * should endeavor never to shorten a line once it's been written.
 */



/*
 * Recheck that the data directory lock file still exists with expected
 * content.  Return true if the lock file appears OK, false if it isn't.
 *
 * We call this periodically in the postmaster.  The idea is that if the
 * lock file has been removed or replaced by another postmaster, we should
 * do a panic database shutdown.  Therefore, we should return true if there
 * is any doubt: we do not want to cause a panic shutdown unnecessarily.
 * Transient failures like EINTR or ENFILE should not cause us to fail.
 * (If there really is something wrong, we'll detect it on a future recheck.)
 */



/*-------------------------------------------------------------------------
 *				Version checking support
 *-------------------------------------------------------------------------
 */

/*
 * Determine whether the PG_VERSION file in directory `path' indicates
 * a data version compatible with the version of this program.
 *
 * If compatible, return. Otherwise, ereport(FATAL).
 */


/*-------------------------------------------------------------------------
 *				Library preload support
 *-------------------------------------------------------------------------
 */

/*
 * GUC variables: lists of library names to be preloaded at postmaster
 * start and at backend start
 */




/* Flag telling that we are loading shared_preload_libraries */






/*
 * load the shared libraries listed in 'libraries'
 *
 * 'gucname': name of GUC variable, for error reports
 * 'restricted': if true, force libraries to be in $libdir/plugins/
 */


/*
 * process any libraries that should be preloaded at postmaster start
 */


/*
 * process any libraries that should be preloaded at backend start
 */


/*
 * process any shared memory requests from preloaded libraries
 */


#ifdef ENABLE_NLS
#endif
