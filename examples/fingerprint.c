#include <pg_query.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t testCount = 62;

const char* tests[] = {
  "SELECT 1",
  "8e1acac181c6d28f4a923392cf1c4eda49ee4cd2",
  "SELECT 2",
  "8e1acac181c6d28f4a923392cf1c4eda49ee4cd2",
  "SELECT ?",
  "8e1acac181c6d28f4a923392cf1c4eda49ee4cd2",
  "SELECT 1; SELECT a FROM b",
  "c8ff78820feae5ed6d7ca580c598f51e25aa2dbe",
  "SELECT COUNT(DISTINCT id), * FROM targets WHERE something IS NOT NULL AND elsewhere::interval < now()",
  "fbfa0619cd50c64ab1301830e8f3f55d6f1c81ff",
  "INSERT INTO test (a, b) VALUES (?, ?)",
  "7987d8bb26ed399b481728a6e8ca1b668f13d93e",
  "INSERT INTO test (b, a) VALUES (?, ?)",
  "7987d8bb26ed399b481728a6e8ca1b668f13d93e",
  "SELECT b AS x, a AS y FROM z",
  "b3a90446a1b17d7e89f211c28e791f45da72ca8b",
  "SELECT * FROM x WHERE y IN (?)",
  "68d00e0f1420c03fa1600ddf49455e068f6185c4",
  "SELECT * FROM x WHERE y IN (?, ?, ?)",
  "68d00e0f1420c03fa1600ddf49455e068f6185c4",
  "SELECT * FROM x WHERE y IN ( ?::uuid )",
  "949ab5b077dc2025b9bfc537fdcd678e42d042fd",
  "SELECT * FROM x WHERE y IN ( ?::uuid, ?::uuid, ?::uuid )",
  "949ab5b077dc2025b9bfc537fdcd678e42d042fd",
  "PREPARE a123 AS SELECT a",
  "0fd9ef315fb2409090b1c6457e3ff581018d3bed",
  "EXECUTE a123",
  "a936fb821c81d405a6834bd3a9ece412d2f8ce99",
  "DEALLOCATE a123",
  "387f1c2286cffa102e46dfc1b866e18ffc8c421f",
  "DEALLOCATE ALL",
  "387f1c2286cffa102e46dfc1b866e18ffc8c421f",
  "EXPLAIN ANALYZE SELECT a",
  "315ff6b68acdf887c8196fd2cb9ee7be506adf36",
  "WITH a AS (SELECT * FROM x WHERE x.y = ? AND x.z = 1) SELECT * FROM a",
  "fcf2500b7dcb8b030f3f00cb7c4f2dafd0dbca1c",
  "CREATE TABLE types (a float(2), b float(49), c NUMERIC(2, 3), d character(4), e char(5), f varchar(6), g character varying(7))",
  "8b9c10a0987ccba4f8d8263f3fa7e9e8095d6c58",
  "CREATE VIEW view_a (a, b) AS WITH RECURSIVE view_a (a, b) AS (SELECT * FROM a(1)) SELECT \"a\", \"b\" FROM \"view_a\"",
  "c1164d94a613858d257352dc6b7d3998d23cc27e",
  "VACUUM FULL my_table",
  "764cba2fdeb69c2136c4450280456af1cb0065d5",
  "SELECT * FROM x AS a, y AS b",
  "449b0e33058c2020cb901507428371e76dd1135c",
  "SELECT * FROM y AS a, x AS b",
  "449b0e33058c2020cb901507428371e76dd1135c",
  "SELECT x AS a, y AS b FROM x",
  "dff6cdb02bb700f67eb86d53a66fe5a527c04a5b",
  "SELECT y AS a, x AS b FROM x",
  "dff6cdb02bb700f67eb86d53a66fe5a527c04a5b",
  "SELECT x, y FROM z",
  "67ab69242d6b9daf09ea4e1ab11b0b90b53a2b15",
  "SELECT y, x FROM z",
  "67ab69242d6b9daf09ea4e1ab11b0b90b53a2b15",
  "INSERT INTO films (code, title, did) VALUES ('UA502', 'Bananas', 105), ('T_601', 'Yojimbo', DEFAULT)",
  "8658f8f49178096f7dd87f81ed184208efe7ed56",
  "INSERT INTO films (code, title, did) VALUES (?, ?, ?)",
  "8658f8f49178096f7dd87f81ed184208efe7ed56",
  "SELECT * FROM a",
  "1f3a0a714c4e3bbf38e9eab45104fe96f7746ab2",
  "SELECT * FROM a AS b",
  "1f3a0a714c4e3bbf38e9eab45104fe96f7746ab2",
};

int main() {
  size_t i;

  pg_query_init();

  for (i = 0; i < testCount; i += 2) {
    PgQueryFingerprintResult result = pg_query_fingerprint(tests[i]);

    if (strcmp(result.hexdigest, tests[i + 1]) == 0) {
      printf(".");
    } else {
      printf("INVALID (%s needs to be %s, SQL was: %s)\n", result.hexdigest, tests[i + 1], tests[i]);
      pg_query_fingerprint_with_opts(tests[i], true);
    }

    pg_query_free_fingerprint_result(result);
  }

  printf("\n");

  return 0;
}
