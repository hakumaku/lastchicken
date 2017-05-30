/*
 * A much improved variation of random_quick_sort.
 * It creates three random pivots ,and choose the median of three
 * to obtain better expected performance.
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TEST_VAL1 12

void median_quick_sort(int *arr, size_t p, size_t r);
size_t median_partition(int *arr, size_t p, size_t r);
size_t partition(int *arr, size_t p, size_t r);
size_t random(size_t a, size_t b);

void print_array(int *arr, size_t len);

int main(void)
{
	int var1[TEST_VAL1] = {13, 19, 9, 5, 12, 8, 7, 4, 21, 2, 6, 11};
	int var2[TEST_VAL1] = {12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

	median_quick_sort(var1, 0, TEST_VAL1);
	median_quick_sort(var2, 0, TEST_VAL1);

	print_array(var1, TEST_VAL1);
	print_array(var2, TEST_VAL1);

	return 0;
}
/*
 * The performance of quicksort depends on the pivot;
 * the better the pivot value is, the faster the function sorts.
 * Although the cost of creating three random varaibles is expensive,
 * it is highly expected to run in the average case.
 */
void median_quick_sort(int *arr, size_t p, size_t r)
{
	if(p+1 < r)
	{
		size_t q = median_partition(arr, p, r);
		median_quick_sort(arr, p, q);
		median_quick_sort(arr, q+1, r);
	}
}
size_t median_partition(int *arr, size_t p, size_t r)
{
	srand(time(NULL));
	size_t i1 = random(p, r);
	size_t i2 = random(p, r);
	size_t i3 = random(p, r);
	int median = i1;
	int median2 = i1 ^ i2;
	/*	Does not generate 'cmov', but still seems not bad.	*/
	if(arr[median] < arr[i2])
		median = i2;
	median2 ^= median;

	if(arr[median2] < arr[i3])
		median2 = i3;

	if(arr[median2] < arr[median])
		median = median2;

	int temp = arr[r-1];
	arr[r-1] = arr[median];
	arr[median] = temp;

	return partition(arr, p, r);
}
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
void print_array(int *arr, size_t len)
{
	for(size_t i = 0; i < len; i++)
		printf("%d ", arr[i]);
	putchar('\n');
}
