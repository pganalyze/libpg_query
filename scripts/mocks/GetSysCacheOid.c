Oid
GetSysCacheOid(int cacheId,
			   AttrNumber oidcol,
			   Datum key1,
			   Datum key2,
			   Datum key3,
			   Datum key4)
{
	if (cacheId != TYPENAMENSP)
        elog(ERROR, "Not implemented (GetSysCacheOid only supports TYPENAMENSP cache (%d), got cache %d)", TYPENAMENSP, cacheId);

    if (oidcol != Anum_pg_type_oid)
        elog(ERROR, "Not implemented (GetSysCacheOid oidcol not as expected)");

    if (key3 != 0 || key4 != 0)
        elog(ERROR, "Not implemented (GetSysCacheOid key 3 and key 4 must be zero)");

    if (IsCatalogNamespace(DatumGetObjectId(key2)))
    {
        return pg_query_builtin_type_oid_by_name(DatumGetPointer(key1));
    }
    else if (DatumGetObjectId(key2) == PG_PUBLIC_NAMESPACE)
    {
        return RECORDOID;
    }
    else
    {
        elog(ERROR, "Not implemented (GetSysCacheOid only supported for built-in catalog types or custom pseudotypes in public namespace)");
    }
}
