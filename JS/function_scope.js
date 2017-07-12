/*
 * Unlike C which has "block scope",
 * Javascript has "function scope".
 */

function test(o) {
	var i = 0;
	if (typeof o == "object") {
		var j = 0;
		for (var k = 0; k < 3; k++) {
			console.log(k);
		}
		/* Visible */
		console.log(k);
	}
	/* Visible */	
	console.log(k);
}
var hi = new Number(1);
test(hi);

/*
 * Another example.
 */
var scope = "global"
function spam() {
	console.log(scope);
}
function foo() {
	/* It prints out 'Undefined'. */
	console.log(scope);
	var scope = "local";
	console.log(scope);
}
/* What the above actually did is.. */
function bar() {
	/* Called "hoisting" */
	var scope;
	console.log(scope);
	scope = "local";
	console.log(scope);
}
spam();
foo();
bar();