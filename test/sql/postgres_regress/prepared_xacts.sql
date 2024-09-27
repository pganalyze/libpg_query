--
-- PREPARED TRANSACTIONS (two-phase commit)
--
-- We can't readily test persistence of prepared xacts within the
-- regression script framework, unfortunately.  Note that a crash
-- isn't really needed ... stopping and starting the postmaster would
-- be enough, but we can't even do that here.


-- create a simple table that we'll use in the tests
CREATE TABLE pxtest1 (foobar VARCHAR(10));

INSERT INTO pxtest1 VALUES ('aaa');


-- Test PREPARE TRANSACTION
BEGIN TRANSACTION ISOLATION LEVEL SERIALIZABLE;
UPDATE pxtest1 SET foobar = 'bbb' WHERE foobar = 'aaa';
SELECT * FROM pxtest1;
PREPARE TRANSACTION 'regress_foo1';

SELECT * FROM pxtest1;

-- Test pg_prepared_xacts system view
SELECT gid FROM pg_prepared_xacts WHERE gid ~ '^regress_' ORDER BY gid;

-- Test ROLLBACK PREPARED
ROLLBACK PREPARED 'regress_foo1';

SELECT * FROM pxtest1;

SELECT gid FROM pg_prepared_xacts WHERE gid ~ '^regress_' ORDER BY gid;


-- Test COMMIT PREPARED
BEGIN TRANSACTION ISOLATION LEVEL SERIALIZABLE;
INSERT INTO pxtest1 VALUES ('ddd');
SELECT * FROM pxtest1;
PREPARE TRANSACTION 'regress_foo2';

SELECT * FROM pxtest1;

COMMIT PREPARED 'regress_foo2';

SELECT * FROM pxtest1;

-- Test duplicate gids
BEGIN TRANSACTION ISOLATION LEVEL SERIALIZABLE;
UPDATE pxtest1 SET foobar = 'eee' WHERE foobar = 'ddd';
SELECT * FROM pxtest1;
PREPARE TRANSACTION 'regress_foo3';

SELECT gid FROM pg_prepared_xacts WHERE gid ~ '^regress_' ORDER BY gid;

BEGIN TRANSACTION ISOLATION LEVEL SERIALIZABLE;
INSERT INTO pxtest1 VALUES ('fff');

-- This should fail, because the gid foo3 is already in use
PREPARE TRANSACTION 'regress_foo3';

SELECT * FROM pxtest1;

ROLLBACK PREPARED 'regress_foo3';

SELECT * FROM pxtest1;

-- Test serialization failure (SSI)
BEGIN TRANSACTION ISOLATION LEVEL SERIALIZABLE;
UPDATE pxtest1 SET foobar = 'eee' WHERE foobar = 'ddd';
SELECT * FROM pxtest1;
PREPARE TRANSACTION 'regress_foo4';

SELECT gid FROM pg_prepared_xacts WHERE gid ~ '^regress_' ORDER BY gid;

BEGIN TRANSACTION ISOLATION LEVEL SERIALIZABLE;
SELECT * FROM pxtest1;

-- This should fail, because the two transactions have a write-skew anomaly
INSERT INTO pxtest1 VALUES ('fff');
PREPARE TRANSACTION 'regress_foo5';

SELECT gid FROM pg_prepared_xacts WHERE gid ~ '^regress_' ORDER BY gid;

ROLLBACK PREPARED 'regress_foo4';

SELECT gid FROM pg_prepared_xacts WHERE gid ~ '^regress_' ORDER BY gid;

-- Clean up
DROP TABLE pxtest1;

-- Test detection of session-level and xact-level locks on same object
BEGIN;
SELECT pg_advisory_lock(1);
SELECT pg_advisory_xact_lock_shared(1);
PREPARE TRANSACTION 'regress_foo6';  -- fails

-- Test subtransactions
BEGIN TRANSACTION ISOLATION LEVEL SERIALIZABLE;
  CREATE TABLE pxtest2 (a int);
  INSERT INTO pxtest2 VALUES (1);
  SAVEPOINT a;
    INSERT INTO pxtest2 VALUES (2);
  ROLLBACK TO a;
  SAVEPOINT b;
  INSERT INTO pxtest2 VALUES (3);
PREPARE TRANSACTION 'regress_sub1';

CREATE TABLE pxtest3(fff int);

-- Test shared invalidation
BEGIN TRANSACTION ISOLATION LEVEL SERIALIZABLE;
  DROP TABLE pxtest3;
  CREATE TABLE pxtest4 (a int);
  INSERT INTO pxtest4 VALUES (1);
  INSERT INTO pxtest4 VALUES (2);
  DECLARE foo CURSOR FOR SELECT * FROM pxtest4;
  -- Fetch 1 tuple, keeping the cursor open
  FETCH 1 FROM foo;
PREPARE TRANSACTION 'regress_sub2';

-- No such cursor
FETCH 1 FROM foo;

-- Table doesn't exist, the creation hasn't been committed yet
SELECT * FROM pxtest2;

-- There should be two prepared transactions
SELECT gid FROM pg_prepared_xacts WHERE gid ~ '^regress_' ORDER BY gid;

-- pxtest3 should be locked because of the pending DROP
begin;
lock table pxtest3 in access share mode nowait;
rollback;

-- Disconnect, we will continue testing in a different backend
\c -

-- There should still be two prepared transactions
SELECT gid FROM pg_prepared_xacts WHERE gid ~ '^regress_' ORDER BY gid;

-- pxtest3 should still be locked because of the pending DROP
begin;
lock table pxtest3 in access share mode nowait;
rollback;

-- Commit table creation
COMMIT PREPARED 'regress_sub1';
\d pxtest2
SELECT * FROM pxtest2;

-- There should be one prepared transaction
SELECT gid FROM pg_prepared_xacts WHERE gid ~ '^regress_' ORDER BY gid;

-- Commit table drop
COMMIT PREPARED 'regress_sub2';
SELECT * FROM pxtest3;

-- There should be no prepared transactions
SELECT gid FROM pg_prepared_xacts WHERE gid ~ '^regress_' ORDER BY gid;

-- Clean up
DROP TABLE pxtest2;
DROP TABLE pxtest3;  -- will still be there if prepared xacts are disabled
DROP TABLE pxtest4;
