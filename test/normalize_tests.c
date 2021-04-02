const char* tests[] = {
  "SELECT 1",
  "SELECT $1",
	"SELECT $1, 1",
	"SELECT $1, $2",
  "ALTER ROLE postgres LOGIN SUPERUSER PASSWORD 'xyz'",
  "ALTER ROLE postgres LOGIN SUPERUSER PASSWORD $1",
  "CREATE ROLE postgres ENCRYPTED PASSWORD 'xyz'",
  "CREATE ROLE postgres ENCRYPTED PASSWORD $1",
  "ALTER ROLE foo WITH PASSWORD 'bar' VALID UNTIL 'infinity'",
  "ALTER ROLE foo WITH PASSWORD $1 VALID UNTIL $2",
  // These below are as expected, though questionable if upstream shouldn't be
  // fixed as this could bloat pg_stat_statements
  "DECLARE cursor_b CURSOR FOR SELECT * FROM x WHERE id = 123",
  "DECLARE cursor_b CURSOR FOR SELECT * FROM x WHERE id = $1",
  "FETCH 1000 FROM cursor_a",
  "FETCH 1000 FROM cursor_a",
  "CLOSE cursor_a",
  "CLOSE cursor_a",
};

size_t testsLength = __LINE__ - 6;
