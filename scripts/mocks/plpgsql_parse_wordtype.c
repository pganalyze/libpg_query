PLpgSQL_type *
plpgsql_parse_wordtype(char *ident)
{
	PLpgSQL_type *typ;

	typ = (PLpgSQL_type *) palloc0(sizeof(PLpgSQL_type));
	typ->typname = psprintf("%s%%TYPE", ident);
	typ->ttype = PLPGSQL_TTYPE_SCALAR;
	return typ;
}
