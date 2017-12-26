#include <iostream>

class MyClass
{
public:
	static int foo;
	static bool bar;
	static void yell(void);

private:
	int x;
};

int MyClass::foo = 10;
bool MyClass::bar = true;

int main(void)
{
	MyClass a, b;

	/* static function */
	MyClass::yell();

	std::cout << a.foo << std::endl;
	std::cout << b.foo << std::endl;

	a.foo = 20;

	std::cout << a.foo << std::endl;
	std::cout << b.foo << std::endl;

	return 0;
}

void MyClass::yell(void)
{
	std::cout << "Hello, world!\n";
}

