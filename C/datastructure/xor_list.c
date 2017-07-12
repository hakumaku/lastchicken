#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define XOR(a,b)	((node_t *)((unsigned long)a ^ (unsigned long)b))

/* Doubly linked list */
typedef struct node{
	struct node *ptr;
	int key;
}node_t;

typedef struct list{
	node_t *head;
	node_t *tail;
}list_t;

list_t *init_list();
node_t *make_node(int input_key);
void free_list(list_t *src);
node_t *search_node(list_t *src, int key);
void insert_node(list_t *src, int key);
void delete_node(list_t *src, int key);
void print_list(list_t *src);


int main(void)
{
	list_t *test = init_list();

	for(int i = 0; i < 20; i++)
		insert_node(test, i);
	print_list(test); putchar('\n');

	for(int i = 0; i < 30; i++)
		delete_node(test, i);
	print_list(test); putchar('\n');

	for(int i = 0; i < 40; i++)
		insert_node(test, i);
	print_list(test); putchar('\n');

	delete_node(test, 0);
	print_list(test); putchar('\n');

	delete_node(test, 39);
	print_list(test); putchar('\n');

	delete_node(test, 7);
	print_list(test); putchar('\n');

	delete_node(test, 17);
	print_list(test); putchar('\n');

	delete_node(test, 3);
	print_list(test); putchar('\n');

	delete_node(test, 29);
	print_list(test); putchar('\n');

	free_list(test);

	return 0;
}
list_t *init_list()
{
	list_t *new = (list_t *)calloc(1, sizeof(list_t));
	new->head = NULL;
	new->tail = NULL;
	return new;
}
node_t *make_node(int input_key)
{
	node_t *new = (node_t *)calloc(1, sizeof(node_t));
	new->key = input_key;
	new->ptr = 0;
	return new;
}
/*
 * 1) prev--node
 * 2) prev--node--next=XOR(node->ptr,prev)
 * 3) (prev,node)--next
 * 4) prev--(node,next)
 * 5) free(prev)--(node,next)
 */
void free_list(list_t *src)
{
	node_t *prev = NULL;
	node_t *node = src->head;
	node_t *next = NULL;
	while(node)
	{
		next = XOR(node->ptr, prev);
		prev = node;
		node = next;
		free(prev);
	}
	free(src);
}
node_t *search_node(list_t *src, int key)
{
	node_t *prev = NULL;
	node_t *node = src->head;
	node_t *next = NULL;
	while(node && node->key != key)
	{
		next = XOR(node->ptr, prev);
		prev = node;
		node = next;
	}
	return node;
}
void insert_node(list_t *src, int key)
{
	node_t *new = make_node(key);
	node_t *tail = src->tail;
	new->ptr = XOR(tail,NULL);

	if(!tail)
		src->head = new;
	/* XOR(tail->ptr,NULL)--tail--new */
	if(tail)
		tail->ptr = XOR(new,XOR(tail->ptr,NULL));

	src->tail = new;
}
void delete_node(list_t *src, int key)
{
	node_t *prev = NULL;
	node_t *node = src->head;
	node_t *next = NULL;

	/* Searching */
	while(node && node->key != key)
	{
		next = XOR(node->ptr, prev);
		prev = node;
		node = next;
	}
	/* When it found */
	/*
	 * Always make sure that a ptr to be dereferenced is not NULL.
	 */
	if(node)
	{
		next = XOR(node->ptr, prev);
		if(!prev)
			src->head = next;
		else
			prev->ptr = XOR(next, XOR(prev->ptr, node));
		if(!next)
			src->tail = prev;
		else
			next->ptr = XOR(prev, XOR(next->ptr, node));
		/* Free the target */
		free(node);
	}
}
void print_list(list_t *src)
{
	node_t *prev = NULL;
	node_t *node = src->head;
	node_t *next = NULL;

	while(node)
	{
		printf("%d ", node->key);
		next = XOR(node->ptr,prev);
		prev = node;
		node = next;
	}
}
