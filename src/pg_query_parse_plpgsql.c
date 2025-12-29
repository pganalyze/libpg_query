#include <stdio.h>

#include "pg_query.h"
#include "pg_query_internal.h"
#include "pg_query_json_plpgsql.h"

#include <assert.h>

#include <catalog/pg_type.h>
#include <catalog/objectaddress.h>
#include <catalog/pg_language_d.h>
#include <catalog/pg_proc.h>
#include <commands/defrem.h>
#include <nodes/parsenodes.h>
#include <nodes/nodeFuncs.h>
#include <parser/parse_type.h>
#include <utils/builtins.h>
#include <utils/lsyscache.h>
#include <utils/syscache.h>

typedef struct {
	PLpgSQL_function *func;
	PgQueryError* error;
} PgQueryInternalPlpgsqlFuncAndError;

static PgQueryInternalPlpgsqlFuncAndError pg_query_raw_parse_plpgsql(Node* stmt);

/*
 * Add a name for a function parameter to the function's namespace
 */
static void
add_parameter_name(PLpgSQL_nsitem_type itemtype, int itemno, const char *name)
{
	/*
	 * Before adding the name, check for duplicates.  We need this even though
	 * functioncmds.c has a similar check, because that code explicitly
	 * doesn't complain about conflicting IN and OUT parameter names.  In
	 * plpgsql, such names are in the same namespace, so there is no way to
	 * disambiguate.
	 */
	if (plpgsql_ns_lookup(plpgsql_ns_top(), true,
						  name, NULL, NULL,
						  NULL) != NULL)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_FUNCTION_DEFINITION),
				 errmsg("parameter name \"%s\" used more than once",
						name)));

	/* OK, add the name */
	plpgsql_ns_additem(itemtype, itemno, name);
}

/*
 * Add a dummy RETURN statement to the given function's body
 */
static void
add_dummy_return(PLpgSQL_function *function)
{
	/*
	 * If the outer block has an EXCEPTION clause, we need to make a new outer
	 * block, since the added RETURN shouldn't act like it is inside the
	 * EXCEPTION clause.
	 */
	if (function->action->exceptions != NULL)
	{
		PLpgSQL_stmt_block *new;

		new = palloc0(sizeof(PLpgSQL_stmt_block));
		new->cmd_type = PLPGSQL_STMT_BLOCK;
		new->body = list_make1(function->action);

		function->action = new;
	}
	if (function->action->body == NIL ||
		((PLpgSQL_stmt *) llast(function->action->body))->cmd_type != PLPGSQL_STMT_RETURN)
	{
		PLpgSQL_stmt_return *new;

		new = palloc0(sizeof(PLpgSQL_stmt_return));
		new->cmd_type = PLPGSQL_STMT_RETURN;
		new->expr = NULL;
		new->retvarno = function->out_param_varno;

		function->action->body = lappend(function->action->body, new);
	}
}

/*
 * Build a row-variable data structure given the component variables.
 * Include a rowtupdesc, since we will need to materialize the row result.
 */
static PLpgSQL_row *
build_row_from_vars(PLpgSQL_variable **vars, int numvars)
{
	PLpgSQL_row *row;
	int			i;

	row = palloc0(sizeof(PLpgSQL_row));
	row->dtype = PLPGSQL_DTYPE_ROW;
	row->refname = "(unnamed row)";
	row->lineno = -1;
	row->rowtupdesc = CreateTemplateTupleDesc(numvars);
	row->nfields = numvars;
	row->fieldnames = palloc(numvars * sizeof(char *));
	row->varnos = palloc(numvars * sizeof(int));

	for (i = 0; i < numvars; i++)
	{
		PLpgSQL_variable *var = vars[i];
		Oid			typoid;
		int32		typmod;
		Oid			typcoll;

		/* Member vars of a row should never be const */
		Assert(!var->isconst);

		switch (var->dtype)
		{
			case PLPGSQL_DTYPE_VAR:
			case PLPGSQL_DTYPE_PROMISE:
				typoid = ((PLpgSQL_var *) var)->datatype->typoid;
				typmod = ((PLpgSQL_var *) var)->datatype->atttypmod;
				typcoll = ((PLpgSQL_var *) var)->datatype->collation;
				break;

			case PLPGSQL_DTYPE_REC:
				/* shouldn't need to revalidate rectypeid already... */
				typoid = ((PLpgSQL_rec *) var)->rectypeid;
				typmod = -1;	/* don't know typmod, if it's used at all */
				typcoll = InvalidOid;	/* composite types have no collation */
				break;

			default:
				elog(ERROR, "unrecognized dtype: %d", var->dtype);
				typoid = InvalidOid;	/* keep compiler quiet */
				typmod = 0;
				typcoll = InvalidOid;
				break;
		}

		row->fieldnames[i] = var->refname;
		row->varnos[i] = var->dno;

		TupleDescInitEntry(row->rowtupdesc, i + 1,
						   var->refname,
						   typoid, typmod,
						   0);
		TupleDescInitEntryCollation(row->rowtupdesc, i + 1, typcoll);
	}

	return row;
}

/*
 *	 Examine the RETURNS clause of the CREATE FUNCTION statement
 *	 and return information about it as *prorettype_p and *returnsSet_p.
 *
 * This is more complex than the average typename lookup because we want to
 * allow a shell type to be used, or even created if the specified return type
 * doesn't exist yet.  (Without this, there's no way to define the I/O procs
 * for a new type.)  But SQL function creation won't cope, so error out if
 * the target language is SQL.  (We do this here, not in the SQL-function
 * validator, so as not to produce a NOTICE and then an ERROR for the same
 * condition.)
 */
static void
compute_return_type(TypeName *returnType, Oid languageOid,
					Oid *prorettype_p, bool *returnsSet_p)
{
	Oid			rettype;
	Type		typtup;
	//AclResult	aclresult;

	typtup = LookupTypeName(NULL, returnType, NULL, false);

	if (typtup)
	{
		if (!((Form_pg_type) GETSTRUCT(typtup))->typisdefined)
		{
			if (languageOid == SQLlanguageId)
				ereport(ERROR,
						(errcode(ERRCODE_INVALID_FUNCTION_DEFINITION),
						 errmsg("SQL function cannot return shell type %s",
								TypeNameToString(returnType))));
			else
				ereport(NOTICE,
						(errcode(ERRCODE_WRONG_OBJECT_TYPE),
						 errmsg("return type %s is only a shell",
								TypeNameToString(returnType))));
		}
		rettype = typeTypeId(typtup);
		ReleaseSysCache(typtup);
	}
	else
	{
		char	   *typnam = TypeNameToString(returnType);
		Oid			namespaceId;
		char	   *typname;
		ObjectAddress address;

		/*
		 * Only C-coded functions can be I/O functions.  We enforce this
		 * restriction here mainly to prevent littering the catalogs with
		 * shell types due to simple typos in user-defined function
		 * definitions.
		 */
		if (languageOid != INTERNALlanguageId &&
			languageOid != ClanguageId)
			ereport(ERROR,
					(errcode(ERRCODE_UNDEFINED_OBJECT),
					 errmsg("type \"%s\" does not exist", typnam)));

		/* Reject if there's typmod decoration, too */
		if (returnType->typmods != NIL)
			ereport(ERROR,
					(errcode(ERRCODE_SYNTAX_ERROR),
					 errmsg("type modifier cannot be specified for shell type \"%s\"",
							typnam)));

		elog(ERROR, "Not implemented");

		/* Otherwise, go ahead and make a shell type */
		/*ereport(NOTICE,
				(errcode(ERRCODE_UNDEFINED_OBJECT),
				 errmsg("type \"%s\" is not yet defined", typnam),
				 errdetail("Creating a shell type definition.")));
		namespaceId = QualifiedNameGetCreationNamespace(returnType->names,
														&typname);
		aclresult = object_aclcheck(NamespaceRelationId, namespaceId, GetUserId(),
									ACL_CREATE);
		if (aclresult != ACLCHECK_OK)
			aclcheck_error(aclresult, OBJECT_SCHEMA,
						   get_namespace_name(namespaceId));
		address = TypeShellMake(typname, namespaceId, GetUserId());
		rettype = address.objectId;
		Assert(OidIsValid(rettype));*/
	}

	//aclresult = object_aclcheck(TypeRelationId, rettype, GetUserId(), ACL_USAGE);
	//if (aclresult != ACLCHECK_OK)
	//	aclcheck_error_type(aclresult, rettype);

	*prorettype_p = rettype;
	*returnsSet_p = returnType->setof;
}

struct compile_error_callback_arg
{
	const char *proc_source;
	yyscan_t	yyscanner;
};

/*
 * error context callback to let us supply a call-stack traceback.
 * If we are validating or executing an anonymous code block, the function
 * source text is passed as an argument.
 */
static void
plpgsql_compile_error_callback(void *arg)
{
	struct compile_error_callback_arg *cbarg = (struct compile_error_callback_arg *) arg;
	yyscan_t	yyscanner = cbarg->yyscanner;

	if (cbarg->proc_source)
	{
		/*
		 * Try to convert syntax error position to reference text of original
		 * CREATE FUNCTION or DO command.
		 */
		if (function_parse_error_transpose(cbarg->proc_source))
			return;

		/*
		 * Done if a syntax error position was reported; otherwise we have to
		 * fall back to a "near line N" report.
		 */
	}

	if (plpgsql_error_funcname)
		errcontext("compilation of PL/pgSQL function \"%s\" near line %d",
				   plpgsql_error_funcname, plpgsql_latest_lineno(yyscanner));
}

static PLpgSQL_function *compile_do_stmt(DoStmt* stmt)
{
	char *proc_source = NULL;
	const ListCell *lc;
	char *language = "plpgsql";

	assert(IsA(stmt, DoStmt));

	foreach(lc, stmt->args)
	{
		DefElem* elem = (DefElem*) lfirst(lc);

		if (strcmp(elem->defname, "as") == 0) {

			assert(IsA(elem->arg, String));
			proc_source = strVal(elem->arg);
		} else if (strcmp(elem->defname, "language") == 0) {
			language = strVal(elem->arg);
		}
	}

	assert(proc_source != NULL);

	if(strcmp(language, "plpgsql") != 0) {
		return (PLpgSQL_function *) palloc0(sizeof(PLpgSQL_function));
	}
	return plpgsql_compile_inline(proc_source);

}

static Form_pg_proc proc_from_create_stmt(CreateFunctionStmt* stmt, int *numargs, Oid **p_argtypes, char ***p_argnames, char **p_argmodes)
{
	Form_pg_proc procStruct = palloc0(sizeof(FormData_pg_proc));
	oidvector  *parameterTypes;
	List	   *parameterTypes_list = NIL;
	ArrayType  *allParameterTypes;
	ArrayType  *parameterModes;
	ArrayType  *parameterNames;
	List	   *inParameterNames_list = NIL;
	List	   *parameterDefaults;
	Oid			variadicArgType;
	Oid			requiredResultType;
	Datum	   *elems;
	int			nelems;
	int			i;

	procStruct->prokind = stmt->is_procedure ? OBJECT_PROCEDURE : OBJECT_FUNCTION;
	//procStruct->prorettype = VOIDOID; // TODO: Make this dependent on CreateFunctionStmt
	//procStruct->proretset = is_setof;

	interpret_function_parameter_list(palloc0(sizeof(ParseState)),
									  stmt->parameters,
									  InvalidOid /* We don't know the PL/pgSQL language OID */,
									  stmt->is_procedure ? OBJECT_PROCEDURE : OBJECT_FUNCTION,
									  &parameterTypes,
									  &parameterTypes_list,
									  &allParameterTypes,
									  &parameterModes,
									  &parameterNames,
									  &inParameterNames_list,
									  &parameterDefaults,
									  &variadicArgType,
									  &requiredResultType);

	if (stmt->is_procedure)
	{
		Assert(!stmt->returnType);
		procStruct->prorettype = requiredResultType ? requiredResultType : VOIDOID;
		procStruct->proretset = false;
	}
	else if (stmt->returnType)
	{
		/* explicit RETURNS clause */
		compute_return_type(stmt->returnType, InvalidOid,
							&procStruct->prorettype, &procStruct->proretset);
		if (OidIsValid(requiredResultType) && procStruct->prorettype != requiredResultType)
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_FUNCTION_DEFINITION),
					 errmsg("function result type must be %s because of OUT parameters",
							format_type_be(requiredResultType))));
	}
	else if (OidIsValid(requiredResultType))
	{
		/* default RETURNS clause from OUT parameters */
		procStruct->prorettype = requiredResultType;
		procStruct->proretset = false;
	}
	else
	{
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_FUNCTION_DEFINITION),
				 errmsg("function result type must be specified")));
		/* Alternative possibility: default to RETURNS VOID */
		procStruct->prorettype = VOIDOID;
		procStruct->proretset = false;
	}

	if (allParameterTypes != NULL)
	{
		deconstruct_array_builtin(allParameterTypes, OIDOID,
								  &elems, NULL, numargs);
		*p_argtypes = (Oid *) palloc(*numargs * sizeof(Oid));
		for (i = 0; i < *numargs; i++)
			(*p_argtypes)[i] = elems[i];
	}
	else
	{
		*p_argtypes = parameterTypes->values;
		*numargs = parameterTypes->dim1;
	}

	if (parameterModes != NULL)
	{
		deconstruct_array_builtin(parameterModes, CHAROID,
								  &elems, NULL, &nelems);
		Assert(nelems == *numargs);
		*p_argmodes = (char *) palloc(*numargs * sizeof(char));
		for (i = 0; i < *numargs; i++)
			(*p_argmodes)[i] = elems[i];
	}
	else
	{
		*p_argmodes = NULL;
	}

	if (parameterNames != NULL)
	{
		deconstruct_array_builtin(parameterNames, TEXTOID,
								  &elems, NULL, &nelems);
		Assert(nelems == *numargs);
		*p_argnames = (char **) palloc(sizeof(char *) * *numargs);
		for (i = 0; i < *numargs; i++)
			(*p_argnames)[i] = TextDatumGetCString(elems[i]);
	}
	else
	{
		*p_argnames = NULL;
	}

	return procStruct;
}

static PLpgSQL_function *compile_create_function_stmt(CreateFunctionStmt* stmt)
{
	PLpgSQL_function *function = (PLpgSQL_function *) palloc0(sizeof(PLpgSQL_function));
	Form_pg_proc procStruct = NULL;//(Form_pg_proc) GETSTRUCT(procTup)
	bool		is_dml_trigger = false;//CALLED_AS_TRIGGER(fcinfo);
	bool		is_event_trigger = false;//CALLED_AS_EVENT_TRIGGER(fcinfo);
	yyscan_t	scanner;
	char *func_name;
	char *proc_source = NULL;
	HeapTuple	typeTup;
	Form_pg_type typeStruct;
	PLpgSQL_variable *var;
	PLpgSQL_rec *rec;
	int			i;
	struct compile_error_callback_arg cbarg;
	ErrorContextCallback plerrcontext;
	int			parse_rc;
	Oid			rettypeid;
	int			numargs;
	int			num_in_args = 0;
	int			num_out_args = 0;
	Oid		   *argtypes;
	char	  **argnames;
	char	   *argmodes;
	int		   *in_arg_varnos = NULL;
	PLpgSQL_variable **out_arg_variables;
	MemoryContext func_cxt;
	char *language = "plpgsql";
	bool forValidator = true;

	assert(IsA(stmt, CreateFunctionStmt));

	func_name = strVal(linitial(stmt->funcname));

	foreach_ptr(DefElem, elem, stmt->options)
	{
		if (strcmp(elem->defname, "as") == 0)
		{
			assert(IsA(elem->arg, List));

			foreach_ptr(String, proc_source_str, (List*) elem->arg)
			{
				proc_source = proc_source_str->sval;
			}
		}
		else if (strcmp(elem->defname, "language") == 0)
		{
			language = strVal(elem->arg);
		}
	}

	assert(proc_source != NULL);

	if (strcmp(language, "plpgsql") != 0)
		return (PLpgSQL_function *) palloc0(sizeof(PLpgSQL_function));

	if (stmt->returnType != NULL)
	{
		foreach_ptr(String, val, stmt->returnType->names)
		{
			if (strcmp(val->sval, "trigger") == 0)
				is_dml_trigger = true;
		}
	}

	/* Populate an interim procStruct from the passed in CREATE FUNCTION */
	procStruct = proc_from_create_stmt(stmt, &numargs, &argtypes, &argnames, &argmodes);

	/*
	 * Setup the scanner input and error info.  We assume that this function
	 * cannot be invoked recursively, so there's no need to save and restore
	 * the static variables used here.
	 */
	scanner = plpgsql_scanner_init(proc_source);

	plpgsql_error_funcname = func_name;

	/*
	 * Setup error traceback support for ereport()
	 */
	cbarg.proc_source = proc_source;
	cbarg.yyscanner = scanner;
	plerrcontext.callback = plpgsql_compile_error_callback;
	plerrcontext.arg = &cbarg;
	plerrcontext.previous = error_context_stack;
	error_context_stack = &plerrcontext;

	/* Do extra syntax checking if check_function_bodies is on */
	plpgsql_check_syntax = true;

	plpgsql_curr_compile = function;

	/*
	 * All the rest of the compile-time storage (e.g. parse tree) is kept in
	 * its own memory context, so it can be reclaimed easily.
	 */
	func_cxt = AllocSetContextCreate(CurrentMemoryContext,
									 "PL/pgSQL pg_query context",
									 ALLOCSET_DEFAULT_SIZES);
	plpgsql_compile_tmp_cxt = MemoryContextSwitchTo(func_cxt);

	function->fn_signature = pstrdup(func_name);
	function->fn_is_trigger = PLPGSQL_NOT_TRIGGER;
	function->fn_input_collation = InvalidOid;
	function->fn_cxt = func_cxt;
	function->out_param_varno = -1;		/* set up for no OUT param */
	function->resolve_option = plpgsql_variable_conflict;
	function->print_strict_params = plpgsql_print_strict_params;
	function->extra_warnings = plpgsql_extra_warnings;
	function->extra_errors = plpgsql_extra_errors;

	if (is_dml_trigger)
		function->fn_is_trigger = PLPGSQL_DML_TRIGGER;
	else if (is_event_trigger)
		function->fn_is_trigger = PLPGSQL_EVENT_TRIGGER;
	else
		function->fn_is_trigger = PLPGSQL_NOT_TRIGGER;

	function->fn_prokind = procStruct->prokind;

	function->nstatements = 0;
	function->requires_procedure_resowner = false;
	function->has_exception_block = false;

	/*
	 * Initialize the compiler, particularly the namespace stack.  The
	 * outermost namespace contains function parameters and other special
	 * variables (such as FOUND), and is named after the function itself.
	 */
	plpgsql_ns_init();
	plpgsql_ns_push(func_name, PLPGSQL_LABEL_BLOCK);
	plpgsql_DumpExecTree = false;
	plpgsql_start_datums();

	/* Setup parameter names */
	switch (function->fn_is_trigger)
	{
		case PLPGSQL_NOT_TRIGGER:

			/*
			 * Fetch info about the procedure's parameters. Allocations aren't
			 * needed permanently, so make them in tmp cxt.
			 *
			 * We also need to resolve any polymorphic input or output
			 * argument types.  In validation mode we won't be able to, so we
			 * arbitrarily assume we are dealing with integers.
			 */
			MemoryContextSwitchTo(plpgsql_compile_tmp_cxt);

			/*numargs = get_func_arg_info(procTup,
			//							&argtypes, &argnames, &argmodes);*/
			// TODO: Populate numargs/argtypes/argnames/argmodes

			/*cfunc_resolve_polymorphic_argtypes(numargs, argtypes, argmodes,
											   fcinfo->flinfo->fn_expr,
											   forValidator,
											   plpgsql_error_funcname);*/
			// TODO: Can we do this resolve in some way?

			in_arg_varnos = (int *) palloc(numargs * sizeof(int));
			out_arg_variables = (PLpgSQL_variable **) palloc(numargs * sizeof(PLpgSQL_variable *));

			MemoryContextSwitchTo(func_cxt);

			/*
			 * Create the variables for the procedure's parameters.
			 */
			for (i = 0; i < numargs; i++)
			{
				char		buf[32];
				Oid			argtypeid = argtypes[i];
				char		argmode = argmodes ? argmodes[i] : PROARGMODE_IN;
				PLpgSQL_type *argdtype;
				PLpgSQL_variable *argvariable;
				PLpgSQL_nsitem_type argitemtype;

				/* Create $n name for variable */
				snprintf(buf, sizeof(buf), "$%d", i + 1);

				/* Create datatype info */
				argdtype = plpgsql_build_datatype(argtypeid,
												  -1,
												  function->fn_input_collation,
												  NULL);

				/* Disallow pseudotype argument */
				/* (note we already replaced polymorphic types) */
				/* (build_variable would do this, but wrong message) */
				if (argdtype->ttype == PLPGSQL_TTYPE_PSEUDO)
					ereport(ERROR,
							(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
							 errmsg("PL/pgSQL functions cannot accept type %s",
									format_type_be(argtypeid))));

				/*
				 * Build variable and add to datum list.  If there's a name
				 * for the argument, use that as refname, else use $n name.
				 */
				argvariable = plpgsql_build_variable((argnames &&
													  argnames[i][0] != '\0') ?
													 argnames[i] : buf,
													 0, argdtype, false);

				if (argvariable->dtype == PLPGSQL_DTYPE_VAR)
				{
					argitemtype = PLPGSQL_NSTYPE_VAR;
				}
				else
				{
					Assert(argvariable->dtype == PLPGSQL_DTYPE_REC);
					argitemtype = PLPGSQL_NSTYPE_REC;
				}

				/* Remember arguments in appropriate arrays */
				if (argmode == PROARGMODE_IN ||
					argmode == PROARGMODE_INOUT ||
					argmode == PROARGMODE_VARIADIC)
					in_arg_varnos[num_in_args++] = argvariable->dno;
				if (argmode == PROARGMODE_OUT ||
					argmode == PROARGMODE_INOUT ||
					argmode == PROARGMODE_TABLE)
					out_arg_variables[num_out_args++] = argvariable;

				/* Add to namespace under the $n name */
				add_parameter_name(argitemtype, argvariable->dno, buf);

				/* If there's a name for the argument, make an alias */
				if (argnames && argnames[i][0] != '\0')
					add_parameter_name(argitemtype, argvariable->dno,
									   argnames[i]);
			}

			/*
			 * If there's just one OUT parameter, out_param_varno points
			 * directly to it.  If there's more than one, build a row that
			 * holds all of them.  Procedures return a row even for one OUT
			 * parameter.
			 */
			if (num_out_args > 1 ||
				(num_out_args == 1 && function->fn_prokind == PROKIND_PROCEDURE))
			{
				PLpgSQL_row *row = build_row_from_vars(out_arg_variables,
													   num_out_args);

				plpgsql_adddatum((PLpgSQL_datum *) row);
				function->out_param_varno = row->dno;
			}
			else if (num_out_args == 1)
				function->out_param_varno = out_arg_variables[0]->dno;

			/*
			 * Check for a polymorphic returntype. If found, use the actual
			 * returntype type from the caller's FuncExpr node, if we have
			 * one.  (In validation mode we arbitrarily assume we are dealing
			 * with integers.)
			 *
			 * Note: errcode is FEATURE_NOT_SUPPORTED because it should always
			 * work; if it doesn't we're in some context that fails to make
			 * the info available.
			 */
			rettypeid = procStruct->prorettype;
			if (IsPolymorphicType(rettypeid))
			{
				if (forValidator)
				{
					if (rettypeid == ANYARRAYOID ||
						rettypeid == ANYCOMPATIBLEARRAYOID)
						rettypeid = INT4ARRAYOID;
					else if (rettypeid == ANYRANGEOID ||
							 rettypeid == ANYCOMPATIBLERANGEOID)
						rettypeid = INT4RANGEOID;
					else if (rettypeid == ANYMULTIRANGEOID)
						rettypeid = INT4MULTIRANGEOID;
					else		/* ANYELEMENT or ANYNONARRAY or ANYCOMPATIBLE */
						rettypeid = INT4OID;
					/* XXX what could we use for ANYENUM? */
				}
				else
				{
					Assert(false); // We're always in validating mode
					/*rettypeid = get_fn_expr_rettype(fcinfo->flinfo);
					if (!OidIsValid(rettypeid))
						ereport(ERROR,
								(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
								 errmsg("could not determine actual return type "
										"for polymorphic function \"%s\"",
										plpgsql_error_funcname)));*/
				}
			}

			/*
			 * Normal function has a defined returntype
			 */
			function->fn_rettype = rettypeid;
			function->fn_retset = procStruct->proretset;

			/*
			 * Lookup the function's return type
			 */
			typeTup = SearchSysCache1(TYPEOID, ObjectIdGetDatum(rettypeid));
			if (!HeapTupleIsValid(typeTup))
				elog(ERROR, "cache lookup failed for type %u", rettypeid);
			typeStruct = (Form_pg_type) GETSTRUCT(typeTup);

			/* Disallow pseudotype result, except VOID or RECORD */
			/* (note we already replaced polymorphic types) */
			if (typeStruct->typtype == TYPTYPE_PSEUDO)
			{
				if (rettypeid == VOIDOID ||
					rettypeid == RECORDOID ||
					rettypeid == UNKNOWNOID) // Changed: UNKNOWNOID is added here because we return this whne we don't know a type
					 /* okay */ ;
				else if (rettypeid == TRIGGEROID || rettypeid == EVENT_TRIGGEROID)
					ereport(ERROR,
							(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
							 errmsg("trigger functions can only be called as triggers")));
				else
					ereport(ERROR,
							(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
							 errmsg("PL/pgSQL functions cannot return type %s",
									format_type_be(rettypeid))));
			}

			function->fn_retistuple = type_is_rowtype(rettypeid);
			function->fn_retisdomain = (typeStruct->typtype == TYPTYPE_DOMAIN);
			function->fn_retbyval = typeStruct->typbyval;
			function->fn_rettyplen = typeStruct->typlen;

			/*
			 * install $0 reference, but only for polymorphic return types,
			 * and not when the return is specified through an output
			 * parameter.
			 */
			if (IsPolymorphicType(procStruct->prorettype) &&
				num_out_args == 0)
			{
				(void) plpgsql_build_variable("$0", 0,
											  //build_datatype(typeTup,
											  plpgsql_build_datatype(rettypeid,
															 -1,
															 function->fn_input_collation,
															 NULL),
											  true);
			}

			/*ReleaseSysCache(typeTup);*/
			break;

		case PLPGSQL_DML_TRIGGER:
			/* Trigger procedure's return type is unknown yet */
			function->fn_rettype = InvalidOid;
			function->fn_retbyval = false;
			function->fn_retistuple = true;
			function->fn_retisdomain = false;
			function->fn_retset = false;

			/* shouldn't be any declared arguments */
			if (procStruct->pronargs != 0)
				ereport(ERROR,
						(errcode(ERRCODE_INVALID_FUNCTION_DEFINITION),
						 errmsg("trigger functions cannot have declared arguments"),
						 errhint("The arguments of the trigger can be accessed through TG_NARGS and TG_ARGV instead.")));

			/* Add the record for referencing NEW ROW */
			rec = plpgsql_build_record("new", 0, NULL, RECORDOID, true);
			function->new_varno = rec->dno;

			/* Add the record for referencing OLD ROW */
			rec = plpgsql_build_record("old", 0, NULL, RECORDOID, true);
			function->old_varno = rec->dno;

			/* Add the variable tg_name */
			var = plpgsql_build_variable("tg_name", 0,
										 plpgsql_build_datatype(NAMEOID,
																-1,
																function->fn_input_collation,
																NULL),
										 true);
			Assert(var->dtype == PLPGSQL_DTYPE_VAR);
			var->dtype = PLPGSQL_DTYPE_PROMISE;
			((PLpgSQL_var *) var)->promise = PLPGSQL_PROMISE_TG_NAME;

			/* Add the variable tg_when */
			var = plpgsql_build_variable("tg_when", 0,
										 plpgsql_build_datatype(TEXTOID,
																-1,
																function->fn_input_collation,
																NULL),
										 true);
			Assert(var->dtype == PLPGSQL_DTYPE_VAR);
			var->dtype = PLPGSQL_DTYPE_PROMISE;
			((PLpgSQL_var *) var)->promise = PLPGSQL_PROMISE_TG_WHEN;

			/* Add the variable tg_level */
			var = plpgsql_build_variable("tg_level", 0,
										 plpgsql_build_datatype(TEXTOID,
																-1,
																function->fn_input_collation,
																NULL),
										 true);
			Assert(var->dtype == PLPGSQL_DTYPE_VAR);
			var->dtype = PLPGSQL_DTYPE_PROMISE;
			((PLpgSQL_var *) var)->promise = PLPGSQL_PROMISE_TG_LEVEL;

			/* Add the variable tg_op */
			var = plpgsql_build_variable("tg_op", 0,
										 plpgsql_build_datatype(TEXTOID,
																-1,
																function->fn_input_collation,
																NULL),
										 true);
			Assert(var->dtype == PLPGSQL_DTYPE_VAR);
			var->dtype = PLPGSQL_DTYPE_PROMISE;
			((PLpgSQL_var *) var)->promise = PLPGSQL_PROMISE_TG_OP;

			/* Add the variable tg_relid */
			var = plpgsql_build_variable("tg_relid", 0,
										 plpgsql_build_datatype(OIDOID,
																-1,
																InvalidOid,
																NULL),
										 true);
			Assert(var->dtype == PLPGSQL_DTYPE_VAR);
			var->dtype = PLPGSQL_DTYPE_PROMISE;
			((PLpgSQL_var *) var)->promise = PLPGSQL_PROMISE_TG_RELID;

			/* Add the variable tg_relname */
			var = plpgsql_build_variable("tg_relname", 0,
										 plpgsql_build_datatype(NAMEOID,
																-1,
																function->fn_input_collation,
																NULL),
										 true);
			Assert(var->dtype == PLPGSQL_DTYPE_VAR);
			var->dtype = PLPGSQL_DTYPE_PROMISE;
			((PLpgSQL_var *) var)->promise = PLPGSQL_PROMISE_TG_TABLE_NAME;

			/* tg_table_name is now preferred to tg_relname */
			var = plpgsql_build_variable("tg_table_name", 0,
										 plpgsql_build_datatype(NAMEOID,
																-1,
																function->fn_input_collation,
																NULL),
										 true);
			Assert(var->dtype == PLPGSQL_DTYPE_VAR);
			var->dtype = PLPGSQL_DTYPE_PROMISE;
			((PLpgSQL_var *) var)->promise = PLPGSQL_PROMISE_TG_TABLE_NAME;

			/* add the variable tg_table_schema */
			var = plpgsql_build_variable("tg_table_schema", 0,
										 plpgsql_build_datatype(NAMEOID,
																-1,
																function->fn_input_collation,
																NULL),
										 true);
			Assert(var->dtype == PLPGSQL_DTYPE_VAR);
			var->dtype = PLPGSQL_DTYPE_PROMISE;
			((PLpgSQL_var *) var)->promise = PLPGSQL_PROMISE_TG_TABLE_SCHEMA;

			/* Add the variable tg_nargs */
			var = plpgsql_build_variable("tg_nargs", 0,
										 plpgsql_build_datatype(INT4OID,
																-1,
																InvalidOid,
																NULL),
										 true);
			Assert(var->dtype == PLPGSQL_DTYPE_VAR);
			var->dtype = PLPGSQL_DTYPE_PROMISE;
			((PLpgSQL_var *) var)->promise = PLPGSQL_PROMISE_TG_NARGS;

			/* Add the variable tg_argv */
			var = plpgsql_build_variable("tg_argv", 0,
										 plpgsql_build_datatype(TEXTARRAYOID,
																-1,
																function->fn_input_collation,
																NULL),
										 true);
			Assert(var->dtype == PLPGSQL_DTYPE_VAR);
			var->dtype = PLPGSQL_DTYPE_PROMISE;
			((PLpgSQL_var *) var)->promise = PLPGSQL_PROMISE_TG_ARGV;

			break;

		case PLPGSQL_EVENT_TRIGGER:
			function->fn_rettype = VOIDOID;
			function->fn_retbyval = false;
			function->fn_retistuple = true;
			function->fn_retisdomain = false;
			function->fn_retset = false;

			/* shouldn't be any declared arguments */
			if (procStruct->pronargs != 0)
				ereport(ERROR,
						(errcode(ERRCODE_INVALID_FUNCTION_DEFINITION),
						 errmsg("event trigger functions cannot have declared arguments")));

			/* Add the variable tg_event */
			var = plpgsql_build_variable("tg_event", 0,
										 plpgsql_build_datatype(TEXTOID,
																-1,
																function->fn_input_collation,
																NULL),
										 true);
			Assert(var->dtype == PLPGSQL_DTYPE_VAR);
			var->dtype = PLPGSQL_DTYPE_PROMISE;
			((PLpgSQL_var *) var)->promise = PLPGSQL_PROMISE_TG_EVENT;

			/* Add the variable tg_tag */
			var = plpgsql_build_variable("tg_tag", 0,
										 plpgsql_build_datatype(TEXTOID,
																-1,
																function->fn_input_collation,
																NULL),
										 true);
			Assert(var->dtype == PLPGSQL_DTYPE_VAR);
			var->dtype = PLPGSQL_DTYPE_PROMISE;
			((PLpgSQL_var *) var)->promise = PLPGSQL_PROMISE_TG_TAG;

			break;

		default:
			elog(ERROR, "unrecognized function typecode: %d",
				 (int) function->fn_is_trigger);
			break;
	}
	/*foreach(lc, stmt->parameters)
	{
		FunctionParameter *param = lfirst_node(FunctionParameter, lc);
		char buf[32];
		PLpgSQL_type *argdtype;
		PLpgSQL_variable *argvariable;
		PLpgSQL_nsitem_type argitemtype;
		snprintf(buf, sizeof(buf), "$%d", foreach_current_index(lc) + 1);
		argdtype = plpgsql_build_datatype(UNKNOWNOID, -1, InvalidOid, param->argType);
		argvariable = plpgsql_build_variable(param->name ? param->name : buf, 0, argdtype, false);
		if (param->mode == FUNC_PARAM_OUT || param->mode == FUNC_PARAM_INOUT || param->mode == FUNC_PARAM_TABLE)
			function->out_param_varno = argvariable->dno;
		argitemtype = argvariable->dtype == PLPGSQL_DTYPE_VAR ? PLPGSQL_NSTYPE_VAR : PLPGSQL_NSTYPE_REC;
		plpgsql_ns_additem(argitemtype, argvariable->dno, buf);
		if (param->name != NULL)
			plpgsql_ns_additem(argitemtype, argvariable->dno, param->name);
	}*/

	/* Remember if function is STABLE/IMMUTABLE */
	function->fn_readonly = (procStruct->provolatile != PROVOLATILE_VOLATILE);

	/*
	 * Create the magic FOUND variable.
	 */
	var = plpgsql_build_variable("found", 0,
								 plpgsql_build_datatype(BOOLOID,
														-1,
														InvalidOid,
														NULL),
								 true);
	function->found_varno = var->dno;

	/*
	 * Now parse the function's text
	 */
	parse_rc = plpgsql_yyparse(&function->action, scanner);
	if (parse_rc != 0)
		elog(ERROR, "plpgsql parser returned %d", parse_rc);

	plpgsql_scanner_finish(scanner);
	pfree(proc_source);

	/*
	 * If it has OUT parameters or returns VOID or returns a set, we allow
	 * control to fall off the end without an explicit RETURN statement. The
	 * easiest way to implement this is to add a RETURN statement to the end
	 * of the statement list during parsing.
	 */
	if (num_out_args > 0 || function->fn_rettype == VOIDOID ||
		function->fn_retset)
		add_dummy_return(function);

	/*
	 * Complete the function's info
	 */
	function->fn_nargs = procStruct->pronargs;
	for (i = 0; i < function->fn_nargs; i++)
		function->fn_argvarnos[i] = in_arg_varnos[i];

	plpgsql_finish_datums(function);

	if (function->has_exception_block)
		plpgsql_mark_local_assignment_targets(function);

	/* Debug dump for completed functions */
	//if (plpgsql_DumpExecTree)
	//	plpgsql_dumptree(function);

	/*
	 * Pop the error context stack
	 */
	error_context_stack = plerrcontext.previous;
	plpgsql_error_funcname = NULL;

	plpgsql_check_syntax = false;

	MemoryContextSwitchTo(plpgsql_compile_tmp_cxt);
	plpgsql_compile_tmp_cxt = NULL;
	return function;
}

PgQueryInternalPlpgsqlFuncAndError pg_query_raw_parse_plpgsql(Node* stmt)
{
	PgQueryInternalPlpgsqlFuncAndError result = {0};
	MemoryContext cctx = CurrentMemoryContext;

	char stderr_buffer[STDERR_BUFFER_LEN + 1] = {0};
#ifndef DEBUG
	int stderr_global;
	int stderr_pipe[2];
#endif

#ifndef DEBUG
	// Setup pipe for stderr redirection
	if (pipe(stderr_pipe) != 0) {
		PgQueryError* error = malloc(sizeof(PgQueryError));

		error->message = strdup("Failed to open pipe, too many open file descriptors")

		result.error = error;

		return result;
	}

	fcntl(stderr_pipe[0], F_SETFL, fcntl(stderr_pipe[0], F_GETFL) | O_NONBLOCK);

	// Redirect stderr to the pipe
	stderr_global = dup(STDERR_FILENO);
	dup2(stderr_pipe[1], STDERR_FILENO);
	close(stderr_pipe[1]);
#endif

	PG_TRY();
	{
		if (IsA(stmt, CreateFunctionStmt)) {
			result.func = compile_create_function_stmt((CreateFunctionStmt *) stmt);
		} else if (IsA(stmt, DoStmt)){
			result.func = compile_do_stmt((DoStmt *) stmt);
		} else {
			elog(ERROR, "Unexpected node type for PL/pgSQL parsing: %d", nodeTag(stmt));
		}

#ifndef DEBUG
		// Save stderr for result
		read(stderr_pipe[0], stderr_buffer, STDERR_BUFFER_LEN);
#endif

		if (strlen(stderr_buffer) > 0) {
			PgQueryError* error = malloc(sizeof(PgQueryError));
			error->message = strdup(stderr_buffer);
			error->filename = "";
			error->funcname = "";
			error->context  = "";
			result.error = error;
		}
	}
	PG_CATCH();
	{
		ErrorData* error_data;
		PgQueryError* error;

		MemoryContextSwitchTo(cctx);
		error_data = CopyErrorData();

		// Note: This is intentionally malloc so exiting the memory context doesn't free this
		error = malloc(sizeof(PgQueryError));
		error->message   = strdup(error_data->message);
		error->filename  = strdup(error_data->filename);
		error->funcname  = strdup(error_data->funcname);
		error->context   = error_data->context ? strdup(error_data->context) : NULL;
		error->lineno    = error_data->lineno;
		error->cursorpos = error_data->cursorpos;

		result.error = error;
		FlushErrorState();
	}
	PG_END_TRY();

#ifndef DEBUG
	// Restore stderr, close pipe
	dup2(stderr_global, STDERR_FILENO);
	close(stderr_pipe[0]);
	close(stderr_global);
#endif

	return result;
}

typedef struct plStmts
{
	Node **stmts;
	int stmts_buf_size;
	int stmts_count;
} plStmts;

static bool stmts_walker(Node *node, plStmts *state)
{
	bool result;
	MemoryContext ccxt = CurrentMemoryContext;

	if (node == NULL) return false;

	if (IsA(node, CreateFunctionStmt) || IsA(node, DoStmt))
	{
		if (state->stmts_count >= state->stmts_buf_size)
		{
			state->stmts_buf_size *= 2;
			state->stmts = (Node**) repalloc(state->stmts, state->stmts_buf_size * sizeof(Node*));
		}
		state->stmts[state->stmts_count] = (Node *) node;
		state->stmts_count++;
	} else if (IsA(node, RawStmt)) {
		return stmts_walker((Node *) ((RawStmt *) node)->stmt, state);
	}

	PG_TRY();
	{
		result = raw_expression_tree_walker(node, stmts_walker, (void*) state);
	}
	PG_CATCH();
	{
		MemoryContextSwitchTo(ccxt);
		FlushErrorState();
		result = false;
	}
	PG_END_TRY();

	return result;
}

PgQueryPlpgsqlParseResult pg_query_parse_plpgsql(const char* input)
{
	MemoryContext ctx = NULL;
	PgQueryPlpgsqlParseResult result = {0};
	PgQueryInternalParsetreeAndError parse_result;
	plStmts statements;
	size_t i;

	ctx = pg_query_enter_memory_context();

	parse_result = pg_query_raw_parse(input, PG_QUERY_PARSE_DEFAULT);
	result.error = parse_result.error;
	if (result.error != NULL) {
		pg_query_exit_memory_context(ctx);
		return result;
	}

	statements.stmts_buf_size = 100;
	statements.stmts = (Node**) palloc(statements.stmts_buf_size * sizeof(Node*));
	statements.stmts_count = 0;

	stmts_walker((Node*) parse_result.tree, &statements);

	if (statements.stmts_count == 0) {
		result.plpgsql_funcs = strdup("[]");
		pg_query_exit_memory_context(ctx);
		return result;
	}

	result.plpgsql_funcs = strdup("[\n");

	for (i = 0; i < statements.stmts_count; i++) {
		PgQueryInternalPlpgsqlFuncAndError func_and_error;

		func_and_error = pg_query_raw_parse_plpgsql(statements.stmts[i]);

		// These are all malloc-ed and will survive exiting the memory context, the caller is responsible to free them now
		result.error = func_and_error.error;

		if (result.error != NULL) {
			pg_query_exit_memory_context(ctx);
			return result;
		}

		if (func_and_error.func != NULL) {
			char *func_json;
			char *new_out;
			size_t new_out_len;

			func_json = plpgsqlToJSON(func_and_error.func);
			plpgsql_free_function_memory(func_and_error.func);

			new_out_len = strlen(result.plpgsql_funcs) + strlen(func_json) + 3;
			new_out = malloc(new_out_len);
			int n = snprintf(new_out, new_out_len, "%s%s,\n", result.plpgsql_funcs, func_json);
			if (n < 0 || n >= new_out_len) {
				PgQueryError* error = malloc(sizeof(PgQueryError));
				error->message = strdup("Failed to output PL/pgSQL functions due to snprintf failure");
				result.error = error;
			} else {
				free(result.plpgsql_funcs);
				result.plpgsql_funcs = new_out;
			}

			pfree(func_json);
		}
	}

	result.plpgsql_funcs[strlen(result.plpgsql_funcs) - 2] = '\n';
	result.plpgsql_funcs[strlen(result.plpgsql_funcs) - 1] = ']';

	free(parse_result.stderr_buffer);
	pg_query_exit_memory_context(ctx);

	return result;
}

void pg_query_free_plpgsql_parse_result(PgQueryPlpgsqlParseResult result)
{
	if (result.error) {
		pg_query_free_error(result.error);
	}

	free(result.plpgsql_funcs);
}
