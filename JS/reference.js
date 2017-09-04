var person = {
	job: "student",
	favFood: "ramen"
};

var copyPerson = person;
copyPerson.job = "programmer";
/*
 * person.job == "student"
 * copyPerson.job == "programmer" ??
 * No. person.job == copyPerson.job == "programmer"
 */
console.log(person.job);