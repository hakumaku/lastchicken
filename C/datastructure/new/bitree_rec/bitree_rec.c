#include "bitree_rec.h"

#define OUTPUT_LENGTH		9
#define SPACING_LBRANCH		L"       └"
#define SPACING_RBRANCH		L"       │"
#define SPACING_NOBRANCH	L"        "

#define WCHAR_LBRANCH		L'┐'
#define WCHAR_RBRANCH		L'─'
#define WCHAR_FULLBRANCH	L'┬'

struct list_head
{
	struct list_node *head;
	struct list_node *tail;
};

struct list_node
{
	struct list_node *prev;
	struct list_node *next;
	struct binarytree_node *data;
	unsigned depth;
};

struct binarytree_node
{
	struct binarytree_node *left;
	struct binarytree_node *right;
	int key;
};

typedef struct list_head List;
typedef struct list_node ListNode;

static BiTrNode *search_predecessor(BiTrNode *left);
static BiTrNode *search_successor(BiTrNode *right);

static void put_node(int key, wchar_t wch);
static void put_space(List *src);
static void push(List *src, BiTrNode *data, unsigned depth);
static ListNode *pop(List *src);

BiTrNode *bitr_insert(BiTrNode *src, int new_key)
{
	if (src == NULL)
	{
		src = (BiTrNode *)calloc(1, sizeof(BiTrNode));
		src->key = new_key;
		src->left = NULL;
		src->right = NULL;
	}
	else
	{
		/* Go left. */
		if (new_key < src->key)
		{
			src->left = bitr_insert(src->left, new_key);
		}
		/* Go right. */
		else if (new_key > src->key)
		{
			src->right = bitr_insert(src->right, new_key);
		}
		else
		{
			/* Identical keys. */
		}
	}

	return src;
}

BiTrNode *bitr_delete(BiTrNode *src, int key_to_del)
{
	if (src == NULL)
	{
		/* No key. */
		return NULL;
	}

	/* Go left. */
	if (key_to_del < src->key)
	{
		src->left = bitr_delete(src->left, key_to_del);
	}
	/* Go right. */
	else if (key_to_del > src->key)
	{
		src->right = bitr_delete(src->right, key_to_del);
	}
	else
	{
		BiTrNode *del = src;
		/* No left child, attach right to src. */
		if (src->left == NULL)
		{
			src = src->right;
		}
		/* No right child, attach left to src. */
		else if (src->right == NULL)
		{
			src = src->left;
		}
		else
		{
			#ifdef USE_SUCCESSOR

			BiTrNode *successor = search_successor(src->right);
			successor->left = src->left;
			successor->right = src->right;
			src = successor;

			#elif

			BiTrNode *predec = search_predecessor(src->left);
			predec->left = src->left;
			predec->right = src->right;
			src = predec;

			#endif
		}

		free(del);
	}

	return src;
}

BiTrNode *bitr_search(BiTrNode *src, int key_to_find)
{
	if (src == NULL)
	{
		/* No key. */
		return NULL;
	}

	/* Go left. */
	if (key_to_find < src->key)
	{
		return bitr_search(src->left, key_to_find);
	}
	/* Go right. */
	else if (key_to_find > src->key)
	{
		return bitr_search(src->right, key_to_find);
	}
	else
	{
		/* Found one. */
		return src;
	}
}

static BiTrNode *search_predecessor(BiTrNode *left)
{
	BiTrNode *predec = left->right;

	while (predec->right)
	{
		left = left->right;
		predec = predec->right;
	}

	left->right = NULL;

	return predec;
}

static BiTrNode *search_successor(BiTrNode *right)
{
	BiTrNode *successor = right->left;

	while (successor->left)
	{
		right = right->left;
		successor = successor->left;
	}

	right->left = NULL;

	return successor;
}

void destroy_tree(BiTrNode *root)
{
	if (root)
	{
		destroy_tree(root->left);
		destroy_tree(root->right);
		free(root);
	}
}

void print_tree(BiTrNode *root)
{
	if (root == NULL)
	{
		return;
	}

	const wchar_t branch_wch[4] = {
		0, WCHAR_LBRANCH, WCHAR_RBRANCH, WCHAR_FULLBRANCH
	};
	List *stack = (List *)calloc(1, sizeof(List));
	stack->head = NULL;
	stack->tail = NULL;

	setlocale(LC_ALL, "");

	push(stack, root, 0);

	while (stack->head)
	{
		ListNode *temp = pop(stack);
		BiTrNode *data = temp->data;
		unsigned depth = temp->depth;

		while (data)
		{
			int c1 = data->left != NULL;
			int c2 = data->right != NULL;
			c2 <<= 1;
			depth++;

			if (c1)
			{
				push(stack, data->left, depth);
			}
			put_node(data->key, branch_wch[c1|c2]);

			data = data->right;
		}

		free(temp);

		put_space(stack);
	}
	putwchar(L'\n');

	free(stack);
}

/*
 * Prints out key with padding.
 * If wch is 0, it prints only a key.
 */
static void put_node(int key, wchar_t wch)
{
	if (wch == 0)
	{
		wprintf(L"%d", key);
		return;
	}

	wchar_t output[OUTPUT_LENGTH] = { 0 };
	wchar_t *p = output;
	wchar_t *e = output + OUTPUT_LENGTH-2;

	swprintf(output, OUTPUT_LENGTH-1, L"%-*d", OUTPUT_LENGTH-1, key);

	while (p < e)
	{
		if (*p == L' ')
		{
			*p = WCHAR_RBRANCH;
		}
		p++;
	}

	output[OUTPUT_LENGTH-2] = wch;
	wprintf(output);
}

/*
 * Put spaces before it prints out a line.
 * The size of spaces is judged with the depth
 * of a node. If a node is not the last node, the head node,
 * do wprintf(SPACING_RBRANCH),
 * otherwise do wprintf(SPACING_LBRANCH).
 */
static void put_space(List *src)
{
	if (src->head == NULL)
	{
		return;
	}

	ListNode *head = src->head;
	ListNode *temp = src->tail;
	unsigned depth = 0;
	unsigned prev_depth = 0;
	unsigned distance = 0;

	putwchar(L'\n');

	/* All nodes except the head. */
	while (temp != head)
	{
		depth = temp->depth;
		distance = depth - prev_depth;
		prev_depth = depth;

		while (distance > 1)
		{
			wprintf(SPACING_NOBRANCH);
			distance--;
		}
		wprintf(SPACING_RBRANCH);

		temp = temp->prev;
	}

	/* The head node to be printed. */
	depth = head->depth;
	distance = depth - prev_depth;

	while (distance > 1)
	{
		wprintf(SPACING_NOBRANCH);
		distance--;
	}
	wprintf(SPACING_LBRANCH);
}

static void push(List *src, BiTrNode *data, unsigned depth)
{
	ListNode *new_node = (ListNode *)calloc(1, sizeof(ListNode));
	new_node->data = data;
	new_node->depth = depth;
	new_node->prev = NULL;
	new_node->next = src->head;

	if (src->head)
	{
		src->head->prev = new_node;
	}
	else
	{
		src->tail = new_node;
	}

	src->head = new_node;
}

/*
 * Does not check if stack is empty.
 */
static ListNode *pop(List *src)
{
	ListNode *head = src->head;
	src->head = head->next;

	if (src->head)
	{
		src->head->prev = NULL;
	}
	else
	{
		src->tail = NULL;
	}

	return head;
}

