/* Polyfills to avoid building unnecessary objects from the PostgreSQL source */

#include "postgres.h"

/* src/backend/postmaster/postmaster.c */
bool ClientAuthInProgress = false;
bool redirection_done = false;

/* src/backend/postmaster/syslogger.c */
bool am_syslogger = false;

/* src/backend/tcop/postgres.c */
#include "tcop/dest.h"
const char *debug_query_string;
CommandDest whereToSendOutput = DestDebug;

/* src/backend/utils/misc/guc.c */
char *application_name;
int client_min_messages = NOTICE;
int log_min_error_statement = ERROR;
int log_min_messages = WARNING;
int trace_recovery_messages = LOG;

/* src/backend/storage/lmgr/proc.c */
#include "storage/proc.h"
PGPROC *MyProc = NULL;

/* src/backend/storage/ipc/ipc.c */
bool proc_exit_inprogress = false;

/* src/backend/tcop/postgres.c */
#include "miscadmin.h"
void check_stack_depth(void) { /* Do nothing */ }

/* src/backends/commands/define.c */
#include "commands/defrem.h"
#include "nodes/makefuncs.h"
DefElem * defWithOids(bool value)
{
  return makeDefElem("oids", (Node *) makeInteger(value));
}
