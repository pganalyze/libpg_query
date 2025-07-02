SELECT col1, col2
FROM
    xyz
    JOIN abc ON a = b
WHERE
    c IN (
        SELECT id
        FROM test
    )
    AND col2 > 123
