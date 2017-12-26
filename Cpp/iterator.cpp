#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

int main(void)
{
	vector<int> foo;

	for (int i = 0; i < 10; i++)
	{
		foo.push_back(i+1);
	}

	vector<int>::iterator bar;
	for (bar = foo.begin(); bar != foo.end(); bar++)
	{
		cout << *bar << " ";
	}
	cout << endl;


	return 0;
}
