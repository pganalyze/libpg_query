# rubocop:disable all

# You need to call this with the PostgreSQL source directory as the first commandline agument, and the output dir as the second
# ./scripts/extract_source.rb ./tmp/postgres ./src/postgres

require 'ffi/clang'
require 'json'

module FFI::Clang::Lib
  enum :storage_class, [
    :invalid, 0,
    :none, 1,
    :extern, 2,
    :static, 3,
    :private_extern, 4,
    :opencl_workgroup_local, 5,
    :auto, 6,
    :register, 7,
  ]

  attach_function :get_storage_class, :clang_Cursor_getStorageClass, [FFI::Clang::Lib::CXCursor.by_value], :storage_class
end

module FFI::Clang
  class Cursor
    def storage_class
      Lib.get_storage_class(@cursor)
    end

    # Copy of clang::VarDecl::hasExternalStorage http://clang.llvm.org/doxygen/Decl_8h_source.html#l00982
    def has_external_storage
      storage_class == :extern || storage_class == :private_extern
    end
  end
end

class Runner
  attr_reader :unresolved
  attr_reader :code_for_resolve

  def initialize
    @file_analysis = {}
    @global_method_to_base_filename = {}
    @file_to_method_and_pos = {}
    @external_variables = []

    @resolved_static_by_base_filename = {}
    @resolved_global = []

    @symbols_to_output = {}
    @include_files_to_output = []
    @unresolved = []

    @blocklist = []
    @mock = {}

    @basepath = File.absolute_path(ARGV[0]) + '/'
    @out_path = File.absolute_path(ARGV[1]) + '/'
  end

  def blocklist(symbol)
    @blocklist << symbol
  end

  def mock(symbol, code = nil, add_definition = true)
    @mock[symbol] = code ? [code, add_definition] : ["\n" + File.read(File.join(__dir__, 'mocks', symbol + '.c')) + "\n", false]
  end

  def run
    files = Dir.glob(@basepath + 'src/backend/**/*.c') +
    Dir.glob(@basepath + 'src/common/**/*.c') +
    Dir.glob(@basepath + 'src/port/**/*.c') +
    Dir.glob(@basepath + 'src/timezone/**/*.c') +
    Dir.glob(@basepath + 'src/pl/plpgsql/src/*.c') +
    Dir.glob(@basepath + 'contrib/pgcrypto/*.c') -
    [ # blocklist
      @basepath + 'src/backend/libpq/be-secure-openssl.c', # OpenSSL include error
      @basepath + 'src/backend/utils/adt/levenshtein.c', # Built through varlena.c
      @basepath + 'src/backend/utils/adt/like_match.c', # Built through like.c
      @basepath + 'src/backend/utils/adt/jsonpath_scan.c', # Built through jsonpath.c
      @basepath + 'src/backend/utils/misc/guc-file.c', # Built through guc.c
      @basepath + 'src/backend/utils/sort/qsort_tuple.c', # Built through tuplesort.c
      @basepath + 'src/backend/bootstrap/bootscanner.c', # Built through bootparse.c
      @basepath + 'src/backend/regex/regc_color.c', # Built through regcomp.c
      @basepath + 'src/backend/regex/regc_cvec.c', # Built through regcomp.c
      @basepath + 'src/backend/regex/regc_lex.c', # Built through regcomp.c
      @basepath + 'src/backend/regex/regc_pg_locale.c', # Built through regcomp.c
      @basepath + 'src/backend/regex/regc_locale.c', # Built through regcomp.c
      @basepath + 'src/backend/regex/regc_nfa.c', # Built through regcomp.c
      @basepath + 'src/backend/regex/rege_dfa.c', # Built through regexec.c
      @basepath + 'src/backend/replication/repl_scanner.c', # Built through repl_gram.c
      @basepath + 'src/backend/replication/libpqwalreceiver/libpqwalreceiver.c', # Dynamic module
      @basepath + 'src/backend/replication/syncrep_scanner.c', # Built through syncrep.c
      @basepath + 'src/backend/port/posix_sema.c', # Linux only
      @basepath + 'src/backend/utils/activity/pgstat_wait_event.c', # Built through wait_event.c
      @basepath + 'src/backend/utils/activity/wait_event_funcs_data.c', # Built through wait_event.c
      @basepath + 'src/common/fe_memutils.c', # This file is not expected to be compiled for backend code
      @basepath + 'src/common/restricted_token.c', # This file is not expected to be compiled for backend code
      @basepath + 'src/common/unicode/norm_test.c', # This file is not expected to be compiled for backend code
      @basepath + 'src/backend/utils/mb/win866.c', # Win32 only
      @basepath + 'src/backend/utils/mb/win1251.c', # Win32 only
      @basepath + 'src/backend/utils/mb/iso.c', # Win32 only
      @basepath + 'src/port/dirent.c', # Win32 only
      @basepath + 'src/port/win32error.c', # Win32 only
      @basepath + 'src/port/win32env.c', # Win32 only
      @basepath + 'src/port/win32security.c', # Win32 only
      @basepath + 'src/port/win32gettimeofday.c', # Win32 only
      @basepath + 'src/port/win32pwrite.c', # Win32 only
      @basepath + 'src/port/win32pread.c', # Win32 only
      @basepath + 'src/port/win32link.c', # Win32 only
      @basepath + 'src/port/win32getrusage.c', # Win32 only
      @basepath + 'src/port/strnlen.c', # Not needed and conflicts with available function
      @basepath + 'src/port/strlcat.c', # Not needed and conflicts with available function
      @basepath + 'src/port/unsetenv.c', # Not needed and conflicts with available function
      @basepath + 'src/port/getaddrinfo.c', # Not needed and conflicts with available function
      @basepath + 'src/port/getrusage.c', # Not needed and conflicts with available function
      @basepath + 'src/port/pg_crc32c_armv8.c', # Can't be parsed outside of ARMv8 compatible environments
      @basepath + 'src/port/pg_crc32c_armv8_choose.c', # Can't be parsed outside of ARMv8 compatible environments
      @basepath + 'src/backend/jit/llvm/llvmjit_expr.c', # Requires LLVM-C library (which we don't want to require)
      @basepath + 'src/backend/jit/llvm/llvmjit_deform.c', # Requires LLVM-C library (which we don't want to require)
      @basepath + 'src/backend/jit/llvm/llvmjit.c', # Requires LLVM-C library (which we don't want to require)
      @basepath + 'src/backend/libpq/be-gssapi-common.c', # Requires GSSAPI (which we don't want to require)
      @basepath + 'src/backend/libpq/be-secure-gssapi.c', # Requires GSSAPI (which we don't want to require)
      @basepath + 'src/common/protocol_openssl.c', # Requires OpenSSL (which we don't want to require)
      @basepath + 'contrib/pgcrypto/pgp-mpi-openssl.c', # Requires OpenSSL (which we don't want to require)
      @basepath + 'contrib/pgcrypto/openssl.c', # Requires OpenSSL (which we don't want to require)
    ] -
    Dir.glob(@basepath + 'src/backend/port/dynloader/*.c') -
    Dir.glob(@basepath + 'src/backend/port/win32/*.c') -
    Dir.glob(@basepath + 'src/backend/port/win32_*.c') -
    Dir.glob(@basepath + 'src/backend/snowball/**/*.c') -
    Dir.glob(@basepath + 'src/backend/nodes/*.switch.c') -
    Dir.glob(@basepath + 'src/backend/nodes/*.funcs.c')

    #files = [@basepath + 'src/backend/parser/keywords.c']

    files.each do |file|
      if files == [file]
        puts format('Analysing single file: %s', file)
        analysis = analyze_file(file)
        analysis_file = analysis.save
        puts format('Result: %s', analysis_file)
        exit 1
      end

      print '.'
      analysis = FileAnalysis.restore(file, @basepath) || analyze_file(file)
      analysis.save

      @file_analysis[file] = analysis

      analysis.symbol_to_file.each do |symbol, _|
        next if analysis.static_symbols.include?(symbol)
        if @global_method_to_base_filename[symbol] && !['main', 'Pg_magic_func', 'pg_open_tzfile', '_PG_init'].include?(symbol) && !@global_method_to_base_filename[symbol].end_with?('c')
          puts format('Error processing %s, symbol %s already defined by %s', file, symbol, @global_method_to_base_filename[symbol])
        end
        @global_method_to_base_filename[symbol] = file
      end

      analysis.file_to_symbol_positions.each do |file, method_and_pos|
        @file_to_method_and_pos[file] = method_and_pos
      end

      analysis.external_variables.each do |symbol|
        @external_variables << symbol
      end
    end

    #puts @caller_to_static_callees['/Users/lfittl/Code/libpg_query/postgres/src/backend/regex/regc_locale.c']['cclass'].inspect

    puts "\nFinished parsing"
  end

  class FileAnalysis
    attr_accessor :references, :static_symbols, :symbol_to_file, :file_to_symbol_positions, :external_variables, :included_files

    def initialize(filename, basepath, references = {}, static_symbols = [],
      symbol_to_file = {}, file_to_symbol_positions = {}, external_variables = [],
      included_files = [])
      @filename = filename
      @basepath = basepath
      @references = references
      @static_symbols = static_symbols
      @symbol_to_file = symbol_to_file
      @file_to_symbol_positions = file_to_symbol_positions
      @external_variables = external_variables
      @included_files = included_files
    end

    def save
      json = JSON.pretty_generate({
        references: @references,
        static_symbols: @static_symbols,
        symbol_to_file: @symbol_to_file,
        file_to_symbol_positions: @file_to_symbol_positions,
        external_variables: @external_variables,
        included_files: @included_files,
      })

      file = self.class.analysis_filename(@filename, @basepath)
      FileUtils.mkdir_p(File.dirname(file))
      File.write(file, json)
      file
    end

    def self.restore(filename, basepath)
      json = File.read(analysis_filename(filename, basepath))
      hsh = JSON.parse(json)
      new(filename, basepath, hsh['references'], hsh['static_symbols'],
      hsh['symbol_to_file'], hsh['file_to_symbol_positions'], hsh['external_variables'],
      hsh['included_files'])
    rescue Errno::ENOENT
      nil
    end

    private

    def self.analysis_filename(filename, basepath)
      File.absolute_path('./tmp/analysis') + '/' + filename.gsub(%r{^#{basepath}}, '').gsub(/.c$/, '.json')
    end
  end

  def analyze_file(file)
    index = FFI::Clang::Index.new(true, true)
    flags = [
      '-I', @basepath + 'src/include',
      '-I', '/usr/local/opt/openssl/include',
      '-I', `xcrun --sdk macosx --show-sdk-path`.strip + '/usr/include',
      '-DDLSUFFIX=".bundle"',
      '-g',
      '-ferror-limit=0',
      '-DUSE_ASSERT_CHECKING',
      # EXEC_BACKEND is used on Windows, and can always be safely set during code analysis
      '-DEXEC_BACKEND',
      '-Wno-nullability-completeness'
    ]

    # For certain files, use WIN32 define - we can't always do this since it pulls unnecessary code in other cases
    if file == @basepath + 'src/backend/utils/error/elog.c' || file == @basepath + 'src/backend/utils/mb/mbutils.c'
      flags << '-DWIN32'
      flags << '-D__CYGWIN__' # Avoid pulling in win32_port.h (which includes a bunch of system headers we don't actually have)
    end

    # To override built-ins, we must avoid pulling in any system headers, so pretend we already defined c.h
    if file == @basepath + 'src/port/strlcpy.c'
      flags << '-DC_H'
      flags << '-DHAVE_DECL_STRLCPY=0'
      flags << '-Dsize_t=unsigned'
    end

    translation_unit = index.parse_translation_unit(file, flags)

    cursor = translation_unit.cursor

    func_cursor = nil
    analysis = FileAnalysis.new(file, @basepath)

    included_files = []
    translation_unit.inclusions do |included_file, _inclusions|
      next if !included_file.start_with?(@basepath) || included_file == file

      included_files << included_file
    end
    analysis.included_files = included_files.uniq.sort

    cursor.visit_children do |cursor, parent|
      if cursor.location.file && (File.dirname(file) == File.dirname(cursor.location.file) || cursor.location.file.end_with?('_impl.h'))
        if parent.kind == :cursor_translation_unit
          if (cursor.kind == :cursor_function && cursor.definition?) || (cursor.kind == :cursor_variable && !cursor.has_external_storage)
            analysis.symbol_to_file[cursor.spelling] = cursor.location.file

            if cursor.linkage == :external
              # Nothing special
            elsif cursor.linkage == :internal
              (analysis.static_symbols << cursor.spelling).uniq!
            else
              fail format('Unknown linkage: %s', cursor.linkage.inspect)
            end

            start_offset = cursor.extent.start.offset
            end_offset = cursor.extent.end.offset
            end_offset += 1 if cursor.kind == :cursor_variable # The ";" isn't counted correctly by clang

            if cursor.kind == :cursor_variable && (cursor.linkage == :external || cursor.linkage == :internal) &&
              !cursor.type.const_qualified? && !(cursor.type.is_a?(FFI::Clang::Types::Array) && cursor.type.element_type.const_qualified?) &&
              !(cursor.type.is_a?(FFI::Clang::Types::Pointer) && cursor.type.pointee.kind == :type_function_proto)
              analysis.external_variables << cursor.spelling
            end

            analysis.file_to_symbol_positions[cursor.location.file] ||= {}
            analysis.file_to_symbol_positions[cursor.location.file][cursor.spelling] = [start_offset, end_offset]

            cursor.visit_children do |child_cursor, parent|
              # There seems to be a bug here on modern Clang versions where the
              # cursor kind gets modified once we call "child_cursor.definition"
              # - thus we make a copy ahead of calling that, for later use
              child_cursor_kind = child_cursor.kind

              # Ignore variable definitions from the local scope
              next :recurse if child_cursor.definition.semantic_parent == cursor

              if child_cursor_kind == :cursor_decl_ref_expr || child_cursor_kind == :cursor_call_expr
                analysis.references[cursor.spelling] ||= []
                (analysis.references[cursor.spelling] << child_cursor.spelling).uniq!
              end

              :recurse
            end
          end
        end
      end

      next :recurse
    end

    analysis
  end

  RESOLVE_MAX_DEPTH = 100

  def deep_resolve(method_name, depth: 0, trail: [], global_resolved_by_parent: [], static_resolved_by_parent: [], static_base_filename: nil)
    if @blocklist.include?(method_name)
      puts 'ERROR: Hit blocklist entry ' + method_name
      puts 'Trail: ' + trail.inspect
      exit 1
    end

    if depth > RESOLVE_MAX_DEPTH
      puts 'ERROR: Exceeded max depth'
      puts method_name.inspect
      puts trail.inspect
      exit 1
    end

    base_filename = static_base_filename || @global_method_to_base_filename[method_name]
    if !base_filename
      (@unresolved << method_name).uniq!
      return
    end

    analysis = @file_analysis[base_filename]
    fail "could not find analysis data for #{base_filename}" if analysis.nil?

    # We need to determine if we can lookup the place where the method lives
    implementation_filename = analysis.symbol_to_file[method_name]
    if !implementation_filename
      (@unresolved << method_name).uniq!
      return
    end

    @symbols_to_output[implementation_filename] ||= []
    @symbols_to_output[implementation_filename] << method_name

    (@include_files_to_output += analysis.included_files).uniq!

    if @mock.key?(method_name)
      # Code will be overwritten at output time, no need to investigate dependents
      return
    end

    # Now we need to resolve all symbols called by this one
    dependents = (analysis.references[method_name] || [])
    global_dependents = dependents.select { |c| !analysis.static_symbols.include?(c) } - global_resolved_by_parent
    static_dependents = dependents.select { |c| analysis.static_symbols.include?(c) } - static_resolved_by_parent

    # First, make sure we exclude all that have been visited before
    @resolved_static_by_base_filename[base_filename] ||= []
    global_dependents.delete_if { |s| @resolved_global.include?(s) }
    static_dependents.delete_if { |s| @resolved_static_by_base_filename[base_filename].include?(s) }

    # Second, make sure we never visit any of the dependents again
    global_dependents.each { |s| @resolved_global << s }
    static_dependents.each { |s| @resolved_static_by_base_filename[base_filename] << s }

    # Third, actually traverse into the remaining, non-visited, dependents
    global_dependents.each do |symbol|
      deep_resolve(
        symbol, depth: depth + 1, trail: trail + [method_name],
        global_resolved_by_parent: global_resolved_by_parent + global_dependents
      )
    end

    static_dependents.each do |symbol|
      deep_resolve(
        symbol, depth: depth + 1, trail: trail + [method_name],
        global_resolved_by_parent: global_resolved_by_parent + global_dependents,
        static_resolved_by_parent: static_resolved_by_parent + static_dependents,
        static_base_filename: base_filename
      )
    end
  end

  def special_include_file?(filename)
    filename[/\/(reg(c|e)_[\w_]+|guc-file|qsort_tuple|repl_scanner|levenshtein|bootscanner|like_match)\.c$/] || filename[/\/[\w_]+\.funcs.c$/] || filename[/\/[\w_]+_impl.h$/]
  end

  def write_out
    all_thread_local_variables = []

    @symbols_to_output.each do |filename, symbols|
      file_thread_local_variables = []
      dead_positions = (@file_to_method_and_pos[filename] || {}).dup

      symbols.each do |symbol|
        next if @mock.key?(symbol)
        next if @external_variables.include?(symbol)

        alive_pos = dead_positions[symbol]

        # In some cases there are other symbols at the same location (macros), so delete by position instead of name
        dead_positions.delete_if { |_,pos| pos == alive_pos }
      end

      full_code = File.read(filename)

      str = "/*--------------------------------------------------------------------\n"
      str += " * Symbols referenced in this file:\n"
      symbols.each do |symbol|
        str += format(" * - %s\n", symbol)
      end
      str += " *--------------------------------------------------------------------\n"
      str += " */\n\n"

      next_start_pos = 0
      dead_positions.each do |symbol, pos|
        fail format("Position overrun for %s in %s, next_start_pos (%d) > file length (%d)", symbol, filename, next_start_pos, full_code.size) if next_start_pos > full_code.size
        fail format("Position overrun for %s in %s, dead position pos[0]-1 (%d) > file length (%d)", symbol, filename, pos[0]-1, full_code.size) if pos[0]-1 > full_code.size

        str += full_code[next_start_pos...(pos[0]-1)]

        skipped_code = full_code[(pos[0]-1)...pos[1]]

        if @mock.key?(symbol)
          mock_code, mock_add_definition = @mock[symbol]
          str += "\n" + skipped_code.split('{').first + "{\n" if mock_add_definition
          if mock_code == :error_not_implemented
            str += "\tAssert(false); elog(ERROR, \"Not implemented\");\n"
          elsif mock_code == :do_nothing
            str += "\t/* Do nothing */\n"
          else
            str += mock_code
          end
          str += "}" if mock_add_definition
        elsif @external_variables.include?(symbol) && symbols.include?(symbol)
          file_thread_local_variables << symbol
          if skipped_code.include?('static')
            str += "\n" + skipped_code.strip.gsub('static', 'static __thread') + "\n"
          else
            str += "\n__thread " + skipped_code.strip + "\n"
          end
        else
          # In the off chance that part of a macro is before a symbol (e.g. ifdef),
          # but the closing part is inside (e.g. endif) we need to output all macros inside skipped parts
          str += "\n" + skipped_code.scan(/^(#\s*(?:define|undef|if|ifdef|ifndef|else|endif))((?:[^\n]*\\\s*\n)*)([^\n]*)$/m).map { |m| m.compact.join }.join("\n")
        end

        next_start_pos = pos[1]
      end
      str += full_code[next_start_pos..-1]

      # In some cases we also need to take care of definitions in the same file
      file_thread_local_variables.each do |variable|
        str.gsub!(/(PGDLLIMPORT|extern)\s+(const|volatile)?\s*(\w+)\s+(\*{0,2})#{variable}(\[\])?;/, "\\1 __thread \\2 \\3 \\4#{variable}\\5;")
      end
      all_thread_local_variables += file_thread_local_variables

      unless special_include_file?(filename)
        out_name = filename.gsub(%r{^#{@basepath}}, '').gsub('/', '_')
        File.write(@out_path + out_name, str)
      end
    end

    #return

    additional_includes = Dir.glob(@basepath + 'src/include/storage/dsm_impl.h') +
      Dir.glob(@basepath + 'src/include/port/atomics/**/*.h') +
      Dir.glob(@basepath + 'src/include/port/win32/**/*.h') +
      Dir.glob(@basepath + 'src/include/port/win32_msvc/**/*.h') +
      Dir.glob(@basepath + 'src/include/port/win32.h') +
      Dir.glob(@basepath + 'src/include/port/win32_port.h')

    (@include_files_to_output + additional_includes).each do |include_file|
      if include_file.start_with?(@basepath + 'src/include')
        out_file = @out_path + include_file.gsub(%r{^#{@basepath}src/}, '')
      else
        out_file = @out_path + 'include/' + File.basename(include_file)
      end

      code = File.read(include_file)
      all_thread_local_variables.each do |variable|
        code.gsub!(/(extern\s+)(PGDLLIMPORT\s+)?(const\s+)?(volatile\s+)?(\w+)\s+(\*{0,2})#{variable}(\[\])?;/, "\\1\\2__thread \\3\\4\\5 \\6#{variable}\\7;")
      end

      FileUtils.mkdir_p File.dirname(out_file)
      File.write(out_file, code)
    end
  end
end

runner = Runner.new
runner.run

runner.blocklist('SearchSysCache')
runner.blocklist('heap_open')
runner.blocklist('relation_open')
runner.blocklist('ProcessClientWriteInterrupt')
runner.blocklist('LWLockAcquire')
runner.blocklist('SPI_freeplan')
runner.blocklist('get_ps_display')
runner.blocklist('pq_beginmessage')

# The following pull in unnecessary dependencies but could technically be permitted
runner.blocklist('lookup_type_cache')
runner.blocklist('get_database_name')
runner.blocklist('AcceptInvalidationMessages')
runner.blocklist('SharedInvalidMessageCounter')
runner.blocklist('LockRelationOid')
runner.blocklist('RangeVarGetRelidExtended')
runner.blocklist('object_aclcheck')

# We have to mock this as it calls `hash_search`, which eventually makes
# calls down to `pgstat_report_wait_start` and `pgstat_report_wait_end`.
# These functions depend on the existence of a global variable
# `my_wait_event_info`.
#
# The problem here is we can't reasonably compile the source file
# `backend/utils/activity/wait_event.c` which provides this symbol, as it
# initializes the value by-default to a reference to another global.
# Normally this is fine, but we transform both of these globals so that they
# are thread local via `__thread`, and it is not valid to initialize one thread
# local with the address of another.
#
# Instead of tackling this directly, we just return `NULL` in the mock below,
# observing that we do not need to support the registration of custom nodes.
runner.mock('GetExtensibleNodeMethods', 'return NULL;')

# Mocks REQUIRED for basic operations (error handling, memory management)
runner.mock('ProcessInterrupts', :do_nothing) # Required by errfinish
runner.mock('PqCommMethods', 'const PQcommMethods *PqCommMethods = NULL;') # Required by errfinish
runner.mock('proc_exit', 'printf("Terminating process due to FATAL error\n"); exit(1);') # Required by errfinish (we use PG_TRY/PG_CATCH, so this should never be reached in practice)
runner.mock('send_message_to_server_log', :do_nothing)
runner.mock('send_message_to_frontend', :do_nothing)

# Mocks REQUIRED for PL/pgSQL parsing
runner.mock('SearchSysCache1')
runner.mock('GetSysCacheOid')
# Mocks consumed by plpgsql_compile_callback when libpg_query forges a
# pg_proc tuple instead of pulling one from the syscache. The file-based
# mocks expect the libpg_query ProcTupWithAttrs wrapper (see
# src/include/pg_query_proctup_attrs.h).
runner.mock('SysCacheGetAttr')
runner.mock('SysCacheGetAttrNotNull')
runner.mock('get_func_arg_info')
runner.mock('cfunc_resolve_polymorphic_argtypes')
runner.mock('format_procedure', 'return pstrdup("plpgsql_function");')
runner.mock('get_fn_expr_rettype', 'return InvalidOid;') # only reached in non-validator mode, which libpg_query never uses
runner.mock('MemoryContextSetIdentifier', :do_nothing)   # only used in MemoryContextStats dumps
runner.mock('typenameTypeMod', 'return -1;')
runner.mock('LookupExplicitNamespace')
runner.mock('recomputeNamespacePath', 'activeSearchPath = list_make2_oid(PG_CATALOG_NAMESPACE, PG_PUBLIC_NAMESPACE);')
runner.mock('ConditionalLockRelationOid', 'return true;')
runner.mock('LockRelationOid', :do_nothing)
runner.mock('UnlockRelationOid', :do_nothing)
runner.mock('AcceptInvalidationMessages', :do_nothing)
runner.mock('ReleaseSysCache', :do_nothing)
runner.mock('build_row_from_class', :do_nothing)
runner.mock('get_collation_oid', 'return DEFAULT_COLLATION_OID;')
runner.mock('plpgsql_parse_wordtype')      # Stub returning a SCALAR PLpgSQL_type carrying "<ident>%TYPE" as typname
runner.mock('plpgsql_parse_wordrowtype')   # Stub returning a SCALAR PLpgSQL_type carrying "<ident>%rowtype" as typname
runner.mock('plpgsql_parse_cwordtype')     # Stub returning a SCALAR PLpgSQL_type carrying "<dotted.idents>%TYPE" as typname
runner.mock('plpgsql_parse_cwordrowtype')  # Stub returning a SCALAR PLpgSQL_type carrying "<dotted.idents>%rowtype" as typname
runner.mock('function_parse_error_transpose', 'return false;')
runner.mock('TypeIsVisible', 'return true;')
runner.mock('printTypmod', 'return psprintf("%s(%d)", typname, (int) typmod);') # Optionally does OidFunctionCall1Coll (which we don't support, so ignore that branch)
runner.mock('assign_expr_collations', :do_nothing) # We need to skip this because we mock transformExpr (called by interpret_function_parameter_list)
runner.mock('contain_var_clause', 'return false;') # We need to skip this because we mock transformExpr (called by interpret_function_parameter_list)
runner.mock('transformExpr', 'return expr;') # Don't transform default expressions in parameters
runner.mock('coerce_to_specific_type', 'return node;') # Don't handle default expression type coercion
runner.mock('free_expr', :do_nothing) # This would free a cached plan, which does not apply to us
runner.mock('build_datatype') # Adjusted to not call lookup_type_cache to reduce dependencies
runner.mock('DeconstructQualifiedName') # Adjusted to not call get_database_name / check database name, avoid inval and lock handling
runner.mock('LookupTypeNameExtended') # Adjusted to not resolve table names
runner.mock('pg_detoast_datum', 'if (VARATT_IS_EXTENDED(datum))
		elog(ERROR, "TOASTed values are not supported");
	else
		return datum;')
runner.mock('pg_detoast_datum_packed', 'if (VARATT_IS_COMPRESSED(datum) || VARATT_IS_EXTERNAL(datum))
		elog(ERROR, "TOASTed values are not supported");
	else
		return datum;')

# Mocks REQUIRED for Windows support
runner.mock('write_stderr') # Avoid pulling in write_console/write_eventlog, and instead always output to stderr (like on POSIX)
runner.mock('should_output_to_client', 'return false;') # Avoid pulling in postmaster.c, which has a bunch of Windows-specific code hidden behind a define

## ---

# SQL Parsing
runner.deep_resolve('raw_parser')

# PL/pgSQL Parsing
runner.deep_resolve('plpgsql_compile_inline')
runner.deep_resolve('plpgsql_compile_callback')
runner.deep_resolve('plpgsql_free_function_memory')
runner.deep_resolve('quote_qualified_identifier')
runner.deep_resolve('interpret_function_parameter_list')
runner.deep_resolve('CreateTemplateTupleDesc')
runner.deep_resolve('TupleDescInitEntry')
runner.deep_resolve('TupleDescInitEntryCollation')
runner.deep_resolve('LookupTypeName')
runner.deep_resolve('typeTypeId')
runner.deep_resolve('IsCatalogNamespace')
runner.deep_resolve('text_to_cstring')
runner.deep_resolve('varstr_levenshtein') # Required so varlena.c builds (needed for text_to_cstring)
runner.deep_resolve('deconstruct_array_builtin')
runner.deep_resolve('plpgsql_extra_errors')
runner.deep_resolve('plpgsql_extra_warnings')
runner.deep_resolve('TypeNameToString')
runner.deep_resolve('get_base_element_type') # needed for build_datatype (dependency not detected due to mock)
runner.deep_resolve('type_is_rowtype') # needed for build_datatype (dependency not detected due to mock)
runner.deep_resolve('setup_parser_errposition_callback') # needed for LookupTypeNameExtended
runner.deep_resolve('cancel_parser_errposition_callback') # needed for LookupTypeNameExtended
runner.deep_resolve('TypenameGetTypidExtended') # needed for LookupTypeNameExtended

# Basic Postgres needed to call parser
runner.deep_resolve('SetDatabaseEncoding')

# Memory management needed to call parser
runner.deep_resolve('MemoryContextInit')
runner.deep_resolve('AllocSetContextCreate')
runner.deep_resolve('MemoryContextSwitchTo')
runner.deep_resolve('CurrentMemoryContext')
runner.deep_resolve('MemoryContextDelete')
runner.deep_resolve('MemoryContextAllocZero')
runner.deep_resolve('MemoryContextSizeFailure')
runner.deep_resolve('AllocSetDeleteFreeList')
runner.deep_resolve('palloc0')

# Error handling needed to call parser
runner.deep_resolve('CopyErrorData')
runner.deep_resolve('FlushErrorState')

# Needed for output funcs
runner.deep_resolve('bms_first_member')
runner.deep_resolve('bms_free')
runner.deep_resolve('bms_next_member')
runner.deep_resolve('bms_num_members')
runner.deep_resolve('makeBitString')

# Needed for deparse
runner.deep_resolve('pg_toupper')
runner.deep_resolve('makeStringInfo')
runner.deep_resolve('list_delete_last')
runner.deep_resolve('list_insert_nth')
runner.deep_resolve('bms_add_member')
runner.deep_resolve('bms_is_member')

# Needed for normalize
runner.deep_resolve('pg_qsort')
runner.deep_resolve('pg_qsort_strcmp')
runner.deep_resolve('raw_expression_tree_walker_impl')

# Needed to work with simplehash (in fingerprinting logic)
runner.deep_resolve('hash_bytes')
runner.deep_resolve('MemoryContextAllocExtended')

# Needed for summary
runner.deep_resolve('makeRangeVarFromNameList')
runner.deep_resolve('list_sort')
runner.deep_resolve('pg_mbcharcliplen')
runner.deep_resolve('pg_mbstrlen')
runner.deep_resolve('destroyStringInfo')

# Other required functions
runner.deep_resolve('pg_printf')
runner.deep_resolve('pg_strncasecmp')

# Retain these functions for optional 32-bit support
# (see BITS_PER_BITMAPWORD checks in bitmapset.c)
runner.deep_resolve('pg_leftmost_one_pos32')
runner.deep_resolve('pg_rightmost_one_pos32')
runner.deep_resolve('pg_popcount32')

# Required for Windows support
runner.deep_resolve('newNodeMacroHolder')
runner.deep_resolve('pg_leftmost_one_pos')
runner.deep_resolve('pg_rightmost_one_pos')
runner.deep_resolve('pg_number_of_ones')
runner.deep_resolve('GetMessageEncoding')
runner.deep_resolve('strlcpy')
runner.deep_resolve('pg_signal_queue')
runner.deep_resolve('pg_signal_mask')
runner.deep_resolve('pgwin32_dispatch_queued_signals')

runner.write_out

#puts runner.unresolved.inspect

# Debugging:
# clang -Xclang -ast-dump -fsyntax-only -I src/include/ src/backend/utils/init/globals.c
