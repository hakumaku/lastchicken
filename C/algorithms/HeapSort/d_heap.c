/*
 * This data structure allows decrease priority operations
 * to be performed more quickly than binary heaps,
 * at the expense of slower delete minimum operations.
 */

#include <stdio.h>
#include <stdlib.h>

#define D_SIZE		4
#define NEG_INF (~(-1U >> 1))
#define TEST_VAL1 50
/*
 * For D == d,
 * CHILDREN(i,j) is ((i*d) + j+1),
 * where j is index such that 0 <= j < d.
 */
#define CHILDREN(i,j)	((i<<2) + j+1)
/*
 * For D == d,
 * PARENT(i) is ((i-i)/d)
 */
#define PARENT(i)		((i-1)>>2)

typedef struct {
	int *keys;
	size_t heap_size;
	size_t length;
}heap_t;

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
	var1 = make_heap(TEST_VAL1+3);
	for(size_t i = 0; i < TEST_VAL1; i++)
	{
		/*	var1->keys[var1->heap_size++] = i	*/
		var1->keys[i] = i;
		var1->heap_size++;
	}

	build_maxheap(var1);
	for(size_t i = 0; i < TEST_VAL1; i++)
	{
		printf("%d ", var1->keys[i]);
	}
	putchar('\n');

	max_heap_insert(var1, 100);
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

	heapsort(var1);
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
	new->heap_size = 0;
	new->length = input_length;

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
/*
 * Selecting the largest one in children nodes.
 */
void max_heapify(heap_t *src, size_t i)
{
	size_t child = 0;
	size_t largest = i;
	size_t valid = src->heap_size;
	for(size_t j = 0; j < D_SIZE; j++)
	{
		child = CHILDREN(i,j);
		if(child < valid && src->keys[child] > src->keys[largest])
		 	largest = child;
	}
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
	for(size_t i = (src->length>>2) - 1; i != (size_t)-1; i--)
		max_heapify(src, i);
}
void heapsort(heap_t *src)
{
	int temp = 0;
	build_maxheap(src);
	size_t org_size = src->heap_size;
	for(size_t i = src->heap_size-1; i != 0; i--)
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
	src->keys[0] = src->keys[--src->heap_size];
	max_heapify(src, 0);

	return max;
}
void heap_increase_key(heap_t *src, size_t i, int key)
{
	if(key < src->keys[i])
	{
		printf("The new key is smaller than current key.\n");
		src->heap_size--;
		return;
	}
	src->keys[i] = key;
	size_t parent = PARENT(i);
	/*
	 * If a tree is not enormous enough,
	 * it does not seem to improve performance.
	 */
	// int pval = 0, cval = 0;
	// while(i != 0 && (pval = src->keys[parent]) < (cval = src->keys[i]))
	// {
	// 	src->keys[parent] = cval;
	// 	src->keys[i] = pval;
	// 	i = parent;
	// 	parent = PARENT(i);
	// }
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
	src->keys[src->heap_size++] = NEG_INF;
	heap_increase_key(src, src->heap_size-1, key);
}
