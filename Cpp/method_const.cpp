#include <iostream>

class MyClass
{
public:
	void Foo(void)
	{
		x++;
		std::cout << "Foo" << std::endl;
	}

	void Foo(void) const
	{
		/*
		 * It gives you an error,
		 * when you try to moify a value
		 * of the calling object.
		 */
		// x++;
		std::cout << "Foo const" << std::endl; 
	}

private:
	int x;
};

int main(void)
{
	MyClass spam;
	const MyClass& eggs = spam;

	spam.Foo();
	eggs.Foo();

	return 0;
}
