#!/usr/bin/env ruby
# frozen_string_literal: true

# Extracts pg_type definitions from postgres.bki and generates an inline
# data table plus lookup helpers in src/include/pg_query_pg_type.c.
#
# The helpers are consumed by the manually maintained mocks
# scripts/mocks/SearchSysCache1.c and scripts/mocks/GetSysCacheOid.c, so
# adding a new built-in type only requires re-running this script.

BKI_FILE = File.join(__dir__, '../tmp/postgres/src/include/catalog/postgres.bki')
PG_TYPE_D_FILE = File.join(__dir__, '../src/postgres/include/catalog/pg_type_d.h')
PG_COLLATION_D_FILE = File.join(__dir__, '../src/postgres/include/catalog/pg_collation_d.h')
OUTPUT_FILE = File.join(__dir__, '../src/include/pg_query_pg_type.c')

TYPTYPE_MAP = {
  'b' => 'TYPTYPE_BASE',
  'c' => 'TYPTYPE_COMPOSITE',
  'd' => 'TYPTYPE_DOMAIN',
  'e' => 'TYPTYPE_ENUM',
  'm' => 'TYPTYPE_MULTIRANGE',
  'p' => 'TYPTYPE_PSEUDO',
  'r' => 'TYPTYPE_RANGE',
}.freeze

TYPCATEGORY_MAP = {
  'A' => 'TYPCATEGORY_ARRAY',
  'B' => 'TYPCATEGORY_BOOLEAN',
  'C' => 'TYPCATEGORY_COMPOSITE',
  'D' => 'TYPCATEGORY_DATETIME',
  'E' => 'TYPCATEGORY_ENUM',
  'G' => 'TYPCATEGORY_GEOMETRIC',
  'I' => 'TYPCATEGORY_NETWORK',
  'N' => 'TYPCATEGORY_NUMERIC',
  'P' => 'TYPCATEGORY_PSEUDOTYPE',
  'R' => 'TYPCATEGORY_RANGE',
  'S' => 'TYPCATEGORY_STRING',
  'T' => 'TYPCATEGORY_TIMESPAN',
  'U' => 'TYPCATEGORY_USER',
  'V' => 'TYPCATEGORY_BITSTRING',
  'X' => 'TYPCATEGORY_UNKNOWN',
  'Z' => 'TYPCATEGORY_INTERNAL',
}.freeze

TYPALIGN_MAP = {
  'c' => 'TYPALIGN_CHAR',
  's' => 'TYPALIGN_SHORT',
  'i' => 'TYPALIGN_INT',
  'd' => 'TYPALIGN_DOUBLE',
}.freeze

def extract_pg_types(bki_path)
  content = File.read(bki_path)

  # Find the pg_type section
  pg_type_section = content[/create pg_type.*?^close pg_type/m]
  raise "Could not find pg_type section in #{bki_path}" unless pg_type_section

  # Extract column names from the schema definition
  # Format is: " (\n col = type ,\n col = type\n )"
  schema_match = pg_type_section.match(/^ \(\n(.*?)^ \)/m)
  raise 'Could not parse pg_type schema' unless schema_match

  columns = schema_match[1].scan(/^ (\w+) =/).flatten

  # Extract insert statements
  types = []
  pg_type_section.scan(/^insert \( (.+?) \)$/) do |match|
    values = parse_values(match[0])

    type_hash = {}
    columns.each_with_index do |col, idx|
      type_hash[col.to_sym] = normalize_value(values[idx])
    end
    types << type_hash
  end

  types
end

def parse_values(line)
  values = []
  current = +''
  in_quote = false

  line.chars.each do |char|
    case char
    when "'"
      in_quote = !in_quote
      current << char
    when ' '
      if in_quote
        current << char
      elsif !current.empty?
        values << current
        current = +''
      end
    else
      current << char
    end
  end
  values << current unless current.empty?

  values
end

def normalize_value(val)
  case val
  when '_null_'
    nil
  when '-'
    nil
  when 't'
    true
  when 'f'
    false
  when /^\d+$/
    val.to_i
  when /^-\d+$/
    val.to_i
  when /^'(.)'$/
    Regexp.last_match(1)
  else
    val
  end
end

# Parse the OID -> macro-name mapping from pg_type_d.h, so the generated
# data table can reference types symbolically (e.g. BOOLOID instead of 16).
def parse_oid_macros(pg_type_d_path)
  content = File.read(pg_type_d_path)
  macros = {}
  content.scan(/^#define\s+([A-Z_0-9]+OID)\s+(\d+)/) do |name, oid|
    macros[oid.to_i] = name
  end
  macros
end

# Parse the collation OID -> macro-name mapping from pg_collation_d.h.
def parse_collation_macros(pg_collation_d_path)
  content = File.read(pg_collation_d_path)
  macros = {}
  content.scan(/^#define\s+([A-Z_0-9]+_COLLATION_OID)\s+(\d+)/) do |name, oid|
    macros[oid.to_i] = name
  end
  macros
end

def format_oid(oid, oid_macros)
  return 'InvalidOid' if oid.nil? || oid == 0
  oid_macros[oid] || oid.to_s
end

# Map BKI symbols that are resolved by initdb at runtime to equivalent C
# expressions so the data table can be a plain static initializer.
BKI_SYMBOL_TO_C_EXPR = {
  'SIZEOF_POINTER' => 'sizeof(void *)',
  'ALIGNOF_POINTER' => '(SIZEOF_VOID_P == 8 ? TYPALIGN_DOUBLE : TYPALIGN_INT)',
}.freeze

def translate_bki_symbol(val)
  BKI_SYMBOL_TO_C_EXPR[val] || val
end

def format_typbyval(val)
  case val
  when true then 'true'
  when false then 'false'
  else translate_bki_symbol(val.to_s) # FLOAT8PASSBYVAL and similar symbolic values pass through
  end
end

def format_typlen(val)
  return val.to_s if val.is_a?(Integer)
  translate_bki_symbol(val.to_s) # NAMEDATALEN, SIZEOF_POINTER, etc.
end

def format_char_field(val, map)
  return "'\\0'" if val.nil? || val.empty?
  return map[val] if map.key?(val)
  # A single char that's not in the map: emit a char literal. A multi-char
  # value (e.g. ALIGNOF_POINTER) is a symbolic C constant and passes through.
  val.length == 1 ? "'#{val}'" : translate_bki_symbol(val)
end

def generate_helper_c(types, oid_macros, collation_macros)
  rows = types.map do |t|
    oid_macro = oid_macros[t[:oid]] || t[:oid].to_s
    fields = [
      oid_macro,
      "\"#{t[:typname]}\"",
      format_typlen(t[:typlen]),
      format_typbyval(t[:typbyval]),
      format_char_field(t[:typtype], TYPTYPE_MAP),
      format_char_field(t[:typcategory], TYPCATEGORY_MAP),
      format_char_field(t[:typalign], TYPALIGN_MAP),
      format_oid(t[:typarray], oid_macros),
      format_oid(t[:typcollation], collation_macros),
    ]
    "\t{ #{fields.join(', ')} },"
  end

  <<~EOC
    /*
     * This file is autogenerated by ./scripts/extract_pg_types.rb
     *
     * It provides inline pg_type data for the SearchSysCache1 / GetSysCacheOid
     * mocks used when running the Postgres parser outside of a backend.
     */

    #ifndef PG_QUERY_PG_TYPE_C
    #define PG_QUERY_PG_TYPE_C

    typedef struct PgQueryBuiltinType
    {
    \tOid\t\toid;
    \tconst char *typname;
    \tint16\t\ttyplen;
    \tbool\t\ttypbyval;
    \tchar\t\ttyptype;
    \tchar\t\ttypcategory;
    \tchar\t\ttypalign;
    \tOid\t\ttyparray;
    \tOid\t\ttypcollation;
    } PgQueryBuiltinType;

    static const PgQueryBuiltinType pg_query_builtin_types[] = {
    #{rows.join("\n")}
    };

    static const PgQueryBuiltinType *
    pg_query_builtin_type_by_oid(Oid oid)
    {
    \tfor (size_t i = 0; i < lengthof(pg_query_builtin_types); i++)
    \t{
    \t\tif (pg_query_builtin_types[i].oid == oid)
    \t\t\treturn &pg_query_builtin_types[i];
    \t}
    \treturn NULL;
    }

    static Oid
    pg_query_builtin_type_oid_by_name(const char *typname)
    {
    \tfor (size_t i = 0; i < lengthof(pg_query_builtin_types); i++)
    \t{
    \t\tif (strcmp(pg_query_builtin_types[i].typname, typname) == 0)
    \t\t\treturn pg_query_builtin_types[i].oid;
    \t}
    \treturn InvalidOid;
    }

    #endif /* PG_QUERY_PG_TYPE_C */
  EOC
end

if __FILE__ == $PROGRAM_NAME
  types = extract_pg_types(BKI_FILE)
  oid_macros = parse_oid_macros(PG_TYPE_D_FILE)
  collation_macros = parse_collation_macros(PG_COLLATION_D_FILE)
  File.write(OUTPUT_FILE, generate_helper_c(types, oid_macros, collation_macros))
  puts "Wrote #{OUTPUT_FILE} (#{types.size} types)"
end
