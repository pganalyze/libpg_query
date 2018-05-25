# Changelog

All versions are tagged by the major Postgres version, plus an individual semver for this library itself.

## 10-1.0.2

* Avoid compiler warning due to unused result in pg_query_parse_plpgsql


## 10-1.0.1   2017-10-31

* Fix fingerprint tests


## 10-1.0.0   2017-10-30

* First release based on PostgreSQL 10.0
  - Parse tree output may have changed in backwards-incompatible ways!
  - Fingerprint base version bumped to "02" to reflect the change in parse trees


## 9.5-1.7.1    2017-10-26

* Allow "$1 FROM $2" to be parsed
  - This is new with Postgres 10 output of pg_stat_statements, so we should
    treat this the same as "? FROM ?" in earlier versions.


## 9.5-1.7.0    2017-10-20

* Update to Postgres 9.5.9
* Support gcc versions earlier than 4.6.0
* Export version information in pg_query.h directly


## 9.5-1.6.2    2017-07-30

* Fingerprinting Version 1.3
  * Attributes to be ignored:
    * RangeVar.relname (if node also has RangeVar.relpersistence = "t")
  * Special cases: List nodes where parent field name is valuesLists
    * Follow same logic described for fromClause/targetList/cols/rexpr


## 9.5-1.6.1    2017-07-29

* Fingerprinting Version 1.2
  * Ignore portal_name in DeclareCursorStmt, FetchStmt and ClosePortalStmt


## 9.5-1.6.0    2017-07-29

* Change normalization methods to output $1/$2 .. $N instead of ? characters
  * BREAKING CHANGE in pg_query_normalize(..) output
  * This matches the change in the upcoming Postgres 10, and makes it easier
    to migrate applications to the new normalization format


## 9.5-1.5.0    2017-05-26

* Update to Postgres 9.5.7
* Disable 128-bit integer support (they are not used), to support 32-bit archs [@herwinw](https://github.com/herwinw)
* Cleanup efforts [@herwinw](https://github.com/herwinw)
  * Improve concurrency tests
  * Make sure we have a valid proc_source
  * Normalized whitespace in pg_query_parse_plpgsql
  * Move inclusion of stdio.h in plpgsql parser


## 9.5-1.4.2    2016-12-06

* Cut off fingerprints at 100 nodes deep to avoid excessive runtimes/memory
* Fix warning on Linux due to missing asprintf include


## 9.5-1.4.1    2016-06-26

* Automatically call pg_query_init as needed to ease threaded usage


## 9.5-1.4.0    2016-06-26

* Clean up includes to avoid dependency on stdbool.h and xlocale.h
* Change PL/pgSQL input to be the full CREATE FUNCTION statement
  * This is necessary for parsing, since we need the argument and return types
* Fingerprinting Version 1.1
  * Only ignore ResTarget.name when parent field name is targetList *and*
    we have a SelectStmt as a parent node (fixes UpdateStmt fingerprinting)
* Normalize the password in ALTER ROLE ... PASSWORD '123' statements
* Make library thread-safe through thread-local storage [#13](https://github.com/lfittl/libpg_query/issues/13)


## 9.5-1.3.0    2016-05-31

* Extract source code using LLVM instead of manually compiling the right objects
  * This speeds up build times considerably since we don't download the Postgres
    source anymore, instead shipping a partial copy created as part of a release.
* Experimental support for parsing PL/pgSQL source code (output format subject to change)


## 9.5-1.2.1    2016-05-17

* Make sure we encode special characters correctly in JSON output ([@zhm](https://github.com/zhm) [#11](https://github.com/lfittl/libpg_query/pull/11))


## 9.5-1.2.0    2016-05-16

* Fix stack overflow when parsing CREATE FOREIGN TABLE ([#9](https://github.com/lfittl/libpg_query/issues/9))
* Update to PostgreSQL 9.5.3


## 9.5-1.1.0    2016-04-17

* Add pg_query_fingerprint() method that uniquely identifies SQL queries,
  whilst ignoring formatting and individual constant values
* Update to PostgreSQL 9.5.2


## 9.5-1.0.0    2016-03-06

* First release based on PostgreSQL 9.5.1
* Make JSON_OUTPUT_V2 the default and remove outfuncs patch
  * NOTE: This is a backwards incompatible change in the output parsetree format!


## 9.4-1.0.0    2016-03-06

* First tagged release based on PostgreSQL 9.4.5
