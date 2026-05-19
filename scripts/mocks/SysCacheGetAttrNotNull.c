/*
 * Thin wrapper over the libpg_query SysCacheGetAttr mock: assert the value
 * isn't NULL and return its Datum.
 */
Datum
SysCacheGetAttrNotNull(int cacheId, HeapTuple tup, AttrNumber attributeNumber)
{
	bool		isNull;
	Datum		d = SysCacheGetAttr(cacheId, tup, attributeNumber, &isNull);

	if (isNull)
		elog(ERROR, "unexpected null attribute %d from pg_proc tuple", attributeNumber);
	return d;
}
