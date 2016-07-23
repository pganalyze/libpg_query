# Emscripten fork of [libpg_query](https://github.com/lfittl/libpg_query)

## Build Instructions:

- `$ emmake make build`
- `$ emcc -O2 -s EXPORTED_FUNCTIONS="['_parse']" libpg_query.a -o pgparse.js --post-js helper.js`