CREATE TABLE public.vacuum_run_stats_35d (
    vacuum_run_stats_id uuid DEFAULT public.gen_random_uuid() NOT NULL,
    server_id uuid NOT NULL,
    vacuum_run_id uuid NOT NULL,
    collected_at timestamp NOT NULL,
    phase int NOT NULL,
    heap_blks_total bigint NOT NULL,
    heap_blks_scanned bigint NOT NULL,
    heap_blks_vacuumed bigint NOT NULL,
    index_vacuum_count bigint NOT NULL,
    max_dead_tuples bigint NOT NULL,
    num_dead_tuples bigint NOT NULL
)
PARTITION BY RANGE (collected_at)
