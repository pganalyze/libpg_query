#!/usr/bin/env bash
#
# Runs the patched gen_node_support.pl (see patches/13_gen_node_support_hook.patch)
# from an already-patched Postgres source tree, with scripts/node_support/hook.pl
# as its hook, to generate:
#
#   src/include/pg_query_fingerprint_defs.c
#   src/include/pg_query_fingerprint_conds.c
#
# Usage: ./scripts/generate_node_support.sh <postgres_source_dir>
#
# This is normally invoked via "make node_support", which ensures the patched
# source tree exists in tmp/postgres first.

set -euo pipefail

if [ $# -ne 1 ]; then
	echo "Usage: $0 <postgres_source_dir>" >&2
	exit 1
fi

pgsrc=$(cd "$1" && pwd)
here=$(cd "$(dirname "$0")/.." && pwd)

gen=$pgsrc/src/backend/nodes/gen_node_support.pl
incdir=$pgsrc/src/include

if [ ! -f "$gen" ]; then
	echo "error: $gen not found" >&2
	exit 1
fi

if ! grep -q 'hook-outdir' "$gen"; then
	echo "error: $gen does not support the --hook option" >&2
	echo "       (is patches/13_gen_node_support_hook.patch applied?)" >&2
	exit 1
fi

# Extract @all_input_files (the node headers, in the exact order the
# generator asserts) from the generator script itself, since the list
# changes between Postgres versions.
headers=()
while IFS= read -r h; do headers+=("$incdir/$h"); done < <(perl -ne '
	$in = 1 if /\@all_input_files\s*=\s*qw\(/;
	next unless $in;
	$in = 0, last if /^\s*\)\s*;/;
	while (/([\w\/]+\.h)/g) { print "$1\n"; }
' "$gen")

if [ ${#headers[@]} -eq 0 ]; then
	echo "error: could not extract input file list from $gen" >&2
	exit 1
fi

tmp=$(mktemp -d)
trap 'rm -rf "$tmp"' EXIT

(cd "$pgsrc/src/backend/nodes" && perl "$gen" \
	--outdir "$tmp" \
	--hook "$here/scripts/node_support/hook.pl" \
	--hook-outdir "$tmp" \
	"${headers[@]}")

cp "$tmp/pg_query_fingerprint_defs.c" "$here/src/include/pg_query_fingerprint_defs.c"
cp "$tmp/pg_query_fingerprint_conds.c" "$here/src/include/pg_query_fingerprint_conds.c"

echo "Generated src/include/pg_query_fingerprint_{defs,conds}.c"
