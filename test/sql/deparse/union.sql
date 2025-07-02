WITH input AS (
    SELECT database_id, fingerprint, last_occurred_at, index
    FROM unnest($1::int[], $2::bigint[], $3::date[], $4::int[]) _(database_id, fingerprint, last_occurred_at, index)
), existing_queries AS (
    SELECT
        queries.id AS query_id, input.database_id, input.fingerprint,
        input.last_occurred_at, input.index
    FROM
        queries
        JOIN input USING (database_id, fingerprint)
), update_occurrences AS (
    UPDATE query_occurrences
    SET last = last_occurred_at
    FROM existing_queries q
    WHERE
        q.query_id = query_occurrences.query_id
        AND last < last_occurred_at
    RETURNING index
)
SELECT index, $5 AS "exists"
FROM update_occurrences
UNION (
    SELECT input.index, $6 AS "exists"
    FROM
        input
        LEFT JOIN existing_queries USING (database_id, fingerprint)
    WHERE existing_queries.database_id IS NULL
    LIMIT 1
)
LIMIT 5
