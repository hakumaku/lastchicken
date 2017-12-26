#include <iostream>
#include <cstdlib>

#define ROW 10
#define COL 10

/*
 * 'new' and 'delete' are similar to
 * malloc() and free() in C respectively.
 *
 * */
int main(void)
{
	srand(99);

	/* Allocating */
	int **foo = new int*[ROW];
	for (int i = 0; i < ROW; i++)
	{
		foo[i] = new int[COL];
	}

	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			foo[i][j] = rand() % 100;
		}
	}
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			std::cout << foo[i][j] << " ";
		}
		std::cout << std::endl;
	}

	/* Deallocating */
	for (int i = 0; i < ROW; i++)
	{
		delete [] foo[i];
	}
	delete [] foo;

	/* Undefined behaviour. */
	// delete arr2;
	// delete arr2[];

	return 0;
}
