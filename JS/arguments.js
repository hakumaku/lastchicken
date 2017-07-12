function foo(x, y, z) {
	console.log(arguments[0]);
	console.log(arguments[1]);
	console.log(arguments[2]);
	console.log(typeof arguments);
}

foo(1, 2, 3);