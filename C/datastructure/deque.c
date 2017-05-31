/*
 * Double-ended Queue
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
	int *keys;
	size_t head;
	size_t tail;
	size_t count;
	size_t size;
} queue_t;

queue_t *make_queue(size_t input_size);
void free_queue(queue_t *src);
bool queue_empty(queue_t *src);
bool queue_full(queue_t *src);
void enqueue_head(queue_t *src, int x);
void enqueue_tail(queue_t *src, int x);
int dequeue_head(queue_t *src);
int dequeue_tail(queue_t *src);

void print_array(int *arr, size_t len);

int main(void)
{
	queue_t *test = make_queue(16);

	for(int i = 0; i < 10; i++)
	{
		enqueue_head(test, i);
		enqueue_tail(test, i);
		print_array(test->keys, 16);
	}
	for(int i = 0; i < 10; i++)
	{
		printf("%d ", dequeue_head(test));
		printf("%d ", dequeue_tail(test));
	}

	free_queue(test);
	return 0;
}

queue_t *make_queue(size_t input_size)
{
	queue_t *new = (queue_t *)calloc(1, sizeof(queue_t));
	new->keys = (int *)calloc(input_size, sizeof(int));
	new->count = 0;
	new->size = input_size;
	new->head = 0;
	new->tail = 0;

	return new;
}
void free_queue(queue_t *src)
{
	if(src)
	{
		free(src->keys);
		free(src);
	}
}
bool queue_empty(queue_t *src)
{
	if(!src->count)
		return true;
	return false;
}
bool queue_full(queue_t *src)
{
	if(src->count == src->size)
		return true;
	return false;
}
/*	The opposite of the original enqueue	*/
void enqueue_head(queue_t *src, int x)
{
	if(queue_full(src))
		return;

	size_t head = src->head;
	/*	It assumes that src->size != UINT_MAX.	*/
	size_t v1 = head-1, v2 = v1 + src->size;
	head = v2 < v1 ? v2 : v1;

	src->keys[head] = x;
	src->head = head;
	src->count++;
}
/*	The original enqueue	*/
void enqueue_tail(queue_t *src, int x)
{
	if(queue_full(src))
		return;

	size_t tail = src->tail;
	/*	It assumes that src->size != UINT_MAX.	*/
	size_t v1 = tail+1, v2 = v1 - src->size;
	src->keys[tail] = x;

	tail = v1 < v2 ? v1 : v2;
	src->tail = tail;
	src->count++;
}
/*	The original dequeue	*/
int dequeue_head(queue_t *src)
{
	if(queue_empty(src))
		return -1;

	size_t head = src->head;
	size_t v1 = head+1, v2 = v1 - src->size;
	int dequeue_val = src->keys[head];

	head = v1 < v2 ? v1 : v2;
	src->head = head;
	src->count--;

	return dequeue_val;
}
/*	The opposite of the original dequeue	*/
int dequeue_tail(queue_t *src)
{
	if(queue_empty(src))
		return -1;

	size_t tail = src->tail;
	size_t v1 = tail-1, v2 = v1 + src->size;
	tail = v2 < v1 ? v2 : v1;

	int dequeue_val = src->keys[tail];
	src->tail = tail;
	src->count--;

	return dequeue_val;
}
void print_array(int *arr, size_t len)
{
	for(size_t i = 0; i < len; i++)
		printf("%d ", arr[i]);
	putchar('\n');
}
