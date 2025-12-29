Oid
LookupExplicitNamespace(const char *nspname, bool missing_ok)
{
	Oid			namespaceId;
	AclResult	aclresult;

	/* check for pg_temp alias */
	if (strcmp(nspname, "pg_temp") == 0)
	{
		if (OidIsValid(myTempNamespace))
			return myTempNamespace;

		/*
		 * Since this is used only for looking up existing objects, there is
		 * no point in trying to initialize the temp namespace here; and doing
		 * so might create problems for some callers --- just fall through.
		 */
	}

    if (strcmp(nspname, "pg_catalog") == 0)
        return PG_CATALOG_NAMESPACE;

    if (strcmp(nspname, "public") == 0)
        return PG_PUBLIC_NAMESPACE;

    elog(ERROR, "Not implemented (LookupExplicitNamespace only supports pg_catalog)");
}
