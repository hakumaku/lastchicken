#include <iostream>

using namespace std;

void swap(int& x, int& y);

int main(void)
{
	int a = 3, b = 7;

	cout << "a: " << a << endl;
	cout << "b: " << b << endl;
	cout << "Swap!\n";

	swap(a, b);

	cout << "a: " << a << endl;
	cout << "b: " << b << endl;

	return 0;
}

void swap(int& x, int& y)
{
	int t = x;
	x = y;
	y = t;
}

