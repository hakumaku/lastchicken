#include "priority_queue.h"

typedef struct list_data List;
typedef struct list_node ListNode;

struct list_data
{
	struct list_node *head;
	struct list_node *tail;
};

struct list_node
{
	struct list_node *next;
	struct list_node *prev;
	int key;
	int priority;
};

static ListNode *create(ListNode *next, ListNode *prev, int key, int priority);
static void push(List *src, int key, int priority);
static int pop(List *src);

static ListNode *create(ListNode *next, ListNode *prev, int key, int priority)
{
	ListNode *node = (ListNode *)calloc(1, sizeof(ListNode));
	node->next = next;
	node->prev = prev;
	node->key = key;
	node->priority = priority;

	return node;
}

static void push(List *src, int key, int priority)
{
	ListNode **node = &src->head;
	ListNode *prev_node = NULL;

	while (*node)
	{
		prev_node = *node;

		if (prev_node->key >= priority)
		{
			node = &prev_node->next;
		}
		else
		{
			break;
		}
	}

	*node = create(*node, prev_node, key, priority);
}

static int pop(List *src)
{
	if (src->head == NULL)
	{
		return -1;
	}

	ListNode *node = src->head;
	src->head = node->next;

	if (src->head)
	{
		src->head->prev = NULL;
	}
	else
	{
		src->tail = NULL;
	}

	int key = node->key;
	free(node);

	return key;
}

