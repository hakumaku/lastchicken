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
 *
 * Pseudocode
 * RANDOMIZED_PARTITION(A,p,r):
 *	i = RANDOM(p,r)
 *	exchange A[r] with A[i]
 *	return PARTITION(A,p,r)
 *
 * Pseudocode
 * RANDOMIZED_QUICKSORT(A,p,r):
 *	if p < r
 *		q = RANDOMIZED_PARTITION(A,p,r)
 *		RANDOMIZED_QUICKSORT(A,p,q-1)
 *		RANDOMIZED_QUICKSORT(A,q+1,r)
 *
 * In order to obtain good expected performance over all inputs,
 * it explicitly permutates the input.
 *
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
#include <time.h>

#define TEST_VAL1	12

typedef struct {
	size_t q;
	size_t t;
}pivot_t;

void quick_sort(int *arr, size_t p, size_t r);
size_t partition(int *arr, size_t p, size_t r);

void random_quick_sort(int *arr, size_t p, size_t r);
size_t random_partition(int *arr, size_t p, size_t r);
size_t random(size_t a, size_t b);

void hoare_quick_sort(int *arr, size_t p, size_t r);
size_t hoare_partition(int *arr, size_t p, size_t r);

void quick_sort_prime(int *arr, size_t p, size_t r);
pivot_t partition_prime(int *arr, size_t p, size_t r);

int main(void)
{
	int var1[TEST_VAL1] = {13, 19, 9, 5, 12, 8, 7, 4, 21, 2, 6, 11};
	int var2[TEST_VAL1] = {12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
	int var3[TEST_VAL1] = {13, 19, 9, 5, 12, 8, 7, 4, 21, 2, 6, 11};
	int var4[TEST_VAL1] = {12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
	int var5[TEST_VAL1] = {13, 19, 9, 5, 12, 8, 7, 4, 21, 2, 6, 11};
	int var6[TEST_VAL1] = {12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
	int var7[TEST_VAL1] = {13, 11, 11, 5, 12, 8, 7, 4, 11, 11, 11, 11};
	int var8[TEST_VAL1] = {12, 8, 10, 9, 8, 8, 8, 5, 4, 3, 8, 1};

	quick_sort(var1, 0, TEST_VAL1);
	quick_sort(var2, 0, TEST_VAL1);
	random_quick_sort(var3, 0, TEST_VAL1);
	random_quick_sort(var4, 0, TEST_VAL1);
	hoare_quick_sort(var5, 0, TEST_VAL1);
	hoare_quick_sort(var6, 0, TEST_VAL1);
	quick_sort_prime(var7, 0, TEST_VAL1);
	quick_sort_prime(var8, 0, TEST_VAL1);

	for(size_t i = 0; i < TEST_VAL1; i++)
	{
		printf("%d ", var1[i]);
	}
	putchar('\n');
	for(size_t i = 0; i < TEST_VAL1; i++)
	{
		printf("%d ", var2[i]);
	}
	putchar('\n');
	for(size_t i = 0; i < TEST_VAL1; i++)
	{
		printf("%d ", var3[i]);
	}
	putchar('\n');
	for(size_t i = 0; i < TEST_VAL1; i++)
	{
		printf("%d ", var4[i]);
	}
	putchar('\n');
	for(size_t i = 0; i < TEST_VAL1; i++)
	{
		printf("%d ", var5[i]);
	}
	putchar('\n');
	for(size_t i = 0; i < TEST_VAL1; i++)
	{
		printf("%d ", var6[i]);
	}
	putchar('\n');
	for(size_t i = 0; i < TEST_VAL1; i++)
	{
		printf("%d ", var7[i]);
	}
	putchar('\n');
	for(size_t i = 0; i < TEST_VAL1; i++)
	{
		printf("%d ", var8[i]);
	}
	putchar('\n');
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
size_t partition(int *arr, size_t p, size_t r)
{
	int temp = 0;
	int x = arr[r-1];
	size_t i = p, j = p;
	/*	Until the penultimate element.	*/
	for(; j < r-1; j++)
	{
		/*	The last element will always be swapped.	*/
		if(arr[j] <= x)
		{
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
			i++;
		}
	}
	temp = arr[j];
	arr[j] = arr[i];
	arr[i] = temp;

	return i;
}
void random_quick_sort(int *arr, size_t p, size_t r)
{
	if(p+1 < r)
	{
		size_t q = random_partition(arr, p, r);
		/*	[p,q)	*/
		random_quick_sort(arr, p, q);
		/*	(q,r)	*/
		random_quick_sort(arr, q+1, r);
	}
}
size_t random_partition(int *arr, size_t p, size_t r)
{
	srand(time(NULL));
	size_t i = random(p, r);
	int temp = arr[r-1];
	arr[r-1] = arr[i];
	arr[i] = temp;

	return partition(arr, p, r);
}
/*	returns x in [a, b)	*/
size_t random(size_t a, size_t b)
{
	size_t ret = 0;
	size_t range = b - a;
	if(b < a)
		return 0;

	do {
		ret = rand();
	} while(ret >= (RAND_MAX - RAND_MAX % range));

	return (ret % range) + a;
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
void quick_sort_prime(int *arr, size_t p, size_t r)
{
	if(p+1 < r)
	{
		pivot_t pivot = partition_prime(arr, p, r);
		quick_sort_prime(arr, p, pivot.q);
		quick_sort_prime(arr, pivot.t+1, r);
	}
}
pivot_t partition_prime(int *arr, size_t p, size_t r)
{
	int temp = 0, x = arr[r-1];
	size_t i = p, j = p, t = 0;

	for(; j < r-1; j++)
	{
		if(arr[j] < x)
		{
			temp = arr[j];
			arr[j] = arr[i];
			arr[i] = temp;
			i++;
		}
	}
	temp = arr[j];
	arr[j] = arr[i];
	arr[i] = temp;

	for(t = i, j = i+1; j < r; j++)
	{
		if(arr[j] == x)
		{
			t++;
			temp = arr[j];
			arr[j] = arr[t];
			arr[t] = temp;
		}
	}

	pivot_t pivot = {i, t};

	return pivot;
}
