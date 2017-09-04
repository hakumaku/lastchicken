function callback() {
	console.log("Nice to see you!");
}

function setTimeFunction(value) {
	setTimeout(callback, 5000);
	console.log("Hello World!!" + value);
}
/*
 * Does it take 5 sec each, 25 sec in sum??
 * No. When it reaches the line it first invokes setTimeFunction,
 * it does not wait but keep on reading next code setting time schedule.
 * When the set time has elapsed, it calls back and excute code.
 */
setTimeFunction(1);
setTimeFunction(2);
setTimeFunction(3);
setTimeFunction(4);
setTimeFunction(5);
