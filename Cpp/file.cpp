#include <iostream>
#include <fstream>

using namespace std;

int main(void)
{
	/* Using open. */
	// fstream file_stream;
	// file_stream.open("hello.txt");
	
	/* Not using open. */
	fstream file_stream("hello.txt");

	string str1, str2, str3;

	file_stream >> str1;
	file_stream >> str2;
	file_stream >> str3;

	cout << str1 + str2 + str3 << endl;

	file_stream.close();

	return 0;
}

