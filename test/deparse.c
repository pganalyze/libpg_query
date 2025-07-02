#include <pg_query.h>
#include <postgres_deparse.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include "deparse_tests.c"
#include "protobuf/pg_query.pb-c.h"

void remove_numeric_key(char *parse_tree_json, char* key)
{
	char *tokstart;
	char *p;
	size_t remaining_len;

	char search[100];

	sprintf(search, "\"%s\":", key);

	p = parse_tree_json;
	while ((p = strstr(p, search)) != NULL)
	{
		tokstart = p;
		if (*(tokstart - 1) == ',')
			tokstart--;
		p += strlen(search);
		if (*p == '-')
			p++;
		while (*p >= '0' && *p <= '9')
			p++;
		remaining_len = strlen(p);
		memmove(tokstart, p, remaining_len);
		p = tokstart;
		*(p + remaining_len) = '\0';
	}
}

// Removes the location values from the JSON parse tree string, replacing them with nothing
// (we don't use any special replacement value to avoid increasing the string size)
void remove_node_locations(char *parse_tree_json)
{
	remove_numeric_key(parse_tree_json, "location");
	remove_numeric_key(parse_tree_json, "name_location");
}

int run_test(const char *query, bool compare_query_text, bool pretty_print) {
	PgQueryProtobufParseResult parse_result = pg_query_parse_protobuf(query);
	if (parse_result.error) {
		if (!compare_query_text) { // Silently fail for regression tests which can contain intentional syntax errors
			pg_query_free_protobuf_parse_result(parse_result);
			return EXIT_SUCCESS;
		}
		printf("\nERROR for \"%s\"\n  %s\n", query, parse_result.error->message);
		pg_query_free_protobuf_parse_result(parse_result);
		return EXIT_FAILURE;
	}

	PgQueryParseResult parse_result_original = pg_query_parse(query);
	PgQueryDeparseCommentsResult comments_result = pg_query_deparse_comments_for_query(query);
	PostgresDeparseOpts deparse_opts = {0};
	deparse_opts.pretty_print = pretty_print;
	deparse_opts.trailing_newline = true;
	deparse_opts.comments = comments_result.comments;
	deparse_opts.comment_count = comments_result.comment_count;
	PgQueryDeparseResult deparse_result = pg_query_deparse_protobuf_opts(parse_result.parse_tree, deparse_opts);
	if (deparse_result.error) {
		printf("\nERROR for \"%s\"\n  %s\n  parsetree: %s\n",
			   query,
			   deparse_result.error->message,
			   parse_result_original.parse_tree);
		pg_query_free_protobuf_parse_result(parse_result);
		pg_query_free_deparse_result(deparse_result);
		pg_query_free_parse_result(parse_result_original);
		return EXIT_FAILURE;
	} else if (compare_query_text && strcmp(deparse_result.query, query) != 0) {
		printf("\nQUERY TEXT MISMATCH - expected:\n%s\n\nactual:\n%s\n\noriginal parsetree: %s\n",
			   query,
			   deparse_result.query,
			   parse_result_original.parse_tree);
		pg_query_free_protobuf_parse_result(parse_result);
		pg_query_free_deparse_result(deparse_result);
		pg_query_free_parse_result(parse_result_original);
		return EXIT_FAILURE;
	}

	// Compare the original and the deparsed parse tree, whilst ignoring location data
	int ret_code = EXIT_SUCCESS;
	PgQueryParseResult parse_result_deparse = pg_query_parse(deparse_result.query);
	if (parse_result_original.error) {
		ret_code = EXIT_FAILURE;
		printf("\nERROR for parsing \"%s\"\n  error: %s\n", query, parse_result_original.error->message);
	} else if (parse_result_deparse.error) {
		ret_code = EXIT_FAILURE;
		remove_node_locations(parse_result_deparse.parse_tree);
		printf("\nERROR for parsing deparse of \"%s\"\n  deparsed sql: %s\n  error: %s\n  original parsetree: %s\n",
			   query,
			   deparse_result.query,
			   parse_result_deparse.error->message,
			   parse_result_original.parse_tree);
	} else {
		remove_node_locations(parse_result_original.parse_tree);
		remove_node_locations(parse_result_deparse.parse_tree);

		if (strcmp(parse_result_original.parse_tree, parse_result_deparse.parse_tree) != 0) {
			ret_code = EXIT_FAILURE;
			printf("\nPARSETREE MISMATCH for parsing deparse of \"%s\"\n  deparsed sql: %s\n  original parsetree: %s\n  deparsed parsetree: %s\n",
				   query,
				   deparse_result.query,
				   parse_result_original.parse_tree,
				   parse_result_deparse.parse_tree);
		} else {
			printf(".");
		}
	}

	pg_query_free_deparse_comments_result(comments_result);
	pg_query_free_protobuf_parse_result(parse_result);
	pg_query_free_parse_result(parse_result_original);
	pg_query_free_parse_result(parse_result_deparse);
	pg_query_free_deparse_result(deparse_result);

	return ret_code;
}

int run_tests_from_file(const char * filename, bool compare_query_text, bool pretty_print) {
	char *sample_buffer;
	struct stat sample_stat;
	int fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0) {
		printf("\nERROR opening regression test file: %s\n", filename);
		return EXIT_FAILURE;
	}
	fstat(fd, &sample_stat);

	sample_buffer = malloc(sample_stat.st_size + 1);
	read(fd, sample_buffer, sample_stat.st_size);
	sample_buffer[sample_stat.st_size] = 0;

	if (sample_buffer == (void *) -1)
	{
		printf("Could not read samples file\n");
		close(fd);
		return EXIT_FAILURE;
	}

	char *sample_buffer_p = sample_buffer;

	// Special cases to avoid scanner errors
	if (strcmp(filename, "test/sql/postgres_regress/strings.sql") == 0)
	{
		// Skip early parts of the file that intentionally test "invalid Unicode escape" errors
		sample_buffer_p = strstr(sample_buffer_p, "-- bytea\n");
	}

	PgQuerySplitResult split_result = pg_query_split_with_scanner(sample_buffer_p);
	if (split_result.error != NULL)
	{
		printf("\nERROR splitting file \"%s\"\n  error: %s\n", filename, split_result.error->message);
		pg_query_free_split_result(split_result);
		free(sample_buffer);
		close(fd);
		return EXIT_FAILURE;
	}

	int ret_code = EXIT_SUCCESS;

	for (int i = 0; i < split_result.n_stmts; ++i)
	{
		int test_ret_code;
		char *query = malloc(split_result.stmts[i]->stmt_len + 1);

		memcpy(query, sample_buffer_p + split_result.stmts[i]->stmt_location, split_result.stmts[i]->stmt_len);
		query[split_result.stmts[i]->stmt_len] = 0;

		test_ret_code = run_test(query, compare_query_text, pretty_print);
		if (test_ret_code != EXIT_SUCCESS)
			ret_code = test_ret_code;

		free(query);
	}

	pg_query_free_split_result(split_result);

	free(sample_buffer);
	close(fd);

	return ret_code;
}

const char* deparseFilenames[] =
{
	"simple.sql",
	"case.sql",
	"nested_cte.sql",
	"union.sql",
	"union_2.sql",
	"comment_multiline.sql",
	"complex_depesz.sql",
	"complex_gitlab.sql",
	"complex_mattm.sql",
	"ddl_alter_table_add_constraint.sql",
	"ddl_create_index.sql",
	"ddl_create_table.sql",
	"ddl_create_trigger.sql",
	"ddl_create_type.sql",
	"insert_long.sql",
};
size_t deparseFilenameCount = sizeof(deparseFilenames) / sizeof(deparseFilenames[0]);

const char* deparseDepeszFilenames[] =
{
	"08-selects.d/01-numbers.psql",
	"08-selects.d/02-string.psql",
	"08-selects.d/03-sql-functions.psql",
	"08-selects.d/04-functions.psql",
	"08-selects.d/06-column-aliases.psql",
	"08-selects.d/07-casts.psql",
	"08-selects.d/08-fields-in-table.psql",
	"08-selects.d/09-operators.psql",
	"08-selects.d/10-operators.psql",
	"08-selects.d/11-weird-operator.psql",
	"08-selects.d/12-boolean-operation.psql",
	"08-selects.d/13-joins.psql",
	"08-selects.d/14-star.psql",
	"08-selects.d/15-where.psql",
	"08-selects.d/16-groupby.psql",
	"08-selects.d/17-orderby.psql",
	"08-selects.d/18-limitoffset.psql",
	"08-selects.d/19-having.psql",
	"08-selects.d/20-case.psql",
	"08-selects.d/21-in.psql", // TODO
	"08-selects.d/22-subselect.psql",
	"08-selects.d/23-null.psql",
	"08-selects.d/24-range-function.psql",
	"08-selects.d/25-coalesce.psql",
	"08-selects.d/26-range-subselect.psql",
	"08-selects.d/27-distinct.psql",
	"08-selects.d/28-distinct-on.psql",
	"08-selects.d/29-param-ref.psql",
	"08-selects.d/30-array.psql",
	"08-selects.d/31-indirection.psql",
	"08-selects.d/32-collate.psql",
	"08-selects.d/33-window-functions.psql",
	"08-selects.d/34-framed-functions.psql",
	"08-selects.d/35-setops.psql", // TODO
	"08-selects.d/36-values.psql",
	"08-selects.d/37-cte.psql",
	"08-selects.d/38-rcte.psql",
	"08-selects.d/39-any.psql",
	"08-selects.d/40-all.psql",
	"08-selects.d/41-special-a-expr.psql",
	"08-selects.d/42-minimax.psql",
	"08-selects.d/43-rowexpr.psql",
	"08-selects.d/44-bitstring.psql",
	"08-selects.d/45-grouping-sets.psql",
	"08-selects.d/46-cube.psql",
	"08-selects.d/47-rollup.psql",
	"08-selects.d/48-sublink-any-all.psql",
	"08-selects.d/49-variadic-func-call.psql",
	"09-inserts.d/01-basic.psql",
	"09-inserts.d/02-with-columns.psql",
	"09-inserts.d/03-many-columns.psql", // TODO
	"09-inserts.d/04-with-schema.psql",
	"09-inserts.d/05-multirow.psql",
	"09-inserts.d/06-returning-all.psql",
	"09-inserts.d/07-returning-some.psql",
	"09-inserts.d/08-default.psql",
	"09-inserts.d/09-cte.psql",
	"10-updates.d/01-single-column-no-where.psql",
	"10-updates.d/02-many-columns-and-where.psql",
	"10-updates.d/03-with.psql",
	"10-updates.d/04-returning-all.psql",
	"10-updates.d/05-returning-some.psql",
	"10-updates.d/06-multi-assign-simple.psql",
	"10-updates.d/07-multi-assign-long.psql",
	"10-updates.d/08-multi-assign-mix.psql",
	"10-updates.d/09-cte.psql",
	"10-updates.d/10-complex-where.psql",
	"11-deletes.d/01-simple.psql",
	"11-deletes.d/02-where.psql",
	"11-deletes.d/03-using.psql",
	"11-deletes.d/04-returning-all.psql",
	"11-deletes.d/05-returning-some.psql",
	"11-deletes.d/06-cte.psql",
	"11-deletes.d/07-complex-where.psql",
	"12-explains.d/01-base.psql", // TODO
	"12-explains.d/02-analyze.psql",
	"12-explains.d/03-verbose.psql",
	"12-explains.d/04-analyze-verbose.psql",
	"12-explains.d/05-other.psql",
	"13-tablesample.d/01-system.psql",
	"13-tablesample.d/02-bernoulli.psql",
	"13-tablesample.d/03-repeatable.psql",
	"14-xml.d/01-simple.psql",
	"14-xml.d/02-concat.psql",
	"14-xml.d/03-forest.psql",
	"14-xml.d/04-parse.psql",
	"14-xml.d/05-pi.psql",
	"14-xml.d/06-root.psql",
	"14-xml.d/07-serialize.psql",
	"14-xml.d/08-is-document.psql",
	"16-bugs.d/01-lateral.psql",
	"16-bugs.d/02-current-row.psql",
	"16-bugs.d/03-filtered-aggregates.psql",
	"16-bugs.d/04-cast-of-expression.psql",
	"16-bugs.d/05-literal-new-line.psql",
	"16-bugs.d/06-aggregate-filter-inside-case.psql",
	"16-bugs.d/07-missing-ordinality-and-order-by.psql",
	"16-bugs.d/08-missing-dot-before-start.psql",
	"16-bugs.d/09-missing-dot-before-column.psql",
	"16-bugs.d/10-missing-not.psql",
	"16-bugs.d/11-distinct-aggregate.psql",
	"17-locking-selects.d/01-for-update.psql",
	"17-locking-selects.d/02-for-no-key-update.psql",
	"17-locking-selects.d/03-for-share.psql",
	"17-locking-selects.d/04-for-key-share.psql",
	"17-locking-selects.d/05-of-table.psql",
	"17-locking-selects.d/06-of-tables.psql",
	"17-locking-selects.d/07-nowait.psql",
	"17-locking-selects.d/08-skip-locked.psql",
	"17-locking-selects.d/09-multi.psql",
	"18-conflicts.d/01-basic-nothing.psql",
	"18-conflicts.d/02-constraint-nothing.psql",
	"18-conflicts.d/03-columns-nothing.psql",
	"18-conflicts.d/04-expr-complex.psql",
	"18-conflicts.d/05-simple-update.psql",
	"18-conflicts.d/06-update-multicolumn.psql",
	"18-conflicts.d/07-update-complex.psql",
	"19-transactions.d/01-rollback.sql",
	"19-transactions.d/02-rollback_and_chain.sql",
	"19-transactions.d/03-commit.sql",
	"19-transactions.d/04-commit_and_chain.sql",
	"19-transactions.d/05-start_transaction.sql",
	"19-transactions.d/06-start_transaction_isolation_level_serializable.sql",
	"19-transactions.d/07-start_transaction_isolation_level_repeatable_read.sql",
	"19-transactions.d/08-start_transaction_isolation_level_read_committed.sql",
	"19-transactions.d/09-start_transaction_isolation_level_read_uncommitted.sql",
	"19-transactions.d/10-start_transaction_read_write.sql",
	"19-transactions.d/11-start_transaction_read_only.sql",
	"19-transactions.d/12-start_transaction_deferrable.sql",
	"19-transactions.d/13-start_transaction_not_deferrable.sql",
	"19-transactions.d/14-start_transaction_isolation_level_serializable,_deferrable.sql",
	"19-transactions.d/15-begin.sql",
	"19-transactions.d/16-begin_isolation_level_serializable.sql",
	"19-transactions.d/17-begin_isolation_level_repeatable_read.sql",
	"19-transactions.d/18-begin_isolation_level_read_committed.sql",
	"19-transactions.d/19-begin_isolation_level_read_uncommitted.sql",
	"19-transactions.d/20-begin_read_write.sql",
	"19-transactions.d/21-begin_read_only.sql",
	"19-transactions.d/22-begin_deferrable.sql",
	"19-transactions.d/23-begin_not_deferrable.sql",
	"19-transactions.d/24-begin_isolation_level_serializable,_deferrable.sql"
};
size_t deparseDepeszFilenameCount = sizeof(deparseDepeszFilenames) / sizeof(deparseDepeszFilenames[0]);

const char* regressFilenames[] = {
	"advisory_lock.sql",
	"aggregates.sql",
	"alter_generic.sql",
	"alter_operator.sql",
	"alter_table.sql",
	"amutils.sql",
	"arrays.sql",
	"async.sql",
	"bit.sql",
	"bitmapops.sql",
	"boolean.sql",
	"box.sql",
	"brin.sql",
	"brin_bloom.sql",
	"brin_multi.sql",
	"btree_index.sql",
	"case.sql",
	"char.sql",
	"circle.sql",
	"cluster.sql",
	"collate.icu.utf8.sql",
	"collate.linux.utf8.sql",
	"collate.sql",
	"collate.utf8.sql",
	"collate.windows.win1252.sql",
	"combocid.sql",
	"comments.sql",
	"compression.sql",
	"constraints.sql",
	"conversion.sql",
	"copy.sql",
	"copy2.sql",
	"copydml.sql",
	"copyselect.sql",
	"create_aggregate.sql",
	"create_am.sql",
	"create_cast.sql",
	"create_function_c.sql",
	"create_function_sql.sql",
	"create_index.sql",
	"create_index_spgist.sql",
	"create_misc.sql",
	"create_operator.sql",
	"create_procedure.sql",
	"create_role.sql",
	"create_schema.sql",
	"create_table.sql",
	"create_table_like.sql",
	"create_type.sql",
	"create_view.sql",
	"database.sql",
	"date.sql",
	"dbsize.sql",
	"delete.sql",
	"dependency.sql",
	"domain.sql",
	"drop_if_exists.sql",
	"drop_operator.sql",
	"enum.sql",
	"equivclass.sql",
	"errors.sql",
	"event_trigger.sql",
	"event_trigger_login.sql",
	"explain.sql",
	"expressions.sql",
	"fast_default.sql",
	"float4.sql",
	"float8.sql",
	"foreign_data.sql",
	"foreign_key.sql",
	"functional_deps.sql",
	"generated.sql",
	"geometry.sql",
	"gin.sql",
	"gist.sql",
	"groupingsets.sql",
	"guc.sql",
	"hash_func.sql",
	"hash_index.sql",
	"hash_part.sql",
	"horology.sql",
	"identity.sql",
	"incremental_sort.sql",
	"index_including.sql",
	"index_including_gist.sql",
	"indexing.sql",
	"indirect_toast.sql",
	"inet.sql",
	"infinite_recurse.sql",
	"inherit.sql",
	"init_privs.sql",
	"insert.sql",
	"insert_conflict.sql",
	"int2.sql",
	"int4.sql",
	"int8.sql",
	"interval.sql",
	"join.sql",
	"join_hash.sql",
	"json.sql",
	"json_encoding.sql",
	"jsonb.sql",
	"jsonb_jsonpath.sql",
	"jsonpath.sql",
	"jsonpath_encoding.sql",
	"largeobject.sql",
	"limit.sql",
	"line.sql",
	"lock.sql",
	"lseg.sql",
	"macaddr.sql",
	"macaddr8.sql",
	"matview.sql",
	"md5.sql",
	"memoize.sql",
	"merge.sql",
	"misc.sql",
	"misc_functions.sql",
	"misc_sanity.sql",
	"money.sql",
	"multirangetypes.sql",
	"mvcc.sql",
	"name.sql",
	"namespace.sql",
	"numeric.sql",
	"numeric_big.sql",
	"object_address.sql",
	"oid.sql",
	"oidjoins.sql",
	"opr_sanity.sql",
	"partition_aggregate.sql",
	"partition_info.sql",
	"partition_join.sql",
	"partition_prune.sql",
	"password.sql",
	"path.sql",
	"pg_lsn.sql",
	"plancache.sql",
	"plpgsql.sql",
	"point.sql",
	"polygon.sql",
	"polymorphism.sql",
	"portals.sql",
	"portals_p2.sql",
	"predicate.sql",
	"prepare.sql",
	"prepared_xacts.sql",
	"privileges.sql",
	"psql.sql",
	"psql_crosstab.sql",
	"publication.sql",
	"random.sql",
	"rangefuncs.sql",
	"rangetypes.sql",
	"regex.sql",
	"regproc.sql",
	"reindex_catalog.sql",
	"reloptions.sql",
	"replica_identity.sql",
	"returning.sql",
	"roleattributes.sql",
	"rowsecurity.sql",
	"rowtypes.sql",
	"rules.sql",
	"sanity_check.sql",
	"security_label.sql",
	"select.sql",
	"select_distinct.sql",
	"select_distinct_on.sql",
	"select_having.sql",
	"select_implicit.sql",
	"select_into.sql",
	"select_parallel.sql",
	"select_views.sql",
	"sequence.sql",
	"spgist.sql",
	"sqljson.sql",
	"sqljson_jsontable.sql",
	"sqljson_queryfuncs.sql",
	"stats.sql",
	"stats_ext.sql",
	"strings.sql",
	"subscription.sql",
	"subselect.sql",
	"sysviews.sql",
	"tablesample.sql",
	"tablespace.sql",
	"temp.sql",
	"test_setup.sql",
	"text.sql",
	"tid.sql",
	"tidrangescan.sql",
	"tidscan.sql",
	"time.sql",
	"timestamp.sql",
	"timestamptz.sql",
	"timetz.sql",
	"transactions.sql",
	"triggers.sql",
	"truncate.sql",
	"tsdicts.sql",
	"tsearch.sql",
	"tsrf.sql",
	"tstypes.sql",
	"tuplesort.sql",
	"txid.sql",
	"type_sanity.sql",
	"typed_table.sql",
	"unicode.sql",
	"union.sql",
	"updatable_views.sql",
	"update.sql",
	"uuid.sql",
	"vacuum.sql",
	"vacuum_parallel.sql",
	"varchar.sql",
	"window.sql",
	"with.sql",
	"write_parallel.sql",
	"xid.sql",
	"xml.sql",
	"xmlmap.sql",
};
size_t regressFilenameCount = sizeof(regressFilenames) / sizeof(regressFilenames[0]);

const char* plpgsqlRegressFilenames[] =
{
	"plpgsql_array.sql",
	"plpgsql_cache.sql",
	"plpgsql_call.sql",
	"plpgsql_control.sql",
	"plpgsql_copy.sql",
	"plpgsql_domain.sql",
	"plpgsql_misc.sql",
	"plpgsql_record.sql",
	"plpgsql_simple.sql",
	"plpgsql_transaction.sql",
	"plpgsql_trap.sql",
	"plpgsql_trigger.sql",
	"plpgsql_varprops.sql"
};
size_t plpgsqlRegressFilenameCount = sizeof(plpgsqlRegressFilenames) / sizeof(plpgsqlRegressFilenames[0]);

int main() {
	size_t i;
	int ret_code = EXIT_SUCCESS;
	int test_ret_code;

	for (i = 0; i < testsLength; i += 1) {
		test_ret_code = run_test(tests[i], true, false);
		if (test_ret_code != EXIT_SUCCESS)
			ret_code = test_ret_code;
	}

	for (i = 0; i < deparseFilenameCount; i += 1) {
		printf("\n%s\n", deparseFilenames[i]);
		char *filename = malloc(sizeof(char) * strlen("test/sql/deparse/") + strlen(deparseFilenames[i]) + 1);
		strcpy(filename, "test/sql/deparse/");
		strcat(filename, deparseFilenames[i]);
		test_ret_code = run_tests_from_file(filename, true, true);
		free(filename);
		if (test_ret_code != EXIT_SUCCESS)
			ret_code = test_ret_code;
	}

	for (i = 0; i < deparseDepeszFilenameCount; i += 1) {
		printf("\n%s\n", deparseDepeszFilenames[i]);
		char *filename = malloc(sizeof(char) * strlen("test/sql/deparse-depesz/") + strlen(deparseDepeszFilenames[i]) + 1);
		strcpy(filename, "test/sql/deparse-depesz/");
		strcat(filename, deparseDepeszFilenames[i]);
		test_ret_code = run_tests_from_file(filename, true, true);
		free(filename);
		if (test_ret_code != EXIT_SUCCESS)
			ret_code = test_ret_code;
	}

	for (i = 0; i < regressFilenameCount; i += 1) {
		printf("\n%s\n", regressFilenames[i]);
		char *filename = malloc(sizeof(char) * strlen("test/sql/postgres_regress/") + strlen(regressFilenames[i]) + 1);
		strcpy(filename, "test/sql/postgres_regress/");
		strcat(filename, regressFilenames[i]);
		test_ret_code = run_tests_from_file(filename, false, false);
		free(filename);
		if (test_ret_code != EXIT_SUCCESS)
			ret_code = test_ret_code;
	}

	for (i = 0; i < plpgsqlRegressFilenameCount; i += 1) {
		printf("\n%s\n", plpgsqlRegressFilenames[i]);
		char *filename = malloc(sizeof(char) * strlen("test/sql/postgres_regress/") + strlen(plpgsqlRegressFilenames[i]) + 1);
		strcpy(filename, "test/sql/plpgsql_regress/");
		strcat(filename, plpgsqlRegressFilenames[i]);
		test_ret_code = run_tests_from_file(filename, false, false);
		free(filename);
		if (test_ret_code != EXIT_SUCCESS)
			ret_code = test_ret_code;
	}

	printf("\n");

	pg_query_exit();

	return ret_code;
}
