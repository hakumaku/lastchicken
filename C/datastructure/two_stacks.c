/*
 * [---stack1--> <--stack2---]
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
	int *keys;
	/* From top to bottom */
	size_t ti;
	/* From bottom to top(original) */
	size_t bi;
	size_t count;
	size_t size;
} stack_t;

stack_t *make_stack(size_t input_size);
void free_stack(stack_t *src);
bool stack_empty(stack_t *src);
bool stack_full(stack_t *src);
void push_top(stack_t *src, int x);
void push_bottom(stack_t *src, int x);
int pop_top(stack_t *src);
int pop_bottom(stack_t *src);

int main(void)
{
	stack_t *test = make_stack(16);

	for(int i = 0; i < 10; i++)
	{
		push_top(test, i);
		push_bottom(test, i);
	}
	for(int i = 0; i < 10; i++)
	{
		printf("%d ", pop_top(test));
		printf("%d ", pop_bottom(test));
	}

	free_stack(test);
	return 0;
}
stack_t *make_stack(size_t input_size)
{
	stack_t *new = (stack_t *)calloc(1, sizeof(stack_t));
	new->keys = (int *)calloc(input_size, sizeof(int));
	new->size = input_size;
	new->count = 0;

	new->ti = 0;
	new->bi = 0;

	return new;
}
void free_stack(stack_t *src)
{
	if(src)
	{
		free(src->keys);
		free(src);
	}
}
bool stack_empty(stack_t *src)
{
	if(!src->count)
		return true;
	return false;
}
bool stack_full(stack_t *src)
{
	if(src->count == src->size)
		return true;
	return false;
}
/* The original push */
void push_top(stack_t *src, int x)
{
	if(stack_full(src))
		return;
	src->keys[src->ti++] = x;
	src->count++;
}
/* The opposite of the original push */
void push_bottom(stack_t *src, int x)
{
	if(stack_full(src))
		return;
	src->keys[src->bi++] = x;
	src->count++;
}
/* The original pop */
int pop_top(stack_t *src)
{
	if(stack_empty(src))
		return -1;
	int pop_val = src->keys[--src->ti];
	src->count--;

	return pop_val;
}
/* The opposite of the original pop */
int pop_bottom(stack_t *src)
{
	if(stack_empty(src))
		return -1;
	int pop_val = src->keys[--src->bi];
	src->count--;

	return pop_val;
}
