#include <iostream>
#include <cstdlib>

using namespace std;

int main(void)
{
	srand(99);
	for (int i = 0; i < 10; i++)
	{
		cout << rand() % 10 << endl;
	}

	return 0;
}
