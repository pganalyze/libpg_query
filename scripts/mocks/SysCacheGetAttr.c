#include "pg_query_proctup_attrs.h"

/*
 * libpg_query only ever invokes SysCacheGetAttr from inside
 * plpgsql_compile_callback (transitively via get_func_arg_info), and the
 * tuple it sees is the libpg_query-forged pg_proc HeapTuple embedded in a
 * ProcTupWithAttrs wrapper. We recover the wrapper from the tuple pointer
 * and read the Anum-indexed value the caller asked for.
 */
Datum
SysCacheGetAttr(int cacheId, HeapTuple tup, AttrNumber attributeNumber, bool *isNull)
{
	ProcTupWithAttrs *w;

	if (cacheId != PROCOID)
		elog(ERROR, "Not implemented (SysCacheGetAttr only supports PROCOID, got cache %d)", cacheId);

	if (attributeNumber < 1 || attributeNumber > Natts_pg_proc)
		elog(ERROR, "SysCacheGetAttr: invalid pg_proc attribute number %d", attributeNumber);

	w = (ProcTupWithAttrs *) ((char *) tup - offsetof(ProcTupWithAttrs, tup));

	*isNull = w->nulls[attributeNumber - 1];
	return w->values[attributeNumber - 1];
}
