#include "bintree.h"

#define OUTPUT_LENGTH		9
#define SPACING_LBRANCH		L"       └"
#define SPACING_RBRANCH		L"       │"
#define SPACING_NOBRANCH	L"        "

#define WCHAR_LBRANCH		L'┐'
#define WCHAR_RBRANCH		L'─'
#define WCHAR_FULLBRANCH	L'┬'

struct binary_tree
{
	struct binary_node *root;
};

struct binary_node
{
	struct binary_node *left;
	struct binary_node *right;
	struct binary_node *parent;
	int key;
};

struct print_list
{
	struct print_node *head;
	struct print_node *tail;
};

struct print_node
{
	struct print_node *prev;
	struct print_node *next;
	struct binary_node *data;
	unsigned depth;
};

typedef struct binary_node BinNode;
typedef struct print_node PrintNode;
typedef struct print_list PrintList;

static void put_node(BinNode *data, int c);
static void put_space(PrintList *src);
static void push(PrintList *list, BinNode *data, unsigned depth);
static PrintNode *pop(PrintList *list);

static inline void swap(int *a, int *b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

static inline void set_parent(BinNode *parent, BinNode *node)
{
	node->parent = parent;
}

static inline void change_child(BinNode *old, BinNode *new, BinNode *parent, BinNode **root)
{
	if (parent)
	{
		if (parent->left == old)
		{
			parent->left = new;
		}
		else
		{
			parent->right = new;
		}
	}
	else
	{
		*root = new;
	}
}

static inline BinNode *bin_parent(BinNode *node)
{
	return node->parent;
}

static void insert(BinNode **src, int k);
static void delete(BinNode **src, int k);
static BinNode *create(int k);
static void free_node(BinNode *src);
static BinNode *bin_next(BinNode *src);
static BinNode *bin_prev(BinNode *src);

BinTree *init_bintree(void)
{
	BinTree *new_tree = (BinTree *)calloc(1, sizeof(BinTree));
	new_tree->root = NULL;

	return new_tree;
}

static BinNode *create(int k)
{
	BinNode *new = (BinNode *)calloc(1, sizeof(BinNode));
	new->left = NULL;
	new->right = NULL;
	new->key = k;

	return new;
}

void bin_insert(BinTree *src, int k)
{
	insert(&src->root, k);
}

static void insert(BinNode **src, int k)
{
	BinNode **node = src;
	BinNode *tmp = NULL;

	while (*node)
	{
		tmp = *node;

		if (tmp->key > k)
		{
			node = &tmp->left;
		}
		else if (tmp->key < k)
		{
			node = &tmp->right;
		}
		else
		{
			return;
		}
	}

	*node = create(k);
	set_parent(tmp, *node);
}

void bin_delete(BinTree *src, int k)
{
	delete(&src->root, k);
}

static void delete(BinNode **src, int k)
{
	BinNode **node = src;
	BinNode *tmp = NULL;

	while (*node)
	{
		tmp = *node;

		if (tmp->key > k)
		{
			node = &tmp->left;
		}
		else if (tmp->key < k)
		{
			node = &tmp->right;
		}
		else
		{
			/* full node */
			if (tmp->left && tmp->right)
			{
				BinNode *next = bin_next(tmp);
				BinNode *next_parent = bin_parent(next);

				swap(&next->key, &tmp->key);

				/* next->right can be NULL. */
				change_child(next, next->right, next_parent, src);
				if (next->right)
				{
					set_parent(next_parent, next->right);
				}

				free(next);
			}
			else /* only left, only right or none */
			{
				BinNode *next = tmp->left ? tmp->left : tmp->right;
				BinNode *gparent = bin_parent(tmp);

				/* next can be NULL. */
				change_child(tmp, next, gparent, src);
				if (next)
				{
					set_parent(gparent, next);
				}

				free(tmp);
			}
			return;
		}
	}
}

void bin_destroy(BinTree *src)
{
	BinNode **node = &src->root;
	BinNode *tmp = NULL;

	while (*node)
	{
		tmp = *node;

		if (tmp->left)
		{
			node = &tmp->left;
		}
		else if (tmp->right)
		{
			node = &tmp->right;
		}
		else
		{
			tmp = tmp->parent;
			free(*node);
			*node = NULL;
		}
	}
}

static BinNode *bin_next(BinNode *src)
{
	BinNode *tmp = src->right;

	while (tmp->left)
	{
		tmp = tmp->left;
	}

	return tmp;
}

static BinNode *bin_prev(BinNode *src)
{
	BinNode *tmp = src;

	while (tmp->right)
	{
		tmp = tmp->right;
	}

	return tmp;
}

/*
 * Printing a tree on terminal.
 *	print_tree()
 *		put_node()
 *		put_space()
 *		push()
 *		pop()
 */
void bin_print(BinTree *src)
{
	if (src->root == NULL)
	{
		return;
	}

	setlocale(LC_ALL, "");

	PrintList buf = { 0 };
	push(&buf, src->root, 0);

	while (buf.head)
	{
		PrintNode *node = pop(&buf);
		BinNode *data = node->data;
		unsigned depth = node->depth;

		while (data)
		{
			int c1 = data->left != NULL;
			int c2 = data->right != NULL;
			c2 <<= 1;
			depth++;

			if (c1)
			{
				push(&buf, data->left, depth);
			}
			put_node(data, c1|c2);

			data = data->right;
		}
		put_space(&buf);
	}
	putwchar(L'\n');
}

/*
 * Prints out data with padding.
 * If wch is 0, it prints only a key.
 */
static void put_node(BinNode *data, int c)
{
	const wchar_t branch_wch[4] = {
		0, WCHAR_LBRANCH, WCHAR_RBRANCH, WCHAR_FULLBRANCH
	};
	int key = data->key;

	if (c == 0)
	{
		wprintf(L"%d", key);
		return;
	}

	wchar_t output[OUTPUT_LENGTH] = { 0 };
	wchar_t *s = output;
	wchar_t *e = output + OUTPUT_LENGTH-2;

	swprintf(output, OUTPUT_LENGTH-1, L"%-*d", OUTPUT_LENGTH-1, key);

	while (s < e)
	{
		if (*s == L' ')
		{
			*s = WCHAR_RBRANCH;
		}
		s++;
	}

	output[OUTPUT_LENGTH-2] = branch_wch[c];
	wprintf(output);
}

/*
 * Put spaces before it prints out a line.
 * The size of spaces is judged with the depth
 * of the node. If the node is not the last node, the head node,
 * do wprintf(SPACING_RBRANCH), otherwise do wprintf(SPACING_LBRANCH).
 */
static void put_space(PrintList *src)
{
	if (src->head == NULL)
	{
		return;
	}

	PrintNode *head = src->head;
	PrintNode *node = src->tail;
	unsigned depth = 0;
	unsigned prev_depth = 0;
	unsigned distance = 0;

	putwchar(L'\n');

	while (node)
	{
		wchar_t *s = node != head ? SPACING_RBRANCH : SPACING_LBRANCH;
		depth = node->depth;
		distance = depth - prev_depth;
		prev_depth = depth;

		while (distance > 1)
		{
			wprintf(SPACING_NOBRANCH);
			distance--;
		}
		wprintf(s);

		node = node->prev;
	}
}

static void push(PrintList *list, BinNode *data, unsigned depth)
{
	PrintNode *new = (PrintNode *)calloc(1, sizeof(PrintNode));
	new->next = list->head;
	new->prev = NULL;
	new->data = data;
	new->depth = depth;

	if (list->head)
	{
		list->head->prev = new;
	}
	else
	{
		list->tail = new;
	}

	list->head = new;
}

static PrintNode *pop(PrintList *list)
{
	PrintNode *head = list->head;
	list->head = head->next;

	if (list->head)
	{
		list->head->prev = NULL;
	}
	else
	{
		list->tail = NULL;
	}

	return head;
}

