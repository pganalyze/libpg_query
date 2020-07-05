/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
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
     SQL_COMMENT = 273,
     C_COMMENT = 274,
     ABORT_P = 275,
     ABSOLUTE_P = 276,
     ACCESS = 277,
     ACTION = 278,
     ADD_P = 279,
     ADMIN = 280,
     AFTER = 281,
     AGGREGATE = 282,
     ALL = 283,
     ALSO = 284,
     ALTER = 285,
     ALWAYS = 286,
     ANALYSE = 287,
     ANALYZE = 288,
     AND = 289,
     ANY = 290,
     ARRAY = 291,
     AS = 292,
     ASC = 293,
     ASSERTION = 294,
     ASSIGNMENT = 295,
     ASYMMETRIC = 296,
     AT = 297,
     ATTACH = 298,
     ATTRIBUTE = 299,
     AUTHORIZATION = 300,
     BACKWARD = 301,
     BEFORE = 302,
     BEGIN_P = 303,
     BETWEEN = 304,
     BIGINT = 305,
     BINARY = 306,
     BIT = 307,
     BOOLEAN_P = 308,
     BOTH = 309,
     BY = 310,
     CACHE = 311,
     CALL = 312,
     CALLED = 313,
     CASCADE = 314,
     CASCADED = 315,
     CASE = 316,
     CAST = 317,
     CATALOG_P = 318,
     CHAIN = 319,
     CHAR_P = 320,
     CHARACTER = 321,
     CHARACTERISTICS = 322,
     CHECK = 323,
     CHECKPOINT = 324,
     CLASS = 325,
     CLOSE = 326,
     CLUSTER = 327,
     COALESCE = 328,
     COLLATE = 329,
     COLLATION = 330,
     COLUMN = 331,
     COLUMNS = 332,
     COMMENT = 333,
     COMMENTS = 334,
     COMMIT = 335,
     COMMITTED = 336,
     CONCURRENTLY = 337,
     CONFIGURATION = 338,
     CONFLICT = 339,
     CONNECTION = 340,
     CONSTRAINT = 341,
     CONSTRAINTS = 342,
     CONTENT_P = 343,
     CONTINUE_P = 344,
     CONVERSION_P = 345,
     COPY = 346,
     COST = 347,
     CREATE = 348,
     CROSS = 349,
     CSV = 350,
     CUBE = 351,
     CURRENT_P = 352,
     CURRENT_CATALOG = 353,
     CURRENT_DATE = 354,
     CURRENT_ROLE = 355,
     CURRENT_SCHEMA = 356,
     CURRENT_TIME = 357,
     CURRENT_TIMESTAMP = 358,
     CURRENT_USER = 359,
     CURSOR = 360,
     CYCLE = 361,
     DATA_P = 362,
     DATABASE = 363,
     DAY_P = 364,
     DEALLOCATE = 365,
     DEC = 366,
     DECIMAL_P = 367,
     DECLARE = 368,
     DEFAULT = 369,
     DEFAULTS = 370,
     DEFERRABLE = 371,
     DEFERRED = 372,
     DEFINER = 373,
     DELETE_P = 374,
     DELIMITER = 375,
     DELIMITERS = 376,
     DEPENDS = 377,
     DESC = 378,
     DETACH = 379,
     DICTIONARY = 380,
     DISABLE_P = 381,
     DISCARD = 382,
     DISTINCT = 383,
     DO = 384,
     DOCUMENT_P = 385,
     DOMAIN_P = 386,
     DOUBLE_P = 387,
     DROP = 388,
     EACH = 389,
     ELSE = 390,
     ENABLE_P = 391,
     ENCODING = 392,
     ENCRYPTED = 393,
     END_P = 394,
     ENUM_P = 395,
     ESCAPE = 396,
     EVENT = 397,
     EXCEPT = 398,
     EXCLUDE = 399,
     EXCLUDING = 400,
     EXCLUSIVE = 401,
     EXECUTE = 402,
     EXISTS = 403,
     EXPLAIN = 404,
     EXTENSION = 405,
     EXTERNAL = 406,
     EXTRACT = 407,
     FALSE_P = 408,
     FAMILY = 409,
     FETCH = 410,
     FILTER = 411,
     FIRST_P = 412,
     FLOAT_P = 413,
     FOLLOWING = 414,
     FOR = 415,
     FORCE = 416,
     FOREIGN = 417,
     FORWARD = 418,
     FREEZE = 419,
     FROM = 420,
     FULL = 421,
     FUNCTION = 422,
     FUNCTIONS = 423,
     GENERATED = 424,
     GLOBAL = 425,
     GRANT = 426,
     GRANTED = 427,
     GREATEST = 428,
     GROUP_P = 429,
     GROUPING = 430,
     GROUPS = 431,
     HANDLER = 432,
     HAVING = 433,
     HEADER_P = 434,
     HOLD = 435,
     HOUR_P = 436,
     IDENTITY_P = 437,
     IF_P = 438,
     ILIKE = 439,
     IMMEDIATE = 440,
     IMMUTABLE = 441,
     IMPLICIT_P = 442,
     IMPORT_P = 443,
     IN_P = 444,
     INCLUDE = 445,
     INCLUDING = 446,
     INCREMENT = 447,
     INDEX = 448,
     INDEXES = 449,
     INHERIT = 450,
     INHERITS = 451,
     INITIALLY = 452,
     INLINE_P = 453,
     INNER_P = 454,
     INOUT = 455,
     INPUT_P = 456,
     INSENSITIVE = 457,
     INSERT = 458,
     INSTEAD = 459,
     INT_P = 460,
     INTEGER = 461,
     INTERSECT = 462,
     INTERVAL = 463,
     INTO = 464,
     INVOKER = 465,
     IS = 466,
     ISNULL = 467,
     ISOLATION = 468,
     JOIN = 469,
     KEY = 470,
     LABEL = 471,
     LANGUAGE = 472,
     LARGE_P = 473,
     LAST_P = 474,
     LATERAL_P = 475,
     LEADING = 476,
     LEAKPROOF = 477,
     LEAST = 478,
     LEFT = 479,
     LEVEL = 480,
     LIKE = 481,
     LIMIT = 482,
     LISTEN = 483,
     LOAD = 484,
     LOCAL = 485,
     LOCALTIME = 486,
     LOCALTIMESTAMP = 487,
     LOCATION = 488,
     LOCK_P = 489,
     LOCKED = 490,
     LOGGED = 491,
     MAPPING = 492,
     MATCH = 493,
     MATERIALIZED = 494,
     MAXVALUE = 495,
     METHOD = 496,
     MINUTE_P = 497,
     MINVALUE = 498,
     MODE = 499,
     MONTH_P = 500,
     MOVE = 501,
     NAME_P = 502,
     NAMES = 503,
     NATIONAL = 504,
     NATURAL = 505,
     NCHAR = 506,
     NEW = 507,
     NEXT = 508,
     NO = 509,
     NONE = 510,
     NOT = 511,
     NOTHING = 512,
     NOTIFY = 513,
     NOTNULL = 514,
     NOWAIT = 515,
     NULL_P = 516,
     NULLIF = 517,
     NULLS_P = 518,
     NUMERIC = 519,
     OBJECT_P = 520,
     OF = 521,
     OFF = 522,
     OFFSET = 523,
     OIDS = 524,
     OLD = 525,
     ON = 526,
     ONLY = 527,
     OPERATOR = 528,
     OPTION = 529,
     OPTIONS = 530,
     OR = 531,
     ORDER = 532,
     ORDINALITY = 533,
     OTHERS = 534,
     OUT_P = 535,
     OUTER_P = 536,
     OVER = 537,
     OVERLAPS = 538,
     OVERLAY = 539,
     OVERRIDING = 540,
     OWNED = 541,
     OWNER = 542,
     PARALLEL = 543,
     PARSER = 544,
     PARTIAL = 545,
     PARTITION = 546,
     PASSING = 547,
     PASSWORD = 548,
     PLACING = 549,
     PLANS = 550,
     POLICY = 551,
     POSITION = 552,
     PRECEDING = 553,
     PRECISION = 554,
     PRESERVE = 555,
     PREPARE = 556,
     PREPARED = 557,
     PRIMARY = 558,
     PRIOR = 559,
     PRIVILEGES = 560,
     PROCEDURAL = 561,
     PROCEDURE = 562,
     PROCEDURES = 563,
     PROGRAM = 564,
     PUBLICATION = 565,
     QUOTE = 566,
     RANGE = 567,
     READ = 568,
     REAL = 569,
     REASSIGN = 570,
     RECHECK = 571,
     RECURSIVE = 572,
     REF = 573,
     REFERENCES = 574,
     REFERENCING = 575,
     REFRESH = 576,
     REINDEX = 577,
     RELATIVE_P = 578,
     RELEASE = 579,
     RENAME = 580,
     REPEATABLE = 581,
     REPLACE = 582,
     REPLICA = 583,
     RESET = 584,
     RESTART = 585,
     RESTRICT = 586,
     RETURNING = 587,
     RETURNS = 588,
     REVOKE = 589,
     RIGHT = 590,
     ROLE = 591,
     ROLLBACK = 592,
     ROLLUP = 593,
     ROUTINE = 594,
     ROUTINES = 595,
     ROW = 596,
     ROWS = 597,
     RULE = 598,
     SAVEPOINT = 599,
     SCHEMA = 600,
     SCHEMAS = 601,
     SCROLL = 602,
     SEARCH = 603,
     SECOND_P = 604,
     SECURITY = 605,
     SELECT = 606,
     SEQUENCE = 607,
     SEQUENCES = 608,
     SERIALIZABLE = 609,
     SERVER = 610,
     SESSION = 611,
     SESSION_USER = 612,
     SET = 613,
     SETS = 614,
     SETOF = 615,
     SHARE = 616,
     SHOW = 617,
     SIMILAR = 618,
     SIMPLE = 619,
     SKIP = 620,
     SMALLINT = 621,
     SNAPSHOT = 622,
     SOME = 623,
     SQL_P = 624,
     STABLE = 625,
     STANDALONE_P = 626,
     START = 627,
     STATEMENT = 628,
     STATISTICS = 629,
     STDIN = 630,
     STDOUT = 631,
     STORAGE = 632,
     STORED = 633,
     STRICT_P = 634,
     STRIP_P = 635,
     SUBSCRIPTION = 636,
     SUBSTRING = 637,
     SUPPORT = 638,
     SYMMETRIC = 639,
     SYSID = 640,
     SYSTEM_P = 641,
     TABLE = 642,
     TABLES = 643,
     TABLESAMPLE = 644,
     TABLESPACE = 645,
     TEMP = 646,
     TEMPLATE = 647,
     TEMPORARY = 648,
     TEXT_P = 649,
     THEN = 650,
     TIES = 651,
     TIME = 652,
     TIMESTAMP = 653,
     TO = 654,
     TRAILING = 655,
     TRANSACTION = 656,
     TRANSFORM = 657,
     TREAT = 658,
     TRIGGER = 659,
     TRIM = 660,
     TRUE_P = 661,
     TRUNCATE = 662,
     TRUSTED = 663,
     TYPE_P = 664,
     TYPES_P = 665,
     UNBOUNDED = 666,
     UNCOMMITTED = 667,
     UNENCRYPTED = 668,
     UNION = 669,
     UNIQUE = 670,
     UNKNOWN = 671,
     UNLISTEN = 672,
     UNLOGGED = 673,
     UNTIL = 674,
     UPDATE = 675,
     USER = 676,
     USING = 677,
     VACUUM = 678,
     VALID = 679,
     VALIDATE = 680,
     VALIDATOR = 681,
     VALUE_P = 682,
     VALUES = 683,
     VARCHAR = 684,
     VARIADIC = 685,
     VARYING = 686,
     VERBOSE = 687,
     VERSION_P = 688,
     VIEW = 689,
     VIEWS = 690,
     VOLATILE = 691,
     WHEN = 692,
     WHERE = 693,
     WHITESPACE_P = 694,
     WINDOW = 695,
     WITH = 696,
     WITHIN = 697,
     WITHOUT = 698,
     WORK = 699,
     WRAPPER = 700,
     WRITE = 701,
     XML_P = 702,
     XMLATTRIBUTES = 703,
     XMLCONCAT = 704,
     XMLELEMENT = 705,
     XMLEXISTS = 706,
     XMLFOREST = 707,
     XMLNAMESPACES = 708,
     XMLPARSE = 709,
     XMLPI = 710,
     XMLROOT = 711,
     XMLSERIALIZE = 712,
     XMLTABLE = 713,
     YEAR_P = 714,
     YES_P = 715,
     ZONE = 716,
     NOT_LA = 717,
     NULLS_LA = 718,
     WITH_LA = 719,
     POSTFIXOP = 720,
     UMINUS = 721
   };
#endif
/* Tokens.  */
#define IDENT 258
#define FCONST 259
#define SCONST 260
#define BCONST 261
#define XCONST 262
#define Op 263
#define ICONST 264
#define PARAM 265
#define TYPECAST 266
#define DOT_DOT 267
#define COLON_EQUALS 268
#define EQUALS_GREATER 269
#define LESS_EQUALS 270
#define GREATER_EQUALS 271
#define NOT_EQUALS 272
#define SQL_COMMENT 273
#define C_COMMENT 274
#define ABORT_P 275
#define ABSOLUTE_P 276
#define ACCESS 277
#define ACTION 278
#define ADD_P 279
#define ADMIN 280
#define AFTER 281
#define AGGREGATE 282
#define ALL 283
#define ALSO 284
#define ALTER 285
#define ALWAYS 286
#define ANALYSE 287
#define ANALYZE 288
#define AND 289
#define ANY 290
#define ARRAY 291
#define AS 292
#define ASC 293
#define ASSERTION 294
#define ASSIGNMENT 295
#define ASYMMETRIC 296
#define AT 297
#define ATTACH 298
#define ATTRIBUTE 299
#define AUTHORIZATION 300
#define BACKWARD 301
#define BEFORE 302
#define BEGIN_P 303
#define BETWEEN 304
#define BIGINT 305
#define BINARY 306
#define BIT 307
#define BOOLEAN_P 308
#define BOTH 309
#define BY 310
#define CACHE 311
#define CALL 312
#define CALLED 313
#define CASCADE 314
#define CASCADED 315
#define CASE 316
#define CAST 317
#define CATALOG_P 318
#define CHAIN 319
#define CHAR_P 320
#define CHARACTER 321
#define CHARACTERISTICS 322
#define CHECK 323
#define CHECKPOINT 324
#define CLASS 325
#define CLOSE 326
#define CLUSTER 327
#define COALESCE 328
#define COLLATE 329
#define COLLATION 330
#define COLUMN 331
#define COLUMNS 332
#define COMMENT 333
#define COMMENTS 334
#define COMMIT 335
#define COMMITTED 336
#define CONCURRENTLY 337
#define CONFIGURATION 338
#define CONFLICT 339
#define CONNECTION 340
#define CONSTRAINT 341
#define CONSTRAINTS 342
#define CONTENT_P 343
#define CONTINUE_P 344
#define CONVERSION_P 345
#define COPY 346
#define COST 347
#define CREATE 348
#define CROSS 349
#define CSV 350
#define CUBE 351
#define CURRENT_P 352
#define CURRENT_CATALOG 353
#define CURRENT_DATE 354
#define CURRENT_ROLE 355
#define CURRENT_SCHEMA 356
#define CURRENT_TIME 357
#define CURRENT_TIMESTAMP 358
#define CURRENT_USER 359
#define CURSOR 360
#define CYCLE 361
#define DATA_P 362
#define DATABASE 363
#define DAY_P 364
#define DEALLOCATE 365
#define DEC 366
#define DECIMAL_P 367
#define DECLARE 368
#define DEFAULT 369
#define DEFAULTS 370
#define DEFERRABLE 371
#define DEFERRED 372
#define DEFINER 373
#define DELETE_P 374
#define DELIMITER 375
#define DELIMITERS 376
#define DEPENDS 377
#define DESC 378
#define DETACH 379
#define DICTIONARY 380
#define DISABLE_P 381
#define DISCARD 382
#define DISTINCT 383
#define DO 384
#define DOCUMENT_P 385
#define DOMAIN_P 386
#define DOUBLE_P 387
#define DROP 388
#define EACH 389
#define ELSE 390
#define ENABLE_P 391
#define ENCODING 392
#define ENCRYPTED 393
#define END_P 394
#define ENUM_P 395
#define ESCAPE 396
#define EVENT 397
#define EXCEPT 398
#define EXCLUDE 399
#define EXCLUDING 400
#define EXCLUSIVE 401
#define EXECUTE 402
#define EXISTS 403
#define EXPLAIN 404
#define EXTENSION 405
#define EXTERNAL 406
#define EXTRACT 407
#define FALSE_P 408
#define FAMILY 409
#define FETCH 410
#define FILTER 411
#define FIRST_P 412
#define FLOAT_P 413
#define FOLLOWING 414
#define FOR 415
#define FORCE 416
#define FOREIGN 417
#define FORWARD 418
#define FREEZE 419
#define FROM 420
#define FULL 421
#define FUNCTION 422
#define FUNCTIONS 423
#define GENERATED 424
#define GLOBAL 425
#define GRANT 426
#define GRANTED 427
#define GREATEST 428
#define GROUP_P 429
#define GROUPING 430
#define GROUPS 431
#define HANDLER 432
#define HAVING 433
#define HEADER_P 434
#define HOLD 435
#define HOUR_P 436
#define IDENTITY_P 437
#define IF_P 438
#define ILIKE 439
#define IMMEDIATE 440
#define IMMUTABLE 441
#define IMPLICIT_P 442
#define IMPORT_P 443
#define IN_P 444
#define INCLUDE 445
#define INCLUDING 446
#define INCREMENT 447
#define INDEX 448
#define INDEXES 449
#define INHERIT 450
#define INHERITS 451
#define INITIALLY 452
#define INLINE_P 453
#define INNER_P 454
#define INOUT 455
#define INPUT_P 456
#define INSENSITIVE 457
#define INSERT 458
#define INSTEAD 459
#define INT_P 460
#define INTEGER 461
#define INTERSECT 462
#define INTERVAL 463
#define INTO 464
#define INVOKER 465
#define IS 466
#define ISNULL 467
#define ISOLATION 468
#define JOIN 469
#define KEY 470
#define LABEL 471
#define LANGUAGE 472
#define LARGE_P 473
#define LAST_P 474
#define LATERAL_P 475
#define LEADING 476
#define LEAKPROOF 477
#define LEAST 478
#define LEFT 479
#define LEVEL 480
#define LIKE 481
#define LIMIT 482
#define LISTEN 483
#define LOAD 484
#define LOCAL 485
#define LOCALTIME 486
#define LOCALTIMESTAMP 487
#define LOCATION 488
#define LOCK_P 489
#define LOCKED 490
#define LOGGED 491
#define MAPPING 492
#define MATCH 493
#define MATERIALIZED 494
#define MAXVALUE 495
#define METHOD 496
#define MINUTE_P 497
#define MINVALUE 498
#define MODE 499
#define MONTH_P 500
#define MOVE 501
#define NAME_P 502
#define NAMES 503
#define NATIONAL 504
#define NATURAL 505
#define NCHAR 506
#define NEW 507
#define NEXT 508
#define NO 509
#define NONE 510
#define NOT 511
#define NOTHING 512
#define NOTIFY 513
#define NOTNULL 514
#define NOWAIT 515
#define NULL_P 516
#define NULLIF 517
#define NULLS_P 518
#define NUMERIC 519
#define OBJECT_P 520
#define OF 521
#define OFF 522
#define OFFSET 523
#define OIDS 524
#define OLD 525
#define ON 526
#define ONLY 527
#define OPERATOR 528
#define OPTION 529
#define OPTIONS 530
#define OR 531
#define ORDER 532
#define ORDINALITY 533
#define OTHERS 534
#define OUT_P 535
#define OUTER_P 536
#define OVER 537
#define OVERLAPS 538
#define OVERLAY 539
#define OVERRIDING 540
#define OWNED 541
#define OWNER 542
#define PARALLEL 543
#define PARSER 544
#define PARTIAL 545
#define PARTITION 546
#define PASSING 547
#define PASSWORD 548
#define PLACING 549
#define PLANS 550
#define POLICY 551
#define POSITION 552
#define PRECEDING 553
#define PRECISION 554
#define PRESERVE 555
#define PREPARE 556
#define PREPARED 557
#define PRIMARY 558
#define PRIOR 559
#define PRIVILEGES 560
#define PROCEDURAL 561
#define PROCEDURE 562
#define PROCEDURES 563
#define PROGRAM 564
#define PUBLICATION 565
#define QUOTE 566
#define RANGE 567
#define READ 568
#define REAL 569
#define REASSIGN 570
#define RECHECK 571
#define RECURSIVE 572
#define REF 573
#define REFERENCES 574
#define REFERENCING 575
#define REFRESH 576
#define REINDEX 577
#define RELATIVE_P 578
#define RELEASE 579
#define RENAME 580
#define REPEATABLE 581
#define REPLACE 582
#define REPLICA 583
#define RESET 584
#define RESTART 585
#define RESTRICT 586
#define RETURNING 587
#define RETURNS 588
#define REVOKE 589
#define RIGHT 590
#define ROLE 591
#define ROLLBACK 592
#define ROLLUP 593
#define ROUTINE 594
#define ROUTINES 595
#define ROW 596
#define ROWS 597
#define RULE 598
#define SAVEPOINT 599
#define SCHEMA 600
#define SCHEMAS 601
#define SCROLL 602
#define SEARCH 603
#define SECOND_P 604
#define SECURITY 605
#define SELECT 606
#define SEQUENCE 607
#define SEQUENCES 608
#define SERIALIZABLE 609
#define SERVER 610
#define SESSION 611
#define SESSION_USER 612
#define SET 613
#define SETS 614
#define SETOF 615
#define SHARE 616
#define SHOW 617
#define SIMILAR 618
#define SIMPLE 619
#define SKIP 620
#define SMALLINT 621
#define SNAPSHOT 622
#define SOME 623
#define SQL_P 624
#define STABLE 625
#define STANDALONE_P 626
#define START 627
#define STATEMENT 628
#define STATISTICS 629
#define STDIN 630
#define STDOUT 631
#define STORAGE 632
#define STORED 633
#define STRICT_P 634
#define STRIP_P 635
#define SUBSCRIPTION 636
#define SUBSTRING 637
#define SUPPORT 638
#define SYMMETRIC 639
#define SYSID 640
#define SYSTEM_P 641
#define TABLE 642
#define TABLES 643
#define TABLESAMPLE 644
#define TABLESPACE 645
#define TEMP 646
#define TEMPLATE 647
#define TEMPORARY 648
#define TEXT_P 649
#define THEN 650
#define TIES 651
#define TIME 652
#define TIMESTAMP 653
#define TO 654
#define TRAILING 655
#define TRANSACTION 656
#define TRANSFORM 657
#define TREAT 658
#define TRIGGER 659
#define TRIM 660
#define TRUE_P 661
#define TRUNCATE 662
#define TRUSTED 663
#define TYPE_P 664
#define TYPES_P 665
#define UNBOUNDED 666
#define UNCOMMITTED 667
#define UNENCRYPTED 668
#define UNION 669
#define UNIQUE 670
#define UNKNOWN 671
#define UNLISTEN 672
#define UNLOGGED 673
#define UNTIL 674
#define UPDATE 675
#define USER 676
#define USING 677
#define VACUUM 678
#define VALID 679
#define VALIDATE 680
#define VALIDATOR 681
#define VALUE_P 682
#define VALUES 683
#define VARCHAR 684
#define VARIADIC 685
#define VARYING 686
#define VERBOSE 687
#define VERSION_P 688
#define VIEW 689
#define VIEWS 690
#define VOLATILE 691
#define WHEN 692
#define WHERE 693
#define WHITESPACE_P 694
#define WINDOW 695
#define WITH 696
#define WITHIN 697
#define WITHOUT 698
#define WORK 699
#define WRAPPER 700
#define WRITE 701
#define XML_P 702
#define XMLATTRIBUTES 703
#define XMLCONCAT 704
#define XMLELEMENT 705
#define XMLEXISTS 706
#define XMLFOREST 707
#define XMLNAMESPACES 708
#define XMLPARSE 709
#define XMLPI 710
#define XMLROOT 711
#define XMLSERIALIZE 712
#define XMLTABLE 713
#define YEAR_P 714
#define YES_P 715
#define ZONE 716
#define NOT_LA 717
#define NULLS_LA 718
#define WITH_LA 719
#define POSTFIXOP 720
#define UMINUS 721




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 206 "gram.y"
{
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
}
/* Line 1529 of yacc.c.  */
#line 1025 "gram.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


