# Changelog

All versions are tagged by the major Postgres version, plus an individual semver for this library itself.


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
