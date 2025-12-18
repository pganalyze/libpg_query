void it_parses_simple_query(TestState* test_state) {
	TEST_INIT();
	Summary result = summary("SELECT * FROM test WHERE a = 1", 0, -1);

	TEST_ASSERT_LIST_LENGTH(result.tables, 1);
	TEST_SUMMARY_ASSERT_TABLES(result.tables, ((char*[]){"test", NULL}));
	TEST_ASSERT_LIST_LENGTH(result.aliases, 0);
	TEST_ASSERT_LIST_LENGTH(result.cte_names, 0);
	TEST_ASSERT_LIST_LENGTH(result.functions, 0);
	TEST_ASSERT_LIST_LENGTH(result.filter_columns, 1);
	TEST_ASSERT_NULL(result.truncated_query);
	TEST_ASSERT_LIST_EQUAL(result.statement_types, list_make1("SelectStmt"));
}

void it_parses_simple_query_with_alias(TestState* test_state) {
	TEST_INIT();
	Summary result = summary("SELECT * FROM test AS x WHERE a = 1", 0, -1);

	TEST_ASSERT_LIST_LENGTH(result.tables, 1);
	TEST_SUMMARY_ASSERT_TABLES(result.tables, ((char*[]){"test", NULL}));
	TEST_ASSERT_LIST_LENGTH(result.aliases, 1);
	TEST_SUMMARY_ASSERT_ALIAS(result.aliases, "x", "test");
	TEST_ASSERT_LIST_LENGTH(result.cte_names, 0);
	TEST_ASSERT_LIST_LENGTH(result.functions, 0);
	TEST_ASSERT_LIST_LENGTH(result.filter_columns, 1);
	TEST_ASSERT_NULL(result.truncated_query);
	TEST_ASSERT_LIST_EQUAL(result.statement_types, list_make1("SelectStmt"));
}

void it_parses_query_with_nested_select_where(TestState* test_state) {
	TEST_INIT();
	Summary result = summary("SELECT * FROM test WHERE col1 = (SELECT col2 FROM test2 WHERE col3 = 123)", 0, -1);

	TEST_ASSERT_LIST_LENGTH(result.tables, 2);
	TEST_SUMMARY_ASSERT_TABLES(result.tables, ((char*[]){"test", "test2", NULL}));
	TEST_ASSERT_LIST_LENGTH(result.aliases, 0);
	TEST_ASSERT_LIST_LENGTH(result.cte_names, 0);
	TEST_ASSERT_LIST_LENGTH(result.functions, 0);
	
	TEST_SUMMARY_ASSERT_FILTER_COLUMN(result.filter_columns, NULL, NULL, "col1");
	TEST_SUMMARY_ASSERT_FILTER_COLUMN(result.filter_columns, NULL, NULL, "col3");
	    
	TEST_ASSERT_LIST_EQUAL(result.statement_types, list_make1("SelectStmt"));
}

void it_handles_errors(TestState* test_state) {
	TEST_INIT();

	PgQuerySummaryParseResultInternal parse_result = summary_internal("CREATE RANDOM ix_test ON contacts.person;", 0, -1);
	TEST_ASSERT_STR_EQUAL(parse_result.error->message, "syntax error at or near \"RANDOM\"");
	pg_query_free_summary_parse_result_internal(parse_result);

	parse_result = summary_internal("SELECT 'ERR", 0, -1);
	TEST_ASSERT_STR_EQUAL(parse_result.error->message, "unterminated quoted string at or near \"'ERR\"");
	pg_query_free_summary_parse_result_internal(parse_result);
}

void it_handles_basic_query(TestState* test_state) {
	TEST_INIT();
	char* query = "SELECT * FROM \"t0\"";
	Summary result = summary(query, 0, -1);
	TEST_ASSERT_LIST_LENGTH(result.tables, 1);
	TEST_SUMMARY_ASSERT_TABLES(result.tables, ((char*[]){"t0", NULL}));
	TEST_ASSERT_LIST_LENGTH(result.aliases, 0);
	TEST_ASSERT_LIST_LENGTH(result.cte_names, 0);
	TEST_ASSERT_LIST_LENGTH(result.functions, 0);
	TEST_ASSERT_LIST_LENGTH(result.filter_columns, 0);
	TEST_ASSERT_NULL(result.truncated_query);
}

void it_handles_join_expression(TestState* test_state) {
	TEST_INIT();
	char* query = "SELECT * FROM \"t0\" JOIN \"t1\" ON (1)";
	Summary result = summary(query, 0, -1);
	TEST_ASSERT_LIST_LENGTH(result.tables, 2);
	TEST_SUMMARY_ASSERT_TABLES(result.tables, ((char*[]){"t0", "t1", NULL}));
	TEST_ASSERT_LIST_EQUAL(result.statement_types, list_make1("SelectStmt"));
}

void it_handles_recursion_without_error(TestState* test_state) {
	TEST_INIT();
	// The Ruby version of pg_query fails here because of Ruby protobuf limitations
	char* query = "SELECT * FROM \"t0\"\n\
	    JOIN \"t1\" ON (1) JOIN \"t2\" ON (1) JOIN \"t3\" ON (1) JOIN \"t4\" ON (1) JOIN \"t5\" ON (1)\n\
	    JOIN \"t6\" ON (1) JOIN \"t7\" ON (1) JOIN \"t8\" ON (1) JOIN \"t9\" ON (1) JOIN \"t10\" ON (1)\n\
	    JOIN \"t11\" ON (1) JOIN \"t12\" ON (1) JOIN \"t13\" ON (1) JOIN \"t14\" ON (1) JOIN \"t15\" ON (1)\n\
	    JOIN \"t16\" ON (1) JOIN \"t17\" ON (1) JOIN \"t18\" ON (1) JOIN \"t19\" ON (1) JOIN \"t20\" ON (1)\n\
	    JOIN \"t21\" ON (1) JOIN \"t22\" ON (1) JOIN \"t23\" ON (1) JOIN \"t24\" ON (1) JOIN \"t25\" ON (1)\n\
	    JOIN \"t26\" ON (1) JOIN \"t27\" ON (1) JOIN \"t28\" ON (1) JOIN \"t29\" ON (1)";
	Summary result = summary(query, 0, -1);
	TEST_ASSERT_LIST_LENGTH(result.tables, 30);
	TEST_SUMMARY_ASSERT_TABLES(result.tables, ((char*[]){
		"t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7", "t8", "t9",
		"t10", "t11", "t12", "t13", "t14", "t15", "t16", "t17", "t18", "t19",
		"t20", "t21", "t22", "t23", "t24", "t25", "t26", "t27", "t28", "t29",
		NULL
	}));
	TEST_ASSERT_LIST_EQUAL(result.statement_types, list_make1("SelectStmt"));
}

void it_parses_real_queries(TestState* test_state) {
	TEST_INIT();
	char* query = "\n\
	    SELECT memory_total_bytes, memory_free_bytes, memory_pagecache_bytes, memory_buffers_bytes, memory_applications_bytes,\n\
	        (memory_swap_total_bytes - memory_swap_free_bytes) AS swap, date_part($0, s.collected_at) AS collected_at\n\
	    FROM snapshots s JOIN system_snapshots ON (snapshot_id = s.id)\n\
	    WHERE s.database_id = $0 AND s.collected_at BETWEEN $0 AND $0\n\
	    ORDER BY collected_at";
	Summary result = summary(query, 0, -1);
	TEST_SUMMARY_ASSERT_TABLES(result.tables, ((char*[]){"snapshots", "system_snapshots", NULL}));
	TEST_SUMMARY_ASSERT_TABLES_WITH_CTX(result.tables, CONTEXT_SELECT, ((char*[]){"snapshots", "system_snapshots", NULL}));
	TEST_ASSERT_LIST_EQUAL(result.statement_types, list_make1("SelectStmt"));
}

void it_parses_empty_queries(TestState* test_state) {
	TEST_INIT();
	Summary result = summary("-- nothing", 0, -1);
	TEST_ASSERT_LIST_LENGTH(result.statement_types, 0);
	TEST_ASSERT_LIST_LENGTH(result.tables, 0);
	TEST_ASSERT_LIST_LENGTH(result.aliases, 0);
	TEST_ASSERT_LIST_LENGTH(result.cte_names, 0);
	TEST_ASSERT_LIST_LENGTH(result.functions, 0);
	TEST_ASSERT_LIST_LENGTH(result.filter_columns, 0);
	TEST_ASSERT_NULL(result.truncated_query);
}

void it_parses_floats_with_leading_dot(TestState* test_state) {
	TEST_INIT();
	// summary() will exit(1) if there's an error.
	summary("SELECT .1", 0, -1);
}

void it_parses_bit_strings_hex_notation(TestState* test_state) {
	TEST_INIT();
	// summary() will exit(1) if there's an error.
	summary("SELECT X'EFFF'", 0, -1);
}

void it_parses_ALTER_TABLE(TestState* test_state) {
	TEST_INIT();
	Summary result = summary("ALTER TABLE test ADD PRIMARY KEY (gid)", 0, -1);
	TEST_SUMMARY_ASSERT_TABLES(result.tables, ((char*[]){"test", NULL}));
	TEST_SUMMARY_ASSERT_TABLES_WITH_CTX(result.tables, CONTEXT_DDL, ((char*[]){"test", NULL}));
	TEST_ASSERT_LIST_EQUAL(result.statement_types, list_make1("AlterTableStmt"));
}

void it_parses_SET(TestState* test_state) {
	TEST_INIT();
	Summary result = summary("SET statement_timeout=1", 0, -1);
	TEST_ASSERT_LIST_LENGTH(result.tables, 0);
	TEST_ASSERT_LIST_EQUAL(result.statement_types, list_make1("VariableSetStmt"));
}

void it_parses_SHOW(TestState* test_state) {
	TEST_INIT();
	Summary result = summary("SHOW work_mem", 0, -1);
	TEST_ASSERT_LIST_LENGTH(result.tables, 0);
	TEST_ASSERT_LIST_EQUAL(result.statement_types, list_make1("VariableShowStmt"));
}

void it_parses_COPY(TestState* test_state) {
	TEST_INIT();
	Summary result = summary("COPY test (id) TO stdout", 0, -1);
	TEST_SUMMARY_ASSERT_TABLES(result.tables, ((char*[]){"test", NULL}));
	TEST_ASSERT_LIST_EQUAL(result.statement_types, list_make1("CopyStmt"));
}

void it_parses_DROP_TABLE(TestState* test_state) {
	TEST_INIT();
	Summary result = summary("drop table abc.test123 cascade", 0, -1);
	TEST_SUMMARY_ASSERT_TABLES(result.tables, ((char*[]){"abc.test123", NULL}));
	TEST_SUMMARY_ASSERT_TABLES_WITH_CTX(result.tables, CONTEXT_DDL, ((char*[]){"abc.test123", NULL}));
	TEST_ASSERT_LIST_EQUAL(result.statement_types, list_make1("DropStmt"));

	result = summary("drop table abc.test123, test", 0, -1);
	TEST_SUMMARY_ASSERT_TABLES(result.tables, ((char*[]){"abc.test123", "test", NULL}));
	TEST_SUMMARY_ASSERT_TABLES_WITH_CTX(result.tables, CONTEXT_DDL, ((char*[]){"abc.test123", "test", NULL}));
}

void it_parses_COMMIT(TestState* test_state) {
	TEST_INIT();
	Summary result = summary("COMMIT", 0, -1);
	TEST_ASSERT_LIST_EQUAL(result.statement_types, list_make1("TransactionStmt"));
}

void it_parses_CHECKPOINT(TestState* test_state) {
	TEST_INIT();
	Summary result = summary("CHECKPOINT", 0, -1);
	TEST_ASSERT_LIST_EQUAL(result.statement_types, list_make1("CheckPointStmt"));
}

void it_parses_VACUUM(TestState* test_state) {
	TEST_INIT();
	Summary result = summary("VACUUM my_table", 0, -1);
	TEST_SUMMARY_ASSERT_TABLES(result.tables, ((char*[]){"my_table", NULL}));
	TEST_SUMMARY_ASSERT_TABLES_WITH_CTX(result.tables, CONTEXT_DDL, ((char*[]){"my_table", NULL}));
	TEST_ASSERT_LIST_EQUAL(result.statement_types, list_make1("VacuumStmt"));
}

void it_parses_MERGE(TestState* test_state) {
	TEST_INIT();
	Summary result = summary(
		"WITH cte AS (SELECT * FROM g.other_table CROSS JOIN p) MERGE INTO my_table USING cte ON (id=oid) WHEN MATCHED THEN UPDATE SET a=b WHEN NOT MATCHED THEN INSERT (id, a) VALUES (oid, b);",
		0,
		-1
	);
	TEST_SUMMARY_ASSERT_TABLES_WITH_CTX(result.tables, CONTEXT_SELECT, ((char*[]){"g.other_table", "p", NULL}));
	TEST_SUMMARY_ASSERT_TABLES_WITH_CTX(result.tables, CONTEXT_DML, ((char*[]){"my_table", NULL}));
	TEST_SUMMARY_ASSERT_TABLES(result.tables, ((char*[]){"g.other_table", "my_table", "p", NULL}));
	TEST_ASSERT_LIST_EQUAL(result.cte_names, list_make1("cte"));
	TEST_ASSERT_LIST_EQUAL(result.statement_types, list_make2("MergeStmt", "SelectStmt"));
}

void it_parses_EXPLAIN(TestState* test_state) {
	TEST_INIT();
	Summary result = summary("EXPLAIN DELETE FROM test", 0, -1);
	TEST_SUMMARY_ASSERT_TABLES(result.tables, ((char*[]){"test", NULL}));
	TEST_ASSERT_LIST_EQUAL(result.statement_types, list_make2("ExplainStmt", "DeleteStmt"));
}

void it_parses_SELECT_INTO(TestState* test_state) {
	TEST_INIT();
	Summary result = summary("CREATE TEMP TABLE test AS SELECT 1", 0, -1);
	TEST_SUMMARY_ASSERT_TABLES(result.tables, ((char*[]){"test", NULL}));
	TEST_SUMMARY_ASSERT_TABLES_WITH_CTX(result.tables, CONTEXT_DDL, ((char*[]){"test", NULL}));
	TEST_ASSERT_LIST_EQUAL(result.statement_types, list_make2("CreateTableAsStmt", "SelectStmt"));
}

void it_parses_LOCK(TestState* test_state) {
	TEST_INIT();
	Summary result = summary("LOCK TABLE public.schema_migrations IN ACCESS SHARE MODE", 0, -1);
	TEST_SUMMARY_ASSERT_TABLES(result.tables, ((char*[]){"public.schema_migrations", NULL}));
	TEST_ASSERT_LIST_EQUAL(result.statement_types, list_make1("LockStmt"));
}

void it_parses_CREATE_TABLE(TestState* test_state) {
	TEST_INIT();
	Summary result = summary("CREATE TABLE test (a int4)", 0, -1);
	TEST_SUMMARY_ASSERT_TABLES(result.tables, ((char*[]){"test", NULL}));
	TEST_SUMMARY_ASSERT_TABLES_WITH_CTX(result.tables, CONTEXT_DDL, ((char*[]){"test", NULL}));
	TEST_ASSERT_LIST_EQUAL(result.statement_types, list_make1("CreateStmt"));
}

void it_parses_CREATE_TABLE_AS(TestState* test_state) {
	TEST_INIT();
	Summary result = summary("CREATE TABLE foo AS SELECT * FROM bar;", 0, -1);
	TEST_SUMMARY_ASSERT_TABLES(result.tables, ((char*[]){"bar", "foo", NULL}));
	TEST_SUMMARY_ASSERT_TABLES_WITH_CTX(result.tables, CONTEXT_DDL, ((char*[]){"foo", NULL}));
	TEST_SUMMARY_ASSERT_TABLES_WITH_CTX(result.tables, CONTEXT_SELECT, ((char*[]){"bar", NULL}));
	TEST_ASSERT_LIST_EQUAL(result.statement_types, list_make2("CreateTableAsStmt", "SelectStmt"));

	char* sql = "CREATE TABLE foo AS SELECT id FROM bar UNION SELECT id from baz;";
	result = summary(sql, 0, -1);
	TEST_SUMMARY_ASSERT_TABLES(result.tables, ((char*[]){"bar", "baz", "foo", NULL}));
	TEST_SUMMARY_ASSERT_TABLES_WITH_CTX(result.tables, CONTEXT_DDL, ((char*[]){"foo", NULL}));
	TEST_SUMMARY_ASSERT_TABLES_WITH_CTX(result.tables, CONTEXT_SELECT, ((char*[]){"bar", "baz", NULL}));
	TEST_ASSERT_LIST_EQUAL(result.statement_types, list_make2("CreateTableAsStmt", "SelectStmt"));
}

void it_fails_to_parse_CREATE_TABLE_WITH_OIDS(TestState* test_state) {
	PgQuerySummaryParseResultInternal parse_result = summary_internal("CREATE TABLE test (a int4) WITH OIDS", 0, -1);
	TEST_ASSERT_STR_EQUAL(parse_result.error->message, "syntax error at or near \"OIDS\"");
	pg_query_free_summary_parse_result_internal(parse_result);
}


void it_parses_CREATE_INDEX(TestState* test_state) {
	TEST_INIT();
	Summary result = summary("CREATE INDEX testidx ON test USING btree (a, (lower(b) || upper(c))) WHERE pow(a, 2) > 25", 0, -1);
	TEST_SUMMARY_ASSERT_TABLES(result.tables, ((char*[]){"test", NULL}));
	TEST_SUMMARY_ASSERT_TABLES_WITH_CTX(result.tables, CONTEXT_DDL, ((char*[]){"test", NULL}));
	TEST_ASSERT_LIST_EQUAL(result.statement_types, list_make1("IndexStmt"));
	TEST_SUMMARY_ASSERT_FUNCTIONS_WITH_CTX(result.functions, CONTEXT_CALL, ((char*[]){"lower", "pow", "upper", NULL}));
}

void it_parses_CREATE_SCHEMA(TestState* test_state) {
	TEST_INIT();
	Summary result = summary("CREATE SCHEMA IF NOT EXISTS test AUTHORIZATION joe", 0, -1);
	TEST_ASSERT_LIST_LENGTH(result.tables, 0);
	TEST_ASSERT_LIST_EQUAL(result.statement_types, list_make1("CreateSchemaStmt"));
}

void it_parses_CREATE_VIEW(TestState* test_state) {
	TEST_INIT();
	Summary result = summary("CREATE VIEW myview AS SELECT * FROM mytab", 0, -1);
	TEST_SUMMARY_ASSERT_TABLES(result.tables, ((char*[]){"mytab", "myview", NULL}));
	TEST_SUMMARY_ASSERT_TABLES_WITH_CTX(result.tables, CONTEXT_DDL, ((char*[]){"myview", NULL}));
	TEST_SUMMARY_ASSERT_TABLES_WITH_CTX(result.tables, CONTEXT_SELECT, ((char*[]){"mytab", NULL}));
	TEST_ASSERT_LIST_EQUAL(result.statement_types, list_make2("ViewStmt", "SelectStmt"));
}

void it_parses_REFRESH_MATERIALIZED_VIEW(TestState* test_state) {
	TEST_INIT();
	Summary result = summary("REFRESH MATERIALIZED VIEW myview", 0, -1);
	TEST_SUMMARY_ASSERT_TABLES(result.tables, ((char*[]){"myview", NULL}));
	TEST_SUMMARY_ASSERT_TABLES_WITH_CTX(result.tables, CONTEXT_DDL, ((char*[]){"myview", NULL}));
	TEST_ASSERT_LIST_EQUAL(result.statement_types, list_make1("RefreshMatViewStmt"));
}

void it_parses_CREATE_RULE(TestState* test_state) {
	TEST_INIT();
	char* sql = "CREATE RULE shoe_ins_protect AS ON INSERT TO shoe DO INSTEAD NOTHING";
	Summary result = summary(sql, 0, -1);
	TEST_SUMMARY_ASSERT_TABLES(result.tables, ((char*[]){"shoe", NULL}));
	TEST_SUMMARY_ASSERT_TABLES_WITH_CTX(result.tables, CONTEXT_DDL, ((char*[]){"shoe", NULL}));
	TEST_ASSERT_LIST_EQUAL(result.statement_types, list_make1("RuleStmt"));
}

void it_parses_CREATE_TRIGGER(TestState* test_state) {
	TEST_INIT();
	char* sql = "CREATE TRIGGER check_update BEFORE UPDATE ON accounts FOR EACH ROW EXECUTE PROCEDURE check_account_update()";
	Summary result = summary(sql, 0, -1);
	TEST_SUMMARY_ASSERT_TABLES(result.tables, ((char*[]){"accounts", NULL}));
	TEST_SUMMARY_ASSERT_TABLES_WITH_CTX(result.tables, CONTEXT_DDL, ((char*[]){"accounts", NULL}));
	TEST_ASSERT_LIST_EQUAL(result.statement_types, list_make1("CreateTrigStmt"));
}

void it_parses_DROP_SCHEMA(TestState* test_state) {
	TEST_INIT();
	Summary result = summary("DROP SCHEMA myschema", 0, -1);
	TEST_ASSERT_LIST_LENGTH(result.tables, 0);
	TEST_ASSERT_LIST_EQUAL(result.statement_types, list_make1("DropStmt"));
}

void it_parses_DROP_VIEW(TestState* test_state) {
	TEST_INIT();
	Summary result = summary("DROP VIEW myview, myview2", 0, -1);
	TEST_ASSERT_LIST_LENGTH(result.tables, 0);
	TEST_ASSERT_LIST_EQUAL(result.statement_types, list_make1("DropStmt"));
}

void it_parses_DROP_INDEX(TestState* test_state) {
	TEST_INIT();
	Summary result = summary("DROP INDEX CONCURRENTLY myindex", 0, -1);
	TEST_ASSERT_LIST_LENGTH(result.tables, 0);
	TEST_ASSERT_LIST_EQUAL(result.statement_types, list_make1("DropStmt"));
}

void it_parses_DROP_RULE(TestState* test_state) {
	TEST_INIT();
	Summary result = summary("DROP RULE myrule ON mytable CASCADE", 0, -1);
	TEST_SUMMARY_ASSERT_TABLES(result.tables, ((char*[]){"mytable", NULL}));
	TEST_SUMMARY_ASSERT_TABLES_WITH_CTX(result.tables, CONTEXT_DDL, ((char*[]){"mytable", NULL}));
	TEST_ASSERT_LIST_EQUAL(result.statement_types, list_make1("DropStmt"));
}

void it_parses_DROP_TRIGGER(TestState* test_state) {
	TEST_INIT();
	Summary result = summary("DROP TRIGGER IF EXISTS mytrigger ON mytable RESTRICT", 0, -1);
	TEST_SUMMARY_ASSERT_TABLES(result.tables, ((char*[]){"mytable", NULL}));
	TEST_SUMMARY_ASSERT_TABLES_WITH_CTX(result.tables, CONTEXT_DDL, ((char*[]){"mytable", NULL}));
	TEST_ASSERT_LIST_EQUAL(result.statement_types, list_make1("DropStmt"));
}

void it_parses_GRANT(TestState* test_state) {
	TEST_INIT();
	Summary result = summary("GRANT INSERT, UPDATE ON mytable TO myuser", 0, -1);
	TEST_SUMMARY_ASSERT_TABLES(result.tables, ((char*[]){"mytable", NULL}));
	TEST_SUMMARY_ASSERT_TABLES_WITH_CTX(result.tables, CONTEXT_DDL, ((char*[]){"mytable", NULL}));
	TEST_ASSERT_LIST_EQUAL(result.statement_types, list_make1("GrantStmt"));
}

void it_parses_REVOKE(TestState* test_state) {
	TEST_INIT();
	Summary result = summary("REVOKE admins FROM joe", 0, -1);
	TEST_ASSERT_LIST_LENGTH(result.tables, 0);
	TEST_ASSERT_LIST_EQUAL(result.statement_types, list_make1("GrantRoleStmt"));
}

void it_parses_TRUNCATE(TestState* test_state) {
	TEST_INIT();
	Summary result = summary("TRUNCATE bigtable, \"fattable\" RESTART IDENTITY", 0, -1);
	TEST_SUMMARY_ASSERT_TABLES(result.tables, ((char*[]){"bigtable", "fattable", NULL}));
	TEST_SUMMARY_ASSERT_TABLES_WITH_CTX(result.tables, CONTEXT_DDL, ((char*[]){"bigtable", "fattable", NULL}));
	TEST_ASSERT_LIST_EQUAL(result.statement_types, list_make1("TruncateStmt"));
}

void it_parses_WITH(TestState* test_state) {
	TEST_INIT();
	Summary result = summary("WITH a AS (SELECT * FROM x WHERE x.y = $1 AND x.z = 1) SELECT * FROM a", 0, -1);
	TEST_SUMMARY_ASSERT_TABLES(result.tables, ((char*[]){"x", NULL}));
	TEST_ASSERT_LIST_EQUAL(result.cte_names, list_make1("a"));
	TEST_ASSERT_LIST_EQUAL(result.statement_types, list_make1("SelectStmt"));
}

void it_parses_multi_line_functions(TestState* test_state) {
	TEST_INIT();
	char* sql = "CREATE OR REPLACE FUNCTION thing(parameter_thing text)\n\
  RETURNS bigint AS\n\
$BODY$\n\
DECLARE\n\
	    local_thing_id BIGINT := 0;\n\
BEGIN\n\
	    SELECT thing_id INTO local_thing_id FROM thing_map\n\
	    WHERE\n\
	            thing_map_field = parameter_thing\n\
	    ORDER BY 1 LIMIT 1;\n\
\n\
	    IF NOT FOUND THEN\n\
	            local_thing_id = 0;\n\
	    END IF;\n\
	    RETURN local_thing_id;\n\
END;\n\
$BODY$\n\
  LANGUAGE plpgsql STABLE";
	Summary result = summary(sql, 0, -1);
	TEST_ASSERT_LIST_LENGTH(result.tables, 0);
	TEST_SUMMARY_ASSERT_FUNCTIONS(result.functions, ((char*[]){"thing", NULL}));
	TEST_SUMMARY_ASSERT_FUNCTIONS_WITH_CTX(result.functions, CONTEXT_DDL, ((char*[]){"thing", NULL}));
	TEST_SUMMARY_ASSERT_FUNCTIONS_WITH_CTX(result.functions, CONTEXT_CALL, ((char*[]){NULL}));
	TEST_ASSERT_LIST_EQUAL(result.statement_types, list_make1("CreateFunctionStmt"));
}

void it_parses_table_functions(TestState* test_state) {
	TEST_INIT();
	char* sql = "CREATE FUNCTION getfoo(int) RETURNS TABLE (f1 int) AS 'SELECT * FROM foo WHERE fooid = $1;' LANGUAGE SQL";
	Summary result = summary(sql, 0, -1);
	TEST_ASSERT_LIST_LENGTH(result.tables, 0);
	TEST_SUMMARY_ASSERT_FUNCTIONS(result.functions, ((char*[]){"getfoo", NULL}));
	TEST_SUMMARY_ASSERT_FUNCTIONS_WITH_CTX(result.functions, CONTEXT_DDL, ((char*[]){"getfoo", NULL}));
	TEST_SUMMARY_ASSERT_FUNCTIONS_WITH_CTX(result.functions, CONTEXT_CALL, ((char*[]){NULL}));
	TEST_ASSERT_LIST_EQUAL(result.statement_types, list_make1("CreateFunctionStmt"));
}

void it_finds_called_functions(TestState* test_state) {
	TEST_INIT();
	Summary result = summary("SELECT testfunc(1);", 0, -1);
	TEST_ASSERT_LIST_LENGTH(result.tables, 0);
	TEST_SUMMARY_ASSERT_FUNCTIONS(result.functions, ((char*[]){"testfunc", NULL}));
	TEST_SUMMARY_ASSERT_FUNCTIONS_WITH_CTX(result.functions, CONTEXT_DDL, ((char*[]){NULL}));
	TEST_SUMMARY_ASSERT_FUNCTIONS_WITH_CTX(result.functions, CONTEXT_CALL, ((char*[]){"testfunc", NULL}));
	TEST_ASSERT_LIST_EQUAL(result.statement_types, list_make1("SelectStmt"));
}

void it_finds_functions_invoked_with_CALL(TestState* test_state) {
	TEST_INIT();
	Summary result = summary("CALL testfunc(1);", 0, -1);
	TEST_ASSERT_LIST_LENGTH(result.tables, 0);
	TEST_SUMMARY_ASSERT_FUNCTIONS(result.functions, ((char*[]){"testfunc", NULL}));
	TEST_SUMMARY_ASSERT_FUNCTIONS_WITH_CTX(result.functions, CONTEXT_DDL, ((char*[]){NULL}));
	TEST_SUMMARY_ASSERT_FUNCTIONS_WITH_CTX(result.functions, CONTEXT_CALL, ((char*[]){"testfunc", NULL}));
	TEST_ASSERT_LIST_EQUAL(result.statement_types, list_make1("CallStmt"));
}

void it_finds_dropped_functions(TestState* test_state) {
	TEST_INIT();
	Summary result = summary("DROP FUNCTION IF EXISTS testfunc(x integer);", 0, -1);
	TEST_ASSERT_LIST_LENGTH(result.tables, 0);
	TEST_SUMMARY_ASSERT_FUNCTIONS(result.functions, ((char*[]){"testfunc", NULL}));
	TEST_SUMMARY_ASSERT_FUNCTIONS_WITH_CTX(result.functions, CONTEXT_DDL, ((char*[]){"testfunc", NULL}));
	TEST_SUMMARY_ASSERT_FUNCTIONS_WITH_CTX(result.functions, CONTEXT_CALL, ((char*[]){NULL}));
	TEST_ASSERT_LIST_EQUAL(result.statement_types, list_make1("DropStmt"));
}

void it_finds_renamed_functions(TestState* test_state) {
	TEST_INIT();
	Summary result = summary("ALTER FUNCTION testfunc(integer) RENAME TO testfunc2;", 0, -1);
	TEST_ASSERT_LIST_LENGTH(result.tables, 0);
	TEST_SUMMARY_ASSERT_FUNCTIONS(result.functions, ((char*[]){"testfunc", "testfunc2", NULL}));
	TEST_SUMMARY_ASSERT_FUNCTIONS_WITH_CTX(result.functions, CONTEXT_DDL, ((char*[]){"testfunc", "testfunc2", NULL}));
	TEST_SUMMARY_ASSERT_FUNCTIONS_WITH_CTX(result.functions, CONTEXT_CALL, ((char*[]){NULL}));
	TEST_ASSERT_LIST_EQUAL(result.statement_types, list_make1("RenameStmt"));
}

void it_finds_nested_tables_in_SELECT(TestState* test_state) {
	TEST_INIT();
	char* sql = "select u.email, (select count(*) from enrollments e where e.user_id = u.id) as num_enrollments from users u";
	Summary result = summary(sql, 0, -1);
	TEST_SUMMARY_ASSERT_TABLES(result.tables, ((char*[]){"enrollments", "users", NULL}));
	TEST_SUMMARY_ASSERT_TABLES_WITH_CTX(result.tables, CONTEXT_SELECT, ((char*[]){"enrollments", "users", NULL}));
	TEST_ASSERT_LIST_EQUAL(result.statement_types, list_make1("SelectStmt"));
}

void it_separates_CTE_names_from_table_names(TestState* test_state) {
	TEST_INIT();
	char* sql = "WITH cte_name AS (SELECT 1) SELECT * FROM table_name, cte_name";
	Summary result = summary(sql, 0, -1);
	TEST_SUMMARY_ASSERT_TABLES(result.tables, ((char*[]){"table_name", NULL}));
	TEST_SUMMARY_ASSERT_TABLES_WITH_CTX(result.tables, CONTEXT_SELECT, ((char*[]){"table_name", NULL}));
	TEST_ASSERT_LIST_EQUAL(result.cte_names, list_make1("cte_name"));
	TEST_ASSERT_LIST_EQUAL(result.statement_types, list_make1("SelectStmt"));
}

void it_finds_tables_in_SELECT_FROM_TABLESAMPLE(TestState* test_state) {
	TEST_INIT();
	char* sql = "SELECT * FROM tbl TABLESAMPLE sample(1)";
	Summary result = summary(sql, 0, -1);
	TEST_SUMMARY_ASSERT_TABLES(result.tables, ((char*[]){"tbl", NULL}));
	TEST_SUMMARY_ASSERT_TABLES_WITH_CTX(result.tables, CONTEXT_SELECT, ((char*[]){"tbl", NULL}));
	TEST_ASSERT_LIST_LENGTH(result.cte_names, 0);
	TEST_ASSERT_LIST_EQUAL(result.statement_types, list_make1("SelectStmt"));
}

void it_finds_tables_in_SELECT_FROM_XMLTABLE(TestState* test_state) {
	TEST_INIT();
	char* sql = "SELECT xmltable.* FROM xmlelements, XMLTABLE('/root' PASSING data COLUMNS element text)";
	Summary result = summary(sql, 0, -1);
	TEST_SUMMARY_ASSERT_TABLES(result.tables, ((char*[]){"xmlelements", NULL}));
	TEST_SUMMARY_ASSERT_TABLES_WITH_CTX(result.tables, CONTEXT_SELECT, ((char*[]){"xmlelements", NULL}));
	TEST_ASSERT_LIST_LENGTH(result.cte_names, 0);
	TEST_ASSERT_LIST_EQUAL(result.statement_types, list_make1("SelectStmt"));
}

void it_ignores_JSON_TABLE(TestState* test_state) {
	TEST_INIT();
	char* sql = "SELECT jt.* FROM my_films, JSON_TABLE (js, '$.favorites[*]' COLUMNS (id FOR ORDINALITY, kind text PATH '$.kind')) AS jt;";
	Summary result = summary(sql, 0, -1);
	TEST_SUMMARY_ASSERT_TABLES(result.tables, ((char*[]){"my_films", NULL}));
	TEST_SUMMARY_ASSERT_TABLES_WITH_CTX(result.tables, CONTEXT_SELECT, ((char*[]){"my_films", NULL}));
	TEST_ASSERT_LIST_LENGTH(result.cte_names, 0);
	TEST_ASSERT_LIST_EQUAL(result.statement_types, list_make1("SelectStmt"));
}

void it_finds_nested_tables_in_FROM_clause(TestState* test_state) {
	TEST_INIT();
	Summary result = summary("select u.* from (select * from users) u", 0, -1);
	TEST_SUMMARY_ASSERT_TABLES(result.tables, ((char*[]){"users", NULL}));
	TEST_SUMMARY_ASSERT_TABLES_WITH_CTX(result.tables, CONTEXT_SELECT, ((char*[]){"users", NULL}));
	TEST_ASSERT_LIST_EQUAL(result.statement_types, list_make1("SelectStmt"));
}

void it_finds_nested_tables_in_WHERE_clause(TestState* test_state) {
	TEST_INIT();
	Summary result = summary("select users.id from users where 1 = (select count(*) from user_roles)", 0, -1);
	TEST_SUMMARY_ASSERT_TABLES(result.tables, ((char*[]){"user_roles", "users", NULL}));
	TEST_SUMMARY_ASSERT_TABLES_WITH_CTX(result.tables, CONTEXT_SELECT, ((char*[]){"user_roles", "users", NULL}));
	TEST_ASSERT_LIST_EQUAL(result.statement_types, list_make1("SelectStmt"));
}

void it_finds_tables_in_SELECT_with_subselects_without_FROM(TestState* test_state) {
	TEST_INIT();
	char* query = "\n\
	    SELECT *\n\
	    FROM pg_catalog.pg_class c\n\
	    JOIN (\n\
	        SELECT 17650 AS oid\n\
	        UNION ALL\n\
	        SELECT 17663 AS oid\n\
	    ) vals ON c.oid = vals.oid\n\
	";
	Summary result = summary(query, 0, -1);
	TEST_SUMMARY_ASSERT_TABLES(result.tables, ((char*[]){"pg_catalog.pg_class", NULL}));
	TEST_SUMMARY_ASSERT_TABLES_WITH_CTX(result.tables, CONTEXT_SELECT, ((char*[]){"pg_catalog.pg_class", NULL}));
	TEST_ASSERT_LIST_EQUAL(result.statement_types, list_make1("SelectStmt"));
	// TODO: add filter_columns
	// expect(query.filter_columns).to eq [["pg_catalog.pg_class", "oid"], ["vals", "oid"]]
}

void it_finds_nested_tables_in_IN_clause(TestState* test_state) {
	TEST_INIT();
	char* sql = "\n\
	    select users.*\n\
	    from users\n\
	    where users.id IN (select user_roles.user_id from user_roles)\n\
	        and (users.created_at between '2016-06-01' and '2016-06-30')\n\
	";
	Summary result = summary(sql, 0, -1);
	TEST_SUMMARY_ASSERT_TABLES(result.tables, ((char*[]){"user_roles", "users", NULL}));
	TEST_SUMMARY_ASSERT_TABLES_WITH_CTX(result.tables, CONTEXT_SELECT, ((char*[]){"user_roles", "users", NULL}));
	TEST_ASSERT_LIST_EQUAL(result.statement_types, list_make1("SelectStmt"));
}

void it_finds_nested_tables_in_ORDER_BY_clause(TestState* test_state) {
	TEST_INIT();
	char* sql = "\n\
	    select users.*\n\
	    from users\n\
	    order by (\n\
	        select max(user_roles.role_id)\n\
	        from user_roles\n\
	        where user_roles.user_id = users.id\n\
	    )\n\
	";
	Summary result = summary(sql, 0, -1);
	TEST_SUMMARY_ASSERT_TABLES(result.tables, ((char*[]){"user_roles", "users", NULL}));
	TEST_SUMMARY_ASSERT_TABLES_WITH_CTX(result.tables, CONTEXT_SELECT, ((char*[]){"user_roles", "users", NULL}));
	TEST_ASSERT_LIST_EQUAL(result.statement_types, list_make1("SelectStmt"));
}

void it_finds_nested_tables_in_ORDER_BY_clause_with_multiple_entries(TestState* test_state) {
	TEST_INIT();
	char* sql = "\n\
	    select users.*\n\
	    from users\n\
	    order by (\n\
	        select max(user_roles.role_id)\n\
	        from user_roles\n\
	        where user_roles.user_id = users.id\n\
	    ) asc, (\n\
	        select max(user_logins.role_id)\n\
	        from user_logins\n\
	        where user_logins.user_id = users.id\n\
	    ) desc\n\
	";
	Summary result = summary(sql, 0, -1);
	TEST_SUMMARY_ASSERT_TABLES(result.tables, ((char*[]){"user_logins", "user_roles", "users", NULL}));
	TEST_SUMMARY_ASSERT_TABLES_WITH_CTX(result.tables, CONTEXT_SELECT, ((char*[]){"user_logins", "user_roles", "users", NULL}));
	TEST_ASSERT_LIST_EQUAL(result.statement_types, list_make1("SelectStmt"));
}

void it_finds_nested_tables_in_GROUP_BY_clause(TestState* test_state) {
	TEST_INIT();
	char* sql = "\n\
	    select users.*\n\
	    from users\n\
	    group by (\n\
	        select max(user_roles.role_id)\n\
	        from user_roles\n\
	        where user_roles.user_id = users.id\n\
	    )\n\
	";
	Summary result = summary(sql, 0, -1);
	TEST_SUMMARY_ASSERT_TABLES(result.tables, ((char*[]){"user_roles", "users", NULL}));
	TEST_SUMMARY_ASSERT_TABLES_WITH_CTX(result.tables, CONTEXT_SELECT, ((char*[]){"user_roles", "users", NULL}));
	TEST_ASSERT_LIST_EQUAL(result.statement_types, list_make1("SelectStmt"));
}

void it_finds_nested_tables_in_GROUP_BY_clause_with_multiple_entries(TestState* test_state) {
	TEST_INIT();
	char* sql = "\n\
	    select users.*\n\
	    from users\n\
	    group by (\n\
	        select max(user_roles.role_id)\n\
	        from user_roles\n\
	        where user_roles.user_id = users.id\n\
	    ), (\n\
	        select max(user_logins.role_id)\n\
	        from user_logins\n\
	        where user_logins.user_id = users.id\n\
	    )\n\
	";
	Summary result = summary(sql, 0, -1);
	TEST_SUMMARY_ASSERT_TABLES(result.tables, ((char*[]){"user_logins", "user_roles", "users", NULL}));
	TEST_SUMMARY_ASSERT_TABLES_WITH_CTX(result.tables, CONTEXT_SELECT, ((char*[]){"user_logins", "user_roles", "users", NULL}));
	TEST_ASSERT_LIST_EQUAL(result.statement_types, list_make1("SelectStmt"));
}

void it_finds_nested_tables_in_HAVING_clause(TestState* test_state) {
	TEST_INIT();
	char* sql = "\n\
	    select users.*\n\
	    from users\n\
	    group by users.id\n\
	    having 1 > (\n\
	        select count(user_roles.role_id)\n\
	        from user_roles\n\
	        where user_roles.user_id = users.id\n\
	    )\n\
	";
	Summary result = summary(sql, 0, -1);
	TEST_SUMMARY_ASSERT_TABLES(result.tables, ((char*[]){"user_roles", "users", NULL}));
	TEST_SUMMARY_ASSERT_TABLES_WITH_CTX(result.tables, CONTEXT_SELECT, ((char*[]){"user_roles", "users", NULL}));
	TEST_ASSERT_LIST_EQUAL(result.statement_types, list_make1("SelectStmt"));
}

void it_finds_nested_tables_in_HAVING_clause_with_boolean_expression(TestState* test_state) {
	TEST_INIT();
	char* sql = "\n\
	    select users.*\n\
	    from users\n\
	    group by users.id\n\
	    having true and 1 > (\n\
	        select count(user_roles.role_id)\n\
	        from user_roles\n\
	        where user_roles.user_id = users.id\n\
	    )\n\
	";
	Summary result = summary(sql, 0, -1);
	TEST_SUMMARY_ASSERT_TABLES(result.tables, ((char*[]){"user_roles", "users", NULL}));
	TEST_SUMMARY_ASSERT_TABLES_WITH_CTX(result.tables, CONTEXT_SELECT, ((char*[]){"user_roles", "users", NULL}));
	TEST_ASSERT_LIST_EQUAL(result.statement_types, list_make1("SelectStmt"));
}

void it_finds_nested_tables_in_a_subselect_on_a_JOIN(TestState* test_state) {
	TEST_INIT();
	char* sql = "\n\
	    select foo.*\n\
	    from foo\n\
	    join ( select * from bar ) b\n\
	    on b.baz = foo.quux\n\
	";
	Summary result = summary(sql, 0, -1);
	TEST_SUMMARY_ASSERT_TABLES(result.tables, ((char*[]){"bar", "foo", NULL}));
	TEST_SUMMARY_ASSERT_TABLES_WITH_CTX(result.tables, CONTEXT_SELECT, ((char*[]){"foo", "bar", NULL}));
	TEST_ASSERT_LIST_EQUAL(result.statement_types, list_make1("SelectStmt"));
}

void it_finds_nested_tables_in_a_subselect_in_a_JOIN_condition(TestState* test_state) {
	TEST_INIT();
	char* sql = "\n\
	    SELECT *\n\
	    FROM foo\n\
	    INNER JOIN join_a ON foo.id = join_a.id AND join_a.id IN (\n\
	        SELECT id\n\
	        FROM sub_a\n\
	        INNER JOIN sub_b ON sub_a.id = sub_b.id AND sub_b.id IN (\n\
	            SELECT id\n\
	            FROM sub_c\n\
	            INNER JOIN sub_d ON sub_c.id IN (SELECT id from sub_e)\n\
	        )\n\
	    )\n\
	    INNER JOIN join_b ON foo.id = join_b.id AND join_b.id IN (\n\
	      SELECT id FROM sub_f\n\
	    )\n\
	";
	Summary result = summary(sql, 0, -1);
	TEST_SUMMARY_ASSERT_TABLES(result.tables, ((char*[]){"foo", "join_a", "join_b", "sub_a", "sub_b", "sub_c", "sub_d", "sub_e", "sub_f", NULL}));
	TEST_SUMMARY_ASSERT_TABLES_WITH_CTX(result.tables, CONTEXT_SELECT, ((char*[]){"foo", "join_a", "join_b", "sub_a", "sub_b", "sub_c", "sub_d", "sub_e", "sub_f", NULL}));
	TEST_ASSERT_LIST_EQUAL(result.statement_types, list_make1("SelectStmt"));
}

void it_correctly_categorizes_CTEs_after_UNION_SELECT(TestState* test_state) {
	TEST_INIT();
	char* sql = "\n\
	    WITH cte_a AS (\n\
	        SELECT * FROM table_a\n\
	    ), cte_b AS (\n\
	        SELECT * FROM table_b\n\
	    )\n\
	    SELECT id FROM table_c\n\
	    LEFT JOIN cte_b ON table_c.id = cte_b.c_id\n\
	    UNION\n\
	    SELECT * FROM cte_a\n\
	";
	Summary result = summary(sql, 0, -1);
	TEST_SUMMARY_ASSERT_TABLES(result.tables, ((char*[]){"table_a", "table_b", "table_c", NULL}));
	TEST_ASSERT_LIST_EQUAL(result.cte_names, list_make2("cte_a", "cte_b"));
	TEST_ASSERT_LIST_EQUAL(result.statement_types, list_make1("SelectStmt"));
}

void it_correctly_categorizes_CTEs_after_EXCEPT_SELECT(TestState* test_state) {
	TEST_INIT();
	char* sql = "\n\
	    WITH cte_a AS (\n\
	        SELECT * FROM table_a\n\
	    ), cte_b AS (\n\
	        SELECT * FROM table_b\n\
	    )\n\
	    SELECT id FROM table_c\n\
	    LEFT JOIN cte_b ON table_c.id = cte_b.c_id\n\
	    EXCEPT\n\
	    SELECT * FROM cte_a\n\
	";
	Summary result = summary(sql, 0, -1);
	TEST_SUMMARY_ASSERT_TABLES(result.tables, ((char*[]){"table_a", "table_b", "table_c", NULL}));
	TEST_ASSERT_LIST_EQUAL(result.cte_names, list_make2("cte_a", "cte_b"));
	TEST_ASSERT_LIST_EQUAL(result.statement_types, list_make1("SelectStmt"));
}

void it_correctly_categorizes_CTEs_after_INTERSECT_SELECT(TestState* test_state) {
	TEST_INIT();
	char* sql = "\n\
	    WITH cte_a AS (\n\
	        SELECT * FROM table_a\n\
	    ), cte_b AS (\n\
	        SELECT * FROM table_b\n\
	    )\n\
	    SELECT id FROM table_c\n\
	    LEFT JOIN cte_b ON table_c.id = cte_b.c_id\n\
	    INTERSECT\n\
	    SELECT * FROM cte_a\n\
	";
	Summary result = summary(sql, 0, -1);
	TEST_SUMMARY_ASSERT_TABLES(result.tables, ((char*[]){"table_a", "table_b", "table_c", NULL}));
	TEST_ASSERT_LIST_EQUAL(result.cte_names, list_make2("cte_a", "cte_b"));
	TEST_ASSERT_LIST_EQUAL(result.statement_types, list_make1("SelectStmt"));
}

void it_finds_tables_inside_subselectes_in_MIN_MAX_COALESCE(TestState* test_state) {
	TEST_INIT();
	char* sql = "\n\
	    SELECT GREATEST(\n\
	        date_trunc($1, $2::timestamptz) + $3::interval,\n\
	        COALESCE(\n\
	            (\n\
	                SELECT first_aggregate_starts_at\n\
	                FROM schema_aggregate_infos\n\
	                WHERE base_table = $4 LIMIT $5\n\
	            ),\n\
	            now() + $6::interval\n\
	        )\n\
	    ) AS first_hourly_start_ts\n\
	";
	Summary result = summary(sql, 0, -1);
	TEST_SUMMARY_ASSERT_TABLES(result.tables, ((char*[]){"schema_aggregate_infos", NULL}));
	TEST_SUMMARY_ASSERT_TABLES_WITH_CTX(result.tables, CONTEXT_SELECT, ((char*[]){"schema_aggregate_infos", NULL}));
	TEST_ASSERT_LIST_EQUAL(result.statement_types, list_make1("SelectStmt"));
}

void it_finds_tables_inside_CASE_statements(TestState* test_state) {
	TEST_INIT();
	char* sql = "\n\
	    SELECT\n\
	    CASE\n\
	        WHEN id IN (SELECT foo_id FROM when_a) THEN (SELECT MAX(id) FROM then_a)\n\
	        WHEN id IN (SELECT foo_id FROM when_b) THEN (SELECT MAX(id) FROM then_b)\n\
	        ELSE (SELECT MAX(id) FROM elsey)\n\
	    END\n\
	    FROM foo\n\
	";
	Summary result = summary(sql, 0, -1);
	TEST_SUMMARY_ASSERT_TABLES(result.tables, ((char*[]){"elsey", "foo", "then_a", "then_b", "when_a", "when_b", NULL}));
	TEST_SUMMARY_ASSERT_TABLES_WITH_CTX(result.tables, CONTEXT_SELECT, ((char*[]){"elsey", "foo", "then_a", "then_b", "when_a", "when_b", NULL}));
	TEST_ASSERT_LIST_EQUAL(result.statement_types, list_make1("SelectStmt"));
}

void it_finds_tables_inside_casts(TestState* test_state) {
	TEST_INIT();
	char* sql = "\n\
	    SELECT 1\n\
	    FROM   foo\n\
	    WHERE  x = any(cast(array(SELECT a FROM bar) as bigint[]))\n\
	        OR x = any(array(SELECT a FROM baz)::bigint[])\n\
	";
	Summary result = summary(sql, 0, -1);
	TEST_SUMMARY_ASSERT_TABLES(result.tables, ((char*[]){"bar", "baz", "foo", NULL}));
	TEST_ASSERT_LIST_LENGTH(result.functions, 0);
	TEST_SUMMARY_ASSERT_FUNCTIONS_WITH_CTX(result.functions, CONTEXT_CALL, ((char*[]){NULL}));
	TEST_ASSERT_LIST_EQUAL(result.statement_types, list_make1("SelectStmt"));
}

void it_finds_functions_in_FROM_clause(TestState* test_state) {
	TEST_INIT();
	char* sql = "SELECT * FROM my_custom_func()";
	Summary result = summary(sql, 0, -1);
	TEST_ASSERT_LIST_LENGTH(result.tables, 0);
	TEST_SUMMARY_ASSERT_FUNCTIONS(result.functions, ((char*[]){"my_custom_func", NULL}));
	TEST_SUMMARY_ASSERT_FUNCTIONS_WITH_CTX(result.functions, CONTEXT_CALL, ((char*[]){"my_custom_func", NULL}));
	TEST_ASSERT_LIST_EQUAL(result.statement_types, list_make1("SelectStmt"));
}

void it_finds_functions_in_LATERAL_clause(TestState* test_state) {
	TEST_INIT();
	char* sql = "\n\
	    SELECT *\n\
	    FROM unnest($1::text[]) AS a(x)\n\
	    LEFT OUTER JOIN LATERAL (\n\
	        SELECT json_build_object($2, z.z)\n\
	        FROM (\n\
	            SELECT *\n\
	            FROM (\n\
	                SELECT row_to_json(\n\
	                    (SELECT * FROM (SELECT public.my_function(b) FROM public.c) d)\n\
	                )\n\
	            ) e\n\
	        ) f\n\
	    ) AS g ON (1)\n\
	";
	Summary result = summary(sql, 0, -1);
	TEST_SUMMARY_ASSERT_TABLES(result.tables, ((char*[]){"public.c", NULL}));
	TEST_SUMMARY_ASSERT_FUNCTIONS(result.functions, ((char*[]){"json_build_object", "public.my_function", "row_to_json", "unnest", NULL}));
	TEST_SUMMARY_ASSERT_FUNCTIONS_WITH_CTX(result.functions, CONTEXT_CALL, ((char*[]){"json_build_object", "public.my_function", "row_to_json", "unnest", NULL}));
	TEST_ASSERT_LIST_EQUAL(result.statement_types, list_make1("SelectStmt"));
}

void it_parses_INSERT(TestState* test_state) {
	TEST_INIT();
	Summary result = summary("insert into users(pk, name) values (1, 'bob');", 0, -1);
	TEST_SUMMARY_ASSERT_TABLES(result.tables, ((char*[]){"users", NULL}));

	result = summary("insert into users(pk, name) select pk, name from other_users;", 0, -1);
	TEST_SUMMARY_ASSERT_TABLES(result.tables, ((char*[]){"other_users", "users", NULL}));

	char* sql = "\n\
	    with cte as (\n\
	        select pk, name from other_users\n\
	    )\n\
	    insert into users(pk, name) select * from cte;\n\
	";
	result = summary(sql, 0, -1);
	TEST_SUMMARY_ASSERT_TABLES(result.tables, ((char*[]){"other_users", "users", NULL}));
	TEST_SUMMARY_ASSERT_TABLES_WITH_CTX(result.tables, CONTEXT_SELECT, ((char*[]){"other_users", NULL}));
	TEST_SUMMARY_ASSERT_TABLES_WITH_CTX(result.tables, CONTEXT_DML, ((char*[]){"users", NULL}));
	TEST_ASSERT_LIST_EQUAL(result.cte_names, list_make1("cte"));
	TEST_ASSERT_LIST_EQUAL(result.statement_types, list_make2("InsertStmt", "SelectStmt"));
}

void it_parses_UPDATE(TestState* test_state) {
	TEST_INIT();
	Summary result = summary("update users set name = 'bob';", 0, -1);
	TEST_SUMMARY_ASSERT_TABLES(result.tables, ((char*[]){"users", NULL}));
	TEST_ASSERT_LIST_EQUAL(result.statement_types, list_make1("UpdateStmt"));

	result = summary("update users set name = (select name from other_users limit 1);", 0, -1);
	TEST_SUMMARY_ASSERT_TABLES(result.tables, ((char*[]){"other_users", "users", NULL}));
	TEST_ASSERT_LIST_EQUAL(result.statement_types, list_make2("UpdateStmt", "SelectStmt"));

	char* sql = "\n\
	    with cte as (\n\
	        select name from other_users limit 1\n\
	    )\n\
	    update users set name = (select name from cte);\n\
	";
	result = summary(sql, 0, -1);
	TEST_SUMMARY_ASSERT_TABLES(result.tables, ((char*[]){"other_users", "users", NULL}));
	TEST_SUMMARY_ASSERT_TABLES_WITH_CTX(result.tables, CONTEXT_SELECT, ((char*[]){"other_users", NULL}));
	TEST_SUMMARY_ASSERT_TABLES_WITH_CTX(result.tables, CONTEXT_DML, ((char*[]){"users", NULL}));
	TEST_ASSERT_LIST_EQUAL(result.cte_names, list_make1("cte"));
	TEST_ASSERT_LIST_EQUAL(result.statement_types, list_make2("UpdateStmt", "SelectStmt"));

	sql = "\n\
	    UPDATE users SET name = users_new.name\n\
	    FROM users_new\n\
	    INNER JOIN join_table ON join_table.user_id = new_users.id\n\
	    WHERE users.id = users_new.id\n\
	";
	result = summary(sql, 0, -1);
	TEST_SUMMARY_ASSERT_TABLES(result.tables, ((char*[]){"join_table", "users", "users_new", NULL}));
	TEST_SUMMARY_ASSERT_TABLES_WITH_CTX(result.tables, CONTEXT_SELECT, ((char*[]){"join_table", "users_new", NULL}));
	TEST_SUMMARY_ASSERT_TABLES_WITH_CTX(result.tables, CONTEXT_DML, ((char*[]){"users", NULL}));
	TEST_ASSERT_LIST_EQUAL(result.statement_types, list_make1("UpdateStmt"));
}

void it_parses_DELETE(TestState* test_state) {
	TEST_INIT();
	Summary result = summary("DELETE FROM users;", 0, -1);
	TEST_SUMMARY_ASSERT_TABLES(result.tables, ((char*[]){"users", NULL}));
	TEST_SUMMARY_ASSERT_TABLES_WITH_CTX(result.tables, CONTEXT_DML, ((char*[]){"users", NULL}));
	TEST_ASSERT_LIST_EQUAL(result.statement_types, list_make1("DeleteStmt"));

	char* sql = "\n\
	    DELETE FROM users USING foo\n\
	    WHERE foo_id = foo.id AND foo.action = 'delete';\n\
	";
	result = summary(sql, 0, -1);
	TEST_SUMMARY_ASSERT_TABLES(result.tables, ((char*[]){"foo", "users", NULL}));
	TEST_SUMMARY_ASSERT_TABLES_WITH_CTX(result.tables, CONTEXT_SELECT, ((char*[]){"foo", NULL}));
	TEST_SUMMARY_ASSERT_TABLES_WITH_CTX(result.tables, CONTEXT_DML, ((char*[]){"users", NULL}));
	TEST_ASSERT_LIST_EQUAL(result.statement_types, list_make1("DeleteStmt"));

	sql = "\n\
	    DELETE FROM users\n\
	    WHERE foo_id IN (SELECT id FROM foo WHERE action = 'delete');\n\
	";
	result = summary(sql, 0, -1);
	TEST_SUMMARY_ASSERT_TABLES(result.tables, ((char*[]){"foo", "users", NULL}));
	TEST_SUMMARY_ASSERT_TABLES_WITH_CTX(result.tables, CONTEXT_SELECT, ((char*[]){"foo", NULL}));
	TEST_SUMMARY_ASSERT_TABLES_WITH_CTX(result.tables, CONTEXT_DML, ((char*[]){"users", NULL}));
	TEST_ASSERT_LIST_EQUAL(result.statement_types, list_make2("DeleteStmt", "SelectStmt"));
}

void it_parses_DROP_TYPE(TestState* test_state) {
	TEST_INIT();
	Summary result = summary("DROP TYPE IF EXISTS repack.pk_something", 0, -1);
	TEST_ASSERT_LIST_EQUAL(result.statement_types, list_make1("DropStmt"));

	// TODO: VERIFY THIS IS CORRECT.
	TEST_ASSERT_LIST_LENGTH(result.tables, 0);
	TEST_ASSERT_LIST_LENGTH(result.aliases, 0);
	TEST_ASSERT_LIST_LENGTH(result.cte_names, 0);
	TEST_ASSERT_LIST_LENGTH(result.functions, 0);
	TEST_ASSERT_LIST_LENGTH(result.filter_columns, 0);
	TEST_ASSERT_NULL(result.truncated_query);
}

// filter column tests

void it_finds_unqualified_names(TestState* test_state) {
	TEST_INIT();
	Summary result = summary("SELECT * FROM x WHERE y = $1 AND z = 1", 0, -1);
	TEST_ASSERT_LIST_LENGTH(result.filter_columns, 2);
	TEST_SUMMARY_ASSERT_FILTER_COLUMN(result.filter_columns, NULL, NULL, "y");
	TEST_SUMMARY_ASSERT_FILTER_COLUMN(result.filter_columns, NULL, NULL, "z");
}

void it_finds_qualified_names(TestState* test_state) {
	TEST_INIT();
	Summary result = summary("SELECT * FROM x WHERE x.y = $1 AND x.z = 1", 0, -1);
	TEST_ASSERT_LIST_LENGTH(result.filter_columns, 2);
	TEST_SUMMARY_ASSERT_FILTER_COLUMN(result.filter_columns, NULL, "x", "y");
	TEST_SUMMARY_ASSERT_FILTER_COLUMN(result.filter_columns, NULL, "x", "z");
}

void it_traverses_into_ctes(TestState* test_state) {
	TEST_INIT();
	Summary result = summary("WITH a AS (SELECT * FROM x WHERE x.y = $1 AND x.z = 1) SELECT * FROM a WHERE b = 5", 0, -1);
	TEST_ASSERT_LIST_LENGTH(result.filter_columns, 3);
	TEST_SUMMARY_ASSERT_FILTER_COLUMN(result.filter_columns, NULL, NULL, "b");
	TEST_SUMMARY_ASSERT_FILTER_COLUMN(result.filter_columns, NULL, "x", "y");
	TEST_SUMMARY_ASSERT_FILTER_COLUMN(result.filter_columns, NULL, "x", "z");
}

void it_recognizes_boolean_tests(TestState* test_state) {
	TEST_INIT();
	Summary result = summary("SELECT * FROM x WHERE x.y IS TRUE AND x.z IS NOT FALSE", 0, -1);
	TEST_ASSERT_LIST_LENGTH(result.filter_columns, 2);
	TEST_SUMMARY_ASSERT_FILTER_COLUMN(result.filter_columns, NULL, "x", "y");
	TEST_SUMMARY_ASSERT_FILTER_COLUMN(result.filter_columns, NULL, "x", "z");
}

void it_recognizes_null_tests(TestState* test_state) {
	TEST_INIT();
	Summary result = summary("SELECT * FROM x WHERE x.y IS NULL AND x.z IS NOT NULL", 0, -1);
	TEST_ASSERT_LIST_LENGTH(result.filter_columns, 2);
	TEST_SUMMARY_ASSERT_FILTER_COLUMN(result.filter_columns, NULL, "x", "y");
	TEST_SUMMARY_ASSERT_FILTER_COLUMN(result.filter_columns, NULL, "x", "z");
}

void it_finds_coalesce_argument_names(TestState* test_state) {
	TEST_INIT();
	Summary result = summary("SELECT * FROM x WHERE x.y = COALESCE(z.a, z.b)", 0, -1);
	TEST_ASSERT_LIST_LENGTH(result.filter_columns, 3);
	TEST_SUMMARY_ASSERT_FILTER_COLUMN(result.filter_columns, NULL, "x", "y");
	TEST_SUMMARY_ASSERT_FILTER_COLUMN(result.filter_columns, NULL, "z", "a");
	TEST_SUMMARY_ASSERT_FILTER_COLUMN(result.filter_columns, NULL, "z", "b");
}

void it_finds_unqualified_names_in_union_query(TestState* test_state) {
	TEST_INIT();
	Summary result = summary("SELECT * FROM x where y = $1 UNION SELECT * FROM x where z = $2", 0, -1);
	TEST_ASSERT_LIST_LENGTH(result.filter_columns, 2);
	TEST_SUMMARY_ASSERT_FILTER_COLUMN(result.filter_columns, NULL, NULL, "y");
	TEST_SUMMARY_ASSERT_FILTER_COLUMN(result.filter_columns, NULL, NULL, "z");
}

void it_finds_unqualified_names_in_union_all_query(TestState* test_state) {
	Summary result = summary("SELECT * FROM x where y = $1 UNION ALL SELECT * FROM x where z = $2", 0, -1);
	TEST_ASSERT_LIST_LENGTH(result.filter_columns, 2);
	TEST_SUMMARY_ASSERT_FILTER_COLUMN(result.filter_columns, NULL, NULL, "y");
	TEST_SUMMARY_ASSERT_FILTER_COLUMN(result.filter_columns, NULL, NULL, "z");
}

void it_finds_unqualified_names_in_except_query(TestState* test_state) {
	Summary result = summary("SELECT * FROM x where y = $1 EXCEPT SELECT * FROM x where z = $2", 0, -1);
	TEST_ASSERT_LIST_LENGTH(result.filter_columns, 2);
	TEST_SUMMARY_ASSERT_FILTER_COLUMN(result.filter_columns, NULL, NULL, "y");
	TEST_SUMMARY_ASSERT_FILTER_COLUMN(result.filter_columns, NULL, NULL, "z");
}

void it_finds_unqualified_names_in_except_all_query(TestState* test_state) {
	Summary result = summary("SELECT * FROM x where y = $1 EXCEPT ALL SELECT * FROM x where z = $2", 0, -1);
	TEST_ASSERT_LIST_LENGTH(result.filter_columns, 2);
	TEST_SUMMARY_ASSERT_FILTER_COLUMN(result.filter_columns, NULL, NULL, "y");
	TEST_SUMMARY_ASSERT_FILTER_COLUMN(result.filter_columns, NULL, NULL, "z");
}

void it_finds_unqualified_names_in_intersect_query(TestState* test_state) {
	Summary result = summary("SELECT * FROM x where y = $1 INTERSECT SELECT * FROM x where z = $2", 0, -1);
	TEST_ASSERT_LIST_LENGTH(result.filter_columns, 2);
	TEST_SUMMARY_ASSERT_FILTER_COLUMN(result.filter_columns, NULL, NULL, "y");
	TEST_SUMMARY_ASSERT_FILTER_COLUMN(result.filter_columns, NULL, NULL, "z");
}

void it_finds_unqualified_names_in_intersect_all_query(TestState* test_state) {
	Summary result = summary("SELECT * FROM x where y = $1 INTERSECT ALL SELECT * FROM x where z = $2", 0, -1);
	TEST_ASSERT_LIST_LENGTH(result.filter_columns, 2);
	TEST_SUMMARY_ASSERT_FILTER_COLUMN(result.filter_columns, NULL, NULL, "y");
	TEST_SUMMARY_ASSERT_FILTER_COLUMN(result.filter_columns, NULL, NULL, "z");
}

void it_ignores_target_list_columns(TestState* test_state) {
	Summary result = summary("SELECT a, y, z FROM x WHERE x.y = $1 AND x.z = 1", 0, -1);
	TEST_ASSERT_LIST_LENGTH(result.filter_columns, 2);
	TEST_SUMMARY_ASSERT_FILTER_COLUMN(result.filter_columns, NULL, "x", "y");
	TEST_SUMMARY_ASSERT_FILTER_COLUMN(result.filter_columns, NULL, "x", "z");
}

void it_ignores_order_by_columns(TestState* test_state) {
	Summary result = summary("SELECT * FROM x WHERE x.y = $1 AND x.z = 1 ORDER BY a, b", 0, -1);
	TEST_ASSERT_LIST_LENGTH(result.filter_columns, 2);
	TEST_SUMMARY_ASSERT_FILTER_COLUMN(result.filter_columns, NULL, "x", "y");
	TEST_SUMMARY_ASSERT_FILTER_COLUMN(result.filter_columns, NULL, "x", "z");
}

void it_handles_all_tables_in_schema(TestState* test_state) {
	Summary result = summary("GRANT SELECT ON ALL TABLES IN SCHEMA public TO myrole", 0, -1);
	TEST_ASSERT_LIST_LENGTH(result.filter_columns, 0);
}

void it_handles_schema_qualified_columns(TestState* test_state) {
	Summary result = summary("SELECT * FROM b.c WHERE a.b.c = 1", 0, -1);
	TEST_ASSERT_LIST_LENGTH(result.filter_columns, 1);
	TEST_SUMMARY_ASSERT_FILTER_COLUMN(result.filter_columns, "a", "b", "c");
}
