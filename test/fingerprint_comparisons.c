#include <pg_query.h>
#include "src/pg_query_summary.h"

#include <stdio.h>
#include <stdlib.h>

#include "test/framework/main.h"

#define TEST_ASSERT_FINGERPRINT_SAME(query1, query2) TEST_ASSERT_FINGERPRINT_SAME_impl(test_state, query1, query2)
void TEST_ASSERT_FINGERPRINT_SAME_impl(TestState* test_state, char* query1, char* query2) {
	PgQueryFingerprintResult result1 = pg_query_fingerprint(query1);
	PgQueryFingerprintResult result2 = pg_query_fingerprint(query2);

	if (result1.error)
		TEST_FAIL("  ERROR   result for \"%s\":\n %s\n", query1, result1.error->message);
	else if (result2.error)
		TEST_FAIL("  ERROR   result for \"%s\":\n %s\n", query2, result2.error->message);
	else if (strcmp(result1.fingerprint_str, result2.fingerprint_str) == 0)
	{
		printf(".");
		TEST_PASS();
	}
	else
		TEST_FAIL("  FAIL: fingerprints for \"%s\" (a) and \"%s\" (b) should be EQUAL.\n fingerprint for a: %s\n fingerprint for b: %s\n", query1, query2, result1.fingerprint_str, result2.fingerprint_str);

	pg_query_free_fingerprint_result(result1);
	pg_query_free_fingerprint_result(result2);
}

#define TEST_ASSERT_FINGERPRINT_DIFF(query1, query2) TEST_ASSERT_FINGERPRINT_DIFF_impl(test_state, query1, query2)
void TEST_ASSERT_FINGERPRINT_DIFF_impl(TestState* test_state, char* query1, char* query2) {
	PgQueryFingerprintResult result1 = pg_query_fingerprint(query1);
	PgQueryFingerprintResult result2 = pg_query_fingerprint(query2);

	if (result1.error)
		TEST_FAIL("  ERROR   result for \"%s\":\n %s\n", query1, result1.error->message);
	else if (result2.error)
		TEST_FAIL("  ERROR   result for \"%s\":\n %s\n", query2, result2.error->message);
	else if (strcmp(result1.fingerprint_str, result2.fingerprint_str) == 0)
		TEST_FAIL("  FAIL: fingerprints for \"%s\" (a) and \"%s\" (b) should be NOT EQUAL.\n fingerprint for a: %s\n fingerprint for b: %s\n", query1, query2, result1.fingerprint_str, result2.fingerprint_str);
	else
	{
		printf(".");
		TEST_PASS();
	}

	pg_query_free_fingerprint_result(result1);
	pg_query_free_fingerprint_result(result2);
}

#define TEST_ASSERT_FINGERPRINT_NORMALIZE_TO(query, result) TEST_ASSERT_FINGERPRINT_NORMALIZE_TO_impl(test_state, query, result)
void TEST_ASSERT_FINGERPRINT_NORMALIZE_TO_impl(TestState* test_state, char* query, char* result) {
	printf("TODO: implement TEST_ASSERT_FINGERPRINT_NORMALIZE_TO_impl()\n");
}

// Convenience method to make our intent clearer for tests that check the fingerprint is unchanged.
#define TEST_ASSERT_FINGERPRINT_NORMALIZE_UNCHANGED(query) TEST_ASSERT_FINGERPRINT_NORMALIZE_TO_impl(test_state, query, query)

void it_gives_same_fingerprints_only_when_it_should(TestState* test_state) {
	TEST_INIT();

	// Segments that are all numbers should be ignored.
	TEST_ASSERT_FINGERPRINT_SAME(
		"SELECT * FROM orders_2024_01",
		"SELECT * FROM orders_2024_02"
	);

	// Segments that are all numbers should be ignored.
	TEST_ASSERT_FINGERPRINT_SAME(
		"SELECT * FROM events_20231230",
		"SELECT * FROM events_20231231"
	);

	// FIXME: I think these are supposed to be the same? If so, there's an impl bug.
	TEST_ASSERT_FINGERPRINT_SAME(
		"SELECT * FROM calls_p20240301",
		"SELECT * FROM calls_p20240302"
	);

	// Something that's all letters should be treated verbatim.
	TEST_ASSERT_FINGERPRINT_DIFF(
		"SELECT * FROM default_partition",
		"SELECT * FROM default_partitions"
	);

	TEST_ASSERT_FINGERPRINT_DIFF(
		"SELECT * FROM oauth1_tokens",
		"SELECT * FROM oauth2_tokens"
	);

	TEST_ASSERT_FINGERPRINT_DIFF(
		"SELECT * FROM backup2024",
		"SELECT * FROM backup2025"
	);

	// v1 and v2 are only 2 chars long, so should be kept as-is.
	TEST_ASSERT_FINGERPRINT_DIFF(
		"SELECT * FROM api_v1",
		"SELECT * FROM api_v2"
	);

	// 9000 and 9001 are >2 chars long and all digts, so ignored.
	TEST_ASSERT_FINGERPRINT_SAME(
		"SELECT * FROM pump_9000",
		"SELECT * FROM pump_9001"
	);

	TEST_ASSERT_FINGERPRINT_SAME(
		"SELECT * FROM tenant1001_users",
		"SELECT * FROM tenant1002_users"
	);

	// <2 digit sequences are not ignored.
	TEST_ASSERT_FINGERPRINT_DIFF(
		"SELECT * FROM shard_4_accounts",
		"SELECT * FROM shard_5_accounts"
	);

	TEST_ASSERT_FINGERPRINT_DIFF(
		"SELECT * FROM a",
		"SELECT * FROM a_star"
	);

	TEST_ASSERT_FINGERPRINT_DIFF(
		"SELECT * FROM ab1c",
		"SELECT * FROM ab2c"
	);

	TEST_ASSERT_FINGERPRINT_DIFF(
		"SELECT * FROM ab1c",
		"SELECT * FROM abc2"
	);

	TEST_ASSERT_FINGERPRINT_SAME(
		"SELECT * FROM agg_data_20k",
		"SELECT * FROM agg_data_2k"
	);

	TEST_ASSERT_FINGERPRINT_SAME(
		"SELECT * FROM alter_idx_rename_test",
		"SELECT * FROM alter_idx_rename_test_parted"
	);

	TEST_ASSERT_FINGERPRINT_SAME(
		"SELECT * FROM alterlock2",
		"SELECT * FROM alterlock3"
	);

	TEST_ASSERT_FINGERPRINT_DIFF(
		"SELECT * FROM am_partitioned_5p1",
		"SELECT * FROM am_partitioned_6p1"
	);

	TEST_ASSERT_FINGERPRINT_SAME(
		"SELECT * FROM am_partitioned_5p1",
		"SELECT * FROM am_partitioned_5p2"
	);

	// rangep_0_to_200 should match rangep_0_to_100.
	TEST_ASSERT_FINGERPRINT_SAME(
		"SELECT * FROM rangep_0_to_100",
		"SELECT * FROM rangep_0_to_200"
	);

	// Since 1 and 2 are only one digit, they're left alone.
	TEST_ASSERT_FINGERPRINT_DIFF(
		"SELECT * FROM rangep_0_to_100_1",
		"SELECT * FROM rangep_0_to_100_2"
	);

	// Since 0 is only one digit, it's left alone.
	TEST_ASSERT_FINGERPRINT_DIFF(
		"SELECT * FROM rangep_0_to_200",
		"SELECT * FROM rangep_100_to_200"
	);

	TEST_ASSERT_FINGERPRINT_DIFF(
		"SELECT * FROM temporal_fk2_mltrng2mltrng",
		"SELECT * FROM temporal_fk2_rng2rng"
	);

	TEST_ASSERT_FINGERPRINT_DIFF(
		"SELECT * FROM temporal_partitioned_fk_mltrng2mltrng",
		"SELECT * FROM temporal_partitioned_fk_rng2rng"
	);

	TEST_ASSERT_FINGERPRINT_DIFF(
		"SELECT * FROM tenk1",
		"SELECT * FROM tenk2"
	);

	TEST_ASSERT_FINGERPRINT_NORMALIZE_TO(
		"SELECT * FROM plt1_adv_p1_null",
		"SELECT * FROM plt1_adv_p1_null"
	);

	TEST_ASSERT_FINGERPRINT_SAME(
		"SELECT * FROM plt2_adv_p2_1",
		"SELECT * FROM plt2_adv_p2_2"
	);
}

void it_normalizes_to_correct_value(TestState* test_state) {
	TEST_INIT();

	TEST_ASSERT_FINGERPRINT_NORMALIZE_TO(
		"SELECT * FROM orders_2024_01",
		"SELECT * FROM orders__"
	);

	TEST_ASSERT_FINGERPRINT_NORMALIZE_TO(
		"SELECT * FROM events_20231231",
		"SELECT * FROM events_"
	);

	TEST_ASSERT_FINGERPRINT_NORMALIZE_TO(
		"SELECT * FROM calls_p20240301",
		"SELECT * FROM calls_"
	);

	TEST_ASSERT_FINGERPRINT_NORMALIZE_UNCHANGED(
		"SELECT * FROM default_partition"
	);

	TEST_ASSERT_FINGERPRINT_NORMALIZE_UNCHANGED(
		"SELECT * FROM tenant1001_users"
	);

	TEST_ASSERT_FINGERPRINT_NORMALIZE_UNCHANGED(
		"SELECT * FROM shard_4_accounts"
	);

	TEST_ASSERT_FINGERPRINT_NORMALIZE_UNCHANGED(
		"SELECT * FROM tenant1001_users"
	);

	TEST_ASSERT_FINGERPRINT_NORMALIZE_UNCHANGED(
		"SELECT * FROM temporal_fk2_mltrng2mltrng"
	);

	TEST_ASSERT_FINGERPRINT_NORMALIZE_UNCHANGED(
		"SELECT * FROM temporal_fk2_rng2rng"
	);

	TEST_ASSERT_FINGERPRINT_NORMALIZE_UNCHANGED(
		"SELECT * FROM rparted_by_int2_maxvalue"
	);

	TEST_ASSERT_FINGERPRINT_NORMALIZE_UNCHANGED(
		"SELECT * FROM rf_tbl_abcd_part_pk_1"
	);

	TEST_ASSERT_FINGERPRINT_NORMALIZE_UNCHANGED(
		"SELECT * FROM part_column_drop_1_10"
	);

	TEST_ASSERT_FINGERPRINT_NORMALIZE_UNCHANGED(
		"SELECT * FROM parted2_stmt_trig1"
	);

	TEST_ASSERT_FINGERPRINT_NORMALIZE_UNCHANGED(
		"SELECT * FROM pitest1_p1_like"
	);
	TEST_ASSERT_FINGERPRINT_NORMALIZE_UNCHANGED(
		"SELECT * FROM plt1_adv_p1_null"
	);

	TEST_ASSERT_FINGERPRINT_NORMALIZE_UNCHANGED(
		"SELECT * FROM plt2_adv_p1_null"
	);

	TEST_ASSERT_FINGERPRINT_NORMALIZE_UNCHANGED(
		"SELECT * FROM plt2_adv_p2_1"
	);

	TEST_ASSERT_FINGERPRINT_NORMALIZE_UNCHANGED(
		"SELECT * FROM plt2_adv_p2_2"
	);

	TEST_ASSERT_FINGERPRINT_NORMALIZE_UNCHANGED(
		"SELECT * FROM pp_intrangepart2inf"
	);
}



static void
test_cleanup(void)
{
}

int
main(int argc, char *argv[])
{
	TestFn	   *tests[] = {
		&it_gives_same_fingerprints_only_when_it_should,
		&it_normalizes_to_correct_value,
		NULL
	};

	return test_run_with_mcxt(argc, argv, tests, &test_cleanup);
}
