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
    ASENSITIVE = 296,              /* ASENSITIVE  */
    ASSERTION = 297,               /* ASSERTION  */
    ASSIGNMENT = 298,              /* ASSIGNMENT  */
    ASYMMETRIC = 299,              /* ASYMMETRIC  */
    ATOMIC = 300,                  /* ATOMIC  */
    AT = 301,                      /* AT  */
    ATTACH = 302,                  /* ATTACH  */
    ATTRIBUTE = 303,               /* ATTRIBUTE  */
    AUTHORIZATION = 304,           /* AUTHORIZATION  */
    BACKWARD = 305,                /* BACKWARD  */
    BEFORE = 306,                  /* BEFORE  */
    BEGIN_P = 307,                 /* BEGIN_P  */
    BETWEEN = 308,                 /* BETWEEN  */
    BIGINT = 309,                  /* BIGINT  */
    BINARY = 310,                  /* BINARY  */
    BIT = 311,                     /* BIT  */
    BOOLEAN_P = 312,               /* BOOLEAN_P  */
    BOTH = 313,                    /* BOTH  */
    BREADTH = 314,                 /* BREADTH  */
    BY = 315,                      /* BY  */
    CACHE = 316,                   /* CACHE  */
    CALL = 317,                    /* CALL  */
    CALLED = 318,                  /* CALLED  */
    CASCADE = 319,                 /* CASCADE  */
    CASCADED = 320,                /* CASCADED  */
    CASE = 321,                    /* CASE  */
    CAST = 322,                    /* CAST  */
    CATALOG_P = 323,               /* CATALOG_P  */
    CHAIN = 324,                   /* CHAIN  */
    CHAR_P = 325,                  /* CHAR_P  */
    CHARACTER = 326,               /* CHARACTER  */
    CHARACTERISTICS = 327,         /* CHARACTERISTICS  */
    CHECK = 328,                   /* CHECK  */
    CHECKPOINT = 329,              /* CHECKPOINT  */
    CLASS = 330,                   /* CLASS  */
    CLOSE = 331,                   /* CLOSE  */
    CLUSTER = 332,                 /* CLUSTER  */
    COALESCE = 333,                /* COALESCE  */
    COLLATE = 334,                 /* COLLATE  */
    COLLATION = 335,               /* COLLATION  */
    COLUMN = 336,                  /* COLUMN  */
    COLUMNS = 337,                 /* COLUMNS  */
    COMMENT = 338,                 /* COMMENT  */
    COMMENTS = 339,                /* COMMENTS  */
    COMMIT = 340,                  /* COMMIT  */
    COMMITTED = 341,               /* COMMITTED  */
    COMPRESSION = 342,             /* COMPRESSION  */
    CONCURRENTLY = 343,            /* CONCURRENTLY  */
    CONFIGURATION = 344,           /* CONFIGURATION  */
    CONFLICT = 345,                /* CONFLICT  */
    CONNECTION = 346,              /* CONNECTION  */
    CONSTRAINT = 347,              /* CONSTRAINT  */
    CONSTRAINTS = 348,             /* CONSTRAINTS  */
    CONTENT_P = 349,               /* CONTENT_P  */
    CONTINUE_P = 350,              /* CONTINUE_P  */
    CONVERSION_P = 351,            /* CONVERSION_P  */
    COPY = 352,                    /* COPY  */
    COST = 353,                    /* COST  */
    CREATE = 354,                  /* CREATE  */
    CROSS = 355,                   /* CROSS  */
    CSV = 356,                     /* CSV  */
    CUBE = 357,                    /* CUBE  */
    CURRENT_P = 358,               /* CURRENT_P  */
    CURRENT_CATALOG = 359,         /* CURRENT_CATALOG  */
    CURRENT_DATE = 360,            /* CURRENT_DATE  */
    CURRENT_ROLE = 361,            /* CURRENT_ROLE  */
    CURRENT_SCHEMA = 362,          /* CURRENT_SCHEMA  */
    CURRENT_TIME = 363,            /* CURRENT_TIME  */
    CURRENT_TIMESTAMP = 364,       /* CURRENT_TIMESTAMP  */
    CURRENT_USER = 365,            /* CURRENT_USER  */
    CURSOR = 366,                  /* CURSOR  */
    CYCLE = 367,                   /* CYCLE  */
    DATA_P = 368,                  /* DATA_P  */
    DATABASE = 369,                /* DATABASE  */
    DAY_P = 370,                   /* DAY_P  */
    DEALLOCATE = 371,              /* DEALLOCATE  */
    DEC = 372,                     /* DEC  */
    DECIMAL_P = 373,               /* DECIMAL_P  */
    DECLARE = 374,                 /* DECLARE  */
    DEFAULT = 375,                 /* DEFAULT  */
    DEFAULTS = 376,                /* DEFAULTS  */
    DEFERRABLE = 377,              /* DEFERRABLE  */
    DEFERRED = 378,                /* DEFERRED  */
    DEFINER = 379,                 /* DEFINER  */
    DELETE_P = 380,                /* DELETE_P  */
    DELIMITER = 381,               /* DELIMITER  */
    DELIMITERS = 382,              /* DELIMITERS  */
    DEPENDS = 383,                 /* DEPENDS  */
    DEPTH = 384,                   /* DEPTH  */
    DESC = 385,                    /* DESC  */
    DETACH = 386,                  /* DETACH  */
    DICTIONARY = 387,              /* DICTIONARY  */
    DISABLE_P = 388,               /* DISABLE_P  */
    DISCARD = 389,                 /* DISCARD  */
    DISTINCT = 390,                /* DISTINCT  */
    DO = 391,                      /* DO  */
    DOCUMENT_P = 392,              /* DOCUMENT_P  */
    DOMAIN_P = 393,                /* DOMAIN_P  */
    DOUBLE_P = 394,                /* DOUBLE_P  */
    DROP = 395,                    /* DROP  */
    EACH = 396,                    /* EACH  */
    ELSE = 397,                    /* ELSE  */
    ENABLE_P = 398,                /* ENABLE_P  */
    ENCODING = 399,                /* ENCODING  */
    ENCRYPTED = 400,               /* ENCRYPTED  */
    END_P = 401,                   /* END_P  */
    ENUM_P = 402,                  /* ENUM_P  */
    ESCAPE = 403,                  /* ESCAPE  */
    EVENT = 404,                   /* EVENT  */
    EXCEPT = 405,                  /* EXCEPT  */
    EXCLUDE = 406,                 /* EXCLUDE  */
    EXCLUDING = 407,               /* EXCLUDING  */
    EXCLUSIVE = 408,               /* EXCLUSIVE  */
    EXECUTE = 409,                 /* EXECUTE  */
    EXISTS = 410,                  /* EXISTS  */
    EXPLAIN = 411,                 /* EXPLAIN  */
    EXPRESSION = 412,              /* EXPRESSION  */
    EXTENSION = 413,               /* EXTENSION  */
    EXTERNAL = 414,                /* EXTERNAL  */
    EXTRACT = 415,                 /* EXTRACT  */
    FALSE_P = 416,                 /* FALSE_P  */
    FAMILY = 417,                  /* FAMILY  */
    FETCH = 418,                   /* FETCH  */
    FILTER = 419,                  /* FILTER  */
    FINALIZE = 420,                /* FINALIZE  */
    FIRST_P = 421,                 /* FIRST_P  */
    FLOAT_P = 422,                 /* FLOAT_P  */
    FOLLOWING = 423,               /* FOLLOWING  */
    FOR = 424,                     /* FOR  */
    FORCE = 425,                   /* FORCE  */
    FOREIGN = 426,                 /* FOREIGN  */
    FORWARD = 427,                 /* FORWARD  */
    FREEZE = 428,                  /* FREEZE  */
    FROM = 429,                    /* FROM  */
    FULL = 430,                    /* FULL  */
    FUNCTION = 431,                /* FUNCTION  */
    FUNCTIONS = 432,               /* FUNCTIONS  */
    GENERATED = 433,               /* GENERATED  */
    GLOBAL = 434,                  /* GLOBAL  */
    GRANT = 435,                   /* GRANT  */
    GRANTED = 436,                 /* GRANTED  */
    GREATEST = 437,                /* GREATEST  */
    GROUP_P = 438,                 /* GROUP_P  */
    GROUPING = 439,                /* GROUPING  */
    GROUPS = 440,                  /* GROUPS  */
    HANDLER = 441,                 /* HANDLER  */
    HAVING = 442,                  /* HAVING  */
    HEADER_P = 443,                /* HEADER_P  */
    HOLD = 444,                    /* HOLD  */
    HOUR_P = 445,                  /* HOUR_P  */
    IDENTITY_P = 446,              /* IDENTITY_P  */
    IF_P = 447,                    /* IF_P  */
    ILIKE = 448,                   /* ILIKE  */
    IMMEDIATE = 449,               /* IMMEDIATE  */
    IMMUTABLE = 450,               /* IMMUTABLE  */
    IMPLICIT_P = 451,              /* IMPLICIT_P  */
    IMPORT_P = 452,                /* IMPORT_P  */
    IN_P = 453,                    /* IN_P  */
    INCLUDE = 454,                 /* INCLUDE  */
    INCLUDING = 455,               /* INCLUDING  */
    INCREMENT = 456,               /* INCREMENT  */
    INDEX = 457,                   /* INDEX  */
    INDEXES = 458,                 /* INDEXES  */
    INHERIT = 459,                 /* INHERIT  */
    INHERITS = 460,                /* INHERITS  */
    INITIALLY = 461,               /* INITIALLY  */
    INLINE_P = 462,                /* INLINE_P  */
    INNER_P = 463,                 /* INNER_P  */
    INOUT = 464,                   /* INOUT  */
    INPUT_P = 465,                 /* INPUT_P  */
    INSENSITIVE = 466,             /* INSENSITIVE  */
    INSERT = 467,                  /* INSERT  */
    INSTEAD = 468,                 /* INSTEAD  */
    INT_P = 469,                   /* INT_P  */
    INTEGER = 470,                 /* INTEGER  */
    INTERSECT = 471,               /* INTERSECT  */
    INTERVAL = 472,                /* INTERVAL  */
    INTO = 473,                    /* INTO  */
    INVOKER = 474,                 /* INVOKER  */
    IS = 475,                      /* IS  */
    ISNULL = 476,                  /* ISNULL  */
    ISOLATION = 477,               /* ISOLATION  */
    JOIN = 478,                    /* JOIN  */
    KEY = 479,                     /* KEY  */
    LABEL = 480,                   /* LABEL  */
    LANGUAGE = 481,                /* LANGUAGE  */
    LARGE_P = 482,                 /* LARGE_P  */
    LAST_P = 483,                  /* LAST_P  */
    LATERAL_P = 484,               /* LATERAL_P  */
    LEADING = 485,                 /* LEADING  */
    LEAKPROOF = 486,               /* LEAKPROOF  */
    LEAST = 487,                   /* LEAST  */
    LEFT = 488,                    /* LEFT  */
    LEVEL = 489,                   /* LEVEL  */
    LIKE = 490,                    /* LIKE  */
    LIMIT = 491,                   /* LIMIT  */
    LISTEN = 492,                  /* LISTEN  */
    LOAD = 493,                    /* LOAD  */
    LOCAL = 494,                   /* LOCAL  */
    LOCALTIME = 495,               /* LOCALTIME  */
    LOCALTIMESTAMP = 496,          /* LOCALTIMESTAMP  */
    LOCATION = 497,                /* LOCATION  */
    LOCK_P = 498,                  /* LOCK_P  */
    LOCKED = 499,                  /* LOCKED  */
    LOGGED = 500,                  /* LOGGED  */
    MAPPING = 501,                 /* MAPPING  */
    MATCH = 502,                   /* MATCH  */
    MATERIALIZED = 503,            /* MATERIALIZED  */
    MAXVALUE = 504,                /* MAXVALUE  */
    METHOD = 505,                  /* METHOD  */
    MINUTE_P = 506,                /* MINUTE_P  */
    MINVALUE = 507,                /* MINVALUE  */
    MODE = 508,                    /* MODE  */
    MONTH_P = 509,                 /* MONTH_P  */
    MOVE = 510,                    /* MOVE  */
    NAME_P = 511,                  /* NAME_P  */
    NAMES = 512,                   /* NAMES  */
    NATIONAL = 513,                /* NATIONAL  */
    NATURAL = 514,                 /* NATURAL  */
    NCHAR = 515,                   /* NCHAR  */
    NEW = 516,                     /* NEW  */
    NEXT = 517,                    /* NEXT  */
    NFC = 518,                     /* NFC  */
    NFD = 519,                     /* NFD  */
    NFKC = 520,                    /* NFKC  */
    NFKD = 521,                    /* NFKD  */
    NO = 522,                      /* NO  */
    NONE = 523,                    /* NONE  */
    NORMALIZE = 524,               /* NORMALIZE  */
    NORMALIZED = 525,              /* NORMALIZED  */
    NOT = 526,                     /* NOT  */
    NOTHING = 527,                 /* NOTHING  */
    NOTIFY = 528,                  /* NOTIFY  */
    NOTNULL = 529,                 /* NOTNULL  */
    NOWAIT = 530,                  /* NOWAIT  */
    NULL_P = 531,                  /* NULL_P  */
    NULLIF = 532,                  /* NULLIF  */
    NULLS_P = 533,                 /* NULLS_P  */
    NUMERIC = 534,                 /* NUMERIC  */
    OBJECT_P = 535,                /* OBJECT_P  */
    OF = 536,                      /* OF  */
    OFF = 537,                     /* OFF  */
    OFFSET = 538,                  /* OFFSET  */
    OIDS = 539,                    /* OIDS  */
    OLD = 540,                     /* OLD  */
    ON = 541,                      /* ON  */
    ONLY = 542,                    /* ONLY  */
    OPERATOR = 543,                /* OPERATOR  */
    OPTION = 544,                  /* OPTION  */
    OPTIONS = 545,                 /* OPTIONS  */
    OR = 546,                      /* OR  */
    ORDER = 547,                   /* ORDER  */
    ORDINALITY = 548,              /* ORDINALITY  */
    OTHERS = 549,                  /* OTHERS  */
    OUT_P = 550,                   /* OUT_P  */
    OUTER_P = 551,                 /* OUTER_P  */
    OVER = 552,                    /* OVER  */
    OVERLAPS = 553,                /* OVERLAPS  */
    OVERLAY = 554,                 /* OVERLAY  */
    OVERRIDING = 555,              /* OVERRIDING  */
    OWNED = 556,                   /* OWNED  */
    OWNER = 557,                   /* OWNER  */
    PARALLEL = 558,                /* PARALLEL  */
    PARSER = 559,                  /* PARSER  */
    PARTIAL = 560,                 /* PARTIAL  */
    PARTITION = 561,               /* PARTITION  */
    PASSING = 562,                 /* PASSING  */
    PASSWORD = 563,                /* PASSWORD  */
    PLACING = 564,                 /* PLACING  */
    PLANS = 565,                   /* PLANS  */
    POLICY = 566,                  /* POLICY  */
    POSITION = 567,                /* POSITION  */
    PRECEDING = 568,               /* PRECEDING  */
    PRECISION = 569,               /* PRECISION  */
    PRESERVE = 570,                /* PRESERVE  */
    PREPARE = 571,                 /* PREPARE  */
    PREPARED = 572,                /* PREPARED  */
    PRIMARY = 573,                 /* PRIMARY  */
    PRIOR = 574,                   /* PRIOR  */
    PRIVILEGES = 575,              /* PRIVILEGES  */
    PROCEDURAL = 576,              /* PROCEDURAL  */
    PROCEDURE = 577,               /* PROCEDURE  */
    PROCEDURES = 578,              /* PROCEDURES  */
    PROGRAM = 579,                 /* PROGRAM  */
    PUBLICATION = 580,             /* PUBLICATION  */
    QUOTE = 581,                   /* QUOTE  */
    RANGE = 582,                   /* RANGE  */
    READ = 583,                    /* READ  */
    REAL = 584,                    /* REAL  */
    REASSIGN = 585,                /* REASSIGN  */
    RECHECK = 586,                 /* RECHECK  */
    RECURSIVE = 587,               /* RECURSIVE  */
    REF = 588,                     /* REF  */
    REFERENCES = 589,              /* REFERENCES  */
    REFERENCING = 590,             /* REFERENCING  */
    REFRESH = 591,                 /* REFRESH  */
    REINDEX = 592,                 /* REINDEX  */
    RELATIVE_P = 593,              /* RELATIVE_P  */
    RELEASE = 594,                 /* RELEASE  */
    RENAME = 595,                  /* RENAME  */
    REPEATABLE = 596,              /* REPEATABLE  */
    REPLACE = 597,                 /* REPLACE  */
    REPLICA = 598,                 /* REPLICA  */
    RESET = 599,                   /* RESET  */
    RESTART = 600,                 /* RESTART  */
    RESTRICT = 601,                /* RESTRICT  */
    RETURN = 602,                  /* RETURN  */
    RETURNING = 603,               /* RETURNING  */
    RETURNS = 604,                 /* RETURNS  */
    REVOKE = 605,                  /* REVOKE  */
    RIGHT = 606,                   /* RIGHT  */
    ROLE = 607,                    /* ROLE  */
    ROLLBACK = 608,                /* ROLLBACK  */
    ROLLUP = 609,                  /* ROLLUP  */
    ROUTINE = 610,                 /* ROUTINE  */
    ROUTINES = 611,                /* ROUTINES  */
    ROW = 612,                     /* ROW  */
    ROWS = 613,                    /* ROWS  */
    RULE = 614,                    /* RULE  */
    SAVEPOINT = 615,               /* SAVEPOINT  */
    SCHEMA = 616,                  /* SCHEMA  */
    SCHEMAS = 617,                 /* SCHEMAS  */
    SCROLL = 618,                  /* SCROLL  */
    SEARCH = 619,                  /* SEARCH  */
    SECOND_P = 620,                /* SECOND_P  */
    SECURITY = 621,                /* SECURITY  */
    SELECT = 622,                  /* SELECT  */
    SEQUENCE = 623,                /* SEQUENCE  */
    SEQUENCES = 624,               /* SEQUENCES  */
    SERIALIZABLE = 625,            /* SERIALIZABLE  */
    SERVER = 626,                  /* SERVER  */
    SESSION = 627,                 /* SESSION  */
    SESSION_USER = 628,            /* SESSION_USER  */
    SET = 629,                     /* SET  */
    SETS = 630,                    /* SETS  */
    SETOF = 631,                   /* SETOF  */
    SHARE = 632,                   /* SHARE  */
    SHOW = 633,                    /* SHOW  */
    SIMILAR = 634,                 /* SIMILAR  */
    SIMPLE = 635,                  /* SIMPLE  */
    SKIP = 636,                    /* SKIP  */
    SMALLINT = 637,                /* SMALLINT  */
    SNAPSHOT = 638,                /* SNAPSHOT  */
    SOME = 639,                    /* SOME  */
    SQL_P = 640,                   /* SQL_P  */
    STABLE = 641,                  /* STABLE  */
    STANDALONE_P = 642,            /* STANDALONE_P  */
    START = 643,                   /* START  */
    STATEMENT = 644,               /* STATEMENT  */
    STATISTICS = 645,              /* STATISTICS  */
    STDIN = 646,                   /* STDIN  */
    STDOUT = 647,                  /* STDOUT  */
    STORAGE = 648,                 /* STORAGE  */
    STORED = 649,                  /* STORED  */
    STRICT_P = 650,                /* STRICT_P  */
    STRIP_P = 651,                 /* STRIP_P  */
    SUBSCRIPTION = 652,            /* SUBSCRIPTION  */
    SUBSTRING = 653,               /* SUBSTRING  */
    SUPPORT = 654,                 /* SUPPORT  */
    SYMMETRIC = 655,               /* SYMMETRIC  */
    SYSID = 656,                   /* SYSID  */
    SYSTEM_P = 657,                /* SYSTEM_P  */
    TABLE = 658,                   /* TABLE  */
    TABLES = 659,                  /* TABLES  */
    TABLESAMPLE = 660,             /* TABLESAMPLE  */
    TABLESPACE = 661,              /* TABLESPACE  */
    TEMP = 662,                    /* TEMP  */
    TEMPLATE = 663,                /* TEMPLATE  */
    TEMPORARY = 664,               /* TEMPORARY  */
    TEXT_P = 665,                  /* TEXT_P  */
    THEN = 666,                    /* THEN  */
    TIES = 667,                    /* TIES  */
    TIME = 668,                    /* TIME  */
    TIMESTAMP = 669,               /* TIMESTAMP  */
    TO = 670,                      /* TO  */
    TRAILING = 671,                /* TRAILING  */
    TRANSACTION = 672,             /* TRANSACTION  */
    TRANSFORM = 673,               /* TRANSFORM  */
    TREAT = 674,                   /* TREAT  */
    TRIGGER = 675,                 /* TRIGGER  */
    TRIM = 676,                    /* TRIM  */
    TRUE_P = 677,                  /* TRUE_P  */
    TRUNCATE = 678,                /* TRUNCATE  */
    TRUSTED = 679,                 /* TRUSTED  */
    TYPE_P = 680,                  /* TYPE_P  */
    TYPES_P = 681,                 /* TYPES_P  */
    UESCAPE = 682,                 /* UESCAPE  */
    UNBOUNDED = 683,               /* UNBOUNDED  */
    UNCOMMITTED = 684,             /* UNCOMMITTED  */
    UNENCRYPTED = 685,             /* UNENCRYPTED  */
    UNION = 686,                   /* UNION  */
    UNIQUE = 687,                  /* UNIQUE  */
    UNKNOWN = 688,                 /* UNKNOWN  */
    UNLISTEN = 689,                /* UNLISTEN  */
    UNLOGGED = 690,                /* UNLOGGED  */
    UNTIL = 691,                   /* UNTIL  */
    UPDATE = 692,                  /* UPDATE  */
    USER = 693,                    /* USER  */
    USING = 694,                   /* USING  */
    VACUUM = 695,                  /* VACUUM  */
    VALID = 696,                   /* VALID  */
    VALIDATE = 697,                /* VALIDATE  */
    VALIDATOR = 698,               /* VALIDATOR  */
    VALUE_P = 699,                 /* VALUE_P  */
    VALUES = 700,                  /* VALUES  */
    VARCHAR = 701,                 /* VARCHAR  */
    VARIADIC = 702,                /* VARIADIC  */
    VARYING = 703,                 /* VARYING  */
    VERBOSE = 704,                 /* VERBOSE  */
    VERSION_P = 705,               /* VERSION_P  */
    VIEW = 706,                    /* VIEW  */
    VIEWS = 707,                   /* VIEWS  */
    VOLATILE = 708,                /* VOLATILE  */
    WHEN = 709,                    /* WHEN  */
    WHERE = 710,                   /* WHERE  */
    WHITESPACE_P = 711,            /* WHITESPACE_P  */
    WINDOW = 712,                  /* WINDOW  */
    WITH = 713,                    /* WITH  */
    WITHIN = 714,                  /* WITHIN  */
    WITHOUT = 715,                 /* WITHOUT  */
    WORK = 716,                    /* WORK  */
    WRAPPER = 717,                 /* WRAPPER  */
    WRITE = 718,                   /* WRITE  */
    XML_P = 719,                   /* XML_P  */
    XMLATTRIBUTES = 720,           /* XMLATTRIBUTES  */
    XMLCONCAT = 721,               /* XMLCONCAT  */
    XMLELEMENT = 722,              /* XMLELEMENT  */
    XMLEXISTS = 723,               /* XMLEXISTS  */
    XMLFOREST = 724,               /* XMLFOREST  */
    XMLNAMESPACES = 725,           /* XMLNAMESPACES  */
    XMLPARSE = 726,                /* XMLPARSE  */
    XMLPI = 727,                   /* XMLPI  */
    XMLROOT = 728,                 /* XMLROOT  */
    XMLSERIALIZE = 729,            /* XMLSERIALIZE  */
    XMLTABLE = 730,                /* XMLTABLE  */
    YEAR_P = 731,                  /* YEAR_P  */
    YES_P = 732,                   /* YES_P  */
    ZONE = 733,                    /* ZONE  */
    NOT_LA = 734,                  /* NOT_LA  */
    NULLS_LA = 735,                /* NULLS_LA  */
    WITH_LA = 736,                 /* WITH_LA  */
    MODE_TYPE_NAME = 737,          /* MODE_TYPE_NAME  */
    MODE_PLPGSQL_EXPR = 738,       /* MODE_PLPGSQL_EXPR  */
    MODE_PLPGSQL_ASSIGN1 = 739,    /* MODE_PLPGSQL_ASSIGN1  */
    MODE_PLPGSQL_ASSIGN2 = 740,    /* MODE_PLPGSQL_ASSIGN2  */
    MODE_PLPGSQL_ASSIGN3 = 741,    /* MODE_PLPGSQL_ASSIGN3  */
    UMINUS = 742                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 219 "gram.y"

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
	StatsElem			*selem;
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
	SetQuantifier	 setquantifier;
	struct GroupClause  *groupclause;

#line 599 "gram.h"

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
