#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void tail_quick_sort_modified(int *arr, size_t p, size_t r);
void quick_sort(int *arr, size_t p, size_t r);
size_t partition(int *arr, size_t p, size_t r);
void radix_sort(int *arr, size_t len);

int main(int argc, const char *argv[])
{
	if(argc != 2)
	{
		puts("Type the size of array.");
		exit(1);
	}
	int size = atoi(argv[1]);
	clock_t s, e;
	int *test1 = (int *)calloc(size, sizeof(int));
	int *test2 = (int *)calloc(size, sizeof(int));
	int *test3 = (int *)calloc(size, sizeof(int));

	printf("Initializing...(Array size : %d)\n", size);
	for(int i = 0; i < size; i++)
	{
		test1[i] = size - 1;
		test2[i] = size - 1;
		test3[i] = size - 1;
	}
	puts("Done");

	puts("tail_quick_sort_modified processing..");
	s = clock();
		tail_quick_sort_modified(test1, 0, size);
	e = clock();
	printf("tail_quick_sort_modified: %Lf\n", difftime(e,s)/CLOCKS_PER_SEC);

	puts("quick_sort processing..");
	s = clock();
		quick_sort(test2, 0, size);
	e = clock();
	printf("quick_sort: %Lf\n", difftime(e,s)/CLOCKS_PER_SEC);

	puts("radix_sort processing..");
	s = clock();
		radix_sort(test3, size);
	e = clock();
	printf("radix_sort: %Lf\n", difftime(e,s)/CLOCKS_PER_SEC);

	return 0;
}

void tail_quick_sort_modified(int *arr, size_t p, size_t r)
{
	// static int stack_count = 0;
	// printf("stack_count:%d\n", ++stack_count);
	while(p+1 < r)
	{
		size_t q = partition(arr, p, r);
		/*	Reverse the symbol and observe the result.	*/
		if(q < (p+r)>>1)
		{
			tail_quick_sort_modified(arr, p, q);
			p = q+1;
		}
		else
		{
			tail_quick_sort_modified(arr, q+1, r);
			r = q;
		}
	}
	// printf("stack_count:%d\n", --stack_count);
}
void quick_sort(int *arr, size_t p, size_t r)
{
	/*
	 * It removes out an element, arr[q].
	 * every time it is called.
	 * It is obvious that arr[q] must be at the
	 * correct position, all the left of which are
	 * less than or equal to q, the right greater than q.
	 */
	if(p+1 < r)
	{
		size_t q = partition(arr, p, r);
		/*	[p,q)	*/
		quick_sort(arr, p, q);
		/*	(q,r)	*/
		quick_sort(arr, q+1, r);
	}
}
size_t partition(int *arr, size_t p, size_t r)
{
	int temp = 0;
	int x = arr[r-1];
	size_t i = p, j = p;
	/*	Until the penultimate element.	*/
	for(; j < r-1; j++)
	{
		/*	The last element will always be swapped.	*/
		if(arr[j] <= x)
		{
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
			i++;
		}
	}
	temp = arr[j];
	arr[j] = arr[i];
	arr[i] = temp;

	return i;
}
void radix_sort(int *arr, size_t len)
{
	size_t radix = 0, table_len = 0;
	int mask = 0, lsb_pos = 0;
	int *buf = NULL, *table = NULL, *prev = NULL;
	int arr_pos = 0, arr_val = 0;

	/*
	 * It just simply chooses 'r'.
	 * Other strageties can be applied.
	 */
	for(size_t n = len; n; n >>= 1)
		radix++;
	mask = (1 << radix) - 1;
	table_len = mask+1;

	buf = (int *)calloc(len, sizeof(int));
	table = (int *)calloc(table_len, sizeof(int));
	prev = table;

	/*
	 * In 'counting_sort.c', it was simply 'table[arr[i]]++;'
	 * with a strong assumption that all elements in the array
	 * are less than or eqaul to its length.
	 * In this code, it coerces the assumption to always hold true
	 * by masking arr[i] and then
	 * shifting it to the least significant digit position,
	 * yieding a value less than (mask+1).
	 */
	while(mask)
	{
		for(size_t i = 0; i < len; i++)
		{
			arr_pos = (arr[i] & mask) >> lsb_pos;
			table[arr_pos]++;
		}

		for(size_t i = 1; i < table_len; i++, prev++)
			table[i] += *prev;

		for(size_t i = len-1; i != (size_t)-1; i--)
		{
			arr_val = arr[i];
			arr_pos = (arr_val & mask) >> lsb_pos;
			buf[table[arr_pos]-1] = arr_val;
			table[arr_pos]--;
		}

		/*	Writing back.	*/
		for(size_t i = 0; i < len; i++)
			arr[i] = buf[i];

		mask <<= radix;
		lsb_pos += radix;
		prev = table;
	}

	free(buf);
	free(table);
}
