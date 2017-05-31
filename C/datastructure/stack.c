/*
 * Psuedocode
 * STACK_EMPTY(S):
 *	if S.top == 0
 *		return TRUE
 *	else
 *		return FALSE
 *
 * PUSH(S,x):
 *	S.top = S.top + 1
 *	S[S.top] = x
 *
 * POP(S):
 *	if STACK_EMPTY(S)
 *		error "underflow"
 *	else
 *		S.top = S.top - 1
 *		return S[S.top+1]
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
	int *keys;
	size_t count;
	size_t size;
} stack_t;

stack_t *make_stack(size_t input_size);
void free_stack(stack_t *src);
bool stack_empty(stack_t *src);
bool stack_full(stack_t *src);
void push(stack_t *src, int x);
int pop(stack_t *src);

int main(void)
{
	stack_t *test = make_stack(10);

	for(int i = 0; i < 15; i++)
		push(test, i);
	for(int i = 0; i < 15; i++)
		printf("%d ", pop(test));

	free_stack(test);
	return 0;
}
stack_t *make_stack(size_t input_size)
{
	stack_t *new = (stack_t *)calloc(1, sizeof(stack_t));
	new->keys = (int *)calloc(input_size, sizeof(int));
	new->size = input_size;
	new->count = 0;

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
void push(stack_t *src, int x)
{
	if(stack_full(src))
		return;
	src->keys[src->count++] = x;
}
int pop(stack_t *src)
{
	if(stack_empty(src))
		return -1;
	int pop_val = src->keys[--src->count];
	return pop_val;
}
