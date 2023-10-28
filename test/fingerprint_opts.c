#include <pg_query.h>
#include <pg_query_fingerprint.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fingerprint_opts_tests.c"

int main()
{
	size_t i;
	bool ret_code = 0;

	for (i = 0; i < testsLength; i += 3)
	{
		PgQueryParseMode mode = atoi(tests[i+1]);
		PgQueryFingerprintResult result = pg_query_fingerprint_opts(tests[i], mode);

		if (result.error)
		{
			ret_code = -1;
			printf("%s\n", result.error->message);
			pg_query_free_fingerprint_result(result);
			continue;
		}
		else if (strcmp(result.fingerprint_str, tests[i + 2]) == 0)
		{
			printf(".");
		}
		else
		{
			ret_code = -1;
			printf("INVALID result for \"%s\" with %d mode\nexpected: \"%s\"\nactual: \"%s\"\nactual tokens: ", tests[i], mode, tests[i + 2], result.fingerprint_str);
			pg_query_fingerprint_with_opts(tests[i], mode, true);
		}

		pg_query_free_fingerprint_result(result);
	}

	// Ensures that there isn't a memory leak in the error case
	PgQueryFingerprintResult result = pg_query_fingerprint("SELECT !");
	if (strcmp(result.error->message, "syntax error at end of input") != 0) {
		printf("\nERROR mismatch: %s\n", result.error->message);
		return EXIT_FAILURE;
	}
	pg_query_free_fingerprint_result(result);

	printf("\n");

	pg_query_exit();

	return ret_code;
}
