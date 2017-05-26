/*
 * Psuedocode
 * RADIX_SORT(A,d):
 *	for i = 1 to d
 *		use a stable sort to sort array A on digit i
 *
 * Given n b-bit numbers and any positive integer r <= b,
 * RADIX_SORT correctly sorts these numbers in theta((b/r)(n+2^r)) time
 * if the stable sort it uses takes theta(n+k) time
 * for inputs in the range 0 to k.
 * Theoretically,
 * 1) b < floor(log n), r should be such that r <= b.
 * 2) b >= floor(log n), r should be floor(log n).
 */
#include <stdio.h>
#include <stdlib.h>

#define TEST_VAL1 21

void radix_sort(int *arr, size_t len);
void print_array(int *arr, size_t len);

int main(void)
{
	int arr[TEST_VAL1] = { 0 };
	for(int i = 0; i < TEST_VAL1; i++)
		arr[i] = TEST_VAL1 - i;

	radix_sort(arr, TEST_VAL1);
	print_array(arr, TEST_VAL1);

	return 0;
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
	 * shifting it to the least significant bit position,
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
	}

	free(buf);
	free(table);
}
void print_array(int *arr, size_t len)
{
	for(size_t i = 0; i < len; i++)
		printf("%d ", arr[i]);
	putchar('\n');
}
