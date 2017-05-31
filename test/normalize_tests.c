const char* tests[] = {
  "SELECT 1",
  "SELECT $1",
	"SELECT $1, 1",
	"SELECT $1, $2",
  "ALTER ROLE postgres LOGIN SUPERUSER PASSWORD 'xyz'",
  "ALTER ROLE postgres LOGIN SUPERUSER PASSWORD $1"
};

size_t testsLength = __LINE__ - 6;
