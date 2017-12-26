#include <iostream>
using namespace std;

int main(void)
{
	int foo = 10;
	float bar = 20.0F;
	const float spam = 20.1F;
	float eggs = 20.2F;

	bar = static_cast<float>(foo);

	return 0;
}
