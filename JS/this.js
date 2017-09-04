var Person = {
	printThis: function () {
		console.log("Hello!!");
		console.log(this == Person);
	}
}

function whoIsThis() {
	console.log("Hi!!");
	console.log(this == global);
}

Person.printThis();
whoIsThis();