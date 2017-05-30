/*
 * Pseudocode
 * HOARE_PARTITION(A,p,r):
 *	x = A[p]
 *	i = p - 1
 *	j = r + 1
 *	while TRUE
 *		repeat
 *			j = j - 1
 *		until A[j] <= x
 *		repeat
 *			i = i + 1
 *		until A[i] >= x
 *		if i < j
 *			exchange A[i] with A[j]
 *		else
 *			return j
 *
 * (Sir Tony Hoare developed quick sort.)
 * Don't get confused with 'until' and COMPARISON SYMBOLS.
 * THREE PROPERTIES you should be aware of:
 *	1) The indices i and j are such that
 *	we never access an element of A outside the subarray A[p..r].
 *		-'x', or A[p], is the key to the termination condition.
 *		Either 'i' or 'j' will never exceed the index 'p' which is between
 *		'i' and 'j', since A[p] cannot be greater than itself or less than.
 *	2) When HOARE_PARTITION terminates,
 *	it returns a value j such that p <= j < r.
 *		-Since 'j' starts from the last element 'r-1', it is obvious that
 *		j < r holds. Also, when there are no appropriate values so that
 *		j equals to p, A[j] cannot be greater than itself, A[p].
 *		Thus, p <= j and j < r.
 *	3) Every element of A[p..j] is less than or equal to every
 *	element of A[j+1..r] when HOARE_PARTITION terminates.
 */
#include <stdio.h>
#include <stdlib.h>

#define TEST_VAL1 12

void hoare_quick_sort(int *arr, size_t p, size_t r);
size_t hoare_partition(int *arr, size_t p, size_t r);

void print_array(int *arr, size_t len);

int main(void)
{
	int var1[TEST_VAL1] = {13, 19, 9, 5, 12, 8, 7, 4, 21, 2, 6, 11};
	int var2[TEST_VAL1] = {12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

	hoare_quick_sort(var1, 0, TEST_VAL1);
	hoare_quick_sort(var2, 0, TEST_VAL1);
	print_array(var1, TEST_VAL1);
	print_array(var2, TEST_VAL1);

	return 0;
}

void hoare_quick_sort(int *arr, size_t p, size_t r)
{
	if(p+1 < r)
	{
		size_t q = hoare_partition(arr, p, r);
		hoare_quick_sort(arr, p, q);
		hoare_quick_sort(arr, q+1, r);
	}
}
/*
 * If you read the pseudocode again, you will find out that
 * the first loop always fails; 'x' is assigned 'arr[p]', and
 * it compares 'x' with 'arr[i]' such that 'i' is 'p'.
 * The first swapping occurs when the suitable 'j' is found in the array,
 * in which 'i' < 'j' holds.
 * It returns 'j', or 'q', the entry of which is in the sorted positiion.
 * e.g)
 * p:0 r:12 q:11
 * 1 11 10 9 8 7 6 5 4 3 2 12
 * p:0 r:11 q:0
 * 1 11 10 9 8 7 6 5 4 3 2 12
 * p:1 r:11 q:10
 * 1 2 10 9 8 7 6 5 4 3 11 12
 * p:1 r:10 q:1
 * 1 2 10 9 8 7 6 5 4 3 11 12
 * p:2 r:10 q:9
 * 1 2 3 9 8 7 6 5 4 10 11 12
 * p:2 r:9 q:2
 * 1 2 3 9 8 7 6 5 4 10 11 12
 * p:3 r:9 q:8
 * 1 2 3 4 8 7 6 5 9 10 11 12
 * p:3 r:8 q:3
 * 1 2 3 4 8 7 6 5 9 10 11 12
 * p:4 r:8 q:7
 * 1 2 3 4 5 7 6 8 9 10 11 12
 * p:4 r:7 q:4
 * 1 2 3 4 5 7 6 8 9 10 11 12
 * p:5 r:7 q:6
 * 1 2 3 4 5 6 7 8 9 10 11 12
 */
size_t hoare_partition(int *arr, size_t p, size_t r)
{
	int temp = 0;
	int x = arr[p];
	size_t i = p, j = r-1;
	while(1)
	{
		while(arr[j] > x)
			j--;
		if(i < j)
		{
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
			while(arr[i] < x)
				i++;
		}
		else
			return j;
	}
}
void print_array(int *arr, size_t len)
{
	for(size_t i = 0; i < len; i++)
		printf("%d ", arr[i]);
	putchar('\n');
}
