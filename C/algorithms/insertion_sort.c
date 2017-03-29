/*
 * Input: A sequence of n numbers
 * Ouput: A permutation of the input sequence such
 * that a1 <= a2 <= a3 <= ... <= an
 *
 * Pseudocode
 * INSERTION_SORT(A):
 *	for j = 2 to A.length
 *		key = A[j]
 *		//Insert A[j] into the sorted sequence A[1..j-1]
 *		i = j - 1
 *		while i > 0 and A[i] > key
 *			A[i+1] = A[i]
 *			i = i - 1
 *		A[i+1] = key
 */

#include <stdio.h>

/*	non-decreasing	*/
void isort_nd(int *arr, size_t len);
/*	non-increasing	*/
void isort_ni(int *arr, size_t len);

int main(void)
{
	int test1[] = {100, 99, 98, 32, 23, 12, 7, 8, 9, 3, 1};
	int len1 = sizeof(test1) / sizeof(int);

	isort_nd(test1, len1);
	for(int i = 0; i < len1; i++)
		printf("%d ", test1[i]);
	putchar('\n');

	isort_ni(test1, len1);
	for(int i = 0; i < len1; i++)
		printf("%d ", test1[i]);
	putchar('\n');

	return 0;
}
/*
 * Try subscripting from 0 to A.length, or 'j',
 * and you'll see its inefficiency.
 */
void isort_nd(int *arr, size_t len)
{
	/*
	 * A[1..j-1]: the ordered subarray.
	 * A[j]: the current index.
	 * A[j+1..n]: the rest which needs ordered.
	 */
	int i = 0, j = 1, smaller = 0;
	for(; j < len; j++)
	{
		smaller = arr[j];
		i = j - 1;
		for(; i >= 0 && arr[i] > smaller; i--)
			arr[i+1] = arr[i];
		arr[i+1] = smaller;
	}
}
void isort_ni(int *arr, size_t len)
{
	int i = 0, j = 1, smaller = 0;
	for(; j < len; j++)
	{
		smaller = arr[j];
		i = j - 1;
		for(; i >= 0 && arr[i] < smaller; i--)
			arr[i+1] = arr[i];
		arr[i+1] = smaller;
	}
}