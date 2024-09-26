/*-------------------------------------------------------------------------
 *
 * bgwriter.h
 *	  Exports from postmaster/bgwriter.c and postmaster/checkpointer.c.
 *
 * The bgwriter process used to handle checkpointing duties too.  Now
 * there is a separate process, but we did not bother to split this header.
 *
 * Portions Copyright (c) 1996-2024, PostgreSQL Global Development Group
 *
 * src/include/postmaster/bgwriter.h
 *
 *-------------------------------------------------------------------------
 */
#ifndef _BGWRITER_H
#define _BGWRITER_H

#include "storage/block.h"
#include "storage/relfilelocator.h"
#include "storage/smgr.h"
#include "storage/sync.h"


/* GUC options */
extern PGDLLIMPORT int BgWriterDelay;
extern PGDLLIMPORT int CheckPointTimeout;
extern PGDLLIMPORT int CheckPointWarning;
extern PGDLLIMPORT double CheckPointCompletionTarget;

extern void BackgroundWriterMain(char *startup_data, size_t startup_data_len) pg_attribute_noreturn();
extern void CheckpointerMain(char *startup_data, size_t startup_data_len) pg_attribute_noreturn();

extern void RequestCheckpoint(int flags);
extern void CheckpointWriteDelay(int flags, double progress);

extern bool ForwardSyncRequest(const FileTag *ftag, SyncRequestType type);

extern void AbsorbSyncRequests(void);

extern Size CheckpointerShmemSize(void);
extern void CheckpointerShmemInit(void);

extern bool FirstCallSinceLastCheckpoint(void);

#endif							/* _BGWRITER_H */
