/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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
    K_ARRAY = 281,
    K_ASSERT = 282,
    K_BACKWARD = 283,
    K_BEGIN = 284,
    K_BY = 285,
    K_CALL = 286,
    K_CASE = 287,
    K_CLOSE = 288,
    K_COLLATE = 289,
    K_COLUMN = 290,
    K_COLUMN_NAME = 291,
    K_COMMIT = 292,
    K_CONSTANT = 293,
    K_CONSTRAINT = 294,
    K_CONSTRAINT_NAME = 295,
    K_CONTINUE = 296,
    K_CURRENT = 297,
    K_CURSOR = 298,
    K_DATATYPE = 299,
    K_DEBUG = 300,
    K_DECLARE = 301,
    K_DEFAULT = 302,
    K_DETAIL = 303,
    K_DIAGNOSTICS = 304,
    K_DO = 305,
    K_DUMP = 306,
    K_ELSE = 307,
    K_ELSIF = 308,
    K_END = 309,
    K_ERRCODE = 310,
    K_ERROR = 311,
    K_EXCEPTION = 312,
    K_EXECUTE = 313,
    K_EXIT = 314,
    K_FETCH = 315,
    K_FIRST = 316,
    K_FOR = 317,
    K_FOREACH = 318,
    K_FORWARD = 319,
    K_FROM = 320,
    K_GET = 321,
    K_HINT = 322,
    K_IF = 323,
    K_IMPORT = 324,
    K_IN = 325,
    K_INFO = 326,
    K_INSERT = 327,
    K_INTO = 328,
    K_IS = 329,
    K_LAST = 330,
    K_LOG = 331,
    K_LOOP = 332,
    K_MESSAGE = 333,
    K_MESSAGE_TEXT = 334,
    K_MOVE = 335,
    K_NEXT = 336,
    K_NO = 337,
    K_NOT = 338,
    K_NOTICE = 339,
    K_NULL = 340,
    K_OPEN = 341,
    K_OPTION = 342,
    K_OR = 343,
    K_PERFORM = 344,
    K_PG_CONTEXT = 345,
    K_PG_DATATYPE_NAME = 346,
    K_PG_EXCEPTION_CONTEXT = 347,
    K_PG_EXCEPTION_DETAIL = 348,
    K_PG_EXCEPTION_HINT = 349,
    K_PRINT_STRICT_PARAMS = 350,
    K_PRIOR = 351,
    K_QUERY = 352,
    K_RAISE = 353,
    K_RELATIVE = 354,
    K_RESET = 355,
    K_RESULT_OID = 356,
    K_RETURN = 357,
    K_RETURNED_SQLSTATE = 358,
    K_REVERSE = 359,
    K_ROLLBACK = 360,
    K_ROW_COUNT = 361,
    K_ROWTYPE = 362,
    K_SCHEMA = 363,
    K_SCHEMA_NAME = 364,
    K_SCROLL = 365,
    K_SET = 366,
    K_SLICE = 367,
    K_SQLSTATE = 368,
    K_STACKED = 369,
    K_STRICT = 370,
    K_TABLE = 371,
    K_TABLE_NAME = 372,
    K_THEN = 373,
    K_TO = 374,
    K_TYPE = 375,
    K_USE_COLUMN = 376,
    K_USE_VARIABLE = 377,
    K_USING = 378,
    K_VARIABLE_CONFLICT = 379,
    K_WARNING = 380,
    K_WHEN = 381,
    K_WHILE = 382
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 120 "pl_gram.y" /* yacc.c:1909  */

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

#line 233 "pl_gram.h" /* yacc.c:1909  */
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
