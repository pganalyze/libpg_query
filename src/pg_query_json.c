#include "pg_query_json.h"

#include "postgres.h"

#include <ctype.h>

#include "access/relation.h"
#include "nodes/parsenodes.h"
#include "nodes/plannodes.h"
#include "nodes/value.h"
#include "utils/datum.h"

static void _outNode(StringInfo str, const void *obj);

#include "pg_query_json_helper.c"

#define OUT_TYPE(typename) StringInfo

#define OUT_NODE(typename, typename_underscore, typename_cast, fldname) \
  { \
    WRITE_NODE_TYPE(CppAsString(typename_cast)); \
    _out##typename(out, (const typename_cast *) obj); \
  }

/* Write the label for the node type */
#define WRITE_NODE_TYPE(nodelabel) \
	appendStringInfoString(out, "\"" nodelabel "\": {")

/* Write an integer field */
#define WRITE_INT_FIELD(outname, outname_json, fldname) \
	if (node->fldname != 0) { \
		appendStringInfo(out, "\"" CppAsString(outname_json) "\": %d, ", node->fldname); \
	}

/* Write an unsigned integer field */
#define WRITE_UINT_FIELD(outname, outname_json, fldname) \
	if (node->fldname != 0) { \
		appendStringInfo(out, "\"" CppAsString(outname_json) "\": %u, ", node->fldname); \
	}

/* Write a long-integer field */
#define WRITE_LONG_FIELD(outname, outname_json, fldname) \
	if (node->fldname != 0) { \
		appendStringInfo(out, "\"" CppAsString(outname_json) "\": %ld, ", node->fldname); \
	}

/* Write a char field (ie, one ascii character) */
#define WRITE_CHAR_FIELD(outname, outname_json, fldname) \
	if (node->fldname != 0) { \
		appendStringInfo(out, "\"" CppAsString(outname_json) "\": \"%c\", ", node->fldname); \
	}

/* Write an enumerated-type field as an integer code */
#define WRITE_ENUM_FIELD(typename, outname, outname_json, fldname) \
	appendStringInfo(out, "\"" CppAsString(outname_json) "\": \"%s\", ", \
					 _enumToString##typename(node->fldname));

/* Write a float field */
#define WRITE_FLOAT_FIELD(outname, outname_json, fldname) \
	appendStringInfo(out, "\"" CppAsString(outname_json) "\": %f, ", node->fldname)

/* Write a boolean field */
#define WRITE_BOOL_FIELD(outname, outname_json, fldname) \
	if (node->fldname) { \
		appendStringInfo(out, "\"" CppAsString(outname_json) "\": %s, ", \
					 	booltostr(node->fldname)); \
	}

/* Write a character-string (possibly NULL) field */
#define WRITE_STRING_FIELD(outname, outname_json, fldname) \
	if (node->fldname != NULL) { \
		appendStringInfo(out, "\"" CppAsString(outname_json) "\": "); \
	 	_outToken(out, node->fldname); \
	 	appendStringInfo(out, ", "); \
	}

#define WRITE_LIST_FIELD(outname, outname_json, fldname) \
	if (node->fldname != NULL) { \
		const ListCell *lc; \
		appendStringInfo(out, "\"" CppAsString(outname_json) "\": "); \
		appendStringInfoChar(out, '['); \
		foreach(lc, node->fldname) { \
			_outNode(out, lfirst(lc)); \
			if (lnext(node->fldname, lc)) \
				appendStringInfoString(out, ", "); \
		} \
		 appendStringInfo(out, "], "); \
    }

#define WRITE_NODE_FIELD(outname, outname_json, fldname) \
	if (true) { \
		 appendStringInfo(out, "\"" CppAsString(outname_json) "\": "); \
	     _outNode(out, &node->fldname); \
		 appendStringInfo(out, ", "); \
  	}

#define WRITE_NODE_PTR_FIELD(outname, outname_json, fldname) \
	if (node->fldname != NULL) { \
		 appendStringInfo(out, "\"" CppAsString(outname_json) "\": "); \
		 _outNode(out, node->fldname); \
		 appendStringInfo(out, ", "); \
	}

#define WRITE_SPECIFIC_NODE_FIELD(typename, typename_underscore, outname, outname_json, fldname) \
	{ \
    	appendStringInfo(out, "\"" CppAsString(outname_json) "\": {"); \
    	_out##typename(out, &node->fldname); \
		removeTrailingDelimiter(out); \
 		appendStringInfo(out, "}, "); \
  	}

#define WRITE_SPECIFIC_NODE_PTR_FIELD(typename, typename_underscore, outname, outname_json, fldname) \
	if (node->fldname != NULL) { \
		 appendStringInfo(out, "\"" CppAsString(outname_json) "\": {"); \
	   	 _out##typename(out, node->fldname); \
		 removeTrailingDelimiter(out); \
 		 appendStringInfo(out, "}, "); \
	}

#define WRITE_BITMAPSET_FIELD(outname, outname_json, fldname) \
	(appendStringInfo(out, "\"" CppAsString(outname_json) "\": "), \
	 _outBitmapset(out, node->fldname), \
	 appendStringInfo(out, ", "))


static void
_outList(StringInfo out, const List *node)
{
	const ListCell *lc;

	// Simple lists are frequent structures - we don't make them into full nodes to avoid super-verbose output
	appendStringInfoChar(out, '[');

	foreach(lc, node)
	{
		_outNode(out, lfirst(lc));

		if (lnext(node, lc))
			appendStringInfoString(out, ", ");
	}

	appendStringInfoChar(out, ']');
}

static void
_outIntList(StringInfo out, const List *node)
{
	const ListCell *lc;

	WRITE_NODE_TYPE("IntList");
	appendStringInfo(out, "\"items\": ");
	appendStringInfoChar(out, '[');

	foreach(lc, node)
	{
		appendStringInfo(out, " %d", lfirst_int(lc));

		if (lnext(node, lc))
			appendStringInfoString(out, ", ");
	}

	appendStringInfoChar(out, ']');
	appendStringInfo(out, ", ");
}

static void
_outOidList(StringInfo out, const List *node)
{
	const ListCell *lc;

	WRITE_NODE_TYPE("OidList");
	appendStringInfo(out, "\"items\": ");
	appendStringInfoChar(out, '[');

	foreach(lc, node)
	{
		appendStringInfo(out, " %u", lfirst_oid(lc));

		if (lnext(node, lc))
			appendStringInfoString(out, ", ");
	}

	appendStringInfoChar(out, ']');
	appendStringInfo(out, ", ");
}

static void
_outBitmapset(StringInfo out, const Bitmapset *bms)
{
	Bitmapset	*tmpset;
	int			x;

	appendStringInfoChar(out, '[');
	/*appendStringInfoChar(out, 'b');*/
	tmpset = bms_copy(bms);
	while ((x = bms_first_member(tmpset)) >= 0)
		appendStringInfo(out, "%d, ", x);
	bms_free(tmpset);
	removeTrailingDelimiter(out);
	appendStringInfoChar(out, ']');
}

static void
_outInteger(StringInfo out, const Value *node)
{
	WRITE_NODE_TYPE("Integer");
	appendStringInfo(out, "\"ival\": %d, ", node->val.ival);
}

static void
_outFloat(StringInfo out, const Value *node)
{
	WRITE_NODE_TYPE("Float");
	appendStringInfo(out, "\"str\": ");
	_outToken(out, node->val.str);
	appendStringInfo(out, ", ");
}

static void
_outString(StringInfo out, const Value *node)
{
	WRITE_NODE_TYPE("String");
	appendStringInfo(out, "\"str\": ");
	_outToken(out, node->val.str);
	appendStringInfo(out, ", ");
}

static void
_outBitString(StringInfo out, const Value *node)
{
	WRITE_NODE_TYPE("BitString");
	appendStringInfo(out, "\"str\": ");
	_outToken(out, node->val.str);
	appendStringInfo(out, ", ");
}

static void
_outNull(StringInfo out, const Value *node)
{
	WRITE_NODE_TYPE("Null");
}

#include "pg_query_outfuncs_defs.c"

static void
_outNode(StringInfo out, const void *obj)
{
	if (obj == NULL)
	{
		appendStringInfoString(out, "null");
	}
	else if (IsA(obj, List))
	{
		_outList(out, obj);
	}
	else
	{
		appendStringInfoChar(out, '{');
		switch (nodeTag(obj))
		{
			case T_Integer:
				_outInteger(out, obj);
				break;
			case T_Float:
				_outFloat(out, obj);
				break;
			case T_String:
				_outString(out, obj);
				break;
			case T_BitString:
				_outBitString(out, obj);
				break;
			case T_Null:
				_outNull(out, obj);
				break;
			case T_IntList:
				_outIntList(out, obj);
				break;
			case T_OidList:
				_outOidList(out, obj);
				break;

			#include "pg_query_outfuncs_conds.c"

			default:
				elog(WARNING, "could not dump unrecognized node type: %d",
					 (int) nodeTag(obj));

				appendStringInfo(out, "}");
				return;
		}
		removeTrailingDelimiter(out);
		appendStringInfo(out, "}}");
	}
}

char *
pg_query_nodes_to_json(const void *obj)
{
	StringInfoData out;

	initStringInfo(&out);

	if (obj == NULL) /* Make sure we generate valid JSON for empty queries */
		appendStringInfoString(&out, "[]");
	else
		_outNode(&out, obj);

	return out.data;
}
