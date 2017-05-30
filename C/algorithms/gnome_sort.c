/*
 * A variation of insertion sort.
 * The average, or expected, running time is O(n^2),
 * but tends towards O(n) if the list is initially almost sorted.
 */
#include <stdio.h>

#define TEST_VAL1 11

void gnome_sort(int *arr, size_t len);
void print_array(int *arr, size_t len);

int main(void)
{
	int test1[] = {100, 99, 98, 32, 23, 12, 7, 8, 9, 3, 1};

	gnome_sort(test1, TEST_VAL1);
	print_array(test1, TEST_VAL1);

	return 0;
}

void gnome_sort(int *arr, size_t len)
{
	int temp = 0;
	for(size_t i = 1; i < len;)
	{
		if(i == 0 || arr[i] > arr[i-1])
			i++;
		else
		{
			temp = arr[i];
			arr[i] = arr[i-1];
			arr[i-1] = temp;
			i--;
		}
	}
}
void print_array(int *arr, size_t len)
{
	for(size_t i = 0; i < len; i++)
		printf("%d ", arr[i]);
	putchar('\n');
}
