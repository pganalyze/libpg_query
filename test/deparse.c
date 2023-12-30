#include <pg_query.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include "deparse_tests.c"

// Removes the location values from the JSON parse tree string, replacing them with nothing
// (we don't use any special replacement value to avoid increasing the string size)
void remove_node_locations(char *parse_tree_json)
{
	char *tokstart;
	char *p;
	size_t remaining_len;

	p = parse_tree_json;
	while ((p = strstr(p, "\"location\":")) != NULL)
	{
		tokstart = p;
		if (*(tokstart - 1) == ',')
			tokstart--;
		p += strlen("\"location\":");
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

int run_test(const char *query, bool compare_query_text) {
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
	PgQueryDeparseResult deparse_result = pg_query_deparse_protobuf(parse_result.parse_tree);
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
		printf("\nQUERY TEXT MISMATCH for \"%s\"\n  actual: \"%s\"\n  original parsetree: %s\n",
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

	pg_query_free_protobuf_parse_result(parse_result);
	pg_query_free_parse_result(parse_result_original);
	pg_query_free_parse_result(parse_result_deparse);
	pg_query_free_deparse_result(deparse_result);

	return ret_code;
}

int run_tests_from_file(const char * filename) {
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

		test_ret_code = run_test(query, false);
		if (test_ret_code != EXIT_SUCCESS)
			ret_code = test_ret_code;

		free(query);
	}

	pg_query_free_split_result(split_result);

	free(sample_buffer);
	close(fd);

	return ret_code;
}

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
	"xmlmap.sql"
};
size_t regressFilenameCount = sizeof(regressFilenames) / sizeof(regressFilenames[0]);

const char* plpgsqlRegressFilenames[] =
{
	"plpgsql_array.sql",
	"plpgsql_cache.sql",
	"plpgsql_call.sql",
	"plpgsql_control.sql",
	"plpgsql_domain.sql",
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
		test_ret_code = run_test(tests[i], true);
		if (test_ret_code != EXIT_SUCCESS)
			ret_code = test_ret_code;
	}

	for (i = 0; i < regressFilenameCount; i += 1) {
		printf("\n%s\n", regressFilenames[i]);
		char *filename = malloc(sizeof(char) * strlen("test/sql/postgres_regress/") + strlen(regressFilenames[i]) + 1);
		strcpy(filename, "test/sql/postgres_regress/");
		strcat(filename, regressFilenames[i]);
		test_ret_code = run_tests_from_file(filename);
		free(filename);
		if (test_ret_code != EXIT_SUCCESS)
			ret_code = test_ret_code;
	}

	for (i = 0; i < plpgsqlRegressFilenameCount; i += 1) {
		printf("\n%s\n", plpgsqlRegressFilenames[i]);
		char *filename = malloc(sizeof(char) * strlen("test/sql/postgres_regress/") + strlen(plpgsqlRegressFilenames[i]) + 1);
		strcpy(filename, "test/sql/plpgsql_regress/");
		strcat(filename, plpgsqlRegressFilenames[i]);
		test_ret_code = run_tests_from_file(filename);
		free(filename);
		if (test_ret_code != EXIT_SUCCESS)
			ret_code = test_ret_code;
	}

	printf("\n");

	pg_query_exit();

	return ret_code;
}
