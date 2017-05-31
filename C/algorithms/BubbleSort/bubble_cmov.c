#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


void bubble_sort(int *arr, size_t len);
void bubble_sort_cmov(int *arr, size_t len);

int main(int argc, const char *argv[])
{
	if(argc != 2)
	{
		puts("Type test_val");
		exit(1);
	}
	clock_t s, e;
	int test_val = atoi(argv[1]);
	int *test1 = (int *)calloc(test_val, sizeof(int));
	int *test2 = (int *)calloc(test_val, sizeof(int));

	printf("Initializing...(Array size : %d)\n", test_val);
	for(size_t i = 0; i < test_val; i++)
	{
		test1[i] = test_val - i;
		test2[i] = test_val - i;
	}
	puts("Done");

	s = clock();
		bubble_sort(test1, test_val);
	e = clock();
	printf("bubble_sort: %Lf\n", difftime(e, s)/CLOCKS_PER_SEC);

	s = clock();
		bubble_sort_cmov(test2, test_val);
	e = clock();
	printf("bubble_sort_cmov: %Lf\n", difftime(e, s)/CLOCKS_PER_SEC);



	free(test1), free(test2);
	return 0;
}
void bubble_sort(int *arr, size_t len)
{
	int temp = 0;
	// int v1 = 0, v2 = 0;
	for(size_t i = 1; i < len; i++)
	{
		for(size_t j = 0; j < len - i; j++)
		{
			// v1 = arr[j];
			// v2 = arr[j+1];
			// arr[j] = v1 > v2 ? v2 : v1;
			// arr[j+1] = v1 > v2 ? v1 : v2;
			if(arr[j] > arr[j+1])
			{
				temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
			}
		}
	}
}
void bubble_sort_cmov(int *arr, size_t len)
{
	// int temp = 0;
	int v1 = 0, v2 = 0;
	for(size_t i = 1; i < len; i++)
	{
		for(size_t j = 0; j < len - i; j++)
		{
			v1 = arr[j];
			v2 = arr[j+1];
			arr[j] = v1 > v2 ? v2 : v1;
			arr[j+1] = v1 > v2 ? v1 : v2;
			// if(arr[j] > arr[j+1])
			// {
			// 	temp = arr[j];
			// 	arr[j] = arr[j+1];
			// 	arr[j+1] = temp;
			// }
		}
	}
}
