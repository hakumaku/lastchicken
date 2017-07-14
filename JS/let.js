/*
 * as a variable declaration like var;
 * in a for or for/in loop, as a substitute for var;
 * as a block statemen, to define new variables and explicitly delimit their scope;
 * to define varaibles that are scoped to a single expression.
 */

function oddsums (n) {
	let total = 0, result = [];
	for (let x = 1; x <= n; x++) {
		let odd = 2*x-1;
		total += odd;
		result.push(total);
	}	
	/*
	 * 'x', 'odd' not accessible here
	 * console.log(x);
	 * console.log(odd);
	 */
	return result;
}

console.log(oddsums(5));