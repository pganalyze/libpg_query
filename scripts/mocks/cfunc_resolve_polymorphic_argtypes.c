/*
 * libpg_query never has a real fn_expr to consult, and only invokes the
 * plpgsql compile path in validator mode. Implement the validator branch
 * of upstream's cfunc_resolve_polymorphic_argtypes (mapping polymorphic
 * types to INT4OID family) and bail out for anything else.
 */
void
cfunc_resolve_polymorphic_argtypes(int numargs, Oid *argtypes, char *argmodes,
								   Node *call_expr, bool forValidator,
								   const char *proname)
{
	int			i;

	if (!forValidator)
		elog(ERROR, "Not implemented (cfunc_resolve_polymorphic_argtypes outside validator mode)");

	for (i = 0; i < numargs; i++)
	{
		switch (argtypes[i])
		{
			case ANYELEMENTOID:
			case ANYNONARRAYOID:
			case ANYENUMOID:
			case ANYCOMPATIBLEOID:
			case ANYCOMPATIBLENONARRAYOID:
				argtypes[i] = INT4OID;
				break;
			case ANYARRAYOID:
			case ANYCOMPATIBLEARRAYOID:
				argtypes[i] = INT4ARRAYOID;
				break;
			case ANYRANGEOID:
			case ANYCOMPATIBLERANGEOID:
				argtypes[i] = INT4RANGEOID;
				break;
			case ANYMULTIRANGEOID:
				argtypes[i] = INT4MULTIRANGEOID;
				break;
			default:
				break;
		}
	}
}
