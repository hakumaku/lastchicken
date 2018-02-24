#include "avltree.h"

#define BALANCED	0
#define RIGHT_HEAVY	1
#define LEFT_HEAVY	2
#define DUMMY		3

#define INSERTION	0
#define DELETION	1

/*
 * bf not done
 * deletion incomplete
 */

struct avltree_node
{
	unsigned long parent;
	struct avltree_node *left;
	struct avltree_node *right;
	int key;
};

struct avltree
{
	struct avltree_node *root;
};

typedef struct avltree_node AVLNode;
typedef struct avltree AVLTree;

static inline void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

static inline int get_bf(AVLNode *src)
{
	return src->parent & 3;
}

static inline void set_parent(AVLNode *child, AVLNode *parent)
{
	child->parent = (unsigned long)parent;
}
static inline void change_child(AVLNode *old, AVLNode *new, AVLNode *parent)
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
		/*
		 * if root
		 */
	}
}

static inline AVLNode *avl_parent(AVLNode *src)
{
	return (AVLNode *)src->parent;
}

static inline void set_bf_left(AVLNode *src)
{
	src->parent |= LEFT_HEAVY;
}

static inline void set_bf_right(AVLNode *src)
{
	src->parent |= RIGHT_HEAVY;
}

static inline void set_bf_full(AVLNode *src)
{
	src->parent &= ~(unsigned long)3;
}

static inline AVLNode *avl_next(AVLNode *src)
{
	src = src->right;

	while (src->left)
	{
		src = src->left;
	}

	return src;
}

static inline AVLNode *avl_prev(AVLNode *src)
{
	src = src->left;

	while (src->right)
	{
		src = src->right;
	}

	return src;
}

static AVLNode *create(AVLNode *parent, int key);

static void insert(AVLNode **src, int new_key);
static void insert_balance(AVLNode *src);
static void insert_reset_bf();

static void delete(AVLNode **src, int key_to_del);
static void delete_balance(AVLNode *src);
static void delete_reset_bf();

static void ll_rotate(AVLNode *src);
static void lr_rotate(AVLNode *src);
static void rr_rotate(AVLNode *src);
static void rl_rotate(AVLNode *src);

static void free_node(AVLNode *src);

void avl_insert(AVLTree *src, int new_key)
{
	insert(&src->root, new_key);
}

void avl_delete(AVLTree *src, int key_to_del)
{
	delete(&src->root, key_to_del);
}

static AVLNode *create(AVLNode *parent, int key)
{
	AVLNode *new_node = (AVLNode *)calloc(1, sizeof(AVLNode));
	new_node->parent = (unsigned long)parent;
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->key = key;

	return new_node;
}

static void insert(AVLNode **src, int new_key)
{
	AVLNode *parent = NULL;
	AVLNode **new = src;

	while (*new)
	{
		parent = *new;

		if (parent->key < new_key)
		{
			new = &parent->left;
		}
		else if (parent->key > new_key)
		{
			new = &parent->right;
		}
		else
		{
			return;
		}
	}

	*new = create(parent, new_key);

	/* full */
	if (parent->left != NULL && parent->right != NULL)
	{
		set_bf_full(parent);
	}
	/* left only */
	else if (parent->left == *new)
	{
		set_bf_left(parent);
	}
	/* right only */
	else
	{
		set_bf_right(parent);
	}

	insert_balance(parent);
}

static void insert_balance(AVLNode *parent)
{
	bool imbalanced = true;

	while (imbalanced)
	{
		AVLNode *gparent = avl_parent(parent);
		int bf = get_bf(gparent);

		/* left */
		if (gparent->left == parent)
		{
			if (bf == BALANCED)
			{
				set_bf_left(gparent);
			}
			else if (bf == RIGHT_HEAVY)
			{
				set_bf_full(gparent);
				imbalanced = false;
			}
			else
			{
				int bf = get_bf(parent);

				if (bf == LEFT_HEAVY)
				{
					ll_rotate(gparent);
					set_bf_full(gparent);
					set_bf_full(gparent->left);
				}
				else
				{
					lr_rotate(gparent);
					AVLNode *node = gparent->left->right;
					if (node != NULL)
					{
						set_bf_full(gparent->left);
						set_bf_right(gparent->right);
					}
					else
					{
						set_bf_left(gparent->left);
						set_bf_full(gparent->right);
					}
				}

				imbalanced = false;
			}
		}
		/* right */
		else
		{
			if (bf == BALANCED)
			{
				set_bf_right(gparent);
			}
			else if (bf == RIGHT_HEAVY)
			{
				int bf = get_bf(parent);

				if (bf == LEFT_HEAVY)
				{
					rl_rotate(gparent);
					AVLNode *node = gparent->left->right;
					if (node != NULL)
					{
						set_bf_full(gparent->left);
						set_bf_right(gparent->right);
					}
					else
					{
						set_bf_left(gparent->left);
						set_bf_full(gparent->right);
					}
				}
				else
				{
					rr_rotate(gparent);
					set_bf_full(gparent);
					set_bf_full(gparent->right);
				}
				imbalanced = false;
			}
			else
			{
				set_bf_full(gparent);
				imbalanced = false;
			}
		}

		parent = avl_parent(parent);
	}
}

static void delete(AVLNode **src, int key_to_del)
{
	AVLNode **node = src;
	AVLNode *del = NULL;

	while (*node)
	{
		int key = (*node)->key;

		if (key < key_to_del)
		{
			(*node) = (*node)->left;
		}
		else if (key > key_to_del)
		{
			(*node) = (*node)->right;
		}
		else
		{
			break;
		}
	}

	if (*node == NULL)
	{
		return;
	}
	else
	{
		AVLNode *left = (*node)->left;
		AVLNode *right = (*node)->right;

		if (left != NULL && right != NULL)
		{
			AVLNode *next = avl_next(*src);
			AVLNode *parent = avl_parent(next);

			if (parent->left == next)
			{
				parent->left = NULL;
			}
			else
			{
				parent->right = NULL;
			}
			swap(&next->key, &(*src)->key);
			free(next);

			del = avl_parent(parent);
		}
		else
		{
			AVLNode *next = left != NULL ? left : right;
			free(*src);
			*src = next;

			del = avl_parent(next);
		}
	}

	delete_balance(del);
}

static void delete_balance(AVLNode *parent)
{
	bool imbalanced = true;

	while (imbalanced)
	{
		AVLNode *gparent = avl_parent(parent);
		int bf = get_bf(gparent);

		/* left */
		if (gparent->left == parent)
		{
			if (bf == BALANCED)
			{
				set_bf_left(gparent);
			}
			else if (bf == RIGHT_HEAVY)
			{
				set_bf_full(gparent);
				imbalanced = false;
			}
			else
			{
				int bf = get_bf(parent);

				if (bf == LEFT_HEAVY)
				{
					ll_rotate(gparent);
					set_bf_full(gparent);
					set_bf_full(gparent->left);
				}
				else
				{
					lr_rotate(gparent);
					AVLNode *node = gparent->left->right;
					if (node != NULL)
					{
						set_bf_full(gparent->left);
						set_bf_right(gparent->right);
					}
					else
					{
						set_bf_left(gparent->left);
						set_bf_full(gparent->right);
					}
				}

				imbalanced = false;
			}
		}
		/* right */
		else
		{
			if (bf == BALANCED)
			{
				set_bf_right(gparent);
			}
			else if (bf == RIGHT_HEAVY)
			{
				int bf = get_bf(parent);

				if (bf == LEFT_HEAVY)
				{
					rl_rotate(gparent);
					AVLNode *node = gparent->left->right;
					if (node != NULL)
					{
						set_bf_full(gparent->left);
						set_bf_right(gparent->right);
					}
					else
					{
						set_bf_left(gparent->left);
						set_bf_full(gparent->right);
					}
				}
				else
				{
					rr_rotate(gparent);
					set_bf_full(gparent);
					set_bf_full(gparent->right);
				}
				imbalanced = false;
			}
			else
			{
				set_bf_full(gparent);
				imbalanced = false;
			}
		}

		parent = avl_parent(parent);
	}
}

static void ll_rotate(AVLNode *src)
{
	AVLNode *root = avl_parent(src);
	AVLNode *x = src;
	AVLNode *y = x->left;

	x->left = y->right;
	y->right = x;

	set_parent(x, y);
	set_parent(x->left, x);
	set_parent(y, root);
	change_child(x, y, root);
}

static void lr_rotate(AVLNode *src)
{
	AVLNode *root = avl_parent(src);
	AVLNode *x = src;
	AVLNode *y = x->left;
	AVLNode *z = y->right;

	x->left = z->right;
	y->right = z->left;
	z->right = x;
	z->left = y;

	set_parent(x, z);
	set_parent(y, z);
	change_child(x, z, root);
}

static void rr_rotate(AVLNode *src)
{
	AVLNode *root = avl_parent(src);
	AVLNode *x = src;
	AVLNode *y = x->right;

	x->right = y->left;
	y->left = x;

	set_parent(x, y);
	set_parent(x->right, x);
	set_parent(y, root);
	change_child(x, y, root);
}

static void rl_rotate(AVLNode *src)
{
	AVLNode *root = avl_parent(src);
	AVLNode *x = src;
	AVLNode *y = x->right;
	AVLNode *z = y->left;

	x->right = z->left;
	y->left = z->right;
	z->left = x;
	z->right = y;

	if (x->right != NULL)
	{
		set_bf_full(x);
		set_bf_right(y);
	}
	else
	{
		set_bf_left(x);
		set_bf_full(y);
	}
	set_bf_full(z);

	set_parent(x, z);
	set_parent(y, z);
	change_child(x, z, root);
}

void destroy_tree(AVLTree *src)
{
	free_node(src->root);
}

static void free_node(AVLNode *node)
{
	if (node)
	{
		free_node(node->left);
		free_node(node->right);
		free(node);
	}
}

