CREATE UNIQUE INDEX schema_tables_database_id_schema_name_table_name_idx
ON public.schema_tables USING btree (database_id, schema_name, table_name)
WHERE removed_at IS NULL
