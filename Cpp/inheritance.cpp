#include <iostream>

using namespace std;

class A 
{
public:
	A();
	A(int a)
		:x(a) {};
	A(int a, int b)
		:x(a), y(b) {};
	A(int a, int b, int c)
		:x(a), y(b), z(c) {};

	int x;

	/* y and z are accessible within A. */
	int get_y(void) { return y; };
	int get_z(void) { return z; };

	void hello(void)
	{
		cout << "Hello, world!(from A)\n";
	}

protected:
	int y;

private:
	int z;
};
/*
 * x is public.
 * y is protected.
 * z is not accessible from B.
 */
class B : public A
{
public:
	B() : A() {};
	B(int a) : A(a) {};
	B(int a, int b) : A(a, b) {};
	B(int a, int b, int c) : A(a, b, c) {};

	/* y is accessible but z within B. */
	int get_y(void) { return y; };

	/* Redefinition */
	void hello(void)
	{
		cout << "Hello, world!(from B)\n";
	}
};

class C : protected A
{
	/*
	 * x is protected.
	 * y is protected.
	 * z is not accessible from B.
	 */
};

/*
 * x is private.
 * y is private.
 * z is not accessible from B.
 * 'private' is default for classes.
 */
class D : private A
{
public:
	D() : A() {};
	D(int a) : A(a) {};
	D(int a, int b) : A(a, b) {};
	D(int a, int b, int c) : A(a, b, c) {};

	int get_x(void)
	{
		return x;
	}
	int get_y(void)
	{
		return y;
	}
};

int main(void)
{
	A bar(1, 2, 3);
	B eggs(1, 2, 3);
	D foo(1, 2, 3);

	foo.get_x();
	bar.hello();
	eggs.hello();


	return 0;
}

