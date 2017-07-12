/*
 * Primitive types: numbers, strings, booleans.
 * Object types: Date, RegExp, Error, Math, String, Array.
 * The following code illustrates the major difference
 * between a string of primitive type and that of object String.
 */

 var primString = "Hello World!";
 var objString = new String("Hello World!");

 console.log(primString);
 console.log(objString);

 primString.len = 10;
 /* Undefined */
 console.log(primString.len);

 objString.len = 10;
 /* 10 */
 console.log(objString.len);

 /*
  * The following is valid, since
  * it converts it to new String(primtString)
  * then it calls primString.length.
  */
 console.log(primString.length);