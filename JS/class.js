/* Common way of defining Class */
function Range(from, to) {
	this.from = from;
	this.to = to;
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