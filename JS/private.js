function counter() {
	var n = 0;
	return {
		count: function() { return ++n; },
		reset: function() { n = 0; }
	}
}

var foo = counter(), bar = counter();
console.log(foo.count());	// foo 1
console.log(foo.count());	// foo 2
console.log(foo.count()); 	// foo 3
console.log(bar.count());	// bar 1
console.log(bar.count());	// bar 2
bar.reset();				// bar 0
console.log(bar.count());	// bar 1
console.log(foo.count());	// foo 3