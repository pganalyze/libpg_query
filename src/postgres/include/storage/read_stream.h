/*-------------------------------------------------------------------------
 *
 * read_stream.h
 *	  Mechanism for accessing buffered relation data with look-ahead
 *
 *
 * Portions Copyright (c) 1996-2024, PostgreSQL Global Development Group
 * Portions Copyright (c) 1994, Regents of the University of California
 *
 * src/include/storage/read_stream.h
 *
 *-------------------------------------------------------------------------
 */
#ifndef READ_STREAM_H
#define READ_STREAM_H

#include "storage/bufmgr.h"

/* Default tuning, reasonable for many users. */
#define READ_STREAM_DEFAULT 0x00

/*
 * I/O streams that are performing maintenance work on behalf of potentially
 * many users, and thus should be governed by maintenance_io_concurrency
 * instead of effective_io_concurrency.  For example, VACUUM or CREATE INDEX.
 */
#define READ_STREAM_MAINTENANCE 0x01

/*
 * We usually avoid issuing prefetch advice automatically when sequential
 * access is detected, but this flag explicitly disables it, for cases that
 * might not be correctly detected.  Explicit advice is known to perform worse
 * than letting the kernel (at least Linux) detect sequential access.
 */
#define READ_STREAM_SEQUENTIAL 0x02

/*
 * We usually ramp up from smaller reads to larger ones, to support users who
 * don't know if it's worth reading lots of buffers yet.  This flag disables
 * that, declaring ahead of time that we'll be reading all available buffers.
 */
#define READ_STREAM_FULL 0x04

struct ReadStream;
typedef struct ReadStream ReadStream;

/* Callback that returns the next block number to read. */
typedef BlockNumber (*ReadStreamBlockNumberCB) (ReadStream *stream,
												void *callback_private_data,
												void *per_buffer_data);

extern ReadStream *read_stream_begin_relation(int flags,
											  BufferAccessStrategy strategy,
											  Relation rel,
											  ForkNumber forknum,
											  ReadStreamBlockNumberCB callback,
											  void *callback_private_data,
											  size_t per_buffer_data_size);
extern Buffer read_stream_next_buffer(ReadStream *stream, void **per_buffer_data);
extern void read_stream_reset(ReadStream *stream);
extern void read_stream_end(ReadStream *stream);

#endif							/* READ_STREAM_H */
