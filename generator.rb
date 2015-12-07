# rubocop:disable Metrics/ClassLength, Metrics/MethodLength, Style/WordArray, Metrics/LineLength, Style/Documentation, Style/PerlBackrefs, Style/TrailingComma, Metrics/AbcSize, Metrics/CyclomaticComplexity, Metrics/PerceivedComplexity, Metrics/BlockNesting, Lint/AssignmentInCondition

require 'bundler'

class Generator
  def initialize(pgdir)
    @pgdir = pgdir
  end

  def generate_nodetypes!
    inside = false
    @nodetypes = []

    lines = File.read(File.join(@pgdir, '/src/include/nodes/nodes.h'))
    lines.each_line do |line|
      if inside
        if line[/([A-z_]+)(\s+=\s+\d+)?,/]
          @nodetypes << $1[2..-1] # Without T_ prefix
        elsif line == "} NodeTag;\n"
          inside = false
        end
      elsif line == "typedef enum NodeTag\n"
        inside = true
      end
    end
  end

  TYPE_OVERRIDES = {
    ['Query', 'queryId']                     => :skip, # we intentionally do not print the queryId field
    ['RangeVar', 'catalogname']              => :skip, # presently not semantically meaningful
    ['PlannerGlobal', 'boundParams']         => :skip, # NB: this isn't a complete set of fields
    ['PlannerGlobal', 'subroots']            => :skip, # ^
    ['Plan', 'startup_cost']                 => 'float',
    ['Plan', 'total_cost']                   => 'float',
    ['Plan', 'plan_rows']                    => 'float',
    ['IndexPath', 'indextotalcost']          => 'float',
    ['IndexPath', 'indexselectivity']        => 'float',
    ['BitmapAndPath', 'bitmapselectivity']   => 'float',
    ['BitmapOrPath', 'bitmapselectivity']    => 'float',
    ['MergeAppendPath', 'limit_tuples']      => 'float',
    ['SubPlan', 'startup_cost']              => 'float',
    ['SubPlan', 'per_call_cost']             => 'float',
    ['ParamPathInfo', 'ppi_rows']            => 'float',
    ['RestrictInfo', 'eval_cost']            => :skip, # NB: this isn't a complete set of fields
    ['RestrictInfo', 'scansel_cache']        => :skip, # ^
    ['RestrictInfo', 'left_bucketsize']      => :skip, # ^
    ['RestrictInfo', 'right_bucketsize']     => :skip, # ^
    ['RestrictInfo', 'parent_ec']            => :skip, # don't write, leads to infinite recursion in plan tree dump
    ['RestrictInfo', 'left_ec']              => :skip, # ^
    ['RestrictInfo', 'right_ec']             => :skip, # ^
    ['RestrictInfo', 'norm_selec']           => 'float',
    ['RestrictInfo', 'outer_selec']          => 'float',
    ['MinMaxAggInfo', 'subroot']             => :skip, # too large, not interesting enough
    ['MinMaxAggInfo', 'pathcost']            => 'float',
    ['PlannerInfo', 'parent_root']           => :skip, # NB: this isn't a complete set of fields
    ['PlannerInfo', 'simple_rel_array_size'] => :skip, # ^
    ['PlannerInfo', 'join_rel_hash']         => :skip, # ^
    ['PlannerInfo', 'initial_rels']          => :skip, # ^
    ['PlannerInfo', 'planner_cxt']           => :skip, # ^
    ['PlannerInfo', 'non_recursive_plan']    => :skip, # ^
    ['PlannerInfo', 'join_search_private']   => :skip, # ^
    ['PlannerInfo', 'total_table_pages']     => 'float',
    ['PlannerInfo', 'tuple_fraction']        => 'float',
    ['PlannerInfo', 'limit_tuples']          => 'float',
    ['RelOptInfo', 'rows']                   => 'float',
    ['RelOptInfo', 'reltablespace']          => 'uint',
    ['RelOptInfo', 'pages']                  => 'uint',
    ['RelOptInfo', 'tuples']                 => 'float',
    ['RelOptInfo', 'allvisfrac']             => 'float',
    ['RelOptInfo', 'attr_needed']            => :skip, # NB: this isn't a complete set of fields
    ['RelOptInfo', 'attr_widths']            => :skip, # ^
    ['RelOptInfo', 'baserestrictcost']       => :skip, # ^
    ['RelOptInfo', 'fdwroutine']             => :skip, # don't try to print
    ['RelOptInfo', 'fdw_private']            => :skip, # ^
    ['IndexOptInfo', 'pages']                => 'uint',
    ['IndexOptInfo', 'tuples']               => 'float',
    ['IndexOptInfo', 'reltablespace']        => :skip, # NB: this isn't a complete set of fields
    ['IndexOptInfo', 'amcostestimate']       => :skip, # ^
    ['IndexOptInfo', 'rel']                  => :skip, # Do NOT print rel field, else infinite recursion
    ['IndexOptInfo', 'indexkeys']            => :skip, # array fields aren't really worth the trouble to print
    ['IndexOptInfo', 'indexcollations']      => :skip, # ^
    ['IndexOptInfo', 'opfamily']             => :skip, # ^
    ['IndexOptInfo', 'opcintype']            => :skip, # ^
    ['IndexOptInfo', 'sortopfamily']         => :skip, # ^
    ['IndexOptInfo', 'reverse_sort']         => :skip, # ^
    ['IndexOptInfo', 'nulls_first']          => :skip, # ^
    ['IndexOptInfo', 'indexprs']             => :skip, # redundant since we print indextlist
    ['IndexOptInfo', 'canreturn']            => :skip, # we don't bother with fields copied from the pg_am entry
    ['IndexOptInfo', 'amcanorderbyop']       => :skip, # ^
    ['IndexOptInfo', 'amoptionalkey']        => :skip, # ^
    ['IndexOptInfo', 'amsearcharray']        => :skip, # ^
    ['IndexOptInfo', 'amsearchnulls']        => :skip, # ^
    ['IndexOptInfo', 'amhasgettuple']        => :skip, # ^
    ['IndexOptInfo', 'amhasgetbitmap']       => :skip, # ^
  }

  INLINE_LISTS = {
    'SetOp' => {
      'dupColIdx' => 'numCols',
      'dupOperators' => 'numCols',
    },
    'Unique' => {
      'uniqColIdx' => 'numCols',
      'uniqOperators' => 'numCols',
    },
    'Sort' => {
      'sortColIdx' => 'numCols',
      'sortOperators' => 'numCols',
      'collations' => 'numCols',
      'nullsFirst' => 'numCols',
    },
    'Group' => {
      'grpColIdx' => 'numCols',
      'grpOperators' => 'numCols',
    },
    'WindowAgg' => {
      'partColIdx' => 'partNumCols',
      'partOperators' => 'partNumCols',
      'ordColIdx' => 'ordNumCols',
      'ordOperators' => 'ordNumCols',
    },
    'Agg' => {
      'grpColIdx' => 'numCols',
      'grpOperators' => 'numCols',
    },
    'MergeJoin' => {
      'mergeFamilies' => 'numCols',
      'mergeCollations' => 'numCols',
      'mergeStrategies' => 'numCols',
      'mergeNullsFirst' => 'numCols',
    },
    'RecursiveUnion' => {
      'dupColIdx' => 'numCols',
      'dupOperators' => 'numCols',
    },
    'MergeAppend' => {
      'sortColIdx' => 'numCols',
      'sortOperators' => 'numCols',
      'collations' => 'numCols',
      'nullsFirst' => 'numCols',
    },
  }
  INLINED_TYPES = [
    'Plan', 'Scan', 'Join',
    'Path', 'JoinPath',
    'CreateStmt',
  ]

  def generate_outmethods!
    source = target = nil
    @outmethods = {}
    @inlined_outmethods = []

    lines = File.read(File.join(@pgdir, '/src/include/nodes/parsenodes.h')) +
            File.read(File.join(@pgdir, '/src/include/nodes/plannodes.h')) +
            File.read(File.join(@pgdir, '/src/include/nodes/primnodes.h')) +
            File.read(File.join(@pgdir, '/src/include/nodes/value.h')) +
            File.read(File.join(@pgdir, '/src/include/nodes/relation.h'))
    lines.each_line do |line|
      if source
        if line[/^\s+(struct |const )?([A-z0-9]+)\s+(\*)?([A-z_]+);/]
          name = $4
          orig_type = $2 + $3.to_s
          type = TYPE_OVERRIDES[[source, name]] || orig_type
          if type == :skip || type == 'Expr'
            # Ignore
          elsif type == 'NodeTag'
            # Nothing
          elsif INLINED_TYPES.include?(type)
            # Inline this field as if its sub-fields were part of the struct
            @outmethods[target] += format("  _out%sInfo(str, (const %s *) node);\n\n", type, type)
          elsif name == 'location' && type == 'int'
            @outmethods[target] += format("  WRITE_LOCATION_FIELD(%s);\n", name)
          elsif ['bool', 'long', 'Oid', 'char'].include?(type)
            @outmethods[target] += format("  WRITE_%s_FIELD(%s);\n", type.upcase, name)
          elsif ['int', 'int16', 'int32', 'AttrNumber'].include?(type)
            @outmethods[target] += format("  WRITE_INT_FIELD(%s);\n", name)
          elsif ['uint', 'uint16', 'uint32', 'Index', 'bits32'].include?(type)
            @outmethods[target] += format("  WRITE_UINT_FIELD(%s);\n", name)
          elsif type == 'char*'
            @outmethods[target] += format("  WRITE_STRING_FIELD(%s);\n", name)
          elsif ['float', 'double', 'Cost', 'Selectivity'].include?(type)
            @outmethods[target] += format("  WRITE_FLOAT_FIELD(%s);\n", name)
          elsif ['Bitmapset*', 'Relids'].include?(type)
            @outmethods[target] += format("  WRITE_BITMAPSET_FIELD(%s);\n", name)
          elsif type == 'Value'
            @outmethods[target] += format("  _outValue(str, &node->%s);\n", name)
          elsif type == 'Node*' || @nodetypes.include?(type[0..-2])
            @outmethods[target] += format("  WRITE_NODE_FIELD(%s);\n", name)
          elsif type.end_with?('*')
            if INLINE_LISTS[target] && num_src = INLINE_LISTS[target][name]
              unless @outmethods[target].start_with?('  int i;')
                @outmethods[target] = "  int i;\n\n" + @outmethods[target]
              end
              @outmethods[target] += format("  appendStringInfoString(str, \"\\\"%s\\\": [\");\n", name)
              @outmethods[target] += format("  for (i = 0; i < node->%s; i++)\n", num_src)
              if ['AttrNumber*', 'int*'].include?(type)
                @outmethods[target] += format("    appendStringInfo(str, \"%%d, \", node->%s[i]);\n", name)
              elsif ['Oid*'].include?(type)
                @outmethods[target] += format("    appendStringInfo(str, \"%%u, \", node->%s[i]);\n", name)
              elsif type == 'bool*'
                @outmethods[target] += format("    appendStringInfo(str, \"%%s, \", booltostr(node->%s[i]));\n", name)
              else
                puts format('ERR: Unknown list item type %s', type)
              end
              @outmethods[target] += "  removeTrailingDelimiter(str);\n"
              @outmethods[target] += "  appendStringInfoString(str, \"], \");\n\n"
            else
              puts format('ERR: %s %s', name, type)
            end
          else # Enum
            @outmethods[target] += format("  WRITE_ENUM_FIELD(%s, %s);\n", name, type)
          end
        elsif line == format("} %s;\n", source)
          source = target = nil
        end
      elsif line[/typedef struct ([A-z]+)/]
        if INLINED_TYPES.include?($1)
          source = $1
          target = $1 + 'Info'
          @outmethods[target] = format("  WRITE_NODE_TYPE(\"%s\");\n\n", target.upcase)
          @outmethods[source] = format("  _out%s(str, (const %s *) node);\n\n", target, source)
        else
          source = target = $1
          @outmethods[target] = format("  WRITE_NODE_TYPE(\"%s\");\n\n", target.upcase)
        end
      elsif line[/^typedef ([A-z]+) ([A-z]+);/]
        @outmethods[$2] = @outmethods[$1]
      end
    end
  end

  IGNORE_LIST = [
    'Expr', # Unclear why this isn't needed (FIXME)
    'Const', # Complex case (Datum)
    'Path', # Complex case
    'EquivalenceClass', # Complex case
    'MergeJoin', # Special case
    'Value', # Special case
  ]
  def generate!
    generate_nodetypes!
    generate_outmethods!

    defs = ''
    conds = ''

    INLINED_TYPES.each do |type|
      next if IGNORE_LIST.include?(type)
      defs += "static void\n"
      defs += format("_out%sInfo(StringInfo str, const %s *node)\n", type, type)
      defs += "{\n"
      defs += @outmethods[type + 'Info']
      defs += "}\n"
      defs += "\n"
    end

    @nodetypes.each do |type|
      next if IGNORE_LIST.include?(type)
      outmethod = @outmethods[type]
      next unless outmethod

      defs += "static void\n"
      defs += format("_out%s(StringInfo str, const %s *node)\n", type, type)
      defs += "{\n"
      defs += outmethod
      defs += "}\n"
      defs += "\n"

      conds += format("case T_%s:\n", type)
      conds += format("  _out%s(str, obj);\n", type)
      conds += "  break;\n"
    end

    File.write('./output_node_json_defs.c', defs)
    File.write('./output_node_json_conds.c', conds)
  end
end

Generator.new('./postgres').generate!
