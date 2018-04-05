#include "priority_queue.h"

static PriorListNode *create(PriorListNode *next, void *data, size_t priority);

PriorList *init_prior_list(void)
{
	PriorList *list = (PriorList *)calloc(1, sizeof(PriorList));
	list->head = NULL;
	list->tail = NULL;
	list->count = 0;

	return list;
}

void free_prior_list(PriorList *src)
{
	if (src)
	{
		PriorListNode *node = src->head;

		while (node)
		{
			PriorListNode *del = node;
			node = node->next;
			free(del);
		}

		free(src);
	}
}

static PriorListNode *create(PriorListNode *next, void *data, size_t priority)
{
	PriorListNode *node = (PriorListNode *)calloc(1, sizeof(PriorListNode));
	node->next = next;
	node->data = data;
	node->priority = priority;

	return node;
}

void prior_push(PriorList *src, void *data, size_t priority)
{
	if (src == NULL)
	{
		return;
	}

	PriorListNode **parent = &src->head;

	while (*parent)
	{
		PriorListNode *node = *parent;

		if (node->priority <= priority)
		{
			parent = &node->next;
		}
		else
		{
			break;
		}
	}

	src->count++;
	*parent = create(*parent, data, priority);
}

void *prior_pop(PriorList *src)
{
	if (src == NULL || src->head == NULL)
	{
		return NULL;
	}

	PriorListNode *node = src->head;
	src->head = node->next;

	if (src->head == NULL)
	{
		src->tail = NULL;
	}

	src->count--;

	void *data = node->data;
	free(node);

	return data;
}

