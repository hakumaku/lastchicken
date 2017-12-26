#include <iostream>

using namespace std;
/*
 * using std::cin;
 * using std::cout;
 * using std::cerr;
 */
int main(void)
{
	string str1 = "Hello, world!\n";
	string str2 = "Welcome to C++.\n";
	int numberOfLanguages = 0;

	cout << str1 + str2;

	cout << "How many programming languages have you used? ";
	cin >> numberOfLanguages;

	if (numberOfLanguages < 1)
	{
		cout << "Read the preface. You may prefer\n"
			<< "a more elementary book by the same author." << endl;
	}
	else
	{
		cout << "Enjoy the book." << endl;
	}

	return 0;
}

