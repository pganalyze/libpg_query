/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_PLPGSQL_YY_PL_GRAM_H_INCLUDED
# define YY_PLPGSQL_YY_PL_GRAM_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int plpgsql_yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    IDENT = 258,                   /* IDENT  */
    UIDENT = 259,                  /* UIDENT  */
    FCONST = 260,                  /* FCONST  */
    SCONST = 261,                  /* SCONST  */
    USCONST = 262,                 /* USCONST  */
    BCONST = 263,                  /* BCONST  */
    XCONST = 264,                  /* XCONST  */
    Op = 265,                      /* Op  */
    ICONST = 266,                  /* ICONST  */
    PARAM = 267,                   /* PARAM  */
    TYPECAST = 268,                /* TYPECAST  */
    DOT_DOT = 269,                 /* DOT_DOT  */
    COLON_EQUALS = 270,            /* COLON_EQUALS  */
    EQUALS_GREATER = 271,          /* EQUALS_GREATER  */
    LESS_EQUALS = 272,             /* LESS_EQUALS  */
    GREATER_EQUALS = 273,          /* GREATER_EQUALS  */
    NOT_EQUALS = 274,              /* NOT_EQUALS  */
    SQL_COMMENT = 275,             /* SQL_COMMENT  */
    C_COMMENT = 276,               /* C_COMMENT  */
    T_WORD = 277,                  /* T_WORD  */
    T_CWORD = 278,                 /* T_CWORD  */
    T_DATUM = 279,                 /* T_DATUM  */
    LESS_LESS = 280,               /* LESS_LESS  */
    GREATER_GREATER = 281,         /* GREATER_GREATER  */
    K_ABSOLUTE = 282,              /* K_ABSOLUTE  */
    K_ALIAS = 283,                 /* K_ALIAS  */
    K_ALL = 284,                   /* K_ALL  */
    K_AND = 285,                   /* K_AND  */
    K_ARRAY = 286,                 /* K_ARRAY  */
    K_ASSERT = 287,                /* K_ASSERT  */
    K_BACKWARD = 288,              /* K_BACKWARD  */
    K_BEGIN = 289,                 /* K_BEGIN  */
    K_BY = 290,                    /* K_BY  */
    K_CALL = 291,                  /* K_CALL  */
    K_CASE = 292,                  /* K_CASE  */
    K_CHAIN = 293,                 /* K_CHAIN  */
    K_CLOSE = 294,                 /* K_CLOSE  */
    K_COLLATE = 295,               /* K_COLLATE  */
    K_COLUMN = 296,                /* K_COLUMN  */
    K_COLUMN_NAME = 297,           /* K_COLUMN_NAME  */
    K_COMMIT = 298,                /* K_COMMIT  */
    K_CONSTANT = 299,              /* K_CONSTANT  */
    K_CONSTRAINT = 300,            /* K_CONSTRAINT  */
    K_CONSTRAINT_NAME = 301,       /* K_CONSTRAINT_NAME  */
    K_CONTINUE = 302,              /* K_CONTINUE  */
    K_CURRENT = 303,               /* K_CURRENT  */
    K_CURSOR = 304,                /* K_CURSOR  */
    K_DATATYPE = 305,              /* K_DATATYPE  */
    K_DEBUG = 306,                 /* K_DEBUG  */
    K_DECLARE = 307,               /* K_DECLARE  */
    K_DEFAULT = 308,               /* K_DEFAULT  */
    K_DETAIL = 309,                /* K_DETAIL  */
    K_DIAGNOSTICS = 310,           /* K_DIAGNOSTICS  */
    K_DO = 311,                    /* K_DO  */
    K_DUMP = 312,                  /* K_DUMP  */
    K_ELSE = 313,                  /* K_ELSE  */
    K_ELSIF = 314,                 /* K_ELSIF  */
    K_END = 315,                   /* K_END  */
    K_ERRCODE = 316,               /* K_ERRCODE  */
    K_ERROR = 317,                 /* K_ERROR  */
    K_EXCEPTION = 318,             /* K_EXCEPTION  */
    K_EXECUTE = 319,               /* K_EXECUTE  */
    K_EXIT = 320,                  /* K_EXIT  */
    K_FETCH = 321,                 /* K_FETCH  */
    K_FIRST = 322,                 /* K_FIRST  */
    K_FOR = 323,                   /* K_FOR  */
    K_FOREACH = 324,               /* K_FOREACH  */
    K_FORWARD = 325,               /* K_FORWARD  */
    K_FROM = 326,                  /* K_FROM  */
    K_GET = 327,                   /* K_GET  */
    K_HINT = 328,                  /* K_HINT  */
    K_IF = 329,                    /* K_IF  */
    K_IMPORT = 330,                /* K_IMPORT  */
    K_IN = 331,                    /* K_IN  */
    K_INFO = 332,                  /* K_INFO  */
    K_INSERT = 333,                /* K_INSERT  */
    K_INTO = 334,                  /* K_INTO  */
    K_IS = 335,                    /* K_IS  */
    K_LAST = 336,                  /* K_LAST  */
    K_LOG = 337,                   /* K_LOG  */
    K_LOOP = 338,                  /* K_LOOP  */
    K_MESSAGE = 339,               /* K_MESSAGE  */
    K_MESSAGE_TEXT = 340,          /* K_MESSAGE_TEXT  */
    K_MOVE = 341,                  /* K_MOVE  */
    K_NEXT = 342,                  /* K_NEXT  */
    K_NO = 343,                    /* K_NO  */
    K_NOT = 344,                   /* K_NOT  */
    K_NOTICE = 345,                /* K_NOTICE  */
    K_NULL = 346,                  /* K_NULL  */
    K_OPEN = 347,                  /* K_OPEN  */
    K_OPTION = 348,                /* K_OPTION  */
    K_OR = 349,                    /* K_OR  */
    K_PERFORM = 350,               /* K_PERFORM  */
    K_PG_CONTEXT = 351,            /* K_PG_CONTEXT  */
    K_PG_DATATYPE_NAME = 352,      /* K_PG_DATATYPE_NAME  */
    K_PG_EXCEPTION_CONTEXT = 353,  /* K_PG_EXCEPTION_CONTEXT  */
    K_PG_EXCEPTION_DETAIL = 354,   /* K_PG_EXCEPTION_DETAIL  */
    K_PG_EXCEPTION_HINT = 355,     /* K_PG_EXCEPTION_HINT  */
    K_PRINT_STRICT_PARAMS = 356,   /* K_PRINT_STRICT_PARAMS  */
    K_PRIOR = 357,                 /* K_PRIOR  */
    K_QUERY = 358,                 /* K_QUERY  */
    K_RAISE = 359,                 /* K_RAISE  */
    K_RELATIVE = 360,              /* K_RELATIVE  */
    K_RESET = 361,                 /* K_RESET  */
    K_RETURN = 362,                /* K_RETURN  */
    K_RETURNED_SQLSTATE = 363,     /* K_RETURNED_SQLSTATE  */
    K_REVERSE = 364,               /* K_REVERSE  */
    K_ROLLBACK = 365,              /* K_ROLLBACK  */
    K_ROW_COUNT = 366,             /* K_ROW_COUNT  */
    K_ROWTYPE = 367,               /* K_ROWTYPE  */
    K_SCHEMA = 368,                /* K_SCHEMA  */
    K_SCHEMA_NAME = 369,           /* K_SCHEMA_NAME  */
    K_SCROLL = 370,                /* K_SCROLL  */
    K_SET = 371,                   /* K_SET  */
    K_SLICE = 372,                 /* K_SLICE  */
    K_SQLSTATE = 373,              /* K_SQLSTATE  */
    K_STACKED = 374,               /* K_STACKED  */
    K_STRICT = 375,                /* K_STRICT  */
    K_TABLE = 376,                 /* K_TABLE  */
    K_TABLE_NAME = 377,            /* K_TABLE_NAME  */
    K_THEN = 378,                  /* K_THEN  */
    K_TO = 379,                    /* K_TO  */
    K_TYPE = 380,                  /* K_TYPE  */
    K_USE_COLUMN = 381,            /* K_USE_COLUMN  */
    K_USE_VARIABLE = 382,          /* K_USE_VARIABLE  */
    K_USING = 383,                 /* K_USING  */
    K_VARIABLE_CONFLICT = 384,     /* K_VARIABLE_CONFLICT  */
    K_WARNING = 385,               /* K_WARNING  */
    K_WHEN = 386,                  /* K_WHEN  */
    K_WHILE = 387                  /* K_WHILE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 120 "pl_gram.y"

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

#line 247 "pl_gram.h"

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
