/*
 * A simple sorting algorithm.
 * Usually not used in practice.
 */
#include <stdio.h>

#define TEST_VAL1 11

void bubble_sort(int *arr, size_t len);
void print_array(int *arr, size_t len);

int main(void)
{
	int test1[] = {100, 99, 98, 32, 23, 12, 7, 8, 9, 3, 1};

	bubble_sort(test1, TEST_VAL1);
	print_array(test1, TEST_VAL1);

	return 0;
}
void bubble_sort(int *arr, size_t len)
{
	int temp = 0;
	for(size_t i = 1; i < len; i++)
	{
		for(size_t j = 0; j < len - i; j++)
		{
			if(arr[j] > arr[j+1])
			{
				temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
			}
		}
	}
}
void print_array(int *arr, size_t len)
{
	for(size_t i = 0; i < len; i++)
		printf("%d ", arr[i]);
	putchar('\n');
}
