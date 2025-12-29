void
interpret_function_parameter_list(ParseState *pstate,
								  List *parameters,
								  Oid languageOid,
								  ObjectType objtype,
								  oidvector **parameterTypes,
								  List **parameterTypes_list,
								  ArrayType **allParameterTypes,
								  ArrayType **parameterModes,
								  ArrayType **parameterNames,
								  List **inParameterNames_list,
								  List **parameterDefaults,
								  Oid *variadicArgType,
								  Oid *requiredResultType)
{
	int			parameterCount = list_length(parameters);
	Oid		   *inTypes;
	int			inCount = 0;
	Datum	   *allTypes;
	Datum	   *paramModes;
	Datum	   *paramNames;
	int			outCount = 0;
	int			varCount = 0;
	bool		have_names = false;
	bool		have_defaults = false;
	ListCell   *x;
	int			i;

	*variadicArgType = InvalidOid;	/* default result */
	*requiredResultType = InvalidOid;	/* default result */

	inTypes = (Oid *) palloc(parameterCount * sizeof(Oid));
	allTypes = (Datum *) palloc(parameterCount * sizeof(Datum));
	paramModes = (Datum *) palloc(parameterCount * sizeof(Datum));
	paramNames = (Datum *) palloc0(parameterCount * sizeof(Datum));
	*parameterDefaults = NIL;

	/* Scan the list and extract data into work arrays */
	i = 0;
	foreach(x, parameters)
	{
		FunctionParameter *fp = (FunctionParameter *) lfirst(x);
		TypeName   *t = fp->argType;
		FunctionParameterMode fpmode = fp->mode;
		bool		isinput = false;
		Oid			toid;
		Type		typtup;
		AclResult	aclresult;

		/* For our purposes here, a defaulted mode spec is identical to IN */
		if (fpmode == FUNC_PARAM_DEFAULT)
			fpmode = FUNC_PARAM_IN;

		typtup = LookupTypeName(pstate, t, NULL, false);
		if (typtup)
		{
			if (!((Form_pg_type) GETSTRUCT(typtup))->typisdefined)
			{
				/* As above, hard error if language is SQL */
				if (languageOid == SQLlanguageId)
					ereport(ERROR,
							(errcode(ERRCODE_INVALID_FUNCTION_DEFINITION),
							 errmsg("SQL function cannot accept shell type %s",
									TypeNameToString(t)),
							 parser_errposition(pstate, t->location)));
				/* We don't allow creating aggregates on shell types either */
				else if (objtype == OBJECT_AGGREGATE)
					ereport(ERROR,
							(errcode(ERRCODE_INVALID_FUNCTION_DEFINITION),
							 errmsg("aggregate cannot accept shell type %s",
									TypeNameToString(t)),
							 parser_errposition(pstate, t->location)));
				else
					ereport(NOTICE,
							(errcode(ERRCODE_WRONG_OBJECT_TYPE),
							 errmsg("argument type %s is only a shell",
									TypeNameToString(t)),
							 parser_errposition(pstate, t->location)));
			}
			toid = typeTypeId(typtup);
			ReleaseSysCache(typtup);
		}
		else
		{
			ereport(ERROR,
					(errcode(ERRCODE_UNDEFINED_OBJECT),
					 errmsg("type %s does not exist",
							TypeNameToString(t)),
					 parser_errposition(pstate, t->location)));
			toid = InvalidOid;	/* keep compiler quiet */
		}

        // CHANGED: Skip ACL check to reduce dependencies
		//aclresult = object_aclcheck(TypeRelationId, toid, GetUserId(), ACL_USAGE);
		//if (aclresult != ACLCHECK_OK)
		//	aclcheck_error_type(aclresult, toid);

		if (t->setof)
		{
			if (objtype == OBJECT_AGGREGATE)
				ereport(ERROR,
						(errcode(ERRCODE_INVALID_FUNCTION_DEFINITION),
						 errmsg("aggregates cannot accept set arguments"),
						 parser_errposition(pstate, fp->location)));
			else if (objtype == OBJECT_PROCEDURE)
				ereport(ERROR,
						(errcode(ERRCODE_INVALID_FUNCTION_DEFINITION),
						 errmsg("procedures cannot accept set arguments"),
						 parser_errposition(pstate, fp->location)));
			else
				ereport(ERROR,
						(errcode(ERRCODE_INVALID_FUNCTION_DEFINITION),
						 errmsg("functions cannot accept set arguments"),
						 parser_errposition(pstate, fp->location)));
		}

		/* handle input parameters */
		if (fpmode != FUNC_PARAM_OUT && fpmode != FUNC_PARAM_TABLE)
		{
			/* other input parameters can't follow a VARIADIC parameter */
			if (varCount > 0)
				ereport(ERROR,
						(errcode(ERRCODE_INVALID_FUNCTION_DEFINITION),
						 errmsg("VARIADIC parameter must be the last input parameter"),
						 parser_errposition(pstate, fp->location)));
			inTypes[inCount++] = toid;
			isinput = true;
			if (parameterTypes_list)
				*parameterTypes_list = lappend_oid(*parameterTypes_list, toid);
		}

		/* handle output parameters */
		if (fpmode != FUNC_PARAM_IN && fpmode != FUNC_PARAM_VARIADIC)
		{
			if (objtype == OBJECT_PROCEDURE)
			{
				/*
				 * We disallow OUT-after-VARIADIC only for procedures.  While
				 * such a case causes no confusion in ordinary function calls,
				 * it would cause confusion in a CALL statement.
				 */
				if (varCount > 0)
					ereport(ERROR,
							(errcode(ERRCODE_INVALID_FUNCTION_DEFINITION),
							 errmsg("VARIADIC parameter must be the last parameter"),
							 parser_errposition(pstate, fp->location)));
				/* Procedures with output parameters always return RECORD */
				*requiredResultType = RECORDOID;
			}
			else if (outCount == 0) /* save first output param's type */
				*requiredResultType = toid;
			outCount++;
		}

		if (fpmode == FUNC_PARAM_VARIADIC)
		{
			*variadicArgType = toid;
			varCount++;
			/* validate variadic parameter type */
			switch (toid)
			{
				case ANYARRAYOID:
				case ANYCOMPATIBLEARRAYOID:
				case ANYOID:
					/* okay */
					break;
				default:
					if (!OidIsValid(get_element_type(toid)))
						ereport(ERROR,
								(errcode(ERRCODE_INVALID_FUNCTION_DEFINITION),
								 errmsg("VARIADIC parameter must be an array"),
								 parser_errposition(pstate, fp->location)));
					break;
			}
		}

		allTypes[i] = ObjectIdGetDatum(toid);

		paramModes[i] = CharGetDatum(fpmode);

		if (fp->name && fp->name[0])
		{
			ListCell   *px;

			/*
			 * As of Postgres 9.0 we disallow using the same name for two
			 * input or two output function parameters.  Depending on the
			 * function's language, conflicting input and output names might
			 * be bad too, but we leave it to the PL to complain if so.
			 */
			foreach(px, parameters)
			{
				FunctionParameter *prevfp = (FunctionParameter *) lfirst(px);
				FunctionParameterMode prevfpmode;

				if (prevfp == fp)
					break;
				/* as above, default mode is IN */
				prevfpmode = prevfp->mode;
				if (prevfpmode == FUNC_PARAM_DEFAULT)
					prevfpmode = FUNC_PARAM_IN;
				/* pure in doesn't conflict with pure out */
				if ((fpmode == FUNC_PARAM_IN ||
					 fpmode == FUNC_PARAM_VARIADIC) &&
					(prevfpmode == FUNC_PARAM_OUT ||
					 prevfpmode == FUNC_PARAM_TABLE))
					continue;
				if ((prevfpmode == FUNC_PARAM_IN ||
					 prevfpmode == FUNC_PARAM_VARIADIC) &&
					(fpmode == FUNC_PARAM_OUT ||
					 fpmode == FUNC_PARAM_TABLE))
					continue;
				if (prevfp->name && prevfp->name[0] &&
					strcmp(prevfp->name, fp->name) == 0)
					ereport(ERROR,
							(errcode(ERRCODE_INVALID_FUNCTION_DEFINITION),
							 errmsg("parameter name \"%s\" used more than once",
									fp->name),
							 parser_errposition(pstate, fp->location)));
			}

			paramNames[i] = CStringGetTextDatum(fp->name);
			have_names = true;
		}

		if (inParameterNames_list)
			*inParameterNames_list = lappend(*inParameterNames_list, makeString(fp->name ? fp->name : pstrdup("")));

		if (fp->defexpr)
		{
			Node	   *def;

			if (!isinput)
				ereport(ERROR,
						(errcode(ERRCODE_INVALID_FUNCTION_DEFINITION),
						 errmsg("only input parameters can have default values"),
						 parser_errposition(pstate, fp->location)));

			def = transformExpr(pstate, fp->defexpr,
								EXPR_KIND_FUNCTION_DEFAULT);
			def = coerce_to_specific_type(pstate, def, toid, "DEFAULT");
			assign_expr_collations(pstate, def);

			/*
			 * Make sure no variables are referred to (this is probably dead
			 * code now that add_missing_from is history).
			 */
			if (pstate->p_rtable != NIL ||
				contain_var_clause(def))
				ereport(ERROR,
						(errcode(ERRCODE_INVALID_COLUMN_REFERENCE),
						 errmsg("cannot use table references in parameter default value"),
						 parser_errposition(pstate, fp->location)));

			/*
			 * transformExpr() should have already rejected subqueries,
			 * aggregates, and window functions, based on the EXPR_KIND_ for a
			 * default expression.
			 *
			 * It can't return a set either --- but coerce_to_specific_type
			 * already checked that for us.
			 *
			 * Note: the point of these restrictions is to ensure that an
			 * expression that, on its face, hasn't got subplans, aggregates,
			 * etc cannot suddenly have them after function default arguments
			 * are inserted.
			 */

			*parameterDefaults = lappend(*parameterDefaults, def);
			have_defaults = true;
		}
		else
		{
			if (isinput && have_defaults)
				ereport(ERROR,
						(errcode(ERRCODE_INVALID_FUNCTION_DEFINITION),
						 errmsg("input parameters after one with a default value must also have defaults"),
						 parser_errposition(pstate, fp->location)));

			/*
			 * For procedures, we also can't allow OUT parameters after one
			 * with a default, because the same sort of confusion arises in a
			 * CALL statement.
			 */
			if (objtype == OBJECT_PROCEDURE && have_defaults)
				ereport(ERROR,
						(errcode(ERRCODE_INVALID_FUNCTION_DEFINITION),
						 errmsg("procedure OUT parameters cannot appear after one with a default value"),
						 parser_errposition(pstate, fp->location)));
		}

		i++;
	}

	/* Now construct the proper outputs as needed */
	*parameterTypes = buildoidvector(inTypes, inCount);

	if (outCount > 0 || varCount > 0)
	{
		*allParameterTypes = construct_array_builtin(allTypes, parameterCount, OIDOID);
		*parameterModes = construct_array_builtin(paramModes, parameterCount, CHAROID);
		if (outCount > 1)
			*requiredResultType = RECORDOID;
		/* otherwise we set requiredResultType correctly above */
	}
	else
	{
		*allParameterTypes = NULL;
		*parameterModes = NULL;
	}

	if (have_names)
	{
		for (i = 0; i < parameterCount; i++)
		{
			if (paramNames[i] == PointerGetDatum(NULL))
				paramNames[i] = CStringGetTextDatum("");
		}
		*parameterNames = construct_array_builtin(paramNames, parameterCount, TEXTOID);
	}
	else
		*parameterNames = NULL;
}