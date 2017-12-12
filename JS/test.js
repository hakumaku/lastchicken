var foo = {};
foo.foo = 'ho~~';
foo.bar = 'hello';
foo.spam = 'world!';
foo.hi = ['a', 'b', 'c'];

for (let i in foo) {
	console.log(i);
}

for (let i of foo) {
	console.log(i);
}

