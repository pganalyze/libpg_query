# rubocop:disable Metrics/MethodLength, Style/WordArray, Metrics/LineLength, Style/Documentation, Style/PerlBackrefs, Metrics/AbcSize, Metrics/CyclomaticComplexity, Metrics/PerceivedComplexity

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
    ['Query', 'queryId']        => :skip, # we intentionally do not print the queryId field
    ['RangeVar', 'catalogname'] => :skip, # presently not semantically meaningful
  }

  def generate_outmethods!
    source = target = nil
    @outmethods = {}

    # Note: We intentionally don't read relation.h & plannodes.h since we're only
    #   interesting in parsing (not planning) queries
    lines = File.read(File.join(@pgdir, '/src/include/nodes/parsenodes.h')) +
            File.read(File.join(@pgdir, '/src/include/nodes/primnodes.h')) +
            File.read(File.join(@pgdir, '/src/include/nodes/value.h'))
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
          elsif name == 'location' && type == 'int'
            @outmethods[target] += format("  WRITE_LOCATION_FIELD(%s);\n", name)
          elsif ['bool', 'long', 'char'].include?(type)
            @outmethods[target] += format("  WRITE_%s_FIELD(%s);\n", type.upcase, name)
          elsif ['int', 'int16', 'int32', 'AttrNumber'].include?(type)
            @outmethods[target] += format("  WRITE_INT_FIELD(%s);\n", name)
          elsif ['uint', 'uint16', 'uint32', 'Index', 'bits32', 'Oid'].include?(type)
            @outmethods[target] += format("  WRITE_UINT_FIELD(%s);\n", name)
          elsif type == 'char*'
            @outmethods[target] += format("  WRITE_STRING_FIELD(%s);\n", name)
          elsif ['float', 'double', 'Cost', 'Selectivity'].include?(type)
            @outmethods[target] += format("  WRITE_FLOAT_FIELD(%s);\n", name)
          elsif ['Bitmapset*', 'Relids'].include?(type)
            @outmethods[target] += format("  WRITE_BITMAPSET_FIELD(%s);\n", name)
          elsif ['Value', 'CreateStmt'].include?(type)
            @outmethods[target] += format("  appendStringInfo(str, \"\\\"%s\\\": \");\n", name)
            @outmethods[target] += format("  _outNode(str, &node->%s);\n", name)
            @outmethods[target] += format("  appendStringInfo(str, \", \");\n")
          elsif type == 'Node*' || @nodetypes.include?(type[0..-2])
            @outmethods[target] += format("  WRITE_NODE_FIELD(%s);\n", name)
          elsif type.end_with?('*')
            puts format('ERR: %s %s', name, type)
          else # Enum
            @outmethods[target] += format("  WRITE_ENUM_FIELD(%s, %s);\n", name, type)
          end
        elsif line == format("} %s;\n", source)
          source = target = nil
        end
      elsif line[/typedef struct ([A-z]+)/]
        source = target = $1
        @outmethods[target] = format("  WRITE_NODE_TYPE(\"%s\");\n\n", target)
      elsif line[/^typedef ([A-z]+) ([A-z]+);/]
        @outmethods[$2] = @outmethods[$1]
      end
    end
  end

  IGNORE_LIST = [
    'Expr', # Unclear why this isn't needed (FIXME)
    'Value', # Special case
    'Const', # Only needed in post-parse analysis (and it introduces Datums, which we can't output)
  ]
  def generate!
    generate_nodetypes!
    generate_outmethods!

    defs = ''
    conds = ''

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
