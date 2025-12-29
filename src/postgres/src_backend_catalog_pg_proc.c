/*--------------------------------------------------------------------
 * Symbols referenced in this file:
 * - function_parse_error_transpose
 *--------------------------------------------------------------------
 */

/*-------------------------------------------------------------------------
 *
 * pg_proc.c
 *	  routines to support manipulation of the pg_proc relation
 *
 * Portions Copyright (c) 1996-2025, PostgreSQL Global Development Group
 * Portions Copyright (c) 1994, Regents of the University of California
 *
 *
 * IDENTIFICATION
 *	  src/backend/catalog/pg_proc.c
 *
 *-------------------------------------------------------------------------
 */
#include "postgres.h"

#include "access/htup_details.h"
#include "access/table.h"
#include "access/xact.h"
#include "catalog/catalog.h"
#include "catalog/dependency.h"
#include "catalog/indexing.h"
#include "catalog/objectaccess.h"
#include "catalog/pg_language.h"
#include "catalog/pg_namespace.h"
#include "catalog/pg_proc.h"
#include "catalog/pg_transform.h"
#include "catalog/pg_type.h"
#include "executor/functions.h"
#include "funcapi.h"
#include "mb/pg_wchar.h"
#include "miscadmin.h"
#include "nodes/nodeFuncs.h"
#include "parser/parse_coerce.h"
#include "pgstat.h"
#include "rewrite/rewriteHandler.h"
#include "tcop/pquery.h"
#include "tcop/tcopprot.h"
#include "utils/acl.h"
#include "utils/builtins.h"
#include "utils/lsyscache.h"
#include "utils/regproc.h"
#include "utils/rel.h"
#include "utils/syscache.h"


typedef struct
{
	char	   *proname;
	char	   *prosrc;
} parse_error_callback_arg;

static void sql_function_parse_error_callback(void *arg);
static int	match_prosrc_to_query(const char *prosrc, const char *queryText,
								  int cursorpos);
static bool match_prosrc_to_literal(const char *prosrc, const char *literal,
									int cursorpos, int *newcursorpos);


/* ----------------------------------------------------------------
 *		ProcedureCreate
 *
 *	procedureName: string name of routine (proname)
 *	procNamespace: OID of namespace (pronamespace)
 *	replace: true to allow replacement of an existing pg_proc entry
 *	returnsSet: returns set? (proretset)
 *	returnType: OID of result type (prorettype)
 *	proowner: OID of owner role (proowner)
 *	languageObjectId: OID of function language (prolang)
 *	languageValidator: OID of validator function to apply, if any
 *	prosrc: string form of function definition (prosrc)
 *	probin: string form of binary reference, or NULL (probin)
 *	prosqlbody: Node tree of pre-parsed SQL body, or NULL (prosqlbody)
 *	prokind: function/aggregate/procedure/etc code (prokind)
 *	security_definer: security definer? (prosecdef)
 *	isLeakProof: leak proof? (proleakproof)
 *	isStrict: strict? (proisstrict)
 *	volatility: volatility code (provolatile)
 *	parallel: parallel safety code (proparallel)
 *	parameterTypes: input parameter types, as an oidvector (proargtypes)
 *	allParameterTypes: all parameter types, as an OID array (proallargtypes)
 *	parameterModes: parameter modes, as a "char" array (proargmodes)
 *	parameterNames: parameter names, as a text array (proargnames)
 *	parameterDefaults: defaults, as a List of Node trees (proargdefaults)
 *	trftypes: transformable type OIDs, as an OID array (protrftypes)
 *	trfoids: List of transform OIDs that routine should depend on
 *	proconfig: GUC set clauses, as a text array (proconfig)
 *	prosupport: OID of support function, if any (prosupport)
 *	procost: cost factor (procost)
 *	prorows: estimated output rows for a SRF (prorows)
 *
 * Note: allParameterTypes, parameterModes, parameterNames, trftypes, and proconfig
 * are either arrays of the proper types or NULL.  We declare them Datum,
 * not "ArrayType *", to avoid importing array.h into pg_proc.h.
 * ----------------------------------------------------------------
 */




/*
 * Validator for internal functions
 *
 * Check that the given internal function name (the "prosrc" value) is
 * a known builtin function.
 */




/*
 * Validator for C language functions
 *
 * Make sure that the library file exists, is loadable, and contains
 * the specified link symbol. Also check for a valid function
 * information record.
 */



/*
 * Validator for SQL language functions
 *
 * Parse it here in order to be sure that it contains no syntax errors.
 */


/*
 * Error context callback for handling errors in SQL function definitions
 */


/*
 * Adjust a syntax error occurring inside the function body of a CREATE
 * FUNCTION or DO command.  This can be used by any function validator or
 * anonymous-block handler, not only for SQL-language functions.
 * It is assumed that the syntax error position is initially relative to the
 * function body string (as passed in).  If possible, we adjust the position
 * to reference the original command text; if we can't manage that, we set
 * up an "internal query" syntax error instead.
 *
 * Returns true if a syntax error was processed, false if not.
 */

bool
function_parse_error_transpose(const char *prosrc)
{
return false;}

/*
 * Try to locate the string literal containing the function body in the
 * given text of the CREATE FUNCTION or DO command.  If successful, return
 * the character (not byte) index within the command corresponding to the
 * given character index within the literal.  If not successful, return 0.
 */


/*
 * Try to match the given source text to a single-quoted literal.
 * If successful, adjust newcursorpos to correspond to the character
 * (not byte) index corresponding to cursorpos in the source text.
 *
 * At entry, literal points just past a ' character.  We must check for the
 * trailing quote.
 */



