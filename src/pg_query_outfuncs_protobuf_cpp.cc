
#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <fstream>
#include <string>
#include <protobuf/pg_query.pb.h>
#include <google/protobuf/util/json_util.h>

extern "C"
{
#include "pg_query_outfuncs.h"

#include "postgres.h"
#include <ctype.h>
#include "access/relation.h"
#include "nodes/parsenodes.h"
#include "nodes/plannodes.h"
#include "nodes/value.h"
#include "utils/datum.h"
}

#define OUT_TYPE(typename, typename_c) pg_query::typename*

#define OUT_NODE(typename, typename_c, typename_underscore, typename_underscore_upcase, typename_cast, fldname) \
	{ \
		pg_query::typename *fldname = new pg_query::typename(); \
		out->set_allocated_##fldname(fldname); \
		_out##typename_c(fldname, (const typename_cast *) obj); \
	}

#define WRITE_INT_FIELD(outname, outname_json, fldname) out->set_##outname(node->fldname);
#define WRITE_UINT_FIELD(outname, outname_json, fldname) out->set_##outname(node->fldname);
#define WRITE_UINT64_FIELD(outname, outname_json, fldname) out->set_##outname(node->fldname);
#define WRITE_LONG_FIELD(outname, outname_json, fldname) out->set_##outname(node->fldname);
#define WRITE_FLOAT_FIELD(outname, outname_json, fldname) out->set_##outname(node->fldname);
#define WRITE_BOOL_FIELD(outname, outname_json, fldname) out->set_##outname(node->fldname);

#define WRITE_CHAR_FIELD(outname, outname_json, fldname) \
	if (node->fldname != 0) { \
		out->set_##outname({node->fldname}); \
	}

#define WRITE_STRING_FIELD(outname, outname_json, fldname) \
	if (node->fldname != NULL) { \
	  out->set_##outname(node->fldname); \
	}

#define WRITE_ENUM_FIELD(typename, outname, outname_json, fldname) \
	out->set_##outname((pg_query::typename) _enumToInt##typename(node->fldname));

#define WRITE_LIST_FIELD(outname, outname_json, fldname) \
	if (node->fldname != NULL) { \
    	const ListCell *lc; \
    	foreach(lc, node->fldname) \
    	{ \
    		_outNode(out->add_##outname(), lfirst(lc)); \
    	} \
	}

#define WRITE_BITMAPSET_FIELD(outname, outname_json, fldname) // FIXME

#define WRITE_NODE_FIELD(outname, outname_json, fldname) \
	{ \
		out->set_allocated_##fldname(new pg_query::Node()); \
    	_outNode(out->mutable_##outname(), &node->fldname); \
  	}

#define WRITE_NODE_PTR_FIELD(outname, outname_json, fldname) \
	if (node->fldname != NULL) { \
    	out->set_allocated_##outname(new pg_query::Node()); \
    	_outNode(out->mutable_##outname(), node->fldname); \
	}

#define WRITE_SPECIFIC_NODE_FIELD(typename, typename_underscore, outname, outname_json, fldname) \
	{ \
		out->set_allocated_##outname(new pg_query::typename()); \
		_out##typename(out->mutable_##outname(), &node->fldname); \
	}

#define WRITE_SPECIFIC_NODE_PTR_FIELD(typename, typename_underscore, outname, outname_json, fldname) \
	if (node->fldname != NULL) { \
		out->set_allocated_##outname(new pg_query::typename()); \
		_out##typename(out->mutable_##outname(), node->fldname); \
	}

static void _outNode(pg_query::Node* out, const void *obj);

static void
_outList(pg_query::List* out_node, const List *node)
{
	const ListCell *lc;

	foreach(lc, node)
	{
		_outNode(out_node->add_items(), lfirst(lc));
	}
}

static void
_outIntList(pg_query::IntList* out_node, const List *node)
{
	const ListCell *lc;

	foreach(lc, node)
	{
		_outNode(out_node->add_items(), lfirst(lc));
	}
}

static void
_outOidList(pg_query::OidList* out_node, const List *node)
{
	const ListCell *lc;

	foreach(lc, node)
	{
		_outNode(out_node->add_items(), lfirst(lc));
	}
}

// TODO: Add Bitmapset

static void
_outInteger(pg_query::Integer* out_node, const Integer *node)
{
	out_node->set_ival(node->ival);
}

static void
_outFloat(pg_query::Float* out_node, const Float *node)
{
	out_node->set_fval(node->fval);
}

static void
_outBoolean(pg_query::Boolean* out_node, const Boolean *node)
{
	out_node->set_boolval(node->boolval);
}

static void
_outString(pg_query::String* out_node, const String *node)
{
	out_node->set_sval(node->sval);
}

static void
_outBitString(pg_query::BitString* out_node, const BitString *node)
{
	out_node->set_bsval(node->bsval);
}

static void
_outAConst(pg_query::A_Const* out_node, const A_Const *node)
{
	out_node->set_isnull(node->isnull);
	out_node->set_location(node->location);

	if (!node->isnull) {
		switch (nodeTag(&node->val.node)) {
			case T_Integer: {
				pg_query::Integer *value = new pg_query::Integer();
				value->set_ival(node->val.ival.ival);
				out_node->set_allocated_ival(value);
				break;
			}
			case T_Float: {
				pg_query::Float *value = new pg_query::Float();
				value->set_fval(pstrdup(node->val.fval.fval));
				out_node->set_allocated_fval(value);
				break;
			}
			case T_Boolean: {
				pg_query::Boolean *value = new pg_query::Boolean();
				value->set_boolval(node->val.boolval.boolval);
				out_node->set_allocated_boolval(value);
				break;
			}
			case T_String: {
				pg_query::String *value = new pg_query::String();
				value->set_sval(pstrdup(node->val.sval.sval));
				out_node->set_allocated_sval(value);
				break;
			}
			case T_BitString: {
				pg_query::BitString *value = new pg_query::BitString();
				value->set_bsval(pstrdup(node->val.bsval.bsval));
				out_node->set_allocated_bsval(value);
				break;
			}
			default:
				// Unreachable
				Assert(false);
		}
	}
}

#include "pg_query_enum_defs.c"
#include "pg_query_outfuncs_defs.c"

static void
_outNode(pg_query::Node* out, const void *obj)
{
	if (obj == NULL)
		return; // Keep out as NULL

	switch (nodeTag(obj))
	{
		#include "pg_query_outfuncs_conds.c"

		default:
			printf("could not dump unrecognized node type: %d", (int) nodeTag(obj));
			elog(WARNING, "could not dump unrecognized node type: %d",
					(int) nodeTag(obj));

			return;
	}
}

extern "C" PgQueryProtobuf
pg_query_nodes_to_protobuf(const void *obj)
{
	PgQueryProtobuf protobuf;
	const ListCell *lc;
	pg_query::ParseResult parse_result;
	if (obj == NULL) {
		protobuf.data = strdup("");
		protobuf.len = 0;
		return protobuf;
	}

	parse_result.set_version(PG_VERSION_NUM);
	foreach(lc, (List*) obj)
	{
		_outRawStmt(parse_result.add_stmts(), (const RawStmt*) lfirst(lc));
	}

	std::string output;
	parse_result.SerializeToString(&output);

	protobuf.data = (char*) calloc(output.size(), sizeof(char));
	memcpy(protobuf.data, output.data(), output.size());
	protobuf.len = output.size();

	return protobuf;
}

extern "C" char *
pg_query_nodes_to_json(const void *obj)
{
	const ListCell *lc;
	pg_query::ParseResult parse_result;

	if (obj == NULL)
		return pstrdup("{}");

	parse_result.set_version(PG_VERSION_NUM);
	foreach(lc, (List*) obj)
	{
		_outRawStmt(parse_result.add_stmts(), (const RawStmt*) lfirst(lc));
	}

	std::string output;
	google::protobuf::util::MessageToJsonString(parse_result, &output);

	return pstrdup(output.c_str());
}
