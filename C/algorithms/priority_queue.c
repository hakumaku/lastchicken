/*
 * Pseudocode
 * HEAP_MAXIMUM(A):
 *	return A[1]
 *
 * Pseudocode
 * HEAP_EXTRACT_MAX(A):
 *	if A.heap_size < 1
 *		error "heap underflow"
 *	max = A[1]
 *	A[1] = A[A.heap_size]
 *	A.heap_size = A.heap_size - 1
 *	MAX_HEAPIFY(A,1)
 *	return max
 * (IMO, "heap underflow" should be written "heap overflow".)
 *
 * Pseudocode
 * HEAP_INCREASE_KEY(A,i,key):
 *	if key < A[i]
 *		error "new key is smaller than current key"
 * A[i] = key
 * while i > 1 and A[PARENT(i)] < A[i]
 *	exchange A[i] with A[PARENT(i)]
 *	i = PARENT(i)
 *
 * Pseudocode
 * MAX_HEAP_INSERT(A,key):
 *	A.heap_size = A.heap_size + 1
 *	A[A.heap_size] = NEG_INF
 *	HEAP_INCREASE_KEY(A,A.heap_size,key)
 *
 * Q) Why do we bother setting the key of the inserted node to NEG_INF?
 * A) Otherwise, it will never make it in line 1 of HEAP_INCREASE_KEY.
 *
 * In practice, 'keys' should be reallocated or flexible to cope with
 * inserting and extracting. In this implementation, however,
 * it will just allocate an array large enough to insert a key
 * and when inserting keys, check whether the array is
 * still large enough or not.
 */

#include <stdio.h>
#include <stdlib.h>

#define PARENT(i)	((i-1) >> 1)
#define LEFT(i)		((i<<1) + 1)
#define RIGHT(i)	(LEFT(i) + 1)

#define NEG_INF (~(-1U >> 1))
#define TRUE	1
#define FALSE	0

#define TEST_VAL1 10

/*	heap data structue	*/
typedef struct {
	int *keys;
	size_t length;
	size_t heap_size;
}heap_t;

/*	See also 'heap_sort.c'	*/
heap_t *make_heap(size_t input_length);
void free_heap(heap_t *src);
void max_heapify(heap_t *src, size_t i);
void build_maxheap(heap_t *src);
void heapsort(heap_t *src);

int heap_maximum(heap_t *src);
int heap_extract_max(heap_t *src);
void heap_increase_key(heap_t *src, size_t i, int key);
void max_heap_insert(heap_t *src, int key);

int main(void)
{
	heap_t *var1 = NULL;
	var1 = make_heap(TEST_VAL1+10);
	var1->heap_size = TEST_VAL1;

	var1->keys[0] = 4;
	var1->keys[1] = 1;
	var1->keys[2] = 3;
	var1->keys[3] = 2;
	var1->keys[4] = 16;
	var1->keys[5] = 9;
	var1->keys[6] = 10;
	var1->keys[7] = 14;
	var1->keys[8] = 8;
	var1->keys[9] = 7;

	build_maxheap(var1);
	for(size_t i = 0; i < TEST_VAL1; i++)
	{
		printf("%d ", var1->keys[i]);
	}
	putchar('\n');

	max_heap_insert(var1, 15);
	for(size_t i = 0; i < TEST_VAL1+1; i++)
	{
		printf("%d ", var1->keys[i]);
	}
	putchar('\n');

	heap_extract_max(var1);
	for(size_t i = 0; i < TEST_VAL1; i++)
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
	if(src)
	{
		if(src->keys)
			free(src->keys);
		free(src);
	}
}
void max_heapify(heap_t *src, size_t i)
{
	size_t left = LEFT(i);
	size_t right = RIGHT(i);
	size_t largest = i;
	size_t valid = src->heap_size;

	if(left < valid && src->keys[left] > src->keys[largest])
		largest = left;
	if(right < valid && src->keys[right] > src->keys[largest])
		largest = right;

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
	for(size_t i = (src->length>>1) - 1; i != (size_t)-1; i--)
		max_heapify(src, i);
}
void heapsort(heap_t *src)
{

	int temp = 0;
	build_maxheap(src);
	size_t org_size = src->heap_size;

	for(size_t i = src->length-1; i != 0; i--)
	{
		temp = src->keys[0];
		src->keys[0] = src->keys[i];
		src->keys[i] = temp;
		src->heap_size--;
		max_heapify(src, 0);
	}
	src->heap_size = org_size;
}

int heap_maximum(heap_t *src)
{
	return src->keys[0];
}
int heap_extract_max(heap_t *src)
{
	if(src->heap_size == 0)
	{
		printf("The heap is empty.\n");
		return 0;
	}
	int max = src->keys[0];
	/*
	 * Make the last element be at the top,
	 * meanwhile decrease its size.(It's 'extracting'.)
	 */
	src->keys[0] = src->keys[--src->heap_size];
	max_heapify(src, 0);
	return max;
}
/*
 * This is a part of process that keeps a tree sorted,
 * after inserting a key.
 */
void heap_increase_key(heap_t *src, size_t i, int key)
{
	/*	This part should be more sophiscated than this.	*/
	if(key < src->keys[i])
	{
		printf("The new key is smaller than current key.\n");
		src->heap_size--;
		return;
	}
	src->keys[i] = key;

	/*
	 * 'i' goes up which means it gets decreased, and
	 * eventually becomes 0, or it stops when the current key is
	 * not larger than its parent such that the tree remains
	 * 'max-heap-sorted'.
	 */
	size_t parent = PARENT(i);
	while(i != 0 && src->keys[parent] < src->keys[i])
	{
		int temp = src->keys[parent];
		src->keys[parent] = src->keys[i];
		src->keys[i] = temp;
		i = parent;
		parent = PARENT(i);
	}
}
void max_heap_insert(heap_t *src, int key)
{
	if(src->heap_size == src->length)
	{
		printf("The heap is full.\n");
		return;
	}
	/*
	 * Be careful with the increament operator,
	 * and 'heap_size'.
	 */
	src->keys[src->heap_size++] = NEG_INF;
	heap_increase_key(src, src->heap_size-1, key);
}
