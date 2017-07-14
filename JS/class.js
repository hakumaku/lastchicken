/* Common way of defining Class */
function Range(from, to) {
	/* Private variable */
	var privateVariable = "foo";

	/* Public variable */
	this.from = from;
	this.to = to;

	/* Public method */
	this.publicMethod = function() {
		console.log("Spam!");
	}
}
/* One is.. */
Range.prototype = {
	constructor: Range,
	includes: function (x) {
		return this.from <= x && x <= this.to;
	},
	forEach: function (f) {
		for (var x = Math.ceil(this.from); x <= this.to; x++)
			f(x);
	},
	toString: function() {
		return "(" + this.from + "..." + this.to ")";
	}
}
/* The other is.. */
// Range.prototype.includes = function (x) {
// 		return this.from <= x && x <= this.to;
// };
// Range.prototype.forEach = function (f) {
// 	for (var x = Math.ceil(this.from); x <= this.to; x++)
// 		f(x);
// };
// Range.prototype.toString = function () {
// 	return "(" + this.from + "..." + this.to ")";
// }