--
-- Regression tests for schemas (namespaces)
--

-- set the whitespace-only search_path to test that the
-- GUC list syntax is preserved during a schema creation
SELECT pg_catalog.set_config('search_path', ' ', false);

CREATE SCHEMA test_ns_schema_1
       CREATE UNIQUE INDEX abc_a_idx ON abc (a)

       CREATE VIEW abc_view AS
              SELECT a+1 AS a, b+1 AS b FROM abc

       CREATE TABLE abc (
              a serial,
              b int UNIQUE
       );

-- verify that the correct search_path restored on abort
SET search_path to public;
BEGIN;
SET search_path to public, test_ns_schema_1;
CREATE SCHEMA test_ns_schema_2
       CREATE VIEW abc_view AS SELECT c FROM abc;
COMMIT;
SHOW search_path;

-- verify that the correct search_path preserved
-- after creating the schema and on commit
BEGIN;
SET search_path to public, test_ns_schema_1;
CREATE SCHEMA test_ns_schema_2
       CREATE VIEW abc_view AS SELECT a FROM abc;
SHOW search_path;
COMMIT;
SHOW search_path;
DROP SCHEMA test_ns_schema_2 CASCADE;

-- verify that the objects were created
SELECT COUNT(*) FROM pg_class WHERE relnamespace =
    (SELECT oid FROM pg_namespace WHERE nspname = 'test_ns_schema_1');

INSERT INTO test_ns_schema_1.abc DEFAULT VALUES;
INSERT INTO test_ns_schema_1.abc DEFAULT VALUES;
INSERT INTO test_ns_schema_1.abc DEFAULT VALUES;

SELECT * FROM test_ns_schema_1.abc;
SELECT * FROM test_ns_schema_1.abc_view;

ALTER SCHEMA test_ns_schema_1 RENAME TO test_ns_schema_renamed;
SELECT COUNT(*) FROM pg_class WHERE relnamespace =
    (SELECT oid FROM pg_namespace WHERE nspname = 'test_ns_schema_1');

-- test IF NOT EXISTS cases
CREATE SCHEMA test_ns_schema_renamed; -- fail, already exists
CREATE SCHEMA IF NOT EXISTS test_ns_schema_renamed; -- ok with notice
CREATE SCHEMA IF NOT EXISTS test_ns_schema_renamed -- fail, disallowed
       CREATE TABLE abc (
              a serial,
              b int UNIQUE
       );

DROP SCHEMA test_ns_schema_renamed CASCADE;

-- verify that the objects were dropped
SELECT COUNT(*) FROM pg_class WHERE relnamespace =
    (SELECT oid FROM pg_namespace WHERE nspname = 'test_ns_schema_renamed');

--
-- Verify that search_path is set to a safe value during maintenance
-- commands.
--

CREATE SCHEMA test_maint_search_path;
SET search_path = test_maint_search_path;

CREATE FUNCTION fn(INT) RETURNS INT IMMUTABLE LANGUAGE plpgsql AS $$
  BEGIN
    RAISE NOTICE 'current search_path: %', current_setting('search_path');
    RETURN $1;
  END;
$$;

CREATE TABLE test_maint(i INT);
INSERT INTO test_maint VALUES (1), (2);
CREATE MATERIALIZED VIEW test_maint_mv AS SELECT fn(i) FROM test_maint;

-- the following commands should see search_path as pg_catalog, pg_temp

CREATE INDEX test_maint_idx ON test_maint_search_path.test_maint (fn(i));
REINDEX TABLE test_maint_search_path.test_maint;
ANALYZE test_maint_search_path.test_maint;
VACUUM FULL test_maint_search_path.test_maint;
CLUSTER test_maint_search_path.test_maint USING test_maint_idx;
REFRESH MATERIALIZED VIEW test_maint_search_path.test_maint_mv;

RESET search_path;

DROP SCHEMA test_maint_search_path CASCADE;
