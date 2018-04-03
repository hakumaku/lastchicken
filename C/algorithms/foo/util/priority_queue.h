#ifndef PRIORITY_QUEUE_H

#define PRIORITY_QUEUE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct prior_list_data PriorList;
typedef struct prior_list_node PriorListNode;

struct prior_list_data
{
	struct prior_list_node *head;
	struct prior_list_node *tail;
	size_t count;
};

struct prior_list_node
{
	struct prior_list_node *next;
	void *data;
	size_t priority;
};

PriorList *init_prior_list(void);
void prior_push(PriorList *src, void *data, size_t priority);
void *prior_pop(PriorList *src);

#endif

