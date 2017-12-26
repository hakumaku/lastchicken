#include <iostream>
#include <cstddef>

using namespace std;

int main(void)
{
	/* 1) A pointer can be re-assigned. */
	int foo = 1;
	int bar = 2;
	int *spam = &foo;
	int &eggs = foo;

	/* Valid */
	spam = &bar;

	/* Invalid */
	// &eggs = bar;

	/* 2) A pointer has its own memory address and size. */
	int x = 0;
	int &r = x;
	int *p1 = &x;
	int *p2 = &r;

	if (p1 == p2)
	{
		cout << "p1 == p2 True." << endl;
	}

	/* 3) A pointer pointer is valid. */
	int i = 12;
	int *j = &i;
	int **k = &j;
	int **&l = k;

	cout << **k << endl;

	/* 4) nullptr */

	/* Valid */
	int *a = nullptr;

	/* Invalid */
	// int &b = nullptr;

	/* 5) References cannot be stuffed into an array. */


	return 0;
}
