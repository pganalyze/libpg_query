#include "pg_query.h"
#include "pg_query_internal.h"
#include "pg_query_readfuncs.h"

#include "lib/stringinfo.h"
#include "nodes/nodes.h"
#include "nodes/parsenodes.h"
#include "nodes/pg_list.h"
#include "utils/builtins.h"
#include "catalog/pg_class.h"
#include "utils/datetime.h"
#include "utils/timestamp.h"

typedef enum DeparseNodeContext {
	DEPARSE_NODE_CONTEXT_NONE,
	// Parent node context
	DEPARSE_NODE_CONTEXT_SELECT,
	DEPARSE_NODE_CONTEXT_INSERT_TARGET_LIST,
	DEPARSE_NODE_CONTEXT_INSERT_ON_CONFLICT,
	DEPARSE_NODE_CONTEXT_UPDATE,
	DEPARSE_NODE_CONTEXT_RETURNING,
	DEPARSE_NODE_CONTEXT_A_EXPR,
	// Identifier vs constant context
	DEPARSE_NODE_CONTEXT_IDENTIFIER,
	DEPARSE_NODE_CONTEXT_CONSTANT
} DeparseNodeContext;

static void
removeTrailingSpace(StringInfo str)
{
	if (str->len >= 1 && str->data[str->len - 1] == ' ') {
		str->len -= 1;
		str->data[str->len] = '\0';
	}
}

/*
 * Append a SQL string literal representing "val" to buf.
 *
 * Copied here from postgres_fdw/deparse.c to avoid adding
 * many additional dependencies.
 */
static void
deparseStringLiteral(StringInfo buf, const char *val)
{
	const char *valptr;

	/*
	 * Rather than making assumptions about the remote server's value of
	 * standard_conforming_strings, always use E'foo' syntax if there are any
	 * backslashes.  This will fail on remote servers before 8.1, but those
	 * are long out of support.
	 */
	if (strchr(val, '\\') != NULL)
		appendStringInfoChar(buf, ESCAPE_STRING_SYNTAX);
	appendStringInfoChar(buf, '\'');
	for (valptr = val; *valptr; valptr++)
	{
		char		ch = *valptr;

		if (SQL_STR_DOUBLE(ch, true))
			appendStringInfoChar(buf, ch);
		appendStringInfoChar(buf, ch);
	}
	appendStringInfoChar(buf, '\'');
}

static void deparseSelectStmt(StringInfo str, SelectStmt *stmt);
static void deparseIntoClause(StringInfo str, IntoClause *into_clause);
static void deparseRangeVar(StringInfo str, RangeVar *range_var);
static void deparseResTarget(StringInfo str, ResTarget *res_target, DeparseNodeContext context);
static void deparseRawStmt(StringInfo str, RawStmt *raw_stmt);
static void deparseAlias(StringInfo str, Alias *alias);
static void deparseWindowDef(StringInfo str, WindowDef* window_def);
static void deparseColumnRef(StringInfo str, ColumnRef* column_ref);
static void deparseSubLink(StringInfo str, SubLink* sub_link);
static void deparseAExpr(StringInfo str, A_Expr* a_expr, DeparseNodeContext context);
static void deparseBoolExpr(StringInfo str, BoolExpr *bool_expr);
static void deparseAStar(StringInfo str, A_Star* a_star);
static void deparseCollateClause(StringInfo str, CollateClause* collate_clause);
static void deparseSortBy(StringInfo str, SortBy* sort_by);
static void deparseParamRef(StringInfo str, ParamRef* param_ref);
static void deparseSQLValueFunction(StringInfo str, SQLValueFunction* sql_value_function);
static void deparseWithClause(StringInfo str, WithClause *with_clause);
static void deparseJoinExpr(StringInfo str, JoinExpr *join_expr);
static void deparseCommonTableExpr(StringInfo str, CommonTableExpr *cte);
static void deparseRangeSubselect(StringInfo str, RangeSubselect *range_subselect);
static void deparseRangeFunction(StringInfo str, RangeFunction *range_func);
static void deparseAArrayExpr(StringInfo str, A_ArrayExpr * array_expr);
static void deparseRowExpr(StringInfo str, RowExpr *row_expr);
static void deparseTypeCast(StringInfo str, TypeCast *type_cast);
static void deparseTypeName(StringInfo str, TypeName *type_name);
static void deparseNullTest(StringInfo str, NullTest *null_test);
static void deparseCaseExpr(StringInfo str, CaseExpr *case_expr);
static void deparseCaseWhen(StringInfo str, CaseWhen *case_when);
static void deparseAIndirection(StringInfo str, A_Indirection *a_indirection);
static void deparseAIndices(StringInfo str, A_Indices *a_indices);
static void deparseCoalesceExpr(StringInfo str, CoalesceExpr *coalesce_expr);
static void deparseBooleanTest(StringInfo str, BooleanTest *boolean_test);
static void deparseColumnDef(StringInfo str, ColumnDef *column_def);
static void deparseInsertStmt(StringInfo str, InsertStmt *insert_stmt);
static void deparseOnConflictClause(StringInfo str, OnConflictClause *on_conflict_clause);
static void deparseIndexElem(StringInfo str, IndexElem* index_elem);
static void deparseUpdateStmt(StringInfo str, UpdateStmt *update_stmt);
static void deparseDeleteStmt(StringInfo str, DeleteStmt *delete_stmt);
static void deparseLockingClause(StringInfo str, LockingClause *locking_clause);
static void deparseSetToDefault(StringInfo str, SetToDefault *set_to_default);
static void deparseCreateCastStmt(StringInfo str, CreateCastStmt *create_cast_stmt);
static void deparseCreateDomainStmt(StringInfo str, CreateDomainStmt *create_domain_stmt);
static void deparseFunctionParameter(StringInfo str, FunctionParameter *function_parameter);
static void deparseRoleSpec(StringInfo str, RoleSpec *role_spec);
static void deparseCreateStmt(StringInfo str, CreateStmt *create_stmt);
static void deparseViewStmt(StringInfo str, ViewStmt *view_stmt);

static void deparseValue(StringInfo str, Value *value, DeparseNodeContext context);
static void deparseNode(StringInfo str, Node *node, DeparseNodeContext context);

static void deparseSelectStmt(StringInfo str, SelectStmt *stmt)
{
	const ListCell *lc = NULL;
	const ListCell *lc2 = NULL;

	if (stmt->withClause)
	{
		deparseWithClause(str, stmt->withClause);
		appendStringInfoChar(str, ' ');
	}

	switch (stmt->op) {
		case SETOP_NONE:
			if (list_length(stmt->valuesLists) > 0)
			{
				const ListCell *lc;
				appendStringInfoString(str, "VALUES ");

				foreach(lc, stmt->valuesLists)
				{
					appendStringInfoChar(str, '(');
					foreach(lc2, lfirst(lc))
					{
						deparseNode(str, lfirst(lc2), DEPARSE_NODE_CONTEXT_SELECT);
						if (lnext(lfirst(lc), lc2))
							appendStringInfoString(str, ", ");
					}
					appendStringInfoChar(str, ')');
					if (lnext(stmt->valuesLists, lc))
						appendStringInfoString(str, ", ");
				}
				appendStringInfoChar(str, ' ');
				break;
			}

			if (list_length(stmt->fromClause) > 0 || list_length(stmt->targetList) > 0)
			{
				appendStringInfoString(str, "SELECT ");
			}

			if (list_length(stmt->targetList) > 0)
			{
				if (stmt->distinctClause != NULL)
				{
					appendStringInfoString(str, "DISTINCT ");

					if (list_length(stmt->distinctClause) > 0 && linitial(stmt->distinctClause) != NULL)
					{
						appendStringInfoString(str, "ON (");
						foreach(lc, stmt->distinctClause)
						{
							deparseNode(str, lfirst(lc), DEPARSE_NODE_CONTEXT_SELECT);
							if (lnext(stmt->distinctClause, lc))
								appendStringInfoString(str, ", ");
						}
						appendStringInfoString(str, ") ");
					}
				}

				foreach(lc, stmt->targetList)
				{
					deparseNode(str, lfirst(lc), DEPARSE_NODE_CONTEXT_SELECT);
					if (lnext(stmt->targetList, lc))
						appendStringInfoString(str, ", ");
				}
				appendStringInfoChar(str, ' ');

				if (stmt->intoClause != NULL)
				{
					appendStringInfoString(str, "INTO ");
					deparseIntoClause(str, stmt->intoClause);
					appendStringInfoChar(str, ' ');
				}
			}

			if (list_length(stmt->fromClause) > 0)
			{
				appendStringInfoString(str, "FROM ");

				foreach(lc, stmt->fromClause)
				{
					deparseNode(str, lfirst(lc), DEPARSE_NODE_CONTEXT_SELECT);
					if (lnext(stmt->fromClause, lc))
						appendStringInfoString(str, ", ");
				}
				appendStringInfoChar(str, ' ');
			}

			if (stmt->whereClause != NULL)
			{
				appendStringInfoString(str, "WHERE ");
				deparseNode(str, stmt->whereClause, DEPARSE_NODE_CONTEXT_SELECT);
				appendStringInfoChar(str, ' ');
			}

			if (list_length(stmt->groupClause) > 0)
			{
				appendStringInfoString(str, "GROUP BY ");

				foreach(lc, stmt->groupClause)
				{
					deparseNode(str, lfirst(lc), DEPARSE_NODE_CONTEXT_SELECT);
					if (lnext(stmt->groupClause, lc))
						appendStringInfoString(str, ", ");
				}
				appendStringInfoChar(str, ' ');
			}

			if (stmt->havingClause != NULL)
			{
				appendStringInfoString(str, "HAVING ");
				deparseNode(str, stmt->havingClause, DEPARSE_NODE_CONTEXT_SELECT);
				appendStringInfoChar(str, ' ');
			}
			break;
		case SETOP_UNION:
			if (list_length(stmt->larg->sortClause) > 0)
				appendStringInfoChar(str, '(');
			deparseSelectStmt(str, stmt->larg);
			if (list_length(stmt->larg->sortClause) > 0)
				appendStringInfoChar(str, ')');
			appendStringInfoString(str, " UNION ");
			if (stmt->all)
				appendStringInfoString(str, "ALL ");
			if (list_length(stmt->rarg->sortClause) > 0)
				appendStringInfoChar(str, '(');
			deparseSelectStmt(str, stmt->rarg);
			if (list_length(stmt->rarg->sortClause) > 0)
				appendStringInfoChar(str, ')');
			appendStringInfoChar(str, ' ');
			break;
		case SETOP_INTERSECT:
			deparseSelectStmt(str, stmt->larg);
			appendStringInfoString(str, " INTERSECT ");
			deparseSelectStmt(str, stmt->rarg);
			break;
		case SETOP_EXCEPT:
			deparseSelectStmt(str, stmt->larg);
			appendStringInfoString(str, " EXCEPT ");
			deparseSelectStmt(str, stmt->rarg);
			break;
	}

	if (list_length(stmt->sortClause) > 0)
	{
		appendStringInfoString(str, "ORDER BY ");

		foreach(lc, stmt->sortClause)
		{
			deparseNode(str, lfirst(lc), DEPARSE_NODE_CONTEXT_SELECT);
			if (lnext(stmt->sortClause, lc))
				appendStringInfoString(str, ", ");
		}
		appendStringInfoChar(str, ' ');
	}

	if (stmt->limitCount != NULL)
	{
		appendStringInfoString(str, "LIMIT ");
		deparseNode(str, stmt->limitCount, DEPARSE_NODE_CONTEXT_SELECT);
		appendStringInfoChar(str, ' ');
	}

	if (stmt->limitOffset != NULL)
	{
		appendStringInfoString(str, "OFFSET ");
		deparseNode(str, stmt->limitOffset, DEPARSE_NODE_CONTEXT_SELECT);
		appendStringInfoChar(str, ' ');
	}

	if (list_length(stmt->lockingClause) > 0)
	{
		foreach(lc, stmt->lockingClause)
		{
			deparseNode(str, lfirst(lc), DEPARSE_NODE_CONTEXT_SELECT);
			if (lnext(stmt->lockingClause, lc))
				appendStringInfoString(str, " ");
		}
		appendStringInfoChar(str, ' ');
	}

	removeTrailingSpace(str);
}

static void deparseIntoClause(StringInfo str, IntoClause *into_clause)
{
	deparseRangeVar(str, into_clause->rel); /* target relation name */

	// TODO: Review these additional fields
	//List	   *colNames;		/* column names to assign, or NIL */
	//char	   *accessMethod;	/* table access method */
	//List	   *options;		/* options from WITH clause */
	//OnCommitAction onCommit;	/* what do we do at COMMIT? */
	//char	   *tableSpaceName; /* table space to use, or NULL */
	//Node	   *viewQuery;		/* materialized view's SELECT query */
	//bool		skipData;		/* true for WITH NO DATA */
}

static void deparseRangeVar(StringInfo str, RangeVar *range_var)
{
	if (!range_var->inh)
	{
		appendStringInfoString(str, "ONLY ");
	}

	if (range_var->schemaname != NULL)
	{
		appendStringInfoString(str, quote_identifier(range_var->schemaname));
		appendStringInfoChar(str, '.');
	}

	Assert(range_var->relname != NULL);
	appendStringInfoString(str, quote_identifier(range_var->relname));
	appendStringInfoChar(str, ' ');

	if (range_var->alias != NULL)
	{
		deparseAlias(str, range_var->alias);
		appendStringInfoChar(str, ' ');
	}

	removeTrailingSpace(str);
}

static void deparseResTarget(StringInfo str, ResTarget *res_target, DeparseNodeContext context)
{
	/*
	 * In a SELECT target list, 'name' is the column label from an
	 * 'AS ColumnLabel' clause, or NULL if there was none, and 'val' is the
	 * value expression itself.  The 'indirection' field is not used.
	 */
	if (context == DEPARSE_NODE_CONTEXT_SELECT)
	{
		Assert(res_target->val != NULL);
		deparseNode(str, res_target->val, context);
		if (res_target->name != NULL) {
			appendStringInfoString(str, " AS ");
			appendStringInfoString(str, quote_identifier(res_target->name));
		}
	}
	/*
	 * INSERT uses ResTarget in its target-column-names list.  Here, 'name' is
	 * the name of the destination column, 'indirection' stores any subscripts
	 * attached to the destination, and 'val' is not used.
	 */
	else if (context == DEPARSE_NODE_CONTEXT_INSERT_TARGET_LIST)
	{
		Assert(res_target->name != NULL);
		appendStringInfoString(str, quote_identifier(res_target->name));
		// TODO: Handle indirection
	}
	/*
	 * In an UPDATE target list, 'name' is the name of the destination column,
	 * 'indirection' stores any subscripts attached to the destination, and
	 * 'val' is the expression to assign.
	 */
	else if (context == DEPARSE_NODE_CONTEXT_UPDATE || context == DEPARSE_NODE_CONTEXT_INSERT_ON_CONFLICT)
	{
		Assert(res_target->name != NULL);
		Assert(res_target->val != NULL);
		appendStringInfoString(str, quote_identifier(res_target->name));
		appendStringInfoString(str, " = ");
		deparseNode(str, res_target->val, context);
		// TODO: Handle indirection
	}
	else if (context == DEPARSE_NODE_CONTEXT_RETURNING)
	{
		Assert(res_target->val != NULL);
		deparseNode(str, res_target->val, context);
		if (res_target->name != NULL) {
			appendStringInfoString(str, " AS ");
			appendStringInfoString(str, quote_identifier(res_target->name));
		}
	}
	else
	{
		elog(ERROR, "Can't deparse ResTarget in context %d", context);
	}
}

static void deparseRawStmt(StringInfo str, RawStmt *raw_stmt)
{
	deparseNode(str, raw_stmt->stmt, DEPARSE_NODE_CONTEXT_NONE);
}

static void deparseAlias(StringInfo str, Alias *alias)
{
	appendStringInfoString(str, quote_identifier(alias->aliasname));

	if (list_length(alias->colnames) > 0)
	{
		const ListCell *lc = NULL;
		appendStringInfoChar(str, '(');
		foreach(lc, alias->colnames)
		{
			deparseNode(str, lfirst(lc), DEPARSE_NODE_CONTEXT_NONE);
			if (lnext(alias->colnames, lc))
				appendStringInfoString(str, ", ");
		}
		appendStringInfoChar(str, ')');
	}
}

static void deparseAConst(StringInfo str, A_Const *a_const)
{
	deparseValue(str, &a_const->val, DEPARSE_NODE_CONTEXT_CONSTANT);
}

static void deparseFuncCall(StringInfo str, FuncCall *func_call)
{
	const ListCell *lc = NULL;
	const ListCell *lc2 = NULL;

	Assert(list_length(func_call->funcname) > 0);

	if (list_length(func_call->funcname) == 2 &&
		strcmp(strVal(linitial(func_call->funcname)), "pg_catalog") == 0 &&
		strcmp(strVal(lsecond(func_call->funcname)), "overlay") == 0 &&
		list_length(func_call->args) == 4)
	{
		/*
		 * Note that this is a bit odd, but "OVERLAY" is a keyword on its own merit, and only accepts the
         * keyword parameter style when its called as a keyword, not as a regular function (i.e. pg_catalog.overlay)
		 */
		appendStringInfoString(str, "OVERLAY(");
		deparseNode(str, linitial(func_call->args), DEPARSE_NODE_CONTEXT_NONE);
		appendStringInfoString(str, " PLACING ");
		deparseNode(str, lsecond(func_call->args), DEPARSE_NODE_CONTEXT_NONE);
		appendStringInfoString(str, " FROM ");
		deparseNode(str, lthird(func_call->args), DEPARSE_NODE_CONTEXT_NONE);
		appendStringInfoString(str, " FOR ");
		deparseNode(str, lfourth(func_call->args), DEPARSE_NODE_CONTEXT_NONE);
		appendStringInfoChar(str, ')');
		return;
	}

	foreach(lc, func_call->funcname)
	{
		deparseNode(str, lfirst(lc), DEPARSE_NODE_CONTEXT_IDENTIFIER);
		if (lnext(func_call->funcname, lc))
			appendStringInfoChar(str, '.');
	}
	appendStringInfoChar(str, '(');

	if (func_call->agg_distinct)
		appendStringInfoString(str, "DISTINCT ");

	if (func_call->agg_star)
	{
		appendStringInfoChar(str, '*');
	}
	else if (list_length(func_call->args) > 0)
	{
		foreach(lc2, func_call->args)
		{
			deparseNode(str, lfirst(lc2), DEPARSE_NODE_CONTEXT_NONE);
			if (lnext(func_call->args, lc2))
				appendStringInfoString(str, ", ");
		}
	}

	appendStringInfoString(str, ") ");

	if (func_call->agg_filter)
	{
		appendStringInfoString(str, "FILTER (WHERE ");
		deparseNode(str, func_call->agg_filter, DEPARSE_NODE_CONTEXT_NONE);
		appendStringInfoString(str, ") ");
	}

	if (func_call->over)
	{
		appendStringInfoString(str, "OVER ");
		deparseWindowDef(str, func_call->over);
	}

	removeTrailingSpace(str);
}

static void deparseWindowDef(StringInfo str, WindowDef* window_def)
{
	ListCell *lc;

	if (window_def->name)
	{
		appendStringInfoString(str, window_def->name);
		return;
	}

	appendStringInfoChar(str, '(');

	if (list_length(window_def->partitionClause) > 0)
	{
		appendStringInfoString(str, "PARTITION BY ");
		foreach(lc, window_def->partitionClause)
		{
			deparseNode(str, lfirst(lc), DEPARSE_NODE_CONTEXT_NONE);
			if (lnext(window_def->partitionClause, lc))
				appendStringInfoString(str, ", ");
		}
		appendStringInfoChar(str, ' ');
	}

	if (list_length(window_def->orderClause) > 0)
	{
		appendStringInfoString(str, "ORDER BY ");
		foreach(lc, window_def->orderClause)
		{
			deparseNode(str, lfirst(lc), DEPARSE_NODE_CONTEXT_NONE);
			if (lnext(window_def->orderClause, lc))
				appendStringInfoString(str, ", ");
		}
		appendStringInfoChar(str, ' ');
	}

	removeTrailingSpace(str);
	appendStringInfoChar(str, ')');

	// TODO: refname
	// TODO: frameOptions
	// TODO: startOffset
	// TODO: endOffset
}

static void deparseColumnRef(StringInfo str, ColumnRef* column_ref)
{
	ListCell *lc;
	foreach(lc, column_ref->fields) {
		deparseNode(str, lfirst(lc), DEPARSE_NODE_CONTEXT_IDENTIFIER);
		if (lnext(column_ref->fields, lc))
			appendStringInfoString(str, ".");
	}
}

static void deparseSubLink(StringInfo str, SubLink* sub_link)
{
	switch (sub_link->subLinkType) {
		case EXISTS_SUBLINK:
			appendStringInfoString(str, "EXISTS (");
			deparseNode(str, sub_link->subselect, DEPARSE_NODE_CONTEXT_NONE);
			appendStringInfoChar(str, ')');
			return;
		case ALL_SUBLINK:
			Assert(list_length(sub_link->operName) == 1);
			Assert(IsA(linitial(sub_link->operName), String));
			deparseNode(str, sub_link->testexpr, DEPARSE_NODE_CONTEXT_NONE);
			appendStringInfoChar(str, ' ');
			appendStringInfoString(str, strVal(linitial(sub_link->operName)));
			appendStringInfoString(str, " ALL (");
			deparseNode(str, sub_link->subselect, DEPARSE_NODE_CONTEXT_NONE);
			appendStringInfoChar(str, ')');
			return;
		case ANY_SUBLINK:
			deparseNode(str, sub_link->testexpr, DEPARSE_NODE_CONTEXT_NONE);
			appendStringInfoString(str, " IN (");
			deparseNode(str, sub_link->subselect, DEPARSE_NODE_CONTEXT_NONE);
			appendStringInfoChar(str, ')');
			return;
		case ROWCOMPARE_SUBLINK:
			// FIXME
	        // format('(%s)', deparse_item(node['subselect']))
			Assert(false);
			return;
		case EXPR_SUBLINK:
			appendStringInfoString(str, "(");
			deparseNode(str, sub_link->subselect, DEPARSE_NODE_CONTEXT_NONE);
			appendStringInfoChar(str, ')');
			return;
		case MULTIEXPR_SUBLINK:
			// FIXME
	        // format('(%s)', deparse_item(node['subselect']))
			Assert(false);
			return;
		case ARRAY_SUBLINK:
			appendStringInfoString(str, "ARRAY(");
			deparseNode(str, sub_link->subselect, DEPARSE_NODE_CONTEXT_NONE);
			appendStringInfoChar(str, ')');
			return;
		case CTE_SUBLINK: /* for SubPlans only */
			// FIXME
	        // format('(%s)', deparse_item(node['subselect']))
			Assert(false);
			return;
	}
}

static void deparseAExpr(StringInfo str, A_Expr* a_expr, DeparseNodeContext context)
{
	ListCell *lc;
	char *name;

	switch (a_expr->kind) {
		case AEXPR_OP: /* normal operator */
			// TODO: Handle schema-qualified operators
			Assert(list_length(a_expr->name) == 1);
			Assert(IsA(linitial(a_expr->name), String));

			bool need_parens = context == DEPARSE_NODE_CONTEXT_A_EXPR;

			if (need_parens)
				appendStringInfoChar(str, '(');

			deparseNode(str, a_expr->lexpr, DEPARSE_NODE_CONTEXT_A_EXPR);
			appendStringInfoChar(str, ' ');
			appendStringInfoString(str, strVal(linitial(a_expr->name)));
			appendStringInfoChar(str, ' ');
			deparseNode(str, a_expr->rexpr, DEPARSE_NODE_CONTEXT_A_EXPR);

			if (need_parens)
				appendStringInfoChar(str, ')');

			return;
		case AEXPR_OP_ANY: /* scalar op ANY (array) */
			// TODO: Handle schema-qualified operators
			Assert(list_length(a_expr->name) == 1);
			Assert(IsA(linitial(a_expr->name), String));
			deparseNode(str, a_expr->lexpr, DEPARSE_NODE_CONTEXT_NONE);
			appendStringInfoChar(str, ' ');
			appendStringInfoString(str, strVal(linitial(a_expr->name)));
			appendStringInfoString(str, " ANY(");
			deparseNode(str, a_expr->rexpr, DEPARSE_NODE_CONTEXT_NONE);
			appendStringInfoChar(str, ')');
			return;
		case AEXPR_OP_ALL: /* scalar op ALL (array) */
			// TODO: Handle schema-qualified operators
			Assert(list_length(a_expr->name) == 1);
			Assert(IsA(linitial(a_expr->name), String));
			deparseNode(str, a_expr->lexpr, DEPARSE_NODE_CONTEXT_NONE);
			appendStringInfoChar(str, ' ');
			appendStringInfoString(str, strVal(linitial(a_expr->name)));
			appendStringInfoString(str, " ALL(");
			deparseNode(str, a_expr->rexpr, DEPARSE_NODE_CONTEXT_NONE);
			appendStringInfoChar(str, ')');
			return;
		case AEXPR_DISTINCT: /* IS DISTINCT FROM - name must be "=" */
			// TODO
			Assert(false);
			return;
		case AEXPR_NOT_DISTINCT: /* IS NOT DISTINCT FROM - name must be "=" */
			// TODO
			Assert(false);
			return;
		case AEXPR_NULLIF: /* NULLIF - name must be "=" */
			Assert(list_length(a_expr->name) == 1);
			Assert(IsA(linitial(a_expr->name), String));
			Assert(strcmp(strVal(linitial(a_expr->name)), "=") == 0);

			appendStringInfoString(str, "NULLIF(");
			deparseNode(str, a_expr->lexpr, DEPARSE_NODE_CONTEXT_NONE);
			appendStringInfoString(str, ", ");
			deparseNode(str, a_expr->rexpr, DEPARSE_NODE_CONTEXT_NONE);
			appendStringInfoChar(str, ')');
			return;
		case AEXPR_OF: /* IS [NOT] OF - name must be "=" or "<>" */
			// TODO
			Assert(false);
			return;
		case AEXPR_IN: /* [NOT] IN - name must be "=" or "<>" */
			Assert(list_length(a_expr->name) == 1);
			Assert(IsA(linitial(a_expr->name), String));
			Assert(IsA(a_expr->rexpr, List));
			deparseNode(str, a_expr->lexpr, DEPARSE_NODE_CONTEXT_NONE);
			appendStringInfoChar(str, ' ');
			name = ((Value *) linitial(a_expr->name))->val.str;
			if (strcmp(name, "=") == 0) {
				appendStringInfoString(str, "IN ");
			} else if (strcmp(name, "<>") == 0) {
				appendStringInfoString(str, "NOT IN ");
			} else {
				Assert(false);
			}
			appendStringInfoChar(str, '(');
			foreach(lc, castNode(List, a_expr->rexpr)) {
				deparseNode(str, lfirst(lc), DEPARSE_NODE_CONTEXT_NONE);
				if (lnext(castNode(List, a_expr->rexpr), lc))
					appendStringInfoString(str, ", ");
			}
			appendStringInfoChar(str, ')');
			return;
		case AEXPR_LIKE: /* [NOT] LIKE - name must be "~~" or "!~~" */
			Assert(list_length(a_expr->name) == 1);
			Assert(IsA(linitial(a_expr->name), String));
			deparseNode(str, a_expr->lexpr, DEPARSE_NODE_CONTEXT_NONE);
			appendStringInfoChar(str, ' ');

			name = ((Value *) linitial(a_expr->name))->val.str;
			if (strcmp(name, "~~") == 0) {
				appendStringInfoString(str, "LIKE ");
			} else if (strcmp(name, "!~~") == 0) {
				appendStringInfoString(str, "NOT LIKE ");
			} else {
				Assert(false);
			}

			deparseNode(str, a_expr->rexpr, DEPARSE_NODE_CONTEXT_NONE);
			return;
		case AEXPR_ILIKE: /* [NOT] ILIKE - name must be "~~*" or "!~~*" */
			Assert(list_length(a_expr->name) == 1);
			Assert(IsA(linitial(a_expr->name), String));
			deparseNode(str, a_expr->lexpr, DEPARSE_NODE_CONTEXT_NONE);
			appendStringInfoChar(str, ' ');

			name = ((Value *) linitial(a_expr->name))->val.str;
			if (strcmp(name, "~~*") == 0) {
				appendStringInfoString(str, "ILIKE ");
			} else if (strcmp(name, "!~~*") == 0) {
				appendStringInfoString(str, "NOT ILIKE ");
			} else {
				Assert(false);
			}

			deparseNode(str, a_expr->rexpr, DEPARSE_NODE_CONTEXT_NONE);
			return;
		case AEXPR_SIMILAR: /* [NOT] SIMILAR - name must be "~" or "!~" */
			// TODO
			Assert(false);
			return;
		case AEXPR_BETWEEN: /* name must be "BETWEEN" */
		case AEXPR_NOT_BETWEEN: /* name must be "NOT BETWEEN" */
		case AEXPR_BETWEEN_SYM: /* name must be "BETWEEN SYMMETRIC" */
		case AEXPR_NOT_BETWEEN_SYM: /* name must be "NOT BETWEEN SYMMETRIC" */
			Assert(list_length(a_expr->name) == 1);
			Assert(IsA(linitial(a_expr->name), String));
			Assert(IsA(a_expr->rexpr, List));

			deparseNode(str, a_expr->lexpr, DEPARSE_NODE_CONTEXT_NONE);
			appendStringInfoChar(str, ' ');
			appendStringInfoString(str, strVal(linitial(a_expr->name)));
			appendStringInfoChar(str, ' ');

			foreach(lc, castNode(List, a_expr->rexpr)) {
				deparseNode(str, lfirst(lc), DEPARSE_NODE_CONTEXT_NONE);
				if (lnext(castNode(List, a_expr->rexpr), lc))
					appendStringInfoString(str, " AND ");
			}
			return;
		case AEXPR_PAREN: /* nameless dummy node for parentheses */
			// TODO
			Assert(false);
			return;
	}
}

static void deparseBoolExpr(StringInfo str, BoolExpr *bool_expr)
{
	const ListCell *lc = NULL;
	switch (bool_expr->boolop)
	{
		case AND_EXPR:
			foreach(lc, bool_expr->args)
			{
				// Put parentheses around OR nodes that are inside this one
				bool need_parens = IsA(lfirst(lc), BoolExpr) && castNode(BoolExpr, lfirst(lc))->boolop == OR_EXPR;

				if (need_parens)
					appendStringInfoChar(str, '(');

				deparseNode(str, lfirst(lc), DEPARSE_NODE_CONTEXT_NONE);

				if (need_parens)
					appendStringInfoChar(str, ')');

				if (lnext(bool_expr->args, lc))
					appendStringInfoString(str, " AND ");
			}
			return;
		case OR_EXPR:
			foreach(lc, bool_expr->args)
			{
				// Put parantheses around AND + OR nodes that are inside
				bool need_parens = IsA(lfirst(lc), BoolExpr) && (castNode(BoolExpr, lfirst(lc))->boolop == AND_EXPR || castNode(BoolExpr, lfirst(lc))->boolop == OR_EXPR);

				if (need_parens)
					appendStringInfoChar(str, '(');

				deparseNode(str, lfirst(lc), DEPARSE_NODE_CONTEXT_NONE);

				if (need_parens)
					appendStringInfoChar(str, ')');

				if (lnext(bool_expr->args, lc))
					appendStringInfoString(str, " OR ");
			}
			return;
		case NOT_EXPR:
			Assert(list_length(bool_expr->args) == 1);
			appendStringInfoString(str, "NOT ");
			deparseNode(str, linitial(bool_expr->args), DEPARSE_NODE_CONTEXT_NONE);
			return;
	}
}

static void deparseAStar(StringInfo str, A_Star *a_star)
{
	appendStringInfoChar(str, '*');
}

static void deparseCollateClause(StringInfo str, CollateClause* collate_clause)
{
	ListCell *lc;
	if (collate_clause->arg != NULL)
	{
		deparseNode(str, collate_clause->arg, DEPARSE_NODE_CONTEXT_NONE);
		appendStringInfoChar(str, ' ');
	}
	appendStringInfoString(str, "COLLATE ");
	foreach(lc, collate_clause->collname) {
		deparseNode(str, lfirst(lc), DEPARSE_NODE_CONTEXT_IDENTIFIER);
		if (lnext(collate_clause->collname, lc))
			appendStringInfoString(str, ".");
	}
}

static void deparseSortBy(StringInfo str, SortBy* sort_by)
{
	deparseNode(str, sort_by->node, DEPARSE_NODE_CONTEXT_NONE);
	appendStringInfoChar(str, ' ');

	switch (sort_by->sortby_dir)
	{
		case SORTBY_DEFAULT:
			break;
		case SORTBY_ASC:
			appendStringInfoString(str, "ASC ");
			break;
		case SORTBY_DESC:
			appendStringInfoString(str, "DESC ");
			break;
		case SORTBY_USING:
			// TODO: Handle USING [operator] syntax
			Assert(false);
			break;
	}

	switch (sort_by->sortby_nulls)
	{
		case SORTBY_NULLS_DEFAULT:
			break;
		case SORTBY_NULLS_FIRST:
			appendStringInfoString(str, "NULLS FIRST ");
			break;
		case SORTBY_NULLS_LAST:
			appendStringInfoString(str, "NULLS LAST ");
			break;
	}

	removeTrailingSpace(str);
}

static void deparseParamRef(StringInfo str, ParamRef* param_ref)
{
	if (param_ref->number == 0) {
		appendStringInfoChar(str, '?');
	} else {
		appendStringInfo(str, "$%d", param_ref->number);
	}
}

static void deparseSQLValueFunction(StringInfo str, SQLValueFunction* sql_value_function)
{
	switch (sql_value_function->op)
	{
		case SVFOP_CURRENT_DATE:
			appendStringInfoString(str, "current_date");
			break;
		case SVFOP_CURRENT_TIME:
			appendStringInfoString(str, "current_time");
			break;
		case SVFOP_CURRENT_TIME_N:
			appendStringInfoString(str, "current_time"); // with precision
			break;
		case SVFOP_CURRENT_TIMESTAMP:
			appendStringInfoString(str, "current_timestamp");
			break;
		case SVFOP_CURRENT_TIMESTAMP_N:
			appendStringInfoString(str, "current_timestamp"); // with precision
			break;
		case SVFOP_LOCALTIME:
			appendStringInfoString(str, "localtime");
			break;
		case SVFOP_LOCALTIME_N:
			appendStringInfoString(str, "localtime"); // with precision
			break;
		case SVFOP_LOCALTIMESTAMP:
			appendStringInfoString(str, "localtimestamp");
			break;
		case SVFOP_LOCALTIMESTAMP_N:
			appendStringInfoString(str, "localtimestamp"); // with precision
			break;
		case SVFOP_CURRENT_ROLE:
			appendStringInfoString(str, "current_role");
			break;
		case SVFOP_CURRENT_USER:
			appendStringInfoString(str, "current_user");
			break;
		case SVFOP_USER:
			appendStringInfoString(str, "user");
			break;
		case SVFOP_SESSION_USER:
			appendStringInfoString(str, "session_user");
			break;
		case SVFOP_CURRENT_CATALOG:
			appendStringInfoString(str, "current_catalog");
			break;
		case SVFOP_CURRENT_SCHEMA:
			appendStringInfoString(str, "current_schema");
			break;
	}

	if (sql_value_function->typmod != -1)
	{
		appendStringInfo(str, "(%d)", sql_value_function->typmod);
	}
}

static void deparseWithClause(StringInfo str, WithClause *with_clause)
{
	ListCell *lc;

	appendStringInfoString(str, "WITH ");
	if (with_clause->recursive)
		appendStringInfoString(str, "RECURSIVE ");
	
	foreach(lc, with_clause->ctes) {
		deparseNode(str, lfirst(lc), DEPARSE_NODE_CONTEXT_NONE);
		if (lnext(with_clause->ctes, lc))
			appendStringInfoString(str, ", ");
	}

	removeTrailingSpace(str);
}

static void deparseJoinExpr(StringInfo str, JoinExpr *join_expr)
{
	ListCell *lc;

	deparseNode(str, join_expr->larg, DEPARSE_NODE_CONTEXT_NONE);
	appendStringInfoChar(str, ' ');

	switch (join_expr->jointype)
	{
		case JOIN_INNER: /* matching tuple pairs only */
			if (join_expr->isNatural)
				appendStringInfoString(str, "NATURAL ");
			else if (join_expr->quals == NULL && list_length(join_expr->usingClause) == 0)
				appendStringInfoString(str, "CROSS ");
			break;
		case JOIN_LEFT: /* pairs + unmatched LHS tuples */
			appendStringInfoString(str, "LEFT ");
			break;
		case JOIN_FULL: /* pairs + unmatched LHS + unmatched RHS */
			appendStringInfoString(str, "FULL ");
			break;
		case JOIN_RIGHT: /* pairs + unmatched RHS tuples */
			appendStringInfoString(str, "RIGHT ");
			break;
		case JOIN_SEMI:
		case JOIN_ANTI:
		case JOIN_UNIQUE_OUTER:
		case JOIN_UNIQUE_INNER:
			// Only used by the planner/executor, not seen in parser output
			Assert(false);
			break;
	}
	
	appendStringInfoString(str, "JOIN ");

	deparseNode(str, join_expr->rarg, DEPARSE_NODE_CONTEXT_NONE);
	appendStringInfoChar(str, ' ');

	if (join_expr->quals != NULL)
	{
		appendStringInfoString(str, "ON ");
		deparseNode(str, join_expr->quals, DEPARSE_NODE_CONTEXT_NONE);
		appendStringInfoChar(str, ' ');
	}

	if (list_length(join_expr->usingClause) > 0)
	{
		appendStringInfoString(str, "USING (");
		foreach(lc, join_expr->usingClause) {
			deparseNode(str, lfirst(lc), DEPARSE_NODE_CONTEXT_IDENTIFIER);
			if (lnext(join_expr->usingClause, lc))
				appendStringInfoString(str, ", ");
		}
		appendStringInfoChar(str, ')');
	}

	removeTrailingSpace(str);
}

static void deparseCommonTableExpr(StringInfo str, CommonTableExpr *cte)
{
	ListCell *lc;

	appendStringInfoString(str, cte->ctename);
	if (list_length(cte->aliascolnames) > 0)
	{
		appendStringInfoChar(str, '(');
		foreach(lc, cte->aliascolnames) {
			deparseNode(str, lfirst(lc), DEPARSE_NODE_CONTEXT_IDENTIFIER);
			if (lnext(cte->aliascolnames, lc))
				appendStringInfoString(str, ", ");
		}
		appendStringInfoChar(str, ')');
	}
	appendStringInfoChar(str, ' ');

	appendStringInfoString(str, "AS ");
	switch (cte->ctematerialized) {
		case CTEMaterializeDefault: /* no option specified */
			break;
		case CTEMaterializeAlways:
			appendStringInfoString(str, "MATERIALIZED ");
			break;
		case CTEMaterializeNever:
			appendStringInfoString(str, "NOT MATERIALIZED ");
			break;
	}

	appendStringInfoChar(str, '(');
	deparseNode(str, cte->ctequery, DEPARSE_NODE_CONTEXT_NONE);
	appendStringInfoChar(str, ')');
}

static void deparseRangeSubselect(StringInfo str, RangeSubselect *range_subselect)
{
	if (range_subselect->lateral)
		appendStringInfoString(str, "LATERAL ");

	appendStringInfoChar(str, '(');
	deparseNode(str, range_subselect->subquery, DEPARSE_NODE_CONTEXT_NONE);
	appendStringInfoChar(str, ')');

	if (range_subselect->alias != NULL)
	{
		appendStringInfoChar(str, ' ');
		deparseAlias(str, range_subselect->alias);
	}
}

static void deparseRangeFunction(StringInfo str, RangeFunction *range_func)
{
	ListCell *lc;

	if (range_func->lateral)
		appendStringInfoString(str, "LATERAL ");

	if (list_length(range_func->functions) == 1)
	{
		Assert(list_length(linitial(range_func->functions)) == 2);
		deparseNode(str, linitial(linitial(range_func->functions)), DEPARSE_NODE_CONTEXT_NONE);
	}
	else if (list_length(range_func->functions) > 1)
	{
		// FIXME: Add support for ROWS FROM
		Assert(false);
	}
	else
	{
		Assert(false);
	}
	appendStringInfoChar(str, ' ');

	if (range_func->alias != NULL)
	{
		deparseAlias(str, range_func->alias);
		appendStringInfoChar(str, ' ');
	}

	if (list_length(range_func->coldeflist) > 0)
	{
		if (range_func->alias == NULL)
			appendStringInfoString(str, "AS ");
		appendStringInfoChar(str, '(');
		foreach(lc, range_func->coldeflist) {
			deparseNode(str, lfirst(lc), DEPARSE_NODE_CONTEXT_NONE);
			if (lnext(range_func->coldeflist, lc))
				appendStringInfoString(str, ", ");
		}
		appendStringInfoChar(str, ')');
	}

	removeTrailingSpace(str);
}

static void deparseAArrayExpr(StringInfo str, A_ArrayExpr *array_expr)
{
	ListCell *lc;

	appendStringInfoString(str, "ARRAY[");
	foreach(lc, array_expr->elements) {
		deparseNode(str, lfirst(lc), DEPARSE_NODE_CONTEXT_NONE);
		if (lnext(array_expr->elements, lc))
			appendStringInfoString(str, ", ");
	}
	appendStringInfoChar(str, ']');
}

static void deparseRowExpr(StringInfo str, RowExpr *row_expr)
{
	ListCell *lc;

	appendStringInfoString(str, "ROW(");
	foreach(lc, row_expr->args) {
		deparseNode(str, lfirst(lc), DEPARSE_NODE_CONTEXT_NONE);
		if (lnext(row_expr->args, lc))
			appendStringInfoString(str, ", ");
	}
	appendStringInfoChar(str, ')');
}

static void deparseTypeCast(StringInfo str, TypeCast *type_cast)
{
	bool need_parens = IsA(type_cast->arg, A_Expr);

	Assert(type_cast->typeName != NULL);

	/*
	 * Handle "bool" or "false" in the statement, which is represented as a typecast
     * (other boolean casts should be represented as a cast, i.e. don't need special handling)
	 */
	if (IsA(type_cast->arg, A_Const) &&
		list_length(type_cast->typeName->names) == 2 &&
		strcmp(strVal(linitial(type_cast->typeName->names)), "pg_catalog") == 0 &&
		strcmp(strVal(lsecond(type_cast->typeName->names)), "bool") == 0 &&
		nodeTag(&castNode(A_Const, type_cast->arg)->val) == T_String) {
		char *const_val = castNode(A_Const, type_cast->arg)->val.val.str;
		if (strcmp(const_val, "t") == 0)
		{
			appendStringInfoString(str, "true");
			return;
		}
		if (strcmp(const_val, "f") == 0)
		{
			appendStringInfoString(str, "false");
			return;
		}
	}

	if (need_parens)
		appendStringInfoChar(str, '(');
	deparseNode(str, type_cast->arg, DEPARSE_NODE_CONTEXT_NONE);
	if (need_parens)
		appendStringInfoChar(str, ')');

	appendStringInfoString(str, "::");
	deparseTypeName(str, type_cast->typeName);
}

static void deparseTypeName(StringInfo str, TypeName *type_name)
{
	ListCell *lc;
	bool interval_type = false;

	if (type_name->setof)
		appendStringInfoString(str, "SETOF ");

	if (list_length(type_name->names) == 2 && strcmp(strVal(linitial(type_name->names)), "pg_catalog") == 0)
	{
		const char *name = strVal(lsecond(type_name->names));
		if (strcmp(name, "bpchar") == 0)
		{
			appendStringInfoString(str, "char");
		}
		else if (strcmp(name, "varchar") == 0)
		{
			appendStringInfoString(str, "varchar");
		}
		else if (strcmp(name, "numeric") == 0)
		{
			appendStringInfoString(str, "numeric");
		}
		else if (strcmp(name, "bool") == 0)
		{
			appendStringInfoString(str, "boolean");
		}
		else if (strcmp(name, "int2") == 0)
		{
			appendStringInfoString(str, "smallint");
		}
		else if (strcmp(name, "int4") == 0)
		{
			appendStringInfoString(str, "int");
		}
		else if (strcmp(name, "int8") == 0)
		{
			appendStringInfoString(str, "bigint");
		}
		else if (strcmp(name, "real") == 0 || strcmp(name, "float4") == 0)
		{
			appendStringInfoString(str, "real");
		}
		else if (strcmp(name, "float8") == 0)
		{
			appendStringInfoString(str, "double precision");
		}
		else if (strcmp(name, "time") == 0)
		{
			appendStringInfoString(str, "time");
		}
		else if (strcmp(name, "timetz") == 0)
		{
			appendStringInfoString(str, "time with time zone");
		}
		else if (strcmp(name, "timestamp") == 0)
		{
			appendStringInfoString(str, "timestamp");
		}
		else if (strcmp(name, "timestamptz") == 0)
		{
			appendStringInfoString(str, "timestamp with time zone");
		}
		else if (strcmp(name, "interval") == 0 && list_length(type_name->typmods) == 0)
		{
			appendStringInfoString(str, "interval");
		}
		else if (strcmp(name, "interval") == 0 && list_length(type_name->typmods) >= 1)
		{
			Assert(IsA(linitial(type_name->typmods), A_Const));
			Assert(IsA(&castNode(A_Const, linitial(type_name->typmods))->val, Integer));

			int fields = intVal(&castNode(A_Const, linitial(type_name->typmods))->val);

			appendStringInfoString(str, "interval");

			// This logic is based on intervaltypmodout in timestamp.c
			switch (fields)
			{
				case INTERVAL_MASK(YEAR):
					appendStringInfoString(str, " year");
					break;
				case INTERVAL_MASK(MONTH):
					appendStringInfoString(str, " month");
					break;
				case INTERVAL_MASK(DAY):
					appendStringInfoString(str, " day");
					break;
				case INTERVAL_MASK(HOUR):
					appendStringInfoString(str, " hour");
					break;
				case INTERVAL_MASK(MINUTE):
					appendStringInfoString(str, " minute");
					break;
				case INTERVAL_MASK(SECOND):
					appendStringInfoString(str, " second");
					break;
				case INTERVAL_MASK(YEAR) | INTERVAL_MASK(MONTH):
					appendStringInfoString(str, " year to month");
					break;
				case INTERVAL_MASK(DAY) | INTERVAL_MASK(HOUR):
					appendStringInfoString(str, " day to hour");
					break;
				case INTERVAL_MASK(DAY) | INTERVAL_MASK(HOUR) | INTERVAL_MASK(MINUTE):
					appendStringInfoString(str, " day to minute");
					break;
				case INTERVAL_MASK(DAY) | INTERVAL_MASK(HOUR) | INTERVAL_MASK(MINUTE) | INTERVAL_MASK(SECOND):
					appendStringInfoString(str, " day to second");
					break;
				case INTERVAL_MASK(HOUR) | INTERVAL_MASK(MINUTE):
					appendStringInfoString(str, " hour to minute");
					break;
				case INTERVAL_MASK(HOUR) | INTERVAL_MASK(MINUTE) | INTERVAL_MASK(SECOND):
					appendStringInfoString(str, " hour to second");
					break;
				case INTERVAL_MASK(MINUTE) | INTERVAL_MASK(SECOND):
					appendStringInfoString(str, " minute to second");
					break;
				case INTERVAL_FULL_RANGE:
					// Nothing
					break;
				default:
					Assert(false);
					break;
			}

			if (list_length(type_name->typmods) == 2)
			{
				int precision = intVal(&castNode(A_Const, lsecond(type_name->typmods))->val);
				if (precision != INTERVAL_FULL_PRECISION)
					appendStringInfo(str, "(%d)", precision);
			}
			
			interval_type = true;
		}
		else
		{
			appendStringInfoString(str, "pg_catalog.");
			appendStringInfoString(str, name);
		}
	}
	else
	{
		foreach(lc, type_name->names) {
			deparseNode(str, lfirst(lc), DEPARSE_NODE_CONTEXT_IDENTIFIER);
			if (lnext(type_name->names, lc))
				appendStringInfoString(str, ".");
		}
	}

	if (list_length(type_name->typmods) > 0 && !interval_type)
	{
		appendStringInfoChar(str, '(');
		foreach(lc, type_name->typmods) {
			deparseNode(str, lfirst(lc), DEPARSE_NODE_CONTEXT_NONE);
			if (lnext(type_name->typmods, lc))
				appendStringInfoString(str, ", ");
		}
		appendStringInfoChar(str, ')');
	}

	foreach(lc, type_name->arrayBounds) {
		appendStringInfoChar(str, '[');
		if (!IsA(lfirst(lc), Integer) || intVal(lfirst(lc)) != -1)
			deparseNode(str, lfirst(lc), DEPARSE_NODE_CONTEXT_NONE);
		appendStringInfoChar(str, ']');
	}
}

static void deparseNullTest(StringInfo str, NullTest *null_test)
{
	// TODO: Add support for row type inputs
	Assert(null_test->argisrow == false);

	deparseNode(str, (Node *) null_test->arg, DEPARSE_NODE_CONTEXT_NONE);
	switch (null_test->nulltesttype)
	{
		case IS_NULL:
			appendStringInfoString(str, " IS NULL");
			break;
		case IS_NOT_NULL:
			appendStringInfoString(str, " IS NOT NULL");
			break;
	}
}

static void deparseCaseExpr(StringInfo str, CaseExpr *case_expr)
{
	ListCell *lc;

	appendStringInfoString(str, "CASE ");

	if (case_expr->arg != NULL)
	{
		deparseNode(str, (Node *) case_expr->arg, DEPARSE_NODE_CONTEXT_NONE);
		appendStringInfoChar(str, ' ');
	}

	foreach(lc, case_expr->args) {
		deparseNode(str, lfirst(lc), DEPARSE_NODE_CONTEXT_NONE);
		appendStringInfoChar(str, ' ');
	}

	if (case_expr->defresult != NULL)
	{
		appendStringInfoString(str, "ELSE ");
		deparseNode(str, (Node *) case_expr->defresult, DEPARSE_NODE_CONTEXT_NONE);
		appendStringInfoChar(str, ' ');
	}

	appendStringInfoString(str, "END");
}

static void deparseCaseWhen(StringInfo str, CaseWhen *case_when)
{
	appendStringInfoString(str, "WHEN ");
	deparseNode(str, (Node *) case_when->expr, DEPARSE_NODE_CONTEXT_NONE);
	appendStringInfoString(str, " THEN ");
	deparseNode(str, (Node *) case_when->result, DEPARSE_NODE_CONTEXT_NONE);
}

static void deparseAIndirection(StringInfo str, A_Indirection *a_indirection)
{
	ListCell *lc;
	bool need_parens = IsA(a_indirection->arg, FuncCall) || IsA(a_indirection->arg, A_Expr);

	if (need_parens)
		appendStringInfoChar(str, '(');

	deparseNode(str, a_indirection->arg, DEPARSE_NODE_CONTEXT_NONE);

	if (need_parens)
		appendStringInfoChar(str, ')');

	foreach(lc, a_indirection->indirection)
	{
		if (!IsA(lfirst(lc), A_Indices))
			appendStringInfoChar(str, '.');
		deparseNode(str, lfirst(lc), DEPARSE_NODE_CONTEXT_NONE);
	}
}

static void deparseAIndices(StringInfo str, A_Indices *a_indices)
{
	appendStringInfoChar(str, '[');
	if (a_indices->lidx != NULL)
		deparseNode(str, a_indices->lidx, DEPARSE_NODE_CONTEXT_NONE);
	if (a_indices->lidx != NULL && a_indices->uidx != NULL)
		appendStringInfoChar(str, ':');
	if (a_indices->uidx != NULL)
		deparseNode(str, a_indices->uidx, DEPARSE_NODE_CONTEXT_NONE);
	appendStringInfoChar(str, ']');
}

static void deparseCoalesceExpr(StringInfo str, CoalesceExpr *coalesce_expr)
{
	ListCell *lc;
	appendStringInfoString(str, "COALESCE(");
	foreach(lc, coalesce_expr->args) {
		deparseNode(str, lfirst(lc), DEPARSE_NODE_CONTEXT_NONE);
		if (lnext(coalesce_expr->args, lc))
			appendStringInfoString(str, ", ");
	}
	appendStringInfoChar(str, ')');
}

static void deparseBooleanTest(StringInfo str, BooleanTest *boolean_test)
{
	deparseNode(str, (Node *) boolean_test->arg, DEPARSE_NODE_CONTEXT_NONE);
	switch (boolean_test->booltesttype)
	{
		case IS_TRUE:
			appendStringInfoString(str, " IS TRUE");
			break;
		case IS_NOT_TRUE:
			appendStringInfoString(str, " IS NOT TRUE");
			break;
		case IS_FALSE:
			appendStringInfoString(str, " IS FALSE");
			break;
		case IS_NOT_FALSE:
			appendStringInfoString(str, " IS NOT FALSE");
			break;
		case IS_UNKNOWN:
			appendStringInfoString(str, " IS UNKNOWN");
			break;
		case IS_NOT_UNKNOWN:
			appendStringInfoString(str, " IS NOT UNKNOWN");
			break;
		default:
			Assert(false);
	}
}

static void deparseColumnDef(StringInfo str, ColumnDef *column_def)
{
	ListCell *lc;

	if (column_def->colname != NULL)
	{
		appendStringInfoString(str, column_def->colname);
		appendStringInfoChar(str, ' ');
	}

	deparseTypeName(str, column_def->typeName);
	appendStringInfoChar(str, ' ');

	if (column_def->raw_default != NULL)
	{
		appendStringInfoString(str, "USING ");
		deparseNode(str, column_def->raw_default, DEPARSE_NODE_CONTEXT_NONE);
		appendStringInfoChar(str, ' ');
	}

	foreach(lc, column_def->constraints) {
		deparseNode(str, lfirst(lc), DEPARSE_NODE_CONTEXT_NONE);
		if (lnext(column_def->constraints, lc))
			appendStringInfoChar(str, ' ');
	}

	if (column_def->collClause != NULL)
	{
		deparseCollateClause(str, column_def->collClause);
	}

	removeTrailingSpace(str);

	// TODO
	/*
      if node['collClause']
        output << 'COLLATE'
        output += node['collClause']['CollateClause']['collname'].map(&method(:deparse_item))
      end
	  */
}

static void deparseInsertStmt(StringInfo str, InsertStmt *insert_stmt)
{
	ListCell *lc;
	ListCell *lc2;

	if (insert_stmt->withClause != NULL)
	{
		deparseWithClause(str, insert_stmt->withClause);
		appendStringInfoChar(str, ' ');
	}

	appendStringInfoString(str, "INSERT INTO ");
	deparseRangeVar(str, insert_stmt->relation);
	appendStringInfoChar(str, ' ');

	if (list_length(insert_stmt->cols) > 0)
	{
		appendStringInfoChar(str, '(');
		foreach(lc, insert_stmt->cols)
		{
			deparseNode(str, lfirst(lc), DEPARSE_NODE_CONTEXT_INSERT_TARGET_LIST);
			if (lnext(insert_stmt->cols, lc))
				appendStringInfoString(str, ", ");
		}
		appendStringInfoString(str, ") ");
	}

	if (insert_stmt->selectStmt != NULL)
	{
		deparseNode(str, insert_stmt->selectStmt, DEPARSE_NODE_CONTEXT_NONE);
		appendStringInfoChar(str, ' ');
	}

	if (insert_stmt->onConflictClause != NULL)
	{
		deparseOnConflictClause(str, insert_stmt->onConflictClause);
		appendStringInfoChar(str, ' ');
	}

	if (list_length(insert_stmt->returningList) > 0)
	{
		appendStringInfoString(str, "RETURNING ");
		foreach(lc2, insert_stmt->returningList)
		{
			deparseNode(str, lfirst(lc2), DEPARSE_NODE_CONTEXT_RETURNING);
			if (lnext(insert_stmt->returningList, lc2))
				appendStringInfoString(str, ", ");
		}
	}

	removeTrailingSpace(str);
}

static void deparseOnConflictClause(StringInfo str, OnConflictClause *on_conflict_clause)
{
	ListCell *lc;
	ListCell *lc2;
	InferClause *infer_clause = castNode(InferClause, on_conflict_clause->infer);

	appendStringInfoString(str, "ON CONFLICT ");

	if (list_length(infer_clause->indexElems) > 0)
	{
		appendStringInfoChar(str, '(');
		foreach(lc, infer_clause->indexElems)
		{
			deparseNode(str, lfirst(lc), DEPARSE_NODE_CONTEXT_NONE);
			if (lnext(infer_clause->indexElems, lc))
				appendStringInfoString(str, ", ");
		}
		appendStringInfoString(str, ") ");
	}

	if (infer_clause->conname != NULL)
	{
		appendStringInfoString(str, "ON CONSTRAINT ");
		appendStringInfoString(str, quote_identifier(infer_clause->conname));
		appendStringInfoChar(str, ' ');
	}

	// TODO: Do we also need to look at on_conflict_clause->whereClause?
	if (infer_clause->whereClause != NULL)
	{
		appendStringInfoString(str, "WHERE ");
		deparseNode(str, infer_clause->whereClause, DEPARSE_NODE_CONTEXT_NONE);
		appendStringInfoChar(str, ' ');
	}

	switch (on_conflict_clause->action)
	{
		case ONCONFLICT_NONE:
			Assert(false);
			break;
		case ONCONFLICT_NOTHING:
			appendStringInfoString(str, "DO NOTHING ");
			break;
		case ONCONFLICT_UPDATE:
			appendStringInfoString(str, "DO UPDATE ");
			break;
	}

	if (list_length(on_conflict_clause->targetList) > 0)
	{
		appendStringInfoString(str, "SET ");
		foreach(lc2, on_conflict_clause->targetList)
		{
			deparseNode(str, lfirst(lc2), DEPARSE_NODE_CONTEXT_INSERT_ON_CONFLICT);
			if (lnext(on_conflict_clause->targetList, lc2))
				appendStringInfoString(str, ", ");
		}
		appendStringInfoChar(str, ' ');
	}

	removeTrailingSpace(str);
}

static void deparseIndexElem(StringInfo str, IndexElem* index_elem)
{
	appendStringInfoString(str, quote_identifier(index_elem->name));
	// TODO: Support other columns
}

static void deparseUpdateStmt(StringInfo str, UpdateStmt *update_stmt)
{
	ListCell* lc;
	ListCell* lc2;
	ListCell* lc3;

	if (update_stmt->withClause != NULL)
	{
		deparseWithClause(str, update_stmt->withClause);
		appendStringInfoChar(str, ' ');
	}

	appendStringInfoString(str, "UPDATE ");
	deparseRangeVar(str, update_stmt->relation);
	appendStringInfoChar(str, ' ');

	if (list_length(update_stmt->targetList) > 0)
	{
		appendStringInfoString(str, "SET ");
		foreach(lc, update_stmt->targetList)
		{
			deparseNode(str, lfirst(lc), DEPARSE_NODE_CONTEXT_UPDATE);
			if (lnext(update_stmt->targetList, lc))
				appendStringInfoString(str, ", ");
		}
		appendStringInfoChar(str, ' ');
	}

	if (list_length(update_stmt->fromClause) > 0)
	{
		appendStringInfoString(str, "FROM ");

		foreach(lc2, update_stmt->fromClause)
		{
			deparseNode(str, lfirst(lc2), DEPARSE_NODE_CONTEXT_UPDATE);
			if (lnext(update_stmt->fromClause, lc2))
				appendStringInfoString(str, ", ");
		}
		appendStringInfoChar(str, ' ');
	}

	if (update_stmt->whereClause != NULL)
	{
		appendStringInfoString(str, "WHERE ");
		deparseNode(str, update_stmt->whereClause, DEPARSE_NODE_CONTEXT_NONE);
		appendStringInfoChar(str, ' ');
	}

	if (list_length(update_stmt->returningList) > 0)
	{
		appendStringInfoString(str, "RETURNING ");
		foreach(lc3, update_stmt->returningList)
		{
			deparseNode(str, lfirst(lc3), DEPARSE_NODE_CONTEXT_RETURNING);
			if (lnext(update_stmt->returningList, lc3))
				appendStringInfoString(str, ", ");
		}
	}

	removeTrailingSpace(str);
}

static void deparseDeleteStmt(StringInfo str, DeleteStmt *delete_stmt)
{
	ListCell* lc;
	ListCell* lc2;

	if (delete_stmt->withClause != NULL)
	{
		deparseWithClause(str, delete_stmt->withClause);
		appendStringInfoChar(str, ' ');
	}

	appendStringInfoString(str, "DELETE FROM ");
	deparseRangeVar(str, delete_stmt->relation);
	appendStringInfoChar(str, ' ');

	if (delete_stmt->usingClause != NULL)
	{
		appendStringInfoString(str, "USING ");
		foreach(lc, delete_stmt->usingClause)
		{
			deparseNode(str, lfirst(lc), DEPARSE_NODE_CONTEXT_NONE);
			if (lnext(delete_stmt->usingClause, lc))
				appendStringInfoString(str, ", ");
		}
		appendStringInfoChar(str, ' ');
	}

	if (delete_stmt->whereClause != NULL)
	{
		appendStringInfoString(str, "WHERE ");
		deparseNode(str, delete_stmt->whereClause, DEPARSE_NODE_CONTEXT_NONE);
		appendStringInfoChar(str, ' ');
	}

	if (list_length(delete_stmt->returningList) > 0)
	{
		appendStringInfoString(str, "RETURNING ");
		foreach(lc2, delete_stmt->returningList)
		{
			deparseNode(str, lfirst(lc2), DEPARSE_NODE_CONTEXT_RETURNING);
			if (lnext(delete_stmt->returningList, lc2))
				appendStringInfoString(str, ", ");
		}
	}

	removeTrailingSpace(str);
}

static void deparseLockingClause(StringInfo str, LockingClause *locking_clause)
{
	ListCell *lc;

	switch (locking_clause->strength)
	{
		case LCS_NONE:
			/* no such clause - only used in PlanRowMark */
			Assert(false);
			break;
		case LCS_FORKEYSHARE:
			appendStringInfoString(str, "FOR KEY SHARE ");
			break;
		case LCS_FORSHARE:
			appendStringInfoString(str, "FOR SHARE ");
			break;
		case LCS_FORNOKEYUPDATE:
			appendStringInfoString(str, "FOR NO KEY UPDATE ");
			break;
		case LCS_FORUPDATE:
			appendStringInfoString(str, "FOR UPDATE ");
			break;
	}

	if (list_length(locking_clause->lockedRels) > 0)
	{
		appendStringInfoString(str, "OF ");
		foreach(lc, locking_clause->lockedRels)
		{
			deparseNode(str, lfirst(lc), DEPARSE_NODE_CONTEXT_NONE);
			if (lnext(locking_clause->lockedRels, lc))
				appendStringInfoString(str, ", ");
		}
	}

	// TODO: LockWaitPolicy waitPolicy;	/* NOWAIT and SKIP LOCKED */

	removeTrailingSpace(str);
}

static void deparseSetToDefault(StringInfo str, SetToDefault *set_to_default)
{
	appendStringInfoString(str, "DEFAULT");
}

static void deparseCreateCastStmt(StringInfo str, CreateCastStmt *create_cast_stmt)
{
	ListCell *lc;
	ListCell *lc2;

	appendStringInfoString(str, "CREATE CAST (");
	deparseTypeName(str, create_cast_stmt->sourcetype);
	appendStringInfoString(str, " AS ");
	deparseTypeName(str, create_cast_stmt->targettype);
	appendStringInfoString(str, ") ");

	if (create_cast_stmt->func != NULL)
	{
		appendStringInfoString(str, "WITH FUNCTION ");
		foreach(lc, create_cast_stmt->func->objname)
		{
			deparseNode(str, lfirst(lc), DEPARSE_NODE_CONTEXT_IDENTIFIER);
			if (lnext(create_cast_stmt->func->objname, lc))
				appendStringInfoString(str, ".");
		}
		appendStringInfoChar(str, '(');
		foreach(lc2, create_cast_stmt->func->objargs)
		{
			deparseNode(str, lfirst(lc2), DEPARSE_NODE_CONTEXT_IDENTIFIER);
			if (lnext(create_cast_stmt->func->objargs, lc2))
				appendStringInfoString(str, ", ");
		}
		appendStringInfoString(str, ") ");
	}
	else if (create_cast_stmt->inout)
	{
		appendStringInfoString(str, "WITH INOUT ");
	}
	else
	{
		appendStringInfoString(str, "WITHOUT FUNCTION ");
	}

	switch (create_cast_stmt->context)
	{
		case COERCION_IMPLICIT:
			appendStringInfoString(str, "AS IMPLICIT");
			break;
		case COERCION_ASSIGNMENT:
			appendStringInfoString(str, "AS ASSIGNMENT");
			break;
		case COERCION_EXPLICIT:
			// Default
			break;
	}
}

static void deparseCreateDomainStmt(StringInfo str, CreateDomainStmt *create_domain_stmt)
{
	ListCell *lc;

	Assert(create_domain_stmt->typeName != NULL);

	appendStringInfoString(str, "CREATE DOMAIN ");
	foreach(lc, create_domain_stmt->domainname)
	{
		deparseNode(str, lfirst(lc), DEPARSE_NODE_CONTEXT_IDENTIFIER);
		if (lnext(create_domain_stmt->domainname, lc))
			appendStringInfoString(str, ".");
	}
	appendStringInfoString(str, " AS ");

	deparseTypeName(str, create_domain_stmt->typeName);
	appendStringInfoChar(str, ' ');

	if (create_domain_stmt->collClause != NULL)
	{
		deparseCollateClause(str, create_domain_stmt->collClause);
		appendStringInfoChar(str, ' ');
	}

	foreach(lc, create_domain_stmt->constraints)
	{
		deparseNode(str, lfirst(lc), DEPARSE_NODE_CONTEXT_NONE);
		appendStringInfoChar(str, ' ');
	}

	removeTrailingSpace(str);
}

static void deparseConstraint(StringInfo str, Constraint *constraint)
{
	ListCell *lc;

	if (constraint->conname != NULL)
	{
		appendStringInfoString(str, "CONSTRAINT ");
		appendStringInfoString(str, constraint->conname);
		appendStringInfoChar(str, ' ');
	}

	switch (constraint->contype) {
		case CONSTR_NULL:
			appendStringInfoString(str, "NULL ");
			break;
		case CONSTR_NOTNULL:
			appendStringInfoString(str, "NOT NULL ");
			break;
		case CONSTR_DEFAULT:
			appendStringInfoString(str, "DEFAULT ");
			break;
		case CONSTR_IDENTITY:
			// TODO
			Assert(false);
			break;
		case CONSTR_GENERATED:
			// TODO
			Assert(false);
			break;
		case CONSTR_CHECK:
			appendStringInfoString(str, "CHECK ");
			break;
		case CONSTR_PRIMARY:
			appendStringInfoString(str, "PRIMARY KEY ");
			break;
		case CONSTR_UNIQUE:
			appendStringInfoString(str, "UNIQUE ");
			break;
		case CONSTR_EXCLUSION:
			appendStringInfoString(str, "EXCLUSION ");
			break;
		case CONSTR_FOREIGN:
			appendStringInfoString(str, "FOREIGN KEY ");
			break;
		case CONSTR_ATTR_DEFERRABLE:
		case CONSTR_ATTR_NOT_DEFERRABLE:
		case CONSTR_ATTR_DEFERRED:
		case CONSTR_ATTR_IMMEDIATE:
			// TODO: attributes for previous constraint node
			Assert(false);
			break;
	}

	if (constraint->raw_expr != NULL)
	{
		bool needs_parens = IsA(constraint->raw_expr, BoolExpr) || (IsA(constraint->raw_expr, A_Expr) && castNode(A_Expr, constraint->raw_expr)->kind == AEXPR_OP);

		if (needs_parens)
			appendStringInfoChar(str, '(');
		
		deparseNode(str, constraint->raw_expr, DEPARSE_NODE_CONTEXT_NONE);

		if (needs_parens)
			appendStringInfoChar(str, ')');
		
		appendStringInfoChar(str, ' ');
	}

	if (list_length(constraint->keys) > 0)
	{
		appendStringInfoChar(str, '(');
		foreach(lc, constraint->keys)
		{
			deparseNode(str, lfirst(lc), DEPARSE_NODE_CONTEXT_NONE);
			if (lnext(constraint->keys, lc))
				appendStringInfoString(str, ", ");
		}
		appendStringInfoString(str, ") ");
	}

	if (list_length(constraint->fk_attrs) > 0)
	{
		appendStringInfoChar(str, '(');
		foreach(lc, constraint->fk_attrs)
		{
			deparseNode(str, lfirst(lc), DEPARSE_NODE_CONTEXT_NONE);
			if (lnext(constraint->fk_attrs, lc))
				appendStringInfoString(str, ", ");
		}
		appendStringInfoString(str, ") ");
	}

	if (constraint->pktable != NULL)
	{
		appendStringInfoString(str, "REFERENCES ");
		deparseRangeVar(str, constraint->pktable);
		appendStringInfoString(str, " (");
		foreach(lc, constraint->pk_attrs)
		{
			deparseNode(str, lfirst(lc), DEPARSE_NODE_CONTEXT_NONE);
			if (lnext(constraint->pk_attrs, lc))
				appendStringInfoString(str, ", ");
		}
		appendStringInfoString(str, ") ");
	}

	if (constraint->skip_validation)
		appendStringInfoString(str, "NOT VALID ");
	
	if (constraint->indexname != NULL)
		appendStringInfo(str, "USING INDEX %s", constraint->indexname);
	
	removeTrailingSpace(str);
}

static void deparseCreateFunctionStmt(StringInfo str, CreateFunctionStmt *create_function_stmt)
{
	ListCell *lc;

	appendStringInfoString(str, "CREATE ");
	if (create_function_stmt->replace)
		appendStringInfoString(str, "OR REPLACE ");
	appendStringInfoString(str, "FUNCTION ");

	foreach(lc, create_function_stmt->funcname)
	{
		deparseNode(str, lfirst(lc), DEPARSE_NODE_CONTEXT_IDENTIFIER);
		if (lnext(create_function_stmt->funcname, lc))
			appendStringInfoString(str, ", ");
	}

	appendStringInfoChar(str, '(');
	foreach(lc, create_function_stmt->parameters)
	{
		deparseNode(str, lfirst(lc), DEPARSE_NODE_CONTEXT_NONE);
		if (lnext(create_function_stmt->parameters, lc))
			appendStringInfoString(str, ", ");
	}
	appendStringInfoString(str, ") ");

	appendStringInfoString(str, "RETURNS ");

	deparseTypeName(str, create_function_stmt->returnType);
	appendStringInfoChar(str, ' ');

	foreach(lc, create_function_stmt->options)
	{
		deparseNode(str, lfirst(lc), DEPARSE_NODE_CONTEXT_NONE);
		appendStringInfoChar(str, ' ');
	}

	removeTrailingSpace(str);
}

static void deparseFunctionParameter(StringInfo str, FunctionParameter *function_parameter)
{
	deparseTypeName(str, function_parameter->argType);
	// TODO: Review additional FunctionParameter fields
}

static void deparseDefElem(StringInfo str, DefElem *def_elem)
{
	ListCell *lc;
	if (strcmp(def_elem->defname, "as") == 0)
	{
		Assert(IsA(def_elem->arg, List));
		appendStringInfoString(str, "AS $$");
		foreach(lc, castNode(List, def_elem->arg))
		{
			deparseNode(str, lfirst(lc), DEPARSE_NODE_CONTEXT_NONE);
			if (lnext(castNode(List, def_elem->arg), lc))
				appendStringInfoChar(str, ' ');
		}
		appendStringInfoString(str, "$$");
	}
	else if (strcmp(def_elem->defname, "language") == 0)
	{
		appendStringInfoString(str, "language ");
		deparseNode(str, def_elem->arg, DEPARSE_NODE_CONTEXT_NONE);
	}
	else if (strcmp(def_elem->defname, "volatility") == 0)
	{
		Assert(IsA(def_elem->arg, String));
		char *volatility = pstrdup(strVal(def_elem->arg));
		for (unsigned char *p = (unsigned char *) volatility; *p; p++)
			*p = pg_toupper(*p);
		appendStringInfoString(str, volatility);
	}
	else if (strcmp(def_elem->defname, "strict") == 0)
	{
		Assert(IsA(def_elem->arg, Integer));
		if (intVal(def_elem->arg) == 1)
			appendStringInfoString(str, "RETURNS NULL ON NULL INPUT");
		else
			appendStringInfoString(str, "CALLED ON NULL INPUT");
	}
	else if (strcmp(def_elem->defname, "transaction_isolation") == 0)
	{
		appendStringInfoString(str, "ISOLATION LEVEL ");
		char *iso_level = pstrdup(strVal(&castNode(A_Const, def_elem->arg)->val));
		for (unsigned char *p = (unsigned char *) iso_level; *p; p++)
			*p = pg_toupper(*p);
		appendStringInfoString(str, iso_level);
	}
	else if (strcmp(def_elem->defname, "transaction_read_only") == 0 && intVal(&castNode(A_Const, def_elem->arg)->val) == 1)
	{
		appendStringInfoString(str, "READ ONLY");
	}
	else if (strcmp(def_elem->defname, "transaction_read_only") == 0 && intVal(&castNode(A_Const, def_elem->arg)->val) == 0)
	{
		appendStringInfoString(str, "READ WRITE");
	}
	else if (strcmp(def_elem->defname, "transaction_deferrable") == 0 && intVal(&castNode(A_Const, def_elem->arg)->val) == 1)
	{
		appendStringInfoString(str, "DEFERRABLE");
	}
	else if (strcmp(def_elem->defname, "transaction_deferrable") == 0 && intVal(&castNode(A_Const, def_elem->arg)->val) == 0)
	{
		appendStringInfoString(str, "NOT DEFERRABLE");
	}
	else
	{
		if (def_elem->defname != NULL)
			appendStringInfoString(str, def_elem->defname);
		if (def_elem->defname != NULL && def_elem->arg != NULL)
			appendStringInfoChar(str, '=');
		if (def_elem->arg != NULL)
			deparseNode(str, def_elem->arg, DEPARSE_NODE_CONTEXT_NONE);
	}
}

static void deparseCreateSchemaStmt(StringInfo str, CreateSchemaStmt *create_schema_stmt)
{
	ListCell *lc;

	appendStringInfoString(str, "CREATE SCHEMA ");

	if (create_schema_stmt->if_not_exists)
		appendStringInfoString(str, "IF NOT EXISTS ");

	if (create_schema_stmt->schemaname)
	{
		appendStringInfoString(str, quote_identifier(create_schema_stmt->schemaname));
		appendStringInfoChar(str, ' ');
	}
		
	if (create_schema_stmt->authrole != NULL)
	{
		appendStringInfoString(str, "AUTHORIZATION ");
		deparseRoleSpec(str, create_schema_stmt->authrole);
		appendStringInfoChar(str, ' ');
	}

	foreach(lc, create_schema_stmt->schemaElts)
	{
		deparseNode(str, lfirst(lc), DEPARSE_NODE_CONTEXT_NONE);
		if (lnext(create_schema_stmt->schemaElts, lc))
			appendStringInfoChar(str, ' ');
	}

	removeTrailingSpace(str);
}

static void deparseRoleSpec(StringInfo str, RoleSpec *role_spec)
{
	switch (role_spec->roletype)
	{
		case ROLESPEC_CSTRING:
			Assert(role_spec->rolename != NULL);
			appendStringInfoString(str, quote_identifier(role_spec->rolename));
			break;
		case ROLESPEC_CURRENT_USER:
			appendStringInfoString(str, "CURRENT_USER");
			break;
		case ROLESPEC_SESSION_USER:
			appendStringInfoString(str, "SESSION_USER");
			break;
		case ROLESPEC_PUBLIC:
			appendStringInfoString(str, "public");
			break;
	}
}

static void deparseCreateStmt(StringInfo str, CreateStmt *create_stmt)
{
	ListCell *lc;
	appendStringInfoString(str, "CREATE ");

	switch (create_stmt->relation->relpersistence)
	{
		case RELPERSISTENCE_PERMANENT:
			// Default
			break;
		case RELPERSISTENCE_UNLOGGED:
			appendStringInfoString(str, "UNLOGGED ");
			break;
		case RELPERSISTENCE_TEMP:
			appendStringInfoString(str, "TEMPORARY ");
			break;
		default:
			Assert(false);
			break;
	}

	appendStringInfoString(str, "TABLE ");

	if (create_stmt->if_not_exists)
		appendStringInfoString(str, "IF NOT EXISTS ");

	deparseRangeVar(str, create_stmt->relation);
	appendStringInfoString(str, " (");
	foreach(lc, create_stmt->tableElts)
	{
		deparseNode(str, lfirst(lc), DEPARSE_NODE_CONTEXT_NONE);
		if (lnext(create_stmt->tableElts, lc))
			appendStringInfoString(str, ", ");
	}
	appendStringInfoString(str, ") ");

	if (list_length(create_stmt->inhRelations) > 0)
	{
		appendStringInfoString(str, "INHERITS (");
		foreach(lc, create_stmt->inhRelations)
		{
			deparseNode(str, lfirst(lc), DEPARSE_NODE_CONTEXT_NONE);
			if (lnext(create_stmt->inhRelations, lc))
				appendStringInfoString(str, ", ");
		}
		appendStringInfoString(str, ") ");
	}

	removeTrailingSpace(str);
}

static void deparseCreateTableAsStmt(StringInfo str, CreateTableAsStmt *create_table_as_stmt)
{
	ListCell *lc;
	appendStringInfoString(str, "CREATE ");

	switch (create_table_as_stmt->into->rel->relpersistence)
	{
		case RELPERSISTENCE_PERMANENT:
			// Default
			break;
		case RELPERSISTENCE_UNLOGGED:
			appendStringInfoString(str, "UNLOGGED ");
			break;
		case RELPERSISTENCE_TEMP:
			appendStringInfoString(str, "TEMPORARY ");
			break;
		default:
			Assert(false);
			break;
	}

	appendStringInfoString(str, "TABLE ");

	deparseIntoClause(str, create_table_as_stmt->into);
	appendStringInfoChar(str, ' ');

	switch (create_table_as_stmt->into->onCommit)
	{
		case ONCOMMIT_NOOP:
			// Not specified
			break;
		case ONCOMMIT_PRESERVE_ROWS:
			appendStringInfoString(str, "ON COMMIT ");
			break;
		case ONCOMMIT_DELETE_ROWS:
			appendStringInfoString(str, "ON COMMIT DELETE ROWS ");
			break;
		case ONCOMMIT_DROP:
			appendStringInfoString(str, "ON COMMIT DROP ");
			break;
	}

	appendStringInfoString(str, "AS ");
	deparseNode(str, create_table_as_stmt->query, DEPARSE_NODE_CONTEXT_NONE);
}

static void deparseViewStmt(StringInfo str, ViewStmt *view_stmt)
{
	ListCell *lc;

	appendStringInfoString(str, "CREATE ");

	if (view_stmt->replace)
		appendStringInfoString(str, "OR REPLACE ");

	switch (view_stmt->view->relpersistence)
	{
		case RELPERSISTENCE_PERMANENT:
			// Default
			break;
		case RELPERSISTENCE_UNLOGGED:
			appendStringInfoString(str, "UNLOGGED ");
			break;
		case RELPERSISTENCE_TEMP:
			appendStringInfoString(str, "TEMPORARY ");
			break;
		default:
			Assert(false);
			break;
	}

	appendStringInfoString(str, "VIEW ");
	deparseRangeVar(str, view_stmt->view);
	appendStringInfoChar(str, ' ');

	if (list_length(view_stmt->aliases) > 0)
	{
		appendStringInfoChar(str, '(');
		foreach(lc, view_stmt->aliases)
		{
			deparseNode(str, lfirst(lc), DEPARSE_NODE_CONTEXT_NONE);
			if (lnext(view_stmt->aliases, lc))
				appendStringInfoString(str, ", ");
		}
		appendStringInfoString(str, ") ");
	}

	appendStringInfoString(str, "AS ");
	deparseNode(str, view_stmt->query, DEPARSE_NODE_CONTEXT_NONE);
	appendStringInfoChar(str, ' ');

	switch (view_stmt->withCheckOption)
	{
		case NO_CHECK_OPTION:
			// Default
			break;
		case LOCAL_CHECK_OPTION:
			appendStringInfoString(str, "WITH CHECK OPTION ");
			break;
		case CASCADED_CHECK_OPTION:
			appendStringInfoString(str, "WITH CASCADED CHECK OPTION ");
			break;
	}

	removeTrailingSpace(str);
}

static void deparseDropStmt(StringInfo str, DropStmt *drop_stmt)
{
	ListCell *lc;
	ListCell *lc2;

	appendStringInfoString(str, "DROP ");

	switch (drop_stmt->removeType)
	{
		case OBJECT_ACCESS_METHOD:
			appendStringInfoString(str, "ACCESS METHOD ");
			break;
		case OBJECT_AGGREGATE:
			appendStringInfoString(str, "AGGREGATE ");
			break;
		case OBJECT_AMOP:
			// TODO
			Assert(false);
			break;
		case OBJECT_AMPROC:
			// TODO
			Assert(false);
			break;
		case OBJECT_ATTRIBUTE:
			// TODO
			Assert(false);
			break;
		case OBJECT_CAST:
			appendStringInfoString(str, "CAST ");
			break;
		case OBJECT_COLUMN:
			// TODO
			Assert(false);
			break;
		case OBJECT_COLLATION:
			appendStringInfoString(str, "COLLATION ");
			break;
		case OBJECT_CONVERSION:
			appendStringInfoString(str, "CONVERSION ");
			break;
		case OBJECT_DATABASE:
			// TODO
			Assert(false);
			break;
		case OBJECT_DEFAULT:
			// TODO
			Assert(false);
			break;
		case OBJECT_DEFACL:
			// TODO
			Assert(false);
			break;
		case OBJECT_DOMAIN:
			appendStringInfoString(str, "DOMAIN ");
			break;
		case OBJECT_DOMCONSTRAINT:
			// TODO
			Assert(false);
			break;
		case OBJECT_EVENT_TRIGGER:
			appendStringInfoString(str, "EVENT TRIGGER ");
			break;
		case OBJECT_EXTENSION:
			appendStringInfoString(str, "EXTENSION ");
			break;
		case OBJECT_FDW:
			appendStringInfoString(str, "FOREIGN DATA WRAPPER ");
			break;
		case OBJECT_FOREIGN_SERVER:
			appendStringInfoString(str, "SERVER ");
			break;
		case OBJECT_FOREIGN_TABLE:
			appendStringInfoString(str, "FOREIGN TABLE ");
			break;
		case OBJECT_FUNCTION:
			appendStringInfoString(str, "FUNCTION ");
			break;
		case OBJECT_INDEX:
			appendStringInfoString(str, "INDEX ");
			break;
		case OBJECT_LANGUAGE:
			// TODO
			Assert(false);
			break;
		case OBJECT_LARGEOBJECT:
			// TODO
			Assert(false);
			break;
		case OBJECT_MATVIEW:
			appendStringInfoString(str, "MATERIALIZED VIEW ");
			break;
		case OBJECT_OPCLASS:
			appendStringInfoString(str, "OPERATOR CLASS ");
			break;
		case OBJECT_OPERATOR:
			// TODO
			Assert(false);
			break;
		case OBJECT_OPFAMILY:
			appendStringInfoString(str, "OPERATOR FAMILY ");
			break;
		case OBJECT_POLICY:
			appendStringInfoString(str, "POLICY ");
			break;
		case OBJECT_PROCEDURE:
			// TODO
			Assert(false);
			break;
		case OBJECT_PUBLICATION:
			appendStringInfoString(str, "PUBLICATION ");
			break;
		case OBJECT_PUBLICATION_REL:
			// TODO
			Assert(false);
			break;
		case OBJECT_ROLE:
			// TODO
			Assert(false);
			break;
		case OBJECT_ROUTINE:
			// TODO
			Assert(false);
			break;
		case OBJECT_RULE:
			appendStringInfoString(str, "RULE ");
			break;
		case OBJECT_SCHEMA:
			appendStringInfoString(str, "SCHEMA ");
			break;
		case OBJECT_SEQUENCE:
			appendStringInfoString(str, "SEQUENCE ");
			break;
		case OBJECT_SUBSCRIPTION:
			// TODO
			Assert(false);
			break;
		case OBJECT_STATISTIC_EXT:
			appendStringInfoString(str, "STATISTICS ");
			break;
		case OBJECT_TABCONSTRAINT:
			// TODO
			Assert(false);
			break;
		case OBJECT_TABLE:
			appendStringInfoString(str, "TABLE ");
			break;
		case OBJECT_TABLESPACE:
			// TODO
			Assert(false);
			break;
		case OBJECT_TRANSFORM:
			appendStringInfoString(str, "TRANSFORM ");
			break;
		case OBJECT_TRIGGER:
			appendStringInfoString(str, "TRIGGER ");
			break;
		case OBJECT_TSCONFIGURATION:
			appendStringInfoString(str, "TEXT SEARCH CONFIGURATION ");
			break;
		case OBJECT_TSDICTIONARY:
			appendStringInfoString(str, "TEXT SEARCH DICTIONARY ");
			break;
		case OBJECT_TSPARSER:
			appendStringInfoString(str, "TEXT SEARCH PARSER ");
			break;
		case OBJECT_TSTEMPLATE:
			appendStringInfoString(str, "TEXT SEARCH TEMPLATE ");
			break;
		case OBJECT_TYPE:
			appendStringInfoString(str, "TYPE ");
			break;
		case OBJECT_USER_MAPPING:
			// TODO
			Assert(false);
			break;
		case OBJECT_VIEW:
			appendStringInfoString(str, "VIEW ");
			break;
	}

	if (drop_stmt->concurrent)
		appendStringInfoString(str, "CONCURRENTLY ");

	if (drop_stmt->missing_ok)
		appendStringInfoString(str, "IF EXISTS ");

	switch (drop_stmt->removeType)
	{
		case OBJECT_CAST:
			Assert(list_length(drop_stmt->objects) == 1);
			Assert(list_length(linitial(drop_stmt->objects)) == 2);
			appendStringInfoChar(str, '(');
			deparseNode(str, linitial(linitial(drop_stmt->objects)), DEPARSE_NODE_CONTEXT_NONE);
			appendStringInfoString(str, " AS ");
			deparseNode(str, lsecond(linitial(drop_stmt->objects)), DEPARSE_NODE_CONTEXT_NONE);
			appendStringInfoChar(str, ')');
			break;
		case OBJECT_OPFAMILY:
		case OBJECT_OPCLASS:
			Assert(list_length(drop_stmt->objects) == 1);
			Assert(list_length(linitial(drop_stmt->objects)) >= 2);
			deparseNode(str, llast(linitial(drop_stmt->objects)), DEPARSE_NODE_CONTEXT_NONE);
			appendStringInfoString(str, " USING ");
			foreach(lc, linitial(drop_stmt->objects))
			{
				// Ignore last element
				if (lnext(linitial(drop_stmt->objects), lc))
				{
					deparseNode(str, lfirst(lc), DEPARSE_NODE_CONTEXT_NONE);
					if (foreach_current_index(lc) < list_length(linitial(drop_stmt->objects)) - 2)
						appendStringInfoChar(str, '.');
				}
			}
			break;
		case OBJECT_TRIGGER:
		case OBJECT_RULE:
		case OBJECT_POLICY:
			Assert(list_length(drop_stmt->objects) == 1);
			Assert(list_length(linitial(drop_stmt->objects)) >= 2);
			deparseNode(str, llast(linitial(drop_stmt->objects)), DEPARSE_NODE_CONTEXT_NONE);
			appendStringInfoString(str, " ON ");
			foreach(lc, linitial(drop_stmt->objects))
			{
				// Ignore last element
				if (lnext(linitial(drop_stmt->objects), lc))
				{
					deparseNode(str, lfirst(lc), DEPARSE_NODE_CONTEXT_NONE);
					if (foreach_current_index(lc) < list_length(linitial(drop_stmt->objects)) - 2)
						appendStringInfoChar(str, '.');
				}
			}
			break;
		case OBJECT_TRANSFORM:
			Assert(list_length(drop_stmt->objects) == 1);
			Assert(list_length(linitial(drop_stmt->objects)) == 2);
			appendStringInfoString(str, "FOR ");
			deparseNode(str, linitial(linitial(drop_stmt->objects)), DEPARSE_NODE_CONTEXT_NONE);
			appendStringInfoString(str, " LANGUAGE ");
			deparseNode(str, lsecond(linitial(drop_stmt->objects)), DEPARSE_NODE_CONTEXT_NONE);
			appendStringInfoChar(str, ' ');
			break;
		default:
			foreach(lc, drop_stmt->objects)
			{
				if (IsA(lfirst(lc), List))
				{
					foreach(lc2, lfirst(lc))
					{
						deparseNode(str, lfirst(lc2), DEPARSE_NODE_CONTEXT_NONE);
						if (lnext(lfirst(lc), lc2))
							appendStringInfoChar(str, '.');
					}
				}
				else
				{
					deparseNode(str, lfirst(lc), DEPARSE_NODE_CONTEXT_NONE);
				}
				if (lnext(drop_stmt->objects, lc))
					appendStringInfoString(str, ", ");
			}
			appendStringInfoChar(str, ' ');
	}

	switch (drop_stmt->behavior)
	{
		case DROP_RESTRICT:
			// Default
			break;
		case DROP_CASCADE:
			appendStringInfoString(str, "CASCADE ");
			break;
	}

	removeTrailingSpace(str);
}

static void deparseObjectWithArgs(StringInfo str, ObjectWithArgs *object_with_args)
{
	ListCell *lc;

	foreach(lc, object_with_args->objname)
	{
		deparseNode(str, lfirst(lc), DEPARSE_NODE_CONTEXT_NONE);
		if (lnext(object_with_args->objname, lc))
			appendStringInfoChar(str, '.');
	}

	if (!object_with_args->args_unspecified)
	{
		appendStringInfoChar(str, '(');
		foreach(lc, object_with_args->objargs)
		{
			deparseNode(str, lfirst(lc), DEPARSE_NODE_CONTEXT_NONE);
			if (lnext(object_with_args->objargs, lc))
				appendStringInfoString(str, ", ");
		}
		appendStringInfoChar(str, ')');
	}
}

static void deparseDropTableSpaceStmt(StringInfo str, DropTableSpaceStmt *drop_table_space_stmt)
{
	appendStringInfoString(str, "DROP TABLESPACE ");

	if (drop_table_space_stmt->missing_ok)
		appendStringInfoString(str, "IF EXISTS ");

	appendStringInfoString(str, drop_table_space_stmt->tablespacename);
}

static void deparseDropSubscriptionStmt(StringInfo str, DropSubscriptionStmt *drop_subscription_stmt)
{
	appendStringInfoString(str, "DROP SUBSCRIPTION ");

	if (drop_subscription_stmt->missing_ok)
		appendStringInfoString(str, "IF EXISTS ");

	appendStringInfoString(str, drop_subscription_stmt->subname);
}

static void deparseAlterTableStmt(StringInfo str, AlterTableStmt *alter_table_stmt)
{
	ListCell *lc;

	appendStringInfoString(str, "ALTER ");

	switch (alter_table_stmt->relkind)
	{
		case OBJECT_TABLE:
			appendStringInfoString(str, "TABLE ");
			break;
		case OBJECT_VIEW:
			appendStringInfoString(str, "VIEW ");
			break;
		default:
			Assert(false);
			break;
	}

	deparseRangeVar(str, alter_table_stmt->relation);
	appendStringInfoChar(str, ' ');

	foreach(lc, alter_table_stmt->cmds)
	{
		deparseNode(str, lfirst(lc), DEPARSE_NODE_CONTEXT_NONE);
		if (lnext(alter_table_stmt->cmds, lc))
			appendStringInfoString(str, ", ");
	}
}

static void deparseAlterTableCmd(StringInfo str, AlterTableCmd *alter_table_cmd)
{
	const char *options = NULL;

	switch (alter_table_cmd->subtype)
	{
		case AT_AddColumn:
			appendStringInfoString(str, "ADD COLUMN ");
			break;
		case AT_ColumnDefault:
			appendStringInfoString(str, "ALTER COLUMN ");
			if (alter_table_cmd->def != NULL)
				options = "SET DEFAULT";
			else
				options = "DROP DEFAULT";
			break;
		case AT_DropNotNull:
			appendStringInfoString(str, "ALTER COLUMN ");
			options = "DROP NOT NULL";
			break;
		case AT_SetNotNull:
			appendStringInfoString(str, "ALTER COLUMN ");
			options = "SET NOT NULL";
			break;
		case AT_SetStatistics:
			appendStringInfoString(str, "ALTER COLUMN ");
			options = "SET STATISTICS";
			break;
		case AT_SetOptions:
			appendStringInfoString(str, "ALTER COLUMN ");
			options = "SET";
			break;
		case AT_ResetOptions:
			appendStringInfoString(str, "ALTER COLUMN ");
			options = "RESET";
			break;
		case AT_SetStorage:
			appendStringInfoString(str, "ALTER COLUMN ");
			options = "SET STORAGE";
			break;
		case AT_DropColumn:
			appendStringInfoString(str, "DROP ");
			break;
		case AT_AddIndex:
			appendStringInfoString(str, "ADD INDEX ");
			break;
		case AT_AddConstraint:
			appendStringInfoString(str, "ADD ");
			break;
		case AT_AlterConstraint:
			appendStringInfoString(str, "ALTER CONSTRAINT ");
			break;
		case AT_ValidateConstraint:
			appendStringInfoString(str, "VALIDATE CONSTRAINT ");
			break;
		case AT_DropConstraint:
			appendStringInfoString(str, "DROP CONSTRAINT ");
			break;
		case AT_AlterColumnType:
			appendStringInfoString(str, "ALTER COLUMN ");
			options = "TYPE";
			break;
		case AT_AlterColumnGenericOptions:
			appendStringInfoString(str, "ALTER COLUMN ");
			options = "OPTIONS";
			break;
		default:
			// TODO: Support all alter commands
			Assert(false);
	}

	if (alter_table_cmd->missing_ok)
		appendStringInfoString(str, "IF EXISTS ");

	if (alter_table_cmd->name != NULL)
	{
		appendStringInfoString(str, quote_identifier(alter_table_cmd->name));
		appendStringInfoChar(str, ' ');
	}

	if (options != NULL)
	{
		appendStringInfoString(str, options);
		appendStringInfoChar(str, ' ');
	}

	if (alter_table_cmd->def != NULL)
	{
		deparseNode(str, alter_table_cmd->def, DEPARSE_NODE_CONTEXT_NONE);
		appendStringInfoChar(str, ' ');
	}

	switch (alter_table_cmd->behavior)
	{
		case DROP_RESTRICT:
			// Default
			break;
		case DROP_CASCADE:
			appendStringInfoString(str, "CASCADE ");
			break;
	}

	removeTrailingSpace(str);
}

static void deparseRenameStmt(StringInfo str, RenameStmt *rename_stmt)
{
	appendStringInfoString(str, "ALTER ");

	switch (rename_stmt->renameType)
	{
		case OBJECT_CONVERSION:
			appendStringInfoString(str, "CONVERSION ");
			deparseNode(str, rename_stmt->object, DEPARSE_NODE_CONTEXT_IDENTIFIER);
			appendStringInfoString(str, " RENAME ");
			break;
		case OBJECT_TABLE:
			appendStringInfoString(str, "TABLE ");
			deparseRangeVar(str, rename_stmt->relation);
			appendStringInfoString(str, " RENAME ");
			break;
		case OBJECT_TABCONSTRAINT:
			appendStringInfoString(str, "TABLE ");
			deparseRangeVar(str, rename_stmt->relation);
			appendStringInfoString(str, " RENAME CONSTRAINT ");
			appendStringInfoString(str, quote_identifier(rename_stmt->subname));
			appendStringInfoChar(str, ' ');
			break;
		case OBJECT_INDEX:
			appendStringInfoString(str, "INDEX ");
			deparseRangeVar(str, rename_stmt->relation);
			appendStringInfoString(str, " RENAME ");
			break;
		case OBJECT_MATVIEW:
			appendStringInfoString(str, "MATERIALIZED VIEW ");
			deparseRangeVar(str, rename_stmt->relation);
			appendStringInfoString(str, " RENAME ");
			break;
		case OBJECT_TABLESPACE:
			appendStringInfoString(str, "TABLESPACE ");
			appendStringInfoString(str, quote_identifier(rename_stmt->subname));
			appendStringInfoString(str, " RENAME ");
			break;
		case OBJECT_VIEW:
			appendStringInfoString(str, "VIEW ");
			deparseRangeVar(str, rename_stmt->relation);
			appendStringInfoString(str, " RENAME ");
			break;
		case OBJECT_COLUMN:
			appendStringInfoString(str, "TABLE ");
			deparseRangeVar(str, rename_stmt->relation);
			appendStringInfoString(str, " RENAME COLUMN ");
			appendStringInfoString(str, quote_identifier(rename_stmt->subname));
			appendStringInfoChar(str, ' ');
			break;
		case OBJECT_COLLATION:
			appendStringInfoString(str, "COLLATION ");
			deparseNode(str, rename_stmt->object, DEPARSE_NODE_CONTEXT_IDENTIFIER);
			appendStringInfoString(str, " RENAME ");
			break;
		case OBJECT_TYPE:
			appendStringInfoString(str, "TYPE ");
			deparseNode(str, rename_stmt->object, DEPARSE_NODE_CONTEXT_IDENTIFIER);
			appendStringInfoString(str, " RENAME ");
			break;
		case OBJECT_DOMCONSTRAINT:
			appendStringInfoString(str, "DOMAIN ");
			deparseNode(str, rename_stmt->object, DEPARSE_NODE_CONTEXT_IDENTIFIER);
			appendStringInfoString(str, " RENAME CONSTRAINT ");
			appendStringInfoString(str, quote_identifier(rename_stmt->subname));
			appendStringInfoChar(str, ' ');
			break;
		case OBJECT_RULE:
			appendStringInfoString(str, "RULE ");
			appendStringInfoString(str, quote_identifier(rename_stmt->subname));
			appendStringInfoString(str, " ON ");
			deparseRangeVar(str, rename_stmt->relation);
			appendStringInfoString(str, " RENAME ");
			break;
		case OBJECT_TRIGGER:
			appendStringInfoString(str, "TRIGGER ");
			appendStringInfoString(str, quote_identifier(rename_stmt->subname));
			appendStringInfoString(str, " ON ");
			deparseRangeVar(str, rename_stmt->relation);
			appendStringInfoString(str, " RENAME ");
			break;
		case OBJECT_AGGREGATE:
			appendStringInfoString(str, "AGGREGATE ");
			deparseNode(str, rename_stmt->object, DEPARSE_NODE_CONTEXT_IDENTIFIER);
			appendStringInfoString(str, " RENAME ");
			break;
		case OBJECT_FUNCTION:
			appendStringInfoString(str, "FUNCTION ");
			deparseNode(str, rename_stmt->object, DEPARSE_NODE_CONTEXT_IDENTIFIER);
			appendStringInfoString(str, " RENAME ");
			break;
		default:
			// TODO: Add additional object types
			Assert(false);
			break;
	}

	appendStringInfoString(str, "TO ");
	appendStringInfoString(str, quote_identifier(rename_stmt->newname));
}

static void deparseTransactionStmt(StringInfo str, TransactionStmt *transaction_stmt)
{
	ListCell *lc;
	switch (transaction_stmt->kind)
	{
		case TRANS_STMT_BEGIN:
			appendStringInfoString(str, "BEGIN ");
			foreach(lc, transaction_stmt->options) {
				deparseNode(str, lfirst(lc), DEPARSE_NODE_CONTEXT_NONE);
				if (lnext(transaction_stmt->options, lc))
					appendStringInfoString(str, ", ");
			}
			break;
		case TRANS_STMT_START:
			appendStringInfoString(str, "START TRANSACTION ");
			foreach(lc, transaction_stmt->options) {
				deparseNode(str, lfirst(lc), DEPARSE_NODE_CONTEXT_NONE);
				if (lnext(transaction_stmt->options, lc))
					appendStringInfoString(str, ", ");
			}
			break;
		case TRANS_STMT_COMMIT:
			appendStringInfoString(str, "COMMIT ");
			if (transaction_stmt->chain)
				appendStringInfoString(str, "AND CHAIN ");
			break;
		case TRANS_STMT_ROLLBACK:
			appendStringInfoString(str, "ROLLBACK ");
			if (transaction_stmt->chain)
				appendStringInfoString(str, "AND CHAIN ");
			break;
		case TRANS_STMT_SAVEPOINT:
			appendStringInfoString(str, "SAVEPOINT ");
			appendStringInfoString(str, quote_identifier(transaction_stmt->savepoint_name));
			break;
		case TRANS_STMT_RELEASE:
			appendStringInfoString(str, "RELEASE ");
			appendStringInfoString(str, quote_identifier(transaction_stmt->savepoint_name));
			break;
		case TRANS_STMT_ROLLBACK_TO:
			appendStringInfoString(str, "ROLLBACK ");
			appendStringInfoString(str, "TO SAVEPOINT ");
			appendStringInfoString(str, quote_identifier(transaction_stmt->savepoint_name));
			break;
		case TRANS_STMT_PREPARE:
			appendStringInfoString(str, "PREPARE TRANSACTION ");
			appendStringInfoString(str, quote_identifier(transaction_stmt->gid));
			break;
		case TRANS_STMT_COMMIT_PREPARED:
			appendStringInfoString(str, "COMMIT PREPARED ");
			appendStringInfoString(str, quote_identifier(transaction_stmt->gid));
			break;
		case TRANS_STMT_ROLLBACK_PREPARED:
			appendStringInfoString(str, "ROLLBACK PREPARED ");
			appendStringInfoString(str, quote_identifier(transaction_stmt->gid));
			break;
	}

	removeTrailingSpace(str);
}

static void deparseVariableSetStmt(StringInfo str, VariableSetStmt* variable_set_stmt)
{
	ListCell *lc;

	appendStringInfoString(str, "SET ");

	if (variable_set_stmt->is_local)
		appendStringInfoString(str, "LOCAL ");

	appendStringInfoString(str, quote_identifier(variable_set_stmt->name));
	appendStringInfoString(str, " TO ");

	foreach(lc, variable_set_stmt->args)
	{
		deparseNode(str, lfirst(lc), DEPARSE_NODE_CONTEXT_NONE);
		if (lnext(variable_set_stmt->args, lc))
			appendStringInfoString(str, ", ");
	}
}

static void deparseVacuumStmt(StringInfo str, VacuumStmt* vacuum_stmt)
{
	ListCell *lc = NULL;
	ListCell *lc2 = NULL;
	char *defname = NULL;

	appendStringInfoString(str, "VACUUM ");

	foreach(lc, vacuum_stmt->options)
	{
		Assert(IsA(lfirst(lc), DefElem));
		defname = pstrdup(castNode(DefElem, lfirst(lc))->defname);
		for (unsigned char *p = (unsigned char *) defname; *p; p++)
			*p = pg_toupper(*p);
		appendStringInfoString(str, defname);
		appendStringInfoChar(str, ' ');
		pfree(defname);
	}

	foreach(lc, vacuum_stmt->rels)
	{
		Assert(IsA(lfirst(lc), VacuumRelation));
		VacuumRelation *rel = castNode(VacuumRelation, lfirst(lc));

		deparseRangeVar(str, rel->relation);
		if (list_length(rel->va_cols) > 0)
		{
			appendStringInfoChar(str, '(');
			foreach(lc2, rel->va_cols)
			{
				deparseNode(str, lfirst(lc2), DEPARSE_NODE_CONTEXT_NONE);
				if (lnext(rel->va_cols, lc2))
					appendStringInfoString(str, ", ");
			}
			appendStringInfoChar(str, ')');
		}

		if (lnext(vacuum_stmt->rels, lc))
			appendStringInfoString(str, ", ");
	}

	removeTrailingSpace(str);
}

static void deparseLockStmt(StringInfo str, LockStmt *lock_stmt)
{
	ListCell *lc;

	appendStringInfoString(str, "LOCK TABLE ");

	foreach(lc, lock_stmt->relations)
	{
		deparseNode(str, lfirst(lc), DEPARSE_NODE_CONTEXT_NONE);
		if (lnext(lock_stmt->relations, lc))
			appendStringInfoString(str, ", ");
	}

	// TODO: mode
	// TODO: nowait
}

static void deparseExplainStmt(StringInfo str, ExplainStmt *explain_stmt)
{
	ListCell *lc = NULL;
	char *defname = NULL;
	bool need_parens = list_length(explain_stmt->options) > 1;

	appendStringInfoString(str, "EXPLAIN ");

	if (need_parens)
		appendStringInfoChar(str, '(');

	foreach(lc, explain_stmt->options)
	{
		Assert(IsA(lfirst(lc), DefElem));
		defname = pstrdup(castNode(DefElem, lfirst(lc))->defname);
		for (unsigned char *p = (unsigned char *) defname; *p; p++)
			*p = pg_toupper(*p);
		appendStringInfoString(str, defname);
		pfree(defname);
		if (lnext(explain_stmt->options, lc))
			appendStringInfoString(str, ", ");
	}

	if (need_parens)
		appendStringInfoChar(str, ')');

	removeTrailingSpace(str);
	appendStringInfoChar(str, ' ');
	deparseNode(str, explain_stmt->query, DEPARSE_NODE_CONTEXT_NONE);
}

static void deparseCopyStmt(StringInfo str, CopyStmt *copy_stmt)
{
	ListCell *lc;

	appendStringInfoString(str, "COPY ");

	if (copy_stmt->relation != NULL)
	{
		deparseRangeVar(str, copy_stmt->relation);
		if (list_length(copy_stmt->attlist) > 0)
		{
			appendStringInfoChar(str, '(');
			foreach(lc, copy_stmt->attlist)
			{
				deparseNode(str, lfirst(lc), DEPARSE_NODE_CONTEXT_NONE);
				if (lnext(copy_stmt->attlist, lc))
					appendStringInfoString(str, ", ");
			}
			appendStringInfoChar(str, ')');
		}
		appendStringInfoChar(str, ' ');
	}

	if (copy_stmt->query != NULL)
	{
		appendStringInfoChar(str, '(');
		deparseNode(str, copy_stmt->query, DEPARSE_NODE_CONTEXT_NONE);
		appendStringInfoString(str, ") ");
	}

	if (copy_stmt->is_from)
		appendStringInfoString(str, "FROM ");
	else
		appendStringInfoString(str, "TO ");

	if (copy_stmt->is_program)
		appendStringInfoString(str, "PROGRAM ");

	if (copy_stmt->filename != NULL)
	{
		deparseStringLiteral(str, copy_stmt->filename);
	}
	else
	{
		if (copy_stmt->is_from)
			appendStringInfoString(str, "STDIN");
		else
			appendStringInfoString(str, "STDOUT");
	}
}

static void deparseDoStmt(StringInfo str, DoStmt *do_stmt)
{
	ListCell *lc;

	appendStringInfoString(str, "DO ");

	foreach (lc, do_stmt->args)
	{
		DefElem *defel = castNode(DefElem, lfirst(lc));
		if (strcmp(defel->defname, "language") == 0)
		{
			appendStringInfoString(str, "LANGUAGE ");
			appendStringInfoString(str, quote_identifier(strVal(defel->arg)));
			appendStringInfoChar(str, ' ');
		}
		else if (strcmp(defel->defname, "as") == 0)
		{
			appendStringInfoString(str, "$$");
			appendStringInfoString(str, strVal(defel->arg));
			appendStringInfoString(str, "$$");
			appendStringInfoChar(str, ' ');
		}
	}

	removeTrailingSpace(str);
}

static void deparseDiscardStmt(StringInfo str, DiscardStmt *discard_stmt)
{
	appendStringInfoString(str, "DISCARD ");
	switch (discard_stmt->target)
	{
		case DISCARD_ALL:
			appendStringInfoString(str, "ALL");
			break;
		case DISCARD_PLANS:
			appendStringInfoString(str, "PLANS");
			break;
		case DISCARD_SEQUENCES:
			appendStringInfoString(str, "SEQUENCES");
			break;
		case DISCARD_TEMP:
			appendStringInfoString(str, "TEMP");
			break;
	}
}

static void deparseDefineStmt(StringInfo str, DefineStmt *define_stmt)
{
	ListCell *lc;

	appendStringInfoString(str, "CREATE ");

	// TODO: if_not_exists
	// TODO: replace

	switch (define_stmt->kind)
	{
		case OBJECT_AGGREGATE:
			appendStringInfoString(str, "AGGREGATE ");
			break;
		case OBJECT_OPERATOR:
			appendStringInfoString(str, "OPERATOR ");
			break;
		case OBJECT_TYPE:
			appendStringInfoString(str, "TYPE ");
			break;
		default:
			// This shouldn't happen
			Assert(false);
			break;
	}

	foreach(lc, define_stmt->defnames)
	{
		deparseNode(str, lfirst(lc), DEPARSE_NODE_CONTEXT_NONE);
		if (lnext(define_stmt->defnames, lc))
			appendStringInfoChar(str, '.');
	}
	appendStringInfoChar(str, ' ');

	/*
	 * Per gram.y for aggr_args:
	 *
	 * (*)									- normal agg with no args
	 * (aggr_arg,...)						- normal agg with args
	 * (ORDER BY aggr_arg,...)				- ordered-set agg with no direct args
	 * (aggr_arg,... ORDER BY aggr_arg,...)	- ordered-set agg with direct args
	 *
	 * ...
	 *
	 * The return value of this production is a two-element list, in which the
	 * first item is a sublist of FunctionParameter nodes (with any duplicate
	 * VARIADIC item already dropped, as per above) and the second is an integer
	 * Value node, containing -1 if there was no ORDER BY and otherwise the number
	 * of argument declarations before the ORDER BY.
	 */
	if (define_stmt->kind == OBJECT_AGGREGATE)
	{
		Assert(list_length(define_stmt->args) == 2);
		int order_by_idx = intVal(lsecond(define_stmt->args));
		appendStringInfoChar(str, '(');
		if (list_length(linitial(define_stmt->args)) > 0)
		{
			foreach(lc, linitial(define_stmt->args))
			{
				if (foreach_current_index(lc) == order_by_idx)
					appendStringInfoString(str, "ORDER BY ");

				deparseNode(str, lfirst(lc), DEPARSE_NODE_CONTEXT_NONE);

				if (foreach_current_index(lc) == order_by_idx - 1)
					appendStringInfoChar(str, ' ');
				else if (lnext(linitial(define_stmt->args), lc))
					appendStringInfoString(str, ", ");
			}
		}
		else
		{
			appendStringInfoChar(str, '*');
		}
		appendStringInfoString(str, ") ");
	}

	if (list_length(define_stmt->definition) > 0)
	{
		appendStringInfoChar(str, '(');
		foreach(lc, define_stmt->definition)
		{
			deparseNode(str, lfirst(lc), DEPARSE_NODE_CONTEXT_NONE);
			if (lnext(define_stmt->definition, lc))
					appendStringInfoString(str, ", ");
		}
		appendStringInfoString(str, ") ");
	}

	removeTrailingSpace(str);
}

static void deparseCompositeTypeStmt(StringInfo str, CompositeTypeStmt *composite_type_stmt)
{
	ListCell *lc;
	RangeVar *typevar;

	appendStringInfoString(str, "CREATE TYPE ");

	typevar = copyObject(composite_type_stmt->typevar);
	typevar->inh = true; // Avoid showing a bogus "ONLY" in the output
	deparseRangeVar(str, typevar);

	appendStringInfoString(str, " AS (");
	foreach(lc, composite_type_stmt->coldeflist)
	{
		deparseNode(str, lfirst(lc), DEPARSE_NODE_CONTEXT_NONE);
		if (lnext(composite_type_stmt->coldeflist, lc))
			appendStringInfoString(str, ", ");
	}
	appendStringInfoChar(str, ')');
}

static void deparseCreateEnumStmt(StringInfo str, CreateEnumStmt *create_enum_stmt)
{
	ListCell *lc;
	appendStringInfoString(str, "CREATE TYPE ");

	foreach(lc, create_enum_stmt->typeName)
	{
		deparseNode(str, lfirst(lc), DEPARSE_NODE_CONTEXT_NONE);
		if (lnext(create_enum_stmt->typeName, lc))
			appendStringInfoChar(str, '.');
	}
	appendStringInfoString(str, " AS ENUM (");
	foreach(lc, create_enum_stmt->vals)
	{
		deparseNode(str, lfirst(lc), DEPARSE_NODE_CONTEXT_CONSTANT);
		if (lnext(create_enum_stmt->vals, lc))
			appendStringInfoString(str, ", ");
	}
	appendStringInfoChar(str, ')');
}

static void deparseCreateRangeStmt(StringInfo str, CreateRangeStmt *create_range_stmt)
{
	ListCell *lc;
	appendStringInfoString(str, "CREATE TYPE ");

	foreach(lc, create_range_stmt->typeName)
	{
		deparseNode(str, lfirst(lc), DEPARSE_NODE_CONTEXT_NONE);
		if (lnext(create_range_stmt->typeName, lc))
			appendStringInfoChar(str, '.');
	}
	appendStringInfoString(str, " AS RANGE (");
	foreach(lc, create_range_stmt->params)
	{
		deparseNode(str, lfirst(lc), DEPARSE_NODE_CONTEXT_CONSTANT);
		if (lnext(create_range_stmt->params, lc))
			appendStringInfoString(str, ", ");
	}
	appendStringInfoChar(str, ')');
}

static void deparseGrantStmt(StringInfo str, GrantStmt *grant_stmt)
{
	ListCell *lc;

	if (grant_stmt->is_grant)
		appendStringInfoString(str, "GRANT ");
	else
		appendStringInfoString(str, "REVOKE ");

	if (list_length(grant_stmt->privileges) > 0)
	{
		foreach(lc, grant_stmt->privileges)
		{
			deparseNode(str, lfirst(lc), DEPARSE_NODE_CONTEXT_CONSTANT);
			if (lnext(grant_stmt->privileges, lc))
				appendStringInfoString(str, ", ");
		}
		appendStringInfoChar(str, ' ');
	}
	else
	{
		appendStringInfoString(str, "ALL ");
	}
	
	appendStringInfoString(str, "ON ");

	switch (grant_stmt->targtype)
	{
		case ACL_TARGET_OBJECT:
			switch (grant_stmt->objtype)
			{
				case OBJECT_TABLE:
					// Default object type
					break;
				case OBJECT_SEQUENCE:
					appendStringInfoString(str, "SEQUENCE ");
					break;
				case OBJECT_FDW:
					appendStringInfoString(str, "FOREIGN DATA WRAPPER ");
					break;
				case OBJECT_FOREIGN_SERVER:
					appendStringInfoString(str, "FOREIGN SERVER ");
					break;
				case OBJECT_FUNCTION:
					appendStringInfoString(str, "FUNCTION ");
					break;
				case OBJECT_PROCEDURE:
					appendStringInfoString(str, "PROCEDURE ");
					break;
				case OBJECT_ROUTINE:
					appendStringInfoString(str, "ROUTINE ");
					break;
				case OBJECT_DATABASE:
					appendStringInfoString(str, "DATABASE ");
					break;
				case OBJECT_DOMAIN:
					appendStringInfoString(str, "DOMAIN ");
					break;
				case OBJECT_LANGUAGE:
					appendStringInfoString(str, "LANGUAGE ");
					break;
				case OBJECT_LARGEOBJECT:
					appendStringInfoString(str, "LARGE OBJECT ");
					break;
				case OBJECT_SCHEMA:
					appendStringInfoString(str, "SCHEMA ");
					break;
				case OBJECT_TABLESPACE:
					appendStringInfoString(str, "TABLESPACE ");
					break;
				case OBJECT_TYPE:
					appendStringInfoString(str, "TYPE ");
					break;
				default:
					// Other types are not supported here
					Assert(false);
					break;
			}
			break;
		case ACL_TARGET_ALL_IN_SCHEMA:
			switch (grant_stmt->objtype)
			{
				case OBJECT_TABLE:
					appendStringInfoString(str, "ALL TABLES IN SCHEMA ");
					break;
				case OBJECT_SEQUENCE:
					appendStringInfoString(str, "ALL SEQUENCES IN SCHEMA ");
					break;
				case OBJECT_FUNCTION:
					appendStringInfoString(str, "ALL FUNCTIONS IN SCHEMA ");
					break;
				case OBJECT_PROCEDURE:
					appendStringInfoString(str, "ALL PROCEDURES IN SCHEMA ");
					break;
				case OBJECT_ROUTINE:
					appendStringInfoString(str, "ALL ROUTINES IN SCHEMA ");
					break;
				default:
					// Other types are not supported here
					Assert(false);
					break;
			}
			break;
		case ACL_TARGET_DEFAULTS:
			Assert(false);
			// TODO: Review this case
			break;
	}
	
	if (list_length(grant_stmt->objects) > 0)
	{
		foreach(lc, grant_stmt->objects)
		{
			deparseNode(str, lfirst(lc), DEPARSE_NODE_CONTEXT_IDENTIFIER);
			if (lnext(grant_stmt->objects, lc))
				appendStringInfoString(str, ", ");
		}
		appendStringInfoChar(str, ' ');
	}

	if (grant_stmt->is_grant)
		appendStringInfoString(str, "TO ");
	else
		appendStringInfoString(str, "FROM ");

	foreach(lc, grant_stmt->grantees)
	{
		deparseNode(str, lfirst(lc), DEPARSE_NODE_CONTEXT_CONSTANT);
		if (lnext(grant_stmt->grantees, lc))
			appendStringInfoChar(str, ',');
		appendStringInfoChar(str, ' ');
	}

	if (grant_stmt->grant_option)
		appendStringInfoString(str, "WITH GRANT OPTION ");

	// TODO: behavior

	removeTrailingSpace(str);
}

static void deparseAccessPriv(StringInfo str, AccessPriv *access_priv)
{
	ListCell *lc;

	appendStringInfoString(str, access_priv->priv_name);
	appendStringInfoChar(str, ' ');

	if (list_length(access_priv->cols) > 0)
	{
		appendStringInfoChar(str, '(');
		foreach(lc, access_priv->cols)
		{
			deparseNode(str, lfirst(lc), DEPARSE_NODE_CONTEXT_IDENTIFIER);
			if (lnext(access_priv->cols, lc))
				appendStringInfoString(str, ", ");
		}
		appendStringInfoChar(str, ')');
	}

	removeTrailingSpace(str);
}

static void deparseGrantRoleStmt(StringInfo str, GrantRoleStmt *grant_role_stmt)
{
	ListCell *lc;

	if (grant_role_stmt->is_grant)
		appendStringInfoString(str, "GRANT ");
	else
		appendStringInfoString(str, "REVOKE ");

	foreach(lc, grant_role_stmt->granted_roles)
	{
		deparseNode(str, lfirst(lc), DEPARSE_NODE_CONTEXT_IDENTIFIER);
		if (lnext(grant_role_stmt->granted_roles, lc))
			appendStringInfoChar(str, ',');
		appendStringInfoChar(str, ' ');
	}

	if (grant_role_stmt->is_grant)
		appendStringInfoString(str, "TO ");
	else
		appendStringInfoString(str, "FROM ");

	foreach(lc, grant_role_stmt->grantee_roles)
	{
		deparseNode(str, lfirst(lc), DEPARSE_NODE_CONTEXT_IDENTIFIER);
		if (lnext(grant_role_stmt->grantee_roles, lc))
			appendStringInfoChar(str, ',');
		appendStringInfoChar(str, ' ');
	}

	if (grant_role_stmt->admin_opt)
		appendStringInfoString(str, "WITH ADMIN OPTION ");

	removeTrailingSpace(str);
}

static void deparseDropRoleStmt(StringInfo str, DropRoleStmt *drop_role_stmt)
{
	ListCell *lc;

	appendStringInfoString(str, "DROP ROLE ");

	if (drop_role_stmt->missing_ok)
		appendStringInfoString(str, "IF EXISTS ");

	foreach(lc, drop_role_stmt->roles)
	{
		deparseNode(str, lfirst(lc), DEPARSE_NODE_CONTEXT_IDENTIFIER);
		if (lnext(drop_role_stmt->roles, lc))
			appendStringInfoString(str, ", ");
	}
}

static void deparseValue(StringInfo str, Value *value, DeparseNodeContext context)
{
	switch (nodeTag(value))
	{
		case T_Integer:
			appendStringInfo(str, "%d", value->val.ival);
			break;
		case T_Float:
			appendStringInfoString(str, value->val.str);
			break;
		case T_String:
			if (context == DEPARSE_NODE_CONTEXT_IDENTIFIER) {
				appendStringInfoString(str, quote_identifier(value->val.str));
			} else if (context == DEPARSE_NODE_CONTEXT_CONSTANT) {
				deparseStringLiteral(str, value->val.str);
			} else {
				appendStringInfoString(str, value->val.str);
			}
			break;
		case T_BitString:
			appendStringInfo(str, "B'%s'", value->val.str);
			break;
		case T_Null:
			appendStringInfoString(str, "NULL");
			break;
		default:
			elog(ERROR, "unrecognized value node type: %d",
				 (int) nodeTag(value));
			break;
	}
}

static void deparseNode(StringInfo str, Node *node, DeparseNodeContext context)
{
	if (node == NULL)
		return;
	
	switch (nodeTag(node))
	{
		case T_SelectStmt:
			deparseSelectStmt(str, (SelectStmt *) node);
			break;
		case T_ResTarget:
			deparseResTarget(str, (ResTarget *) node, context);
			break;
		case T_RawStmt:
			deparseRawStmt(str, (RawStmt *) node);
			break;
		case T_A_Const:
			deparseAConst(str, (A_Const *) node);
			break;
		case T_FuncCall:
			deparseFuncCall(str, (FuncCall *) node);
			break;
		case T_RangeVar:
			deparseRangeVar(str, (RangeVar *) node);
			break;
		case T_ColumnRef:
			deparseColumnRef(str, (ColumnRef *) node);
			break;
		case T_SubLink:
			deparseSubLink(str, (SubLink *) node);
			break;
		case T_A_Expr:
			deparseAExpr(str, (A_Expr *) node, context);
			break;
		case T_BoolExpr:
			deparseBoolExpr(str, (BoolExpr *) node);
			break;
		case T_A_Star:
			deparseAStar(str, (A_Star *) node);
			break;
		case T_CollateClause:
			deparseCollateClause(str, (CollateClause *) node);
			break;
		case T_SortBy:
			deparseSortBy(str, (SortBy *) node);
			break;
		case T_ParamRef:
			deparseParamRef(str, (ParamRef *) node);
			break;
		case T_SQLValueFunction:
			deparseSQLValueFunction(str, (SQLValueFunction *) node);
			break;
		case T_WithClause:
			deparseWithClause(str, (WithClause *) node);
			break;
		case T_JoinExpr:
			deparseJoinExpr(str, (JoinExpr *) node);
			break;
		case T_CommonTableExpr:
			deparseCommonTableExpr(str, (CommonTableExpr *) node);
			break;
		case T_RangeSubselect:
			deparseRangeSubselect(str, (RangeSubselect *) node);
			break;
		case T_RangeFunction:
			deparseRangeFunction(str, (RangeFunction *) node);
			break;
		case T_A_ArrayExpr:
			deparseAArrayExpr(str, (A_ArrayExpr *) node);
			break;
		case T_RowExpr:
			deparseRowExpr(str, (RowExpr *) node);
			break;
		case T_TypeCast:
			deparseTypeCast(str, (TypeCast *) node);
			break;
		case T_TypeName:
			deparseTypeName(str, (TypeName *) node);
			break;
		case T_NullTest:
			deparseNullTest(str, (NullTest *) node);
			break;
		case T_CaseExpr:
			deparseCaseExpr(str, (CaseExpr *) node);
			break;
		case T_CaseWhen:
			deparseCaseWhen(str, (CaseWhen *) node);
			break;
		case T_A_Indirection:
			deparseAIndirection(str, (A_Indirection *) node);
			break;
		case T_A_Indices:
			deparseAIndices(str, (A_Indices *) node);
			break;
		case T_CoalesceExpr:
			deparseCoalesceExpr(str, (CoalesceExpr *) node);
			break;
		case T_BooleanTest:
			deparseBooleanTest(str, (BooleanTest *) node);
			break;
		case T_ColumnDef:
			deparseColumnDef(str, (ColumnDef *) node);
			break;
		case T_InsertStmt:
			deparseInsertStmt(str, (InsertStmt *) node);
			break;
		case T_IndexElem:
			deparseIndexElem(str, (IndexElem *) node);
			break;
		case T_UpdateStmt:
			deparseUpdateStmt(str, (UpdateStmt *) node);
			break;
		case T_DeleteStmt:
			deparseDeleteStmt(str, (DeleteStmt *) node);
			break;
		case T_LockingClause:
			deparseLockingClause(str, (LockingClause *) node);
			break;
		case T_SetToDefault:
			deparseSetToDefault(str, (SetToDefault *) node);
			break;
		case T_CreateCastStmt:
			deparseCreateCastStmt(str, (CreateCastStmt *) node);
			break;
		case T_CreateDomainStmt:
			deparseCreateDomainStmt(str, (CreateDomainStmt *) node);
			break;
		case T_Constraint:
			deparseConstraint(str, (Constraint *) node);
			break;
		case T_CreateFunctionStmt:
			deparseCreateFunctionStmt(str, (CreateFunctionStmt *) node);
			break;
		case T_FunctionParameter:
			deparseFunctionParameter(str, (FunctionParameter *) node);
			break;
		case T_DefElem:
			deparseDefElem(str, (DefElem *) node);
			break;
		case T_CreateSchemaStmt:
			deparseCreateSchemaStmt(str, (CreateSchemaStmt *) node);
			break;
		case T_RoleSpec:
			deparseRoleSpec(str, (RoleSpec *) node);
			break;
		case T_CreateStmt:
			deparseCreateStmt(str, (CreateStmt *) node);
			break;
		case T_CreateTableAsStmt:
			deparseCreateTableAsStmt(str, (CreateTableAsStmt *) node);
			break;
		case T_ViewStmt:
			deparseViewStmt(str, (ViewStmt *) node);
			break;
		case T_DropStmt:
			deparseDropStmt(str, (DropStmt *) node);
			break;
		case T_ObjectWithArgs:
			deparseObjectWithArgs(str, (ObjectWithArgs *) node);
			break;
		case T_DropTableSpaceStmt:
			deparseDropTableSpaceStmt(str, (DropTableSpaceStmt *) node);
			break;
		case T_DropSubscriptionStmt:
			deparseDropSubscriptionStmt(str, (DropSubscriptionStmt *) node);
			break;
		case T_AlterTableStmt:
			deparseAlterTableStmt(str, (AlterTableStmt *) node);
			break;
		case T_AlterTableCmd:
			deparseAlterTableCmd(str, (AlterTableCmd *) node);
			break;
		case T_RenameStmt:
			deparseRenameStmt(str, (RenameStmt *) node);
			break;
		case T_TransactionStmt:
			deparseTransactionStmt(str, (TransactionStmt *) node);
			break;
		case T_VariableSetStmt:
			deparseVariableSetStmt(str, (VariableSetStmt *) node);
			break;
		case T_VacuumStmt:
			deparseVacuumStmt(str, (VacuumStmt *) node);
			break;
		case T_LockStmt:
			deparseLockStmt(str, (LockStmt *) node);
			break;
		case T_ExplainStmt:
			deparseExplainStmt(str, (ExplainStmt *) node);
			break;
		case T_CopyStmt:
			deparseCopyStmt(str, (CopyStmt *) node);
			break;
		case T_DoStmt:
			deparseDoStmt(str, (DoStmt *) node);
			break;
		case T_DiscardStmt:
			deparseDiscardStmt(str, (DiscardStmt *) node);
			break;
		case T_DefineStmt:
			deparseDefineStmt(str, (DefineStmt *) node);
			break;
		case T_CompositeTypeStmt:
			deparseCompositeTypeStmt(str, (CompositeTypeStmt *) node);
			break;
		case T_CreateEnumStmt:
			deparseCreateEnumStmt(str, (CreateEnumStmt *) node);
			break;
		case T_CreateRangeStmt:
			deparseCreateRangeStmt(str, (CreateRangeStmt *) node);
			break;
		case T_GrantStmt:
			deparseGrantStmt(str, (GrantStmt *) node);
			break;
		case T_AccessPriv:
			deparseAccessPriv(str, (AccessPriv *) node);
			break;
		case T_GrantRoleStmt:
			deparseGrantRoleStmt(str, (GrantRoleStmt *) node);
			break;
		case T_DropRoleStmt:
			deparseDropRoleStmt(str, (DropRoleStmt *) node);
			break;
		case T_Integer:
		case T_Float:
		case T_String:
		case T_BitString:
		case T_Null:
			deparseValue(str, (Value *) node, context);
			break;
		case T_List:
			{
				ListCell *lc;
				foreach(lc, (List *) node) {
					deparseNode(str, lfirst(lc), context);
					if (lnext((List *) node, lc))
						appendStringInfoString(str, " ");
				}
			}
			break;
		default:
			elog(ERROR, "unrecognized node type: %d",
				 (int) nodeTag(node));
			break;
	}
}

PgQueryDeparseResult pg_query_deparse_protobuf(PgQueryProtobuf parse_tree)
{
    PgQueryDeparseResult result = {0};
	StringInfoData str;
    MemoryContext ctx;
	List *stmts;
	ListCell *lc;

	ctx = pg_query_enter_memory_context();

	PG_TRY();
	{
		stmts = pg_query_protobuf_to_nodes(parse_tree);

		initStringInfo(&str);

		foreach(lc, stmts) {
			deparseNode(&str, lfirst(lc), DEPARSE_NODE_CONTEXT_NONE);
			if (lnext(stmts, lc))
				appendStringInfoString(&str, "; ");
		}
		result.query = strdup(str.data);
	}
	PG_CATCH();
	{
		ErrorData* error_data;
		PgQueryError* error;

		MemoryContextSwitchTo(ctx);
		error_data = CopyErrorData();

		// Note: This is intentionally malloc so exiting the memory context doesn't free this
		error = malloc(sizeof(PgQueryError));
		error->message   = strdup(error_data->message);
		error->filename  = strdup(error_data->filename);
		error->funcname  = strdup(error_data->funcname);
		error->context   = NULL;
		error->lineno    = error_data->lineno;
		error->cursorpos = error_data->cursorpos;

		result.error = error;
		FlushErrorState();
	}
	PG_END_TRY();

	pg_query_exit_memory_context(ctx);

    return result;
}

void pg_query_free_deparse_result(PgQueryDeparseResult result)
{
    if (result.error) {
        pg_query_free_error(result.error);
    }

    free(result.query);
}
