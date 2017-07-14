/*
 * Common error.
 */
function constfuncs() {
	var funcs = [];
	/* 'i' is visible to all inside the function. */
	for (var i = 0; i < 10; i++) 
		funcs[i] = function() { return i; };
	return funcs;
}

var funcs = constfuncs();
for (var i = 0; i < 10; i++) {
	/* Prints 10, no matter what element is. */
	console.log(funcs[i]());
}

/* Modified */
function constfunc(v) { return function() { return v; }; }

var list = [];
for (var i = 0; i < 10; i++) {
	list[i] = constfunc(i);
}
for (var i = 0; i < 10; i++) {
	console.log(list[i]());
}