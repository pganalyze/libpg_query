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

/* Write an integer field */
#define WRITE_INT_FIELD(fldname) \
	appendStringInfo(str, "\"" CppAsString(fldname) "\": %d, ", node->fldname)

/* Write an unsigned integer field */
#define WRITE_UINT_FIELD(fldname) \
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
	 _outNode(str, &node->fldname), \
		 appendStringInfo(str, ", "))

/* Write a Node* field */
#define WRITE_NODE_PTR_FIELD(fldname) \
	(appendStringInfo(str, "\"" CppAsString(fldname) "\": "), \
	 _outNode(str, node->fldname), \
		 appendStringInfo(str, ", "))

/* Write a bitmapset field */
#define WRITE_BITMAPSET_FIELD(fldname) \
	(appendStringInfo(str, "\"" CppAsString(fldname) "\": "), \
	 _outBitmapset(str, node->fldname), \
	 appendStringInfo(str, ", "))


#define booltostr(x)	((x) ? "true" : "false")

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

static void
_outBitmapset(StringInfo str, const Bitmapset *bms)
{
	Bitmapset	*tmpset;
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

static void
_outInteger(StringInfo str, const Value *node)
{
	WRITE_NODE_TYPE("Integer");
	appendStringInfo(str, "\"ival\": %ld, ", node->val.ival);
}

static void
_outFloat(StringInfo str, const Value *node)
{
	WRITE_NODE_TYPE("Float");
	appendStringInfo(str, "\"str\": ");
	_outToken(str, node->val.str);
	appendStringInfo(str, ", ");
}

static void
_outString(StringInfo str, const Value *node)
{
	WRITE_NODE_TYPE("String");
	appendStringInfo(str, "\"str\": ");
	_outToken(str, node->val.str);
	appendStringInfo(str, ", ");
}

static void
_outBitString(StringInfo str, const Value *node)
{
	WRITE_NODE_TYPE("BitString");
	appendStringInfo(str, "\"str\": ");
	_outToken(str, node->val.str);
	appendStringInfo(str, ", ");
}

static void
_outNull(StringInfo str, const Value *node)
{
	WRITE_NODE_TYPE("Null");
}

#include "output_node_json_defs.c"

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
	else
	{
		appendStringInfoChar(str, '{');
		switch (nodeTag(obj))
		{
			case T_Integer:
				_outInteger(str, obj);
				break;
			case T_Float:
				_outFloat(str, obj);
				break;
			case T_String:
				_outString(str, obj);
				break;
			case T_BitString:
				_outBitString(str, obj);
				break;
			case T_Null:
				_outNull(str, obj);
				break;

			#include "output_node_json_conds.c"

			default:
				elog(WARNING, "could not dump unrecognized node type: %d",
					 (int) nodeTag(obj));

				appendStringInfo(str, "}");
				return;
		}
		removeTrailingDelimiter(str);
		appendStringInfo(str, "}}");
	}
}

char *
nodeToJSONStringV2(const void *obj)
{
	StringInfoData str;

	initStringInfo(&str);

	if (obj == NULL) /* Make sure we generate valid JSON for empty queries */
		appendStringInfoString(&str, "[]");
	else
		_outNode(&str, obj);

	return str.data;
}
