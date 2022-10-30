%module PgQuery									/* NS: This is lso the main Java class name. */
%{
#include "pg_query.h"						/* NS: Include the pg_query.h header in the generate C/C++ files. */
%}
%include "pg_query.h"						/* NS: Tell SWIG to analyze the pg_query.h header. */
