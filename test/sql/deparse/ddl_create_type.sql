CREATE TYPE public.schema_table_event_type AS ENUM (
    'manual_vacuum',
    'auto_vacuum',
    'manual_analyze',
    'auto_analyze'
)
