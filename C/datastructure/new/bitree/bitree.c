#include "bitree.h"

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

int bitr_insert(BiTrNode **src, int new_key)
{
	if (*src == NULL)
	{
		BiTrNode *new_node = (BiTrNode *)calloc(1, sizeof(BiTrNode));
		new_node->left = NULL;
		new_node->right = NULL;
		new_node->key = new_key;

		*src = new_node;

		return true;
	}

	BiTrNode *temp = *src;
	BiTrNode **branch = NULL;

	while (temp)
	{
		int cur_key = temp->key;

		if (new_key < cur_key)
		{
			branch = &(temp->left);
			temp = temp->left;
		}
		else if (new_key > cur_key)
		{
			branch = &(temp->right);
			temp = temp->right;
		}
		else
		{
			return false;
		}
	}

	BiTrNode *new_node = (BiTrNode *)calloc(1, sizeof(BiTrNode));
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->key = new_key;

	*branch = new_node;

	return true;
}

int bitr_delete(BiTrNode **src, int key_to_del)
{
	if (*src == NULL)
	{
		return false;
	}

	BiTrNode *temp = *src;
	BiTrNode **branch = src;

	while (temp)
	{
		int cur_key = temp->key;

		if (key_to_del < cur_key)
		{
			branch = &(temp->left);
			temp = temp->left;
		}
		else if (key_to_del > cur_key)
		{
			branch = &(temp->right);
			temp = temp->right;
		}
		else
		{
			break;
		}
	}

	if (temp)
	{
		if (temp->right == NULL)
		{
			*branch = temp->left;
		}
		else if (temp->left == NULL)
		{
			*branch = temp->right;
		}
		else
		{
			#ifdef USE_SUCCESSOR

			BiTrNode *successor = search_successor(temp->right);
			successor->left = temp->left;
			successor->right = temp->right;
			*branch = successor;

			#else

			BiTrNode *predec = search_predecessor(temp->left);
			predec->left = temp->left;
			predec->right = temp->right;
			*branch = predec;

			#endif
		}

		free(temp);
	}
	else
	{
		return false;
	}

	return true;
}

BiTrNode *bitr_search(BiTrNode *src, int key_to_find)
{
	BiTrNode *temp = src;

	while (temp)
	{
		int cur_key = temp->key;

		if (cur_key < key_to_find)
		{
			temp = temp->left;
		}
		else if (cur_key > key_to_find)
		{
			temp = temp->right;
		}
		else
		{
			break;
		}
	}

	return temp;
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

	while (successor->right)
	{
		right = right->left;
		successor = successor->left;
	}
	right->left = NULL;

	return successor;
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

static void push(List *src, BiTrNode *data, unsigned depth)
{
	ListNode *new_node = (ListNode *)calloc(1, sizeof(ListNode));
	new_node->prev = NULL;
	new_node->next = src->head;
	new_node->data = data;
	new_node->depth = depth;

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

