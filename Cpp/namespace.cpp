#include <iostream>

using std::cout;

namespace Space1
{
	void greeting();
}

namespace Space2
{
	void greeting();
}

void big_greeting();

int main(void)
{
	{
		using namespace Space1;
		greeting();
	}
	
	{
		using namespace Space2;
		greeting();
	}

	big_greeting();

	return 0;
}

namespace Space1
{
	void greeting()
	{
		cout << "Hello from namespace Space1.\n";
	}
}

namespace Space2
{
	void greeting()
	{
		cout << "Hello from namespace Space2.\n";
	}
}

void big_greeting()
{
	cout << "A big global Hello!\n";
}

