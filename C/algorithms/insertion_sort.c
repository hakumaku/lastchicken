/*
 * Input: A sequence of n numbers
 * Ouput: A permutation of the input sequence
 * such that a1 <= a2 <= a3 <= ... <= an
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
/*	Recursive	*/
void isort_re(int *arr, size_t len);

int main(void)
{
	int test1[] = {100, 99, 98, 32, 23, 12, 7, 8, 9, 3, 1};
	int len1 = sizeof(test1) / sizeof(int);
	int test2[] = {100, 99, 98, 32, 23, 12, 7, 8, 9, 3, 1};
	int len2 = sizeof(test2) / sizeof(int);

	isort_nd(test1, len1);
	for(int i = 0; i < len1; i++)
		printf("%d ", test1[i]);
	putchar('\n');

	isort_ni(test1, len1);
	for(int i = 0; i < len1; i++)
		printf("%d ", test1[i]);
	putchar('\n');

	isort_re(test2, len2);
	for(int i = 0; i < len2; i++)
		printf("%d ", test2[i]);
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
	 * Note that 'j' starts from 1, not 0,
	 * since it needs two elements to compare.
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
/*	The only difference is the comparison sign 	*/
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
void isort_re(int *arr, size_t len)
{
	/*
	 * 'len' should be larger than 1
	 * for the same reason as 'j' starting from 1, not 0.
	 */
	if(len > 1)
	{
		/*
		 * It can be comprehended as
		 * smaller = arr[j];
		 * i = j - 1;
		 */
		int i = len-2, smaller = arr[len-1];
		/*	Keep dividing, length is getting smaller	*/
		isort_re(arr, len-1);

		for(; i >= 0 && arr[i] > smaller; i--)
			arr[i+1] = arr[i];
		arr[i+1] = smaller;
	}
}