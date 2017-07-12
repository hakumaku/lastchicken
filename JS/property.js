/* Object */
var a = {
	x: 1,
	y: 2
}
console.log(a);
/* Property */
console.log(a.x);
/* Another way of accessing it. */
console.log(a["y"]);

function counter(n) {
	return {
		get count() { return ++n; },
		set count(m) {
			if (m > n) n = m;
			else throw Error("Value too small");
		}
	};
}

var foo = counter(10);
console.log(foo.count);
foo.count = 20;
console.log(foo.count);
console.log(foo.count);