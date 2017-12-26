#include <iostream>

using namespace std;

double average(double n1=2.0, double n2=2.5);

int main(void)
{
	cout << "The average of 2.0 and 2.5: "
		<< average() << endl;

	return 0;
}
/* Default arguments must not be given a second time. */
double average(double n1, double n2)
{
	return ((n1 + n2) / 2.0);
}


