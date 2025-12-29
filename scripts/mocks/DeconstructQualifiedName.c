void
DeconstructQualifiedName(const List *names,
						 char **nspname_p,
						 char **objname_p)
{
	// CHANGED: catalogname not needed
	//char	   *catalogname;
	char	   *schemaname = NULL;
	char	   *objname = NULL;

	switch (list_length(names))
	{
		case 1:
			objname = strVal(linitial(names));
			break;
		case 2:
			schemaname = strVal(linitial(names));
			objname = strVal(lsecond(names));
			break;
		case 3:
			//catalogname = strVal(linitial(names));
			schemaname = strVal(lsecond(names));
			objname = strVal(lthird(names));

			/*
			 * We check the catalog name and then ignore it.
			 */
            // CHANGED: Ignore without checking to avoid dependency
			/*if (strcmp(catalogname, get_database_name(MyDatabaseId)) != 0)
				ereport(ERROR,
						(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
						 errmsg("cross-database references are not implemented: %s",
								NameListToString(names))));*/
			break;
		default:
			ereport(ERROR,
					(errcode(ERRCODE_SYNTAX_ERROR),
					 errmsg("improper qualified name (too many dotted names): %s",
							NameListToString(names))));
			break;
	}

	*nspname_p = schemaname;
	*objname_p = objname;
}