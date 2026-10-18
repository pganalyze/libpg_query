const char* tests[] = {
  "SELECT 1",
  "0",
  "50fde20626009aba",
  "integer",
  "1",
  "c71927729d707de5",
  "character varying(32)",
  "1",
  "453ab4df8fd3eea9",
  "EXISTS(SELECT 1)",
  "2",
  "976a797c8ca2985b",
  "v_version IS NULL",
  "2",
  "6b292a26fcb78b1c",
  "pos:= instr($1, $2, 1)",
  "3",
  "786552659cc61f6f",
  "temp_str := substring(string FROM beg_index)",
  "3",
  "d6671d73f1654866",
  "v3.c1 := 4",
  "4",
  "a8c86658ce26a653",
  "NEW.name = upper(cleanString(NEW.name))",
  "4",
  "bb52450e4d46f7a1",
  "NEW.author.first_name = upper(cleanString(NEW.author.first_name))",
  "5",
  "a148e3f78b53c252",
  NULL // Trailing NULL to tell the test runner we're done.
};

// Tests for fingerprint options (query, fingerprint options as integer, expected fingerprint)
//
// 0 = PG_QUERY_FINGERPRINT_DEFAULT
// 1 = PG_QUERY_FINGERPRINT_RANGEVAR_IGNORE_ALIASES
// 2 = PG_QUERY_FINGERPRINT_RANGEVAR_INCLUDE_SCHEMA
// 3 = PG_QUERY_FINGERPRINT_RANGEVAR_PG17_COMPAT
// 16 = PG_QUERY_FINGERPRINT_FULL_RELNAME
// 19 = PG_QUERY_FINGERPRINT_RANGEVAR_PG17_COMPAT | PG_QUERY_FINGERPRINT_FULL_RELNAME
const char* fingerprint_option_tests[] = {
  // By default, 2+ consecutive digits in the relation name are ignored (these two match)
  "SELECT * FROM orders_2024_01",
  "0",
  "0e612f391ad711b8",
  "SELECT * FROM orders_2024_02",
  "0",
  "0e612f391ad711b8",
  // With PG_QUERY_FINGERPRINT_FULL_RELNAME the full relation name is fingerprinted (these two differ)
  "SELECT * FROM orders_2024_01",
  "16",
  "3cc2d1ca3f22c9bf",
  "SELECT * FROM orders_2024_02",
  "16",
  "291f96ac98cf4c38",
  // By default (Postgres 18+ behavior), the alias replaces the relation name, and the schema name is ignored
  "SELECT * FROM sales",
  "0",
  "4d93c901b91cb364",
  "SELECT * FROM public.sales", // matches the unqualified reference above
  "0",
  "4d93c901b91cb364",
  "SELECT * FROM sales s",
  "0",
  "93a3bbe18171c380",
  // With PG_QUERY_FINGERPRINT_RANGEVAR_IGNORE_ALIASES, aliases are ignored (matches "SELECT * FROM sales" above)
  "SELECT * FROM sales s",
  "1",
  "4d93c901b91cb364",
  // With PG_QUERY_FINGERPRINT_RANGEVAR_INCLUDE_SCHEMA, the schema name is fingerprinted (differs from "SELECT * FROM sales" above)
  "SELECT * FROM public.sales",
  "2",
  "78d676e53f612747",
  // ... whilst aliases still replace the relation name
  "SELECT * FROM public.sales s",
  "2",
  "9cf22829ca3b350b",
  // PG17_COMPAT matches the fingerprint from libpg_query 17 (which was 4e3d1136f89c4229 by default in libpg_query 18)
  "MERGE into measurement m USING new_measurement nm ON (m.city_id = nm.city_id and m.logdate=nm.logdate) WHEN MATCHED AND nm.peaktemp IS NULL THEN DELETE WHEN MATCHED THEN UPDATE SET peaktemp = greatest(m.peaktemp, nm.peaktemp), unitsales = m.unitsales + coalesce(nm.unitsales, 0) WHEN NOT MATCHED THEN INSERT (city_id, logdate, peaktemp, unitsales) VALUES (city_id, logdate, peaktemp, unitsales)",
  "3",
  "fe086f143f4c7ed9",
  // All flags combined
  "SELECT * FROM public.orders_2024_01 o",
  "19",
  "115077f8a9c3c10d",
  NULL // Trailing NULL to tell the test runner we're done.
};
