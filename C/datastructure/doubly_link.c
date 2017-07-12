#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	struct node *prev;
	struct node *next;
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
	new->next = NULL;
	new->prev = NULL;
	new->key = input_key;
	return new;
}
void free_list(list_t *src)
{
	node_t *node = src->head;
	node_t *del = NULL;
	while(node)
	{
		del = node;
		node = node->next;
		free(del);
	}
	free(src);
}
node_t *search_node(list_t *src, int key)
{
	node_t *node = src->head;
	while(node && node->key != key)
		node = node->next;

	return node;
}

void insert_node(list_t *src, int key)
{
	node_t *tail = src->tail;
	node_t *new = make_node(key);
	if(!tail)
		src->head = new;
	if(tail)
	{
		new->prev = tail;
		tail->next = new;
	}
	src->tail = new;
}
void delete_node(list_t *src, int key)
{
	node_t *del = search_node(src, key);
	if(del)
	{
		/*
		 * Always make sure that a ptr to be dereferenced is not NULL.
		 */
		node_t *prev = del->prev;
		node_t *next = del->next;
		if(!prev)
			src->head = next;
		else
			prev->next = next;
		if(!next)
			src->tail = prev;
		else
			next->prev = prev;
		free(del);
	}
}
void print_list(list_t *src)
{
	node_t *node = src->head;
	while(node)
	{
		printf("%d ", node->key);
		node = node->next;
	}
}
