#!/usr/bin/env ruby

# rubocop:disable Metrics/AbcSize, Metrics/LineLength, Metrics/MethodLength, Style/WordArray, Metrics/ClassLength, Style/Documentation, Metrics/CyclomaticComplexity, Metrics/PerceivedComplexity, Style/MutableConstant, Style/TrailingCommaInLiteral

require 'bundler'
require 'json'

class Generator
  def initialize
    @nodetypes = JSON.parse(File.read('./srcdata/nodetypes.json'))
    @struct_defs = JSON.parse(File.read('./srcdata/struct_defs.json'))
    @enum_defs = JSON.parse(File.read('./srcdata/enum_defs.json'))
    @typedefs = JSON.parse(File.read('./srcdata/typedefs.json'))
    @all_known_enums = JSON.parse(File.read('./srcdata/all_known_enums.json'))
  end

  # The _fingerprintChild* helpers are implemented in pg_query_fingerprint.c,
  # and take care of hashing the field name and rolling it back if the child
  # node ends up contributing nothing to the fingerprint.
  FINGERPRINT_NODE = <<-EOL
  _fingerprintChildNode(ctx, &node->%<name>s, node, "%<name>s", depth);

  EOL

  FINGERPRINT_NODE_PTR = <<-EOL
  if (node->%<name>s != NULL)
    _fingerprintChildNode(ctx, node->%<name>s, node, "%<name>s", depth);

  EOL

  # Calls the node's fingerprint function directly, bypassing the
  # _fingerprintNode dispatch switch. Unlike FINGERPRINT_NODE_PTR, this does
  # not hash the node's type name.
  FINGERPRINT_SPECIFIC_NODE_PTR = <<-EOL
  if (node->%<name>s != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "%<name>s");
    _fingerprint%<typename>s(ctx, node->%<name>s, node, "%<name>s", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  EOL

  FINGERPRINT_LIST = <<-EOL
  if (node->%<name>s != NULL && node->%<name>s->length > 0)
    _fingerprintChildList(ctx, node->%<name>s, node, "%<name>s", depth);

  EOL

  # Scalar fields are handled by the _fingerprint*Field helpers in
  # pg_query_fingerprint.c, which skip zero/NULL/false values.
  FINGERPRINT_INT = <<-EOL
  _fingerprintIntField(ctx, "%<name>s", node->%<name>s);

  EOL

  FINGERPRINT_LONG_INT = <<-EOL
  _fingerprintLongField(ctx, "%<name>s", node->%<name>s);

  EOL

  FINGERPRINT_UINT64 = <<-EOL
  _fingerprintUInt64Field(ctx, "%<name>s", node->%<name>s);

  EOL

  FINGERPRINT_FLOAT = <<-EOL
  _fingerprintFloatField(ctx, "%<name>s", node->%<name>s);

  EOL

  FINGERPRINT_CHAR = <<-EOL
  _fingerprintCharField(ctx, "%<name>s", node->%<name>s);

  EOL

  FINGERPRINT_CHAR_PTR = <<-EOL
  _fingerprintStringField(ctx, "%<name>s", node->%<name>s);

  EOL

  FINGERPRINT_STRING = <<-EOL
  _fingerprintStringNodeField(ctx, "%<name>s", node->%<name>s);

  EOL

  FINGERPRINT_BOOL = <<-EOL
  _fingerprintBoolField(ctx, "%<name>s", node->%<name>s);

  EOL

  FINGERPRINT_INT_ARRAY = <<-EOL
  _fingerprintBitmapsetField(ctx, "%<name>s", node->%<name>s);

  EOL

  FINGERPRINT_ENUM = <<-EOL
  _fingerprintEnumField(ctx, "%<name>s", _enumToString%<typename>s(node->%<name>s));

  EOL

  # Fingerprinting additional code to be inserted
  FINGERPRINT_SKIP_NODES = [
    'A_Const',
    'Alias',
    'ParamRef',
    'SetToDefault',
    'IntList',
    'OidList',
    'Null',
  ]
  # Node types with a custom fingerprint implementation in
  # src/pg_query_fingerprint.c. The generator only emits the declaration
  # and the dispatch case for these, not the function definition.
  FINGERPRINT_CUSTOM_NODES = [
    'RangeVar',
  ]
  # Fields with a custom fingerprint implementation in
  # src/pg_query_fingerprint.c (_fingerprint<Node>_<field>). The generator
  # emits a call instead of the standard per-type handling for these.
  FINGERPRINT_CUSTOM_FIELDS = [
    ['ResTarget', 'name'],
    ['A_Expr', 'kind'],
  ]
  FINGERPRINT_OVERRIDE_FIELDS = {
    [nil, 'location'] => :skip,
    [nil, 'list_start'] => :skip,
    [nil, 'list_end'] => :skip,
    ['A_Expr', 'rexpr_list_start'] => :skip,
    ['A_Expr', 'rexpr_list_end'] => :skip,
    ['PrepareStmt', 'name'] => :skip,
    ['ExecuteStmt', 'name'] => :skip,
    ['DeallocateStmt', 'name'] => :skip,
    ['TransactionStmt', 'options'] => :skip,
    ['TransactionStmt', 'gid'] => :skip,
    ['TransactionStmt', 'savepoint_name'] => :skip,
    ['CreateFunctionStmt', 'options'] => :skip,
    ['FunctionParameter', 'name'] => :skip,
    ['DoStmt', 'args'] => :skip,
    ['ListenStmt', 'conditionname'] => :skip,
    ['UnlistenStmt', 'conditionname'] => :skip,
    ['NotifyStmt', 'conditionname'] => :skip,
    ['NotifyStmt', 'payload'] => :skip,
    ['DeclareCursorStmt', 'portalname'] => :skip,
    ['FetchStmt', 'portalname'] => :skip,
    ['ClosePortalStmt', 'portalname'] => :skip,
    ['RawStmt', 'stmt_len'] => :skip,
    ['RawStmt', 'stmt_location'] => :skip,
    ['JsonTablePath', 'value'] => :skip,
    ['JsonTablePathSpec', 'name_location'] => :skip,
    ['JsonTablePathSpec', 'location'] => :skip,
    ['VariableSetStmt', 'jumble_args'] => :skip, # TODO: Should we be smarter about using this flag ourselves?
  }
  INT_TYPES = ['bits32', 'uint32', 'int', 'int32', 'uint16', 'int16', 'Oid', 'Index', 'AttrNumber', 'SubTransactionId', 'RelFileNumber', 'ParseLoc']
  LONG_INT_TYPES = ['long']
  UINT64_TYPES = ['uint64', 'AclMode']
  INT_ARRAY_TYPES = ['Bitmapset*', 'Bitmapset', 'Relids']
  FLOAT_TYPES = ['Cost', 'double', 'Cardinality']

  IGNORE_FOR_GENERATOR = ['Integer', 'Float', 'String', 'BitString', 'List']

  def generate_fingerprint_defs!
    @fingerprint_defs = {}

    ['nodes/parsenodes', 'nodes/primnodes'].each do |group|
      @struct_defs[group].each do |type, struct_def|
        next if struct_def['fields'].nil?
        next if IGNORE_FOR_GENERATOR.include?(type)

        if FINGERPRINT_SKIP_NODES.include?(type)
          fingerprint_def = "  // Intentionally ignoring all fields for fingerprinting\n"
        elsif FINGERPRINT_CUSTOM_NODES.include?(type)
          fingerprint_def = :custom
        else
          fingerprint_def = ''
          struct_def['fields'].reject { |f| f['name'].nil? }.sort_by { |f| f['name'] }.each do |field|
            name = field['name']
            field_type = field['c_type']

            if FINGERPRINT_CUSTOM_FIELDS.include?([type, name])
              fingerprint_def += format("  _fingerprint%s_%s(ctx, node, parent, field_name, depth);\n\n", type, name)
              next
            end

            fp_override = FINGERPRINT_OVERRIDE_FIELDS[[type, field['name']]] || FINGERPRINT_OVERRIDE_FIELDS[[nil, field['name']]]
            if fp_override
              if fp_override == :skip
                fp_override = format("  // Intentionally ignoring node->%s for fingerprinting\n\n", name)
              end
              fingerprint_def += fp_override
              next
            end

            case field_type
            # when '[][]Node'
            #  fingerprint_def += format(FINGERPRINT_NODE_ARRAY_ARRAY, name: name)
            # when '[]Node'
            #  fingerprint_def += format(FINGERPRINT_NODE_ARRAY, name: name)
            when 'Node', 'JsonTablePlan'
              fingerprint_def += format(FINGERPRINT_NODE, name: name)
            when 'Node*', 'Expr*', 'JsonTablePlan*'
              fingerprint_def += format(FINGERPRINT_NODE_PTR, name: name)
            when 'List*'
              fingerprint_def += format(FINGERPRINT_LIST, name: name)
            when 'CreateStmt'
              fingerprint_def += format("  _fingerprintString(ctx, \"%s\");\n", name)
              fingerprint_def += format("  _fingerprintCreateStmt(ctx, (const CreateStmt*) &node->%s, node, \"%s\", depth);\n", name, name)
            when 'char'
              fingerprint_def += format(FINGERPRINT_CHAR, name: name)
            when 'char*'
              fingerprint_def += format(FINGERPRINT_CHAR_PTR, name: name)
            when 'String*'
              fingerprint_def += format(FINGERPRINT_STRING, name: name)
            when 'bool'
              fingerprint_def += format(FINGERPRINT_BOOL, name: name)
            when 'Datum', 'void*', 'Expr', 'NodeTag'
              # Ignore
            when *INT_TYPES
              fingerprint_def += format(FINGERPRINT_INT, name: name)
            when *LONG_INT_TYPES
              fingerprint_def += format(FINGERPRINT_LONG_INT, name: name)
            when *UINT64_TYPES
              fingerprint_def += format(FINGERPRINT_UINT64, name: name)
            when *INT_ARRAY_TYPES
              fingerprint_def += format(FINGERPRINT_INT_ARRAY, name: name)
            when *FLOAT_TYPES
              fingerprint_def += format(FINGERPRINT_FLOAT, name: name)
            else
              if field_type.end_with?('*') && @nodetypes.include?(field_type[0..-2])
                typename = field_type[0..-2]
                fingerprint_def += format(FINGERPRINT_SPECIFIC_NODE_PTR, name: name, typename: typename)
              elsif @all_known_enums.include?(field_type)
                fingerprint_def += format(FINGERPRINT_ENUM, name: name, typename: field_type)
              else
                # This shouldn't happen - if it does the above is missing something :-)
                puts type
                puts name
                puts field_type
                raise type
              end
            end
          end
        end

        @fingerprint_defs[type] = fingerprint_def
      end
    end
  end

  def generate!
    generate_fingerprint_defs!

    defs = ''
    conds = ''

    @nodetypes.each do |type|
      fingerprint_def = @fingerprint_defs[type]
      next unless fingerprint_def
      defs += format("static void _fingerprint%s(FingerprintContext *ctx, const %s *node, const void *parent, const char *field_name, unsigned int depth);\n", type, type)
    end
    defs += "\n\n"

    @nodetypes.each do |type|
      # next if IGNORE_LIST.include?(type)
      fingerprint_def = @fingerprint_defs[type]
      next unless fingerprint_def

      if fingerprint_def == :custom
        defs += format("// _fingerprint%s has a custom implementation, see pg_query_fingerprint.c\n\n", type)
      else
        defs += "static void\n"
        defs += format("_fingerprint%s(FingerprintContext *ctx, const %s *node, const void *parent, const char *field_name, unsigned int depth)\n", type, type)
        defs += "{\n"
        defs += fingerprint_def
        defs += "}\n"
        defs += "\n"
      end

      conds += format("case T_%s:\n", type)
      if FINGERPRINT_SKIP_NODES.include?(type)
        conds += format("  // Intentionally ignoring for fingerprinting\n")
      else
        conds += format("  if (!IsA(castNode(TypeCast, (void*) obj)->arg, A_Const) && !IsA(castNode(TypeCast, (void*) obj)->arg, ParamRef))\n  {\n") if type == 'TypeCast'
        conds += format("  _fingerprintString(ctx, \"%s\");\n", type)
        conds += format("  _fingerprint%s(ctx, obj, parent, field_name, depth);\n", type)
        conds += "  }\n" if type == 'TypeCast'
      end
      conds += "  break;\n"
    end

    File.write('./src/include/pg_query_fingerprint_defs.c', defs)
    File.write('./src/include/pg_query_fingerprint_conds.c', conds)
  end
end

Generator.new.generate!
