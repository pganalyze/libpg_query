PLpgSQL_type *
plpgsql_parse_cwordrowtype(List *idents)
{
	PLpgSQL_type *typ;

	typ = (PLpgSQL_type *) palloc0(sizeof(PLpgSQL_type));
	typ->typname = psprintf("%s%%rowtype", NameListToString(idents));
	typ->ttype = PLPGSQL_TTYPE_SCALAR;
	return typ;
}
