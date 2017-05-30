#include <stdio.h>
#include <stdbool.h>

#define TEST_VAL1 11

void oddeven_sort(int *arr, size_t len);
void print_array(int *arr, size_t len);

int main(void)
{
	int test1[] = {100, 99, 98, 32, 23, 12, 7, 8, 9, 3, 1};

	oddeven_sort(test1, TEST_VAL1);
	print_array(test1, TEST_VAL1);

	return 0;
}

void oddeven_sort(int *arr, size_t len)
{
	int temp = 0;
	bool sorted = false;
	while(!sorted)
	{
		sorted = true;
		for(size_t i = 1; i < len-1; i += 2)
		{
			if(arr[i+1] < arr[i])
			{
				temp = arr[i];
				arr[i] = arr[i+1];
				arr[i+1] = temp;
				sorted = false;
			}
		}
		for(size_t i = 0; i < len-1; i += 2)
		{
			if(arr[i+1] < arr[i])
			{
				temp = arr[i];
				arr[i] = arr[i+1];
				arr[i+1] = temp;
				sorted = false;
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
