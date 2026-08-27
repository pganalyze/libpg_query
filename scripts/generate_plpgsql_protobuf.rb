#!/usr/bin/env ruby

# Generate PLpgSQL protobuf schema and serialization code
# Uses JSON files from srcdata/ produced by extract_plpgsql_headers.rb

require 'bundler'
require 'json'

class PLpgSQLGenerator
  def initialize
    @struct_defs = JSON.parse(File.read('./srcdata/plpgsql_struct_defs.json'))
    @enum_defs = JSON.parse(File.read('./srcdata/plpgsql_enum_defs.json'))
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

  # Convert PLpgSQL_type to PLpgSQLType (protobuf-c type name style)
  # Removes underscores and capitalizes first letter of each part
  def protobuf_c_type_name(name)
    parts = name.split('_')
    parts.map { |p| p[0].upcase + p[1..-1].to_s }.join
  end

  # Convert PLpgSQL_type to plpg_sql_type (protobuf-c function name style)
  # Insert underscore before uppercase that follows lowercase, then lowercase all
  def protobuf_c_func_name(name)
    name.gsub(/([a-z])([A-Z])/, '\1_\2').downcase
  end

  # Statement types - these need to be handled via cmd_type dispatch
  STMT_TYPES = %w[
    PLpgSQL_stmt_block PLpgSQL_stmt_assign PLpgSQL_stmt_perform
    PLpgSQL_stmt_call PLpgSQL_stmt_commit PLpgSQL_stmt_rollback
    PLpgSQL_stmt_getdiag PLpgSQL_stmt_if PLpgSQL_stmt_case
    PLpgSQL_stmt_loop PLpgSQL_stmt_while PLpgSQL_stmt_fori
    PLpgSQL_stmt_fors PLpgSQL_stmt_forc PLpgSQL_stmt_dynfors
    PLpgSQL_stmt_foreach_a PLpgSQL_stmt_open PLpgSQL_stmt_fetch
    PLpgSQL_stmt_close PLpgSQL_stmt_exit PLpgSQL_stmt_return
    PLpgSQL_stmt_return_next PLpgSQL_stmt_return_query PLpgSQL_stmt_raise
    PLpgSQL_stmt_assert PLpgSQL_stmt_execsql PLpgSQL_stmt_dynexecute
  ]

  # Datum types - these need to be handled via dtype dispatch
  DATUM_TYPES = %w[
    PLpgSQL_var PLpgSQL_row PLpgSQL_rec PLpgSQL_recfield
  ]

  # Helper types (not dispatched via enum)
  HELPER_TYPES = %w[
    PLpgSQL_type PLpgSQL_expr PLpgSQL_condition PLpgSQL_exception_block
    PLpgSQL_exception PLpgSQL_if_elsif PLpgSQL_case_when PLpgSQL_diag_item
    PLpgSQL_raise_option PLpgSQL_function
  ]

  # Fields to skip (these are runtime fields or abstract base types)
  SKIP_STRUCTS = %w[
    PLpgSQL_datum PLpgSQL_variable PLpgSQL_stmt PLpgSQL_stmt_forq
  ]

  # Map stmt_type enum values to struct names
  STMT_TYPE_MAP = {
    'PLPGSQL_STMT_BLOCK' => 'PLpgSQL_stmt_block',
    'PLPGSQL_STMT_ASSIGN' => 'PLpgSQL_stmt_assign',
    'PLPGSQL_STMT_IF' => 'PLpgSQL_stmt_if',
    'PLPGSQL_STMT_CASE' => 'PLpgSQL_stmt_case',
    'PLPGSQL_STMT_LOOP' => 'PLpgSQL_stmt_loop',
    'PLPGSQL_STMT_WHILE' => 'PLpgSQL_stmt_while',
    'PLPGSQL_STMT_FORI' => 'PLpgSQL_stmt_fori',
    'PLPGSQL_STMT_FORS' => 'PLpgSQL_stmt_fors',
    'PLPGSQL_STMT_FORC' => 'PLpgSQL_stmt_forc',
    'PLPGSQL_STMT_FOREACH_A' => 'PLpgSQL_stmt_foreach_a',
    'PLPGSQL_STMT_EXIT' => 'PLpgSQL_stmt_exit',
    'PLPGSQL_STMT_RETURN' => 'PLpgSQL_stmt_return',
    'PLPGSQL_STMT_RETURN_NEXT' => 'PLpgSQL_stmt_return_next',
    'PLPGSQL_STMT_RETURN_QUERY' => 'PLpgSQL_stmt_return_query',
    'PLPGSQL_STMT_RAISE' => 'PLpgSQL_stmt_raise',
    'PLPGSQL_STMT_ASSERT' => 'PLpgSQL_stmt_assert',
    'PLPGSQL_STMT_EXECSQL' => 'PLpgSQL_stmt_execsql',
    'PLPGSQL_STMT_DYNEXECUTE' => 'PLpgSQL_stmt_dynexecute',
    'PLPGSQL_STMT_DYNFORS' => 'PLpgSQL_stmt_dynfors',
    'PLPGSQL_STMT_GETDIAG' => 'PLpgSQL_stmt_getdiag',
    'PLPGSQL_STMT_OPEN' => 'PLpgSQL_stmt_open',
    'PLPGSQL_STMT_FETCH' => 'PLpgSQL_stmt_fetch',
    'PLPGSQL_STMT_CLOSE' => 'PLpgSQL_stmt_close',
    'PLPGSQL_STMT_PERFORM' => 'PLpgSQL_stmt_perform',
    'PLPGSQL_STMT_CALL' => 'PLpgSQL_stmt_call',
    'PLPGSQL_STMT_COMMIT' => 'PLpgSQL_stmt_commit',
    'PLPGSQL_STMT_ROLLBACK' => 'PLpgSQL_stmt_rollback',
  }

  # Map datum_type enum values to struct names
  DATUM_TYPE_MAP = {
    'PLPGSQL_DTYPE_VAR' => 'PLpgSQL_var',
    'PLPGSQL_DTYPE_PROMISE' => 'PLpgSQL_var',
    'PLPGSQL_DTYPE_ROW' => 'PLpgSQL_row',
    'PLPGSQL_DTYPE_REC' => 'PLpgSQL_rec',
    'PLPGSQL_DTYPE_RECFIELD' => 'PLpgSQL_recfield',
  }

  # Known PLpgSQL enums
  PLPGSQL_ENUMS = %w[
    PLpgSQL_nsitem_type PLpgSQL_label_type PLpgSQL_datum_type
    PLpgSQL_promise_type PLpgSQL_type_type PLpgSQL_stmt_type
    PLpgSQL_getdiag_kind PLpgSQL_raise_option_type PLpgSQL_resolve_option
    PLpgSQL_trigtype
  ]

  # Known PLpgSQL struct types (for pointer fields)
  PLPGSQL_STRUCTS = %w[
    PLpgSQL_type PLpgSQL_expr PLpgSQL_var PLpgSQL_row PLpgSQL_rec
    PLpgSQL_recfield PLpgSQL_condition PLpgSQL_exception_block
    PLpgSQL_exception PLpgSQL_stmt_block PLpgSQL_stmt_assign
    PLpgSQL_stmt_if PLpgSQL_stmt_case PLpgSQL_stmt_loop
    PLpgSQL_stmt_while PLpgSQL_stmt_fori PLpgSQL_stmt_fors
    PLpgSQL_stmt_forc PLpgSQL_stmt_dynfors PLpgSQL_stmt_foreach_a
    PLpgSQL_stmt_open PLpgSQL_stmt_fetch PLpgSQL_stmt_close
    PLpgSQL_stmt_exit PLpgSQL_stmt_return PLpgSQL_stmt_return_next
    PLpgSQL_stmt_return_query PLpgSQL_stmt_raise PLpgSQL_raise_option
    PLpgSQL_stmt_assert PLpgSQL_stmt_execsql PLpgSQL_stmt_dynexecute
    PLpgSQL_if_elsif PLpgSQL_case_when PLpgSQL_diag_item
    PLpgSQL_stmt_perform PLpgSQL_stmt_call PLpgSQL_stmt_commit
    PLpgSQL_stmt_rollback PLpgSQL_stmt_getdiag PLpgSQL_function
    PLpgSQL_variable PLpgSQL_datum PLpgSQL_stmt
  ]

  def generate!
    generate_outmethods!
    generate_readmethods!
    generate_protobuf!
    generate_enum_funcs!

    # Write output files
    write_protobuf_addon!
    write_outfuncs!
    write_readfuncs!
    write_enum_defs!
    write_api!
    write_header!

    puts "Generated PLpgSQL protobuf files"
  end

  def proto_type_for(c_type, name)
    case c_type
    when 'bool'
      'bool'
    when 'int', 'int32', 'int16'
      'int32'
    when 'unsigned int', 'uint32'
      'uint32'
    when 'long'
      'int64'
    when 'char*'
      'string'
    when 'char'
      'string'
    when 'List*'
      'repeated PLpgSQL_stmt' # Most lists are statement lists
    when 'PLpgSQL_expr*'
      'PLpgSQL_expr'
    when 'PLpgSQL_type*'
      'PLpgSQL_type'
    when 'PLpgSQL_var*'
      'PLpgSQL_var'
    when 'PLpgSQL_variable*'
      'PLpgSQL_datum' # Use the oneof wrapper
    when 'PLpgSQL_condition*'
      'PLpgSQL_condition'
    when 'PLpgSQL_exception_block*'
      'PLpgSQL_exception_block'
    when 'PLpgSQL_stmt_block*'
      'PLpgSQL_stmt_block'
    when 'int*'
      nil # Skip, handled specially with count field
    when 'char**'
      nil # Skip, handled specially with count field
    when 'FetchDirection'
      'int32' # Enum from access/sdir.h
    when 'RawParseMode'
      'int32' # Enum from parser/parser.h
    when /^PLpgSQL_(\w+)$/
      # Check if it's an enum
      if PLPGSQL_ENUMS.include?(c_type)
        c_type
      else
        c_type # Struct type
      end
    else
      nil # Unknown type, skip
    end
  end

  def generate_outmethods!
    @outmethods = {}

    (@struct_defs.keys - SKIP_STRUCTS).each do |struct_name|
      struct_def = @struct_defs[struct_name]
      @outmethods[struct_name] = ''

      proto_field_count = 1
      struct_def['fields'].each do |field_def|
        name = field_def['name']
        c_type = field_def['c_type']

        next unless name && c_type

        outname = underscore(name)

        case c_type
        when 'bool'
          @outmethods[struct_name] += "  WRITE_BOOL_FIELD(#{outname}, #{name}, #{name});\n"
        when 'int', 'int32', 'int16', 'unsigned int'
          @outmethods[struct_name] += "  WRITE_INT_FIELD(#{outname}, #{name}, #{name});\n"
        when 'long'
          @outmethods[struct_name] += "  WRITE_LONG_FIELD(#{outname}, #{name}, #{name});\n"
        when 'char*'
          @outmethods[struct_name] += "  WRITE_STRING_FIELD(#{outname}, #{name}, #{name});\n"
        when 'char'
          @outmethods[struct_name] += "  WRITE_CHAR_FIELD(#{outname}, #{name}, #{name});\n"
        when 'PLpgSQL_expr*'
          @outmethods[struct_name] += "  WRITE_PLPGSQL_EXPR_FIELD(#{outname}, #{name});\n"
        when 'PLpgSQL_type*'
          @outmethods[struct_name] += "  WRITE_PLPGSQL_TYPE_FIELD(#{outname}, #{name});\n"
        when 'PLpgSQL_var*'
          @outmethods[struct_name] += "  WRITE_PLPGSQL_VAR_FIELD(#{outname}, #{name});\n"
        when 'PLpgSQL_variable*'
          @outmethods[struct_name] += "  WRITE_PLPGSQL_DATUM_FIELD(#{outname}, #{name});\n"
        when 'PLpgSQL_condition*'
          @outmethods[struct_name] += "  WRITE_PLPGSQL_CONDITION_FIELD(#{outname}, #{name});\n"
        when 'PLpgSQL_exception_block*'
          @outmethods[struct_name] += "  WRITE_PLPGSQL_EXCEPTION_BLOCK_FIELD(#{outname}, #{name});\n"
        when 'PLpgSQL_stmt_block*'
          @outmethods[struct_name] += "  WRITE_PLPGSQL_STMT_BLOCK_FIELD(#{outname}, #{name});\n"
        when 'List*'
          # Determine list type based on field name
          if name.include?('stmt') || name == 'body' || name == 'action' || name == 'then_body' || name == 'else_body' || name == 'else_stmts'
            @outmethods[struct_name] += "  WRITE_PLPGSQL_STMT_LIST_FIELD(#{outname}, #{name});\n"
          elsif name == 'exc_list'
            @outmethods[struct_name] += "  WRITE_PLPGSQL_EXCEPTION_LIST_FIELD(#{outname}, #{name});\n"
          elsif name == 'elsif_list'
            @outmethods[struct_name] += "  WRITE_PLPGSQL_IF_ELSIF_LIST_FIELD(#{outname}, #{name});\n"
          elsif name == 'case_when_list'
            @outmethods[struct_name] += "  WRITE_PLPGSQL_CASE_WHEN_LIST_FIELD(#{outname}, #{name});\n"
          elsif name == 'diag_items'
            @outmethods[struct_name] += "  WRITE_PLPGSQL_DIAG_ITEM_LIST_FIELD(#{outname}, #{name});\n"
          elsif name == 'params'
            @outmethods[struct_name] += "  WRITE_PLPGSQL_EXPR_LIST_FIELD(#{outname}, #{name});\n"
          elsif name == 'options'
            @outmethods[struct_name] += "  WRITE_PLPGSQL_RAISE_OPTION_LIST_FIELD(#{outname}, #{name});\n"
          else
            @outmethods[struct_name] += "  /* TODO: #{name} List* */\n"
          end
        when 'int*', 'char**'
          # Skip - not included in proto (arrays with count field need special handling)
          next
        when 'FetchDirection', 'RawParseMode'
          @outmethods[struct_name] += "  WRITE_INT_FIELD(#{outname}, #{name}, #{name});\n"
        when 'PLpgSQL_stmt_type', 'PLpgSQL_datum_type', 'PLpgSQL_type_type',
             'PLpgSQL_promise_type', 'PLpgSQL_getdiag_kind', 'PLpgSQL_raise_option_type',
             'PLpgSQL_resolve_option', 'PLpgSQL_trigtype'
          @outmethods[struct_name] += "  WRITE_PLPGSQL_ENUM_FIELD(#{c_type}, #{outname}, #{name});\n"
        else
          @outmethods[struct_name] += "  /* TODO: #{name} #{c_type} */\n"
        end
      end
    end
  end

  def generate_readmethods!
    @readmethods = {}

    (@struct_defs.keys - SKIP_STRUCTS).each do |struct_name|
      struct_def = @struct_defs[struct_name]
      @readmethods[struct_name] = ''

      struct_def['fields'].each do |field_def|
        name = field_def['name']
        c_type = field_def['c_type']

        next unless name && c_type

        outname = underscore(name)

        case c_type
        when 'bool'
          @readmethods[struct_name] += "  READ_BOOL_FIELD(#{outname}, #{name});\n"
        when 'int', 'int32', 'int16', 'unsigned int'
          @readmethods[struct_name] += "  READ_INT_FIELD(#{outname}, #{name});\n"
        when 'long'
          @readmethods[struct_name] += "  READ_LONG_FIELD(#{outname}, #{name});\n"
        when 'char*'
          @readmethods[struct_name] += "  READ_STRING_FIELD(#{outname}, #{name});\n"
        when 'char'
          @readmethods[struct_name] += "  READ_CHAR_FIELD(#{outname}, #{name});\n"
        when 'PLpgSQL_expr*'
          @readmethods[struct_name] += "  READ_PLPGSQL_EXPR_FIELD(#{outname}, #{name});\n"
        when 'PLpgSQL_type*'
          @readmethods[struct_name] += "  READ_PLPGSQL_TYPE_FIELD(#{outname}, #{name});\n"
        when 'PLpgSQL_var*'
          @readmethods[struct_name] += "  READ_PLPGSQL_VAR_FIELD(#{outname}, #{name});\n"
        when 'PLpgSQL_variable*'
          @readmethods[struct_name] += "  READ_PLPGSQL_DATUM_FIELD(#{outname}, #{name});\n"
        when 'PLpgSQL_condition*'
          @readmethods[struct_name] += "  READ_PLPGSQL_CONDITION_FIELD(#{outname}, #{name});\n"
        when 'PLpgSQL_exception_block*'
          @readmethods[struct_name] += "  READ_PLPGSQL_EXCEPTION_BLOCK_FIELD(#{outname}, #{name});\n"
        when 'PLpgSQL_stmt_block*'
          @readmethods[struct_name] += "  READ_PLPGSQL_STMT_BLOCK_FIELD(#{outname}, #{name});\n"
        when 'List*'
          if name.include?('stmt') || name == 'body' || name == 'action' || name == 'then_body' || name == 'else_body' || name == 'else_stmts'
            @readmethods[struct_name] += "  READ_PLPGSQL_STMT_LIST_FIELD(#{outname}, #{name});\n"
          elsif name == 'exc_list'
            @readmethods[struct_name] += "  READ_PLPGSQL_EXCEPTION_LIST_FIELD(#{outname}, #{name});\n"
          elsif name == 'elsif_list'
            @readmethods[struct_name] += "  READ_PLPGSQL_IF_ELSIF_LIST_FIELD(#{outname}, #{name});\n"
          elsif name == 'case_when_list'
            @readmethods[struct_name] += "  READ_PLPGSQL_CASE_WHEN_LIST_FIELD(#{outname}, #{name});\n"
          elsif name == 'diag_items'
            @readmethods[struct_name] += "  READ_PLPGSQL_DIAG_ITEM_LIST_FIELD(#{outname}, #{name});\n"
          elsif name == 'params'
            @readmethods[struct_name] += "  READ_PLPGSQL_EXPR_LIST_FIELD(#{outname}, #{name});\n"
          elsif name == 'options'
            @readmethods[struct_name] += "  READ_PLPGSQL_RAISE_OPTION_LIST_FIELD(#{outname}, #{name});\n"
          else
            @readmethods[struct_name] += "  /* TODO: #{name} List* */\n"
          end
        when 'int*', 'char**'
          # Skip - not included in proto
          next
        when 'FetchDirection', 'RawParseMode'
          @readmethods[struct_name] += "  READ_INT_FIELD(#{outname}, #{name});\n"
        when 'PLpgSQL_stmt_type', 'PLpgSQL_datum_type', 'PLpgSQL_type_type',
             'PLpgSQL_promise_type', 'PLpgSQL_getdiag_kind', 'PLpgSQL_raise_option_type',
             'PLpgSQL_resolve_option', 'PLpgSQL_trigtype'
          @readmethods[struct_name] += "  READ_PLPGSQL_ENUM_FIELD(#{c_type}, #{outname}, #{name});\n"
        else
          @readmethods[struct_name] += "  /* TODO: #{name} #{c_type} */\n"
        end
      end
    end
  end

  def generate_protobuf!
    @protobuf_messages = {}
    @protobuf_enums = {}

    # Generate protobuf messages for each struct
    (@struct_defs.keys - SKIP_STRUCTS).each do |struct_name|
      struct_def = @struct_defs[struct_name]
      @protobuf_messages[struct_name] = ''

      proto_field_count = 1
      struct_def['fields'].each do |field_def|
        name = field_def['name']
        c_type = field_def['c_type']

        next unless name && c_type

        outname = underscore(name)
        proto_type = proto_type_for(c_type, name)

        if proto_type
          # Handle list fields specially
          if c_type == 'List*'
            if name.include?('stmt') || name == 'body' || name == 'action' || name == 'then_body' || name == 'else_body' || name == 'else_stmts'
              @protobuf_messages[struct_name] += "  repeated PLpgSQL_stmt #{outname} = #{proto_field_count};\n"
            elsif name == 'exc_list'
              @protobuf_messages[struct_name] += "  repeated PLpgSQL_exception #{outname} = #{proto_field_count};\n"
            elsif name == 'elsif_list'
              @protobuf_messages[struct_name] += "  repeated PLpgSQL_if_elsif #{outname} = #{proto_field_count};\n"
            elsif name == 'case_when_list'
              @protobuf_messages[struct_name] += "  repeated PLpgSQL_case_when #{outname} = #{proto_field_count};\n"
            elsif name == 'diag_items'
              @protobuf_messages[struct_name] += "  repeated PLpgSQL_diag_item #{outname} = #{proto_field_count};\n"
            elsif name == 'params'
              @protobuf_messages[struct_name] += "  repeated PLpgSQL_expr #{outname} = #{proto_field_count};\n"
            elsif name == 'options'
              @protobuf_messages[struct_name] += "  repeated PLpgSQL_raise_option #{outname} = #{proto_field_count};\n"
            else
              @protobuf_messages[struct_name] += "  /* TODO: #{name} List* */ int32 #{outname}_placeholder = #{proto_field_count};\n"
            end
          elsif c_type == 'int*'
            # Skip - handled separately with array
            next
          elsif c_type == 'char**'
            # Skip - handled separately with array
            next
          else
            @protobuf_messages[struct_name] += "  #{proto_type} #{outname} = #{proto_field_count};\n"
          end
          proto_field_count += 1
        end
      end
    end

    # Generate protobuf enums
    @enum_defs.each do |enum_name, enum_def|
      @protobuf_enums[enum_name] = "enum #{enum_name} {\n"
      @protobuf_enums[enum_name] += "  #{underscore(enum_name).upcase}_UNDEFINED = 0;\n"

      proto_value = 1
      enum_def['values'].each do |value|
        next unless value['name']
        @protobuf_enums[enum_name] += "  #{value['name']} = #{proto_value};\n"
        proto_value += 1
      end

      @protobuf_enums[enum_name] += "}\n"
    end
  end

  def generate_enum_funcs!
    @enum_to_ints = {}
    @int_to_enums = {}

    @enum_defs.each do |enum_name, enum_def|
      @enum_to_ints[enum_name] = "static int\n_plpgsqlEnumToInt#{enum_name}(#{enum_name} value) {\n  switch(value) {\n"
      @int_to_enums[enum_name] = "static #{enum_name}\n_plpgsqlIntToEnum#{enum_name}(int value) {\n  switch(value) {\n"

      proto_value = 1
      first_value = nil
      enum_def['values'].each do |value|
        next unless value['name']
        first_value ||= value['name']
        @enum_to_ints[enum_name] += "    case #{value['name']}: return #{proto_value};\n"
        @int_to_enums[enum_name] += "    case #{proto_value}: return #{value['name']};\n"
        proto_value += 1
      end

      @enum_to_ints[enum_name] += "  }\n  return 0;\n}\n"
      @int_to_enums[enum_name] += "  }\n  return #{first_value || 0};\n}\n"
    end
  end

  def write_protobuf_addon!
    stmt_oneof_fields = []
    STMT_TYPE_MAP.each_with_index do |(enum_val, struct_name), idx|
      field_name = underscore(struct_name.gsub('PLpgSQL_', ''))
      # Avoid naming conflict with protobuf oneof discriminator (stmt_case)
      field_name = "stmt_case_" if field_name == "stmt_case"
      stmt_oneof_fields << "    #{struct_name} #{field_name} = #{idx + 1};"
    end

    datum_oneof_fields = []
    seen_datums = {}
    DATUM_TYPE_MAP.each_with_index do |(enum_val, struct_name), idx|
      next if seen_datums[struct_name]
      seen_datums[struct_name] = true
      field_name = underscore(struct_name.gsub('PLpgSQL_', ''))
      datum_oneof_fields << "    #{struct_name} #{field_name} = #{idx + 1};"
    end

    proto = <<~PROTO
// PLpgSQL Protobuf Definitions
// This file is autogenerated by ./scripts/generate_plpgsql_protobuf.rb

message PLpgSQLParseResult {
  int32 version = 1;
  repeated PLpgSQL_function plpgsql_funcs = 2;
}

// PLpgSQL statement wrapper with oneof for polymorphism
message PLpgSQL_stmt {
  oneof stmt {
#{stmt_oneof_fields.join("\n")}
  }
}

// PLpgSQL datum wrapper with oneof for polymorphism
message PLpgSQL_datum {
  oneof datum {
#{datum_oneof_fields.join("\n")}
  }
}

// PLpgSQL Messages

#{@protobuf_messages.map { |name, fields| "message #{name} {\n#{fields}}\n" }.join("\n")}

// PLpgSQL Enums

#{@protobuf_enums.values.join("\n")}
PROTO

    File.write('./src/include/pg_query_plpgsql_protobuf.proto', proto)
  end

  def write_outfuncs!
    out_defs = ''
    out_impls = ''

    (@struct_defs.keys - SKIP_STRUCTS).each do |struct_name|
      c_type = struct_name
      protobuf_type = protobuf_c_type_name(struct_name)

      out_defs += "static void _out#{c_type}(PgQuery__#{protobuf_type} *out, const #{struct_name} *node);\n"

      out_impls += "static void\n"
      out_impls += "_out#{c_type}(PgQuery__#{protobuf_type} *out, const #{struct_name} *node)\n"
      out_impls += "{\n"
      out_impls += @outmethods[struct_name] || ''
      out_impls += "}\n\n"
    end

    # Generate stmt dispatcher
    stmt_dispatch = "static void\n_outPLpgSQL_stmt(PgQuery__PLpgSQLStmt *out, const PLpgSQL_stmt *node)\n{\n"
    stmt_dispatch += "  switch (node->cmd_type) {\n"
    STMT_TYPE_MAP.each do |enum_val, struct_name|
      field_name = underscore(struct_name.gsub('PLpgSQL_', ''))
      protobuf_type = protobuf_c_type_name(struct_name)
      func_name = protobuf_c_func_name(struct_name)
      # Avoid naming conflict with protobuf oneof discriminator
      proto_field_name = field_name == "stmt_case" ? "stmt_case_" : field_name
      enum_suffix = field_name == "stmt_case" ? "STMT_CASE_" : field_name.upcase
      stmt_dispatch += "    case #{enum_val}:\n"
      stmt_dispatch += "      out->#{proto_field_name} = palloc0(sizeof(PgQuery__#{protobuf_type}));\n"
      stmt_dispatch += "      pg_query__#{func_name}__init(out->#{proto_field_name});\n"
      stmt_dispatch += "      _out#{struct_name}(out->#{proto_field_name}, (const #{struct_name} *) node);\n"
      stmt_dispatch += "      out->stmt_case = PG_QUERY__PLPG_SQL_STMT__STMT_#{enum_suffix};\n"
      stmt_dispatch += "      break;\n"
    end
    stmt_dispatch += "  }\n}\n\n"

    # Generate datum dispatcher
    datum_dispatch = "static void\n_outPLpgSQL_datum(PgQuery__PLpgSQLDatum *out, const PLpgSQL_datum *node)\n{\n"
    datum_dispatch += "  switch (node->dtype) {\n"
    seen_datums = {}
    DATUM_TYPE_MAP.each do |enum_val, struct_name|
      next if seen_datums[struct_name] && enum_val != 'PLPGSQL_DTYPE_PROMISE'
      seen_datums[struct_name] = true unless enum_val == 'PLPGSQL_DTYPE_PROMISE'

      field_name = underscore(struct_name.gsub('PLpgSQL_', ''))
      protobuf_type = protobuf_c_type_name(struct_name)
      func_name = protobuf_c_func_name(struct_name)
      datum_dispatch += "    case #{enum_val}:\n"
      unless enum_val == 'PLPGSQL_DTYPE_PROMISE'
        datum_dispatch += "      out->#{field_name} = palloc0(sizeof(PgQuery__#{protobuf_type}));\n"
        datum_dispatch += "      pg_query__#{func_name}__init(out->#{field_name});\n"
        datum_dispatch += "      _out#{struct_name}(out->#{field_name}, (const #{struct_name} *) node);\n"
        datum_dispatch += "      out->datum_case = PG_QUERY__PLPG_SQL_DATUM__DATUM_#{field_name.upcase};\n"
      else
        datum_dispatch += "      out->var = palloc0(sizeof(PgQuery__PLpgSQLVar));\n"
        datum_dispatch += "      pg_query__plpg_sql_var__init(out->var);\n"
        datum_dispatch += "      _outPLpgSQL_var(out->var, (const PLpgSQL_var *) node);\n"
        datum_dispatch += "      out->datum_case = PG_QUERY__PLPG_SQL_DATUM__DATUM_VAR;\n"
      end
      datum_dispatch += "      break;\n"
    end
    datum_dispatch += "  }\n}\n\n"

    # Forward declare dispatchers since they're used in macros
    dispatcher_decls = <<~C
// Forward declarations for dispatchers (used by macros)
static void _outPLpgSQL_stmt(PgQuery__PLpgSQLStmt *out, const PLpgSQL_stmt *node);
static void _outPLpgSQL_datum(PgQuery__PLpgSQLDatum *out, const PLpgSQL_datum *node);
C

    content = <<~C
// This file is autogenerated by ./scripts/generate_plpgsql_protobuf.rb

#{dispatcher_decls}

#{out_defs}

#{stmt_dispatch}

#{datum_dispatch}

#{out_impls}
C

    File.write('./src/include/pg_query_outfuncs_plpgsql_defs.c', content)
  end

  def write_readfuncs!
    read_defs = ''
    read_impls = ''

    (@struct_defs.keys - SKIP_STRUCTS).each do |struct_name|
      c_type = struct_name
      protobuf_type = protobuf_c_type_name(struct_name)

      read_defs += "static #{struct_name} * _read#{c_type}(const PgQuery__#{protobuf_type} *msg);\n"

      read_impls += "static #{struct_name} *\n"
      read_impls += "_read#{c_type}(const PgQuery__#{protobuf_type} *msg)\n"
      read_impls += "{\n"
      read_impls += "  #{struct_name} *node = palloc0(sizeof(#{struct_name}));\n"
      read_impls += @readmethods[struct_name] || ''
      read_impls += "  return node;\n"
      read_impls += "}\n\n"
    end

    # Generate stmt reader dispatcher
    stmt_read = "static PLpgSQL_stmt *\n_readPLpgSQL_stmt(const PgQuery__PLpgSQLStmt *msg)\n{\n"
    stmt_read += "  switch (msg->stmt_case) {\n"
    STMT_TYPE_MAP.each do |enum_val, struct_name|
      field_name = underscore(struct_name.gsub('PLpgSQL_', ''))
      # Avoid naming conflict with protobuf oneof discriminator
      proto_field_name = field_name == "stmt_case" ? "stmt_case_" : field_name
      enum_suffix = field_name == "stmt_case" ? "STMT_CASE_" : field_name.upcase
      stmt_read += "    case PG_QUERY__PLPG_SQL_STMT__STMT_#{enum_suffix}:\n"
      stmt_read += "      return (PLpgSQL_stmt *) _read#{struct_name}(msg->#{proto_field_name});\n"
    end
    stmt_read += "    default:\n"
    stmt_read += "      return NULL;\n"
    stmt_read += "  }\n}\n\n"

    # Generate datum reader dispatcher
    datum_read = "static PLpgSQL_datum *\n_readPLpgSQL_datum(const PgQuery__PLpgSQLDatum *msg)\n{\n"
    datum_read += "  switch (msg->datum_case) {\n"
    seen_datums = {}
    DATUM_TYPE_MAP.each do |enum_val, struct_name|
      next if seen_datums[struct_name]
      seen_datums[struct_name] = true

      field_name = underscore(struct_name.gsub('PLpgSQL_', ''))
      datum_read += "    case PG_QUERY__PLPG_SQL_DATUM__DATUM_#{field_name.upcase}:\n"
      datum_read += "      return (PLpgSQL_datum *) _read#{struct_name}(msg->#{field_name});\n"
    end
    datum_read += "    default:\n"
    datum_read += "      return NULL;\n"
    datum_read += "  }\n}\n\n"

    # Forward declare dispatchers
    dispatcher_decls = <<~C
// Forward declarations for dispatchers
static PLpgSQL_stmt * _readPLpgSQL_stmt(const PgQuery__PLpgSQLStmt *msg);
static PLpgSQL_datum * _readPLpgSQL_datum(const PgQuery__PLpgSQLDatum *msg);
C

    content = <<~C
// This file is autogenerated by ./scripts/generate_plpgsql_protobuf.rb

#{dispatcher_decls}

#{read_defs}

#{stmt_read}

#{datum_read}

#{read_impls}
C

    File.write('./src/include/pg_query_readfuncs_plpgsql_defs.c', content)
  end

  def write_enum_defs!
    content = <<~C
// This file is autogenerated by ./scripts/generate_plpgsql_protobuf.rb

#{@enum_to_ints.values.join("\n")}

#{@int_to_enums.values.join("\n")}
C

    File.write('./src/include/pg_query_plpgsql_enum_defs.c', content)
  end

  def write_api!
    content = <<~C
/*
 * pg_query_parse_plpgsql_protobuf.c
 *
 * Public API for parsing PL/pgSQL to protobuf format.
 * This file is autogenerated by ./scripts/generate_plpgsql_protobuf.rb
 */

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include "pg_query.h"
#include "pg_query_internal.h"
#include "pg_query_json_plpgsql.h"

#include <assert.h>
#include <catalog/pg_type.h>
#include <catalog/objectaddress.h>
#include <catalog/pg_proc.h>
#include <nodes/parsenodes.h>
#include <nodes/nodeFuncs.h>

#include "protobuf/pg_query.pb-c.h"

// Include generated outfuncs macros
#include "pg_query_outfuncs_plpgsql.c"

typedef struct {
  PLpgSQL_function *func;
  PgQueryError* error;
} PgQueryInternalPlpgsqlFuncAndError;

/* Forward declaration from pg_query_parse_plpgsql.c */
extern PgQueryInternalPlpgsqlFuncAndError pg_query_raw_parse_plpgsql(Node* stmt);

typedef struct plStmts
{
  Node **stmts;
  int stmts_buf_size;
  int stmts_count;
} plStmts;

static bool stmts_walker(Node *node, plStmts *state)
{
  bool result;
  MemoryContext ccxt = CurrentMemoryContext;

  if (node == NULL) return false;

  if (IsA(node, CreateFunctionStmt) || IsA(node, DoStmt))
  {
    if (state->stmts_count >= state->stmts_buf_size)
    {
      state->stmts_buf_size *= 2;
      state->stmts = (Node**) repalloc(state->stmts, state->stmts_buf_size * sizeof(Node*));
    }
    state->stmts[state->stmts_count] = (Node *) node;
    state->stmts_count++;
  } else if (IsA(node, RawStmt)) {
    return stmts_walker((Node *) ((RawStmt *) node)->stmt, state);
  }

  PG_TRY();
  {
    result = raw_expression_tree_walker(node, stmts_walker, (void*) state);
  }
  PG_CATCH();
  {
    MemoryContextSwitchTo(ccxt);
    FlushErrorState();
    result = false;
  }
  PG_END_TRY();

  return result;
}

PgQueryPlpgsqlProtobufParseResult pg_query_parse_plpgsql_protobuf(const char* input)
{
  MemoryContext ctx = NULL;
  PgQueryPlpgsqlProtobufParseResult result = {0};
  PgQueryInternalParsetreeAndError parse_result;
  plStmts statements;
  size_t i;
  PgQuery__PLpgSQLParseResult *parse_result_msg;

  ctx = pg_query_enter_memory_context();

  /* Parse the SQL input first to find CREATE FUNCTION/DO statements */
  parse_result = pg_query_raw_parse(input, PG_QUERY_PARSE_DEFAULT);
  result.error = parse_result.error;
  if (result.error != NULL) {
    pg_query_exit_memory_context(ctx);
    return result;
  }

  statements.stmts_buf_size = 100;
  statements.stmts = (Node**) palloc(statements.stmts_buf_size * sizeof(Node*));
  statements.stmts_count = 0;

  stmts_walker((Node*) parse_result.tree, &statements);

  /* Create the protobuf result message */
  parse_result_msg = palloc0(sizeof(PgQuery__PLpgSQLParseResult));
  pg_query__plpg_sqlparse_result__init(parse_result_msg);
  parse_result_msg->version = PG_VERSION_NUM;

  if (statements.stmts_count == 0) {
    parse_result_msg->n_plpgsql_funcs = 0;
    parse_result_msg->plpgsql_funcs = NULL;
  } else {
    parse_result_msg->n_plpgsql_funcs = statements.stmts_count;
    parse_result_msg->plpgsql_funcs = palloc0(statements.stmts_count * sizeof(PgQuery__PLpgSQLFunction*));

    for (i = 0; i < statements.stmts_count; i++) {
      PgQueryInternalPlpgsqlFuncAndError func_and_error;

      func_and_error = pg_query_raw_parse_plpgsql(statements.stmts[i]);

      result.error = func_and_error.error;
      if (result.error != NULL) {
        pg_query_exit_memory_context(ctx);
        return result;
      }

      if (func_and_error.func != NULL) {
        parse_result_msg->plpgsql_funcs[i] = palloc0(sizeof(PgQuery__PLpgSQLFunction));
        pg_query__plpg_sql_function__init(parse_result_msg->plpgsql_funcs[i]);
        _outPLpgSQL_function(parse_result_msg->plpgsql_funcs[i], func_and_error.func);
        plpgsql_free_function_memory(func_and_error.func);
      }
    }
  }

  /* Pack the protobuf message */
  result.parse_tree.len = pg_query__plpg_sqlparse_result__get_packed_size(parse_result_msg);
  result.parse_tree.data = malloc(result.parse_tree.len);
  pg_query__plpg_sqlparse_result__pack(parse_result_msg, (uint8_t*) result.parse_tree.data);

  /* Copy stderr buffer if present */
  if (parse_result.stderr_buffer != NULL) {
    result.stderr_buffer = strdup(parse_result.stderr_buffer);
    free(parse_result.stderr_buffer);
  }

  pg_query_exit_memory_context(ctx);

  return result;
}

void pg_query_free_plpgsql_protobuf_parse_result(PgQueryPlpgsqlProtobufParseResult result)
{
  if (result.error) {
    pg_query_free_error(result.error);
  }

  if (result.parse_tree.data) {
    free(result.parse_tree.data);
  }

  if (result.stderr_buffer) {
    free(result.stderr_buffer);
  }
}

char* pg_query_plpgsql_protobuf_to_json(PgQueryProtobuf protobuf)
{
  MemoryContext ctx = NULL;
  PgQuery__PLpgSQLParseResult *parse_result;
  char *json_result;
  size_t i;
  size_t json_len;

  ctx = pg_query_enter_memory_context();

  /* Unpack the protobuf */
  parse_result = pg_query__plpg_sqlparse_result__unpack(NULL,
    protobuf.len, (const uint8_t*) protobuf.data);

  if (parse_result == NULL) {
    pg_query_exit_memory_context(ctx);
    return strdup("[]");
  }

  if (parse_result->n_plpgsql_funcs == 0) {
    pg_query__plpg_sqlparse_result__free_unpacked(parse_result, NULL);
    pg_query_exit_memory_context(ctx);
    return strdup("[]");
  }

  /* Build JSON array - reuse existing JSON conversion by converting back to PLpgSQL_function */
  json_result = strdup("[\\n");

  for (i = 0; i < parse_result->n_plpgsql_funcs; i++) {
    PLpgSQL_function *func;
    char *func_json;
    char *new_out;
    size_t new_out_len;

    func = _readPLpgSQL_function(parse_result->plpgsql_funcs[i]);
    func_json = plpgsqlToJSON(func);

    new_out_len = strlen(json_result) + strlen(func_json) + 3;
    new_out = malloc(new_out_len);
    snprintf(new_out, new_out_len, "%s%s,\\n", json_result, func_json);
    free(json_result);
    pfree(func_json);
    json_result = new_out;
  }

  /* Fix trailing comma */
  json_len = strlen(json_result);
  if (json_len >= 2) {
    json_result[json_len - 2] = '\\n';
    json_result[json_len - 1] = ']';
  }

  pg_query__plpg_sqlparse_result__free_unpacked(parse_result, NULL);
  pg_query_exit_memory_context(ctx);

  return json_result;
}
C

    File.write('./src/pg_query_parse_plpgsql_protobuf.c', content)
  end

  def write_header!
    content = <<~C
/*
 * pg_query_outfuncs_plpgsql.c
 *
 * PLpgSQL to protobuf serialization.
 * This file is autogenerated by ./scripts/generate_plpgsql_protobuf.rb
 */

#include "pg_query.h"
#include "pg_query_internal.h"

#include <plpgsql.h>

#include "protobuf/pg_query.pb-c.h"

// Macros for writing PLpgSQL fields to protobuf
#define WRITE_BOOL_FIELD(outname, json_name, field) \\
  out->outname = node->field

#define WRITE_INT_FIELD(outname, json_name, field) \\
  out->outname = node->field

#define WRITE_LONG_FIELD(outname, json_name, field) \\
  out->outname = node->field

#define WRITE_STRING_FIELD(outname, json_name, field) \\
  if (node->field != NULL) out->outname = pstrdup(node->field)

#define WRITE_CHAR_FIELD(outname, json_name, field) \\
  { char buf[2] = {node->field, '\\0'}; out->outname = pstrdup(buf); }

#define WRITE_PLPGSQL_ENUM_FIELD(enum_type, outname, field) \\
  out->outname = _plpgsqlEnumToInt##enum_type(node->field)

#define WRITE_PLPGSQL_EXPR_FIELD(outname, field) \\
  if (node->field != NULL) { \\
    out->outname = palloc0(sizeof(PgQuery__PLpgSQLExpr)); \\
    pg_query__plpg_sql_expr__init(out->outname); \\
    _outPLpgSQL_expr(out->outname, node->field); \\
  }

#define WRITE_PLPGSQL_TYPE_FIELD(outname, field) \\
  if (node->field != NULL) { \\
    out->outname = palloc0(sizeof(PgQuery__PLpgSQLType)); \\
    pg_query__plpg_sql_type__init(out->outname); \\
    _outPLpgSQL_type(out->outname, node->field); \\
  }

#define WRITE_PLPGSQL_VAR_FIELD(outname, field) \\
  if (node->field != NULL) { \\
    out->outname = palloc0(sizeof(PgQuery__PLpgSQLVar)); \\
    pg_query__plpg_sql_var__init(out->outname); \\
    _outPLpgSQL_var(out->outname, node->field); \\
  }

#define WRITE_PLPGSQL_DATUM_FIELD(outname, field) \\
  if (node->field != NULL) { \\
    out->outname = palloc0(sizeof(PgQuery__PLpgSQLDatum)); \\
    pg_query__plpg_sql_datum__init(out->outname); \\
    _outPLpgSQL_datum(out->outname, (PLpgSQL_datum *) node->field); \\
  }

#define WRITE_PLPGSQL_CONDITION_FIELD(outname, field) \\
  if (node->field != NULL) { \\
    out->outname = palloc0(sizeof(PgQuery__PLpgSQLCondition)); \\
    pg_query__plpg_sql_condition__init(out->outname); \\
    _outPLpgSQL_condition(out->outname, node->field); \\
  }

#define WRITE_PLPGSQL_EXCEPTION_BLOCK_FIELD(outname, field) \\
  if (node->field != NULL) { \\
    out->outname = palloc0(sizeof(PgQuery__PLpgSQLExceptionBlock)); \\
    pg_query__plpg_sql_exception_block__init(out->outname); \\
    _outPLpgSQL_exception_block(out->outname, node->field); \\
  }

#define WRITE_PLPGSQL_STMT_BLOCK_FIELD(outname, field) \\
  if (node->field != NULL) { \\
    out->outname = palloc0(sizeof(PgQuery__PLpgSQLStmtBlock)); \\
    pg_query__plpg_sql_stmt_block__init(out->outname); \\
    _outPLpgSQL_stmt_block(out->outname, node->field); \\
  }

#define WRITE_PLPGSQL_STMT_LIST_FIELD(outname, field) \\
  if (node->field != NIL) { \\
    ListCell *lc; \\
    int i = 0; \\
    out->n_##outname = list_length(node->field); \\
    out->outname = palloc0(out->n_##outname * sizeof(PgQuery__PLpgSQLStmt*)); \\
    foreach(lc, node->field) { \\
      PLpgSQL_stmt *stmt = (PLpgSQL_stmt *) lfirst(lc); \\
      out->outname[i] = palloc0(sizeof(PgQuery__PLpgSQLStmt)); \\
      pg_query__plpg_sql_stmt__init(out->outname[i]); \\
      _outPLpgSQL_stmt(out->outname[i], stmt); \\
      i++; \\
    } \\
  }

#define WRITE_PLPGSQL_EXCEPTION_LIST_FIELD(outname, field) \\
  if (node->field != NIL) { \\
    ListCell *lc; \\
    int i = 0; \\
    out->n_##outname = list_length(node->field); \\
    out->outname = palloc0(out->n_##outname * sizeof(PgQuery__PLpgSQLException*)); \\
    foreach(lc, node->field) { \\
      PLpgSQL_exception *exc = (PLpgSQL_exception *) lfirst(lc); \\
      out->outname[i] = palloc0(sizeof(PgQuery__PLpgSQLException)); \\
      pg_query__plpg_sql_exception__init(out->outname[i]); \\
      _outPLpgSQL_exception(out->outname[i], exc); \\
      i++; \\
    } \\
  }

#define WRITE_PLPGSQL_IF_ELSIF_LIST_FIELD(outname, field) \\
  if (node->field != NIL) { \\
    ListCell *lc; \\
    int i = 0; \\
    out->n_##outname = list_length(node->field); \\
    out->outname = palloc0(out->n_##outname * sizeof(PgQuery__PLpgSQLIfElsif*)); \\
    foreach(lc, node->field) { \\
      PLpgSQL_if_elsif *elsif = (PLpgSQL_if_elsif *) lfirst(lc); \\
      out->outname[i] = palloc0(sizeof(PgQuery__PLpgSQLIfElsif)); \\
      pg_query__plpg_sql_if_elsif__init(out->outname[i]); \\
      _outPLpgSQL_if_elsif(out->outname[i], elsif); \\
      i++; \\
    } \\
  }

#define WRITE_PLPGSQL_CASE_WHEN_LIST_FIELD(outname, field) \\
  if (node->field != NIL) { \\
    ListCell *lc; \\
    int i = 0; \\
    out->n_##outname = list_length(node->field); \\
    out->outname = palloc0(out->n_##outname * sizeof(PgQuery__PLpgSQLCaseWhen*)); \\
    foreach(lc, node->field) { \\
      PLpgSQL_case_when *when = (PLpgSQL_case_when *) lfirst(lc); \\
      out->outname[i] = palloc0(sizeof(PgQuery__PLpgSQLCaseWhen)); \\
      pg_query__plpg_sql_case_when__init(out->outname[i]); \\
      _outPLpgSQL_case_when(out->outname[i], when); \\
      i++; \\
    } \\
  }

#define WRITE_PLPGSQL_DIAG_ITEM_LIST_FIELD(outname, field) \\
  if (node->field != NIL) { \\
    ListCell *lc; \\
    int i = 0; \\
    out->n_##outname = list_length(node->field); \\
    out->outname = palloc0(out->n_##outname * sizeof(PgQuery__PLpgSQLDiagItem*)); \\
    foreach(lc, node->field) { \\
      PLpgSQL_diag_item *item = (PLpgSQL_diag_item *) lfirst(lc); \\
      out->outname[i] = palloc0(sizeof(PgQuery__PLpgSQLDiagItem)); \\
      pg_query__plpg_sql_diag_item__init(out->outname[i]); \\
      _outPLpgSQL_diag_item(out->outname[i], item); \\
      i++; \\
    } \\
  }

#define WRITE_PLPGSQL_EXPR_LIST_FIELD(outname, field) \\
  if (node->field != NIL) { \\
    ListCell *lc; \\
    int i = 0; \\
    out->n_##outname = list_length(node->field); \\
    out->outname = palloc0(out->n_##outname * sizeof(PgQuery__PLpgSQLExpr*)); \\
    foreach(lc, node->field) { \\
      PLpgSQL_expr *expr = (PLpgSQL_expr *) lfirst(lc); \\
      out->outname[i] = palloc0(sizeof(PgQuery__PLpgSQLExpr)); \\
      pg_query__plpg_sql_expr__init(out->outname[i]); \\
      _outPLpgSQL_expr(out->outname[i], expr); \\
      i++; \\
    } \\
  }

#define WRITE_PLPGSQL_RAISE_OPTION_LIST_FIELD(outname, field) \\
  if (node->field != NIL) { \\
    ListCell *lc; \\
    int i = 0; \\
    out->n_##outname = list_length(node->field); \\
    out->outname = palloc0(out->n_##outname * sizeof(PgQuery__PLpgSQLRaiseOption*)); \\
    foreach(lc, node->field) { \\
      PLpgSQL_raise_option *opt = (PLpgSQL_raise_option *) lfirst(lc); \\
      out->outname[i] = palloc0(sizeof(PgQuery__PLpgSQLRaiseOption)); \\
      pg_query__plpg_sql_raise_option__init(out->outname[i]); \\
      _outPLpgSQL_raise_option(out->outname[i], opt); \\
      i++; \\
    } \\
  }

#define WRITE_INT_ARRAY_FIELD(outname, field, count_field) \\
  if (node->field != NULL && node->count_field > 0) { \\
    int i; \\
    out->n_##outname = node->count_field; \\
    out->outname = palloc0(out->n_##outname * sizeof(int32_t)); \\
    for (i = 0; i < node->count_field; i++) { \\
      out->outname[i] = node->field[i]; \\
    } \\
  }

#define WRITE_STRING_ARRAY_FIELD(outname, field, count_field) \\
  if (node->field != NULL && node->count_field > 0) { \\
    int i; \\
    out->n_##outname = node->count_field; \\
    out->outname = palloc0(out->n_##outname * sizeof(char*)); \\
    for (i = 0; i < node->count_field; i++) { \\
      if (node->field[i] != NULL) \\
        out->outname[i] = pstrdup(node->field[i]); \\
    } \\
  }

// READ macros for deserialization

#define READ_BOOL_FIELD(protoname, field) \\
  node->field = msg->protoname

#define READ_INT_FIELD(protoname, field) \\
  node->field = msg->protoname

#define READ_LONG_FIELD(protoname, field) \\
  node->field = msg->protoname

#define READ_STRING_FIELD(protoname, field) \\
  if (msg->protoname != NULL) node->field = pstrdup(msg->protoname)

#define READ_CHAR_FIELD(protoname, field) \\
  if (msg->protoname != NULL && msg->protoname[0] != '\\0') node->field = msg->protoname[0]

#define READ_PLPGSQL_ENUM_FIELD(enum_type, protoname, field) \\
  node->field = _plpgsqlIntToEnum##enum_type(msg->protoname)

#define READ_PLPGSQL_EXPR_FIELD(protoname, field) \\
  if (msg->protoname != NULL) node->field = _readPLpgSQL_expr(msg->protoname)

#define READ_PLPGSQL_TYPE_FIELD(protoname, field) \\
  if (msg->protoname != NULL) node->field = _readPLpgSQL_type(msg->protoname)

#define READ_PLPGSQL_VAR_FIELD(protoname, field) \\
  if (msg->protoname != NULL) node->field = _readPLpgSQL_var(msg->protoname)

#define READ_PLPGSQL_DATUM_FIELD(protoname, field) \\
  if (msg->protoname != NULL) node->field = (PLpgSQL_variable *) _readPLpgSQL_datum(msg->protoname)

#define READ_PLPGSQL_CONDITION_FIELD(protoname, field) \\
  if (msg->protoname != NULL) node->field = _readPLpgSQL_condition(msg->protoname)

#define READ_PLPGSQL_EXCEPTION_BLOCK_FIELD(protoname, field) \\
  if (msg->protoname != NULL) node->field = _readPLpgSQL_exception_block(msg->protoname)

#define READ_PLPGSQL_STMT_BLOCK_FIELD(protoname, field) \\
  if (msg->protoname != NULL) node->field = _readPLpgSQL_stmt_block(msg->protoname)

#define READ_PLPGSQL_STMT_LIST_FIELD(protoname, field) \\
  if (msg->n_##protoname > 0) { \\
    int i; \\
    node->field = NIL; \\
    for (i = 0; i < msg->n_##protoname; i++) { \\
      PLpgSQL_stmt *stmt = _readPLpgSQL_stmt(msg->protoname[i]); \\
      node->field = lappend(node->field, stmt); \\
    } \\
  }

#define READ_PLPGSQL_EXCEPTION_LIST_FIELD(protoname, field) \\
  if (msg->n_##protoname > 0) { \\
    int i; \\
    node->field = NIL; \\
    for (i = 0; i < msg->n_##protoname; i++) { \\
      PLpgSQL_exception *exc = _readPLpgSQL_exception(msg->protoname[i]); \\
      node->field = lappend(node->field, exc); \\
    } \\
  }

#define READ_PLPGSQL_IF_ELSIF_LIST_FIELD(protoname, field) \\
  if (msg->n_##protoname > 0) { \\
    int i; \\
    node->field = NIL; \\
    for (i = 0; i < msg->n_##protoname; i++) { \\
      PLpgSQL_if_elsif *elsif = _readPLpgSQL_if_elsif(msg->protoname[i]); \\
      node->field = lappend(node->field, elsif); \\
    } \\
  }

#define READ_PLPGSQL_CASE_WHEN_LIST_FIELD(protoname, field) \\
  if (msg->n_##protoname > 0) { \\
    int i; \\
    node->field = NIL; \\
    for (i = 0; i < msg->n_##protoname; i++) { \\
      PLpgSQL_case_when *when = _readPLpgSQL_case_when(msg->protoname[i]); \\
      node->field = lappend(node->field, when); \\
    } \\
  }

#define READ_PLPGSQL_DIAG_ITEM_LIST_FIELD(protoname, field) \\
  if (msg->n_##protoname > 0) { \\
    int i; \\
    node->field = NIL; \\
    for (i = 0; i < msg->n_##protoname; i++) { \\
      PLpgSQL_diag_item *item = _readPLpgSQL_diag_item(msg->protoname[i]); \\
      node->field = lappend(node->field, item); \\
    } \\
  }

#define READ_PLPGSQL_EXPR_LIST_FIELD(protoname, field) \\
  if (msg->n_##protoname > 0) { \\
    int i; \\
    node->field = NIL; \\
    for (i = 0; i < msg->n_##protoname; i++) { \\
      PLpgSQL_expr *expr = _readPLpgSQL_expr(msg->protoname[i]); \\
      node->field = lappend(node->field, expr); \\
    } \\
  }

#define READ_PLPGSQL_RAISE_OPTION_LIST_FIELD(protoname, field) \\
  if (msg->n_##protoname > 0) { \\
    int i; \\
    node->field = NIL; \\
    for (i = 0; i < msg->n_##protoname; i++) { \\
      PLpgSQL_raise_option *opt = _readPLpgSQL_raise_option(msg->protoname[i]); \\
      node->field = lappend(node->field, opt); \\
    } \\
  }

// Include generated enum conversion functions
#include "include/pg_query_plpgsql_enum_defs.c"

// Include generated outfuncs definitions
#include "include/pg_query_outfuncs_plpgsql_defs.c"

// Include generated readfuncs definitions
#include "include/pg_query_readfuncs_plpgsql_defs.c"

// Public API
PgQueryProtobuf
pg_query_plpgsql_funcs_to_protobuf(PLpgSQL_function **funcs, int nfuncs)
{
  PgQueryProtobuf protobuf = {0};
  int i;
  PgQuery__PLpgSQLParseResult parse_result = PG_QUERY__PLPG_SQLPARSE_RESULT__INIT;

  parse_result.version = PG_VERSION_NUM;

  if (funcs == NULL || nfuncs == 0)
  {
    parse_result.n_plpgsql_funcs = 0;
    parse_result.plpgsql_funcs = NULL;
  }
  else
  {
    parse_result.n_plpgsql_funcs = nfuncs;
    parse_result.plpgsql_funcs = palloc(sizeof(PgQuery__PLpgSQLFunction*) * nfuncs);

    for (i = 0; i < nfuncs; i++)
    {
      parse_result.plpgsql_funcs[i] = palloc(sizeof(PgQuery__PLpgSQLFunction));
      pg_query__plpg_sql_function__init(parse_result.plpgsql_funcs[i]);
      _outPLpgSQL_function(parse_result.plpgsql_funcs[i], funcs[i]);
    }
  }

  protobuf.len = pg_query__plpg_sqlparse_result__get_packed_size(&parse_result);
  protobuf.data = malloc(sizeof(char) * protobuf.len);
  pg_query__plpg_sqlparse_result__pack(&parse_result, (void*) protobuf.data);

  return protobuf;
}
C

    File.write('./src/pg_query_outfuncs_plpgsql.c', content)
  end
end

PLpgSQLGenerator.new.generate!
