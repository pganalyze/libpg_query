// Wrapper header for raw parse tree access
// This header includes the PostgreSQL internal types needed for direct parse tree access

#ifndef PG_QUERY_RAW_H
#define PG_QUERY_RAW_H

#include "pg_query.h"

// Include PostgreSQL headers needed for parse tree access
#include "src/postgres/include/postgres.h"
#include "src/postgres/include/nodes/nodes.h"
#include "src/postgres/include/nodes/pg_list.h"
#include "src/postgres/include/nodes/value.h"
#include "src/postgres/include/nodes/primnodes.h"
#include "src/postgres/include/nodes/parsenodes.h"

#endif
