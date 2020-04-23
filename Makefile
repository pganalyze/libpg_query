root_dir := $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))

TARGET = pg_query
ARLIB = lib$(TARGET).a
PGDIR = $(root_dir)/tmp/postgres
PGDIRBZ2 = $(root_dir)/tmp/postgres.tar.bz2

PG_VERSION = 12.1

SRC_FILES := $(wildcard src/*.c)
OBJ_FILES := $(SRC_FILES:.c=.o)
NOT_OBJ_FILES := src/pg_query_fingerprint_defs.o src/pg_query_fingerprint_conds.o src/pg_query_json_defs.o src/pg_query_json_conds.o src/postgres/guc-file.o src/postgres/scan.o src/pg_query_json_helper.o
OBJ_FILES := $(filter-out $(NOT_OBJ_FILES), $(OBJ_FILES))

CFLAGS  = -I. -I $(PGDIR)/src/pl/plpgsql/src/ -I $(PGDIR)/contrib/pgcrypto -I$(PGDIR)/src/include  -Wall -Wno-unused-function -Wno-unused-value -Wno-unused-variable -fno-strict-aliasing -fwrapv -fPIC -lm -ldl -lrt -pthread -flto -fvisibility=hidden -fdata-sections -ffunction-sections
LIBPATH = -L.
LDFLAGS = -Wl,--gc-sections,--as-needed

PG_CONFIGURE_FLAGS = -q --without-readline --without-zlib --without-icu --with-system-tzdata=/usr/share/zoneinfo
PG_CFLAGS = -fPIC -flto -fvisibility=hidden -fdata-sections -ffunction-sections -Os -pthread

ifeq ($(DEBUG),1)
	CFLAGS += -O0 -g
	PG_CONFIGURE_FLAGS += --enable-cassert --enable-debug
else
	CFLAGS += -g -Os -fno-inline
	PG_CFLAGS += -Os -g
endif

CLEANLIBS = $(ARLIB)
CLEANOBJS = $(OBJ_FILES)
CLEANFILES = $(PGDIRBZ2)

AR = gcc-ar
RM = rm -f
ECHO = echo


all: examples test build


build: $(ARLIB)


clean:
	-@ $(RM) $(CLEANLIBS) $(CLEANOBJS) $(EXAMPLES) $(TESTS)
	-@ $(RM) -rf {test,examples}/*.dSYM
	#-@ $(RM) -r $(PGDIR) $(PGDIRBZ2)

.PHONY: all clean build examples test

$(PGDIRBZ2):
	curl -o $(PGDIRBZ2) https://ftp.postgresql.org/pub/source/v$(PG_VERSION)/postgresql-$(PG_VERSION).tar.bz2

$(PGDIR): $(PGDIRBZ2)
	tar -xjf $(PGDIRBZ2)
	mv $(root_dir)/postgresql-$(PG_VERSION) $(PGDIR)
	cd $(PGDIR); patch -p1 < $(root_dir)/patches/00_disable_targets.patch
	cd $(PGDIR); patch -p1 < $(root_dir)/patches/01_parse_replacement_char.patch
	cd $(PGDIR); AR="$(AR)" CFLAGS="$(PG_CFLAGS)" LDFLAGS="$(LDFLAGS)" ./configure $(PG_CONFIGURE_FLAGS)
	cd $(PGDIR); patch -p1 < $(root_dir)/patches/02_visibility_marks.patch
	cd $(PGDIR); patch -p1 < $(root_dir)/patches/04_mock.patch
	cd $(PGDIR); patch -p1 < $(root_dir)/patches/05_gen_mriscript.patch
	cd $(PGDIR); patch -p1 < $(root_dir)/patches/06_pl_gram.patch
	cd $(PGDIR); patch -p1 < $(root_dir)/patches/07_thread_safety.patch
	cd $(PGDIR); make -C src/backend/ generated-headers
	cd $(PGDIR)/src/common/; make
	cd $(PGDIR)/src/backend/; make
	cd $(PGDIR)/contrib/pgcrypto/; make
	cd $(PGDIR); patch -p1 < $(root_dir)/patches/03_makefiles.patch




$(PGDIR)/src/backend/pglib.a: $(PGDIR)
	cd $(PGDIR)/src/backend; make pglib.a


libpg_query.so: $(OBJ_FILES)
	$(CC) $(CFLAGS) $(CPPFLAGS) -Wl,--gc-sections -shared $< $(LDFLAGS) -o $@

prepare_pg: $(PGDIR)

%.o: %.c $(PGDIR)
	@$(ECHO) compiling $(<)
	@$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ -c $< $(LDFLAGS)

$(ARLIB): $(PGDIR) $(OBJ_FILES) Makefile $(PGDIR)/src/backend/pglib.a
	rm $(ARLIB) -f
	$(AR) rsT $@ $(OBJ_FILES) $(PGDIR)/src/backend/pglib.a

EXAMPLES = examples/simple examples/normalize examples/simple_error examples/normalize_error examples/simple_plpgsql
examples: $(EXAMPLES)
	examples/simple
	examples/normalize
	examples/simple_error
	examples/normalize_error
	examples/simple_plpgsql

examples/simple: examples/simple.c $(ARLIB)
	$(CC) $(CFLAGS) -I. -o $@ -g examples/simple.c $(ARLIB) $(LDFLAGS)

examples/normalize: examples/normalize.c $(ARLIB)
	$(CC) $(CFLAGS) -I. -o $@ -g examples/normalize.c $(ARLIB) $(LDFLAGS)

examples/simple_error: examples/simple_error.c $(ARLIB)
	$(CC) $(CFLAGS) -I. -o $@ -g examples/simple_error.c $(ARLIB) $(LDFLAGS)

examples/normalize_error: examples/normalize_error.c $(ARLIB)
	$(CC) $(CFLAGS) -I. -o $@ -g examples/normalize_error.c $(ARLIB) $(LDFLAGS)

examples/simple_plpgsql: examples/simple_plpgsql.c $(ARLIB)
	$(CC) $(CFLAGS) -I. -o $@ -g examples/simple_plpgsql.c $(ARLIB) $(LDFLAGS)

TESTS = test/complex test/concurrency test/fingerprint test/normalize test/parse test/parse_plpgsql
test: $(TESTS)
	test/complex
	test/concurrency
	test/fingerprint
	test/normalize
	test/parse
	# Output-based tests
	test/parse_plpgsql
	diff -Naur test/plpgsql_samples.expected.json test/plpgsql_samples.actual.json

test/complex: test/complex.c $(ARLIB)
	$(CC) $(CFLAGS) -I. -Isrc -o $@ -g test/complex.c $(ARLIB) $(LDFLAGS)

test/concurrency: test/concurrency.c test/parse_tests.c $(ARLIB)
	$(CC) $(CFLAGS) -I. -o $@ -pthread -g test/concurrency.c $(ARLIB) $(LDFLAGS)

test/fingerprint: test/fingerprint.c test/fingerprint_tests.c $(ARLIB)
	$(CC) $(CFLAGS) -I. -Isrc -o $@ -g test/fingerprint.c $(ARLIB) $(LDFLAGS)

test/normalize: test/normalize.c test/normalize_tests.c $(ARLIB)
	$(CC) $(CFLAGS) -I. -Isrc -o $@ -g test/normalize.c $(ARLIB) $(LDFLAGS)

test/parse: test/parse.c test/parse_tests.c $(ARLIB)
	$(CC) $(CFLAGS) -I. -o $@ -g test/parse.c $(ARLIB) $(LDFLAGS)

test/parse_plpgsql: test/parse_plpgsql.c $(ARLIB)
	$(CC) $(CFLAGS) -I. -o $@ -I./src -I./src/postgres/include -g test/parse_plpgsql.c $(ARLIB) $(LDFLAGS)
