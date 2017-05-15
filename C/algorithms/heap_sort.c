/*
 * Pseudocode
 * PARENT(i):
 *	return floor(i/2)
 *
 * LEFT(i):
 *	return 2i
 *
 * RIGHT(i):
 *	return 2i + 1
 *
 * Pseudocode
 * BUILD_MAX_HEAP(A):
 *	A.heap_size = A.length
 *	for i = floor(A.length/2) downto 1
 *		MAX_HEAPIFY(A,i)
 *
 * Q) Why does it start from 'floor(A.length/2)' instead of '1'?
 * A) Since it works under the assumption that the subtrees rooted at the two
 * children also are both 'Max heaps', you cannot make 'i' start from '1' and
 * increase it to 'floor(A.length/2)'.
 *
 * Pseudocode
 * MAX_HEAPIFY(A,i):
 *	l = LEFT(i)
 *	r = RIGHT(i)
 *	if l <= A.heap-size and A[l] > A[i]
 *		largest = l
 *	else
 *		largest = i
 *	if r <= A.heap-size and A[r] > A[largest]
 *		largest = r
 *	if largest != i
 *		exchange A[i] with A[largest]
 *		MAX_HEAPIFY(A,largest)
 *
 * (what MAX_HEAPIFY function does...)
 * (a)
 * 16─┬─10─┬─3
 *	  │    └─9
 *	  └─(4)─┬─7─┐
 *			│   └─1
 *			└─14─┬─8
 *				 └─2
 * (b)
 * 16─┬─10─┬─3
 *	  │    └─9
 *	  └─14─┬─7─┐
 *		   │   └─1
 *		   └─(4)─┬─8
 *				 └─2
 * (c)
 * 16─┬─10─┬─3
 *	  │    └─9
 *	  └─14─┬─7─┐
 *		   │   └─1
 *		   └─8─┬─(4)
 *			   └─2
 *
 * Pseudocode
 * HEAPSORT(A):
 *	BUILD_MAX_HEAP(A)
 *	for i = A.length downto 2
 *		exchange A[1] with A[i]
 *		A.heap-size = A.heap-size - 1
 *		MAX_HEAPIFY(A, 1)
 *
 * Note that the above HEAPSORT function includes BUILD_MAX_HEAP.
 * BUILD_MAX_HEAP takes time O(n) and each of the n - 1 calls
 * to MAX_HEAPIFY takes time O(lgn) resulting in time O(nlgn).
 */
#include <stdio.h>
#include <stdlib.h>

/*
 * Better be implemented with "macro" or "inline".
 * Since C always starts subscripting from 0, not 1,
 * the following functions are applied slightly differently.
 */
#define PARENT(i)	((i-1) >> 1)
#define LEFT(i)		((i<<1) + 1)
#define RIGHT(i)	(LEFT(i) + 1)

#define TEST_VAL1 16
#define TEST_VAL2 9
#define TEST_VAL3 10
#define TRUE	1
#define FALSE	0


/*	heap data structue	*/
typedef struct {
	/*
	 * "Key"s, usually they are not themselves meaningful data.
	 *	They are in pratice carried with actual data.
	 */
	int *keys;
	/*	the maximum size of keys	*/
	size_t length;
	/*	the current size of keys such that 0 <= heap_size <= length	*/
	size_t heap_size;
}heap_t;

heap_t *make_heap(size_t input_length);
void free_heap(heap_t *src);
void max_heapify(heap_t *src, size_t i);
void build_maxheap(heap_t *src);
void heapsort(heap_t *src);

int main(void)
{
	heap_t *var1 = NULL;
	heap_t *var2 = NULL;
	heap_t *var3 = NULL;
	var1 = make_heap(TEST_VAL1);
	var2 = make_heap(TEST_VAL2);
	var3 = make_heap(TEST_VAL3);
	var2->heap_size = TEST_VAL2;
	var3->heap_size = TEST_VAL3;

	for(size_t i = 0; i < TEST_VAL1; i++)
	{
		/*	var1->keys[var1->heap_size++] = i	*/
		var1->keys[i] = i;
		var1->heap_size++;
		printf("%d ", i);
	}
	putchar('\n');
	var2->keys[0] = 5;
	var2->keys[1] = 3;
	var2->keys[2] = 17;
	var2->keys[3] = 10;
	var2->keys[4] = 84;
	var2->keys[5] = 19;
	var2->keys[6] = 6;
	var2->keys[7] = 22;
	var2->keys[8] = 9;

	var3->keys[0] = 4;
	var3->keys[1] = 1;
	var3->keys[2] = 3;
	var3->keys[3] = 2;
	var3->keys[4] = 16;
	var3->keys[5] = 9;
	var3->keys[6] = 10;
	var3->keys[7] = 14;
	var3->keys[8] = 8;
	var3->keys[9] = 7;


	build_maxheap(var1);
	for(size_t i = 0; i < TEST_VAL1; i++)
	{
		printf("%d ", var1->keys[i]);
	}
	putchar('\n');

	build_maxheap(var2);
	for(size_t i = 0; i < TEST_VAL2; i++)
	{
		printf("%d ", var2->keys[i]);
	}
	putchar('\n');

	heapsort(var3);
	for(size_t i = 0; i < TEST_VAL3; i++)
	{
		printf("%d ", var3->keys[i]);
	}
	putchar('\n');

	free_heap(var1);
	free_heap(var2);
	free_heap(var3);

	return 0;
}

heap_t *make_heap(size_t input_length)
{
	heap_t *new = NULL;
	new = (heap_t *)calloc(1, sizeof(heap_t));
	new->keys = (int *)calloc(input_length, sizeof(int));
	new->length = input_length;
	new->heap_size = 0;

	return new;
}
void free_heap(heap_t *src)
{
	free(src->keys);
	free(src);
}
/*
 * If you want to make 'min_heapify',
 * simply change comparison symbols.¯\_(ツ)_/¯
 */
void max_heapify(heap_t *src, size_t i)
{
	size_t left = LEFT(i);
	size_t right = RIGHT(i);
	size_t largest = i;
	size_t valid = src->heap_size;

	/*
	 * 'largest' was previously initialized as 'i'
	 * This is selecting the maximum of three.
	 */
	if(left < valid && src->keys[left] > src->keys[largest])
		largest = left;
	if(right < valid && src->keys[right] > src->keys[largest])
		largest = right;

	/*	largest is either left, right or i 	*/
	if(largest != i)
	{
		int temp = src->keys[i];
		src->keys[i] = src->keys[largest];
		src->keys[largest] = temp;
		max_heapify(src, largest);
	}
}
void build_maxheap(heap_t *src)
{
	for(size_t i = (src->length >> 1); i != (size_t)-1; i--)
		max_heapify(src, i);
}
void heapsort(heap_t *src)
{

	int temp = 0;
	build_maxheap(src);
	/*	To restore its original value.	*/
	size_t org_size = src->heap_size;

	/*	Be careful with subscripting.	*/
	for(size_t i = src->length-1; i != 0; i--)
	{
		temp = src->keys[0];
		src->keys[0] = src->keys[i];
		src->keys[i] = temp;
		/*
		 * It just sorted 'one' element, keys[i],
		 * and the rest remains unsorted.
		 * The array needs heapifying with one less the size.
		 */
		src->heap_size--;
		max_heapify(src, 0);
	}
	src->heap_size = org_size;
}
