# libpg_query

C library for accessing the PostgreSQL parser outside of the server.

This library uses the actual PostgreSQL server source to parse SQL queries and return the internal PostgreSQL parse tree.

Note that this is mostly intended as a base library for https://github.com/lfittl/pg_query (Ruby) and https://github.com/lfittl/pg_query.go (Go).

You can find further background to why a query's parse tree is useful here: https://pganalyze.com/blog/parse-postgresql-queries-in-ruby.html


## Installation

```
cd $GOROOT/src/pkg
git clone git://github.com/lfittl/pg_query.go.git github.com/lfittl/pg_query.go
cd github.com/lfittl/pg_query.go
make
go build
```

Due to compiling parts of PostgreSQL, running `make` will take a while. Expect up to 5 minutes.

Note: On some Linux systems you'll have to install the ```flex``` and ```curl``` packages beforehand.


## Usage

### Parsing a query

Put the following in a new Go package, after having installed pg_query as above:

```go
package main

import (
  "fmt"
  pg_query "github.com/lfittl/pg_query.go"
)

func main() {
  tree := pg_query.Parse("SELECT 1")
  fmt.Printf("%s\n", tree)
}
```

Running will output the query's parse tree:

```json
$ go run main.go
[{"SELECT": {"distinctClause": null, "intoClause": null, "targetList": [{"RESTARGET": {"name": null, "indirection": null, "val": {"A_CONST": {"val": 1, "location": 7}}, "location": 7}}], "fromClause": null, "whereClause": null, "groupClause": null, "havingClause": null, "windowClause": null, "valuesLists": null, "sortClause": null, "limitOffset": null, "limitCount": null, "lockingClause": null, "withClause": null, "op": 0, "all": false, "larg": null, "rarg": null}}]
```


## Authors

- [Lukas Fittl](mailto:lukas@fittl.com)


## License

Copyright (c) 2015, Lukas Fittl <lukas@fittl.com><br>
libpg_query is licensed under the 3-clause BSD license, see LICENSE file for details.

Query normalization code:<br>
Copyright (c) 2008-2015, PostgreSQL Global Development Group
