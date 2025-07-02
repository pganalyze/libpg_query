SELECT
    CASE
        WHEN count(*) FILTER (WHERE col_state = 2) = count(col_id) THEN true
        WHEN count(*) FILTER (WHERE col_state = 3) > 0 THEN false
        ELSE NULL
    END AS col_alias
FROM my_table
