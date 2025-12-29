#include <catalog/pg_type.h>
#include <catalog/pg_collation_d.h>
#include "pg_query_pg_type.c"

HeapTuple
SearchSysCache1(int cacheId,
				Datum key1)
{
	/*Assert(cacheId >= 0 && cacheId < SysCacheSize &&
		   PointerIsValid(SysCache[cacheId]));
	Assert(SysCache[cacheId]->cc_nkeys == 1);

	return SearchCatCache1(SysCache[cacheId], key1);*/

	HeapTuple tuple;
	HeapTupleHeader td;
	Form_pg_type t = palloc0(sizeof(FormData_pg_type));
	const PgQueryBuiltinType *bt;
	Size		len,
				data_len;
	int			hoff;

    if (cacheId != TYPEOID)
        elog(ERROR, "Not implemented (SearchSysCache1 only supports TYPEOID cache (%d), got cache %d)", TYPEOID, cacheId);

    bt = pg_query_builtin_type_by_oid(DatumGetObjectId(key1));
    if (bt == NULL)
        elog(ERROR, "Not implemented (SearchSysCache1 got TYPEOID cache request for type OID %d)", DatumGetObjectId(key1));

    strlcpy(NameStr(t->typname), bt->typname, NAMEDATALEN);
    t->typlen = bt->typlen;
    t->typbyval = bt->typbyval;
    t->typtype = bt->typtype;
    t->typcategory = bt->typcategory;
    t->typalign = bt->typalign;
    t->typarray = bt->typarray;
    t->typcollation = bt->typcollation;

    t->oid = DatumGetObjectId(key1);
    t->typisdefined = true;

	// The following logic is copied from heap_form_tuple, but pretends there are no nulls, and copies t_data directly

	/*
	 * Determine total space needed
	 */
	len = offsetof(HeapTupleHeaderData, t_bits);

	//if (hasnull)
	//	len += BITMAPLEN(numberOfAttributes);

	hoff = len = MAXALIGN(len); /* align user data safely */

	//data_len = heap_compute_data_size(tupleDescriptor, values, isnull);
	data_len = MAXALIGN(sizeof(FormData_pg_type));

	len += data_len;

	/*
	 * Allocate and zero the space needed.  Note that the tuple body and
	 * HeapTupleData management structure are allocated in one chunk.
	 */
	tuple = (HeapTuple) palloc0(HEAPTUPLESIZE + len);
	tuple->t_data = td = (HeapTupleHeader) ((char *) tuple + HEAPTUPLESIZE);

	/*
	 * And fill in the information.  Note we fill the Datum fields even though
	 * this tuple may never become a Datum.  This lets HeapTupleHeaderGetDatum
	 * identify the tuple type if needed.
	 */
	tuple->t_len = len;
	ItemPointerSetInvalid(&(tuple->t_self));
	tuple->t_tableOid = InvalidOid;

	HeapTupleHeaderSetDatumLength(td, len);
	//HeapTupleHeaderSetTypeId(td, tupleDescriptor->tdtypeid);
	//HeapTupleHeaderSetTypMod(td, tupleDescriptor->tdtypmod);
	/* We also make sure that t_ctid is invalid unless explicitly set */
	ItemPointerSetInvalid(&(td->t_ctid));

	HeapTupleHeaderSetNatts(td, Natts_pg_type);
	td->t_hoff = hoff;

	/*heap_fill_tuple(tupleDescriptor,
					values,
					isnull,
					(char *) td + hoff,
					data_len,
					&td->t_infomask,
					(hasnull ? td->t_bits : NULL));*/
	memcpy((char *) td + hoff, t, sizeof(FormData_pg_type));

	return tuple;
}
