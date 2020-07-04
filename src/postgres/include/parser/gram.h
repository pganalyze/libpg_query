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
     STORED = 631,
     STRICT_P = 632,
     STRIP_P = 633,
     SUBSCRIPTION = 634,
     SUBSTRING = 635,
     SUPPORT = 636,
     SYMMETRIC = 637,
     SYSID = 638,
     SYSTEM_P = 639,
     TABLE = 640,
     TABLES = 641,
     TABLESAMPLE = 642,
     TABLESPACE = 643,
     TEMP = 644,
     TEMPLATE = 645,
     TEMPORARY = 646,
     TEXT_P = 647,
     THEN = 648,
     TIES = 649,
     TIME = 650,
     TIMESTAMP = 651,
     TO = 652,
     TRAILING = 653,
     TRANSACTION = 654,
     TRANSFORM = 655,
     TREAT = 656,
     TRIGGER = 657,
     TRIM = 658,
     TRUE_P = 659,
     TRUNCATE = 660,
     TRUSTED = 661,
     TYPE_P = 662,
     TYPES_P = 663,
     UNBOUNDED = 664,
     UNCOMMITTED = 665,
     UNENCRYPTED = 666,
     UNION = 667,
     UNIQUE = 668,
     UNKNOWN = 669,
     UNLISTEN = 670,
     UNLOGGED = 671,
     UNTIL = 672,
     UPDATE = 673,
     USER = 674,
     USING = 675,
     VACUUM = 676,
     VALID = 677,
     VALIDATE = 678,
     VALIDATOR = 679,
     VALUE_P = 680,
     VALUES = 681,
     VARCHAR = 682,
     VARIADIC = 683,
     VARYING = 684,
     VERBOSE = 685,
     VERSION_P = 686,
     VIEW = 687,
     VIEWS = 688,
     VOLATILE = 689,
     WHEN = 690,
     WHERE = 691,
     WHITESPACE_P = 692,
     WINDOW = 693,
     WITH = 694,
     WITHIN = 695,
     WITHOUT = 696,
     WORK = 697,
     WRAPPER = 698,
     WRITE = 699,
     XML_P = 700,
     XMLATTRIBUTES = 701,
     XMLCONCAT = 702,
     XMLELEMENT = 703,
     XMLEXISTS = 704,
     XMLFOREST = 705,
     XMLNAMESPACES = 706,
     XMLPARSE = 707,
     XMLPI = 708,
     XMLROOT = 709,
     XMLSERIALIZE = 710,
     XMLTABLE = 711,
     YEAR_P = 712,
     YES_P = 713,
     ZONE = 714,
     NOT_LA = 715,
     NULLS_LA = 716,
     WITH_LA = 717,
     POSTFIXOP = 718,
     UMINUS = 719
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
#define ABORT_P 273
#define ABSOLUTE_P 274
#define ACCESS 275
#define ACTION 276
#define ADD_P 277
#define ADMIN 278
#define AFTER 279
#define AGGREGATE 280
#define ALL 281
#define ALSO 282
#define ALTER 283
#define ALWAYS 284
#define ANALYSE 285
#define ANALYZE 286
#define AND 287
#define ANY 288
#define ARRAY 289
#define AS 290
#define ASC 291
#define ASSERTION 292
#define ASSIGNMENT 293
#define ASYMMETRIC 294
#define AT 295
#define ATTACH 296
#define ATTRIBUTE 297
#define AUTHORIZATION 298
#define BACKWARD 299
#define BEFORE 300
#define BEGIN_P 301
#define BETWEEN 302
#define BIGINT 303
#define BINARY 304
#define BIT 305
#define BOOLEAN_P 306
#define BOTH 307
#define BY 308
#define CACHE 309
#define CALL 310
#define CALLED 311
#define CASCADE 312
#define CASCADED 313
#define CASE 314
#define CAST 315
#define CATALOG_P 316
#define CHAIN 317
#define CHAR_P 318
#define CHARACTER 319
#define CHARACTERISTICS 320
#define CHECK 321
#define CHECKPOINT 322
#define CLASS 323
#define CLOSE 324
#define CLUSTER 325
#define COALESCE 326
#define COLLATE 327
#define COLLATION 328
#define COLUMN 329
#define COLUMNS 330
#define COMMENT 331
#define COMMENTS 332
#define COMMIT 333
#define COMMITTED 334
#define CONCURRENTLY 335
#define CONFIGURATION 336
#define CONFLICT 337
#define CONNECTION 338
#define CONSTRAINT 339
#define CONSTRAINTS 340
#define CONTENT_P 341
#define CONTINUE_P 342
#define CONVERSION_P 343
#define COPY 344
#define COST 345
#define CREATE 346
#define CROSS 347
#define CSV 348
#define CUBE 349
#define CURRENT_P 350
#define CURRENT_CATALOG 351
#define CURRENT_DATE 352
#define CURRENT_ROLE 353
#define CURRENT_SCHEMA 354
#define CURRENT_TIME 355
#define CURRENT_TIMESTAMP 356
#define CURRENT_USER 357
#define CURSOR 358
#define CYCLE 359
#define DATA_P 360
#define DATABASE 361
#define DAY_P 362
#define DEALLOCATE 363
#define DEC 364
#define DECIMAL_P 365
#define DECLARE 366
#define DEFAULT 367
#define DEFAULTS 368
#define DEFERRABLE 369
#define DEFERRED 370
#define DEFINER 371
#define DELETE_P 372
#define DELIMITER 373
#define DELIMITERS 374
#define DEPENDS 375
#define DESC 376
#define DETACH 377
#define DICTIONARY 378
#define DISABLE_P 379
#define DISCARD 380
#define DISTINCT 381
#define DO 382
#define DOCUMENT_P 383
#define DOMAIN_P 384
#define DOUBLE_P 385
#define DROP 386
#define EACH 387
#define ELSE 388
#define ENABLE_P 389
#define ENCODING 390
#define ENCRYPTED 391
#define END_P 392
#define ENUM_P 393
#define ESCAPE 394
#define EVENT 395
#define EXCEPT 396
#define EXCLUDE 397
#define EXCLUDING 398
#define EXCLUSIVE 399
#define EXECUTE 400
#define EXISTS 401
#define EXPLAIN 402
#define EXTENSION 403
#define EXTERNAL 404
#define EXTRACT 405
#define FALSE_P 406
#define FAMILY 407
#define FETCH 408
#define FILTER 409
#define FIRST_P 410
#define FLOAT_P 411
#define FOLLOWING 412
#define FOR 413
#define FORCE 414
#define FOREIGN 415
#define FORWARD 416
#define FREEZE 417
#define FROM 418
#define FULL 419
#define FUNCTION 420
#define FUNCTIONS 421
#define GENERATED 422
#define GLOBAL 423
#define GRANT 424
#define GRANTED 425
#define GREATEST 426
#define GROUP_P 427
#define GROUPING 428
#define GROUPS 429
#define HANDLER 430
#define HAVING 431
#define HEADER_P 432
#define HOLD 433
#define HOUR_P 434
#define IDENTITY_P 435
#define IF_P 436
#define ILIKE 437
#define IMMEDIATE 438
#define IMMUTABLE 439
#define IMPLICIT_P 440
#define IMPORT_P 441
#define IN_P 442
#define INCLUDE 443
#define INCLUDING 444
#define INCREMENT 445
#define INDEX 446
#define INDEXES 447
#define INHERIT 448
#define INHERITS 449
#define INITIALLY 450
#define INLINE_P 451
#define INNER_P 452
#define INOUT 453
#define INPUT_P 454
#define INSENSITIVE 455
#define INSERT 456
#define INSTEAD 457
#define INT_P 458
#define INTEGER 459
#define INTERSECT 460
#define INTERVAL 461
#define INTO 462
#define INVOKER 463
#define IS 464
#define ISNULL 465
#define ISOLATION 466
#define JOIN 467
#define KEY 468
#define LABEL 469
#define LANGUAGE 470
#define LARGE_P 471
#define LAST_P 472
#define LATERAL_P 473
#define LEADING 474
#define LEAKPROOF 475
#define LEAST 476
#define LEFT 477
#define LEVEL 478
#define LIKE 479
#define LIMIT 480
#define LISTEN 481
#define LOAD 482
#define LOCAL 483
#define LOCALTIME 484
#define LOCALTIMESTAMP 485
#define LOCATION 486
#define LOCK_P 487
#define LOCKED 488
#define LOGGED 489
#define MAPPING 490
#define MATCH 491
#define MATERIALIZED 492
#define MAXVALUE 493
#define METHOD 494
#define MINUTE_P 495
#define MINVALUE 496
#define MODE 497
#define MONTH_P 498
#define MOVE 499
#define NAME_P 500
#define NAMES 501
#define NATIONAL 502
#define NATURAL 503
#define NCHAR 504
#define NEW 505
#define NEXT 506
#define NO 507
#define NONE 508
#define NOT 509
#define NOTHING 510
#define NOTIFY 511
#define NOTNULL 512
#define NOWAIT 513
#define NULL_P 514
#define NULLIF 515
#define NULLS_P 516
#define NUMERIC 517
#define OBJECT_P 518
#define OF 519
#define OFF 520
#define OFFSET 521
#define OIDS 522
#define OLD 523
#define ON 524
#define ONLY 525
#define OPERATOR 526
#define OPTION 527
#define OPTIONS 528
#define OR 529
#define ORDER 530
#define ORDINALITY 531
#define OTHERS 532
#define OUT_P 533
#define OUTER_P 534
#define OVER 535
#define OVERLAPS 536
#define OVERLAY 537
#define OVERRIDING 538
#define OWNED 539
#define OWNER 540
#define PARALLEL 541
#define PARSER 542
#define PARTIAL 543
#define PARTITION 544
#define PASSING 545
#define PASSWORD 546
#define PLACING 547
#define PLANS 548
#define POLICY 549
#define POSITION 550
#define PRECEDING 551
#define PRECISION 552
#define PRESERVE 553
#define PREPARE 554
#define PREPARED 555
#define PRIMARY 556
#define PRIOR 557
#define PRIVILEGES 558
#define PROCEDURAL 559
#define PROCEDURE 560
#define PROCEDURES 561
#define PROGRAM 562
#define PUBLICATION 563
#define QUOTE 564
#define RANGE 565
#define READ 566
#define REAL 567
#define REASSIGN 568
#define RECHECK 569
#define RECURSIVE 570
#define REF 571
#define REFERENCES 572
#define REFERENCING 573
#define REFRESH 574
#define REINDEX 575
#define RELATIVE_P 576
#define RELEASE 577
#define RENAME 578
#define REPEATABLE 579
#define REPLACE 580
#define REPLICA 581
#define RESET 582
#define RESTART 583
#define RESTRICT 584
#define RETURNING 585
#define RETURNS 586
#define REVOKE 587
#define RIGHT 588
#define ROLE 589
#define ROLLBACK 590
#define ROLLUP 591
#define ROUTINE 592
#define ROUTINES 593
#define ROW 594
#define ROWS 595
#define RULE 596
#define SAVEPOINT 597
#define SCHEMA 598
#define SCHEMAS 599
#define SCROLL 600
#define SEARCH 601
#define SECOND_P 602
#define SECURITY 603
#define SELECT 604
#define SEQUENCE 605
#define SEQUENCES 606
#define SERIALIZABLE 607
#define SERVER 608
#define SESSION 609
#define SESSION_USER 610
#define SET 611
#define SETS 612
#define SETOF 613
#define SHARE 614
#define SHOW 615
#define SIMILAR 616
#define SIMPLE 617
#define SKIP 618
#define SMALLINT 619
#define SNAPSHOT 620
#define SOME 621
#define SQL_P 622
#define STABLE 623
#define STANDALONE_P 624
#define START 625
#define STATEMENT 626
#define STATISTICS 627
#define STDIN 628
#define STDOUT 629
#define STORAGE 630
#define STORED 631
#define STRICT_P 632
#define STRIP_P 633
#define SUBSCRIPTION 634
#define SUBSTRING 635
#define SUPPORT 636
#define SYMMETRIC 637
#define SYSID 638
#define SYSTEM_P 639
#define TABLE 640
#define TABLES 641
#define TABLESAMPLE 642
#define TABLESPACE 643
#define TEMP 644
#define TEMPLATE 645
#define TEMPORARY 646
#define TEXT_P 647
#define THEN 648
#define TIES 649
#define TIME 650
#define TIMESTAMP 651
#define TO 652
#define TRAILING 653
#define TRANSACTION 654
#define TRANSFORM 655
#define TREAT 656
#define TRIGGER 657
#define TRIM 658
#define TRUE_P 659
#define TRUNCATE 660
#define TRUSTED 661
#define TYPE_P 662
#define TYPES_P 663
#define UNBOUNDED 664
#define UNCOMMITTED 665
#define UNENCRYPTED 666
#define UNION 667
#define UNIQUE 668
#define UNKNOWN 669
#define UNLISTEN 670
#define UNLOGGED 671
#define UNTIL 672
#define UPDATE 673
#define USER 674
#define USING 675
#define VACUUM 676
#define VALID 677
#define VALIDATE 678
#define VALIDATOR 679
#define VALUE_P 680
#define VALUES 681
#define VARCHAR 682
#define VARIADIC 683
#define VARYING 684
#define VERBOSE 685
#define VERSION_P 686
#define VIEW 687
#define VIEWS 688
#define VOLATILE 689
#define WHEN 690
#define WHERE 691
#define WHITESPACE_P 692
#define WINDOW 693
#define WITH 694
#define WITHIN 695
#define WITHOUT 696
#define WORK 697
#define WRAPPER 698
#define WRITE 699
#define XML_P 700
#define XMLATTRIBUTES 701
#define XMLCONCAT 702
#define XMLELEMENT 703
#define XMLEXISTS 704
#define XMLFOREST 705
#define XMLNAMESPACES 706
#define XMLPARSE 707
#define XMLPI 708
#define XMLROOT 709
#define XMLSERIALIZE 710
#define XMLTABLE 711
#define YEAR_P 712
#define YES_P 713
#define ZONE 714
#define NOT_LA 715
#define NULLS_LA 716
#define WITH_LA 717
#define POSTFIXOP 718
#define UMINUS 719




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
#line 1021 "gram.h"
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


