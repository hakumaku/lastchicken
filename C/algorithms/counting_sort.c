/*
 * Pseudocode
 * COUNTING_SORT(A,B,k):
 *	let C[0..k] be a new array
 *	for i = 0 to k
 *		C[i] = 0;
 *	for j = 1 to A.length
 *		C[A[j]] = C[A[j]] + 1
 *	// C[i] now contains the number of elements equal to i.
 *	for i = 1 to k
 *		C[i] = C[i] + C[i - 1]
 *	// C[i] now contains the number of elements less than or equal to i.
 *	for j = A.length downto 1
 *		B[C[A[j]]] = A[j]
 *		C[A[j]] = C[A[j]] - 1
 *
 * Q) why j = A.length downto 1?
 * A) It will work properly, but they are not 'stable'.
 * Equal elements will appear in reverse order in the sorted array.
 * e.g)
 * array: 1 6a 8 3 6b 0 6c 4
 *
 * -NOT stable
 * B: X X X X  X  X  X  X	C: 1 2 3 4 7 8
 * B: X 1 X X  X  X  X  X	C: 1 1 3 4 7 8
 * B: X 1 X X  X  X  6a X	C: 1 1 3 4 6 8
 * B: X 1 X X  X  X  6a 8	C: 1 1 3 4 6 7
 * B: X 1 3 X  X  X  6a 8 	C: 1 1 2 4 6 7
 * B: X 1 3 X  X  6b 6a 8	C: 1 1 2 4 5 7
 * B: 0 1 3 X  X  6b 6a 8 	C: 0 1 2 4 5 7
 * B: 0 1 3 X  6c 6b 6a 8	C: 0 1 2 4 4 7
 * B: 0 1 3 4  6c 6b 6a 8	C: 0 1 2 3 4 7
 *
 * -stable
 * B: X X X 4  X  X  X  X	C: 1 2 3 3 7 8
 * B: X X X 4  X  X  6c X	C: 1 2 3 3 6 8
 * B: 0 X X 4  X  X  6c X	C: 0 2 3 3 6 8
 * B: 0 X X 4  X  6b 6c X	C: 0 2 3 3 5 8
 * B: 0 X 3 4  X  6b 6c X	C: 0 2 2 3 5 8
 * B: 0 X 3 4  X  6b 6c 8	C: 0 2 2 3 5 7
 * B: 0 X 3 4  6a 6b 6c 8	C: 0 2 2 3 4 7
 * B: 0 1 3 4  6a 6b 6c 8	C: 0 1 2 3 4 7
 */
#include <stdio.h>
#include <stdlib.h>

#define TEST_VAL1	11

void counting_sort(int *src, int *dest, int len);

int main(void)
{
	int var1[TEST_VAL1] = {6, 0, 2, 0, 1, 3, 4, 6, 1, 3, 2};
	int dest1[TEST_VAL1] = { 0 };

	counting_sort(var1, dest1, TEST_VAL1);
	for(int i = 0; i < TEST_VAL1; i++)
		printf("%d ", dest1[i]);
	putchar('\n');

	return 0;
}

void counting_sort(int *src, int *dest, int len)
{
	int *table = (int *)calloc(len, sizeof(int));
	int *prev = table;
	int src_val = 0;
	/*	C[i] now contains the number of elements equal to i.	*/
	for(size_t i = 0; i < len; i++)
		table[src[i]]++;
	/*	C[i] now contains the number of elements less than or equal to i.	*/
	for(size_t i = 1; i < len; i++, prev++)
		table[i] += *prev;

	for(size_t i = len-1; i != (size_t)-1; i--)
	{
		src_val = src[i];
		dest[table[src_val]] = src_val;
		table[src_val]--;
	}
}
