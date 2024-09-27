--
-- Tests for predicate handling
--

--
-- Test that restrictions that are always true are ignored, and that are always
-- false are replaced with constant-FALSE
--
-- Currently we only check for NullTest quals and OR clauses that include
-- NullTest quals.  We may extend it in the future.
--
CREATE TABLE pred_tab (a int NOT NULL, b int, c int NOT NULL);

--
-- Test restriction clauses
--

-- Ensure the IS_NOT_NULL qual is ignored when the column is non-nullable
EXPLAIN (COSTS OFF)
SELECT * FROM pred_tab t WHERE t.a IS NOT NULL;

-- Ensure the IS_NOT_NULL qual is not ignored on a nullable column
EXPLAIN (COSTS OFF)
SELECT * FROM pred_tab t WHERE t.b IS NOT NULL;

-- Ensure the IS_NULL qual is reduced to constant-FALSE for non-nullable
-- columns
EXPLAIN (COSTS OFF)
SELECT * FROM pred_tab t WHERE t.a IS NULL;

-- Ensure the IS_NULL qual is not reduced to constant-FALSE on nullable
-- columns
EXPLAIN (COSTS OFF)
SELECT * FROM pred_tab t WHERE t.b IS NULL;

--
-- Tests for OR clauses in restriction clauses
--

-- Ensure the OR clause is ignored when an OR branch is always true
EXPLAIN (COSTS OFF)
SELECT * FROM pred_tab t WHERE t.a IS NOT NULL OR t.b = 1;

-- Ensure the OR clause is not ignored for NullTests that can't be proven
-- always true
EXPLAIN (COSTS OFF)
SELECT * FROM pred_tab t WHERE t.b IS NOT NULL OR t.a = 1;

-- Ensure the OR clause is reduced to constant-FALSE when all branches are
-- provably false
EXPLAIN (COSTS OFF)
SELECT * FROM pred_tab t WHERE t.a IS NULL OR t.c IS NULL;

-- Ensure the OR clause is not reduced to constant-FALSE when not all branches
-- are provably false
EXPLAIN (COSTS OFF)
SELECT * FROM pred_tab t WHERE t.b IS NULL OR t.c IS NULL;

--
-- Test join clauses
--

-- Ensure the IS_NOT_NULL qual is ignored, since a) it's on a NOT NULL column,
-- and b) its Var is not nullable by any outer joins
EXPLAIN (COSTS OFF)
SELECT * FROM pred_tab t1
    LEFT JOIN pred_tab t2 ON TRUE
    LEFT JOIN pred_tab t3 ON t2.a IS NOT NULL;

-- Ensure the IS_NOT_NULL qual is not ignored when columns are made nullable
-- by an outer join
EXPLAIN (COSTS OFF)
SELECT * FROM pred_tab t1
    LEFT JOIN pred_tab t2 ON t1.a = 1
    LEFT JOIN pred_tab t3 ON t2.a IS NOT NULL;

-- Ensure the IS_NULL qual is reduced to constant-FALSE, since a) it's on a NOT
-- NULL column, and b) its Var is not nullable by any outer joins
EXPLAIN (COSTS OFF)
SELECT * FROM pred_tab t1
    LEFT JOIN pred_tab t2 ON TRUE
    LEFT JOIN pred_tab t3 ON t2.a IS NULL AND t2.b = 1;

-- Ensure the IS_NULL qual is not reduced to constant-FALSE when the column is
-- nullable by an outer join
EXPLAIN (COSTS OFF)
SELECT * FROM pred_tab t1
    LEFT JOIN pred_tab t2 ON t1.a = 1
    LEFT JOIN pred_tab t3 ON t2.a IS NULL;

--
-- Tests for OR clauses in join clauses
--

-- Ensure the OR clause is ignored when an OR branch is provably always true
EXPLAIN (COSTS OFF)
SELECT * FROM pred_tab t1
    LEFT JOIN pred_tab t2 ON TRUE
    LEFT JOIN pred_tab t3 ON t2.a IS NOT NULL OR t2.b = 1;

-- Ensure the NullTest is not ignored when the column is nullable by an outer
-- join
EXPLAIN (COSTS OFF)
SELECT * FROM pred_tab t1
    LEFT JOIN pred_tab t2 ON t1.a = 1
    LEFT JOIN pred_tab t3 ON t2.a IS NOT NULL OR t2.b = 1;

-- Ensure the OR clause is reduced to constant-FALSE when all OR branches are
-- provably false
EXPLAIN (COSTS OFF)
SELECT * FROM pred_tab t1
    LEFT JOIN pred_tab t2 ON TRUE
    LEFT JOIN pred_tab t3 ON (t2.a IS NULL OR t2.c IS NULL) AND t2.b = 1;

-- Ensure the OR clause is not reduced to constant-FALSE when a column is
-- made nullable from an outer join
EXPLAIN (COSTS OFF)
SELECT * FROM pred_tab t1
    LEFT JOIN pred_tab t2 ON t1.a = 1
    LEFT JOIN pred_tab t3 ON t2.a IS NULL OR t2.c IS NULL;

DROP TABLE pred_tab;

-- Validate we handle IS NULL and IS NOT NULL quals correctly with inheritance
-- parents.
CREATE TABLE pred_parent (a int);
CREATE TABLE pred_child () INHERITS (pred_parent);
ALTER TABLE ONLY pred_parent ALTER a SET NOT NULL;

-- Ensure that the scan on pred_child contains the IS NOT NULL qual.
EXPLAIN (COSTS OFF)
SELECT * FROM pred_parent WHERE a IS NOT NULL;

-- Ensure we only scan pred_child and not pred_parent
EXPLAIN (COSTS OFF)
SELECT * FROM pred_parent WHERE a IS NULL;

ALTER TABLE pred_parent ALTER a DROP NOT NULL;
ALTER TABLE pred_child ALTER a SET NOT NULL;

-- Ensure the IS NOT NULL qual is removed from the pred_child scan.
EXPLAIN (COSTS OFF)
SELECT * FROM pred_parent WHERE a IS NOT NULL;

-- Ensure we only scan pred_parent and not pred_child
EXPLAIN (COSTS OFF)
SELECT * FROM pred_parent WHERE a IS NULL;

DROP TABLE pred_parent, pred_child;
