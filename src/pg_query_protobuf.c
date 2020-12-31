#include "pg_query_protobuf.h"

#include "postgres.h"
#include <ctype.h>
#include "access/relation.h"
#include "nodes/parsenodes.h"
#include "nodes/plannodes.h"
#include "nodes/value.h"
#include "utils/datum.h"

#include "protobuf/parse_tree.pb-c.h"

#define OUT_NODE(typename, typename_underscore, typename_cast, fldname) \
  { \
    PgQuery__##typename *fldname = malloc(sizeof(PgQuery__##typename)); \
	pg_query__##typename_underscore##__init(fldname); \
    _out##typename(fldname, (const typename_cast *) obj); \
  }

#define WRITE_INT_FIELD(outname, fldname) \
	if (node->fldname != 0) { \
	out_node->outname = node->fldname; \
	}

#define WRITE_UINT_FIELD(outname, fldname) \
	if (node->fldname != 0) { \
	out_node->outname = node->fldname; \
	}

#define WRITE_LONG_FIELD(outname, fldname) \
	if (node->fldname != 0) { \
	out_node->outname = node->fldname; \
	}

// FIXME: Memory management
#define WRITE_CHAR_FIELD(outname, fldname) \
	if (node->fldname != 0) { \
	out_node->outname = node->fldname; \
	}

#define WRITE_ENUM_FIELD(typename, outname, fldname) \
	out_node->outname = (int) node->fldname;

#define WRITE_FLOAT_FIELD(outname, fldname) \
	out_node->outname = node->fldname; \

#define WRITE_BOOL_FIELD(outname, fldname) \
	out_node->outname = node->fldname; \

// FIXME: Memory management
#define WRITE_STRING_FIELD(outname, fldname) \
	if (node->fldname != NULL) { \
	  out_node->outname = node->fldname; \
	}

#define WRITE_LIST_FIELD(outname, fldname) \
	if (node->fldname != NULL) { \
	  out_node->n_##outname = list_length(node->fldname); \
	  out_node->outname = malloc(sizeof(PgQuery__Node*) * out_node->n_##outname); \
	  for (int i = 0; i < out_node->n_##outname; i++) \
      { \
	    PgQuery__Node *__node = malloc(sizeof(PgQuery__Node)); \
	    pg_query__node__init(__node); \
	    out_node->outname[i] = __node; \
	    _outNode(out_node->outname[i], list_nth(node->fldname, i)); \
      } \
    }

#define WRITE_BITMAPSET_FIELD(outname, fldname) // FIXME

#define WRITE_NODE_FIELD(outname, fldname) \
	if (true) { \
	  PgQuery__Node *__node = malloc(sizeof(PgQuery__Node)); \
	  pg_query__node__init(__node); \
	  out_node->outname = __node; \
      _outNode(out_node->outname, &node->fldname); \
  	}

#define WRITE_NODE_PTR_FIELD(outname, fldname) \
	if (node->fldname != NULL) { \
	  PgQuery__Node *__node = malloc(sizeof(PgQuery__Node)); \
	  pg_query__node__init(__node); \
	  out_node->outname = __node; \
      _outNode(out_node->outname, node->fldname); \
	}

#define WRITE_SPECIFIC_NODE_FIELD(typename, typename_underscore, outname, fldname) \
  { \
    PgQuery__##typename *outname = malloc(sizeof(typename)); \
    pg_query__##typename_underscore##__init(outname); \
    _out##typename(outname, &node->fldname); \
  }

#define WRITE_SPECIFIC_NODE_PTR_FIELD(typename, typename_underscore, outname, fldname) \
    if (node->fldname != NULL) { \
	  PgQuery__##typename *outname = malloc(sizeof(typename)); \
      pg_query__##typename_underscore##__init(outname); \
      _out##typename(outname, node->fldname); \
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

#include "pg_query_protobuf_defs.c"

static void
_outList(PgQuery__List* out_node, const List *node)
{
	const ListCell *lc;
	int i = 0;
	out_node->n_items = list_length(node);
	out_node->items = malloc(sizeof(PgQuery__Node*) * out_node->n_items);
    foreach(lc, node)
    {
		out_node->items[i] = malloc(sizeof(PgQuery__Node));
		pg_query__node__init(out_node->items[i]);
	    _outNode(out_node->items[i], lfirst(lc));
		i++;
    }
}

static void
_outIntList(PgQuery__IntList* out_node, const List *node)
{
	const ListCell *lc;
	int i = 0;
	out_node->n_items = list_length(node);
	out_node->items = malloc(sizeof(PgQuery__Node*) * out_node->n_items);
    foreach(lc, node)
    {
		out_node->items[i] = malloc(sizeof(PgQuery__Node));
		pg_query__node__init(out_node->items[i]);
	    _outNode(out_node->items[i], lfirst(lc));
		i++;
    }
}

static void
_outOidList(PgQuery__OidList* out_node, const List *node)
{
	const ListCell *lc;
	int i = 0;
	out_node->n_items = list_length(node);
	out_node->items = malloc(sizeof(PgQuery__Node*) * out_node->n_items);
    foreach(lc, node)
    {
		out_node->items[i] = malloc(sizeof(PgQuery__Node));
		pg_query__node__init(out_node->items[i]);
	    _outNode(out_node->items[i], lfirst(lc));
		i++;
    }
}

// TODO: Add Bitmapset

static void
_outInteger(PgQuery__Integer* out_node, const Value *node)
{
  out_node->ival = node->val.ival;
}

static void
_outFloat(PgQuery__Float* out_node, const Value *node)
{
  out_node->str = node->val.str;
}

static void
_outString(PgQuery__String* out_node, const Value *node)
{
  out_node->str = node->val.str;
}

static void
_outBitString(PgQuery__BitString* out_node, const Value *node)
{
  out_node->str = node->val.str;
}

static void
_outNull(PgQuery__Null* out_node, const Value *node)
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

			#include "pg_query_protobuf_conds.c"

			default:
        printf("could not dump unrecognized node type: %d", (int) nodeTag(obj));
				elog(WARNING, "could not dump unrecognized node type: %d",
					 (int) nodeTag(obj));

				return;
		}
	}
}

