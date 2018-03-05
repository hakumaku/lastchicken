#include "avltree.h"

#define OUTPUT_LENGTH		9
#define SPACING_LBRANCH		L"       └"
#define SPACING_RBRANCH		L"       │"
#define SPACING_NOBRANCH	L"        "

#define WCHAR_LBRANCH		L'┐'
#define WCHAR_RBRANCH		L'─'
#define WCHAR_FULLBRANCH	L'┬'

#define BALANCE		0
#define RIGHT_HEAVY	1
#define LEFT_HEAVY	2

struct avl_tree
{
	struct avl_node *root;
};

struct avl_node
{
	struct avl_node *left;
	struct avl_node *right;
	unsigned long parent;
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
	struct avl_node *data;
	unsigned depth;
};

typedef struct avl_node AvlNode;
typedef struct print_list PrintList;
typedef struct print_node PrintNode;

static inline void swap(int *a, int *b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

static inline AvlNode *avl_parent(AvlNode *src)
{
	return (AvlNode *)(src->parent & ~3);
}

static inline int avl_bf(AvlNode *src)
{
	return src->parent & 3;
}

static inline void set_parent(AvlNode *parent, AvlNode *child)
{
	child->parent = (unsigned long)parent;
}

static inline void set_bf(AvlNode *src, int bf)
{
	src->parent &= ~3;
	src->parent |= bf;
}

static inline void change_child(AvlNode *old, AvlNode *new, AvlNode *parent, AvlNode **root)
{
	if (parent)
	{
		if (parent->left == old)
		{
			parent->left = new;
		}
		else /* parent->right == old */
		{
			parent->right = new;
		}
	}
	else
	{
		*root = new;
	}
}

static AvlNode *avl_next(AvlNode *src)
{
	AvlNode *tmp = src->right;

	while (tmp->left)
	{
		tmp = tmp->left;
	}

	return tmp;
}

static AvlNode *avl_prev(AvlNode *src)
{
	AvlNode *tmp = src->left;

	while (tmp->right)
	{
		tmp = tmp->right;
	}

	return tmp;
}


static AvlNode *create(int k);

static void insert(AvlNode **root, int k);
static void insert_bf(AvlNode *src, AvlNode **root);

static void delete(AvlNode **root, int k);
static void delete_bf(AvlNode *src, AvlNode **root);

static void rotate_left(AvlNode *src, AvlNode **root);
static void rotate_right(AvlNode *src, AvlNode **root);

/* working */
static void ll_rotate(AvlNode *src, AvlNode **root);
static void lr_rotate(AvlNode *src, AvlNode **root);
static void rr_rotate(AvlNode *src, AvlNode **root);
static void rl_rotate(AvlNode *src, AvlNode **root);

static void put_node(AvlNode *data, int c);
static void put_space(PrintList *src);
static void push(PrintList *list, AvlNode *data, unsigned depth);
static PrintNode *pop(PrintList *list);

AvlTree *init_avltree(void)
{
	AvlTree *new_tree = (AvlTree *)calloc(1, sizeof(AvlTree));
	new_tree->root = NULL;

	return new_tree;
}

static AvlNode *create(int k)
{
	AvlNode *new = (AvlNode *)calloc(1, sizeof(AvlNode));
	new->left = NULL;
	new->right = NULL;
	new->parent = 0;
	new->key = k;

	return new;
}

void avl_insert(AvlTree *src, int k)
{
	insert(&src->root, k);
}

static void insert(AvlNode **root, int k)
{
	AvlNode **node = root;
	AvlNode *tmp = NULL;

	while (*node)
	{
		tmp = *node;

		if (k < tmp->key)
		{
			node = &tmp->left;
		}
		else if (k > tmp->key)
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
	insert_bf(tmp, root);
}

static void insert_bf(AvlNode *src, AvlNode **root)
{
	if (src == NULL)
	{
		return;
	}

	AvlNode *node = src;

	if (node->left && node->right)
	{
		set_bf(node, BALANCE);
	}
	else if (node->left)
	{
		set_bf(node, LEFT_HEAVY);
	}
	else
	{
		set_bf(node, RIGHT_HEAVY);
	}

	while (true)
	{
		AvlNode *gparent = avl_parent(node);

		if (gparent == NULL)
		{
			return;
		}

		int bf = avl_bf(gparent);
		bool left_child = gparent->left == node;

		/*
		 * 6 cases:
		 *	1) balance && left
		 *	2) balance && right
		 *	3) left_heavy && left
		 *	4) left_heavy && right
		 *	5) right_heavy && left
		 *	6) right_heavy && right
		 */
		if (bf == BALANCE)
		{
			if (left_child)
			{
				set_bf(gparent, LEFT_HEAVY);
			}
			else /* right_child */
			{
				set_bf(gparent, RIGHT_HEAVY);
			}
		}
		else if (bf == LEFT_HEAVY)
		{
			if (left_child)
			{
				int parent_bf = avl_bf(node);
				if (parent_bf == LEFT_HEAVY)
				{
					ll_rotate(gparent, root);

					/* 'y' node */
					set_bf(gparent, BALANCE);
					/* 'x' node */
					set_bf(gparent->right, BALANCE);
				}
				else
				{
					lr_rotate(gparent, root);

					/* 'z' node */
					set_bf(gparent, BALANCE);

					/* If 'x' node is full */
					if (gparent->right->left)
					{
						/* 'x' node */
						set_bf(gparent->right, BALANCE);
						/* 'y' node */
						set_bf(gparent->left, LEFT_HEAVY);
					}
					else /* 'y' node must be full */
					{
						set_bf(gparent->right, RIGHT_HEAVY);
						set_bf(gparent->left, BALANCE);
					}
				}
			}
			else /* right_child */
			{
				set_bf(gparent, BALANCE);
			}
			return;
		}
		else /* bf == RIGHT_HEAVY */
		{
			if (left_child)
			{
				set_bf(gparent, BALANCE);
			}
			else /* right_child */
			{
				int parent_bf = avl_bf(node);
				if (parent_bf == RIGHT_HEAVY)
				{
					rr_rotate(gparent, root);

					/* 'y' node */
					set_bf(gparent, BALANCE);
					/* 'x' node */
					set_bf(gparent->left, BALANCE);
				}
				else
				{
					rl_rotate(gparent, root);

					/* 'z' node */
					set_bf(gparent, BALANCE);

					/* If 'x' node is full */
					if (gparent->left->right)
					{
						/* 'x' node */
						set_bf(gparent->left, BALANCE);
						/* 'y' node */
						set_bf(gparent->right, RIGHT_HEAVY);
					}
					else /* 'y' must be full */
					{
						set_bf(gparent->left, LEFT_HEAVY);
						set_bf(gparent->right, BALANCE);
					}
				}
			}
			return;
		}

		node = avl_parent(node);
	}
}

void avl_delete(AvlTree *src, int k)
{
	delete(&src->root, k);
}

static void delete(AvlNode **root, int k)
{
	AvlNode **node = root;
	AvlNode *tmp = NULL;

	while (*node)
	{
		tmp = *node;

		if (k < tmp->key)
		{
			node = &tmp->left;
		}
		else if (k > tmp->key)
		{
			node = &tmp->right;
		}
		else
		{
			/* full child */
			if (tmp->left && tmp->right)
			{
				AvlNode *next = avl_next(tmp);
				AvlNode *next_parent = avl_parent(next);

				swap(&next->key, &tmp->key);

				change_child(next, next->right, next_parent, root);
				if (next->right)
				{
					set_parent(next_parent, next->right);
				}

				free(next);

				tmp = next_parent;
			}
			else /* left only, right only or none */
			{
				AvlNode *next = tmp->left ? tmp->left : tmp->right;
				AvlNode *gparent = avl_parent(tmp);

				change_child(tmp, next, gparent, root);
				if (next)
				{
					set_parent(gparent, next);
				}

				free(tmp);

				tmp = gparent;
			}
			break;
		}
	}

	// delete_bf(tmp, root);
}

/*
 * Unlike the condition of rotating in insertion
 * in which you can unambiguously select between LL and LR,
 * when it comes to deleting, there is a case
 * in which you can apply either LL or LR, maintaining
 * its balance.
 *
 * e.g)
 *     x
 *    / \
 *   y   z
 *  / \
 * a   b
 * 'z' is the node to be deleted.
 * There are three cases: a only, b only, and both a and b.
 *
 * LL applied:
 *     x       y
 *    /       / \
 *   y   ==> a   x
 *  / \         /
 * a   b       b
 *
 * LR applied:
 *     x         b
 *    /         / \
 *   y   ==>   y   x
 *  / \       /
 * a   b     a
 *
 * If you are to implement with LL-first,
 * you should check the balance factor of x after it is rotated,
 * which can be either 0 or +1,
 * if LR-first, that of y needs to be examined.
 */
static void delete_bf(AvlNode *src, AvlNode **root)
{
	if (src == NULL)
	{
		return;
	}

	AvlNode *node = src;

	if (node->left == NULL && node->right == NULL)
	{
		set_bf(node, BALANCE);
	}
	else if (node->left)
	{
		set_bf(node, LEFT_HEAVY);
	}
	else
	{
		set_bf(node, RIGHT_HEAVY);
	}

	while (true)
	{
		AvlNode *gparent = avl_parent(node);

		if (gparent == NULL)
		{
			return;
		}

		int bf = avl_bf(gparent);
		bool left_child = gparent->left == node;

		if (bf == BALANCE)
		{
			if (left_child)
			{
				set_bf(gparent, RIGHT_HEAVY);
			}
			else
			{
				set_bf(gparent, LEFT_HEAVY);
			}
			return;
		}
		else if (bf == LEFT_HEAVY)
		{
			/*
			 * Note that in the insertion process,
			 * the node is balanced because it is "full",
			 * while it is because it is a "leaf".
			 * Thus, a certain node up to the root might be unbalanced.
			 */
			if (left_child)
			{
				set_bf(gparent, BALANCE);
			}
			else
			{
				int parent_bf = avl_bf(node);
				if (parent_bf == LEFT_HEAVY)
				{
					ll_rotate(gparent, root);

					set_bf(gparent->right, BALANCE);
				}
				else if (parent_bf == BALANCE)
				{
					set_bf(gparent->right, LEFT_HEAVY);
				}
				else
				{
					lr_rotate(gparent, root);

					set_bf(gparent->right, LEFT_HEAVY);
				}

				set_bf(gparent->left, BALANCE);
				set_bf(gparent, BALANCE);

				return;
			}
		}
		else /* bf == RIGHT_HEAVY */
		{
			if (left_child)
			{
				rotate_right(gparent, root);

				return;
			}
			else
			{
				set_bf(gparent, BALANCE);
			}
		}
	}
}

static void rotate_left(AvlNode *src, AvlNode **root)
{
	int bf = avl_bf(src);

	/* LL rotate */
	if (bf == LEFT_HEAVY)
	{
		AvlNode *x = src;
		AvlNode *y = x->left;
		AvlNode *t = y->right;
		AvlNode *parent = avl_parent(src);

		x->left = t;
		if (t)
		{
			set_parent(x, t);
		}

		y->right = x;
		set_parent(y, x);

		set_bf(x, BALANCE);
		set_bf(y, BALANCE);

		set_parent(parent, y);
		if (parent == NULL)
		{
			*root = y;
		}
		else if (parent->left == src)
		{
			parent->left = y;
		}
		else
		{
			parent->right = y;
		}
	}
	else /* LR rotate */
	{
		AvlNode *x = src;
		AvlNode *y = x->left;
		AvlNode *z = y->right;
		AvlNode *t1 = z->left;
		AvlNode *t2 = z->right;
		AvlNode *parent = avl_parent(src);

		x->left = t2;
		z->right = x;
		set_parent(z, x);

		y->right = t1;
		z->left = y;
		set_parent(z, y);

		if (t1)
		{
			set_parent(y, t1);
			set_bf(x, RIGHT_HEAVY);
			set_bf(y, BALANCE);
		}
		else
		{
			set_parent(x, t2);
			set_bf(x, BALANCE);
			set_bf(y, LEFT_HEAVY);
		}

		set_bf(z, BALANCE);
		set_parent(parent, z);
		if (parent == NULL)
		{
			*root = z;
		}
		else if (parent->left == src)
		{
			parent->left = z;
		}
		else
		{
			parent->right = z;
		}
	}
}

static void rotate_right(AvlNode *src, AvlNode **root)
{
	int bf = avl_bf(src);

	/* RR rotate */
	if (bf == RIGHT_HEAVY)
	{
		AvlNode *x = src;
		AvlNode *y = x->right;
		AvlNode *t = y->left;
		AvlNode *parent = avl_parent(src);

		x->right = t;
		if (t)
		{
			set_parent(x, t);
		}

		y->left = x;
		set_parent(y, x);

		set_bf(x, BALANCE);
		set_bf(y, BALANCE);

		set_parent(parent, y);
		if (parent == NULL)
		{
			*root = y;
		}
		else if (parent->left == src)
		{
			parent->left = y;
		}
		else
		{
			parent->right = y;
		}
	}
	else /* RL rotate */
	{
		AvlNode *x = src;
		AvlNode *y = x->right;
		AvlNode *z = y->left;
		AvlNode *t1 = z->left;
		AvlNode *t2 = z->right;
		AvlNode *parent = avl_parent(src);

		x->right = t1;
		z->left = x;
		set_parent(z, x);

		y->left = t2;
		z->right = y;
		set_parent(z, y);

		if (t1)
		{
			set_parent(x, t1);
			set_bf(x, BALANCE);
			set_bf(y, RIGHT_HEAVY);
		}
		else
		{
			set_parent(y, t2);
			set_bf(x, LEFT_HEAVY);
			set_bf(y, BALANCE);
		}

		set_bf(z, BALANCE);
		set_parent(parent, z);
		if (parent == NULL)
		{
			*root = z;
		}
		else if (parent->left == src)
		{
			parent->left = z;
		}
		else
		{
			parent->right = z;
		}
	}
}

/*
 * LL rotation:
 *	x.bf = 0
 *	y.bf = 0
 *       x            y
 *      / \         /   \
 *     y   4       z     x
 *    / \    ==>  / \   / \
 *   z   3       1   2 3   4
 *  / \
 * 1   2
 * There is only one new node, either 1 or 2.
 * Following nodes have changed
 * their parents: x, y and 3.
 */
static void ll_rotate(AvlNode *src, AvlNode **root)
{
	AvlNode *x = src;
	AvlNode *y = x->left;
	AvlNode *t = y->right;
	AvlNode *parent = avl_parent(x);

	x->left = t;
	if (t)
	{
		set_parent(x, t);
	}

	y->right = x;
	set_parent(y, x);

	change_child(x, y, parent, root);
	set_parent(parent, y);

	set_bf(x, BALANCE);
	set_bf(y, BALANCE);
}

/*
 * LR rotation:
 *	x.bf = (new == 2) ? -1 : 0
 *	y.bf = (new == 2) ? 0 : 1
 *	z.bf = 0
 *      x             z
 *     / \          /   \
 *    y   4        y     x
 *   / \     ==>  / \   / \
 *  1   z        1   2 3   4
 *     / \
 *    2   3
 * There is only one new node, either 2 or 3.
 * Following nodes have changed
 * their parents: x, y, z and 2 or 3.
 */
static void lr_rotate(AvlNode *src, AvlNode **root)
{
	AvlNode *x = src;
	AvlNode *y = x->left;
	AvlNode *z = y->right;
	AvlNode *t1 = z->left;
	AvlNode *t2 = z->right;
	AvlNode *parent = avl_parent(x);

	x->left = t2;
	z->right = x;
	set_parent(z, x);

	y->right = t1;
	z->left = y;
	set_parent(z, y);

	if (t1)
	{
		set_parent(y, t1);
		set_bf(x, RIGHT_HEAVY);
		set_bf(y, BALANCE);
	}
	else
	{
		set_parent(x, t2);
		set_bf(x, BALANCE);
		set_bf(y, LEFT_HEAVY);
	}

	change_child(x, z, parent, root);
	set_parent(parent, z);

	set_bf(z, BALANCE);
}

/*
 * RR rotation:
 *	x.bf = 0
 *	y.bf = 0
 *   x                 y
 *  / \              /   \
 * 1   y            x     z
 *    / \    ==>   / \   / \
 *   2   z        1   2 3   4
 *      / \
 *     3   4
 * There is only one new node, either 3 or 4.
 * Following nodes have changed
 * their parents: x, y and 2.
 */
static void rr_rotate(AvlNode *src, AvlNode **root)
{
	AvlNode *x = src;
	AvlNode *y = x->right;
	AvlNode *t = y->left;
	AvlNode *parent = avl_parent(x);

	x->right = t;
	if (t)
	{
		set_parent(x, t);
	}

	y->left = x;
	set_parent(y, x);

	change_child(x, y, parent, root);
	set_parent(parent, y);

	set_bf(x, BALANCE);
	set_bf(y, BALANCE);
}

/* RL rotation:
 *	x.bf = (new == 2) ? 0 : -1
 *	y.bf = (new == 2) ? 1 : 0
 *	z.bf = 0
 *   x                 z
 *  / \              /   \
 * 1   y            x     y
 *    / \    ==>   / \   / \
 *   z   4        1   2 3   4
 *  / \
 * 2   3
 * There is only one new node, either 2 or 3.
 * Following nodes have changed
 * their parents: x, y, z and 2 or 3.
 */
static void rl_rotate(AvlNode *src, AvlNode **root)
{
	AvlNode *x = src;
	AvlNode *y = x->right;
	AvlNode *z = y->left;
	AvlNode *t1 = z->left;
	AvlNode *t2 = z->right;
	AvlNode *parent = avl_parent(x);

	x->right = t1;
	z->left = x;
	set_parent(z, x);

	y->left = t2;
	z->right = y;
	set_parent(z, y);

	if (t1)
	{
		set_parent(x, t1);
		set_bf(x, BALANCE);
		set_bf(y, RIGHT_HEAVY);
	}
	else
	{
		set_parent(y, t2);
		set_bf(x, LEFT_HEAVY);
		set_bf(y, BALANCE);
	}

	change_child(x, z, parent, root);
	set_parent(parent, z);
}

void avl_destroy(AvlTree *src)
{
	AvlNode **node = &src->root;
	AvlNode *tmp = NULL;

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
			tmp = avl_parent(tmp);
			free(*node);
			*node = NULL;
		}
	}
}

void avl_print(AvlTree *src)
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
		AvlNode *data = node->data;
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

static void put_node(AvlNode *data, int c)
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

static void put_space(PrintList *src)
{
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

static void push(PrintList *list, AvlNode *data, unsigned depth)
{
	PrintNode *new = (PrintNode *)calloc(1, sizeof(PrintNode));
	new->prev = NULL;
	new->next = list->head;
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

