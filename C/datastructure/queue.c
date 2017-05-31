/*
 * Circular Queue
 *
 * Psuedocode
 * ENQUEUE(Q,x):
 *	Q[Q.tail] = x
 *	if Q.tail == Q.length
 *		Q.tail = 1
 *	else
 *		Q.tail = Q.tail + 1
 *
 * DEQUUEUE(Q):
 *	x = Q[Q.head];
 *	if Q.head == Q.length
 *		Q.head = 1
 *	else
 *		Q.head = Q.head + 1
 *	return x
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
void enqueue(queue_t *src, int x);
int dequeue(queue_t *src);

int main(void)
{
	queue_t *test = make_queue(10);
	for(int i = 0; i < 15; i++)
		enqueue(test, i);
	for(int i = 0; i < 15; i++)
		printf("%d ", dequeue(test));

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
void enqueue(queue_t *src, int x)
{
	if(queue_full(src))
		return;

	size_t tail = src->tail;
	size_t v1 = tail+1, v2 = v1 - src->size;
	src->keys[tail] = x;

	tail = v1 < v2 ? v1 : v2;
	src->tail = tail;
	src->count++;
}
int dequeue(queue_t *src)
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
