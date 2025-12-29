Type
LookupTypeNameExtended(ParseState *pstate,
					   const TypeName *typeName, int32 *typmod_p,
					   bool temp_ok, bool missing_ok)
{
	Oid			typoid;
	HeapTuple	tup;
	int32		typmod;

	if (typeName->names == NIL)
	{
		/* We have the OID already if it's an internally generated TypeName */
		typoid = typeName->typeOid;
	}
	else if (typeName->pct_type)
	{
        // CHANGED: Not currently implemented, requires us to get type mappings from caller
        elog(ERROR, "Not implemented");
		/* Handle %TYPE reference to type of an existing field */
		//RangeVar   *rel = makeRangeVar(NULL, NULL, typeName->location);
		//char	   *field = NULL;
		//Oid			relid;
		//AttrNumber	attnum;

		/* deconstruct the name list */
		//switch (list_length(typeName->names))
		//{
		//	case 1:
		//		ereport(ERROR,
		//				(errcode(ERRCODE_SYNTAX_ERROR),
		//				 errmsg("improper %%TYPE reference (too few dotted names): %s",
		//						NameListToString(typeName->names)),
		//				 parser_errposition(pstate, typeName->location)));
		//		break;
		//	case 2:
		//		rel->relname = strVal(linitial(typeName->names));
		//		field = strVal(lsecond(typeName->names));
		//		break;
		//	case 3:
		//		rel->schemaname = strVal(linitial(typeName->names));
		//		rel->relname = strVal(lsecond(typeName->names));
		//		field = strVal(lthird(typeName->names));
		//		break;
		//	case 4:
		//		rel->catalogname = strVal(linitial(typeName->names));
		//		rel->schemaname = strVal(lsecond(typeName->names));
		//		rel->relname = strVal(lthird(typeName->names));
		//		field = strVal(lfourth(typeName->names));
		//		break;
		//	default:
		//		ereport(ERROR,
		//				(errcode(ERRCODE_SYNTAX_ERROR),
		//				 errmsg("improper %%TYPE reference (too many dotted names): %s",
		//						NameListToString(typeName->names)),
		//				 parser_errposition(pstate, typeName->location)));
		//		break;
		//}

		/*
		 * Look up the field.
		 *
		 * XXX: As no lock is taken here, this might fail in the presence of
		 * concurrent DDL.  But taking a lock would carry a performance
		 * penalty and would also require a permissions check.
		 */
		//relid = RangeVarGetRelid(rel, NoLock, missing_ok);
		//attnum = get_attnum(relid, field);
		//if (attnum == InvalidAttrNumber)
		//{
		//	if (missing_ok)
		//		typoid = InvalidOid;
		//	else
		//		ereport(ERROR,
		//				(errcode(ERRCODE_UNDEFINED_COLUMN),
		//				 errmsg("column \"%s\" of relation \"%s\" does not exist",
		//						field, rel->relname),
		//				 parser_errposition(pstate, typeName->location)));
		//}
		//else
		//{
		//	typoid = get_atttype(relid, attnum);
        //
		//	/* this construct should never have an array indicator */
		//	Assert(typeName->arrayBounds == NIL);
        //
		//	/* emit nuisance notice (intentionally not errposition'd) */
		//	ereport(NOTICE,
		//			(errmsg("type reference %s converted to %s",
		//					TypeNameToString(typeName),
		//					format_type_be(typoid))));
		//}
	}
	else
	{
		/* Normal reference to a type name */
		char	   *schemaname;
		char	   *typname;

		/* deconstruct the name list */
		DeconstructQualifiedName(typeName->names, &schemaname, &typname);

		if (schemaname)
		{
			/* Look in specific schema only */
			Oid			namespaceId;
			ParseCallbackState pcbstate;

			setup_parser_errposition_callback(&pcbstate, pstate, typeName->location);

			namespaceId = LookupExplicitNamespace(schemaname, missing_ok);
			if (OidIsValid(namespaceId))
				typoid = GetSysCacheOid2(TYPENAMENSP, Anum_pg_type_oid,
										 PointerGetDatum(typname),
										 ObjectIdGetDatum(namespaceId));
			else
				typoid = InvalidOid;

			cancel_parser_errposition_callback(&pcbstate);
		}
		else
		{
			/* Unqualified type name, so search the search path */
			typoid = TypenameGetTypidExtended(typname, temp_ok);
		}

		/* If an array reference, return the array type instead */
		if (typeName->arrayBounds != NIL)
			typoid = get_array_type(typoid);
	}

	if (!OidIsValid(typoid))
	{
		if (typmod_p)
			*typmod_p = -1;
		return NULL;
	}

	tup = SearchSysCache1(TYPEOID, ObjectIdGetDatum(typoid));
	if (!HeapTupleIsValid(tup)) /* should not happen */
		elog(ERROR, "cache lookup failed for type %u", typoid);

	typmod = typenameTypeMod(pstate, typeName, (Type) tup);

	if (typmod_p)
		*typmod_p = typmod;

	return (Type) tup;
}