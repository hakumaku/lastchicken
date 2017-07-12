function counter() {
	var n = 0;
	return {
		count: function() { return ++n; },
		reset: function() { n = 0; }
	}
}

var foo = counter(), bar = counter();
console.log(foo.count()); // foo 1
console.log(foo.count());
console.log(foo.count());
console.log(bar.count());
console.log(bar.count());
bar.reset();
console.log(bar.count());
console.log(foo.count());