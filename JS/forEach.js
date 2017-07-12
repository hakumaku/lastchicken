var a = [1, 2, 3, 4, 5];
a.forEach(function(e) {
	console.log(e);
});

/* Similar but should return a value. */
var b = [];
b = a.map(function(e) {
	return e*e;
});
console.log(b);

/* 
 * The function should be predicate:
 * a function that returns true or false
 */
var c = a.filter(function(e) {
	return e > 2;
});
console.log(c);

/*
 * every(): for all
 * some(): there exists
 */
console.log(c.every(function (e) {
	return e > 2;
}));
console.log(c.some(function (e) {
	return e == 5;
}));