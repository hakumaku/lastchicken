var foo = [4, 5, 6];
var pets = new Set(['Cat', 'Dog', 'Hamster']);
pets['species'] = 'mammals';

/* Properties of an Object */

/* 0, 1, 2 */ 
for (let i in foo) {
	console.log(i);
}
/* 'species' */
for (let pet in pets) {
	console.log(pet);
}

/* Values of iterable objects */

/* 4, 5, 6 */
for (let i of foo) {
	console.log(i);
}
/* 'Cat', 'Dog', 'Hamster' */
for (let pet of pets) {
	console.log(pet);
}


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

