#include <iostream>
#include <vector>

int main(void)
{
	std::vector<int> foo;
	std::vector<int> bar(10);

	/* When initializing, it is invalid. */
	// foo[0] = 10;
	
	foo.push_back(12);
	foo.push_back(7);
	foo.push_back(17);

	for (int i = 0; i < foo.size(); i++)
	{
		std::cout << foo[i] << std::endl;
		/* Changing is valid. */
		foo[i] = 0;
	}
	for (int i = 0; i < foo.size(); i++)
	{
		std::cout << foo[i] << std::endl;
	}

	for (int i = 0; i < bar.size(); i++)
	{
		bar[i] = i+1;
	}
	for (int i = 0; i < bar.size(); i++)
	{
		std::cout << bar[i] << std::endl;
	}

	std::cout << foo.capacity() << std::endl;
	std::cout << bar.capacity() << std::endl;

	return 0;
}
