root_dir := $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))

TARGET = pg_query
ARLIB = lib$(TARGET).a
PGDIR = $(root_dir)/postgres
PGDIRGZ = $(root_dir)/postgres.tar.gz

OBJS = pg_query.o \
pg_query_parse.o \
pg_query_normalize.o \
pg_polyfills.o

PGOBJS = $(PGDIR)/src/backend/utils/mb/wchar.o \
$(PGDIR)/src/backend/utils/mb/encnames.o \
$(PGDIR)/src/backend/utils/mb/mbutils.o \
$(PGDIR)/src/backend/utils/mmgr/mcxt.o \
$(PGDIR)/src/backend/utils/mmgr/aset.o \
$(PGDIR)/src/backend/utils/error/elog.o \
$(PGDIR)/src/backend/utils/init/globals.o \
$(PGDIR)/src/backend/utils/adt/name.o \
$(PGDIR)/src/backend/parser/gram.o \
$(PGDIR)/src/backend/parser/parser.o \
$(PGDIR)/src/backend/parser/keywords.o \
$(PGDIR)/src/backend/parser/kwlookup.o \
$(PGDIR)/src/backend/parser/scansup.o \
$(PGDIR)/src/backend/nodes/copyfuncs.o \
$(PGDIR)/src/backend/nodes/nodeFuncs.o \
$(PGDIR)/src/backend/nodes/makefuncs.o \
$(PGDIR)/src/backend/nodes/value.o \
$(PGDIR)/src/backend/nodes/list.o \
$(PGDIR)/src/backend/nodes/outfuncs_json.o \
$(PGDIR)/src/backend/lib/stringinfo.o \
$(PGDIR)/src/port/qsort.o \
$(PGDIR)/src/common/psprintf.o \
$(PGDIR)/src/timezone/pgtz.o

ALL_OBJS = $(OBJS) $(PGOBJS)

CFLAGS   = -I $(PGDIR)/src/include -O2 -Wall -Wmissing-prototypes -Wpointer-arith \
-Wdeclaration-after-statement -Wendif-labels -Wmissing-format-attribute \
-Wformat-security -fno-strict-aliasing -fwrapv
INCFLAGS = -I.
LIBPATH  = -L.
LIBS 		 = -lpthread -ldl -lobjc

CLEANLIBS = $(ARLIB)
CLEANOBJS = *.o
CLEANFILES = $(PGDIRGZ)

AR = ar rs
RM = rm -f
ECHO = echo

# FIXME: Should respect architecture
CC = clang
LDSHARED = $(CC) -dynamic -bundle

all: $(ARLIB)

clean:
	-@ $(RM) $(CLEANLIBS) $(CLEANOBJS) $(CLEANFILES)
	-@ $(RM) -r $(PGDIR)

.PHONY: all clean

$(PGDIR): $(PGDIRGZ)
	tar -xf $(PGDIRGZ)
	mv $(root_dir)/postgres-pg_query $(PGDIR)
	cd $(PGDIR); CFLAGS=-fPIC ./configure -q
	cd $(PGDIR); make -C src/backend lib-recursive
	cd $(PGDIR); make -C src/backend/utils/mb wchar.o encnames.o mbutils.o
	cd $(PGDIR); make -C src/backend/utils/mmgr mcxt.o aset.o
	cd $(PGDIR); make -C src/backend/utils/error elog.o
	cd $(PGDIR); make -C src/backend/utils/init globals.o
	cd $(PGDIR); make -C src/backend/utils/adt name.o
	cd $(PGDIR); make -C src/backend/parser gram.o parser.o keywords.o kwlookup.o scansup.o
	cd $(PGDIR); make -C src/backend/nodes copyfuncs.o nodeFuncs.o makefuncs.o value.o list.o outfuncs_json.o
	cd $(PGDIR); make -C src/backend/lib stringinfo.o
	cd $(PGDIR); make -C src/port qsort.o
	cd $(PGDIR); make -C src/common psprintf.o
	cd $(PGDIR); make -C src/timezone pgtz.o

$(PGDIRGZ):
	curl -o $(PGDIRGZ) https://codeload.github.com/pganalyze/postgres/tar.gz/pg_query

.c.o: $(PGDIR)
	@$(ECHO) compiling $(<)
	@$(CC) $(INCFLAGS) $(CPPFLAGS) $(CFLAGS) -o $@ -c $<

$(ARLIB): $(PGDIR) $(OBJS) Makefile
	@$(AR) $@ $(ALL_OBJS)
