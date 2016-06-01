const char* tests[] = {
  "DECLARE \n\
      r foo%rowtype; \n\
  BEGIN \n\
    SELECT * FROM foo WHERE fooid > 0; \n\
    RETURN; \n\
  END",
  "{\"PLpgSQL_function\": {\"datums\": [{\"PLpgSQL_var\": {\"refname\": \"found\", \"datatype\": {\"PLpgSQL_type\": {\"typname\": \"UNKNOWN\"}}}}, {\"PLpgSQL_var\": {\"refname\": \"r\", \"lineno\": 2, \"datatype\": {\"PLpgSQL_type\": {\"typname\": \"foo%rowtype\"}}}}], \"action\": {\"PLpgSQL_stmt_block\": {\"lineno\": 3, \"body\": [{\"PLpgSQL_stmt_execsql\": {\"lineno\": 4, \"sqlstmt\": {\"PLpgSQL_expr\": {\"query\": \"SELECT * FROM foo WHERE fooid > 0\"}}}}, {\"PLpgSQL_stmt_return\": {\"lineno\": 5}}]}}}}",
  "BEGIN \n\
      IF v_version IS NULL THEN \n\
          RETURN v_name; \n\
      END IF; \n\
      RETURN v_name || '/' || v_version; \n\
  END;",
  "{\"PLpgSQL_function\": {\"datums\": [{\"PLpgSQL_var\": {\"refname\": \"found\", \"datatype\": {\"PLpgSQL_type\": {\"typname\": \"UNKNOWN\"}}}}], \"action\": {\"PLpgSQL_stmt_block\": {\"lineno\": 1, \"body\": [{\"PLpgSQL_stmt_if\": {\"lineno\": 2, \"cond\": {\"PLpgSQL_expr\": {\"query\": \"SELECT v_version IS NULL\"}}, \"then_body\": [{\"PLpgSQL_stmt_return\": {\"lineno\": 3, \"expr\": {\"PLpgSQL_expr\": {\"query\": \"SELECT v_name\"}}}}]}}, {\"PLpgSQL_stmt_return\": {\"lineno\": 5, \"expr\": {\"PLpgSQL_expr\": {\"query\": \"SELECT v_name || '/' || v_version\"}}}}]}}}}",
  "INVALID SYNTAX",
  "[]",
  "DECLARE \n\
    referrer_key RECORD;  -- declare a generic record to be used in a FOR \n\
    func_body text; \n\
    func_cmd text; \n\
  BEGIN \n\
    func_body := 'BEGIN'; \n\
    -- Notice how we scan through the results of a query in a FOR loop \n\
    -- using the FOR <record> construct. \n\
    FOR referrer_key IN SELECT * FROM cs_referrer_keys ORDER BY try_order LOOP \n\
        func_body := func_body || \n\
          ' IF v_' || referrer_key.kind \n\
          || ' LIKE ' || quote_literal(referrer_key.key_string) \n\
          || ' THEN RETURN ' || quote_literal(referrer_key.referrer_type) \n\
          || '; END IF;' ; \n\
    END LOOP; \n\
    func_body := func_body || ' RETURN NULL; END;'; \n\
    func_cmd := \n\
      'CREATE OR REPLACE FUNCTION cs_find_referrer_type(v_host varchar, \n\
                                                        v_domain varchar, \n\
                                                        v_url varchar) \n\
        RETURNS varchar AS ' \n\
      || quote_literal(func_body) \n\
      || ' LANGUAGE plpgsql;' ; \n\
    EXECUTE func_cmd; \n\
  END;",
  "{\"PLpgSQL_function\": {\"datums\": [{\"PLpgSQL_var\": {\"refname\": \"found\", \"datatype\": {\"PLpgSQL_type\": {\"typname\": \"UNKNOWN\"}}}}, {\"PLpgSQL_var\": {\"refname\": \"referrer_key\", \"lineno\": 2, \"datatype\": {\"PLpgSQL_type\": {\"typname\": \"RECORD\"}}}}, {\"PLpgSQL_var\": {\"refname\": \"func_body\", \"lineno\": 3, \"datatype\": {\"PLpgSQL_type\": {\"typname\": \"text\"}}}}, {\"PLpgSQL_var\": {\"refname\": \"func_cmd\", \"lineno\": 4, \"datatype\": {\"PLpgSQL_type\": {\"typname\": \"text\"}}}}, {\"PLpgSQL_row\": {\"refname\": \"*internal*\", \"lineno\": 9, \"fields\": [{\"name\": \"referrer_key\", \"varno\": 1}]}}], \"action\": {\"PLpgSQL_stmt_block\": {\"lineno\": 5, \"body\": [{\"PLpgSQL_stmt_assign\": {\"lineno\": 6, \"varno\": 2, \"expr\": {\"PLpgSQL_expr\": {\"query\": \"SELECT 'BEGIN'\"}}}}, {\"PLpgSQL_stmt_fors\": {\"lineno\": 9, \"row\": {\"PLpgSQL_row\": {\"refname\": \"*internal*\", \"lineno\": 9, \"fields\": [{\"name\": \"referrer_key\", \"varno\": 1}]}}, \"body\": [{\"PLpgSQL_stmt_assign\": {\"lineno\": 10, \"varno\": 2, \"expr\": {\"PLpgSQL_expr\": {\"query\": \"SELECT func_body || \\n          ' IF v_' || referrer_key.kind \\n          || ' LIKE ' || quote_literal(referrer_key.key_string) \\n          || ' THEN RETURN ' || quote_literal(referrer_key.referrer_type) \\n          || '; END IF;'\"}}}}], \"query\": {\"PLpgSQL_expr\": {\"query\": \"SELECT * FROM cs_referrer_keys ORDER BY try_order\"}}}}, {\"PLpgSQL_stmt_assign\": {\"lineno\": 16, \"varno\": 2, \"expr\": {\"PLpgSQL_expr\": {\"query\": \"SELECT func_body || ' RETURN NULL; END;'\"}}}}, {\"PLpgSQL_stmt_assign\": {\"lineno\": 17, \"varno\": 3, \"expr\": {\"PLpgSQL_expr\": {\"query\": \"SELECT 'CREATE OR REPLACE FUNCTION cs_find_referrer_type(v_host varchar, \\n                                                        v_domain varchar, \\n                                                        v_url varchar) \\n        RETURNS varchar AS ' \\n      || quote_literal(func_body) \\n      || ' LANGUAGE plpgsql;'\"}}}}, {\"PLpgSQL_stmt_dynexecute\": {\"lineno\": 24, \"query\": {\"PLpgSQL_expr\": {\"query\": \"SELECT func_cmd\"}}}}, {\"PLpgSQL_stmt_return\": {}}]}}}}",
};

size_t testsLength = 8;
