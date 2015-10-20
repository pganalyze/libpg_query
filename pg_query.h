#ifndef PG_QUERY_H
#define PG_QUERY_H

typedef struct {
	char* message; // exception message
	char* filename; // source of exception (e.g. parse.l)
	int lineno; // source of exception (e.g. 104)
	int cursorpos; // char in query at which exception occurred
} PgQueryError;

typedef struct {
  char* parse_tree;
  char* stderr_buffer;
  PgQueryError* error;
} PgQueryParseResult;

typedef struct {
  char* normalized_query;
  PgQueryError* error;
} PgQueryNormalizeResult;

void pg_query_init(void);
PgQueryNormalizeResult pg_query_normalize(char* input);
PgQueryParseResult pg_query_parse(char* input);

#endif
