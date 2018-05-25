cmake_minimum_required (VERSION 3.6)
project (pg_query_parser 
	LANGUAGES C
	VERSION 0.0.1 
)

include(GNUInstallDirs)

add_library(libpgqueryparser SHARED

	src/postgres/contrib_pgcrypto_sha1.c
	src/postgres/src_backend_catalog_namespace.c
	src/postgres/src_backend_catalog_pg_proc.c
	src/postgres/src_backend_libpq_pqcomm.c
	src/postgres/src_backend_lib_stringinfo.c
	src/postgres/src_backend_nodes_bitmapset.c
	src/postgres/src_backend_nodes_copyfuncs.c
	src/postgres/src_backend_nodes_equalfuncs.c
	src/postgres/src_backend_nodes_extensible.c
	src/postgres/src_backend_nodes_list.c
	src/postgres/src_backend_nodes_makefuncs.c
	src/postgres/src_backend_nodes_nodeFuncs.c
	src/postgres/src_backend_nodes_value.c
	src/postgres/src_backend_parser_gram.c
	src/postgres/src_backend_parser_parse_expr.c
	src/postgres/src_backend_parser_parser.c
	src/postgres/src_backend_parser_scansup.c
	src/postgres/src_backend_postmaster_postmaster.c
	src/postgres/src_backend_storage_ipc_ipc.c
	src/postgres/src_backend_storage_lmgr_s_lock.c
	src/postgres/src_backend_tcop_postgres.c
	src/postgres/src_backend_utils_adt_datum.c
	src/postgres/src_backend_utils_adt_expandeddatum.c
	src/postgres/src_backend_utils_adt_format_type.c
	src/postgres/src_backend_utils_adt_ruleutils.c
	src/postgres/src_backend_utils_error_assert.c
	src/postgres/src_backend_utils_error_elog.c
	src/postgres/src_backend_utils_hash_dynahash.c
	src/postgres/src_backend_utils_init_globals.c
	src/postgres/src_backend_utils_mb_encnames.c
	src/postgres/src_backend_utils_mb_mbutils.c
	src/postgres/src_backend_utils_mb_wchar.c
	src/postgres/src_backend_utils_misc_guc.c
	src/postgres/src_backend_utils_mmgr_aset.c
	src/postgres/src_backend_utils_mmgr_mcxt.c
	src/postgres/src_common_keywords.c
	src/postgres/src_common_psprintf.c
	src/postgres/src_pl_plpgsql_src_pl_comp.c
	src/postgres/src_pl_plpgsql_src_pl_funcs.c
	src/postgres/src_pl_plpgsql_src_pl_gram.c
	src/postgres/src_pl_plpgsql_src_pl_handler.c
	src/postgres/src_pl_plpgsql_src_pl_scanner.c
	src/postgres/src_port_erand48.c
	src/postgres/src_port_pgsleep.c
	src/postgres/src_port_qsort.c
	src/postgres/src_port_random.c

	src/pg_query.c
	src/pg_query_fingerprint.c
	src/pg_query_json.c
	src/pg_query_json_plpgsql.c
	src/pg_query_normalize.c
	src/pg_query_parse.c
	src/pg_query_parse_plpgsql.c
)

target_include_directories(libpgqueryparser PRIVATE . src/postgres/include)

set_target_properties(libpgqueryparser PROPERTIES 
	VERSION ${PROJECT_VERSION}
	SOVERSION 0
	PUBLIC_HEADER pg_query.h
	
)

install(TARGETS libpgqueryparser
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

configure_file(libpgqueryparser.pc.in libpgqueryparser.pc @ONLY)

install(FILES ${CMAKE_BINARY_DIR}/libpgqueryparser.pc DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)

