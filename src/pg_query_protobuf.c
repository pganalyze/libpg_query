#include "pg_query_protobuf.h"

#include "postgres.h"
#include <ctype.h>
#include "access/relation.h"
#include "nodes/parsenodes.h"
#include "nodes/plannodes.h"
#include "nodes/value.h"
#include "utils/datum.h"

#include "protobuf/parse_tree.pb-c.h"

#define OUT_TYPE(typename) PgQuery__##typename*

#define OUT_NODE(typename, typename_underscore, typename_cast, fldname) \
  { \
    PgQuery__##typename *__node = malloc(sizeof(PgQuery__##typename)); \
	pg_query__##typename_underscore##__init(__node); \
    _out##typename(__node, (const typename_cast *) obj); \
	out->fldname = __node; \
  }

#define WRITE_INT_FIELD(outname, outname_json, fldname) \
	if (node->fldname != 0) { \
	out->outname = node->fldname; \
	}

#define WRITE_UINT_FIELD(outname, outname_json, fldname) \
	if (node->fldname != 0) { \
	out->outname = node->fldname; \
	}

#define WRITE_LONG_FIELD(outname, outname_json, fldname) \
	if (node->fldname != 0) { \
	out->outname = node->fldname; \
	}

#define WRITE_CHAR_FIELD(outname, outname_json, fldname) \
	if (node->fldname != 0) { \
	out->outname = malloc(sizeof(char) * 2); \
	out->outname[0] = node->fldname; \
	out->outname[1] = '\0'; \
	}

#define WRITE_ENUM_FIELD(typename, outname, outname_json, fldname) \
	out->outname = _enumToInt##typename(node->fldname);

#define WRITE_FLOAT_FIELD(outname, outname_json, fldname) \
	out->outname = node->fldname; \

#define WRITE_BOOL_FIELD(outname, outname_json, fldname) \
	out->outname = node->fldname; \

#define WRITE_STRING_FIELD(outname, outname_json, fldname) \
	if (node->fldname != NULL) { \
	  out->outname = strdup(node->fldname); \
	}

#define WRITE_LIST_FIELD(outname, outname_json, fldname) \
	if (node->fldname != NULL) { \
	  out->n_##outname = list_length(node->fldname); \
	  out->outname = malloc(sizeof(PgQuery__Node*) * out->n_##outname); \
	  for (int i = 0; i < out->n_##outname; i++) \
      { \
	    PgQuery__Node *__node = malloc(sizeof(PgQuery__Node)); \
	    pg_query__node__init(__node); \
	    out->outname[i] = __node; \
	    _outNode(out->outname[i], list_nth(node->fldname, i)); \
      } \
    }

#define WRITE_BITMAPSET_FIELD(outname, outname_json, fldname) // FIXME

#define WRITE_NODE_FIELD(outname, outname_json, fldname) \
	if (true) { \
	  PgQuery__Node *__node = malloc(sizeof(PgQuery__Node)); \
	  pg_query__node__init(__node); \
	  out->outname = __node; \
      _outNode(out->outname, &node->fldname); \
  	}

#define WRITE_NODE_PTR_FIELD(outname, outname_json, fldname) \
	if (node->fldname != NULL) { \
	  PgQuery__Node *__node = malloc(sizeof(PgQuery__Node)); \
	  pg_query__node__init(__node); \
	  out->outname = __node; \
      _outNode(out->outname, node->fldname); \
	}

#define WRITE_SPECIFIC_NODE_FIELD(typename, typename_underscore, outname, outname_json, fldname) \
  { \
    PgQuery__##typename *__node = malloc(sizeof(typename)); \
    pg_query__##typename_underscore##__init(__node); \
    _out##typename(__node, &node->fldname); \
	out->outname = __node; \
  }

#define WRITE_SPECIFIC_NODE_PTR_FIELD(typename, typename_underscore, outname, outname_json, fldname) \
    if (node->fldname != NULL) { \
	  PgQuery__##typename *__node = malloc(sizeof(typename)); \
      pg_query__##typename_underscore##__init(__node); \
      _out##typename(__node, node->fldname); \
	  out->outname = __node; \
	}

static void _outNode(PgQuery__Node*, const void *);

PgQueryProtobuf
pg_query_nodes_to_protobuf(const void *obj)
{
  PgQueryProtobuf protobuf;
  if (obj == NULL) {
    protobuf.data = strdup("");
    protobuf.len = 0;
    return protobuf;
  }

  PgQuery__Node root_node = PG_QUERY__NODE__INIT;

  _outNode(&root_node, obj);

  protobuf.len = pg_query__node__get_packed_size(&root_node);
  protobuf.data = malloc(sizeof(char) * protobuf.len);
  pg_query__node__pack(&root_node, (void*) protobuf.data); 
  return protobuf;
}

#include "pg_query_outfuncs_defs.c"

static void
_outList(PgQuery__List* out, const List *node)
{
	const ListCell *lc;
	int i = 0;
	out->n_items = list_length(node);
	out->items = malloc(sizeof(PgQuery__Node*) * out->n_items);
    foreach(lc, node)
    {
		out->items[i] = malloc(sizeof(PgQuery__Node));
		pg_query__node__init(out->items[i]);
	    _outNode(out->items[i], lfirst(lc));
		i++;
    }
}

static void
_outIntList(PgQuery__IntList* out, const List *node)
{
	const ListCell *lc;
	int i = 0;
	out->n_items = list_length(node);
	out->items = malloc(sizeof(PgQuery__Node*) * out->n_items);
    foreach(lc, node)
    {
		out->items[i] = malloc(sizeof(PgQuery__Node));
		pg_query__node__init(out->items[i]);
	    _outNode(out->items[i], lfirst(lc));
		i++;
    }
}

static void
_outOidList(PgQuery__OidList* out, const List *node)
{
	const ListCell *lc;
	int i = 0;
	out->n_items = list_length(node);
	out->items = malloc(sizeof(PgQuery__Node*) * out->n_items);
    foreach(lc, node)
    {
		out->items[i] = malloc(sizeof(PgQuery__Node));
		pg_query__node__init(out->items[i]);
	    _outNode(out->items[i], lfirst(lc));
		i++;
    }
}

// TODO: Add Bitmapset

static void
_outInteger(PgQuery__Integer* out, const Value *node)
{
  out->ival = node->val.ival;
}

static void
_outFloat(PgQuery__Float* out, const Value *node)
{
  out->str = node->val.str;
}

static void
_outString(PgQuery__String* out, const Value *node)
{
  out->str = node->val.str;
}

static void
_outBitString(PgQuery__BitString* out, const Value *node)
{
  out->str = node->val.str;
}

static void
_outNull(PgQuery__Null* out, const Value *node)
{
  // Null has no fields
}

static void
_outNode(PgQuery__Node* out, const void *obj)
{
	if (obj == NULL)
	{
		// TODO
	}
	else if (IsA(obj, List))
	{
    OUT_NODE(List, list, List, list);
	}
	else
	{
		switch (nodeTag(obj))
		{
			case T_Integer:
        OUT_NODE(Integer, integer, Value, integer);
				break;
			case T_Float:
        OUT_NODE(Float, float, Value, float_);
				break;
			case T_String:
        OUT_NODE(String, string, Value, string);
				break;
			case T_BitString:
        OUT_NODE(BitString, bit_string, Value, bit_string);
				break;
			case T_Null:
        OUT_NODE(Null, null, Value, null);
				break;
			case T_IntList:
        OUT_NODE(IntList, int_list, List, int_list);
				break;
			case T_OidList:
        OUT_NODE(OidList, oid_list, List, oid_list);
				break;

			#include "pg_query_outfuncs_conds.c"

			default:
        printf("could not dump unrecognized node type: %d", (int) nodeTag(obj));
				elog(WARNING, "could not dump unrecognized node type: %d",
					 (int) nodeTag(obj));

				return;
		}
	}
}

