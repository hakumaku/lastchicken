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

#define TEST_VAL 5
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

int main(void)
{
	heap_t *var1 = NULL;
	var1 = make_heap(TEST_VAL);

	for(size_t i = 0; i < TEST_VAL; i++)
	{
		/*	var1->keys[var1->heap_size++] = i	*/
		var1->keys[i] = i;
		var1->heap_size++;
		printf("%d ", i);
	}
	putchar('\n');

	build_maxheap(var1);
	for(size_t i = 0; i < TEST_VAL; i++)
	{
		printf("%d ", var1->keys[i]);
	}
	putchar('\n');

	free_heap(var1);

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
	/*
	if(left < valid && src->keys[left] > src->keys[largest])
		largest = left;
	if(right < valid && src->keys[right] > src->keys[largest])
		largest = right;
	*/
	if(left < valid)
	{
		size_t test = src->keys[left] > src->keys[largest] ? left : largest;
		largest = test;
	}
	if(right < valid)
	{
		size_t test = src->keys[right] > src->keys[largest] ? right : largest;
		largest = test;
	}

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