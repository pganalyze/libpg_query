#ifndef PG_QUERY_OUTFUNCS_H
#define PG_QUERY_OUTFUNCS_H

#include "pg_query.h"

/*
 * Throws (via elog) if the tree could not be serialized, either because it
 * exceeds PG_QUERY_PROTOBUF_MAX_DEPTH or the stack depth limit was reached
 * while building or encoding the message. Must be called inside PG_TRY.
 */
PgQueryProtobuf pg_query_nodes_to_protobuf(const void *obj);

char *pg_query_node_to_json(const void *obj);
char *pg_query_nodes_to_json(const void *obj);

/*
 * PL/pgSQL parse trees: funcs is a List of PLpgSQL_function *. Same error
 * behavior as the functions above. The protobuf output references the
 * functions' strings directly, so they must stay allocated until it has been
 * produced (see pg_query_parse_plpgsql.c).
 */
char *pg_query_plpgsql_to_json(const void *funcs);
PgQueryProtobuf pg_query_plpgsql_to_protobuf(const void *funcs);

#endif
