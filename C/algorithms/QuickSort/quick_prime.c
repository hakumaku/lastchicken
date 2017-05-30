/*
 * This implementation of quick sort handles better with
 * sequences of the same values.
 */
#include <stdio.h>
#include <stdlib.h>

#define TEST_VAL1	12

typedef struct {
	size_t q;
	size_t t;
}pivot_t;

void quick_sort_prime(int *arr, size_t p, size_t r);
pivot_t partition_prime(int *arr, size_t p, size_t r);

void print_array(int *arr, size_t len);

int main(void)
{
	int var1[TEST_VAL1] = {13, 11, 11, 5, 12, 8, 7, 4, 11, 11, 11, 11};
	int var2[TEST_VAL1] = {12, 8, 10, 9, 8, 8, 8, 5, 4, 3, 8, 1};

	quick_sort_prime(var1, 0, TEST_VAL1);
	quick_sort_prime(var2, 0, TEST_VAL1);

	print_array(var1, TEST_VAL1);
	print_array(var2, TEST_VAL1);

	return 0;
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
void print_array(int *arr, size_t len)
{
	for(size_t i = 0; i < len; i++)
		printf("%d ", arr[i]);
	putchar('\n');
}
