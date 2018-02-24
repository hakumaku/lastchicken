#include "avltree_rec.h"

#define OUTPUT_LENGTH		9
#define SPACING_LBRANCH		L"       └"
#define SPACING_RBRANCH		L"       │"
#define SPACING_NOBRANCH	L"        "

#define WCHAR_LBRANCH		L'┐'
#define WCHAR_RBRANCH		L'─'
#define WCHAR_FULLBRANCH	L'┬'

#define RIGHT_HEAVY	-1
#define BALANCED	0
#define LEFT_HEAVY	1
#define IMBALANCED	2
#define FOUND		3

#define INSERTION	0
#define DELETION	1

struct list_head
{
	struct list_node *head;
	struct list_node *tail;
};

struct list_node
{
	struct list_node *prev;
	struct list_node *next;
	AVLNode *data;
	unsigned depth;
};

struct avltree_node
{
	struct avltree_node *left;
	struct avltree_node *right;
	int key;
	char bf;
};

typedef struct list_head List;
typedef struct list_node ListNode;

static void insert(AVLNode **src, int new_key, int *flag);
static void delete(AVLNode **src, int key_to_del, int *flag);

static void left_rotate(AVLNode **src, int flag);
static void right_rotate(AVLNode **src, int flag);

static int search_predecessor(AVLNode *left);
static int search_successor(AVLNode *right);

static void put_node(int key, wchar_t wch);
static void put_space(List *src);
static void push(List *stack, AVLNode *data, unsigned depth);
static ListNode *pop(List *stack);

void avl_insert(AVLNode **src, int new_key)
{
	int flag = IMBALANCED;
	insert(src, new_key, &flag);
}

void avl_delete(AVLNode **src, int key_to_del)
{
	int flag = IMBALANCED;
	delete(src, key_to_del, &flag);
}

static void insert(AVLNode **src, int new_key, int *flag)
{
	AVLNode *temp = *src;

	if (temp == NULL)
	{
		AVLNode *new_node = (AVLNode *)calloc(1, sizeof(AVLNode));
		new_node->left = NULL;
		new_node->right = NULL;
		new_node->key = new_key;
		new_node->bf = BALANCED;

		*src = new_node;

		return;
	}

	if (temp->key > new_key)
	{
		insert(&(temp->left), new_key, flag);

		if (*flag == IMBALANCED)
		{
			switch (temp->bf)
			{
				/* left inserted && right heavy */
				case RIGHT_HEAVY:
					temp->bf = BALANCED;
					*flag = BALANCED;
					break;

				/* left inserted && balanced */
				case BALANCED:
					temp->bf = LEFT_HEAVY;
					break;

				/* left inserted && left heavy */
				case LEFT_HEAVY:
					left_rotate(src, INSERTION);
					*flag = BALANCED;
					break;
			}
		}
	}
	else if (temp->key < new_key)
	{
		insert(&(temp->right), new_key, flag);

		if (*flag == IMBALANCED)
		{
			switch (temp->bf)
			{
				case RIGHT_HEAVY:
					right_rotate(src, INSERTION);
					*flag = BALANCED;
					break;

				case BALANCED:
					temp->bf = RIGHT_HEAVY;
					break;

				case LEFT_HEAVY:
					temp->bf = BALANCED;
					*flag = BALANCED;
					break;
			}
		}
	}
	else
	{
		return;
	}
}

/*
 * Unlike the condition of rotating in insertion
 * in which you can unambiguously select between LL and LR,
 * when it comes to deleting, there is a case
 * in which you can apply either LL or LR, maintaining
 * its balance.
 *
 * e.g)
 *      x
 *    /   \
 *   y     z
 *  / \
 * a   b
 * (There is only one node to be deleted, 'z'.)
 * (There can be three cases: a only, b only, and both a and b.)
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
static void delete(AVLNode **src, int key_to_del, int *flag)
{
	AVLNode *temp = *src;

	if (temp == NULL)
	{
		*flag = BALANCED;
		return;
	}

	if (temp->key > key_to_del)
	{
		delete(&(temp->left), key_to_del, flag);

		if (*flag == IMBALANCED)
		{
			switch (temp->bf)
			{
				case RIGHT_HEAVY:
					right_rotate(src, DELETION);
					*flag = BALANCED;
					break;

				case BALANCED:
					temp->bf = RIGHT_HEAVY;
					*flag = BALANCED;
					break;

				case LEFT_HEAVY:
					temp->bf = BALANCED;
					break;
			}
		}
	}
	else if (temp->key < key_to_del)
	{
		delete(&(temp->right), key_to_del, flag);

		if (*flag == IMBALANCED)
		{
			switch (temp->bf)
			{
				case RIGHT_HEAVY:
					temp->bf = BALANCED;
					break;

				case BALANCED:
					temp->bf = LEFT_HEAVY;
					*flag = BALANCED;
					break;

				case LEFT_HEAVY:
					left_rotate(src, DELETION);
					*flag = BALANCED;
					break;
			}
		}
	}
	else
	{
		if (*flag == FOUND)
		{
			*flag = IMBALANCED;
			*src = NULL;
			free(temp);
		}
		else
		{
			if (temp->left != NULL && temp->right != NULL)
			{
				#ifdef USE_SUCCESSOR

				int successor = search_successor(temp->right);
				temp->key = successor;
				delete(&(temp->right), successor, flag);

				#else

				int predec = search_predecessor(temp->left);
				temp->key = predec;
				delete(&(temp->left), predec, flag);

				#endif

				*flag = FOUND;
			}
			else
			{
				*src = temp->left != NULL ? temp->left : temp->right;
				free(temp);
			}
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
 * (There is only one new node, either 1 or 2.)
 *
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
 * (There is only one new node, either 2 or 3.)
 */
static void left_rotate(AVLNode **src, int flag)
{
	AVLNode *x = *src;
	AVLNode *y = x->left;

	/* LL rotation */
	if (y->bf == LEFT_HEAVY || y->bf == BALANCED)
	{
		x->left = y->right;
		y->right = x;

		x->bf = BALANCED;
		y->bf = BALANCED;

		if (flag == DELETION && y->right->left)
		{
			y->right->bf = LEFT_HEAVY;
			y->bf = RIGHT_HEAVY;
		}

		*src = y;
	}
	/* LR rotation */
	else
	{
		AVLNode *z = y->right;

		x->left = z->right;
		z->right = x;

		y->right = z->left;
		z->left = y;

		switch (z->bf)
		{
			case RIGHT_HEAVY:
				x->bf = BALANCED;
				break;

			case BALANCED:
				x->bf = BALANCED;
				y->bf = BALANCED;
				break;

			case LEFT_HEAVY:
				y->bf = BALANCED;
				break;
		}

		z->bf = BALANCED;
		*src = z;
	}
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
 * (There is only one new node, either 3 or 4.)
 *
 * RL rotation:
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
 * (There is only one new node, either 2 or 3.)
 */
static void right_rotate(AVLNode **src, int flag)
{
	AVLNode *x = *src;
	AVLNode *y = x->right;

	/* RR rotation */
	if (y->bf == RIGHT_HEAVY || y->bf == BALANCED)
	{
		x->right = y->left;
		y->left = x;

		x->bf = BALANCED;
		y->bf = BALANCED;

		if (flag == DELETION && y->left->right)
		{
			y->left->bf = RIGHT_HEAVY;
			y->bf = LEFT_HEAVY;
		}

		*src = y;
	}
	/* RL rotation */
	else
	{
		AVLNode *z = y->left;

		x->right = z->left;
		z->left = x;

		y->left = z->right;
		z->right = y;

		switch (z->bf)
		{
			case RIGHT_HEAVY:
				y->bf = BALANCED;
				break;

			case BALANCED:
				x->bf = BALANCED;
				y->bf = BALANCED;
				break;

			case LEFT_HEAVY:
				x->bf = BALANCED;
				break;
		}

		z->bf = BALANCED;
		*src = z;
	}
}

static int search_predecessor(AVLNode *left)
{
	int key = 0;
	AVLNode *predec = left->right;

	while (predec)
	{
		left->bf--;
		left = left->right;
		predec = predec->right;
	}

	left->right = NULL;
	key = predec->key;

	return key;
}

static int search_successor(AVLNode *right)
{
	int key = 0;
	AVLNode *successor = right->left;

	while (successor)
	{
		right->bf--;
		right = right->left;
		successor = successor->left;
	}

	right->left = NULL;
	key = successor->key;

	return key;
}

void destroy_tree(AVLNode *root)
{
	if (root)
	{
		destroy_tree(root->left);
		destroy_tree(root->right);
		free(root);
	}
}

void print_tree(AVLNode *src)
{
	if (src == NULL)
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

	push(stack, src, 0);

	while (stack->head)
	{
		ListNode *temp = pop(stack);
		AVLNode *data = temp->data;
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

static void put_space(List *stack)
{
	if (stack->head == NULL)
	{
		return;
	}

	ListNode *head = stack->head;
	ListNode *temp = stack->tail;
	unsigned depth = 0;
	unsigned prev_depth = 0;
	unsigned distance = 0;

	putwchar(L'\n');

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

	depth = head->depth;
	distance = depth - prev_depth;

	while (distance > 1)
	{
		wprintf(SPACING_NOBRANCH);
		distance--;
	}
	wprintf(SPACING_LBRANCH);
}

static void push(List *stack, AVLNode *data, unsigned depth)
{
	ListNode *new_node = (ListNode *)calloc(1, sizeof(ListNode));
	new_node->prev = NULL;
	new_node->next = stack->head;
	new_node->data = data;
	new_node->depth = depth;

	if (stack->head)
	{
		stack->head->prev = new_node;
	}
	else
	{
		stack->tail = new_node;
	}
	stack->head = new_node;
}

static ListNode *pop(List *stack)
{
	ListNode *head = stack->head;
	stack->head = head->next;

	if (stack->head)
	{
		stack->head->prev = NULL;
	}
	else
	{
		stack->tail = NULL;
	}

	return head;
}

