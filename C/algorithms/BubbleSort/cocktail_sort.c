/*
 * Cocktail shaker sort
 * A variation of bubble sort, but still not used in practice.
 * Bubble sort always starts from the static 0 to 'len - i',
 * whereas cocktail sort also sets the 'moving' lower boundary.
 */
#include <stdio.h>

#define TEST_VAL1 11

void cocktail_sort(int *arr, size_t len);
void print_array(int *arr, size_t len);

int main(void)
{
	int test1[] = {100, 99, 98, 32, 23, 12, 7, 8, 9, 3, 1};

	cocktail_sort(test1, TEST_VAL1);
	print_array(test1, TEST_VAL1);

	 return 0;
}

void cocktail_sort(int *arr, size_t len)
{
	/*	Boundary	*/
	size_t low = 0, high = len-1;
	/*	Pointer	*/
	size_t mov = 0;
	int temp = 0;
	while(low < high)
	{
		for(size_t i = low; i < high; i++)
		{
			if(arr[i] > arr[i+1])
			{
				temp = arr[i];
				arr[i] = arr[i+1];
				arr[i+1] = temp;
				mov = i;
			}
		}
		/*	Decrease high	*/
		high = mov;

		for(size_t i = high; low < i; i--)
		{
			if(arr[i] < arr[i-1])
			{
				temp = arr[i];
				arr[i] = arr[i-1];
				arr[i-1] = temp;
				mov = i;
			}
		}
		/*	Increase low	*/
		low = mov;
	}
}
void print_array(int *arr, size_t len)
{
	for(size_t i = 0; i < len; i++)
		printf("%d ", arr[i]);
	putchar('\n');
}
