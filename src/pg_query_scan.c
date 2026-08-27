#include "pg_query.h"
#include "pg_query_internal.h"

#include "gramparse.h"
#include "lib/stringinfo.h"

#include "protobuf/pg_query.upb.h"

#include <unistd.h>
#include <fcntl.h>

/* This is ugly. We need to access yyleng outside of scan.l, and casting yyscanner
   to this internal struct seemed like one way to do it... */
struct yyguts_t
{
  void *yyextra_r;
  FILE *yyin_r, *yyout_r;
  size_t yy_buffer_stack_top; /**< index of top of stack. */
  size_t yy_buffer_stack_max; /**< capacity of stack. */
  struct yy_buffer_state *yy_buffer_stack; /**< Stack as an array. */
  char yy_hold_char;
  size_t yy_n_chars;
  size_t yyleng_r;
};

PgQueryScanResult pg_query_scan(const char* input)
{
  MemoryContext ctx = NULL;
  PgQueryScanResult result = {0};
  core_yyscan_t yyscanner;
  core_yy_extra_type yyextra;
  core_YYSTYPE yylval;
  YYLTYPE    yylloc;
  upb_Arena *arena = NULL;
  pg_query_ScanResult *scan_result;

  ctx = pg_query_enter_memory_context();

  MemoryContext parse_context = CurrentMemoryContext;

  char stderr_buffer[STDERR_BUFFER_LEN + 1] = {0};
#ifndef DEBUG
  int stderr_global;
  int stderr_pipe[2];
#endif

#ifndef DEBUG
  // Setup pipe for stderr redirection
  if (pipe(stderr_pipe) != 0) {
    PgQueryError* error = malloc(sizeof(PgQueryError));

    error->message = strdup("Failed to open pipe, too many open file descriptors")

    result.error = error;

    return result;
  }

  fcntl(stderr_pipe[0], F_SETFL, fcntl(stderr_pipe[0], F_GETFL) | O_NONBLOCK);

  // Redirect stderr to the pipe
  stderr_global = dup(STDERR_FILENO);
  dup2(stderr_pipe[1], STDERR_FILENO);
  close(stderr_pipe[1]);
#endif

  PG_TRY();
  {
    size_t packed_len;
    char *packed_data;

    arena = upb_Arena_New();
    scan_result = pg_query_ScanResult_new(arena);
    pg_query_ScanResult_set_version(scan_result, PG_VERSION_NUM);

    /* initialize the flex scanner --- should match raw_parser().
     * upb's repeated field grows dynamically, so unlike the protobuf-c path we
     * no longer need a separate pre-counting pass to size the token array. */
    yyscanner = scanner_init(input, &yyextra, &ScanKeywords, ScanKeywordTokens);

    /* Lex tokens  */
    for (;;)
    {
      int tok;
      pg_query_ScanToken *scan_token;

      tok = core_yylex(&yylval, &yylloc, yyscanner);
      if (tok == 0) break;

      scan_token = pg_query_ScanResult_add_tokens(scan_result, arena);
      pg_query_ScanToken_set_start(scan_token, yylloc);
      if (tok == SCONST || tok == USCONST || tok == BCONST || tok == XCONST || tok == IDENT || tok == UIDENT || tok == C_COMMENT) {
        pg_query_ScanToken_set_end(scan_token, yyextra.yyllocend);
      } else {
        pg_query_ScanToken_set_end(scan_token, yylloc + ((struct yyguts_t*) yyscanner)->yyleng_r);
      }
      pg_query_ScanToken_set_token(scan_token, tok);

      switch (tok) {
      #define PG_KEYWORD(a,b,c,d) case b: pg_query_ScanToken_set_keyword_kind(scan_token, c + 1); break;
      #include "parser/kwlist.h"
      #undef PG_KEYWORD
      default: pg_query_ScanToken_set_keyword_kind(scan_token, 0);
      }
    }

    scanner_finish(yyscanner);

    /* Serialize into the arena, then copy out into a malloc'd buffer that
     * survives exiting the memory context (freed in pg_query_free_scan_result). */
    packed_data = pg_query_ScanResult_serialize(scan_result, arena, &packed_len);
    result.pbuf.len = packed_len;
    result.pbuf.data = malloc(packed_len);
    memcpy(result.pbuf.data, packed_data, packed_len);

    upb_Arena_Free(arena);
    arena = NULL;

#ifndef DEBUG
    // Save stderr for result
    read(stderr_pipe[0], stderr_buffer, STDERR_BUFFER_LEN);
#endif

    result.stderr_buffer = strdup(stderr_buffer);
  }
  PG_CATCH();
  {
    ErrorData* error_data;
    PgQueryError* error;

    MemoryContextSwitchTo(parse_context);
    error_data = CopyErrorData();

    // Note: This is intentionally malloc so exiting the memory context doesn't free this
    error = malloc(sizeof(PgQueryError));
    error->message   = strdup(error_data->message);
    error->filename  = strdup(error_data->filename);
    error->funcname  = strdup(error_data->funcname);
    error->context   = NULL;
    error->lineno    = error_data->lineno;
    error->cursorpos = error_data->cursorpos;

    result.error = error;
    FlushErrorState();
  }
  PG_END_TRY();

#ifndef DEBUG
  // Restore stderr, close pipe
  dup2(stderr_global, STDERR_FILENO);
  close(stderr_pipe[0]);
  close(stderr_global);
#endif

  pg_query_exit_memory_context(ctx);

  return result;
}

void pg_query_free_scan_result(PgQueryScanResult result)
{
  if (result.error) {
    pg_query_free_error(result.error);
  }

  free(result.pbuf.data);
  free(result.stderr_buffer);
}
