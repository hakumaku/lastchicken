#include "my_list.h"

inline static Node *create_node(void *data)
{
	Node *node = (Node *)calloc(1, sizeof(Node));
	node->next = NULL;
	node->prev = NULL;
	node->data = data;

	return node;
}

List *init_list(void)
{
	List *list = (List *)calloc(1, sizeof(List));
	list->head = NULL;
	list->tail = NULL;
	list->count = 0;

	return list;
}

void free_list(List *src)
{
	if (src)
	{
		Node *node = src->head;

		while (node)
		{
			Node *del = node;
			node = node->next;
			free(del);
		}

		free(src);
	}
}

void enqueue(List *src, void *data)
{
	if (src == NULL)
	{
		return;
	}

	Node *node = create_node(data);

	if (src->tail)
	{
		src->tail->next = node;
		node->prev = src->tail;
	}
	else
	{
		src->head = node;
	}

	src->tail = node;
	src->count++;
}

void *dequeue(List *src)
{
	if (src == NULL || src->head == NULL)
	{
		return NULL;
	}

	Node *node = src->head;
	src->head = node->next;

	if (src->head)
	{
		src->head->prev = NULL;
	}
	else
	{
		src->tail = NULL;
	}

	src->count--;

	void *data = node->data;
	free(node);

	return data;
}

void push(List *src, void *data)
{
	if (src == NULL)
	{
		return;
	}

	Node *node = create_node(data);

	if (src->head)
	{
		node->next = src->head;
		src->head->prev = node;
	}
	else
	{
		src->tail = node;
	}

	src->head = node;
	src->count++;
}

void *pop(List *src)
{
	if (src == NULL || src->head == NULL)
	{
		return NULL;
	}

	Node *node = src->head;
	src->head = node->next;

	if (src->head)
	{
		src->head->prev = NULL;
	}
	else
	{
		src->tail = NULL;
	}

	src->count--;

	void *data = node->data;
	free(node);

	return data;
}

