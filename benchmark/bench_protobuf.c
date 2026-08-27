/*
 * A/B benchmark for the protobuf encode/decode layer.
 * Identical source compiled against the old (protobuf-c) and new (upb)
 * libpg_query.a. Only the protobuf implementation differs between the two
 * archives; parser and deparse walk are shared, so the per-op delta isolates
 * the encode/decode cost.
 */
#include <pg_query.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/resource.h>

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
	int iters = (argc > 1) ? atoi(argv[1]) : 20000;
	const char *label = (argc > 2) ? argv[2] : "?";

	/* Pre-encode each query once and keep the bytes for the decode benchmark. */
	PgQueryProtobuf bufs[64];
	size_t total_bytes = 0;
	for (int i = 0; i < NQ; i++) {
		PgQueryProtobufParseResult r = pg_query_parse_protobuf(queries[i]);
		if (r.error) { fprintf(stderr, "parse error: %s\n", r.error->message); return 1; }
		bufs[i].len = r.parse_tree.len;
		bufs[i].data = malloc(r.parse_tree.len);
		memcpy(bufs[i].data, r.parse_tree.data, r.parse_tree.len);
		total_bytes += r.parse_tree.len;
		pg_query_free_protobuf_parse_result(r);
	}

	/* Warmup */
	for (int w = 0; w < 200; w++)
		for (int i = 0; i < NQ; i++) {
			PgQueryProtobufParseResult r = pg_query_parse_protobuf(queries[i]);
			pg_query_free_protobuf_parse_result(r);
			PgQueryDeparseResult d = pg_query_deparse_protobuf(bufs[i]);
			pg_query_free_deparse_result(d);
		}

	/* ENCODE: parse_protobuf (parse + protobuf encode) */
	double t0 = now_sec();
	volatile size_t sink = 0;
	for (int it = 0; it < iters; it++)
		for (int i = 0; i < NQ; i++) {
			PgQueryProtobufParseResult r = pg_query_parse_protobuf(queries[i]);
			sink += r.parse_tree.len;
			pg_query_free_protobuf_parse_result(r);
		}
	double t_enc = now_sec() - t0;

	/* DECODE: deparse_protobuf (protobuf decode + deparse walk) */
	t0 = now_sec();
	for (int it = 0; it < iters; it++)
		for (int i = 0; i < NQ; i++) {
			PgQueryDeparseResult d = pg_query_deparse_protobuf(bufs[i]);
			sink += d.query ? strlen(d.query) : 0;
			pg_query_free_deparse_result(d);
		}
	double t_dec = now_sec() - t0;

	long ops = (long) iters * NQ;
	struct rusage ru;
	getrusage(RUSAGE_SELF, &ru);

	printf("[%s] iters=%d queries=%d ops=%ld\n", label, iters, NQ, ops);
	printf("  encode (parse_protobuf): %8.3f s   %8.1f ns/op   %9.0f ops/s\n",
		t_enc, t_enc * 1e9 / ops, ops / t_enc);
	printf("  decode (deparse_protobuf): %6.3f s   %8.1f ns/op   %9.0f ops/s\n",
		t_dec, t_dec * 1e9 / ops, ops / t_dec);
	printf("  protobuf bytes/corpus pass: %zu (per-op avg %.1f)\n", total_bytes, (double) total_bytes / NQ);
	printf("  maxrss: %.1f MB    (sink=%zu)\n", ru.ru_maxrss / (1024.0 * 1024.0), sink);
	return 0;
}
