/*--------------------------------------------------------------------
 * Symbols referenced in this file:
 * - object_aclcheck
 * - aclcheck_error_type
 * - aclcheck_error
 *--------------------------------------------------------------------
 */

/*-------------------------------------------------------------------------
 *
 * aclchk.c
 *	  Routines to check access control permissions.
 *
 * Portions Copyright (c) 1996-2025, PostgreSQL Global Development Group
 * Portions Copyright (c) 1994, Regents of the University of California
 *
 *
 * IDENTIFICATION
 *	  src/backend/catalog/aclchk.c
 *
 * NOTES
 *	  See acl.h.
 *
 *	  The xxx_aclmask() functions in this file are wrappers around
 *	  acl.c's aclmask() function; see that for basic usage information.
 *	  The wrapper functions add object-type-specific lookup capability.
 *	  Generally, they will throw error if the object doesn't exist.
 *
 *	  The xxx_aclmask_ext() functions add the ability to not throw
 *	  error if the object doesn't exist.  If their "is_missing" argument
 *	  isn't NULL, then when the object isn't found they will set
 *	  *is_missing = true and return zero (no privileges) instead of
 *	  throwing an error.  Caller must initialize *is_missing = false.
 *
 *	  The xxx_aclcheck() functions are simplified wrappers around the
 *	  corresponding xxx_aclmask() functions, simply returning ACLCHECK_OK
 *	  if any of the privileges specified in "mode" are held, and otherwise
 *	  a suitable error code (in practice, always ACLCHECK_NO_PRIV).
 *	  Again, they will throw error if the object doesn't exist.
 *
 *	  The xxx_aclcheck_ext() functions add the ability to not throw
 *	  error if the object doesn't exist.  Their "is_missing" argument
 *	  works similarly to the xxx_aclmask_ext() functions.
 *
 *-------------------------------------------------------------------------
 */
#include "postgres.h"

#include "access/genam.h"
#include "access/heapam.h"
#include "access/htup_details.h"
#include "access/sysattr.h"
#include "access/tableam.h"
#include "access/xact.h"
#include "catalog/binary_upgrade.h"
#include "catalog/catalog.h"
#include "catalog/dependency.h"
#include "catalog/indexing.h"
#include "catalog/objectaccess.h"
#include "catalog/pg_authid.h"
#include "catalog/pg_class.h"
#include "catalog/pg_database.h"
#include "catalog/pg_default_acl.h"
#include "catalog/pg_foreign_data_wrapper.h"
#include "catalog/pg_foreign_server.h"
#include "catalog/pg_init_privs.h"
#include "catalog/pg_language.h"
#include "catalog/pg_largeobject.h"
#include "catalog/pg_largeobject_metadata.h"
#include "catalog/pg_namespace.h"
#include "catalog/pg_parameter_acl.h"
#include "catalog/pg_proc.h"
#include "catalog/pg_tablespace.h"
#include "catalog/pg_type.h"
#include "commands/dbcommands.h"
#include "commands/defrem.h"
#include "commands/event_trigger.h"
#include "commands/extension.h"
#include "commands/proclang.h"
#include "commands/tablespace.h"
#include "foreign/foreign.h"
#include "miscadmin.h"
#include "nodes/makefuncs.h"
#include "parser/parse_func.h"
#include "parser/parse_type.h"
#include "storage/lmgr.h"
#include "utils/acl.h"
#include "utils/aclchk_internal.h"
#include "utils/builtins.h"
#include "utils/fmgroids.h"
#include "utils/guc.h"
#include "utils/lsyscache.h"
#include "utils/rel.h"
#include "utils/syscache.h"

/*
 * Internal format used by ALTER DEFAULT PRIVILEGES.
 */
typedef struct
{
	Oid			roleid;			/* owning role */
	Oid			nspid;			/* namespace, or InvalidOid if none */
	/* remaining fields are same as in InternalGrant: */
	bool		is_grant;
	ObjectType	objtype;
	bool		all_privs;
	AclMode		privileges;
	List	   *grantees;
	bool		grant_option;
	DropBehavior behavior;
} InternalDefaultACL;

/*
 * When performing a binary-upgrade, pg_dump will call a function to set
 * this variable to let us know that we need to populate the pg_init_privs
 * table for the GRANT/REVOKE commands while this variable is set to true.
 */


static void ExecGrantStmt_oids(InternalGrant *istmt);
static void ExecGrant_Relation(InternalGrant *istmt);
static void ExecGrant_common(InternalGrant *istmt, Oid classid, AclMode default_privs,
							 void (*object_check) (InternalGrant *istmt, HeapTuple tuple));
static void ExecGrant_Language_check(InternalGrant *istmt, HeapTuple tuple);
static void ExecGrant_Largeobject(InternalGrant *istmt);
static void ExecGrant_Type_check(InternalGrant *istmt, HeapTuple tuple);
static void ExecGrant_Parameter(InternalGrant *istmt);

static void SetDefaultACLsInSchemas(InternalDefaultACL *iacls, List *nspnames);
static void SetDefaultACL(InternalDefaultACL *iacls);

static List *objectNamesToOids(ObjectType objtype, List *objnames,
							   bool is_grant);
static List *objectsInSchemaToOids(ObjectType objtype, List *nspnames);
static List *getRelationsInNamespace(Oid namespaceId, char relkind);
static void expand_col_privileges(List *colnames, Oid table_oid,
								  AclMode this_privileges,
								  AclMode *col_privileges,
								  int num_col_privileges);
static void expand_all_col_privileges(Oid table_oid, Form_pg_class classForm,
									  AclMode this_privileges,
									  AclMode *col_privileges,
									  int num_col_privileges);
static AclMode string_to_privilege(const char *privname);
static const char *privilege_to_string(AclMode privilege);
static AclMode restrict_and_check_grant(bool is_grant, AclMode avail_goptions,
										bool all_privs, AclMode privileges,
										Oid objectId, Oid grantorId,
										ObjectType objtype, const char *objname,
										AttrNumber att_number, const char *colname);
static AclMode pg_aclmask(ObjectType objtype, Oid object_oid, AttrNumber attnum,
						  Oid roleid, AclMode mask, AclMaskHow how);
static AclMode object_aclmask(Oid classid, Oid objectid, Oid roleid,
							  AclMode mask, AclMaskHow how);
static AclMode object_aclmask_ext(Oid classid, Oid objectid, Oid roleid,
								  AclMode mask, AclMaskHow how,
								  bool *is_missing);
static AclMode pg_attribute_aclmask(Oid table_oid, AttrNumber attnum,
									Oid roleid, AclMode mask, AclMaskHow how);
static AclMode pg_attribute_aclmask_ext(Oid table_oid, AttrNumber attnum,
										Oid roleid, AclMode mask,
										AclMaskHow how, bool *is_missing);
static AclMode pg_class_aclmask_ext(Oid table_oid, Oid roleid,
									AclMode mask, AclMaskHow how,
									bool *is_missing);
static AclMode pg_parameter_acl_aclmask(Oid acl_oid, Oid roleid,
										AclMode mask, AclMaskHow how);
static AclMode pg_largeobject_aclmask_snapshot(Oid lobj_oid, Oid roleid,
											   AclMode mask, AclMaskHow how, Snapshot snapshot);
static AclMode pg_namespace_aclmask_ext(Oid nsp_oid, Oid roleid,
										AclMode mask, AclMaskHow how,
										bool *is_missing);
static AclMode pg_type_aclmask_ext(Oid type_oid, Oid roleid,
								   AclMode mask, AclMaskHow how,
								   bool *is_missing);
static void recordExtensionInitPriv(Oid objoid, Oid classoid, int objsubid,
									Acl *new_acl);
static void recordExtensionInitPrivWorker(Oid objoid, Oid classoid, int objsubid,
										  Acl *new_acl);


/*
 * If is_grant is true, adds the given privileges for the list of
 * grantees to the existing old_acl.  If is_grant is false, the
 * privileges for the given grantees are removed from old_acl.
 *
 * NB: the original old_acl is pfree'd.
 */


/*
 * Restrict the privileges to what we can actually grant, and emit
 * the standards-mandated warning and error messages.
 */


/*
 * Called to execute the utility commands GRANT and REVOKE
 */


/*
 * ExecGrantStmt_oids
 *
 * Internal entry point for granting and revoking privileges.
 */


/*
 * objectNamesToOids
 *
 * Turn a list of object names of a given type into an Oid list.
 *
 * XXX This function intentionally takes only an AccessShareLock.  In the face
 * of concurrent DDL, we might easily latch onto an old version of an object,
 * causing the GRANT or REVOKE statement to fail.  But it does prevent the
 * object from disappearing altogether.  To do better, we would need to use a
 * self-exclusive lock, perhaps ShareUpdateExclusiveLock, here and before
 * *every* CatalogTupleUpdate() of a row that GRANT/REVOKE can affect.
 * Besides that additional work, this could have operational costs.  For
 * example, it would make GRANT ALL TABLES IN SCHEMA terminate every
 * autovacuum running in the schema and consume a shared lock table entry per
 * table in the schema.  The user-visible benefit of that additional work is
 * just changing "ERROR: tuple concurrently updated" to blocking.  That's not
 * nothing, but it might not outweigh autovacuum termination and lock table
 * consumption spikes.
 */


/*
 * objectsInSchemaToOids
 *
 * Find all objects of a given type in specified schemas, and make a list
 * of their Oids.  We check USAGE privilege on the schemas, but there is
 * no privilege checking on the individual objects here.
 */


/*
 * getRelationsInNamespace
 *
 * Return Oid list of relations in given namespace filtered by relation kind
 */



/*
 * ALTER DEFAULT PRIVILEGES statement
 */


/*
 * Process ALTER DEFAULT PRIVILEGES for a list of target schemas
 *
 * All fields of *iacls except nspid were filled already
 */



/*
 * Create or update a pg_default_acl entry
 */



/*
 * RemoveRoleFromObjectACL
 *
 * Used by shdepDropOwned to remove mentions of a role in ACLs.
 *
 * Notice that this doesn't accept an objsubid parameter, which is a bit bogus
 * since the pg_shdepend record that caused us to call it certainly had one.
 * If, for example, pg_shdepend records the existence of a permission on
 * mytable.mycol, this function will effectively issue a REVOKE ALL ON TABLE
 * mytable.  That gets the job done because (per SQL spec) such a REVOKE also
 * revokes per-column permissions.  We could not recreate a situation where
 * the role has table-level but not column-level permissions; but it's okay
 * (for now anyway) because this is only used when we're dropping the role
 * and so all its permissions everywhere must go away.  At worst it's a bit
 * inefficient if the role has column permissions on several columns of the
 * same table.
 */



/*
 * expand_col_privileges
 *
 * OR the specified privilege(s) into per-column array entries for each
 * specified attribute.  The per-column array is indexed starting at
 * FirstLowInvalidHeapAttributeNumber, up to relation's last attribute.
 */


/*
 * expand_all_col_privileges
 *
 * OR the specified privilege(s) into per-column array entries for each valid
 * attribute of a relation.  The per-column array is indexed starting at
 * FirstLowInvalidHeapAttributeNumber, up to relation's last attribute.
 */


/*
 *	This processes attributes, but expects to be called from
 *	ExecGrant_Relation, not directly from ExecuteGrantStmt.
 */


/*
 *	This processes both sequences and non-sequences.
 */

















/*
 * Standardized reporting of aclcheck permissions failures.
 *
 * Note: we do not double-quote the %s's below, because many callers
 * supply strings that might be already quoted.
 */
void
aclcheck_error(AclResult aclerr, ObjectType objtype,
			   const char *objectname)
{
	switch (aclerr)
	{
		case ACLCHECK_OK:
			/* no error, so return to caller */
			break;
		case ACLCHECK_NO_PRIV:
			{
				const char *msg = "???";

				switch (objtype)
				{
					case OBJECT_AGGREGATE:
						msg = gettext_noop("permission denied for aggregate %s");
						break;
					case OBJECT_COLLATION:
						msg = gettext_noop("permission denied for collation %s");
						break;
					case OBJECT_COLUMN:
						msg = gettext_noop("permission denied for column %s");
						break;
					case OBJECT_CONVERSION:
						msg = gettext_noop("permission denied for conversion %s");
						break;
					case OBJECT_DATABASE:
						msg = gettext_noop("permission denied for database %s");
						break;
					case OBJECT_DOMAIN:
						msg = gettext_noop("permission denied for domain %s");
						break;
					case OBJECT_EVENT_TRIGGER:
						msg = gettext_noop("permission denied for event trigger %s");
						break;
					case OBJECT_EXTENSION:
						msg = gettext_noop("permission denied for extension %s");
						break;
					case OBJECT_FDW:
						msg = gettext_noop("permission denied for foreign-data wrapper %s");
						break;
					case OBJECT_FOREIGN_SERVER:
						msg = gettext_noop("permission denied for foreign server %s");
						break;
					case OBJECT_FOREIGN_TABLE:
						msg = gettext_noop("permission denied for foreign table %s");
						break;
					case OBJECT_FUNCTION:
						msg = gettext_noop("permission denied for function %s");
						break;
					case OBJECT_INDEX:
						msg = gettext_noop("permission denied for index %s");
						break;
					case OBJECT_LANGUAGE:
						msg = gettext_noop("permission denied for language %s");
						break;
					case OBJECT_LARGEOBJECT:
						msg = gettext_noop("permission denied for large object %s");
						break;
					case OBJECT_MATVIEW:
						msg = gettext_noop("permission denied for materialized view %s");
						break;
					case OBJECT_OPCLASS:
						msg = gettext_noop("permission denied for operator class %s");
						break;
					case OBJECT_OPERATOR:
						msg = gettext_noop("permission denied for operator %s");
						break;
					case OBJECT_OPFAMILY:
						msg = gettext_noop("permission denied for operator family %s");
						break;
					case OBJECT_PARAMETER_ACL:
						msg = gettext_noop("permission denied for parameter %s");
						break;
					case OBJECT_POLICY:
						msg = gettext_noop("permission denied for policy %s");
						break;
					case OBJECT_PROCEDURE:
						msg = gettext_noop("permission denied for procedure %s");
						break;
					case OBJECT_PUBLICATION:
						msg = gettext_noop("permission denied for publication %s");
						break;
					case OBJECT_ROUTINE:
						msg = gettext_noop("permission denied for routine %s");
						break;
					case OBJECT_SCHEMA:
						msg = gettext_noop("permission denied for schema %s");
						break;
					case OBJECT_SEQUENCE:
						msg = gettext_noop("permission denied for sequence %s");
						break;
					case OBJECT_STATISTIC_EXT:
						msg = gettext_noop("permission denied for statistics object %s");
						break;
					case OBJECT_SUBSCRIPTION:
						msg = gettext_noop("permission denied for subscription %s");
						break;
					case OBJECT_TABLE:
						msg = gettext_noop("permission denied for table %s");
						break;
					case OBJECT_TABLESPACE:
						msg = gettext_noop("permission denied for tablespace %s");
						break;
					case OBJECT_TSCONFIGURATION:
						msg = gettext_noop("permission denied for text search configuration %s");
						break;
					case OBJECT_TSDICTIONARY:
						msg = gettext_noop("permission denied for text search dictionary %s");
						break;
					case OBJECT_TYPE:
						msg = gettext_noop("permission denied for type %s");
						break;
					case OBJECT_VIEW:
						msg = gettext_noop("permission denied for view %s");
						break;
						/* these currently aren't used */
					case OBJECT_ACCESS_METHOD:
					case OBJECT_AMOP:
					case OBJECT_AMPROC:
					case OBJECT_ATTRIBUTE:
					case OBJECT_CAST:
					case OBJECT_DEFAULT:
					case OBJECT_DEFACL:
					case OBJECT_DOMCONSTRAINT:
					case OBJECT_PUBLICATION_NAMESPACE:
					case OBJECT_PUBLICATION_REL:
					case OBJECT_ROLE:
					case OBJECT_RULE:
					case OBJECT_TABCONSTRAINT:
					case OBJECT_TRANSFORM:
					case OBJECT_TRIGGER:
					case OBJECT_TSPARSER:
					case OBJECT_TSTEMPLATE:
					case OBJECT_USER_MAPPING:
						elog(ERROR, "unsupported object type: %d", objtype);
				}

				ereport(ERROR,
						(errcode(ERRCODE_INSUFFICIENT_PRIVILEGE),
						 errmsg(msg, objectname)));
				break;
			}
		case ACLCHECK_NOT_OWNER:
			{
				const char *msg = "???";

				switch (objtype)
				{
					case OBJECT_AGGREGATE:
						msg = gettext_noop("must be owner of aggregate %s");
						break;
					case OBJECT_COLLATION:
						msg = gettext_noop("must be owner of collation %s");
						break;
					case OBJECT_CONVERSION:
						msg = gettext_noop("must be owner of conversion %s");
						break;
					case OBJECT_DATABASE:
						msg = gettext_noop("must be owner of database %s");
						break;
					case OBJECT_DOMAIN:
						msg = gettext_noop("must be owner of domain %s");
						break;
					case OBJECT_EVENT_TRIGGER:
						msg = gettext_noop("must be owner of event trigger %s");
						break;
					case OBJECT_EXTENSION:
						msg = gettext_noop("must be owner of extension %s");
						break;
					case OBJECT_FDW:
						msg = gettext_noop("must be owner of foreign-data wrapper %s");
						break;
					case OBJECT_FOREIGN_SERVER:
						msg = gettext_noop("must be owner of foreign server %s");
						break;
					case OBJECT_FOREIGN_TABLE:
						msg = gettext_noop("must be owner of foreign table %s");
						break;
					case OBJECT_FUNCTION:
						msg = gettext_noop("must be owner of function %s");
						break;
					case OBJECT_INDEX:
						msg = gettext_noop("must be owner of index %s");
						break;
					case OBJECT_LANGUAGE:
						msg = gettext_noop("must be owner of language %s");
						break;
					case OBJECT_LARGEOBJECT:
						msg = gettext_noop("must be owner of large object %s");
						break;
					case OBJECT_MATVIEW:
						msg = gettext_noop("must be owner of materialized view %s");
						break;
					case OBJECT_OPCLASS:
						msg = gettext_noop("must be owner of operator class %s");
						break;
					case OBJECT_OPERATOR:
						msg = gettext_noop("must be owner of operator %s");
						break;
					case OBJECT_OPFAMILY:
						msg = gettext_noop("must be owner of operator family %s");
						break;
					case OBJECT_PROCEDURE:
						msg = gettext_noop("must be owner of procedure %s");
						break;
					case OBJECT_PUBLICATION:
						msg = gettext_noop("must be owner of publication %s");
						break;
					case OBJECT_ROUTINE:
						msg = gettext_noop("must be owner of routine %s");
						break;
					case OBJECT_SEQUENCE:
						msg = gettext_noop("must be owner of sequence %s");
						break;
					case OBJECT_SUBSCRIPTION:
						msg = gettext_noop("must be owner of subscription %s");
						break;
					case OBJECT_TABLE:
						msg = gettext_noop("must be owner of table %s");
						break;
					case OBJECT_TYPE:
						msg = gettext_noop("must be owner of type %s");
						break;
					case OBJECT_VIEW:
						msg = gettext_noop("must be owner of view %s");
						break;
					case OBJECT_SCHEMA:
						msg = gettext_noop("must be owner of schema %s");
						break;
					case OBJECT_STATISTIC_EXT:
						msg = gettext_noop("must be owner of statistics object %s");
						break;
					case OBJECT_TABLESPACE:
						msg = gettext_noop("must be owner of tablespace %s");
						break;
					case OBJECT_TSCONFIGURATION:
						msg = gettext_noop("must be owner of text search configuration %s");
						break;
					case OBJECT_TSDICTIONARY:
						msg = gettext_noop("must be owner of text search dictionary %s");
						break;

						/*
						 * Special cases: For these, the error message talks
						 * about "relation", because that's where the
						 * ownership is attached.  See also
						 * check_object_ownership().
						 */
					case OBJECT_COLUMN:
					case OBJECT_POLICY:
					case OBJECT_RULE:
					case OBJECT_TABCONSTRAINT:
					case OBJECT_TRIGGER:
						msg = gettext_noop("must be owner of relation %s");
						break;
						/* these currently aren't used */
					case OBJECT_ACCESS_METHOD:
					case OBJECT_AMOP:
					case OBJECT_AMPROC:
					case OBJECT_ATTRIBUTE:
					case OBJECT_CAST:
					case OBJECT_DEFAULT:
					case OBJECT_DEFACL:
					case OBJECT_DOMCONSTRAINT:
					case OBJECT_PARAMETER_ACL:
					case OBJECT_PUBLICATION_NAMESPACE:
					case OBJECT_PUBLICATION_REL:
					case OBJECT_ROLE:
					case OBJECT_TRANSFORM:
					case OBJECT_TSPARSER:
					case OBJECT_TSTEMPLATE:
					case OBJECT_USER_MAPPING:
						elog(ERROR, "unsupported object type: %d", objtype);
				}

				ereport(ERROR,
						(errcode(ERRCODE_INSUFFICIENT_PRIVILEGE),
						 errmsg(msg, objectname)));
				break;
			}
		default:
			elog(ERROR, "unrecognized AclResult: %d", (int) aclerr);
			break;
	}
}





/*
 * Special common handling for types: use element type instead of array type,
 * and format nicely
 */
void
aclcheck_error_type(AclResult aclerr, Oid typeOid)
{
	Oid			element_type = get_element_type(typeOid);

	aclcheck_error(aclerr, OBJECT_TYPE, format_type_be(element_type ? element_type : typeOid));
}


/*
 * Relay for the various pg_*_mask routines depending on object kind
 */



/* ****************************************************************
 * Exported routines for examining a user's privileges for various objects
 *
 * See aclmask() for a description of the common API for these functions.
 * ****************************************************************
 */

/*
 * Generic routine for examining a user's privileges for an object
 */


/*
 * Generic routine for examining a user's privileges for an object,
 * with is_missing
 */


/*
 * Routine for examining a user's privileges for a column
 *
 * Note: this considers only privileges granted specifically on the column.
 * It is caller's responsibility to take relation-level privileges into account
 * as appropriate.  (For the same reason, we have no special case for
 * superuser-ness here.)
 */


/*
 * Routine for examining a user's privileges for a column, with is_missing
 */


/*
 * Exported routine for examining a user's privileges for a table
 */


/*
 * Routine for examining a user's privileges for a table, with is_missing
 */


/*
 * Routine for examining a user's privileges for a configuration
 * parameter (GUC), identified by GUC name.
 */


/*
 * Routine for examining a user's privileges for a configuration
 * parameter (GUC), identified by the OID of its pg_parameter_acl entry.
 */


/*
 * Routine for examining a user's privileges for a largeobject
 *
 * When a large object is opened for reading, it is opened relative to the
 * caller's snapshot, but when it is opened for writing, a current
 * MVCC snapshot will be used.  See doc/src/sgml/lobj.sgml.  This function
 * takes a snapshot argument so that the permissions check can be made
 * relative to the same snapshot that will be used to read the underlying
 * data.  The caller will actually pass NULL for an instantaneous MVCC
 * snapshot, since all we do with the snapshot argument is pass it through
 * to systable_beginscan().
 */


/*
 * Routine for examining a user's privileges for a namespace, with is_missing
 */


/*
 * Routine for examining a user's privileges for a type, with is_missing
 */


/*
 * Exported generic routine for checking a user's access privileges to an object
 */

AclResult
object_aclcheck(Oid classid, Oid objectid, Oid roleid, AclMode mode)
{
return ACLCHECK_OK;}

/*
 * Exported generic routine for checking a user's access privileges to an
 * object, with is_missing
 */


/*
 * Exported routine for checking a user's access privileges to a column
 *
 * Returns ACLCHECK_OK if the user has any of the privileges identified by
 * 'mode'; otherwise returns a suitable error code (in practice, always
 * ACLCHECK_NO_PRIV).
 *
 * As with pg_attribute_aclmask, only privileges granted directly on the
 * column are considered here.
 */



/*
 * Exported routine for checking a user's access privileges to a column,
 * with is_missing
 */


/*
 * Exported routine for checking a user's access privileges to any/all columns
 *
 * If 'how' is ACLMASK_ANY, then returns ACLCHECK_OK if user has any of the
 * privileges identified by 'mode' on any non-dropped column in the relation;
 * otherwise returns a suitable error code (in practice, always
 * ACLCHECK_NO_PRIV).
 *
 * If 'how' is ACLMASK_ALL, then returns ACLCHECK_OK if user has any of the
 * privileges identified by 'mode' on each non-dropped column in the relation
 * (and there must be at least one such column); otherwise returns a suitable
 * error code (in practice, always ACLCHECK_NO_PRIV).
 *
 * As with pg_attribute_aclmask, only privileges granted directly on the
 * column(s) are considered here.
 *
 * Note: system columns are not considered here; there are cases where that
 * might be appropriate but there are also cases where it wouldn't.
 */


/*
 * Exported routine for checking a user's access privileges to any/all columns,
 * with is_missing
 */


/*
 * Exported routine for checking a user's access privileges to a table
 *
 * Returns ACLCHECK_OK if the user has any of the privileges identified by
 * 'mode'; otherwise returns a suitable error code (in practice, always
 * ACLCHECK_NO_PRIV).
 */


/*
 * Exported routine for checking a user's access privileges to a table,
 * with is_missing
 */


/*
 * Exported routine for checking a user's access privileges to a configuration
 * parameter (GUC), identified by GUC name.
 */


/*
 * Exported routine for checking a user's access privileges to a largeobject
 */


/*
 * Generic ownership check for an object
 */


/*
 * Check whether specified role has CREATEROLE privilege (or is a superuser)
 *
 * Note: roles do not have owners per se; instead we use this test in
 * places where an ownership-like permissions test is needed for a role.
 * Be sure to apply it to the role trying to do the operation, not the
 * role being operated on!	Also note that this generally should not be
 * considered enough privilege if the target role is a superuser.
 * (We don't handle that consideration here because we want to give a
 * separate error message for such cases, so the caller has to deal with it.)
 */




/*
 * Fetch pg_default_acl entry for given role, namespace and object type
 * (object type must be given in pg_default_acl's encoding).
 * Returns NULL if no such entry.
 */


/*
 * Get default permissions for newly created object within given schema
 *
 * Returns NULL if built-in system defaults should be used.
 *
 * If the result is not NULL, caller must call recordDependencyOnNewAcl
 * once the OID of the new object is known.
 */


/*
 * Record dependencies on roles mentioned in a new object's ACL.
 */


/*
 * Record initial privileges for the top-level object passed in.
 *
 * For the object passed in, this will record its ACL (if any) and the ACLs of
 * any sub-objects (eg: columns) into pg_init_privs.
 */


/*
 * For the object passed in, remove its ACL and the ACLs of any object subIds
 * from pg_init_privs (via recordExtensionInitPrivWorker()).
 */


/*
 * Record initial ACL for an extension object
 *
 * Can be called at any time, we check if 'creating_extension' is set and, if
 * not, exit immediately.
 *
 * Pass in the object OID, the OID of the class (the OID of the table which
 * the object is defined in) and the 'sub' id of the object (objsubid), if
 * any.  If there is no 'sub' id (they are currently only used for columns of
 * tables) then pass in '0'.  Finally, pass in the complete ACL to store.
 *
 * If an ACL already exists for this object/sub-object then we will replace
 * it with what is passed in.
 *
 * Passing in NULL for 'new_acl' will result in the entry for the object being
 * removed, if one is found.
 */


/*
 * Record initial ACL for an extension object, worker.
 *
 * This will perform a wholesale replacement of the entire ACL for the object
 * passed in, therefore be sure to pass in the complete new ACL to use.
 *
 * Generally speaking, do *not* use this function directly but instead use
 * recordExtensionInitPriv(), which checks if 'creating_extension' is set.
 * This function does *not* check if 'creating_extension' is set as it is also
 * used when an object is added to or removed from an extension via ALTER
 * EXTENSION ... ADD/DROP.
 */


/*
 * ReplaceRoleInInitPriv
 *
 * Used by shdepReassignOwned to replace mentions of a role in pg_init_privs.
 */


/*
 * RemoveRoleFromInitPriv
 *
 * Used by shdepDropOwned to remove mentions of a role in pg_init_privs.
 */

