#include "bitree.h"

struct binary_tree
{
	struct binary_node *root;
};

struct binary_node
{
	struct binary_node *left;
	struct binary_node *right;
	int key;
};

static inline void swap(int *a, int *b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

static BinNode *create(int k);
static void free_node(BinNode *src);
static BinNode *bin_next(BinNode *src);
static BinNode *bin_prev(BinNode *src);

void insert(BinNode **src, int k)
{
	BinNode **new = src;

	while (*new)
	{
		BinNode *node = *new;

		if (node->key > k)
		{
			new = &node->left;
		}
		else if (node->key < k)
		{
			new = &node->right;
		}
		else
		{
			return;
		}
	}

	*new = create(k);
}

void delete(BinNode **src, int k)
{
	BinNode **parent = src;

	while (*parent)
	{
		BinNode *node = *parent;

		if (node->key > k)
		{
			parent = &node->left;
		}
		else if (node->key < k)
		{
			parent = &node->right;
		}
		else
		{
			/* full node */
			if (node->left && node->right)
			{
				/* Need parent, cannot do next = next->right */
				BinNode *next = bin_next(node);
				swap(&next->key, &node->key);

				if (next->right)
				{
				}
			}
			/* left only */
			else if (node->left)
			{
				*parent = node->left;
				free(node);
			}
			/* right only */
			else
			{
				*parent = node->right;
				free(node);
			}
		}
	}

}

static BinNode *create(int k)
{
	BinNode *new = (BinNode *)calloc(1, sizeof(BinNode));
	new->left = NULL;
	new->right = NULL;
	new->key = k;

	return new;
}

static BinNode *bin_next(BinNode *src)
{
	BinNode *next = src;

	if (next->right)
	{
		next = next->right;

		while (next->left)
		{
			next = next->left;
		}
	}

	return next;
}

static BinNode *bin_prev(BinNode *src)
{
	BinNode *prev = src;

	if (prev->left)
	{
		prev = prev->left;

		while (prev->right)
		{
			prev = prev->right;
		}
	}

	return prev;
}

