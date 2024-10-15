--
-- Tests for PL/pgSQL handling of array variables
--
-- We also check arrays of composites here, so this has some overlap
-- with the plpgsql_record tests.
--

create type complex as (r float8, i float8);
create type quadarray as (c1 complex[], c2 complex);

do $$ declare a int[];
begin a := array[1,2]; a[3] := 4; raise notice 'a = %', a; end$$;

do $$ declare a int[];
begin a[3] := 4; raise notice 'a = %', a; end$$;

do $$ declare a int[];
begin a[1][4] := 4; raise notice 'a = %', a; end$$;

do $$ declare a int[];
begin a[1] := 23::text; raise notice 'a = %', a; end$$;  -- lax typing

do $$ declare a int[];
begin a := array[1,2]; a[2:3] := array[3,4]; raise notice 'a = %', a; end$$;

do $$ declare a int[];
begin a := array[1,2]; a[2] := a[2] + 1; raise notice 'a = %', a; end$$;

do $$ declare a int[];
begin a[1:2] := array[3,4]; raise notice 'a = %', a; end$$;

do $$ declare a int[];
begin a[1:2] := 4; raise notice 'a = %', a; end$$;  -- error

do $$ declare a complex[];
begin a[1] := (1,2); a[1].i := 11; raise notice 'a = %', a; end$$;

do $$ declare a complex[];
begin a[1].i := 11; raise notice 'a = %, a[1].i = %', a, a[1].i; end$$;

-- perhaps this ought to work, but for now it doesn't:
do $$ declare a complex[];
begin a[1:2].i := array[11,12]; raise notice 'a = %', a; end$$;

do $$ declare a quadarray;
begin a.c1[1].i := 11; raise notice 'a = %, a.c1[1].i = %', a, a.c1[1].i; end$$;

do $$ declare a int[];
begin a := array_agg(x) from (values(1),(2),(3)) v(x); raise notice 'a = %', a; end$$;

create temp table onecol as select array[1,2] as f1;

do $$ declare a int[];
begin a := f1 from onecol; raise notice 'a = %', a; end$$;

do $$ declare a int[];
begin a := * from onecol for update; raise notice 'a = %', a; end$$;

-- error cases:

do $$ declare a int[];
begin a := from onecol; raise notice 'a = %', a; end$$;

do $$ declare a int[];
begin a := f1, f1 from onecol; raise notice 'a = %', a; end$$;

insert into onecol values(array[11]);

do $$ declare a int[];
begin a := f1 from onecol; raise notice 'a = %', a; end$$;

do $$ declare a int[];
begin a := f1 from onecol limit 1; raise notice 'a = %', a; end$$;

do $$ declare a real;
begin a[1] := 2; raise notice 'a = %', a; end$$;

do $$ declare a complex;
begin a.r[1] := 2; raise notice 'a = %', a; end$$;

--
-- test of %type[] and %rowtype[] syntax
--

-- check supported syntax
do $$
declare
  v int;
  v1 v%type;
  v2 v%type[];
  v3 v%type[1];
  v4 v%type[][];
  v5 v%type[1][3];
  v6 v%type array;
  v7 v%type array[];
  v8 v%type array[1];
  v9 v%type array[1][1];
  v10 pg_catalog.pg_class%rowtype[];
begin
  raise notice '%', pg_typeof(v1);
  raise notice '%', pg_typeof(v2);
  raise notice '%', pg_typeof(v3);
  raise notice '%', pg_typeof(v4);
  raise notice '%', pg_typeof(v5);
  raise notice '%', pg_typeof(v6);
  raise notice '%', pg_typeof(v7);
  raise notice '%', pg_typeof(v8);
  raise notice '%', pg_typeof(v9);
  raise notice '%', pg_typeof(v10);
end;
$$;

-- some types don't support arrays
do $$
declare
  v pg_node_tree;
  v1 v%type[];
begin
end;
$$;

-- check functionality
do $$
declare
  v1 int;
  v2 varchar;
  a1 v1%type[];
  a2 v2%type[];
begin
  v1 := 10;
  v2 := 'Hi';
  a1 := array[v1,v1];
  a2 := array[v2,v2];
  raise notice '% %', a1, a2;
end;
$$;

create table array_test_table(a int, b varchar);

insert into array_test_table values(1, 'first'), (2, 'second');

do $$
declare tg array_test_table%rowtype[];
begin
  tg := array(select array_test_table from array_test_table);
  raise notice '%', tg;
  tg := array(select row(a,b) from array_test_table);
  raise notice '%', tg;
end;
$$;
