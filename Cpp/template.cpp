#include <iostream>

using std::cout;
using std::endl;

template<class T>
void swap(T& v1, T& v2);

int main(void)
{
	int integer1 = 10, integer2 = 20;
	cout << "integer1: " << integer1 << endl;
	cout << "integer2: " << integer2 << endl;
	swap(integer1, integer2);
	cout << "After swap funtion: \n";
	cout << "integer1: " << integer1 << endl;
	cout << "integer2: " << integer2 << endl;

	double double1 = 10, double2 = 20;
	cout << "double1: " << double1 << endl;
	cout << "double2: " << double2 << endl;
	swap(double1, double2);
	cout << "After swap funtion: \n";
	cout << "double1: " << double1 << endl;
	cout << "double2: " << double2 << endl;
	
	return 0;
}

template<class T>
void swap(T& v1, T& v2)
{
	T temp = v1;
	v1 = v2;
	v2 = temp;
}


