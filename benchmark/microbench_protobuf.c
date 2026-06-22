/*
 * Microbenchmark isolating ONLY the protobuf layer (no parsing, no deparse
 * walk): pg_query_nodes_to_protobuf (encode) and pg_query_protobuf_to_nodes
 * (decode), run on pre-parsed trees / pre-encoded bytes.
 *
 * Identical source compiled against the old (protobuf-c) and new (upb)
 * libpg_query.a; only those two functions differ. A scratch memory context is
 * reset after each op so the per-node palloc churn (protobuf-c) and arena
 * lifecycle (upb) are both counted as part of their real cost, while the
 * persistent parse trees survive across iterations.
 *
 * Built with the library CFLAGS (needs the internal headers + postgres.h).
 */
#include "pg_query.h"
#include "pg_query_internal.h"   /* raw_parse, memory-context helpers, MemoryContext */
#include "pg_query_outfuncs.h"   /* pg_query_nodes_to_protobuf */
#include "pg_query_readfuncs.h"  /* pg_query_protobuf_to_nodes */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static const char *queries[] = {
	"SELECT 1",
	"SELECT id, name FROM users WHERE active = true ORDER BY created_at DESC LIMIT 10",
	"SELECT u.id, count(*) FROM users u JOIN orders o ON o.user_id = u.id "
	  "WHERE o.total > 100 GROUP BY u.id HAVING count(*) > 5",
	"INSERT INTO t (a,b,c,d,e) VALUES (1,2,3,4,5),(6,7,8,9,10),(11,12,13,14,15),"
	  "(16,17,18,19,20),(21,22,23,24,25),(26,27,28,29,30)",
	"WITH RECURSIVE cte AS (SELECT 1 AS n UNION ALL SELECT n+1 FROM cte WHERE n < 100) "
	  "SELECT sum(n) OVER (ORDER BY n ROWS BETWEEN 2 PRECEDING AND CURRENT ROW) FROM cte",
	"UPDATE accounts SET balance = balance - 50 WHERE id = 7 AND balance >= 50 RETURNING id, balance",
	"SELECT CASE WHEN a > b THEN 'x' WHEN a < b THEN 'y' ELSE 'z' END, "
	  "coalesce(nullif(c, 0), d, 1), array_agg(e ORDER BY f) FROM tbl GROUP BY 1",
	"SELECT * FROM a LEFT JOIN b USING (k) LEFT JOIN c ON c.k = b.k "
	  "FULL JOIN d ON d.k = c.k WHERE a.x IN (SELECT x FROM e WHERE y = $1)",
	"CREATE TABLE foo (id serial PRIMARY KEY, name text NOT NULL, "
	  "data jsonb DEFAULT '{}', created timestamptz DEFAULT now(), CHECK (length(name) > 0))",
	"SELECT to_char(d, 'YYYY-MM-DD'), extract(epoch FROM d), d + interval '1 day' "
	  "FROM (SELECT generate_series('2020-01-01'::date, '2020-12-31'::date, '1 day') AS d) s",
};
static const int NQ = sizeof(queries) / sizeof(queries[0]);

static double now_sec(void) {
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	return ts.tv_sec + ts.tv_nsec / 1e9;
}

int main(int argc, char **argv) {
	int iters = (argc > 1) ? atoi(argv[1]) : 50000;
	const char *label = (argc > 2) ? argv[2] : "?";

	MemoryContext persistent = pg_query_enter_memory_context();

	/* Parse every query once; trees live in the persistent context. */
	List	   *trees[64];
	PgQueryProtobuf bufs[64];
	size_t		total_bytes = 0;
	for (int i = 0; i < NQ; i++) {
		PgQueryInternalParsetreeAndError pe = pg_query_raw_parse(queries[i], 0);
		if (pe.error) { fprintf(stderr, "parse error: %s\n", pe.error->message); return 1; }
		trees[i] = pe.tree;
		bufs[i] = pg_query_nodes_to_protobuf(pe.tree);   /* data is malloc'd, survives */
		total_bytes += bufs[i].len;
	}

	/* Scratch context for per-op intermediates; reset after each op. */
	MemoryContext scratch = AllocSetContextCreate(CurrentMemoryContext, "bench_scratch", ALLOCSET_DEFAULT_SIZES);
	MemoryContextSwitchTo(scratch);

	volatile size_t sink = 0;

	/* Warmup */
	for (int w = 0; w < 1000; w++)
		for (int i = 0; i < NQ; i++) {
			PgQueryProtobuf pb = pg_query_nodes_to_protobuf(trees[i]);
			free(pb.data);
			pg_query_protobuf_to_nodes(bufs[i]);
			MemoryContextReset(scratch);
		}

	/* ENCODE only: nodes -> protobuf bytes */
	double t0 = now_sec();
	for (int it = 0; it < iters; it++)
		for (int i = 0; i < NQ; i++) {
			PgQueryProtobuf pb = pg_query_nodes_to_protobuf(trees[i]);
			sink += pb.len;
			free(pb.data);
			MemoryContextReset(scratch);
		}
	double t_enc = now_sec() - t0;

	/* DECODE only: protobuf bytes -> nodes */
	t0 = now_sec();
	for (int it = 0; it < iters; it++)
		for (int i = 0; i < NQ; i++) {
			List *l = pg_query_protobuf_to_nodes(bufs[i]);
			sink += (size_t) l;
			MemoryContextReset(scratch);
		}
	double t_dec = now_sec() - t0;

	long ops = (long) iters * NQ;
	printf("[%s] iters=%d queries=%d ops=%ld\n", label, iters, NQ, ops);
	printf("  ENCODE nodes_to_protobuf:  %7.3f s   %7.1f ns/op   %9.0f ops/s\n",
		t_enc, t_enc * 1e9 / ops, ops / t_enc);
	printf("  DECODE protobuf_to_nodes:  %7.3f s   %7.1f ns/op   %9.0f ops/s\n",
		t_dec, t_dec * 1e9 / ops, ops / t_dec);
	printf("  bytes/corpus pass: %zu   (sink=%zu)\n", total_bytes, sink);

	MemoryContextSwitchTo(persistent);
	pg_query_exit_memory_context(persistent);
	return 0;
}
