#include <iostream>

using namespace std;

double average(double n1, double n2);
double average(double n1, double n2, double n3);

/* Cannot overload soley based on return type. */
// float average(double n1, double n2);
/*
 * However, the following is valid
 * since parameters are different types.
 */
float average(float n1, float n2);

int main(void)
{
	cout << "The average of 2.0 and 2.5: "
		<< average(2.0, 2.5) << endl;

	cout << "The average of 3.0, 4.3 and 5.5: "
		<< average(3.0, 4.3, 5.5) << endl;

	return 0;
}
double average(double n1, double n2)
{
	return ((n1 + n2) / 2.0);
}
double average(double n1, double n2, double n3)
{
	return ((n1 + n2 + n3) / 2.0);
}
float average(float n1, float n2)
{
	return ((n1 + n2) / 2.0);
}

