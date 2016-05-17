root_dir := $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))

TARGET = pg_query
ARLIB = lib$(TARGET).a
PGDIR = $(root_dir)/postgres
PGDIRBZ2 = $(root_dir)/postgres.tar.bz2

PG_VERSION = 9.5.3

OBJS = pg_query.o \
pg_query_parse.o \
pg_query_normalize.o \
pg_polyfills.o \
pg_query_json.o \
pg_query_fingerprint.o

PGOBJS = $(PGDIR)/src/backend/utils/mb/wchar.o \
$(PGDIR)/src/backend/libpq/pqformat.o \
$(PGDIR)/src/backend/utils/mb/encnames.o \
$(PGDIR)/src/backend/utils/mb/mbutils.o \
$(PGDIR)/src/backend/utils/mmgr/mcxt.o \
$(PGDIR)/src/backend/utils/mmgr/aset.o \
$(PGDIR)/src/backend/utils/error/elog.o \
$(PGDIR)/src/backend/utils/error/assert.o \
$(PGDIR)/src/backend/utils/init/globals.o \
$(PGDIR)/src/backend/utils/adt/datum.o \
$(PGDIR)/src/backend/utils/adt/name.o \
$(PGDIR)/src/backend/utils/adt/expandeddatum.o \
$(PGDIR)/src/backend/parser/gram.o \
$(PGDIR)/src/backend/parser/parser.o \
$(PGDIR)/src/backend/parser/keywords.o \
$(PGDIR)/src/backend/parser/kwlookup.o \
$(PGDIR)/src/backend/parser/scansup.o \
$(PGDIR)/src/backend/nodes/bitmapset.o \
$(PGDIR)/src/backend/nodes/copyfuncs.o \
$(PGDIR)/src/backend/nodes/equalfuncs.o \
$(PGDIR)/src/backend/nodes/nodeFuncs.o \
$(PGDIR)/src/backend/nodes/makefuncs.o \
$(PGDIR)/src/backend/nodes/value.o \
$(PGDIR)/src/backend/nodes/list.o \
$(PGDIR)/src/backend/lib/stringinfo.o \
$(PGDIR)/src/port/qsort.o \
$(PGDIR)/src/common/psprintf.o \
$(PGDIR)/contrib/pgcrypto/sha1.o

ALL_OBJS = $(OBJS) $(PGOBJS)

CFLAGS   = -I $(PGDIR)/src/include -I $(PGDIR)/src/timezone -I $(PGDIR)/contrib/pgcrypto -Wall -Wmissing-prototypes -Wpointer-arith \
-Wdeclaration-after-statement -Wendif-labels -Wmissing-format-attribute \
-Wformat-security -fno-strict-aliasing -fwrapv -fPIC
INCFLAGS = -I.
LIBPATH  = -L.

PG_CONFIGURE_FLAGS = -q --without-readline --without-zlib
PG_CFLAGS = -fPIC

ifeq ($(DEBUG),1)
	CFLAGS += -O0 -g
	PG_CONFIGURE_FLAGS += --enable-cassert --enable-debug
else
	CFLAGS += -O3
	PG_CFLAGS += -O3
endif

CLEANLIBS = $(ARLIB)
CLEANOBJS = *.o
CLEANFILES = $(PGDIRBZ2)

AR = ar rs
RM = rm -f
ECHO = echo

CC ?= cc

all: examples test $(ARLIB)

clean:
	-@ $(RM) $(CLEANLIBS) $(CLEANOBJS) $(CLEANFILES) $(EXAMPLES)
	-@ $(RM) -r $(PGDIR)

.PHONY: all clean examples test

$(PGDIR): $(PGDIRBZ2)
	tar -xjf $(PGDIRBZ2)
	mv $(root_dir)/postgresql-$(PG_VERSION) $(PGDIR)
	cd $(PGDIR); patch -p1 < $(root_dir)/patches/01_parse_replacement_char.patch
	cp $(root_dir)/patches/10_regenerated_bison_flex_files/gram.c $(PGDIR)/src/backend/parser
	cp $(root_dir)/patches/10_regenerated_bison_flex_files/scan.c $(PGDIR)/src/backend/parser
	cd $(PGDIR); CFLAGS="$(PG_CFLAGS)" ./configure $(PG_CONFIGURE_FLAGS)
	cd $(PGDIR); make -C src/backend lib-recursive
	cd $(PGDIR); make -C src/backend/libpq pqformat.o
	cd $(PGDIR); make -C src/backend/utils/mb wchar.o encnames.o mbutils.o
	cd $(PGDIR); make -C src/backend/utils/mmgr mcxt.o aset.o
	cd $(PGDIR); make -C src/backend/utils/error elog.o assert.o
	cd $(PGDIR); make -C src/backend/utils/init globals.o
	cd $(PGDIR); make -C src/backend/utils/adt datum.o name.o expandeddatum.o
	cd $(PGDIR); make -C src/backend/parser gram.o parser.o keywords.o kwlookup.o scansup.o
	cd $(PGDIR); make -C src/backend/nodes bitmapset.o copyfuncs.o equalfuncs.o nodeFuncs.o makefuncs.o value.o list.o
	cd $(PGDIR); make -C src/backend/lib stringinfo.o
	cd $(PGDIR); make -C src/port qsort.o
	cd $(PGDIR); make -C src/common psprintf.o
	cd $(PGDIR); make -C contrib/pgcrypto sha1.o

$(PGDIRBZ2):
	curl -o $(PGDIRBZ2) https://ftp.postgresql.org/pub/source/v$(PG_VERSION)/postgresql-$(PG_VERSION).tar.bz2

.c.o: $(PGDIR)
	@$(ECHO) compiling $(<)
	@$(CC) $(INCFLAGS) $(CPPFLAGS) $(CFLAGS) -o $@ -c $<

$(ARLIB): $(PGDIR) $(OBJS) Makefile
	@$(AR) $@ $(ALL_OBJS)

EXAMPLES = examples/simple examples/normalize examples/simple_error examples/normalize_error

pg_query_fingerprint.o: pg_query_fingerprint.c pg_query_fingerprint_defs.c pg_query_fingerprint_conds.c
pg_query_json.o: pg_query_json.c pg_query_json_defs.c pg_query_json_conds.c

examples: $(EXAMPLES)
	examples/simple
	examples/normalize
	examples/simple_error
	examples/normalize_error

examples/simple: examples/simple.c $(ARLIB)
	$(CC) -I. -L. -o $@ -g examples/simple.c $(ARLIB)

examples/normalize: examples/normalize.c $(ARLIB)
	$(CC) -I. -L. -o $@ -g examples/normalize.c $(ARLIB)

examples/simple_error: examples/simple_error.c $(ARLIB)
	$(CC) -I. -L. -o $@ -g examples/simple_error.c $(ARLIB)

examples/normalize_error: examples/normalize_error.c $(ARLIB)
	$(CC) -I. -L. -o $@ -g examples/normalize_error.c $(ARLIB)

TESTS = test/fingerprint test/parse

test: $(TESTS)
	test/fingerprint
	test/parse

test/fingerprint: test/fingerprint.c test/fingerprint_tests.c $(ARLIB)
	$(CC) -I. -L. -o $@ -g test/fingerprint.c $(ARLIB)

test/parse: test/parse.c test/parse_tests.c $(ARLIB)
	$(CC) -I. -L. -o $@ -g test/parse.c $(ARLIB)
