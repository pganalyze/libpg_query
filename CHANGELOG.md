# Changelog

All versions are tagged by the major Postgres version, plus an individual semver for this library itself.

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
