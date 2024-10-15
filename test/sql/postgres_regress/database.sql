CREATE DATABASE regression_tbd
	ENCODING utf8 LC_COLLATE "C" LC_CTYPE "C" TEMPLATE template0;
ALTER DATABASE regression_tbd RENAME TO regression_utf8;
ALTER DATABASE regression_utf8 SET TABLESPACE regress_tblspace;
ALTER DATABASE regression_utf8 RESET TABLESPACE;
ALTER DATABASE regression_utf8 CONNECTION_LIMIT 123;

-- Test PgDatabaseToastTable.  Doing this with GRANT would be slow.
BEGIN;
UPDATE pg_database
SET datacl = array_fill(makeaclitem(10, 10, 'USAGE', false), ARRAY[5e5::int])
WHERE datname = 'regression_utf8';
-- load catcache entry, if nothing else does
ALTER DATABASE regression_utf8 RESET TABLESPACE;
ROLLBACK;

DROP DATABASE regression_utf8;
