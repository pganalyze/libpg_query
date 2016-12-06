module.exports = function parse(sql) {
	// Create a pointer to pass to the parser
	var pointer = allocate(intArrayFromString(sql), 'i8', ALLOC_NORMAL);

	// Return the parse result
	return new Promise(function(resolve, reject) {
		var parsed = Module.parse(pointer);
		var tree   = JSON.parse(parsed['parse_tree']);

		if(tree.length) {
			resolve(tree, parsed);
		}
		else {
			reject(parsed.error);
		}
	});
};
