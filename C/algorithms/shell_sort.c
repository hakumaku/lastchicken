/*
 * A variation of insertion sort.
 * The basic idea is similar to that of comb sort
 * in which the gap can be much more than 1.
 * A good gap sequence determines the performance of it.
 */
#include <stdio.h>

#define TEST_VAL1 11
#define SHELL_TABLE_SIZE	16

void shell_sort(int *arr, size_t len);
void print_array(int *arr, size_t len);

int main(void)
{
	int test1[] = {100, 99, 98, 32, 23, 12, 7, 8, 9, 3, 1};

	shell_sort(test1, TEST_VAL1);
	print_array(test1, TEST_VAL1);

	return 0;
}

void shell_sort(int *arr, size_t len)
{
	const size_t gap_sequence[SHELL_TABLE_SIZE] = {
		1391376, 463792, 198768, 86961, 33936,
		13776, 4592, 1968, 861, 336,
		112, 48, 21, 7, 3, 1
	};
	for (size_t k = 0, gap = 0; k < SHELL_TABLE_SIZE; k++)
	{
		gap = gap_sequence[k];
		for (size_t i = gap, j = 0; i < len; i++)
		{
			/*	insertion sort code, see the similarity	*/
			// int smaller = arr[i];
			// for(j = i - 1; j != (size_t)-1 && arr[j] > smaller; j--)
			// 	arr[j+1] = arr[j];
			// arr[j+1] = smaller;
			int smaller = arr[i];
			for(j = i; j >= gap && arr[j-gap] > smaller; j -= gap)
				arr[j] = arr[j-gap];
			arr[j] = smaller;
		}
	}
}
void print_array(int *arr, size_t len)
{
	for(size_t i = 0; i < len; i++)
		printf("%d ", arr[i]);
	putchar('\n');
}
