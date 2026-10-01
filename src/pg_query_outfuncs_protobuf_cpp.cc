
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
#include "miscadmin.h"

#include "plpgsql.h"
}

#define OUT_TYPE(typename, typename_c) pg_query::typename*

#define OUT_NODE(typename, typename_c, typename_underscore, typename_underscore_upcase, typename_cast, fldname) \
	{ \
		pg_query::typename *fldname = new pg_query::typename(); \
		out->set_allocated_##fldname(fldname); \
		_out##typename_c(fldname, (const typename_cast *) obj); \
	}

/*
 * These macros are invoked from the generated pg_query_outfuncs_defs.c /
 * _conds.c, shared with the upb and JSON backends. The leading `msgtype`
 * argument names the enclosing message for the upb backend; the C++ backend
 * sets fields on the typed `out` message and ignores it.
 */
#define WRITE_INT_FIELD(msgtype, outname, outname_json, fldname) out->set_##outname(node->fldname);
#define WRITE_UINT_FIELD(msgtype, outname, outname_json, fldname) out->set_##outname(node->fldname);
#define WRITE_UINT64_FIELD(msgtype, outname, outname_json, fldname) out->set_##outname(node->fldname);
#define WRITE_LONG_FIELD(msgtype, outname, outname_json, fldname) out->set_##outname(node->fldname);
#define WRITE_FLOAT_FIELD(msgtype, outname, outname_json, fldname) out->set_##outname(node->fldname);
#define WRITE_BOOL_FIELD(msgtype, outname, outname_json, fldname) out->set_##outname(node->fldname);

#define WRITE_CHAR_FIELD(msgtype, outname, outname_json, fldname) \
	if (node->fldname != 0) { \
		out->set_##outname({node->fldname}); \
	}

#define WRITE_STRING_FIELD(msgtype, outname, outname_json, fldname) \
	if (node->fldname != NULL) { \
	  out->set_##outname(node->fldname); \
	}

#define WRITE_ENUM_FIELD(msgtype, enumtype, outname, outname_json, fldname) \
	out->set_##outname((pg_query::enumtype) _enumToInt##enumtype(node->fldname));

#define WRITE_LIST_FIELD(msgtype, outname, outname_json, fldname) \
	if (node->fldname != NULL) { \
    	const ListCell *lc; \
    	foreach(lc, node->fldname) \
    	{ \
    		_outNode(out->add_##outname(), lfirst(lc)); \
    	} \
	}

#define WRITE_BITMAPSET_FIELD(msgtype, outname, outname_json, fldname) // FIXME

#define WRITE_NODE_FIELD(msgtype, outname, outname_json, fldname) \
	{ \
		out->set_allocated_##fldname(new pg_query::Node()); \
    	_outNode(out->mutable_##outname(), &node->fldname); \
  	}

#define WRITE_NODE_PTR_FIELD(msgtype, outname, outname_json, fldname) \
	if (node->fldname != NULL) { \
    	out->set_allocated_##outname(new pg_query::Node()); \
    	_outNode(out->mutable_##outname(), node->fldname); \
	}

#define WRITE_SPECIFIC_NODE_FIELD(msgtype, typename, typename_underscore, outname, outname_json, fldname) \
	{ \
		out->set_allocated_##outname(new pg_query::typename()); \
		_out##typename(out->mutable_##outname(), &node->fldname); \
	}

// This recurses into _out##typename directly, bypassing the stack depth check
// in _outNode, so check here (e.g. a long UNION chain nests SelectStmt in
// SelectStmt without ever going through _outNode).
#define WRITE_SPECIFIC_NODE_PTR_FIELD(msgtype, typename, typename_underscore, outname, outname_json, fldname) \
	if (node->fldname != NULL) { \
		check_stack_depth(); \
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
	check_stack_depth();

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

/*
 * PL/pgSQL parse trees
 *
 * The generated pg_query_outfuncs_plpgsql_defs.c uses the WRITE_*_FIELD macros
 * above plus the following, for the things PL/pgSQL structs have and parse
 * nodes don't (see the plpgsql section of scripts/node_support/overrides.pl).
 */

/* dno of a referenced variable, or -1 if there is none */
#define PLPGSQL_DATUM_DNO(d) \
	((d) != NULL ? ((const PLpgSQL_datum *) (d))->dno : -1)

#define OUT_PLPGSQL_NODE(wrapper, typename, fldname) \
	{ \
		pg_query::typename *__n = new pg_query::typename(); \
		out->set_allocated_##fldname(__n); \
		_out##typename(__n, (const typename *) node); \
	}

#define WRITE_PLPGSQL_DATUM_REF_FIELD(msgtype, outname, outname_json, fldname) \
	out->set_##outname(PLPGSQL_DATUM_DNO(node->fldname));

#define WRITE_PLPGSQL_LIST_FIELD(msgtype, elemtype, outname, outname_json, fldname) \
	if (node->fldname != NULL) { \
		const ListCell *lc; \
		foreach(lc, node->fldname) \
		{ \
			_out##elemtype(out->add_##outname(), (const elemtype *) lfirst(lc)); \
		} \
	}

#define WRITE_PLPGSQL_PTR_ARRAY_FIELD(msgtype, elemtype, outname, outname_json, fldname, countfld) \
	for (int __i = 0; __i < node->countfld; __i++) \
		_out##elemtype(out->add_##outname(), (const elemtype *) node->fldname[__i]);

#define WRITE_PLPGSQL_INT_ARRAY_FIELD(msgtype, outname, outname_json, fldname, countfld) \
	for (int __i = 0; __i < node->countfld; __i++) \
		out->add_##outname(node->fldname[__i]);

#define WRITE_PLPGSQL_LINKED_LIST_FIELD(msgtype, elemtype, outname, outname_json, fldname, nextfld) \
	for (const elemtype *__e = node->fldname; __e != NULL; __e = __e->nextfld) \
		_out##elemtype(out->add_##outname(), __e);

#define WRITE_PLPGSQL_CUSTOM_FIELD(msgtype, outname, outname_json, fldname) \
	_out##msgtype##_##fldname(out, node);

/* PLpgSQL_row.fieldnames[] / varnos[], zipped into a list of PLpgSQL_row_field */
static void
_outPLpgSQL_row_fieldnames(pg_query::PLpgSQL_row *out, const PLpgSQL_row *node)
{
	for (int i = 0; i < node->nfields; i++)
	{
		pg_query::PLpgSQL_row_field *field = out->add_fields();

		if (node->fieldnames[i] != NULL)
			field->set_name(node->fieldnames[i]);
		field->set_varno(node->varnos[i]);
	}
}

#include "pg_query_outfuncs_plpgsql_defs.c"

static pg_query::PLpgSQLParseResult *
_plpgsqlResult(const void *funcs)
{
	pg_query::PLpgSQLParseResult *result = new pg_query::PLpgSQLParseResult();
	const ListCell *lc;

	PG_TRY();
	{
		result->set_version(PG_VERSION_NUM);
		foreach(lc, (const List *) funcs)
		{
			_outPLpgSQL_function(result->add_functions(), (const PLpgSQL_function *) lfirst(lc));
		}
	}
	PG_CATCH();
	{
		delete result;
		PG_RE_THROW();
	}
	PG_END_TRY();

	return result;
}

extern "C" PgQueryProtobuf
pg_query_plpgsql_to_protobuf(const void *funcs)
{
	PgQueryProtobuf protobuf;
	pg_query::PLpgSQLParseResult *result = _plpgsqlResult(funcs);
	std::string output;

	result->SerializeToString(&output);
	protobuf.data = (char*) calloc(output.size(), sizeof(char));
	memcpy(protobuf.data, output.data(), output.size());
	protobuf.len = output.size();

	delete result;
	return protobuf;
}

// Note: Unlike the JSON backend this prints int64 fields (how_many) as strings,
// per the proto3 JSON mapping
extern "C" char *
pg_query_plpgsql_to_json(const void *funcs)
{
	pg_query::PLpgSQLParseResult *result = _plpgsqlResult(funcs);
	std::string output;

	google::protobuf::util::MessageToJsonString(*result, &output);
	delete result;
	return pstrdup(output.c_str());
}

extern "C" PgQueryProtobuf
pg_query_nodes_to_protobuf(const void *obj)
{
	PgQueryProtobuf protobuf;
	const ListCell *lc;

	if (obj == NULL) {
		protobuf.data = strdup("");
		protobuf.len = 0;
		return protobuf;
	}

	pg_query::ParseResult *parse_result = new pg_query::ParseResult();

	PG_TRY();
	{
		parse_result->set_version(PG_VERSION_NUM);
		foreach(lc, (List*) obj)
		{
			_outRawStmt(parse_result->add_stmts(), (const RawStmt*) lfirst(lc));
		}

		std::string output;
		parse_result->SerializeToString(&output);

		protobuf.data = (char*) calloc(output.size(), sizeof(char));
		memcpy(protobuf.data, output.data(), output.size());
		protobuf.len = output.size();
	}
	PG_CATCH();
	{
		delete parse_result;
		PG_RE_THROW();
	}
	PG_END_TRY();

	delete parse_result;
	return protobuf;
}

extern "C" char *
pg_query_nodes_to_json(const void *obj)
{
	const ListCell *lc;
	char	   *result = NULL;

	if (obj == NULL)
		return pstrdup("{}");

	pg_query::ParseResult *parse_result = new pg_query::ParseResult();

	PG_TRY();
	{
		parse_result->set_version(PG_VERSION_NUM);
		foreach(lc, (List*) obj)
		{
			_outRawStmt(parse_result->add_stmts(), (const RawStmt*) lfirst(lc));
		}

		std::string output;
		google::protobuf::util::MessageToJsonString(*parse_result, &output);
		result = pstrdup(output.c_str());
	}
	PG_CATCH();
	{
		delete parse_result;
		PG_RE_THROW();
	}
	PG_END_TRY();

	delete parse_result;
	return result;
}
