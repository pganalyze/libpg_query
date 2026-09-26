#!/usr/bin/env ruby

# rubocop:disable Metrics/MethodLength, Style/WordArray, Metrics/LineLength, Style/Documentation, Style/PerlBackrefs, Metrics/AbcSize, Metrics/CyclomaticComplexity, Metrics/PerceivedComplexity

require 'bundler'
require 'json'

class Generator
  def initialize
    @nodetypes = JSON.parse(File.read('./srcdata/nodetypes.json'))
    @struct_defs = JSON.parse(File.read('./srcdata/struct_defs.json'))
    @enum_defs = JSON.parse(File.read('./srcdata/enum_defs.json'))
    @typedefs = JSON.parse(File.read('./srcdata/typedefs.json'))
  end

  def underscore(camel_cased_word)
    return camel_cased_word unless /[A-Z-]|::/.match?(camel_cased_word)
    word = camel_cased_word.to_s.gsub("::", "/")
    word.gsub!(/^([A-Z\d])([A-Z][a-z])/, '\1__\2')
    word.gsub!(/([A-Z\d]+[a-z]+)([A-Z][a-z])/, '\1_\2')
    word.gsub!(/([a-z\d])([A-Z])/, '\1_\2')
    word.tr!("-", "_")
    word.downcase!
    word
  end

  TYPE_OVERRIDES = {
    ['Query', 'queryId'] => :skip, # we intentionally do not print the queryId field
    ['JsonTablePath', 'value'] => :skip,
  }
  OUTNAME_OVERRIDES = {
    ['CreateForeignTableStmt', 'base'] => 'base_stmt',
  }
  SCAN_ASCII_TOKENS = [36, 37, 40, 41, 42, 43, 44, 45, 46, 47, 58, 59, 60, 61, 62, 63, 91, 92, 93, 94]
  SCAN_KEYWORD_KINDS = ['NO_KEYWORD', 'UNRESERVED_KEYWORD', 'COL_NAME_KEYWORD', 'TYPE_FUNC_NAME_KEYWORD', 'RESERVED_KEYWORD']

  def generate_outmethods!
    @outmethods = {}
    @readmethods = {}
    @protobuf_messages = {}
    @protobuf_enums = {}
    @scan_protobuf_tokens = []
    @enum_to_strings = {}
    @enum_to_ints = {}
    @int_to_enums = {}

    ['nodes/parsenodes', 'nodes/primnodes'].each do |group|
      @struct_defs[group].each do |node_type, struct_def|
        @outmethods[node_type] = ''
        @readmethods[node_type] = ''
        @protobuf_messages[node_type] = ''
        protobuf_field_count = 1

        struct_def['fields'].each do |field_def|
          name = field_def['name']
          orig_type = field_def['c_type']

          # TODO: Add comments to protobuf definitions

          next unless name && orig_type

          type = TYPE_OVERRIDES[[node_type, name]] || orig_type
          outname = OUTNAME_OVERRIDES[[node_type, name]] || underscore(name)
          outname_json = name

          # NOTE: Every WRITE_*/READ_* macro takes the enclosing message type
          # (node_type) as its FIRST argument, so backends that use
          # per-message accessor functions (e.g. pg_query_<MsgType>_set_<field>)
          # can build their names. Keeping it first also lets the typedef-alias
          # handling below rewrite it with a simple gsub on "(<SourceType>, ".
          if type == :skip
            # Ignore
          elsif type == 'NodeTag'
            # Nothing
          elsif ['char'].include?(type)
            @outmethods[node_type] += format("  WRITE_CHAR_FIELD(%s, %s, %s, %s);\n", node_type, outname, outname_json, name)
            @readmethods[node_type] += format("  READ_CHAR_FIELD(%s, %s, %s, %s);\n", node_type, outname, outname_json, name)
            @protobuf_messages[node_type] += format("  string %s = %d [json_name=\"%s\"];\n", outname, protobuf_field_count, name)
            protobuf_field_count += 1
          elsif ['bool'].include?(type)
            @outmethods[node_type] += format("  WRITE_BOOL_FIELD(%s, %s, %s, %s);\n", node_type, outname, outname_json, name)
            @readmethods[node_type] += format("  READ_BOOL_FIELD(%s, %s, %s, %s);\n", node_type, outname, outname_json, name)
            @protobuf_messages[node_type] += format("  bool %s = %d [json_name=\"%s\"];\n", outname, protobuf_field_count, name)
            protobuf_field_count += 1
          elsif ['long'].include?(type)
            @outmethods[node_type] += format("  WRITE_LONG_FIELD(%s, %s, %s, %s);\n", node_type, outname, outname_json, name)
            @readmethods[node_type] += format("  READ_LONG_FIELD(%s, %s, %s, %s);\n", node_type, outname, outname_json, name)
            @protobuf_messages[node_type] += format("  int64 %s = %d [json_name=\"%s\"];\n", outname, protobuf_field_count, name)
            protobuf_field_count += 1
          elsif ['int', 'int16', 'int32', 'AttrNumber', 'ParseLoc'].include?(type)
            @outmethods[node_type] += format("  WRITE_INT_FIELD(%s, %s, %s, %s);\n", node_type, outname, outname_json, name)
            @readmethods[node_type] += format("  READ_INT_FIELD(%s, %s, %s, %s);\n", node_type, outname, outname_json, name)
            @protobuf_messages[node_type] += format("  int32 %s = %d [json_name=\"%s\"];\n", outname, protobuf_field_count, name)
            protobuf_field_count += 1
          elsif ['uint', 'uint16', 'uint32', 'Index', 'bits32', 'Oid', 'SubTransactionId', 'RelFileNumber'].include?(type)
            @outmethods[node_type] += format("  WRITE_UINT_FIELD(%s, %s, %s, %s);\n", node_type, outname, outname_json, name)
            @readmethods[node_type] += format("  READ_UINT_FIELD(%s, %s, %s, %s);\n", node_type, outname, outname_json, name)
            @protobuf_messages[node_type] += format("  uint32 %s = %d [json_name=\"%s\"];\n", outname, protobuf_field_count, name)
            protobuf_field_count += 1
          elsif ['uint64', 'AclMode'].include?(type)
            @outmethods[node_type] += format("  WRITE_UINT64_FIELD(%s, %s, %s, %s);\n", node_type, outname, outname_json, name)
            @readmethods[node_type] += format("  READ_UINT64_FIELD(%s, %s, %s, %s);\n", node_type, outname, outname_json, name)
            @protobuf_messages[node_type] += format("  uint64 %s = %d [json_name=\"%s\"];\n", outname, protobuf_field_count, name)
            protobuf_field_count += 1
          elsif type == 'char*'
            @outmethods[node_type] += format("  WRITE_STRING_FIELD(%s, %s, %s, %s);\n", node_type, outname, outname_json, name)
            @readmethods[node_type] += format("  READ_STRING_FIELD(%s, %s, %s, %s);\n", node_type, outname, outname_json, name)
            @protobuf_messages[node_type] += format("  string %s = %d [json_name=\"%s\"];\n", outname, protobuf_field_count, name)
            protobuf_field_count += 1
          elsif ['float', 'double', 'Cost', 'Cardinality', 'Selectivity'].include?(type)
            @outmethods[node_type] += format("  WRITE_FLOAT_FIELD(%s, %s, %s, %s);\n", node_type, outname, outname_json, name)
            @readmethods[node_type] += format("  READ_FLOAT_FIELD(%s, %s, %s, %s);\n", node_type, outname, outname_json, name)
            @protobuf_messages[node_type] += format("  double %s = %d [json_name=\"%s\"];\n", outname, protobuf_field_count, name)
            protobuf_field_count += 1
          elsif ['Bitmapset*', 'Relids'].include?(type)
            @outmethods[node_type] += format("  WRITE_BITMAPSET_FIELD(%s, %s, %s, %s);\n", node_type, outname, outname_json, name)
            @readmethods[node_type] += format("  READ_BITMAPSET_FIELD(%s, %s, %s, %s);\n", node_type, outname, outname_json, name)
            @protobuf_messages[node_type] += format("  repeated uint64 %s = %d [json_name=\"%s\"];\n", outname, protobuf_field_count, name)
            protobuf_field_count += 1
          elsif ['Value'].include?(type)
            @outmethods[node_type] += format("  WRITE_NODE_FIELD(%s, %s, %s, %s);\n", node_type, outname, outname_json, name)
            @readmethods[node_type] += format("  READ_VALUE_FIELD(%s, %s, %s, %s);\n", node_type, outname, outname_json, name)
            @protobuf_messages[node_type] += format("  Node %s = %d [json_name=\"%s\"];\n", outname, protobuf_field_count, name)
            protobuf_field_count += 1
          elsif ['Value*'].include?(type)
            @outmethods[node_type] += format("  WRITE_NODE_PTR_FIELD(%s, %s, %s, %s);\n", node_type, outname, outname_json, name)
            @readmethods[node_type] += format("  READ_VALUE_PTR_FIELD(%s, %s, %s, %s);\n", node_type, outname, outname_json, name)
            @protobuf_messages[node_type] += format("  Node %s = %d [json_name=\"%s\"];\n", outname, protobuf_field_count, name)
            protobuf_field_count += 1
          elsif ['List*'].include?(type)
            @outmethods[node_type] += format("  WRITE_LIST_FIELD(%s, %s, %s, %s);\n", node_type, outname, outname_json, name)
            @readmethods[node_type] += format("  READ_LIST_FIELD(%s, %s, %s, %s);\n", node_type, outname, outname_json, name)
            @protobuf_messages[node_type] += format("  repeated Node %s = %d [json_name=\"%s\"];\n", outname, protobuf_field_count, name)
            protobuf_field_count += 1
          elsif ['Node*'].include?(type)
            @outmethods[node_type] += format("  WRITE_NODE_PTR_FIELD(%s, %s, %s, %s);\n", node_type, outname, outname_json, name)
            @readmethods[node_type] += format("  READ_NODE_PTR_FIELD(%s, %s, %s, %s);\n", node_type, outname, outname_json, name)
            @protobuf_messages[node_type] += format("  Node %s = %d [json_name=\"%s\"];\n", outname, protobuf_field_count, name)
            protobuf_field_count += 1
          elsif ['Node'].include?(type)
            @outmethods[node_type] += format("  WRITE_NODE_FIELD(%s, %s, %s, %s);\n", node_type, outname, outname_json, name)
            @readmethods[node_type] += format("  READ_NODE_FIELD(%s, %s, %s, %s);\n", node_type, outname, outname_json, name)
            @protobuf_messages[node_type] += format("  Node %s = %d [json_name=\"%s\"];\n", outname, protobuf_field_count, name)
            protobuf_field_count += 1
          # Abstract node types that require casting.
          elsif ['Expr*', 'JsonTablePlan*'].include?(type)
            @outmethods[node_type] += format("  WRITE_NODE_PTR_FIELD(%s, %s, %s, %s);\n", node_type, outname, outname_json, name)
            @readmethods[node_type] += format("  READ_ABSTRACT_PTR_FIELD(%s, %s, %s, %s, %s);\n", node_type, outname, outname_json, name, type)
            @protobuf_messages[node_type] += format("  Node %s = %d [json_name=\"%s\"];\n", outname, protobuf_field_count, name)
            protobuf_field_count += 1
          # Abstract types that have no read or out methods.
          elsif ['Expr', 'JsonTablePlan'].include?(type)
            # FIXME
            @protobuf_messages[node_type] += format("  Node %s = %d [json_name=\"%s\"];\n", outname, protobuf_field_count, name)
            protobuf_field_count += 1
          elsif ['CreateStmt'].include?(type)
            @outmethods[node_type] += format("  WRITE_SPECIFIC_NODE_FIELD(%s, %s, %s, %s, %s, %s);\n", node_type, type.gsub('*', ''), underscore(type.gsub('*', '')).downcase, outname, outname_json, name)
            @readmethods[node_type] += format("  READ_SPECIFIC_NODE_FIELD(%s, %s, %s, %s, %s, %s);\n", node_type, type.gsub('*', ''), underscore(type.gsub('*', '')).downcase, outname, outname_json, name)
            @protobuf_messages[node_type] += format("  %s %s = %d [json_name=\"%s\"];\n", type.gsub('*', ''), outname, protobuf_field_count, name)
            protobuf_field_count += 1
          elsif @nodetypes.include?(type[0..-2])
            @outmethods[node_type] += format("  WRITE_SPECIFIC_NODE_PTR_FIELD(%s, %s, %s, %s, %s, %s);\n", node_type, type.gsub('*', ''), underscore(type.gsub('*', '')).downcase, outname, outname_json, name)
            @readmethods[node_type] += format("  READ_SPECIFIC_NODE_PTR_FIELD(%s, %s, %s, %s, %s, %s);\n", node_type, type.gsub('*', ''), underscore(type.gsub('*', '')).downcase, outname, outname_json, name)
            @protobuf_messages[node_type] += format("  %s %s = %d [json_name=\"%s\"];\n", type.gsub('*', ''), outname, protobuf_field_count, name)
            protobuf_field_count += 1
          elsif type.end_with?('*')
            puts format('ERR: %s %s', name, type)
          else # Enum
            @outmethods[node_type] += format("  WRITE_ENUM_FIELD(%s, %s, %s, %s, %s);\n", node_type, type, outname, outname_json, name)
            @readmethods[node_type] += format("  READ_ENUM_FIELD(%s, %s, %s, %s, %s);\n", node_type, type, outname, outname_json, name)
            @protobuf_messages[node_type] += format("  %s %s = %d [json_name=\"%s\"];\n", type, outname, protobuf_field_count, name)
            protobuf_field_count += 1
          end
        end
      end
    end

    ['nodes/parsenodes', 'nodes/primnodes', 'nodes/nodes', 'nodes/lockoptions', 'access/cmptype'].each do |group|
      @enum_defs[group].each do |enum_type, enum_def|
        next if enum_type == 'NodeTag'

        @protobuf_enums[enum_type] = format("enum %s\n{\n", enum_type)
        @enum_to_strings[enum_type] = format("static const char*\n_enumToString%s(%s value) {\n  switch(value) {\n", enum_type, enum_type)
        @enum_to_ints[enum_type] = format("static int\n_enumToInt%s(%s value) {\n  switch(value) {\n", enum_type, enum_type)
        @int_to_enums[enum_type] = format("static %s\n_intToEnum%s(int value) {\n  switch(value) {\n", enum_type, enum_type)

        # We intentionally add a dummy field for the zero value, that actually is not used in practice
        # - this ensures that the JSON output always includes the enum value (and doesn't skip it because its the zero value)
        @protobuf_enums[enum_type] += format("  %s_UNDEFINED = 0;\n", underscore(enum_type).upcase)
        protobuf_field = 1

        enum_def['values'].each do |value|
          next unless value['name']

          @protobuf_enums[enum_type] += format("  %s = %d;\n", value['name'], protobuf_field)
          @enum_to_strings[enum_type] += format("    case %s: return \"%s\";\n", value['name'], value['name'])
          @enum_to_ints[enum_type] += format("    case %s: return %d;\n", value['name'], protobuf_field)
          @int_to_enums[enum_type] += format("    case %d: return %s;\n", protobuf_field, value['name'])
          protobuf_field += 1
        end

        @protobuf_enums[enum_type] += "}"
        @enum_to_strings[enum_type] += "  }\n  Assert(false);\n  return NULL;\n}"
        @enum_to_ints[enum_type] += "  }\n  Assert(false);\n  return -1;\n}"
        @int_to_enums[enum_type] += format("  }\n  Assert(false);\n  return %s;\n}",  enum_def['values'].map { |v| v['name'] }.compact.first)
      end
    end

    # Single-character tokens that are returned 1:1 (identical with "self" list in scan.l)
    # Either supporting syntax, or single-character operators (some can be both)
    # Also see https://www.postgresql.org/docs/12/sql-syntax-lexical.html#SQL-SYNTAX-SPECIAL-CHARS
    @scan_token_names = [['NUL', 0]]
    SCAN_ASCII_TOKENS.each do |c|
      @scan_token_names << [format('ASCII_%d', c), c]
    end

    scan_values = @enum_defs['../backend/parser/gram']['yytokentype']['values']
    scan_values.each do |value|
      next unless value['name']
      @scan_protobuf_tokens << format('%s = %d;', value['name'], value['value'])
      @scan_token_names << [value['name'], value['value']]
    end

    @typedefs.each do |typedef|
      next unless @outmethods[typedef['source_type']]

      src = typedef['source_type']
      dst = typedef['new_type_name']
      # The new (aliased) type gets its own protobuf message, so the enclosing-type
      # token baked into each WRITE_*/READ_* macro must point at the alias, not
      # the source. Every macro takes that token as its first argument, so a
      # gsub on the "(<SourceType>, " prefix retargets them all.
      @outmethods[dst] = @outmethods[src].gsub("(#{src}, ", "(#{dst}, ")
      @readmethods[dst] = @readmethods[src].gsub("(#{src}, ", "(#{dst}, ")
      @protobuf_messages[dst] = @protobuf_messages[src]
    end
  end

  IGNORE_LIST = [
    'Value', # Special case
    'Const', # Only needed in post-parse analysis (and it introduces Datums, which we can't output)
  ]
  EXPLICT_TAG_SETS = [ # These nodes need an explicit NodeSetTag during read funcs because they are a superset of another node
    'CreateForeignTableStmt',
  ]
  def generate!
    generate_outmethods!

    out_defs = ''
    out_impls = ''
    out_conds = "case T_Integer:
  OUT_NODE(Integer, Integer, integer, INTEGER, Integer, integer);
  break;
case T_Boolean:
  OUT_NODE(Boolean, Boolean, boolean, BOOLEAN, Boolean, boolean);
  break;
case T_Float:
  OUT_NODE(Float, Float, float, FLOAT, Float, float_);
  break;
case T_String:
  OUT_NODE(String, String, string, STRING, String, string);
  break;
case T_BitString:
  OUT_NODE(BitString, BitString, bit_string, BIT_STRING, BitString, bit_string);
  break;
case T_List:
  OUT_NODE(List, List, list, LIST, List, list);
  break;
case T_IntList:
  OUT_NODE(IntList, IntList, int_list, INT_LIST, List, int_list);
  break;
case T_OidList:
  OUT_NODE(OidList, OidList, oid_list, OID_LIST, List, oid_list);
  break;
case T_A_Const:
  OUT_NODE(A_Const, AConst, a__const, A_CONST, A_Const, a_const);
  break;
"
    read_defs = ''
    read_impls = ''
    read_conds = ''
    protobuf_messages = ''
    protobuf_nodes = []

    @nodetypes.each do |type|
      next if IGNORE_LIST.include?(type)
      outmethod = @outmethods[type]
      readmethod = @readmethods[type]
      next unless outmethod && readmethod

      c_type = type.gsub(/_/, '')

      out_defs += format("static void _out%s(OUT_TYPE(%s, %s) out_node, const %s *node);\n", c_type, type, c_type, type)

      out_impls += "static void\n"
      out_impls += format("_out%s(OUT_TYPE(%s, %s) out, const %s *node)\n", c_type, type, c_type, type)
      out_impls += "{\n"
      out_impls += outmethod
      out_impls += "}\n"
      out_impls += "\n"

      out_conds += format("case T_%s:\n", type)
      out_conds += format("  OUT_NODE(%s, %s, %s, %s, %s, %s);\n", type, c_type, underscore(c_type), underscore(c_type).upcase.gsub('__', '_'), type, underscore(type))
      out_conds += "  break;\n"

      read_defs += format("static %s * _read%s(const OUT_TYPE(%s, %s) msg);\n", type, c_type, type, c_type)

      read_impls += format("static %s *\n", type)
      read_impls += format("_read%s(const OUT_TYPE(%s, %s) msg)\n", c_type, type, c_type)
      read_impls += "{\n"
      read_impls += format("  %s *node = makeNode(%s);\n", type, type)
      read_impls += readmethod
      read_impls += format("  NodeSetTag(node, T_%s);\n", type) if EXPLICT_TAG_SETS.include?(type)
      read_impls += "  return node;\n"
      read_impls += "}\n"
      read_impls += "\n"

      read_conds += format("  READ_COND(%s, %s, %s, %s, %s, %s);\n", type, c_type, underscore(c_type), underscore(c_type).upcase.gsub('__', '_'), type, underscore(type))

      protobuf_messages += format("message %s\n{\n", type)
      protobuf_messages += @protobuf_messages[type] || ''
      protobuf_messages += "}\n\n"

      protobuf_nodes << format("%s %s = %d [json_name=\"%s\"];", type, underscore(type), protobuf_nodes.size + 1, type)
    end

    ['Integer', 'Float', 'Boolean', 'String', 'BitString', 'List', 'IntList', 'OidList', 'A_Const'].each do |type|
      protobuf_nodes << format("%s %s = %d [json_name=\"%s\"];", type, underscore(type), protobuf_nodes.size + 1, type)
    end

    protobuf_messages += @protobuf_enums.values.join("\n\n")

    File.write('./src/include/pg_query_enum_defs.c', "// This file is autogenerated by ./scripts/generate_protobuf_and_funcs.rb\n\n" +
      @enum_to_strings.values.join("\n\n") + @enum_to_ints.values.join("\n\n") + @int_to_enums.values.join("\n\n"))

    File.write('./src/include/pg_query_outfuncs_defs.c', "// This file is autogenerated by ./scripts/generate_protobuf_and_funcs.rb\n\n" +
      out_defs + "\n\n" + out_impls)

    File.write('./src/include/pg_query_outfuncs_conds.c', "// This file is autogenerated by ./scripts/generate_protobuf_and_funcs.rb\n\n" + out_conds)

    File.write('./src/include/pg_query_readfuncs_defs.c', "// This file is autogenerated by ./scripts/generate_protobuf_and_funcs.rb\n\n" +
      read_defs + "\n\n" + read_impls)

    File.write('./src/include/pg_query_readfuncs_conds.c', "// This file is autogenerated by ./scripts/generate_protobuf_and_funcs.rb\n\n" + read_conds)

    protobuf = "// This file is autogenerated by ./scripts/generate_protobuf_and_funcs.rb

syntax = \"proto3\";

package pg_query;

message ParseResult {
  int32 version = 1;
  repeated RawStmt stmts = 2;
}

message ScanResult {
  int32 version = 1;
  repeated ScanToken tokens = 2;
}

message Node {
  oneof node {
		#{protobuf_nodes.join("\n    ")}
  }
}

message Integer
{
  int32 ival = 1; /* machine integer */
}

message Float
{
  string fval = 1; /* string */
}

message Boolean
{
  bool boolval = 1;
}

message String
{
  string sval = 1; /* string */
}

message BitString
{
  string bsval = 1; /* string */
}

message List
{
  repeated Node items = 1;
}

message OidList
{
  repeated Node items = 1;
}

message IntList
{
  repeated Node items = 1;
}

message A_Const
{
  oneof val {
    Integer ival = 1;
    Float fval = 2;
    Boolean boolval = 3;
    String sval = 4;
    BitString bsval = 5;
  }
  bool isnull = 10;
  int32 location = 11;
}

#{protobuf_messages}

message ScanToken {
  int32 start = 1;
  int32 end = 2;
  Token token = 4;
  KeywordKind keyword_kind = 5;
}

enum KeywordKind {
  #{SCAN_KEYWORD_KINDS.each_with_index.map { |name, i| format('%s = %d;', name, i) }.join("\n  ")}
}

enum Token {
  NUL = 0;
  // Single-character tokens that are returned 1:1 (identical with \"self\" list in scan.l)
  // Either supporting syntax, or single-character operators (some can be both)
  // Also see https://www.postgresql.org/docs/12/sql-syntax-lexical.html#SQL-SYNTAX-SPECIAL-CHARS
  #{SCAN_ASCII_TOKENS.map { |c| format('ASCII_%d = %d; // "%s"', c, c, c.chr) }.join("\n  ")}
  // Named tokens in scan.l
  #{@scan_protobuf_tokens.join("\n  ")}
}


// protobuf-c doesn't support optional fields, so any optional strings
// are just an empty string if it should be the equivalent of None/nil.
//
// These fields have `// optional` at the end of the line.
//
// Upstream issue: https://github.com/protobuf-c/protobuf-c/issues/476
message SummaryResult {
  enum Context {
    None = 0;
    Select = 1;
    DML = 2;
    DDL = 3;
    Call = 4;
  }

  message Table {
    string name = 1;
    string schema_name = 2;
    string table_name = 3;
    Context context = 4;
  }
  repeated Table tables = 1;

  // The value here is the table name (i.e. schema.table or just table).
  map<string, string> aliases = 2;

  repeated string cte_names = 3;

  message Function {
    string name = 1;
    string function_name = 2;
    string schema_name = 3; // optional
    Context context = 4;
  }
  repeated Function functions = 4;

  message FilterColumn {
    string schema_name = 1; // optional
    string table_name = 2; // optional
    string column = 3;
  }
  repeated FilterColumn filter_columns = 5;
  repeated string statement_types = 6;
  string truncated_query = 7; /* optional, empty if truncation limit is -1 */
}
"

    File.write('./protobuf/pg_query.proto', protobuf)

    # Public C enums for the scan token API, mirroring the Token and KeywordKind
    # enums above (included from pg_query.h)
    ascii_tokens = SCAN_ASCII_TOKENS.map { |c| format('PG_QUERY_TOKEN_ASCII_%d = %d, // "%s"', c, c, c.chr) }
    named_tokens = @scan_token_names.drop(1 + SCAN_ASCII_TOKENS.size).map { |name, v| format('PG_QUERY_TOKEN_%s = %d,', name, v) }
    File.write('./pg_query_scan_tokens.h', "// This file is autogenerated by ./scripts/generate_protobuf_and_funcs.rb

#ifndef PG_QUERY_SCAN_TOKENS_H
#define PG_QUERY_SCAN_TOKENS_H

// Tokens returned by the Postgres scanner, as used by pg_query_scan_tokens.
//
// The values are the token numbers of the Postgres grammar (identical to the
// Token enum in protobuf/pg_query.proto). They change between Postgres
// versions, since Bison numbers tokens in declaration order, so compare by
// name rather than by value.
typedef enum {
  PG_QUERY_TOKEN_NUL = 0,
  // Single-character tokens that are returned 1:1 (identical with \"self\" list in scan.l)
  // Either supporting syntax, or single-character operators (some can be both)
  // Also see https://www.postgresql.org/docs/12/sql-syntax-lexical.html#SQL-SYNTAX-SPECIAL-CHARS
  #{ascii_tokens.join("\n  ")}
  // Named tokens in scan.l
  #{named_tokens.join("\n  ")}
} PgQueryToken;

// Keyword category of a token, as used by pg_query_scan_tokens (identical to
// the KeywordKind enum in protobuf/pg_query.proto). This is the Postgres
// keyword category shifted by one, so that non-keywords are zero.
typedef enum {
  #{SCAN_KEYWORD_KINDS.each_with_index.map { |name, i| format('PG_QUERY_%s = %d,', name, i) }.join("\n  ")}
} PgQueryKeywordKind;

#endif
")

    # Name lookups for the enums above (declared in pg_query.h, included from
    # pg_query_scan.c)
    File.write('./src/include/pg_query_scan_defs.c', "// This file is autogenerated by ./scripts/generate_protobuf_and_funcs.rb

const char *
pg_query_keyword_kind_name(PgQueryKeywordKind keyword_kind)
{
  switch (keyword_kind) {
    #{SCAN_KEYWORD_KINDS.map { |name| format('case PG_QUERY_%s: return "%s";', name, name) }.join("\n    ")}
  }
  return NULL;
}

const char *
pg_query_token_name(PgQueryToken token)
{
  switch (token) {
    #{@scan_token_names.map { |name, _| format('case PG_QUERY_TOKEN_%s: return "%s";', name, name) }.join("\n    ")}
  }
  return NULL;
}
")
  end
end

Generator.new.generate!
