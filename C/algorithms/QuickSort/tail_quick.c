/*
 * Pseudocode:
 * TAIL_RECURSIVE_QUICKSORT(A,p,r):
 *	while p < r
 *		q = PARTITION(A,p,r)
 *		TAIL_RECURSIVE_QUICKSORT(A,p,q-1)
 *		p = q + 1
 *
 * On my desktop intel i5-4460 @ 3.20Ghz,
 * 43343 calls of 'quick_sort' halts the program,
 * whereas this implementation works fine.
 */
#include <stdio.h>
#include <stdlib.h>

#define TEST_VAL1	12

void tail_quick_sort(int *arr, size_t p, size_t r);
void tail_quick_sort_modified(int *arr, size_t p, size_t r);
size_t partition(int *arr, size_t p, size_t r);


void print_array(int *arr, size_t len);

int main(void)
{
	int var1[TEST_VAL1] = {13, 19, 9, 5, 12, 8, 7, 4, 21, 2, 6, 11};
	int var2[TEST_VAL1] = {12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
	int var3[TEST_VAL1] = {13, 19, 9, 5, 12, 8, 7, 4, 21, 2, 6, 11};
	int var4[TEST_VAL1] = {12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

	tail_quick_sort(var1, 0, TEST_VAL1);
	tail_quick_sort(var2, 0, TEST_VAL1);

	tail_quick_sort_modified(var3, 0, TEST_VAL1);
	tail_quick_sort_modified(var4, 0, TEST_VAL1);

	puts("tail_quick_sort");
	print_array(var1, TEST_VAL1);
	print_array(var2, TEST_VAL1);

	putchar('\n');

	puts("tail_quick_sort_modified");
	print_array(var3, TEST_VAL1);
	print_array(var4, TEST_VAL1);

	return 0;
}
void tail_quick_sort(int *arr, size_t p, size_t r)
{
	for(size_t q = 0; p+1 < r; p = q+1)
	{
		q = partition(arr, p, r);
		tail_quick_sort(arr, p, q);
	}
}
/*
 * If you want to see the difference,
 * uncomment 'stack_count' lines.
 * Since choosing the smaller one during the loop,
 * it is likely to invoke 'partition' more
 * resulting in decreament of the stack depth.
 */
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
size_t partition(int *arr, size_t p, size_t r)
{
	int temp = 0;
	int x = arr[r-1];
	size_t i = p, j = p;
	/*	Until the penultimate element.	*/
	for(; j < r-1; j++)
	{
		if(arr[j] <= x)
		{
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
			i++;
		}
	}
	/*	The last element will always be swapped.	*/
	temp = arr[j];
	arr[j] = arr[i];
	arr[i] = temp;

	return i;
}
void print_array(int *arr, size_t len)
{
	for(size_t i = 0; i < len; i++)
		printf("%d ", arr[i]);
	putchar('\n');
}
