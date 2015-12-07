#include "output_node_json.h"

#include "postgres.h"

#include <ctype.h>

#include "lib/stringinfo.h"
#include "nodes/plannodes.h"
#include "nodes/relation.h"
#include "utils/datum.h"

/* Write the label for the node type */
#define WRITE_NODE_TYPE(nodelabel) \
	appendStringInfoString(str, "\"" nodelabel "\": {")

/* Write an integer field (anything written as ":fldname %d") */
#define WRITE_INT_FIELD(fldname) \
	appendStringInfo(str, "\"" CppAsString(fldname) "\": %d, ", node->fldname)

/* Write an unsigned integer field (anything written as ":fldname %u") */
#define WRITE_UINT_FIELD(fldname) \
	appendStringInfo(str, "\"" CppAsString(fldname) "\": %u, ", node->fldname)

/* Write an OID field (don't hard-wire assumption that OID is same as uint) */
#define WRITE_OID_FIELD(fldname) \
	appendStringInfo(str, "\"" CppAsString(fldname) "\": %u, ", node->fldname)

/* Write a long-integer field */
#define WRITE_LONG_FIELD(fldname) \
	appendStringInfo(str, "\"" CppAsString(fldname) "\": %ld, ", node->fldname)

/* Write a char field (ie, one ascii character) */
#define WRITE_CHAR_FIELD(fldname) \
  if (node->fldname == 0) { appendStringInfo(str, "\"" CppAsString(fldname) "\": null, "); \
  } else { appendStringInfo(str, "\"" CppAsString(fldname) "\": \"%c\", ", node->fldname); }

/* Write an enumerated-type field as an integer code */
#define WRITE_ENUM_FIELD(fldname, enumtype) \
	appendStringInfo(str, "\"" CppAsString(fldname) "\": %d, ", \
					 (int) node->fldname)

/* Write a float field */
#define WRITE_FLOAT_FIELD(fldname) \
	appendStringInfo(str, "\"" CppAsString(fldname) "\": %f, ", node->fldname)

/* Write a boolean field */
#define WRITE_BOOL_FIELD(fldname) \
	appendStringInfo(str, "\"" CppAsString(fldname) "\": %s, ", \
					 booltostr(node->fldname))

/* Write a character-string (possibly NULL) field */
#define WRITE_STRING_FIELD(fldname) \
	(appendStringInfo(str, "\"" CppAsString(fldname) "\": "), \
	 _outToken(str, node->fldname), \
	 appendStringInfo(str, ", "))

/* Write a parse location field (actually same as INT case) */
#define WRITE_LOCATION_FIELD(fldname) \
	appendStringInfo(str, "\"" CppAsString(fldname) "\": %d, ", node->fldname)

/* Write a Node field */
#define WRITE_NODE_FIELD(fldname) \
	(appendStringInfo(str, "\"" CppAsString(fldname) "\": "), \
	 _outNode(str, node->fldname), \
     appendStringInfo(str, ", "))

/* Write a bitmapset field */
#define WRITE_BITMAPSET_FIELD(fldname) \
	(appendStringInfo(str, "\"" CppAsString(fldname) "\": "), \
	 _outBitmapset(str, node->fldname), \
	 appendStringInfo(str, ", "))


#define booltostr(x)  ((x) ? "true" : "false")

static void _outNode(StringInfo str, const void *obj);

static void
removeTrailingDelimiter(StringInfo str)
{
	if (str->len >= 2 && str->data[str->len - 2] == ',' && str->data[str->len - 1] == ' ') {
		str->len -= 2;
		str->data[str->len] = '\0';
	}
}

static void
_outToken(StringInfo str, const char *s)
{
	if (s == NULL)
	{
		appendStringInfoString(str, "null");
		return;
	}

	appendStringInfoChar(str, '"');
	while (*s)
	{
		/* These chars must be backslashed anywhere in the string */
		if (*s == '\n')
			appendStringInfoString(str, "\\n");
		else if (*s == '\r')
			appendStringInfoString(str, "\\r");
		else if (*s == '\t')
			appendStringInfoString(str, "\\t");
		else if (*s == '\\' || *s == '"') {
			appendStringInfoChar(str, '\\');
			appendStringInfoChar(str, *s);
		} else
			appendStringInfoChar(str, *s);
		s++;
	}
	appendStringInfoChar(str, '"');
}

static void
_outList(StringInfo str, const List *node)
{
	const ListCell *lc;

	appendStringInfoChar(str, '[');

	foreach(lc, node)
	{
		if (IsA(node, List))
			_outNode(str, lfirst(lc));
		else if (IsA(node, IntList))
			appendStringInfo(str, " %d", lfirst_int(lc));
		else if (IsA(node, OidList))
			appendStringInfo(str, " %u", lfirst_oid(lc));
		else
			elog(ERROR, "unrecognized list node type: %d", (int) node->type);

		if (lnext(lc))
			appendStringInfoString(str, ", ");
	}

	appendStringInfoChar(str, ']');
}

/*
 * _outBitmapset -
 *	   converts a bitmap set of integers
 *
 * Note: the output format is "(b int int ...)", similar to an integer List.
 */
static void
_outBitmapset(StringInfo str, const Bitmapset *bms)
{
	Bitmapset  *tmpset;
	int			x;

	appendStringInfoChar(str, '[');
	/*appendStringInfoChar(str, 'b');*/
	tmpset = bms_copy(bms);
	while ((x = bms_first_member(tmpset)) >= 0)
		appendStringInfo(str, "%d, ", x);
	bms_free(tmpset);
	removeTrailingDelimiter(str);
	appendStringInfoChar(str, ']');
}

/*
 * Print the value of a Datum given its type.
 */
static void
_outDatum(StringInfo str, Datum value, int typlen, bool typbyval)
{
	Size		length,
				i;
	char	   *s;

	length = datumGetSize(value, typbyval, typlen);

	if (typbyval)
	{
		s = (char *) (&value);
		/*appendStringInfo(str, "%u [ ", (unsigned int) length);*/
		appendStringInfoChar(str, '[');
		for (i = 0; i < (Size) sizeof(Datum); i++)
			appendStringInfo(str, "%d, ", (int) (s[i]));
		removeTrailingDelimiter(str);
		appendStringInfoChar(str, ']');
	}
	else
	{
		s = (char *) DatumGetPointer(value);
		if (!PointerIsValid(s))
			appendStringInfoString(str, "[]");
		else
		{
			/*appendStringInfo(str, "%u [ ", (unsigned int) length);*/
			appendStringInfoChar(str, '[');
			for (i = 0; i < length; i++)
				appendStringInfo(str, "%d, ", (int) (s[i]));
			removeTrailingDelimiter(str);
			appendStringInfoChar(str, ']');
		}
	}
}

/*
* print the basic stuff of all nodes that inherit from Path
*
* Note we do NOT print the parent, else we'd be in infinite recursion.
* We can print the parent's relids for identification purposes, though.
* We also do not print the whole of param_info, since it's printed by
* _outRelOptInfo; it's sufficient and less cluttering to print just the
* required outer relids.
*/
static void
_outPathInfo(StringInfo str, const Path *node)
{
	WRITE_ENUM_FIELD(pathtype, NodeTag);
	appendStringInfoString(str, "\"parent_relids\": ");
	_outBitmapset(str, node->parent->relids);
	appendStringInfoString(str, ", ");
	appendStringInfoString(str, "\"required_outer\": ");
	if (node->param_info)
		_outBitmapset(str, node->param_info->ppi_req_outer);
	else
		_outBitmapset(str, NULL);
	appendStringInfoString(str, ", ");
	WRITE_FLOAT_FIELD(rows);
	WRITE_FLOAT_FIELD(startup_cost);
	WRITE_FLOAT_FIELD(total_cost);
	WRITE_NODE_FIELD(pathkeys);
}

static void
_outValue(StringInfo str, const Value *node)
{
  WRITE_NODE_TYPE("VALUE");

	WRITE_ENUM_FIELD(type, NodeTag);

	switch (node->type)
	{
		case T_Integer:
		  appendStringInfo(str, "\"ival\": %ld, ", node->val.ival);
			break;
		case T_Float:
	  case T_String:
    case T_BitString:
		  appendStringInfo(str, "\"str\": ");
		  _outToken(str, node->val.str);
		  appendStringInfo(str, ", ");
			break;
		case T_Null:
			break;
		default:
			elog(ERROR, "unrecognized node type: %d", (int) node->type);
			break;
	}
}

#include "output_node_json_defs.c"

static void
_outMergeJoin(StringInfo str, const MergeJoin *node)
{
	int			numCols;
	int			i;

	WRITE_NODE_TYPE("MERGEJOIN");

	_outJoinInfo(str, (const Join *) node);

	WRITE_NODE_FIELD(mergeclauses);

	numCols = list_length(node->mergeclauses);

	appendStringInfoString(str, "\"mergeFamilies\": [");
	for (i = 0; i < numCols; i++)
		appendStringInfo(str, "%u, ", node->mergeFamilies[i]);
	removeTrailingDelimiter(str);
	appendStringInfoString(str, "], ");

	appendStringInfoString(str, "\"mergeCollations\": [");
	for (i = 0; i < numCols; i++)
		appendStringInfo(str, "%u, ", node->mergeCollations[i]);
	removeTrailingDelimiter(str);
	appendStringInfoString(str, "], ");

	appendStringInfoString(str, "\"mergeStrategies\": [");
	for (i = 0; i < numCols; i++)
		appendStringInfo(str, "%d, ", node->mergeStrategies[i]);
	removeTrailingDelimiter(str);
	appendStringInfoString(str, "], ");

	appendStringInfoString(str, "\"mergeNullsFirst\": [");
	for (i = 0; i < numCols; i++)
		appendStringInfo(str, "%d, ", (int) node->mergeNullsFirst[i]);
	removeTrailingDelimiter(str);
	appendStringInfoString(str, "], ");
}

static void
_outConst(StringInfo str, const Const *node)
{
	WRITE_NODE_TYPE("CONST");

	WRITE_OID_FIELD(consttype);
	WRITE_INT_FIELD(consttypmod);
	WRITE_OID_FIELD(constcollid);
	WRITE_INT_FIELD(constlen);
	WRITE_BOOL_FIELD(constbyval);
	WRITE_BOOL_FIELD(constisnull);
	WRITE_LOCATION_FIELD(location);

	appendStringInfoString(str, "\"constvalue\": ");
	if (node->constisnull)
		appendStringInfoString(str, "null");
	else
		_outDatum(str, node->constvalue, node->constlen, node->constbyval);
	appendStringInfoString(str, ", ");
}

static void
_outPath(StringInfo str, const Path *node)
{
	WRITE_NODE_TYPE("PATH");

	_outPathInfo(str, (const Path *) node);
}

static void
_outEquivalenceClass(StringInfo str, const EquivalenceClass *node)
{
	/* Only the final merged version is relevant for an Equivalence Class node */
	while (node->ec_merged)
		node = node->ec_merged;

	WRITE_NODE_TYPE("EQUIVALENCECLASS");

	WRITE_NODE_FIELD(ec_opfamilies);
	WRITE_OID_FIELD(ec_collation);
	WRITE_NODE_FIELD(ec_members);
	WRITE_NODE_FIELD(ec_sources);
	WRITE_NODE_FIELD(ec_derives);
	WRITE_BITMAPSET_FIELD(ec_relids);
	WRITE_BOOL_FIELD(ec_has_const);
	WRITE_BOOL_FIELD(ec_has_volatile);
	WRITE_BOOL_FIELD(ec_below_outer_join);
	WRITE_BOOL_FIELD(ec_broken);
	WRITE_UINT_FIELD(ec_sortref);
}

/*
 * _outNode -
 *	  converts a Node into the JSON representation and appends it to str
 */
static void
_outNode(StringInfo str, const void *obj)
{
	if (obj == NULL)
	{
		appendStringInfoString(str, "null");
	}
	else if (IsA(obj, List) ||IsA(obj, IntList) || IsA(obj, OidList))
	{
		_outList(str, obj);
	}
	else if (IsA(obj, Integer) || IsA(obj, Float) || IsA(obj, String) || IsA(obj, BitString))
	{
		appendStringInfoChar(str, '{');
		_outValue(str, obj);
		removeTrailingDelimiter(str);
		appendStringInfo(str, "}}");
	}
	else
	{
		appendStringInfoChar(str, '{');
		switch (nodeTag(obj))
		{
			case T_MergeJoin:
				_outMergeJoin(str, obj);
				break;
			case T_Const:
				_outConst(str, obj);
				break;
			case T_Path:
				_outPath(str, obj);
				break;
			case T_EquivalenceClass:
				_outEquivalenceClass(str, obj);
				break;

			#include "output_node_json_conds.c"

			default:

				/*
				 * This should be an ERROR, but it's too useful to be able to
				 * dump structures that _outNode only understands part of.
				 */
				elog(WARNING, "could not dump unrecognized node type: %d",
					 (int) nodeTag(obj));

				appendStringInfo(str, "}");
				return;
		}
		removeTrailingDelimiter(str);
		appendStringInfo(str, "}}");
	}
}

/*
 * nodeToJSONStringV2 -
 *	   returns the JSON representation of the Node as a palloc'd string
 */
char *
nodeToJSONStringV2(const void *obj)
{
	StringInfoData str;

	/* see stringinfo.h for an explanation of this maneuver */
	initStringInfo(&str);

	if (obj == NULL) /* Make sure we generate valid JSON for empty queries */
		appendStringInfoString(&str, "[]");
	else
		_outNode(&str, obj);

	return str.data;
}
