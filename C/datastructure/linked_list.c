#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
 * A singly linked list
 * Not using a dummy at head.
 */
typedef struct node{
	struct node *next;
	int val;
}node_t;

typedef struct stack{
	node_t *keys;
}stack_t;

typedef struct queue{
	node_t *head;
	node_t *tail;
}queue_t;

node_t *make_node(int input_key);
void free_list(node_t *list);

stack_t *make_stack(void);
void free_stack(stack_t *src);
bool stack_empty(stack_t *src);
void push(stack_t *src, int key);
int pop(stack_t *src);

queue_t *make_queue(void);
void free_queue(queue_t *src);
bool queue_empty(queue_t *src);
void enqueue(queue_t *src, int key);
int dequeue(queue_t *src);

int main(void)
{
	stack_t *test1 = make_stack();
	queue_t *test2 = make_queue();

	for(int i = 0; i < 20; i++)
		push(test1, i);
	for(int i = 0; i < 25; i++)
		printf("%d ", pop(test1));

	putchar('\n');

	for(int i = 0; i < 20; i++)
		enqueue(test2, i);
	for(int i = 0; i < 25; i++)
		printf("%d ", dequeue(test2));

	free_stack(test1);
	free_queue(test2);
	return 0;
}

node_t *make_node(int input_key)
{
	node_t *new = (node_t *)calloc(1, sizeof(node_t));
	new->next = NULL;
	new->val = input_key;

	return new;
}
void free_list(node_t *list)
{
	node_t *temp = NULL;
	while(list)
	{
		temp = list;
		list = list->next;
		free(temp);
	}
}

stack_t *make_stack(void)
{
	stack_t *new = (stack_t *)calloc(1, sizeof(stack_t));
	return new;
}
void free_stack(stack_t *src)
{
	free_list(src->keys);
	free(src);
}
bool stack_empty(stack_t *src)
{
	if(!src->keys)
		return true;
	return false;
}
void push(stack_t *src, int key)
{
	node_t *new = make_node(key);
	new->next = src->keys;
	src->keys = new;
}
int pop(stack_t *src)
{
	if(stack_empty(src))
		return -1;

	node_t *del = src->keys;
	int pop_val = del->val;

	src->keys = del->next;
	free(del);

	return pop_val;
}

queue_t *make_queue(void)
{
	queue_t *new = (queue_t *)calloc(1, sizeof(queue_t));
	return new;
}
void free_queue(queue_t *src)
{
	free_list(src->head);
	free(src);
}
bool queue_empty(queue_t *src)
{
	if(!src->head)
		return true;
	return false;
}
void enqueue(queue_t *src, int key)
{
	node_t *new = make_node(key);
	if(queue_empty(src))
	{
		src->head = new;
		src->tail = new;
	}
	else
	{
		src->tail->next = new;
		src->tail = new;
	}
}
int dequeue(queue_t *src)
{
	if(queue_empty(src))
		return -1;
	node_t *del = src->head;
	int dequeue_val = del->val;

	src->head = del->next;
	free(del);

	return dequeue_val;
}
