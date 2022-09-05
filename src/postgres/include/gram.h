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

#ifndef YY_BASE_YY_GRAM_H_INCLUDED
# define YY_BASE_YY_GRAM_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int base_yydebug;
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
    ABORT_P = 277,                 /* ABORT_P  */
    ABSOLUTE_P = 278,              /* ABSOLUTE_P  */
    ACCESS = 279,                  /* ACCESS  */
    ACTION = 280,                  /* ACTION  */
    ADD_P = 281,                   /* ADD_P  */
    ADMIN = 282,                   /* ADMIN  */
    AFTER = 283,                   /* AFTER  */
    AGGREGATE = 284,               /* AGGREGATE  */
    ALL = 285,                     /* ALL  */
    ALSO = 286,                    /* ALSO  */
    ALTER = 287,                   /* ALTER  */
    ALWAYS = 288,                  /* ALWAYS  */
    ANALYSE = 289,                 /* ANALYSE  */
    ANALYZE = 290,                 /* ANALYZE  */
    AND = 291,                     /* AND  */
    ANY = 292,                     /* ANY  */
    ARRAY = 293,                   /* ARRAY  */
    AS = 294,                      /* AS  */
    ASC = 295,                     /* ASC  */
    ASSERTION = 296,               /* ASSERTION  */
    ASSIGNMENT = 297,              /* ASSIGNMENT  */
    ASYMMETRIC = 298,              /* ASYMMETRIC  */
    AT = 299,                      /* AT  */
    ATTACH = 300,                  /* ATTACH  */
    ATTRIBUTE = 301,               /* ATTRIBUTE  */
    AUTHORIZATION = 302,           /* AUTHORIZATION  */
    BACKWARD = 303,                /* BACKWARD  */
    BEFORE = 304,                  /* BEFORE  */
    BEGIN_P = 305,                 /* BEGIN_P  */
    BETWEEN = 306,                 /* BETWEEN  */
    BIGINT = 307,                  /* BIGINT  */
    BINARY = 308,                  /* BINARY  */
    BIT = 309,                     /* BIT  */
    BOOLEAN_P = 310,               /* BOOLEAN_P  */
    BOTH = 311,                    /* BOTH  */
    BY = 312,                      /* BY  */
    CACHE = 313,                   /* CACHE  */
    CALL = 314,                    /* CALL  */
    CALLED = 315,                  /* CALLED  */
    CASCADE = 316,                 /* CASCADE  */
    CASCADED = 317,                /* CASCADED  */
    CASE = 318,                    /* CASE  */
    CAST = 319,                    /* CAST  */
    CATALOG_P = 320,               /* CATALOG_P  */
    CHAIN = 321,                   /* CHAIN  */
    CHAR_P = 322,                  /* CHAR_P  */
    CHARACTER = 323,               /* CHARACTER  */
    CHARACTERISTICS = 324,         /* CHARACTERISTICS  */
    CHECK = 325,                   /* CHECK  */
    CHECKPOINT = 326,              /* CHECKPOINT  */
    CLASS = 327,                   /* CLASS  */
    CLOSE = 328,                   /* CLOSE  */
    CLUSTER = 329,                 /* CLUSTER  */
    COALESCE = 330,                /* COALESCE  */
    COLLATE = 331,                 /* COLLATE  */
    COLLATION = 332,               /* COLLATION  */
    COLUMN = 333,                  /* COLUMN  */
    COLUMNS = 334,                 /* COLUMNS  */
    COMMENT = 335,                 /* COMMENT  */
    COMMENTS = 336,                /* COMMENTS  */
    COMMIT = 337,                  /* COMMIT  */
    COMMITTED = 338,               /* COMMITTED  */
    CONCURRENTLY = 339,            /* CONCURRENTLY  */
    CONFIGURATION = 340,           /* CONFIGURATION  */
    CONFLICT = 341,                /* CONFLICT  */
    CONNECTION = 342,              /* CONNECTION  */
    CONSTRAINT = 343,              /* CONSTRAINT  */
    CONSTRAINTS = 344,             /* CONSTRAINTS  */
    CONTENT_P = 345,               /* CONTENT_P  */
    CONTINUE_P = 346,              /* CONTINUE_P  */
    CONVERSION_P = 347,            /* CONVERSION_P  */
    COPY = 348,                    /* COPY  */
    COST = 349,                    /* COST  */
    CREATE = 350,                  /* CREATE  */
    CROSS = 351,                   /* CROSS  */
    CSV = 352,                     /* CSV  */
    CUBE = 353,                    /* CUBE  */
    CURRENT_P = 354,               /* CURRENT_P  */
    CURRENT_CATALOG = 355,         /* CURRENT_CATALOG  */
    CURRENT_DATE = 356,            /* CURRENT_DATE  */
    CURRENT_ROLE = 357,            /* CURRENT_ROLE  */
    CURRENT_SCHEMA = 358,          /* CURRENT_SCHEMA  */
    CURRENT_TIME = 359,            /* CURRENT_TIME  */
    CURRENT_TIMESTAMP = 360,       /* CURRENT_TIMESTAMP  */
    CURRENT_USER = 361,            /* CURRENT_USER  */
    CURSOR = 362,                  /* CURSOR  */
    CYCLE = 363,                   /* CYCLE  */
    DATA_P = 364,                  /* DATA_P  */
    DATABASE = 365,                /* DATABASE  */
    DAY_P = 366,                   /* DAY_P  */
    DEALLOCATE = 367,              /* DEALLOCATE  */
    DEC = 368,                     /* DEC  */
    DECIMAL_P = 369,               /* DECIMAL_P  */
    DECLARE = 370,                 /* DECLARE  */
    DEFAULT = 371,                 /* DEFAULT  */
    DEFAULTS = 372,                /* DEFAULTS  */
    DEFERRABLE = 373,              /* DEFERRABLE  */
    DEFERRED = 374,                /* DEFERRED  */
    DEFINER = 375,                 /* DEFINER  */
    DELETE_P = 376,                /* DELETE_P  */
    DELIMITER = 377,               /* DELIMITER  */
    DELIMITERS = 378,              /* DELIMITERS  */
    DEPENDS = 379,                 /* DEPENDS  */
    DESC = 380,                    /* DESC  */
    DETACH = 381,                  /* DETACH  */
    DICTIONARY = 382,              /* DICTIONARY  */
    DISABLE_P = 383,               /* DISABLE_P  */
    DISCARD = 384,                 /* DISCARD  */
    DISTINCT = 385,                /* DISTINCT  */
    DO = 386,                      /* DO  */
    DOCUMENT_P = 387,              /* DOCUMENT_P  */
    DOMAIN_P = 388,                /* DOMAIN_P  */
    DOUBLE_P = 389,                /* DOUBLE_P  */
    DROP = 390,                    /* DROP  */
    EACH = 391,                    /* EACH  */
    ELSE = 392,                    /* ELSE  */
    ENABLE_P = 393,                /* ENABLE_P  */
    ENCODING = 394,                /* ENCODING  */
    ENCRYPTED = 395,               /* ENCRYPTED  */
    END_P = 396,                   /* END_P  */
    ENUM_P = 397,                  /* ENUM_P  */
    ESCAPE = 398,                  /* ESCAPE  */
    EVENT = 399,                   /* EVENT  */
    EXCEPT = 400,                  /* EXCEPT  */
    EXCLUDE = 401,                 /* EXCLUDE  */
    EXCLUDING = 402,               /* EXCLUDING  */
    EXCLUSIVE = 403,               /* EXCLUSIVE  */
    EXECUTE = 404,                 /* EXECUTE  */
    EXISTS = 405,                  /* EXISTS  */
    EXPLAIN = 406,                 /* EXPLAIN  */
    EXPRESSION = 407,              /* EXPRESSION  */
    EXTENSION = 408,               /* EXTENSION  */
    EXTERNAL = 409,                /* EXTERNAL  */
    EXTRACT = 410,                 /* EXTRACT  */
    FALSE_P = 411,                 /* FALSE_P  */
    FAMILY = 412,                  /* FAMILY  */
    FETCH = 413,                   /* FETCH  */
    FILTER = 414,                  /* FILTER  */
    FIRST_P = 415,                 /* FIRST_P  */
    FLOAT_P = 416,                 /* FLOAT_P  */
    FOLLOWING = 417,               /* FOLLOWING  */
    FOR = 418,                     /* FOR  */
    FORCE = 419,                   /* FORCE  */
    FOREIGN = 420,                 /* FOREIGN  */
    FORWARD = 421,                 /* FORWARD  */
    FREEZE = 422,                  /* FREEZE  */
    FROM = 423,                    /* FROM  */
    FULL = 424,                    /* FULL  */
    FUNCTION = 425,                /* FUNCTION  */
    FUNCTIONS = 426,               /* FUNCTIONS  */
    GENERATED = 427,               /* GENERATED  */
    GLOBAL = 428,                  /* GLOBAL  */
    GRANT = 429,                   /* GRANT  */
    GRANTED = 430,                 /* GRANTED  */
    GREATEST = 431,                /* GREATEST  */
    GROUP_P = 432,                 /* GROUP_P  */
    GROUPING = 433,                /* GROUPING  */
    GROUPS = 434,                  /* GROUPS  */
    HANDLER = 435,                 /* HANDLER  */
    HAVING = 436,                  /* HAVING  */
    HEADER_P = 437,                /* HEADER_P  */
    HOLD = 438,                    /* HOLD  */
    HOUR_P = 439,                  /* HOUR_P  */
    IDENTITY_P = 440,              /* IDENTITY_P  */
    IF_P = 441,                    /* IF_P  */
    ILIKE = 442,                   /* ILIKE  */
    IMMEDIATE = 443,               /* IMMEDIATE  */
    IMMUTABLE = 444,               /* IMMUTABLE  */
    IMPLICIT_P = 445,              /* IMPLICIT_P  */
    IMPORT_P = 446,                /* IMPORT_P  */
    IN_P = 447,                    /* IN_P  */
    INCLUDE = 448,                 /* INCLUDE  */
    INCLUDING = 449,               /* INCLUDING  */
    INCREMENT = 450,               /* INCREMENT  */
    INDEX = 451,                   /* INDEX  */
    INDEXES = 452,                 /* INDEXES  */
    INHERIT = 453,                 /* INHERIT  */
    INHERITS = 454,                /* INHERITS  */
    INITIALLY = 455,               /* INITIALLY  */
    INLINE_P = 456,                /* INLINE_P  */
    INNER_P = 457,                 /* INNER_P  */
    INOUT = 458,                   /* INOUT  */
    INPUT_P = 459,                 /* INPUT_P  */
    INSENSITIVE = 460,             /* INSENSITIVE  */
    INSERT = 461,                  /* INSERT  */
    INSTEAD = 462,                 /* INSTEAD  */
    INT_P = 463,                   /* INT_P  */
    INTEGER = 464,                 /* INTEGER  */
    INTERSECT = 465,               /* INTERSECT  */
    INTERVAL = 466,                /* INTERVAL  */
    INTO = 467,                    /* INTO  */
    INVOKER = 468,                 /* INVOKER  */
    IS = 469,                      /* IS  */
    ISNULL = 470,                  /* ISNULL  */
    ISOLATION = 471,               /* ISOLATION  */
    JOIN = 472,                    /* JOIN  */
    KEY = 473,                     /* KEY  */
    LABEL = 474,                   /* LABEL  */
    LANGUAGE = 475,                /* LANGUAGE  */
    LARGE_P = 476,                 /* LARGE_P  */
    LAST_P = 477,                  /* LAST_P  */
    LATERAL_P = 478,               /* LATERAL_P  */
    LEADING = 479,                 /* LEADING  */
    LEAKPROOF = 480,               /* LEAKPROOF  */
    LEAST = 481,                   /* LEAST  */
    LEFT = 482,                    /* LEFT  */
    LEVEL = 483,                   /* LEVEL  */
    LIKE = 484,                    /* LIKE  */
    LIMIT = 485,                   /* LIMIT  */
    LISTEN = 486,                  /* LISTEN  */
    LOAD = 487,                    /* LOAD  */
    LOCAL = 488,                   /* LOCAL  */
    LOCALTIME = 489,               /* LOCALTIME  */
    LOCALTIMESTAMP = 490,          /* LOCALTIMESTAMP  */
    LOCATION = 491,                /* LOCATION  */
    LOCK_P = 492,                  /* LOCK_P  */
    LOCKED = 493,                  /* LOCKED  */
    LOGGED = 494,                  /* LOGGED  */
    MAPPING = 495,                 /* MAPPING  */
    MATCH = 496,                   /* MATCH  */
    MATERIALIZED = 497,            /* MATERIALIZED  */
    MAXVALUE = 498,                /* MAXVALUE  */
    METHOD = 499,                  /* METHOD  */
    MINUTE_P = 500,                /* MINUTE_P  */
    MINVALUE = 501,                /* MINVALUE  */
    MODE = 502,                    /* MODE  */
    MONTH_P = 503,                 /* MONTH_P  */
    MOVE = 504,                    /* MOVE  */
    NAME_P = 505,                  /* NAME_P  */
    NAMES = 506,                   /* NAMES  */
    NATIONAL = 507,                /* NATIONAL  */
    NATURAL = 508,                 /* NATURAL  */
    NCHAR = 509,                   /* NCHAR  */
    NEW = 510,                     /* NEW  */
    NEXT = 511,                    /* NEXT  */
    NFC = 512,                     /* NFC  */
    NFD = 513,                     /* NFD  */
    NFKC = 514,                    /* NFKC  */
    NFKD = 515,                    /* NFKD  */
    NO = 516,                      /* NO  */
    NONE = 517,                    /* NONE  */
    NORMALIZE = 518,               /* NORMALIZE  */
    NORMALIZED = 519,              /* NORMALIZED  */
    NOT = 520,                     /* NOT  */
    NOTHING = 521,                 /* NOTHING  */
    NOTIFY = 522,                  /* NOTIFY  */
    NOTNULL = 523,                 /* NOTNULL  */
    NOWAIT = 524,                  /* NOWAIT  */
    NULL_P = 525,                  /* NULL_P  */
    NULLIF = 526,                  /* NULLIF  */
    NULLS_P = 527,                 /* NULLS_P  */
    NUMERIC = 528,                 /* NUMERIC  */
    OBJECT_P = 529,                /* OBJECT_P  */
    OF = 530,                      /* OF  */
    OFF = 531,                     /* OFF  */
    OFFSET = 532,                  /* OFFSET  */
    OIDS = 533,                    /* OIDS  */
    OLD = 534,                     /* OLD  */
    ON = 535,                      /* ON  */
    ONLY = 536,                    /* ONLY  */
    OPERATOR = 537,                /* OPERATOR  */
    OPTION = 538,                  /* OPTION  */
    OPTIONS = 539,                 /* OPTIONS  */
    OR = 540,                      /* OR  */
    ORDER = 541,                   /* ORDER  */
    ORDINALITY = 542,              /* ORDINALITY  */
    OTHERS = 543,                  /* OTHERS  */
    OUT_P = 544,                   /* OUT_P  */
    OUTER_P = 545,                 /* OUTER_P  */
    OVER = 546,                    /* OVER  */
    OVERLAPS = 547,                /* OVERLAPS  */
    OVERLAY = 548,                 /* OVERLAY  */
    OVERRIDING = 549,              /* OVERRIDING  */
    OWNED = 550,                   /* OWNED  */
    OWNER = 551,                   /* OWNER  */
    PARALLEL = 552,                /* PARALLEL  */
    PARSER = 553,                  /* PARSER  */
    PARTIAL = 554,                 /* PARTIAL  */
    PARTITION = 555,               /* PARTITION  */
    PASSING = 556,                 /* PASSING  */
    PASSWORD = 557,                /* PASSWORD  */
    PLACING = 558,                 /* PLACING  */
    PLANS = 559,                   /* PLANS  */
    POLICY = 560,                  /* POLICY  */
    POSITION = 561,                /* POSITION  */
    PRECEDING = 562,               /* PRECEDING  */
    PRECISION = 563,               /* PRECISION  */
    PRESERVE = 564,                /* PRESERVE  */
    PREPARE = 565,                 /* PREPARE  */
    PREPARED = 566,                /* PREPARED  */
    PRIMARY = 567,                 /* PRIMARY  */
    PRIOR = 568,                   /* PRIOR  */
    PRIVILEGES = 569,              /* PRIVILEGES  */
    PROCEDURAL = 570,              /* PROCEDURAL  */
    PROCEDURE = 571,               /* PROCEDURE  */
    PROCEDURES = 572,              /* PROCEDURES  */
    PROGRAM = 573,                 /* PROGRAM  */
    PUBLICATION = 574,             /* PUBLICATION  */
    QUOTE = 575,                   /* QUOTE  */
    RANGE = 576,                   /* RANGE  */
    READ = 577,                    /* READ  */
    REAL = 578,                    /* REAL  */
    REASSIGN = 579,                /* REASSIGN  */
    RECHECK = 580,                 /* RECHECK  */
    RECURSIVE = 581,               /* RECURSIVE  */
    REF = 582,                     /* REF  */
    REFERENCES = 583,              /* REFERENCES  */
    REFERENCING = 584,             /* REFERENCING  */
    REFRESH = 585,                 /* REFRESH  */
    REINDEX = 586,                 /* REINDEX  */
    RELATIVE_P = 587,              /* RELATIVE_P  */
    RELEASE = 588,                 /* RELEASE  */
    RENAME = 589,                  /* RENAME  */
    REPEATABLE = 590,              /* REPEATABLE  */
    REPLACE = 591,                 /* REPLACE  */
    REPLICA = 592,                 /* REPLICA  */
    RESET = 593,                   /* RESET  */
    RESTART = 594,                 /* RESTART  */
    RESTRICT = 595,                /* RESTRICT  */
    RETURNING = 596,               /* RETURNING  */
    RETURNS = 597,                 /* RETURNS  */
    REVOKE = 598,                  /* REVOKE  */
    RIGHT = 599,                   /* RIGHT  */
    ROLE = 600,                    /* ROLE  */
    ROLLBACK = 601,                /* ROLLBACK  */
    ROLLUP = 602,                  /* ROLLUP  */
    ROUTINE = 603,                 /* ROUTINE  */
    ROUTINES = 604,                /* ROUTINES  */
    ROW = 605,                     /* ROW  */
    ROWS = 606,                    /* ROWS  */
    RULE = 607,                    /* RULE  */
    SAVEPOINT = 608,               /* SAVEPOINT  */
    SCHEMA = 609,                  /* SCHEMA  */
    SCHEMAS = 610,                 /* SCHEMAS  */
    SCROLL = 611,                  /* SCROLL  */
    SEARCH = 612,                  /* SEARCH  */
    SECOND_P = 613,                /* SECOND_P  */
    SECURITY = 614,                /* SECURITY  */
    SELECT = 615,                  /* SELECT  */
    SEQUENCE = 616,                /* SEQUENCE  */
    SEQUENCES = 617,               /* SEQUENCES  */
    SERIALIZABLE = 618,            /* SERIALIZABLE  */
    SERVER = 619,                  /* SERVER  */
    SESSION = 620,                 /* SESSION  */
    SESSION_USER = 621,            /* SESSION_USER  */
    SET = 622,                     /* SET  */
    SETS = 623,                    /* SETS  */
    SETOF = 624,                   /* SETOF  */
    SHARE = 625,                   /* SHARE  */
    SHOW = 626,                    /* SHOW  */
    SIMILAR = 627,                 /* SIMILAR  */
    SIMPLE = 628,                  /* SIMPLE  */
    SKIP = 629,                    /* SKIP  */
    SMALLINT = 630,                /* SMALLINT  */
    SNAPSHOT = 631,                /* SNAPSHOT  */
    SOME = 632,                    /* SOME  */
    SQL_P = 633,                   /* SQL_P  */
    STABLE = 634,                  /* STABLE  */
    STANDALONE_P = 635,            /* STANDALONE_P  */
    START = 636,                   /* START  */
    STATEMENT = 637,               /* STATEMENT  */
    STATISTICS = 638,              /* STATISTICS  */
    STDIN = 639,                   /* STDIN  */
    STDOUT = 640,                  /* STDOUT  */
    STORAGE = 641,                 /* STORAGE  */
    STORED = 642,                  /* STORED  */
    STRICT_P = 643,                /* STRICT_P  */
    STRIP_P = 644,                 /* STRIP_P  */
    SUBSCRIPTION = 645,            /* SUBSCRIPTION  */
    SUBSTRING = 646,               /* SUBSTRING  */
    SUPPORT = 647,                 /* SUPPORT  */
    SYMMETRIC = 648,               /* SYMMETRIC  */
    SYSID = 649,                   /* SYSID  */
    SYSTEM_P = 650,                /* SYSTEM_P  */
    TABLE = 651,                   /* TABLE  */
    TABLES = 652,                  /* TABLES  */
    TABLESAMPLE = 653,             /* TABLESAMPLE  */
    TABLESPACE = 654,              /* TABLESPACE  */
    TEMP = 655,                    /* TEMP  */
    TEMPLATE = 656,                /* TEMPLATE  */
    TEMPORARY = 657,               /* TEMPORARY  */
    TEXT_P = 658,                  /* TEXT_P  */
    THEN = 659,                    /* THEN  */
    TIES = 660,                    /* TIES  */
    TIME = 661,                    /* TIME  */
    TIMESTAMP = 662,               /* TIMESTAMP  */
    TO = 663,                      /* TO  */
    TRAILING = 664,                /* TRAILING  */
    TRANSACTION = 665,             /* TRANSACTION  */
    TRANSFORM = 666,               /* TRANSFORM  */
    TREAT = 667,                   /* TREAT  */
    TRIGGER = 668,                 /* TRIGGER  */
    TRIM = 669,                    /* TRIM  */
    TRUE_P = 670,                  /* TRUE_P  */
    TRUNCATE = 671,                /* TRUNCATE  */
    TRUSTED = 672,                 /* TRUSTED  */
    TYPE_P = 673,                  /* TYPE_P  */
    TYPES_P = 674,                 /* TYPES_P  */
    UESCAPE = 675,                 /* UESCAPE  */
    UNBOUNDED = 676,               /* UNBOUNDED  */
    UNCOMMITTED = 677,             /* UNCOMMITTED  */
    UNENCRYPTED = 678,             /* UNENCRYPTED  */
    UNION = 679,                   /* UNION  */
    UNIQUE = 680,                  /* UNIQUE  */
    UNKNOWN = 681,                 /* UNKNOWN  */
    UNLISTEN = 682,                /* UNLISTEN  */
    UNLOGGED = 683,                /* UNLOGGED  */
    UNTIL = 684,                   /* UNTIL  */
    UPDATE = 685,                  /* UPDATE  */
    USER = 686,                    /* USER  */
    USING = 687,                   /* USING  */
    VACUUM = 688,                  /* VACUUM  */
    VALID = 689,                   /* VALID  */
    VALIDATE = 690,                /* VALIDATE  */
    VALIDATOR = 691,               /* VALIDATOR  */
    VALUE_P = 692,                 /* VALUE_P  */
    VALUES = 693,                  /* VALUES  */
    VARCHAR = 694,                 /* VARCHAR  */
    VARIADIC = 695,                /* VARIADIC  */
    VARYING = 696,                 /* VARYING  */
    VERBOSE = 697,                 /* VERBOSE  */
    VERSION_P = 698,               /* VERSION_P  */
    VIEW = 699,                    /* VIEW  */
    VIEWS = 700,                   /* VIEWS  */
    VOLATILE = 701,                /* VOLATILE  */
    WHEN = 702,                    /* WHEN  */
    WHERE = 703,                   /* WHERE  */
    WHITESPACE_P = 704,            /* WHITESPACE_P  */
    WINDOW = 705,                  /* WINDOW  */
    WITH = 706,                    /* WITH  */
    WITHIN = 707,                  /* WITHIN  */
    WITHOUT = 708,                 /* WITHOUT  */
    WORK = 709,                    /* WORK  */
    WRAPPER = 710,                 /* WRAPPER  */
    WRITE = 711,                   /* WRITE  */
    XML_P = 712,                   /* XML_P  */
    XMLATTRIBUTES = 713,           /* XMLATTRIBUTES  */
    XMLCONCAT = 714,               /* XMLCONCAT  */
    XMLELEMENT = 715,              /* XMLELEMENT  */
    XMLEXISTS = 716,               /* XMLEXISTS  */
    XMLFOREST = 717,               /* XMLFOREST  */
    XMLNAMESPACES = 718,           /* XMLNAMESPACES  */
    XMLPARSE = 719,                /* XMLPARSE  */
    XMLPI = 720,                   /* XMLPI  */
    XMLROOT = 721,                 /* XMLROOT  */
    XMLSERIALIZE = 722,            /* XMLSERIALIZE  */
    XMLTABLE = 723,                /* XMLTABLE  */
    YEAR_P = 724,                  /* YEAR_P  */
    YES_P = 725,                   /* YES_P  */
    ZONE = 726,                    /* ZONE  */
    NOT_LA = 727,                  /* NOT_LA  */
    NULLS_LA = 728,                /* NULLS_LA  */
    WITH_LA = 729,                 /* WITH_LA  */
    POSTFIXOP = 730,               /* POSTFIXOP  */
    UMINUS = 731                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 214 "gram.y"

	core_YYSTYPE		core_yystype;
	/* these fields must match core_YYSTYPE: */
	int					ival;
	char				*str;
	const char			*keyword;

	char				chr;
	bool				boolean;
	JoinType			jtype;
	DropBehavior		dbehavior;
	OnCommitAction		oncommit;
	List				*list;
	Node				*node;
	Value				*value;
	ObjectType			objtype;
	TypeName			*typnam;
	FunctionParameter   *fun_param;
	FunctionParameterMode fun_param_mode;
	ObjectWithArgs		*objwithargs;
	DefElem				*defelt;
	SortBy				*sortby;
	WindowDef			*windef;
	JoinExpr			*jexpr;
	IndexElem			*ielem;
	Alias				*alias;
	RangeVar			*range;
	IntoClause			*into;
	WithClause			*with;
	InferClause			*infer;
	OnConflictClause	*onconflict;
	A_Indices			*aind;
	ResTarget			*target;
	struct PrivTarget	*privtarget;
	AccessPriv			*accesspriv;
	struct ImportQual	*importqual;
	InsertStmt			*istmt;
	VariableSetStmt		*vsetstmt;
	PartitionElem		*partelem;
	PartitionSpec		*partspec;
	PartitionBoundSpec	*partboundspec;
	RoleSpec			*rolespec;
	struct SelectLimit	*selectlimit;

#line 585 "gram.h"

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




int base_yyparse (core_yyscan_t yyscanner);


#endif /* !YY_BASE_YY_GRAM_H_INCLUDED  */
