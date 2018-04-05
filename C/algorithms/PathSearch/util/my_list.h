#ifndef MY_LIST_H

#define MY_LIST_H
#include <stdio.h>
#include <stdlib.h>

typedef struct linked_list List;
typedef struct linked_node Node;

struct linked_list
{
	struct linked_node *head;
	struct linked_node *tail;
	size_t count;
};

struct linked_node
{
	struct linked_node *next;
	struct linked_node *prev;
	void *data;
};

List *init_list(void);
void free_list(List *src);
void enqueue(List *src, void *data);
void *dequeue(List *src);
void push(List *src, void *data);
void *pop(List *src);

#endif

