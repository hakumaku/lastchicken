/*
 * Pseudocode
 * QUICKSORT(A,p,r):
 *	if p < r
 *		q = PARTITION(A,p,r)
 *		QUICKSORT(A,p,q-1)
 *		QUICKSORT(A,q+1,r)
 *
 * Pseudocode
 * PARTITION(A,p,r):
 *	x = A[r]
 *	i = p-1
 *	for j = p to r-1
 *		if A[j] <= x
 *			i = i + 1
 *			exchange A[i] with A[j]
 *	exchange A[i+1] with A[r]
 *	return i+1
 *
 * (a)┃┃[2]  [8] [7] [1] [3] [5] [6]┃[4]
 *	(2 is less than 4, exchange 2 with 2.)
 * (b)  [2]┃┃[8] [7] [1] [3] [5] [6]┃[4]
 * (c)  [2] ┃[8]┃[7] [1] [3] [5] [6]┃[4]
 * (d)  [2] ┃[8] [7]┃[1] [3] [5] [6]┃[4]
 *	(1 is less than 4, exchange 1 with 8.)
 * (e)  [2]  [1]┃[7] [8]┃[3] [5] [6]┃[4]
 *	(3 is less than 4, exchange 3 with 7.)
 * (f)  [2]  [1] [3]┃[8] [7]┃[5] [6]┃[4]
 * (g)  [2]  [1] [3]┃[8] [7] [5]┃[6]┃[4]
 * (h)  [2]  [1] [3]┃[8] [7] [5] [6]┃[4]
 * (i)  [2]  [1] [3]┃[4]┃[8] [7] [5] [6]┃
 *	(Done, exchange arr[i+1]==8 with 4.)
 * It partitions the array into four:
 * one has elements equal to or less than x,
 * one has elements greater than x,
 * one has elements to be determined,
 * the last one has a pivot value.
 */
#include <stdio.h>
#include <stdlib.h>

#define TEST_VAL1	12

typedef struct {
	size_t q;
	size_t t;
}pivot_t;

void quick_sort(int *arr, size_t p, size_t r);
size_t partition(int *arr, size_t p, size_t r);

void print_array(int *arr, size_t len);

int main(void)
{
	int var1[TEST_VAL1] = {13, 19, 9, 5, 12, 8, 7, 4, 21, 2, 6, 11};
	int var2[TEST_VAL1] = {12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

	quick_sort(var1, 0, TEST_VAL1);
	quick_sort(var2, 0, TEST_VAL1);

	print_array(var1, TEST_VAL1);
	print_array(var2, TEST_VAL1);

	return 0;
}

void quick_sort(int *arr, size_t p, size_t r)
{
	/*
	 * It removes out an element, arr[q].
	 * every time it is called.
	 * It is obvious that arr[q] must be at the
	 * correct position, all the left of which are
	 * less than or equal to q, the right greater than q.
	 */
	if(p+1 < r)
	{
		size_t q = partition(arr, p, r);
		/*	[p,q)	*/
		quick_sort(arr, p, q);
		/*	(q,r)	*/
		quick_sort(arr, q+1, r);
	}
}
/*
 * Lomuto partition scheme.
 */
size_t partition(int *arr, size_t p, size_t r)
{
	int temp = 0;
	int x = arr[r-1];
	size_t i = p, j = p;
	/*	Until the penultimate element.	*/
	for(; j < r-1; j++)
	{
		if(arr[j] <= x)
		{
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
			i++;
		}
	}
	/*	The last element will always be swapped.	*/
	temp = arr[j];
	arr[j] = arr[i];
	arr[i] = temp;

	return i;
}
void print_array(int *arr, size_t len)
{
	for(size_t i = 0; i < len; i++)
		printf("%d ", arr[i]);
	putchar('\n');
}
