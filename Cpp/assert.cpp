#include <iostream>

/* You can turn it off via defining NDEBUG. */
// #define NDEBUG
#include <cassert>

using namespace std;

int main(void)
{
	assert(1 == 2);

	cout << "Debugging option is turned off!\n";

	return 0;
}

