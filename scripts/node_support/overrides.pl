# libpg_query-specific overrides for the node support code generation done via
# the patched gen_node_support.pl (see patches/16_gen_node_support_hook.patch
# and scripts/node_support/hook.pl).
#
# This file keeps all per-node/per-field policy in the libpg_query repository,
# so routine changes here don't require touching the Postgres patch.
#
# Entry kinds:
#
# - fingerprint_exclude_nodes: no fingerprint function and no dispatch case is
#   generated at all (the node either has hand-written handling in
#   pg_query_fingerprint.c, or intentionally falls through to the default
#   branch of the dispatch switch).
#
# - fingerprint_skip_all_nodes: an (empty) fingerprint function is generated
#   that ignores all fields, and the dispatch case ignores the node entirely
#   (not even the node type name is added to the fingerprint).
#
# - fingerprint_custom_body_nodes: the function prototype and dispatch case
#   are generated, but the function body is hand-written in
#   pg_query_fingerprint.c (mirrors Postgres' custom_query_jumble node attribute).
#
# - fingerprint_custom_fields ("Node.field"): the generated function calls
#   _fingerprint<Node>_<field>(ctx, node, parent, field_name, depth), which is
#   hand-written in pg_query_fingerprint.c (mirrors Postgres'
#   custom_query_jumble field attribute).
#
# - fingerprint_skip_fields ("Node.field", or just "field" to apply to all
#   nodes): the field is ignored, with a comment noting so in the generated code.
#
# - fingerprint_omit_fields ("Node.field"): the field is ignored without a
#   trace in the generated output. Used for fields that only exist after parse
#   analysis (and thus can never be set in the raw parse trees libpg_query
#   fingerprints), where a comment for every field would just be noise. These
#   come from %analysis_only_fields below, shared with outfuncs_skip_fields.
#
# - fingerprint_conds_wrap: opening C code wrapped around the dispatch case
#   body ("  }\n" is appended automatically), for context-dependent dispatch.
#
# - outfuncs_exclude_nodes: no output/input functions, dispatch cases or
#   Protobuf message are generated (the node either has hand-written support,
#   or is intentionally not supported).
#
# - outfuncs_skip_fields ("Node.field"): the field is left out of the
#   output/input functions and the Protobuf message. Since Protobuf field
#   numbers are assigned sequentially, adding or removing entries here changes
#   the numbering of all subsequent fields of the message (i.e. breaks wire
#   compatibility). Fields Postgres marks as read_write_ignore must have an
#   entry here (the generator errors out otherwise). Includes
#   %analysis_only_fields below, shared with fingerprint_omit_fields.
#
# - outfuncs_outname_overrides ("Node.field"): Protobuf field name to use
#   instead of the snake_case version of the C field name.
#
# - outfuncs_explicit_tag_nodes: nodes that need an explicit NodeSetTag in the
#   input functions, because they are a superset of another node.
#
# - plpgsql: output support for PL/pgSQL parse trees, whose structs (from
#   plpgsql.h, parsed via --hook-extra-input) are not nodes. See
#   LibpgQuery::NodeSupport::Plpgsql. Entries:
#
#   - header: plpgsql.h, relative to the Postgres source tree.
#   - root: the struct the output starts from; only structs reachable from it
#     are emitted.
#   - dispatch: polymorphic pointer types (a common prefix struct whose first
#     field tells the concrete struct), emitted as a protobuf oneof. The enum
#     value PREFIX_FOO maps to struct_prefix . lc("FOO") unless listed in
#     structs. The oneof tags are the enum values plus one.
#   - datum_types: structs that are variables (the datum dispatch and its
#     common prefix types). Pointer fields of these types are references into
#     PLpgSQL_function.datums and are emitted as the dno (field name suffixed
#     with _dno; -1 for NULL), not inlined.
#   - list_elem_types: element struct of each List* field, keyed by field
#     name ("Struct.field" to apply to one struct only).
#   - as_int_types: types emitted as plain int32 (enums the generator can't
#     parse).
#   - arrays ("Struct.field" => count field): counted pointer or int arrays,
#     emitted as a repeated field. The count field is consumed (not emitted).
#   - linked_lists ("Struct.field" => next field): singly linked lists,
#     emitted as a repeated field. The next field is consumed.
#   - custom_fields ("Struct.field"): hand-written output in the backends
#     (WRITE_PLPGSQL_CUSTOM_FIELD calls _out<Struct>_<field>), with the
#     protobuf type and name to use, and the other fields it consumes.
#   - extra_proto: hand-written protobuf messages the custom fields use.
#   - structs: for every reachable struct, the fields to emit (in this order,
#     which determines the protobuf field numbers) and the fields to skip
#     (runtime/executor state, back pointers, and the dispatch tag). Every
#     field of the struct must be in one of the two lists or consumed by an
#     entry above; the generator errors out otherwise, so a field added by a
#     Postgres upgrade has to be decided on here.

# Fields that are only set during parse analysis, and thus can never be set
# in the raw parse trees libpg_query fingerprints and outputs. They are
# omitted from the fingerprint functions (without a trace, since a comment
# for every one of them would just be noise) and skipped in the output
# functions and the Protobuf definition (to keep the field numbering, and
# thus wire compatibility, unchanged). One list, so the two can't drift.
my %analysis_only_fields = (
	# Postgres itself also doesn't output this (see its read_write_ignore
	# attribute)
	'Query.queryId' => 1,
	'Var.varnosyn' => 1,
	'Var.varattnosyn' => 1,
	'Aggref.aggtranstype' => 1,
	'Aggref.aggpresorted' => 1,
	'GroupingFunc.cols' => 1,
	'OpExpr.opfuncid' => 1,
	'ScalarArrayOpExpr.opfuncid' => 1,
	'ScalarArrayOpExpr.hashfuncid' => 1,
	'ScalarArrayOpExpr.negfuncid' => 1,
	# Added in Postgres 18.6
	'CreateStatsStmt.owner' => 1,
);

{
	fingerprint_exclude_nodes => [
		# Contains a union; contents are fingerprinted via the value nodes
		# (Integer/Float/Boolean/String/BitString) it falls through to in
		# the dispatch default branch, and intentionally ignored otherwise
		'A_Const',
	],

	fingerprint_skip_all_nodes => [
		'Alias',
		'ParamRef',
		'SetToDefault',
	],

	fingerprint_custom_body_nodes => [
		# Mirrors Postgres' query jumble for relation references after parse
		# analysis (see the comment on _fingerprintRangeVar)
		'RangeVar',
	],

	fingerprint_custom_fields => {
		# Column names in a SELECT target list don't change the query intent
		'ResTarget.name' => 1,
		# IN (...) and = ANY(...) are treated as equivalent
		'A_Expr.kind' => 1,
	},

	fingerprint_skip_fields => {
		# Applies to all nodes: source locations don't change the query
		'location' => 1,
		'arg_location' => 1,
		'conninfo_location' => 1,
		'payload_location' => 1,
		'list_start' => 1,
		'list_end' => 1,

		'A_Expr.rexpr_list_start' => 1,
		'A_Expr.rexpr_list_end' => 1,
		'PrepareStmt.name' => 1,
		'ExecuteStmt.name' => 1,
		'DeallocateStmt.name' => 1,
		'TransactionStmt.gid' => 1,
		'TransactionStmt.savepoint_name' => 1,
		'CreateFunctionStmt.options' => 1,
		'FunctionParameter.name' => 1,
		'DoStmt.args' => 1,
		'ListenStmt.conditionname' => 1,
		'UnlistenStmt.conditionname' => 1,
		'NotifyStmt.conditionname' => 1,
		'NotifyStmt.payload' => 1,
		'DeclareCursorStmt.portalname' => 1,
		'FetchStmt.portalname' => 1,
		'ClosePortalStmt.portalname' => 1,
		'RawStmt.stmt_len' => 1,
		'RawStmt.stmt_location' => 1,
		'JsonTablePath.value' => 1,
		'JsonTablePathSpec.name_location' => 1,
		'JsonTablePathSpec.location' => 1,
		# TODO: Should we be smarter about using this flag ourselves?
		'VariableSetStmt.jumble_args' => 1,
		'CreateRoleStmt.role' => 1,
		'RenameStmt.newname' => 1,
		'RenameStmt.subname' => 1,
		'RoleSpec.rolename' => 1,
	},

	fingerprint_omit_fields => {
		%analysis_only_fields,
	},

	fingerprint_conds_wrap => {
		# A TypeCast around a constant or parameter reference is ignored
		# (the constant/parameter itself is what matters)
		'TypeCast' =>
		  "  if (!IsA(castNode(TypeCast, (void*) obj)->arg, A_Const) && !IsA(castNode(TypeCast, (void*) obj)->arg, ParamRef))\n  {\n",
	},

	outfuncs_exclude_nodes => [
		# Hand-written support (see the value node handling in
		# pg_query_outfuncs_*.c / pg_query_readfuncs_protobuf.c)
		'A_Const',
		# Only needed in post-parse analysis (and it introduces Datums, which
		# we can't output)
		'Const',
	],

	outfuncs_skip_fields => {
		%analysis_only_fields,
		# Contains a Const, which we can't output
		'JsonTablePath.value' => 1,
	},

	outfuncs_outname_overrides => {
		# Avoids a name clash in the generated Protobuf code
		'CreateForeignTableStmt.base' => 'base_stmt',
	},

	outfuncs_explicit_tag_nodes => [
		# Superset of CreateStmt, so makeNode() alone would set the wrong tag
		'CreateForeignTableStmt',
	],

	plpgsql => {
		header => 'src/pl/plpgsql/src/plpgsql.h',
		root => 'PLpgSQL_function',

		dispatch => {
			PLpgSQL_stmt => {
				tag_field => 'cmd_type',
				enum => 'PLpgSQL_stmt_type',
				value_prefix => 'PLPGSQL_STMT_',
				struct_prefix => 'PLpgSQL_stmt_',
			},
			PLpgSQL_datum => {
				tag_field => 'dtype',
				enum => 'PLpgSQL_datum_type',
				value_prefix => 'PLPGSQL_DTYPE_',
				struct_prefix => 'PLpgSQL_',
				structs => {
					# A promise is a PLpgSQL_var that computes its value on
					# first read (trigger variables like TG_NAME)
					PLPGSQL_DTYPE_PROMISE => 'PLpgSQL_var',
				},
			},
		},

		datum_types => [
			qw(PLpgSQL_datum PLpgSQL_variable PLpgSQL_var PLpgSQL_row PLpgSQL_rec PLpgSQL_recfield)
		],

		list_elem_types => {
			# Lists of statements
			body => 'PLpgSQL_stmt',
			then_body => 'PLpgSQL_stmt',
			else_body => 'PLpgSQL_stmt',
			else_stmts => 'PLpgSQL_stmt',
			stmts => 'PLpgSQL_stmt',
			action => 'PLpgSQL_stmt',
			# USING expressions / old-style RAISE parameters
			params => 'PLpgSQL_expr',
			options => 'PLpgSQL_raise_option',
			exc_list => 'PLpgSQL_exception',
			elsif_list => 'PLpgSQL_if_elsif',
			case_when_list => 'PLpgSQL_case_when',
			diag_items => 'PLpgSQL_diag_item',
		},

		as_int_types => [
			# Anonymous "typedef enum { ... } RawParseMode" in parser/parser.h,
			# which the generator can't parse. The int is also what consumers
			# need: it is the parse mode to pass to pg_query_parse_opts() for
			# the query (PgQueryParseMode has the same values).
			'RawParseMode',
		],

		arrays => {
			'PLpgSQL_function.datums' => 'ndatums',
			# Fixed-size array of which the first fn_nargs entries are valid
			# (IN/INOUT/VARIADIC parameters; OUT-only parameters are reached
			# via out_param_varno)
			'PLpgSQL_function.fn_argvarnos' => 'fn_nargs',
			'PLpgSQL_stmt_block.initvarnos' => 'n_initvars',
		},

		linked_lists => {
			'PLpgSQL_exception.conditions' => 'next',
		},

		custom_fields => {
			# Parallel arrays fieldnames[nfields] / varnos[nfields], zipped
			# into one repeated message
			'PLpgSQL_row.fieldnames' => {
				outname => 'fields',
				proto_type => 'repeated PLpgSQL_row_field',
				c_type => 'PLpgSQL_row_field[]',
				consumes => [ 'nfields', 'varnos' ],
			},
		},

		extra_proto => <<'EOT',
message PLpgSQL_row_field
{
  string name = 1 [json_name="name"];
  int32 varno = 2 [json_name="varno"];
}
EOT

		# Emit everything the compiler sets, including values that only
		# reflect the mock catalog libpg_query compiles against (type OIDs,
		# fn_signature is always "0", ...). Skip only runtime/executor state,
		# back pointers, the dispatch tag (which the oneof wrapper conveys,
		# like the NodeTag of parse nodes), and the pass-by-value flags
		# (typbyval, fn_retbyval): those come from FLOAT8PASSBYVAL, which
		# depends on the platform (false on Windows, where libpg_query is
		# built with a 32-bit SIZEOF_VOID_P), so the output would differ
		# between platforms for every 8-byte type.
		structs => {
			PLpgSQL_function => {
				emit => [
					qw(fn_signature fn_oid fn_is_trigger fn_input_collation fn_rettype fn_rettyplen fn_retistuple fn_retisdomain fn_retset fn_readonly fn_prokind fn_argvarnos out_param_varno found_varno new_varno old_varno resolve_option print_strict_params extra_warnings extra_errors datums action nstatements requires_procedure_resowner has_exception_block)
				],
				skip => [qw(cfunc fn_cxt copiable_size cur_estate fn_retbyval)],
			},
			PLpgSQL_stmt_block => {
				emit => [qw(lineno stmtid label body initvarnos exceptions)],
				skip => [qw(cmd_type)],
			},
			PLpgSQL_exception_block => {
				emit => [qw(sqlstate_varno sqlerrm_varno exc_list)],
			},
			PLpgSQL_exception => {
				emit => [qw(lineno conditions action)],
			},
			PLpgSQL_condition => {
				emit => [qw(sqlerrstate condname)],
			},
			PLpgSQL_stmt_assign => {
				emit => [qw(lineno stmtid varno expr)],
				skip => [qw(cmd_type)],
			},
			PLpgSQL_stmt_if => {
				emit => [qw(lineno stmtid cond then_body elsif_list else_body)],
				skip => [qw(cmd_type)],
			},
			PLpgSQL_if_elsif => {
				emit => [qw(lineno cond stmts)],
			},
			PLpgSQL_stmt_case => {
				emit => [qw(lineno stmtid t_expr t_varno case_when_list have_else else_stmts)],
				skip => [qw(cmd_type)],
			},
			PLpgSQL_case_when => {
				emit => [qw(lineno expr stmts)],
			},
			PLpgSQL_stmt_loop => {
				emit => [qw(lineno stmtid label body)],
				skip => [qw(cmd_type)],
			},
			PLpgSQL_stmt_while => {
				emit => [qw(lineno stmtid label cond body)],
				skip => [qw(cmd_type)],
			},
			PLpgSQL_stmt_fori => {
				emit => [qw(lineno stmtid label var lower upper step reverse body)],
				skip => [qw(cmd_type)],
			},
			PLpgSQL_stmt_fors => {
				emit => [qw(lineno stmtid label var body query)],
				skip => [qw(cmd_type)],
			},
			PLpgSQL_stmt_forc => {
				emit => [qw(lineno stmtid label var body curvar argquery)],
				skip => [qw(cmd_type)],
			},
			PLpgSQL_stmt_dynfors => {
				emit => [qw(lineno stmtid label var body query params)],
				skip => [qw(cmd_type)],
			},
			PLpgSQL_stmt_foreach_a => {
				emit => [qw(lineno stmtid label varno slice expr body)],
				skip => [qw(cmd_type)],
			},
			PLpgSQL_stmt_exit => {
				emit => [qw(lineno stmtid is_exit label cond)],
				skip => [qw(cmd_type)],
			},
			PLpgSQL_stmt_return => {
				emit => [qw(lineno stmtid expr retvarno)],
				skip => [qw(cmd_type)],
			},
			PLpgSQL_stmt_return_next => {
				emit => [qw(lineno stmtid expr retvarno)],
				skip => [qw(cmd_type)],
			},
			PLpgSQL_stmt_return_query => {
				emit => [qw(lineno stmtid query dynquery params)],
				skip => [qw(cmd_type)],
			},
			PLpgSQL_stmt_raise => {
				emit => [qw(lineno stmtid elog_level condname message params options)],
				skip => [qw(cmd_type)],
			},
			PLpgSQL_raise_option => {
				emit => [qw(opt_type expr)],
			},
			PLpgSQL_stmt_assert => {
				emit => [qw(lineno stmtid cond message)],
				skip => [qw(cmd_type)],
			},
			PLpgSQL_stmt_execsql => {
				emit => [qw(lineno stmtid sqlstmt into strict target)],
				# mod_stmt is only determined on first execution
				skip => [qw(cmd_type mod_stmt mod_stmt_set)],
			},
			PLpgSQL_stmt_dynexecute => {
				emit => [qw(lineno stmtid query into strict target params)],
				skip => [qw(cmd_type)],
			},
			PLpgSQL_stmt_getdiag => {
				emit => [qw(lineno stmtid is_stacked diag_items)],
				skip => [qw(cmd_type)],
			},
			PLpgSQL_diag_item => {
				emit => [qw(kind target)],
			},
			PLpgSQL_stmt_open => {
				emit => [qw(lineno stmtid curvar cursor_options argquery query dynquery params)],
				skip => [qw(cmd_type)],
			},
			PLpgSQL_stmt_fetch => {
				emit => [qw(lineno stmtid target curvar direction how_many expr is_move returns_multiple_rows)],
				skip => [qw(cmd_type)],
			},
			PLpgSQL_stmt_close => {
				emit => [qw(lineno stmtid curvar)],
				skip => [qw(cmd_type)],
			},
			PLpgSQL_stmt_perform => {
				emit => [qw(lineno stmtid expr)],
				skip => [qw(cmd_type)],
			},
			PLpgSQL_stmt_call => {
				emit => [qw(lineno stmtid expr is_call target)],
				skip => [qw(cmd_type)],
			},
			PLpgSQL_stmt_commit => {
				emit => [qw(lineno stmtid chain)],
				skip => [qw(cmd_type)],
			},
			PLpgSQL_stmt_rollback => {
				emit => [qw(lineno stmtid chain)],
				skip => [qw(cmd_type)],
			},
			PLpgSQL_expr => {
				emit => [qw(query parseMode target_param target_is_local)],
				# Everything from plan on is only set when the query is
				# first planned/executed; func and ns are back pointers
				skip => [
					qw(func ns plan paramnos expr_simple_expr expr_simple_type expr_simple_typmod expr_simple_mutable expr_rwopt expr_rw_param expr_simple_plansource expr_simple_plan expr_simple_plan_lxid expr_simple_state expr_simple_in_use expr_simple_lxid)
				],
			},
			PLpgSQL_var => {
				emit => [
					qw(dno refname lineno isconst notnull default_val datatype cursor_explicit_expr cursor_explicit_argrow cursor_options promise)
				],
				skip => [qw(dtype value isnull freeval)],
			},
			PLpgSQL_row => {
				emit => [qw(dno refname lineno isconst notnull default_val fieldnames)],
				skip => [qw(dtype rowtupdesc)],
			},
			PLpgSQL_rec => {
				emit => [qw(dno refname lineno isconst notnull default_val datatype rectypeid firstfield)],
				skip => [qw(dtype erh)],
			},
			PLpgSQL_recfield => {
				emit => [qw(dno fieldname recparentno nextfield)],
				skip => [qw(dtype rectupledescid finfo)],
			},
			PLpgSQL_type => {
				emit => [
					qw(typname typoid ttype typlen typtype collation typisarray atttypmod origtypname)
				],
				skip => [qw(tcache tupdesc_id typbyval)],
			},
		},
	},
}
