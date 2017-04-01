/*
 * Input: A sequence of n numbers
 * Ouput: A permutation of the input sequence
 * such that a1 <= a2 <= a3 <= ... <= an
 *
 * Pseudocode
 * SELECTION_SORT(A):
 *	for i = 1 to A.length - 1
 *		min = i
 *		for j = i + 1 to A.length
 *			if A[j] < A[min]
 *				min = j;
 *		temp = A[i]
 *		A[i] = A[min]
 *		A[min] = temp
 */

#include <stdio.h>

void selsort(int *arr, size_t len);

int main(void)
{
	int test1[] = {100, 99, 98, 32, 23, 12, 7, 8, 9, 3, 1};
	int len1 = sizeof(test1) / sizeof(int);

	selsort(test1, len1);
	for(int i = 0; i < len1; i++)
		printf("%d ", test1[i]);
	putchar('\n');

	return 0;
}

void selsort(int *arr, size_t len)
{
	size_t i = 0, j = 0, min_index = 0;
	int temp = 0;
	for(; i < len; i++)
	{
		min_index = i;
		/*	Finding the smallest one of its subarray	*/
		for(j = i + 1; j < len; j++)
		{
			
			if(arr[j] < arr[min_index])
				min_index = j;
		}
		/*	Swap it with the current index	*/
		temp = arr[i];
		arr[i] = arr[min_index];
		arr[min_index] = temp;
	}
}