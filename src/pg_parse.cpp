#include <emscripten/bind.h>
#include "pg_query.h"

using namespace emscripten;

/* Map to structs we can export */
typedef struct {
	std::string message; // exception message
	std::string funcname; // source function of exception (e.g. SearchSysCache)
	std::string filename; // source of exception (e.g. parse.l)
	int lineno; // source of exception (e.g. 104)
	int cursorpos; // char in query at which exception occurred
	std::string context; // additional context (optional, can be NULL)
} ParseError;

typedef struct {
	std::string parse_tree;
	std::string stderr_buffer;
	ParseError error;
} ParseResult;

extern "C" {
	ParseResult parse(intptr_t input) {
		PgQueryParseResult tmp_result;
		ParseResult result;
		ParseError error;

		tmp_result = pg_query_parse(reinterpret_cast<char*>(input));

		std::string error_message(tmp_result.error->message);
		std::string error_funcname(tmp_result.error->funcname);
		std::string error_filename(tmp_result.error->filename);

		int error_lineno(tmp_result.error->lineno);
		int error_cursorpos(tmp_result.error->cursorpos);

		std::string error_context(tmp_result.error->context);

		error.message   = error_message;
		error.funcname  = error_funcname;
		error.filename  = error_filename;
		error.lineno    = error_lineno;
		error.cursorpos = error_cursorpos;
		error.context   = error_context;

		std::string parse_tree(tmp_result.parse_tree);
		std::string stderr_buffer(tmp_result.stderr_buffer);

		result.parse_tree    = parse_tree;
		result.stderr_buffer = stderr_buffer;
		result.error         = error;

		return result;
	}
}

EMSCRIPTEN_BINDINGS(my_module) {
	value_object<ParseResult>("ParseResult")
		.field("parse_tree", &ParseResult::parse_tree)
		.field("stderr_buffer", &ParseResult::stderr_buffer)
		.field("error", &ParseResult::error)
		;

	value_object<ParseError>("ParseError")
		.field("message", &ParseError::message)
		.field("funcname", &ParseError::funcname)
		.field("filename", &ParseError::filename)
		.field("lineno", &ParseError::lineno)
		.field("cursorpos", &ParseError::cursorpos)
		.field("context", &ParseError::context)
		;

	function("parse", &parse);
}
