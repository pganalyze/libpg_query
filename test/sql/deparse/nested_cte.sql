--- Note: This is a slightly odd choice (using a WITH on the INSERT's SELECT clause), but valid syntax
WITH q AS (
    SELECT 1 AS z
)
INSERT INTO t (a)
WITH qq AS (
    SELECT *
    FROM q
)
SELECT z
FROM qq
