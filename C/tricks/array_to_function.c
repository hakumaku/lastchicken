#include <stdio.h>
#include <stdlib.h>

#define ROWS	4
#define COLS	5

/*	If you know its rows & columns.	*/
void method1(int arr[ROWS][COLS]);

/*	C99: VLA(variable-length array)	*/
void method2(size_t m, size_t n, int arr[m][n]);

/*	Dynamically allocated	*/
void method3(int **arr, size_t m, size_t n);

/*	Both dynamically and statically allocated	*/
void method4(int *arr, size_t m, size_t n);

int main(void)
{
	int m = ROWS, n = COLS;
	int arr1[ROWS][COLS] = { 0 };
	int **arr2 = NULL;

	method1(arr1);
	method2(m, n, arr1);

	/*	The following code is idiomatic.	*/

	/*	malloc its rows	*/
	arr2 = (int **)malloc(sizeof(int *) * m);
	/*	for each row	*/
	for(size_t i = 0; i < m; i++)
		/*	malloc its columns	*/
		arr2[i] = (int *)malloc(sizeof(int) * n);

	method3(arr2, m, n);

	/*	for each row	*/
	for(size_t i = 0; i < m; i++)
		/*	free its columns	*/
		free(arr2[i]);
	/*	free its rows	*/
	free(arr2);

	/*	End of process	*/


	/*
	 * For an array 'int arr1[ROWS][COLS] = { 0 }',
	 * 'arr1' and '&arr1[0][0]' are
	 * fundamentally equal, which all point to
	 * the address of a segment.
	 * However, their denotions are slightly different:
	 * the former indicates
	 * "The address of a contiguous int segment, or arr1,
	 * which is logically separated per COLS."
	 * (concisely COLS * sizeof(type)),
	 * whereas the latter refers to
	 * "The address of arr1" in which the compiler does not
	 * know this is a "two dimensional" array.
	 *
	 * From that point of view, you might catch it
	 * that why the compiler has to be necessarily informed
	 * the sole number of COLS, not ROWS, like this:
	 * int foo(int arr[][COLS]);
	 *
	 * You need to have learned the conception of "array" to C
	 * that it actually does not store it in a form of "n by n",
	 * but in a logically linear set.
	 */
	method4(&arr1[0][0], m, n);

	return 0;
}
void method1(int arr[ROWS][COLS])
{
	for(size_t i = 0; i < ROWS; i++)
	{
		for(size_t j = 0; j < COLS; j++)
		{
			arr[i][j] = i * j;
		}
	}
}
void method2(size_t m, size_t n, int arr[m][n])
{
	for(size_t i = 0; i < m; i++)
	{
		for(size_t j = 0; j < n; j++)
		{
			arr[i][j] = i * j;
		}
	}
}
void method3(int **arr, size_t m, size_t n)
{
	for(size_t i = 0; i < m; i++)
	{
		for(size_t j = 0; j < n; j++)
		{
			arr[i][j] = i * j;
		}
	}
}
void method4(int *arr, size_t m, size_t n)
{
	for(size_t i = 0; i < m; i++)
	{
		for(size_t j = 0; j < n; j++)
		{
			arr[i*m + j] = i * j;
		}
	}
}