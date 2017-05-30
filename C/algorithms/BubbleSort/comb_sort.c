/*
 * A variation of bubble sort.
 * The basic idea of comb sort is that the gap can be much more than 1.
 * The shrink factor has a great effect on the efficiency of comb sort.
 * k = 1.3 has been suggested as an ideal shrink factor
 * by the authors of the original article
 * after empirical testing on over 200,000 random lists.
 */
#include <stdio.h>
#include <stdbool.h>

#define TEST_VAL1 11

void comb_sort(int *arr, size_t len);
void print_array(int *arr, size_t len);

int main(void)
{
	int test1[] = {100, 99, 98, 32, 23, 12, 7, 8, 9, 3, 1};

	comb_sort(test1, TEST_VAL1);
	print_array(test1, TEST_VAL1);

	return 0;
}
void comb_sort(int *arr, size_t len)
{
	size_t gap = len;
	bool swapped = true;
	int temp = 0;

	while(gap != 1 || swapped)
	{
		/*	shrink == 1.3	*/
		if(gap != 1)
		{
			gap *= 10;
			gap /= 13;
		}

		swapped = false;
		for(size_t i = 0, j = gap; j < len; i++, j++)
		{
			if(arr[j] < arr[i])
			{
				temp = arr[j];
				arr[j] = arr[i];
				arr[i] = temp;
				swapped = true;
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
