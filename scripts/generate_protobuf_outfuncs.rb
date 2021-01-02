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
  }
  OUTNAME_OVERRIDES = {
    ['CreateForeignTableStmt', 'base'] => 'base_stmt',
  }

  def generate_outmethods!
    @outmethods = {}
    @protobuf_messages = {}
    @protobuf_enums = {}
    @scan_protobuf_tokens = []

    ['nodes/parsenodes', 'nodes/primnodes'].each do |group|
      @struct_defs[group].each do |node_type, struct_def|
        @outmethods[node_type] = ''
        @protobuf_messages[node_type] = ''
        protobuf_field_count = 1

        struct_def['fields'].each do |field_def|
          name = field_def['name']
          orig_type = field_def['c_type']

          # TODO: Add comments to protobuf definitions

          next unless name && orig_type

          type = TYPE_OVERRIDES[[node_type, name]] || orig_type
          outname = OUTNAME_OVERRIDES[[node_type, name]] || underscore(name)

          if type == :skip
            # Ignore
          elsif type == 'NodeTag'
            # Nothing
          elsif ['char'].include?(type)
            @outmethods[node_type] += format("  WRITE_CHAR_FIELD(%s, %s);\n", outname, name)
            @protobuf_messages[node_type] += format("  string %s = %d [json_name=\"%s\"];\n", outname, protobuf_field_count, name)
            protobuf_field_count += 1
          elsif ['bool'].include?(type)
            @outmethods[node_type] += format("  WRITE_BOOL_FIELD(%s, %s);\n", outname, name)
            @protobuf_messages[node_type] += format("  bool %s = %d [json_name=\"%s\"];\n", outname, protobuf_field_count, name)
            protobuf_field_count += 1
          elsif ['long'].include?(type)
            @outmethods[node_type] += format("  WRITE_LONG_FIELD(%s, %s);\n", outname, name)
            @protobuf_messages[node_type] += format("  int64 %s = %d [json_name=\"%s\"];\n", outname, protobuf_field_count, name)
            protobuf_field_count += 1
          elsif ['int', 'int16', 'int32', 'AttrNumber'].include?(type)
            @outmethods[node_type] += format("  WRITE_INT_FIELD(%s, %s);\n", outname, name)
            @protobuf_messages[node_type] += format("  int32 %s = %d [json_name=\"%s\"];\n", outname, protobuf_field_count, name)
            protobuf_field_count += 1
          elsif ['uint', 'uint16', 'uint32', 'Index', 'bits32', 'Oid', 'AclMode', 'SubTransactionId'].include?(type)
            @outmethods[node_type] += format("  WRITE_UINT_FIELD(%s, %s);\n", outname, name)
            @protobuf_messages[node_type] += format("  uint32 %s = %d [json_name=\"%s\"];\n", outname, protobuf_field_count, name)
            protobuf_field_count += 1
          elsif type == 'char*'
            @outmethods[node_type] += format("  WRITE_STRING_FIELD(%s, %s);\n", outname, name)
            @protobuf_messages[node_type] += format("  string %s = %d [json_name=\"%s\"];\n", outname, protobuf_field_count, name)
            protobuf_field_count += 1
          elsif ['float', 'double', 'Cost', 'Selectivity'].include?(type)
            @outmethods[node_type] += format("  WRITE_FLOAT_FIELD(%s, %s);\n", outname, name)
            @protobuf_messages[node_type] += format("  double %s = %d [json_name=\"%s\"];\n", outname, protobuf_field_count, name)
            protobuf_field_count += 1
          elsif ['Bitmapset*', 'Relids'].include?(type)
            @outmethods[node_type] += format("  WRITE_BITMAPSET_FIELD(%s, %s);\n", outname, name) # FIXME
            # FIXME: Add to protobuf
          elsif ['Value'].include?(type)
            @outmethods[node_type] += format("  WRITE_NODE_FIELD(%s, %s);\n", outname, name)
            @protobuf_messages[node_type] += format("  Node %s = %d [json_name=\"%s\"];\n", outname, protobuf_field_count, name)
            protobuf_field_count += 1
          elsif ['Value', 'Value*'].include?(type)
            @outmethods[node_type] += format("  WRITE_NODE_PTR_FIELD(%s, %s);\n", outname, name)
            @protobuf_messages[node_type] += format("  Node %s = %d [json_name=\"%s\"];\n", outname, protobuf_field_count, name)
            protobuf_field_count += 1
          elsif ['List*'].include?(type)
            @outmethods[node_type] += format("  WRITE_LIST_FIELD(%s, %s);\n", outname, name)
            @protobuf_messages[node_type] += format("  repeated Node %s = %d [json_name=\"%s\"];\n", outname, protobuf_field_count, name)
            protobuf_field_count += 1
          elsif ['Node*', 'Expr*'].include?(type)
            @outmethods[node_type] += format("  WRITE_NODE_PTR_FIELD(%s, %s);\n", outname, name)
            @protobuf_messages[node_type] += format("  Node %s = %d [json_name=\"%s\"];\n", outname, protobuf_field_count, name)
            protobuf_field_count += 1
          elsif ['Expr'].include?(type)
            # FIXME
            @protobuf_messages[node_type] += format("  Node %s = %d [json_name=\"%s\"];\n", outname, protobuf_field_count, name)
            protobuf_field_count += 1
          elsif ['CreateStmt'].include?(type)
            @outmethods[node_type] += format("  WRITE_SPECIFIC_NODE_FIELD(%s, %s, %s, %s);\n", type.gsub('*', ''), underscore(type.gsub('*', '')).downcase, outname, name)
            @protobuf_messages[node_type] += format("  %s %s = %d [json_name=\"%s\"];\n", type.gsub('*', ''), outname, protobuf_field_count, name)
            protobuf_field_count += 1
          elsif @nodetypes.include?(type[0..-2])
            @outmethods[node_type] += format("  WRITE_SPECIFIC_NODE_PTR_FIELD(%s, %s, %s, %s);\n", type.gsub('*', ''), underscore(type.gsub('*', '')).downcase, outname, name)
            @protobuf_messages[node_type] += format("  %s %s = %d [json_name=\"%s\"];\n", type.gsub('*', ''), outname, protobuf_field_count, name)
            protobuf_field_count += 1
          elsif type.end_with?('*')
            puts format('ERR: %s %s', name, type)
          else # Enum
            @outmethods[node_type] += format("  WRITE_ENUM_FIELD(%s, %s, %s);\n", type, outname, name)
            @protobuf_messages[node_type] += format("  %s %s = %d [json_name=\"%s\"];\n", type, outname, protobuf_field_count, name)
            protobuf_field_count += 1
          end
        end
      end
    end

    ['nodes/parsenodes', 'nodes/primnodes', 'nodes/nodes', 'nodes/lockoptions'].each do |group|
      @enum_defs[group].each do |enum_type, enum_def|
        next if enum_type == 'NodeTag'

        @protobuf_enums[enum_type] = ''
        enum_field_count = 0
        enum_def['values'].each do |value|
          next unless value['name']

          @protobuf_enums[enum_type] += format("  %s = %d;\n", value['name'], enum_field_count)
          enum_field_count += 1
        end
      end
    end

    scan_values = @enum_defs['../backend/parser/gram']['yytokentype']['values']
    scan_values.each do |value|
      next unless value['name']
      @scan_protobuf_tokens << format('%s = %d;', value['name'], value['value'])
    end

    @typedefs.each do |typedef|
      next unless @outmethods[typedef['source_type']]

      @outmethods[typedef['new_type_name']] = @outmethods[typedef['source_type']]
      @protobuf_messages[typedef['new_type_name']] = @protobuf_messages[typedef['source_type']]
    end
  end

  IGNORE_LIST = [
    'Value', # Special case
    'Const', # Only needed in post-parse analysis (and it introduces Datums, which we can't output)
  ]
  def generate!
    generate_outmethods!

    defs = ''
    impls = ''
    conds = ''
    protobuf = ''
    protobuf_nodes = []

    @nodetypes.each do |type|
      next if IGNORE_LIST.include?(type)
      outmethod = @outmethods[type]
      next unless outmethod

      out_type = type.gsub(/_/, '')

      defs += format("static void _out%s(%s * out_node, const %s *node);\n", out_type, 'PgQuery__' + out_type, type)

      impls += "static void\n"
      impls += format("_out%s(%s * out_node, const %s *node)\n", out_type, 'PgQuery__' + out_type, type)
      impls += "{\n"
      impls += outmethod
      impls += "}\n"
      impls += "\n"

      conds += format("case T_%s:\n", type)
      conds += format("  OUT_NODE(%s, %s, %s, %s);\n", out_type, underscore(out_type), type, underscore(type))
      conds += "  break;\n"

      protobuf += format("message %s\n{\n", type)
      protobuf += @protobuf_messages[type] || ''
      protobuf += "}\n\n"

      protobuf_nodes << format("%s %s = %d [json_name=\"%s\"];", type, underscore(type), protobuf_nodes.size + 1, type)
    end

    ['Integer', 'Float', 'String', 'BitString', 'Null', 'List', 'IntList', 'OidList'].each do |type|
      protobuf_nodes << format("%s %s = %d [json_name=\"%s\"];", type, underscore(type), protobuf_nodes.size + 1, type)
    end

    @protobuf_enums.each do |type, out|
      protobuf += format("enum %s\n{\n", type)
      protobuf += out
      protobuf += "}\n\n"
    end

    protobuf_header = "// This file is autogenerated by ./scripts/generate_protobuf/outfuncs.rb

syntax = \"proto3\";

package pg_query;

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
  string str = 1; /* string */
}

message String
{
  string str = 1; /* string */
}

message BitString
{
  string str = 1; /* string */
}

message Null
{
  // intentionally empty
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

"

    File.write('./src/pg_query_protobuf_defs.c', defs + impls)
    File.write('./src/pg_query_protobuf_conds.c', conds)
    File.write('./protobuf/parse_tree.proto', protobuf_header + protobuf)

    scan_protobuf = "// This file is autogenerated by ./scripts/generate_protobuf/outfuncs.rb

syntax = \"proto3\";

package pg_query;

message ScanOutput {
  repeated ScanToken tokens = 1;
}

message ScanToken {
  int32 start = 1;
  int32 end = 2;
  Token token = 4;
  KeywordKind keyword_kind = 5;
}

enum KeywordKind {
  NO_KEYWORD = 0;
  UNRESERVED_KEYWORD = 1;
  COL_NAME_KEYWORD = 2;
  TYPE_FUNC_NAME_KEYWORD = 3;
  RESERVED_KEYWORD = 4;
}

enum Token {
  NUL = 0;
  // Single-character tokens that are returned 1:1 (identical with \"self\" list in scan.l)
  // Either supporting syntax, or single-character operators (some can be both)
  // Also see https://www.postgresql.org/docs/12/sql-syntax-lexical.html#SQL-SYNTAX-SPECIAL-CHARS
  ASCII_37 = 37; // \"%\"
  ASCII_40 = 40; // \"\(\"
  ASCII_41 = 41; // \")\"
  ASCII_42 = 42; // \"*\"
  ASCII_43 = 43; // \"+\"
  ASCII_44 = 44; // \",\"
  ASCII_45 = 45; // \"-\"
  ASCII_46 = 46; // \".\"
  ASCII_47 = 47; // \"/\"
  ASCII_58 = 58; // \":\"
  ASCII_59 = 59; // \";\"
  ASCII_60 = 60; // \"<\"
  ASCII_61 = 61; // \"=\"
  ASCII_62 = 62; // \">\"
  ASCII_63 = 63; // \"?\"
  ASCII_91 = 91; // \"[\"
  ASCII_93 = 93; // \"]\"
  ASCII_94 = 94; // \"^\"
  // Named tokens in scan.l
  #{@scan_protobuf_tokens.join("\n  ")}
}
"
    File.write('./protobuf/scan_output.proto', scan_protobuf)
  end
end

Generator.new.generate!
