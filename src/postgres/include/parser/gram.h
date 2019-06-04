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

#ifndef YY_BASE_YY_GRAM_H_INCLUDED
# define YY_BASE_YY_GRAM_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int base_yydebug;
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
    ABORT_P = 273,
    ABSOLUTE_P = 274,
    ACCESS = 275,
    ACTION = 276,
    ADD_P = 277,
    ADMIN = 278,
    AFTER = 279,
    AGGREGATE = 280,
    ALL = 281,
    ALSO = 282,
    ALTER = 283,
    ALWAYS = 284,
    ANALYSE = 285,
    ANALYZE = 286,
    AND = 287,
    ANY = 288,
    ARRAY = 289,
    AS = 290,
    ASC = 291,
    ASSERTION = 292,
    ASSIGNMENT = 293,
    ASYMMETRIC = 294,
    AT = 295,
    ATTACH = 296,
    ATTRIBUTE = 297,
    AUTHORIZATION = 298,
    BACKWARD = 299,
    BEFORE = 300,
    BEGIN_P = 301,
    BETWEEN = 302,
    BIGINT = 303,
    BINARY = 304,
    BIT = 305,
    BOOLEAN_P = 306,
    BOTH = 307,
    BY = 308,
    CACHE = 309,
    CALL = 310,
    CALLED = 311,
    CASCADE = 312,
    CASCADED = 313,
    CASE = 314,
    CAST = 315,
    CATALOG_P = 316,
    CHAIN = 317,
    CHAR_P = 318,
    CHARACTER = 319,
    CHARACTERISTICS = 320,
    CHECK = 321,
    CHECKPOINT = 322,
    CLASS = 323,
    CLOSE = 324,
    CLUSTER = 325,
    COALESCE = 326,
    COLLATE = 327,
    COLLATION = 328,
    COLUMN = 329,
    COLUMNS = 330,
    COMMENT = 331,
    COMMENTS = 332,
    COMMIT = 333,
    COMMITTED = 334,
    CONCURRENTLY = 335,
    CONFIGURATION = 336,
    CONFLICT = 337,
    CONNECTION = 338,
    CONSTRAINT = 339,
    CONSTRAINTS = 340,
    CONTENT_P = 341,
    CONTINUE_P = 342,
    CONVERSION_P = 343,
    COPY = 344,
    COST = 345,
    CREATE = 346,
    CROSS = 347,
    CSV = 348,
    CUBE = 349,
    CURRENT_P = 350,
    CURRENT_CATALOG = 351,
    CURRENT_DATE = 352,
    CURRENT_ROLE = 353,
    CURRENT_SCHEMA = 354,
    CURRENT_TIME = 355,
    CURRENT_TIMESTAMP = 356,
    CURRENT_USER = 357,
    CURSOR = 358,
    CYCLE = 359,
    DATA_P = 360,
    DATABASE = 361,
    DAY_P = 362,
    DEALLOCATE = 363,
    DEC = 364,
    DECIMAL_P = 365,
    DECLARE = 366,
    DEFAULT = 367,
    DEFAULTS = 368,
    DEFERRABLE = 369,
    DEFERRED = 370,
    DEFINER = 371,
    DELETE_P = 372,
    DELIMITER = 373,
    DELIMITERS = 374,
    DEPENDS = 375,
    DESC = 376,
    DETACH = 377,
    DICTIONARY = 378,
    DISABLE_P = 379,
    DISCARD = 380,
    DISTINCT = 381,
    DO = 382,
    DOCUMENT_P = 383,
    DOMAIN_P = 384,
    DOUBLE_P = 385,
    DROP = 386,
    EACH = 387,
    ELSE = 388,
    ENABLE_P = 389,
    ENCODING = 390,
    ENCRYPTED = 391,
    END_P = 392,
    ENUM_P = 393,
    ESCAPE = 394,
    EVENT = 395,
    EXCEPT = 396,
    EXCLUDE = 397,
    EXCLUDING = 398,
    EXCLUSIVE = 399,
    EXECUTE = 400,
    EXISTS = 401,
    EXPLAIN = 402,
    EXTENSION = 403,
    EXTERNAL = 404,
    EXTRACT = 405,
    FALSE_P = 406,
    FAMILY = 407,
    FETCH = 408,
    FILTER = 409,
    FIRST_P = 410,
    FLOAT_P = 411,
    FOLLOWING = 412,
    FOR = 413,
    FORCE = 414,
    FOREIGN = 415,
    FORWARD = 416,
    FREEZE = 417,
    FROM = 418,
    FULL = 419,
    FUNCTION = 420,
    FUNCTIONS = 421,
    GENERATED = 422,
    GLOBAL = 423,
    GRANT = 424,
    GRANTED = 425,
    GREATEST = 426,
    GROUP_P = 427,
    GROUPING = 428,
    GROUPS = 429,
    HANDLER = 430,
    HAVING = 431,
    HEADER_P = 432,
    HOLD = 433,
    HOUR_P = 434,
    IDENTITY_P = 435,
    IF_P = 436,
    ILIKE = 437,
    IMMEDIATE = 438,
    IMMUTABLE = 439,
    IMPLICIT_P = 440,
    IMPORT_P = 441,
    IN_P = 442,
    INCLUDE = 443,
    INCLUDING = 444,
    INCREMENT = 445,
    INDEX = 446,
    INDEXES = 447,
    INHERIT = 448,
    INHERITS = 449,
    INITIALLY = 450,
    INLINE_P = 451,
    INNER_P = 452,
    INOUT = 453,
    INPUT_P = 454,
    INSENSITIVE = 455,
    INSERT = 456,
    INSTEAD = 457,
    INT_P = 458,
    INTEGER = 459,
    INTERSECT = 460,
    INTERVAL = 461,
    INTO = 462,
    INVOKER = 463,
    IS = 464,
    ISNULL = 465,
    ISOLATION = 466,
    JOIN = 467,
    KEY = 468,
    LABEL = 469,
    LANGUAGE = 470,
    LARGE_P = 471,
    LAST_P = 472,
    LATERAL_P = 473,
    LEADING = 474,
    LEAKPROOF = 475,
    LEAST = 476,
    LEFT = 477,
    LEVEL = 478,
    LIKE = 479,
    LIMIT = 480,
    LISTEN = 481,
    LOAD = 482,
    LOCAL = 483,
    LOCALTIME = 484,
    LOCALTIMESTAMP = 485,
    LOCATION = 486,
    LOCK_P = 487,
    LOCKED = 488,
    LOGGED = 489,
    MAPPING = 490,
    MATCH = 491,
    MATERIALIZED = 492,
    MAXVALUE = 493,
    METHOD = 494,
    MINUTE_P = 495,
    MINVALUE = 496,
    MODE = 497,
    MONTH_P = 498,
    MOVE = 499,
    NAME_P = 500,
    NAMES = 501,
    NATIONAL = 502,
    NATURAL = 503,
    NCHAR = 504,
    NEW = 505,
    NEXT = 506,
    NO = 507,
    NONE = 508,
    NOT = 509,
    NOTHING = 510,
    NOTIFY = 511,
    NOTNULL = 512,
    NOWAIT = 513,
    NULL_P = 514,
    NULLIF = 515,
    NULLS_P = 516,
    NUMERIC = 517,
    OBJECT_P = 518,
    OF = 519,
    OFF = 520,
    OFFSET = 521,
    OIDS = 522,
    OLD = 523,
    ON = 524,
    ONLY = 525,
    OPERATOR = 526,
    OPTION = 527,
    OPTIONS = 528,
    OR = 529,
    ORDER = 530,
    ORDINALITY = 531,
    OTHERS = 532,
    OUT_P = 533,
    OUTER_P = 534,
    OVER = 535,
    OVERLAPS = 536,
    OVERLAY = 537,
    OVERRIDING = 538,
    OWNED = 539,
    OWNER = 540,
    PARALLEL = 541,
    PARSER = 542,
    PARTIAL = 543,
    PARTITION = 544,
    PASSING = 545,
    PASSWORD = 546,
    PLACING = 547,
    PLANS = 548,
    POLICY = 549,
    POSITION = 550,
    PRECEDING = 551,
    PRECISION = 552,
    PRESERVE = 553,
    PREPARE = 554,
    PREPARED = 555,
    PRIMARY = 556,
    PRIOR = 557,
    PRIVILEGES = 558,
    PROCEDURAL = 559,
    PROCEDURE = 560,
    PROCEDURES = 561,
    PROGRAM = 562,
    PUBLICATION = 563,
    QUOTE = 564,
    RANGE = 565,
    READ = 566,
    REAL = 567,
    REASSIGN = 568,
    RECHECK = 569,
    RECURSIVE = 570,
    REF = 571,
    REFERENCES = 572,
    REFERENCING = 573,
    REFRESH = 574,
    REINDEX = 575,
    RELATIVE_P = 576,
    RELEASE = 577,
    RENAME = 578,
    REPEATABLE = 579,
    REPLACE = 580,
    REPLICA = 581,
    RESET = 582,
    RESTART = 583,
    RESTRICT = 584,
    RETURNING = 585,
    RETURNS = 586,
    REVOKE = 587,
    RIGHT = 588,
    ROLE = 589,
    ROLLBACK = 590,
    ROLLUP = 591,
    ROUTINE = 592,
    ROUTINES = 593,
    ROW = 594,
    ROWS = 595,
    RULE = 596,
    SAVEPOINT = 597,
    SCHEMA = 598,
    SCHEMAS = 599,
    SCROLL = 600,
    SEARCH = 601,
    SECOND_P = 602,
    SECURITY = 603,
    SELECT = 604,
    SEQUENCE = 605,
    SEQUENCES = 606,
    SERIALIZABLE = 607,
    SERVER = 608,
    SESSION = 609,
    SESSION_USER = 610,
    SET = 611,
    SETS = 612,
    SETOF = 613,
    SHARE = 614,
    SHOW = 615,
    SIMILAR = 616,
    SIMPLE = 617,
    SKIP = 618,
    SMALLINT = 619,
    SNAPSHOT = 620,
    SOME = 621,
    SQL_P = 622,
    STABLE = 623,
    STANDALONE_P = 624,
    START = 625,
    STATEMENT = 626,
    STATISTICS = 627,
    STDIN = 628,
    STDOUT = 629,
    STORAGE = 630,
    STRICT_P = 631,
    STRIP_P = 632,
    SUBSCRIPTION = 633,
    SUBSTRING = 634,
    SYMMETRIC = 635,
    SYSID = 636,
    SYSTEM_P = 637,
    TABLE = 638,
    TABLES = 639,
    TABLESAMPLE = 640,
    TABLESPACE = 641,
    TEMP = 642,
    TEMPLATE = 643,
    TEMPORARY = 644,
    TEXT_P = 645,
    THEN = 646,
    TIES = 647,
    TIME = 648,
    TIMESTAMP = 649,
    TO = 650,
    TRAILING = 651,
    TRANSACTION = 652,
    TRANSFORM = 653,
    TREAT = 654,
    TRIGGER = 655,
    TRIM = 656,
    TRUE_P = 657,
    TRUNCATE = 658,
    TRUSTED = 659,
    TYPE_P = 660,
    TYPES_P = 661,
    UNBOUNDED = 662,
    UNCOMMITTED = 663,
    UNENCRYPTED = 664,
    UNION = 665,
    UNIQUE = 666,
    UNKNOWN = 667,
    UNLISTEN = 668,
    UNLOGGED = 669,
    UNTIL = 670,
    UPDATE = 671,
    USER = 672,
    USING = 673,
    VACUUM = 674,
    VALID = 675,
    VALIDATE = 676,
    VALIDATOR = 677,
    VALUE_P = 678,
    VALUES = 679,
    VARCHAR = 680,
    VARIADIC = 681,
    VARYING = 682,
    VERBOSE = 683,
    VERSION_P = 684,
    VIEW = 685,
    VIEWS = 686,
    VOLATILE = 687,
    WHEN = 688,
    WHERE = 689,
    WHITESPACE_P = 690,
    WINDOW = 691,
    WITH = 692,
    WITHIN = 693,
    WITHOUT = 694,
    WORK = 695,
    WRAPPER = 696,
    WRITE = 697,
    XML_P = 698,
    XMLATTRIBUTES = 699,
    XMLCONCAT = 700,
    XMLELEMENT = 701,
    XMLEXISTS = 702,
    XMLFOREST = 703,
    XMLNAMESPACES = 704,
    XMLPARSE = 705,
    XMLPI = 706,
    XMLROOT = 707,
    XMLSERIALIZE = 708,
    XMLTABLE = 709,
    YEAR_P = 710,
    YES_P = 711,
    ZONE = 712,
    NOT_LA = 713,
    NULLS_LA = 714,
    WITH_LA = 715,
    POSTFIXOP = 716,
    UMINUS = 717
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 205 "gram.y" /* yacc.c:1909  */

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

#line 561 "gram.h" /* yacc.c:1909  */
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
