#!/usr/bin/env pwsh

$functions = Get-Content pg_query.h | ForEach-Object {
    if ($_ -cmatch '\b(pg_query_\w+)\s*\(') {
        $fn = $matches[1]
        if ($fn -ne "pg_query_init") {
            "    $fn"
        }
    }
}

$output = @(
    "LIBRARY pg_query"
    "EXPORTS"
) + $functions

$output | Set-Content pg_query.def

