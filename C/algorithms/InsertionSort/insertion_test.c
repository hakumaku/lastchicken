#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void isort_old(int *arr, size_t len);
void isort_new(int *arr, size_t len);

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

	// isort_new(test2, test_val);
	// for (size_t i = 0; i < test_val; i++)
	// {
	// 	printf("%d ", test2[i]);
	// }

	s = clock();
		isort_old(test1, test_val);
	e = clock();
	printf("isort_old: %lf\n", difftime(e, s)/CLOCKS_PER_SEC);

	s = clock();
		isort_new(test2, test_val);
	e = clock();
	printf("isort_new %lf\n", difftime(e, s)/CLOCKS_PER_SEC);

	free(test1), free(test2);
	return 0;
}

void isort_old(int *arr, size_t len)
{
	int smaller = 0;
	for(size_t i = 1, j = 0; i < len; i++)
	{
		smaller = arr[i];
		for(j = i - 1; j != (size_t)-1 && arr[j] > smaller; j--)
			arr[j+1] = arr[j];
		arr[j+1] = smaller;
	}
}

/* 1.16 ~ 1.17 faster than old one. */
void isort_new(int *arr, size_t len)
{
	int smaller = 0;
	int *start = arr+1,
		*prev = NULL,
		*current = NULL,
		*end = arr+len;

	while (start < end)
	{
		current = start;
		prev = start-1;
		
		smaller = *start;
		while (current > arr && *prev > smaller)
		{
			*current = *prev;
			current--;
			prev--;
		}
		*current = smaller;
		
		start++;
	}
}
