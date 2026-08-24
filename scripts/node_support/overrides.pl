# libpg_query-specific overrides for the node support code generation done via
# the patched gen_node_support.pl (see patches/13_gen_node_support_hook.patch
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
#   fingerprints), where a comment for every field would just be noise.
#
# - fingerprint_conds_wrap: opening C code wrapped around the dispatch case
#   body ("  }\n" is appended automatically), for context-dependent dispatch.
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
		'list_start' => 1,
		'list_end' => 1,

		'A_Expr.rexpr_list_start' => 1,
		'A_Expr.rexpr_list_end' => 1,
		'PrepareStmt.name' => 1,
		'ExecuteStmt.name' => 1,
		'DeallocateStmt.name' => 1,
		'TransactionStmt.options' => 1,
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
	},

	fingerprint_omit_fields => {
		# Fields that are only set during parse analysis, and thus can never
		# be set in the raw parse trees that libpg_query fingerprints. These
		# are also skipped in the protobuf/outfuncs generation (see
		# TYPE_OVERRIDES in scripts/generate_protobuf_and_funcs.rb) to keep
		# protobuf field numbering unchanged.
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
	},

	fingerprint_conds_wrap => {
		# A TypeCast around a constant or parameter reference is ignored
		# (the constant/parameter itself is what matters)
		'TypeCast' =>
		  "  if (!IsA(castNode(TypeCast, (void*) obj)->arg, A_Const) && !IsA(castNode(TypeCast, (void*) obj)->arg, ParamRef))\n  {\n",
	},
}
