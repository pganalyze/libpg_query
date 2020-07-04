/* A Bison parser, made by GNU Bison 3.3.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2019 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_PLPGSQL_YY_PL_GRAM_H_INCLUDED
# define YY_PLPGSQL_YY_PL_GRAM_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int plpgsql_yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    IDENT = 258,
    FCONST = 259,
    SCONST = 260,
    BCONST = 261,
    XCONST = 262,
    Op = 263,
    ICONST = 264,
    PARAM = 265,
    TYPECAST = 266,
    DOT_DOT = 267,
    COLON_EQUALS = 268,
    EQUALS_GREATER = 269,
    LESS_EQUALS = 270,
    GREATER_EQUALS = 271,
    NOT_EQUALS = 272,
    T_WORD = 273,
    T_CWORD = 274,
    T_DATUM = 275,
    LESS_LESS = 276,
    GREATER_GREATER = 277,
    K_ABSOLUTE = 278,
    K_ALIAS = 279,
    K_ALL = 280,
    K_AND = 281,
    K_ARRAY = 282,
    K_ASSERT = 283,
    K_BACKWARD = 284,
    K_BEGIN = 285,
    K_BY = 286,
    K_CALL = 287,
    K_CASE = 288,
    K_CHAIN = 289,
    K_CLOSE = 290,
    K_COLLATE = 291,
    K_COLUMN = 292,
    K_COLUMN_NAME = 293,
    K_COMMIT = 294,
    K_CONSTANT = 295,
    K_CONSTRAINT = 296,
    K_CONSTRAINT_NAME = 297,
    K_CONTINUE = 298,
    K_CURRENT = 299,
    K_CURSOR = 300,
    K_DATATYPE = 301,
    K_DEBUG = 302,
    K_DECLARE = 303,
    K_DEFAULT = 304,
    K_DETAIL = 305,
    K_DIAGNOSTICS = 306,
    K_DO = 307,
    K_DUMP = 308,
    K_ELSE = 309,
    K_ELSIF = 310,
    K_END = 311,
    K_ERRCODE = 312,
    K_ERROR = 313,
    K_EXCEPTION = 314,
    K_EXECUTE = 315,
    K_EXIT = 316,
    K_FETCH = 317,
    K_FIRST = 318,
    K_FOR = 319,
    K_FOREACH = 320,
    K_FORWARD = 321,
    K_FROM = 322,
    K_GET = 323,
    K_HINT = 324,
    K_IF = 325,
    K_IMPORT = 326,
    K_IN = 327,
    K_INFO = 328,
    K_INSERT = 329,
    K_INTO = 330,
    K_IS = 331,
    K_LAST = 332,
    K_LOG = 333,
    K_LOOP = 334,
    K_MESSAGE = 335,
    K_MESSAGE_TEXT = 336,
    K_MOVE = 337,
    K_NEXT = 338,
    K_NO = 339,
    K_NOT = 340,
    K_NOTICE = 341,
    K_NULL = 342,
    K_OPEN = 343,
    K_OPTION = 344,
    K_OR = 345,
    K_PERFORM = 346,
    K_PG_CONTEXT = 347,
    K_PG_DATATYPE_NAME = 348,
    K_PG_EXCEPTION_CONTEXT = 349,
    K_PG_EXCEPTION_DETAIL = 350,
    K_PG_EXCEPTION_HINT = 351,
    K_PRINT_STRICT_PARAMS = 352,
    K_PRIOR = 353,
    K_QUERY = 354,
    K_RAISE = 355,
    K_RELATIVE = 356,
    K_RESET = 357,
    K_RETURN = 358,
    K_RETURNED_SQLSTATE = 359,
    K_REVERSE = 360,
    K_ROLLBACK = 361,
    K_ROW_COUNT = 362,
    K_ROWTYPE = 363,
    K_SCHEMA = 364,
    K_SCHEMA_NAME = 365,
    K_SCROLL = 366,
    K_SET = 367,
    K_SLICE = 368,
    K_SQLSTATE = 369,
    K_STACKED = 370,
    K_STRICT = 371,
    K_TABLE = 372,
    K_TABLE_NAME = 373,
    K_THEN = 374,
    K_TO = 375,
    K_TYPE = 376,
    K_USE_COLUMN = 377,
    K_USE_VARIABLE = 378,
    K_USING = 379,
    K_VARIABLE_CONFLICT = 380,
    K_WARNING = 381,
    K_WHEN = 382,
    K_WHILE = 383
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 120 "pl_gram.y" /* yacc.c:1921  */

		core_YYSTYPE			core_yystype;
		/* these fields must match core_YYSTYPE: */
		int						ival;
		char					*str;
		const char				*keyword;

		PLword					word;
		PLcword					cword;
		PLwdatum				wdatum;
		bool					boolean;
		Oid						oid;
		struct
		{
			char *name;
			int  lineno;
		}						varname;
		struct
		{
			char *name;
			int  lineno;
			PLpgSQL_datum   *scalar;
			PLpgSQL_datum   *row;
		}						forvariable;
		struct
		{
			char *label;
			int  n_initvars;
			int  *initvarnos;
		}						declhdr;
		struct
		{
			List *stmts;
			char *end_label;
			int   end_label_location;
		}						loop_body;
		List					*list;
		PLpgSQL_type			*dtype;
		PLpgSQL_datum			*datum;
		PLpgSQL_var				*var;
		PLpgSQL_expr			*expr;
		PLpgSQL_stmt			*stmt;
		PLpgSQL_condition		*condition;
		PLpgSQL_exception		*exception;
		PLpgSQL_exception_block	*exception_block;
		PLpgSQL_nsitem			*nsitem;
		PLpgSQL_diag_item		*diagitem;
		PLpgSQL_stmt_fetch		*fetch;
		PLpgSQL_case_when		*casewhen;

#line 238 "pl_gram.h" /* yacc.c:1921  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern __thread  YYSTYPE plpgsql_yylval;
extern __thread  YYLTYPE plpgsql_yylloc;
int plpgsql_yyparse (void);

#endif /* !YY_PLPGSQL_YY_PL_GRAM_H_INCLUDED  */
