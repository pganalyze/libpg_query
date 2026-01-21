#!/usr/bin/env ruby

# Extract PLpgSQL type definitions from plpgsql.h
# Outputs JSON files to srcdata/ for use by generate_plpgsql_protobuf.rb

require 'bundler'
require 'json'

class PLpgSQLExtractor
  def initialize(plpgsql_header_path)
    @header_path = plpgsql_header_path
  end

  def underscore(str)
    str
      .gsub(/([A-Z]+)([A-Z][a-z])/, '\1_\2')
      .gsub(/([a-z\d])([A-Z])/, '\1_\2')
      .tr('-', '_')
      .gsub(/\s/, '_')
      .gsub(/__+/, '_')
      .downcase
  end

  # Types we skip entirely (runtime-only, complex pointers, etc.)
  SKIP_TYPES = [
    'SPIPlanPtr', 'Bitmapset*', 'ExprState*', 'CachedPlanSource*', 'CachedPlan*',
    'Param*', 'TypeCacheEntry*', 'TupleDesc', 'ExpandedRecordHeader*',
    'ExpandedRecordFieldInfo', 'PLpgSQL_function*', 'PLpgSQL_nsitem*',
    'MemoryContext', 'PLpgSQL_func_hashkey*', 'PLpgSQL_execstate*',
    'ItemPointerData', 'Datum', 'LocalTransactionId', 'Expr*', 'TypeName*'
  ]

  # Fields to skip in structs (runtime fields)
  SKIP_FIELDS = {
    'PLpgSQL_expr' => ['plan', 'paramnos', 'func', 'ns', 'expr_simple_expr', 'expr_simple_type',
                       'expr_simple_typmod', 'expr_simple_mutable', 'target_param', 'expr_rw_param',
                       'expr_simple_plansource', 'expr_simple_plan', 'expr_simple_plan_lxid',
                       'expr_simple_state', 'expr_simple_in_use', 'expr_simple_lxid'],
    'PLpgSQL_var' => ['value', 'isnull', 'freeval'],
    'PLpgSQL_row' => ['rowtupdesc', 'varnos'],  # varnos uses nfields for count, complex
    'PLpgSQL_rec' => ['erh', 'rectypeid'],
    'PLpgSQL_recfield' => ['rectupledescid', 'finfo'],
    'PLpgSQL_type' => ['typoid', 'typlen', 'typbyval', 'typtype', 'collation',
                       'typisarray', 'atttypmod', 'origtypname', 'tcache', 'tupdesc_id'],
    'PLpgSQL_function' => ['fn_oid', 'fn_xmin', 'fn_tid', 'fn_input_collation', 'fn_hashkey',
                           'fn_cxt', 'fn_rettype', 'fn_rettyplen', 'fn_retbyval', 'fn_retistuple',
                           'fn_retisdomain', 'fn_retset', 'fn_readonly', 'fn_prokind', 'fn_nargs',
                           'fn_argvarnos', 'copiable_size', 'nstatements',
                           'requires_procedure_resowner', 'cur_estate', 'use_count', 'datums'],
    'PLpgSQL_nsitem' => ['prev', 'name'],
    'PLpgSQL_condition' => ['next'],  # Linked list, handle specially
  }

  # Structs we want to extract (statements, datums, helper types)
  TARGET_STRUCTS = [
    'PLpgSQL_type', 'PLpgSQL_expr', 'PLpgSQL_datum', 'PLpgSQL_variable',
    'PLpgSQL_var', 'PLpgSQL_row', 'PLpgSQL_rec', 'PLpgSQL_recfield',
    'PLpgSQL_condition', 'PLpgSQL_exception_block', 'PLpgSQL_exception',
    'PLpgSQL_stmt', 'PLpgSQL_stmt_block', 'PLpgSQL_stmt_assign',
    'PLpgSQL_stmt_perform', 'PLpgSQL_stmt_call', 'PLpgSQL_stmt_commit',
    'PLpgSQL_stmt_rollback', 'PLpgSQL_diag_item', 'PLpgSQL_stmt_getdiag',
    'PLpgSQL_stmt_if', 'PLpgSQL_if_elsif', 'PLpgSQL_stmt_case',
    'PLpgSQL_case_when', 'PLpgSQL_stmt_loop', 'PLpgSQL_stmt_while',
    'PLpgSQL_stmt_fori', 'PLpgSQL_stmt_forq', 'PLpgSQL_stmt_fors',
    'PLpgSQL_stmt_forc', 'PLpgSQL_stmt_dynfors', 'PLpgSQL_stmt_foreach_a',
    'PLpgSQL_stmt_open', 'PLpgSQL_stmt_fetch', 'PLpgSQL_stmt_close',
    'PLpgSQL_stmt_exit', 'PLpgSQL_stmt_return', 'PLpgSQL_stmt_return_next',
    'PLpgSQL_stmt_return_query', 'PLpgSQL_stmt_raise', 'PLpgSQL_raise_option',
    'PLpgSQL_stmt_assert', 'PLpgSQL_stmt_execsql', 'PLpgSQL_stmt_dynexecute',
    'PLpgSQL_function',
  ]

  # Enums we want to extract
  TARGET_ENUMS = [
    'PLpgSQL_nsitem_type', 'PLpgSQL_label_type', 'PLpgSQL_datum_type',
    'PLpgSQL_promise_type', 'PLpgSQL_type_type', 'PLpgSQL_stmt_type',
    'PLpgSQL_getdiag_kind', 'PLpgSQL_raise_option_type',
    'PLpgSQL_resolve_option', 'PLpgSQL_trigtype',
  ]

  def extract!
    @struct_defs = {}
    @enum_defs = {}
    @current_struct_def = nil
    @current_enum_def = nil
    @open_comment = false
    @open_comment_text = nil

    lines = File.read(@header_path)
    lines.each_line do |line|
      if !@current_struct_def.nil?
        handle_struct(line)
      elsif !@current_enum_def.nil?
        handle_enum(line)
      elsif line[/^typedef struct ([A-z_]+)\s*(\/\*.+)?$/]
        name = $1
        if TARGET_STRUCTS.include?(name)
          @current_struct_def = { name: name, fields: [], comment: @open_comment_text }
          @open_comment_text = nil
        end
      elsif line[/^\s*typedef enum\s*([A-z_]+)?\s*(\/\*.+)?(?: {)?$/]
        name = $1
        if TARGET_ENUMS.include?(name)
          @current_enum_def = { name: name, values: [], comment: @open_comment_text }
          @open_comment_text = nil
        end
      elsif line.strip.start_with?('/*')
        @open_comment_text = line
        @open_comment = !line.include?('*/')
      elsif @open_comment
        @open_comment_text += "\n" unless @open_comment_text.end_with?("\n")
        @open_comment_text += line
        @open_comment = !line.include?('*/')
      end
    end

    # Write output files
    File.write('./srcdata/plpgsql_struct_defs.json', JSON.pretty_generate(@struct_defs))
    File.write('./srcdata/plpgsql_enum_defs.json', JSON.pretty_generate(@enum_defs))

    puts "Extracted #{@struct_defs.size} structs and #{@enum_defs.size} enums"
  end

  def handle_struct(line)
    # Match struct fields, handling array declarations like int field[SIZE]
    # Note: Use [a-zA-Z] instead of [A-z] because A-z includes [ \ ] ^ _ ` characters
    if line[/^\s+(struct |const )?([a-zA-Z0-9_]+)\s+(\*{0,2})([a-zA-Z_]+)(\[[A-Z_0-9]+\])?;\s*(\/\*.+)?/]
      c_type = $2 + $3.to_s
      raw_name = $4
      is_array = !$5.nil?
      comment = $6

      # Extract the actual field name without array subscript
      name = raw_name

      struct_name = @current_struct_def[:name]
      skip_fields = SKIP_FIELDS[struct_name] || []

      # Skip this field if it's in the skip list or uses a skipped type
      # Also skip array fields as they need special handling
      unless skip_fields.include?(name) || SKIP_TYPES.include?(c_type) || is_array
        @current_struct_def[:fields] << { name: name, c_type: c_type, comment: comment }
      end

      @open_comment = line.include?('/*') && !line.include?('*/')
    elsif line[/^\}\s*([A-z_]+)?;/]
      name = @current_struct_def.delete(:name)
      @struct_defs[name] = @current_struct_def
      @current_struct_def = nil
    elsif line.strip.start_with?('/*')
      @current_struct_def[:fields] << { comment: line }
      @open_comment = !line.include?('*/')
    elsif @open_comment
      if @current_struct_def[:fields].last && @current_struct_def[:fields].last[:comment]
        @current_struct_def[:fields].last[:comment] += "\n" unless @current_struct_def[:fields].last[:comment].end_with?("\n")
        @current_struct_def[:fields].last[:comment] += line
      end
      @open_comment = !line.include?('*/')
    end
  end

  def handle_enum(line)
    if line[/^\s+([A-Z0-9_]+)(?: = (\d+))?,?\s*(\/\*.+)?/]
      name = $1
      value = $2&.to_i
      comment = $3

      # Calculate value if not explicit
      if value.nil?
        previous_values = @current_enum_def[:values].map { |v| v[:value] }.compact
        value = previous_values.empty? ? 0 : previous_values.last + 1
      end

      @current_enum_def[:values] << { name: name, value: value, comment: comment }
      @open_comment = line.include?('/*') && !line.include?('*/')
    elsif line[/^\}\s*([A-z_]+)?;/]
      name = @current_enum_def.delete(:name) || $1
      @enum_defs[name] = @current_enum_def
      @current_enum_def = nil
    elsif line.strip.start_with?('/*')
      @current_enum_def[:values] << { comment: line }
      @open_comment = !line.include?('*/')
    elsif @open_comment
      if @current_enum_def[:values].last && @current_enum_def[:values].last[:comment]
        @current_enum_def[:values].last[:comment] += "\n" unless @current_enum_def[:values].last[:comment].end_with?("\n")
        @current_enum_def[:values].last[:comment] += line
      end
      @open_comment = !line.include?('*/')
    end
  end
end

# Default path for the PLpgSQL header in this repo
default_path = './src/postgres/include/plpgsql.h'
header_path = ARGV[0] || default_path

if !File.exist?(header_path)
  puts "ERROR: PLpgSQL header not found at #{header_path}"
  puts "Usage: #{$0} [path/to/plpgsql.h]"
  exit 1
end

PLpgSQLExtractor.new(header_path).extract!
