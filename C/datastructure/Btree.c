/*
 * B-tree
 *
 * A B-tree is a rooted tree(whose root is T.root) having the
 * following properties:
 *
 * 1. Every node x has the following attributes:
 *	a. x.n, the number of keys currently stored in node x.
 *	b. the x.n keys themselves, x.key[1], x.key[2], ..., x.key[n]
 *	stored in nondecreasing order,
 *	so that x.key[1] <= x.key[2] <= ... <= x.key[n]
 *	c. x.leaf, a boolean value that is TRUE if x is a leaf
 *	and FALSE if x is an internal node.
 * (For instance:
 *		typedef struct {
 *	 		size_t n;
 *	 		size_t *key;
 *	 		bool leaf;
 *		} node_t;
 * )
 *
 * 2. Each internal node.x also contains (x.n + 1) pointers
 * ,which means it has one greater number of pointers than its length,
 * x.c[1], x.c[2], ... x.c[n+1] to its children. Leaf nodes have
 * no children, and so their c[i] attributes are undefined.
 *
 * 3. The keys x.key[i] separate the ranges of keys stored in each subtree:
 * if k[i] is any key stored in the subtree with root x.c[i], then
 * k[1] <= x.key[1] <= k[2] <= x.key[2] <= ... <= x.key[n] <= k[n]
 *
 * 4. All leaves have the same depth, which is the tree's height h.
 *
 * 5. Nodes have lower and upper bounds on the number of keys
 * they can contain. We express theses bounds in terms of a fixed integer
 * t >= 2 called the "minimum degree" of the B-tree:
 *	a. Every node other than the root must have at least t-1 keys.
 *	Every internal node other than the root thus has at least t children.
 *	If the tree is nonempty, the root must have at least one key.
 *	b. Every node may contain at most 2t-1 keys. Therefore, an internal node
 *	may have at most 2t children. We say that a node is full
 *	if it contains exactly 2t-1 keys.
 * (Note: B-tree requires each internal node to be at least half full,
 *  whereas B*-tree requires 2/3 full.)
 * (When t=2, every internal node has either 2,3 or 4 children,
 * and the tree is called 2-3-4 tree.)
 *
 * Pseudocode
 * BTREE_SEARCH(x, k):
 *	i = 1
 *	while i <= x.n and k > x.key[i]
 *		i = i + 1
 *	if i <= x.n and k == x.key[i]
 *		return (x, i)
 *	else if x.leaf
 *		return NIL
 *	else DISK_READ(x, c[i])
 *		return BTREE_SEARCH(x.c[i], k)
 *
 * BTREE_CREATE(T):
 *	x = ALLOCATE_NODE()
 *	x.leaf = TRUE
 *	x.n = 0
 *	DISK_WRITE(x)
 *	T.root = x
 *
 * BTREE_SPLIT_CHILD(x, i):
 *	z = ALLOCATE_NODE()
 *	y = x.c[i]
 *	z.leaf = y.leaf
 *	z.n = t-1
 *	for j = 1 to t-1
 *		z.key[j] = y.key[j+t]
 *	if not y.leaf
 *		for j = 1 to t
 *			z.c[j] = y.c[j+t]
 *	y.n = t-1
 *	for j = (x.n + 1) downto i+1
 *		x.c[j+1] = x.c[j]
 *	x.c[i+1] = z
 *	for j = x.n downto i
 *		x.key[j+1] x.key[j]
 *	x.key[i] = y.key[t]
 *	x.n = x.n + 1
 *	DISK_WRITE(y)
 *	DISK_WRITE(z)
 *	DISK_WRITE(x)
 *
 * BTREE_INSERT(T, k):
 *	r = T.root
 *	if r.n == 2t-1
 *		s = ALLOCATE_NODE()
 *		T.root = s
 *		s.leaf = FALSE
 *		s.n = 0
 *		s.c[1] = r
 *		BTREE_SPLIT_CHILD(s, 1)
 *		BTREE_INSERT_NONFULL(s, k)
 *	else
 *		BTREE_INSERT_NONFULL(r, k)
 *
 * BTREE_INSERT_NONFULL(x, k):
 *	i = x.n
 *	if x.leaf
 *		while i >= 1 and k < x.key[i]
 *			x.key[i+1] = x.key[i]
 *			i = i - 1
 *		x.key[i+1] = k
 *		x.n = x.n + 1
 *		DISK_WRITE(x)
 *	else
 *		while i >= 1 and k < x.key[i]
 *			i = i - 1
 *		i = i + 1
 *		DISK_READ(x.c[i])
 *		if x.c[i].n == 2t-1
 *			BTREE_SPLIT_CHILD(x, i)
 *			if k > x.key[i]
 *				i = i + 1
 *		BTREE_INSERT_NONFULL(x.c[i], k)
 *
 * For BTREE_DELETE and BTREE_MERGE
 * 
 * 1. If the key k is in node x and x is a leaf, delete the key k from x.
 *
 * 2. If the key k is in node x and x is an internal node:
 *	a. If the child y that precedes k in node x has at least t keys,
 *	then find the predecessor k` of k in the subtree rooted at y. 
 *	Recursively delete k`, and replace k by k` in x.
 *	(We can find it in a single downward pass.)
 *  b. If y has fewer than t keys, then, symmetrically,
 *	examine the child z that follows k in node x. If z has at least t keys,
 *	then find the successor k` of k in the subtree rooted at z.
 *	Recursively delete k`, and replace k by k` in x.
 *	(We can find it in a single downward pass.)
 *	c. Otherwise, if both y and z have only t-1 keys,
 *	merge k and all of z into y, so that x loses both k and the pointer to z,
 *	and y now contains 2t-1 keys. Then free z, and recursively delete k from y.
 * e.g)
 * pre-condition:
 *   [k] [a] [b]
 * [y] [z] [c] [d]
 *
 * post-condition:
 *        [a]   [b]
 * [y-k-z]   [c]   [d]
 * (However, array in C is not dynamic.
 * The array should be one bigger than it is required to be.)
 *
 * 3. If the key k is not present in internal node x,
 * determine the root x.c[i] of the appropriate subtree that must contain k,
 * if k is in the tree at all. If x.c[i] has only t-1 kyes,
 * execute step 3a or 3b as necessary to guarantee that we descend
 * to a node containing at least t keys.
 * Then finish by recursing on the appropriate child of x.
 *	a. If x.c[i] has only t-1 keys but has an immediate sibling with at least
 *	t keys, give x.c[i] an extra key by moving a key from x down into x.c[i]
 *	moving a key from x.c[i]'s immdediate left or right sibling up into x, and
 *	moving the appropriate child pointer from the sibling into x.c[i].
 *	b. If x.c[i] and both of x.c[i]'s immediate siblings have t-1 keys,
 *	merge x.c[i] with one sibling, which involoves moving a key from x
 *	down into the new merged node to become the median key for that node.
 *
 * This implementation depends on the above idea where it makes use of
 * the degree of B-tree(2t), resulting in better performance.
 * If you want to build a B-tree the degree of which is not even,
 * "it is feasible": search for the apposite position,
 * do insertion or deletion, and reconstruct the B-tree moving upward.
 * HOWEVER, the critical problem assurges when it fails to search a key,
 * because it assumes that there must be the key to find in the tree
 * in every step so that it splits (or merges) in advance.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* the lower bound on the number of children. */
#define BTREE_DEGREE 2
/* the upper bound on the nubmer of children. */
#define BTREE_ORDER (BTREE_DEGREE<<1)
/* the minimum number of keys: t-1 */
#define BTREE_KEY_MIN_COUNT (BTREE_DEGREE - 1)
/* the maximum number of keys: 2t-1 */
#define BTREE_KEY_MAX_COUNT (BTREE_ORDER - 1)

typedef struct node {
	/* The size of currently stored keys. */
	size_t n;
	size_t *key;
	/* Children */
	struct node **c;
	/* If it is an internal node or not. */
	bool leaf;
} node_t;

typedef struct btree {
	node_t *root;
} btree_t;

/* For print_btree */
typedef struct qdata {
	node_t *node_ptr;
	struct qdata *next;
} qdata_t;

typedef struct queue {
	qdata_t *head;
	qdata_t *tail;
} queue_t;

void create_btree(btree_t *src);
node_t *allocate_node();

void insert_btree(btree_t *src, size_t key);
void insert_nonfull_btree(node_t *src, size_t key);
void delete_btree(btree_t *src, size_t key);
void delete_full_btree(node_t *src, size_t key);

void split_btree(node_t *src, size_t pos);
void merge_btree(node_t *src, size_t pos);
size_t rotate_left(node_t *src, size_t i);
size_t rotate_right(node_t *src, size_t i);
void shift_left(node_t *src);
void shift_right(node_t *src);

void free_btree(btree_t *src);
void free_all_node(node_t *src);

/* Printing set */
void print_btree(btree_t *src);
qdata_t *make_qdata(node_t *src);
void enqueue(queue_t *src, node_t *data);
node_t *dequeue(queue_t *src);

int main(int argc, const char *argv[])
{
	if (argc != 2)
	{
		puts("Command-line argument required.");
		exit(1);
	}
	int length = atoi(argv[1]);

	btree_t test = { NULL };
	create_btree(&test);
	for (int i = 1; i <= length; i++)
	{
		insert_btree(&test, i);
	}
	print_btree(&test);

	for (int i = 1; i <= length; i++)
	{
		delete_btree(&test, i);
		printf("===Deleting %d===\n", i);
		/* if i == 16, rotate_left is wrong */
		print_btree(&test);
	}

	free_btree(&test);

	return 0;
}

void create_btree(btree_t *src)
{
	node_t *new = allocate_node();
	new->leaf = true;
	// DISK_WRITE()
	src->root = new;
}
/*
 * NOTE:
 * The maximum number of keys that a node, except the root, can have
 * is 2t-1, HOWEVER, the following implementaion allocates 2t spaces.
 * It is due to implementation of 'split' and 'merge'.
 */
node_t *allocate_node()
{
	node_t *new = (node_t *)calloc(1, sizeof(node_t));
	new->n = 0;
	new->key = (size_t *)calloc(BTREE_ORDER, sizeof(size_t));
	new->c = (node_t **)calloc(BTREE_ORDER, sizeof(node_t *));
	new->leaf = false;
	return new;
}
void insert_btree(btree_t *src, size_t key)
{
	node_t *root = src->root;
	/* If full, split it. */
	if (root->n == BTREE_KEY_MAX_COUNT)
	{
		node_t *new_root = allocate_node();
		src->root = new_root;
		new_root->c[0] = root;
		split_btree(new_root, 0);
		insert_nonfull_btree(new_root, key);
	}
	else
	{
		insert_nonfull_btree(root, key);
	}
}
void insert_nonfull_btree(node_t *src, size_t key)
{
	if (src->leaf)
	{
		size_t i = src->n;
		while (i > 0 && src->key[i-1] > key)
		{
			src->key[i] = src->key[i-1];
			i--;
		}
		src->key[i] = key;
		src->n++;
	}
	else
	{
		size_t i = src->n-1;
		while (i > 0 && src->key[i] > key)
		{
			i--;
		}
		i++;

		if (src->c[i]->n == BTREE_KEY_MAX_COUNT)
		{
			split_btree(src, i);
			/* Compare with the new separator. */
			if (key > src->key[i])
			{
				i++;
			}
		}
		insert_nonfull_btree(src->c[i], key);
	}
}
void delete_btree(btree_t *src, size_t key)
{
	/* Search first */
	node_t *root = src->root;
	delete_full_btree(root, key);
	if (root->n == 0)
	{
		src->root = root->c[0];
		free(root->key);
		free(root);
	}
}
void delete_full_btree(node_t *src, size_t key)
{
	size_t i = 0,
		   len = src->n;
	while (i < len && src->key[i] < key)
	{
		i++;
	}
	if (i < len && src->key[i] == key)
	{
		if (src->leaf)
		{
			size_t len = src->n-1;
			while (i < len)
			{
				src->key[i] = src->key[i+1];
				i++;
			}
			src->key[len] = 0;
			src->n--;
		}
		else
		{
			if (src->c[i]->n != BTREE_KEY_MIN_COUNT)
			{
				size_t new_key = rotate_right(src, i);
				delete_full_btree(src->c[i], new_key);
			}
			else if (src->c[i+1]->n != BTREE_KEY_MIN_COUNT)
			{
				size_t new_key = rotate_left(src, i+1);
				delete_full_btree(src->c[i+1], new_key);
			}
			else
			{
				merge_btree(src, i);
				delete_full_btree(src->c[i], key);
			}
		}
	}
	else
	{
		if (src->leaf)
		{
			return;
		}
		else
		{
			if (src->c[i]->n == BTREE_KEY_MIN_COUNT)
			{
				if (i == len)
				{
					i--;
					merge_btree(src, i);
				}
				else
				{
					merge_btree(src, i);
				}
			}
			delete_full_btree(src->c[i], key);
		}
	}
}
/*
 * pre-condition: a non-full PARENT node and the position of the FULL CHILD node.
 * post-condition: the parent node with the child node and a new sibling.
 */
void split_btree(node_t *src, size_t pos)
{
	node_t *left = src->c[pos],
		   *right = allocate_node();

	/* Insert the new right child. */	
	size_t last_index = src->n;
	src->n++;

	size_t *kp = src->key + last_index - 1,
		   *bkp = kp - 1,
		   *delim = src->key + pos;
	node_t **cp = src->c + last_index,
		   **bcp = cp - 1;

	while (kp != delim)
	{
		*kp = *bkp;
		*cp = *bcp;
		kp--, bkp--;
		cp--, bcp--;
	}
	*kp = left->key[BTREE_KEY_MIN_COUNT];
	left->key[BTREE_KEY_MIN_COUNT] = 0;
	*cp = right;
	/* Insert the new right child(End). */

	/* Construct a new sibling. */
	size_t t = BTREE_KEY_MIN_COUNT + 1;
	kp = right->key;
	bkp = left->key + t;
	/* (bkp + t) == (left->key + left->n - 1) */
	delim = bkp + t;

	while (bkp <= delim)
	{
		*kp = *bkp;
		*bkp = 0;
		kp++;
		bkp++;
	}
	if (left->leaf == false)
	{
		cp = right->c;
		bcp = left->c + t;
		/* TODO */
		node_t **delim = bcp + t;

	}

	/* Update status. */
	right->n = left->n = BTREE_KEY_MIN_COUNT;
	right->leaf = left->leaf;
}
/*
 * pre-condition: a parent node with ENOUGH keys
 * post-condition: the node with the merged child.
 */
void merge_btree(node_t *src, size_t pos)
{
	node_t *left = src->c[pos],
		   *right = src->c[pos+1];
	size_t len = src->n;

	/* Give the separator to its left child. */
	left->key[BTREE_KEY_MIN_COUNT] = src->key[pos];

	/* Decrease the length */
	src->n--;

	/* Delete the right child. */
	for (size_t i = pos, j = i+1; i < len; i++, j++)
	{
		src->key[i] = src->key[i+1];
		src->c[j] = src->c[j+1];
	}
	src->key[len-1] = 0;
	src->c[len] = NULL;

	/* Copy the keys of the right child to the left. */
	for (size_t i = 0, t = BTREE_KEY_MIN_COUNT, ri = t+1; i < t; i++)
	{
		left->key[i+ri] = right->key[i];
	}
	if (left->leaf == false)
	{
		for (size_t i = 0, t = BTREE_KEY_MIN_COUNT, ri = t+1; i < t; i++)
		{
			left->c[i+ri] = right->c[i];
		}
		left->c[BTREE_KEY_MAX_COUNT] = right->c[BTREE_KEY_MIN_COUNT];
	}

	/* Update status. */
	left->n = BTREE_KEY_MAX_COUNT;

	/* Free */
	free(right->key);
	free(right);
}
/* Anti-clockwise */
size_t rotate_left(node_t *src, size_t i)
{
	node_t *left = src->c[i],
		   *right = src->c[i+1];
	size_t last_index = left->n;
	
	left->key[last_index-1] = src->key[i];
	src->key[i] = right->key[0];
	/* Attach the last child to the left. */
	left->c[last_index] = right->c[0];

	shift_left(right);
}
/* Clockwise */
size_t rotate_right(node_t *src, size_t i)
{
	node_t *left = src->c[i],
		   *right = src->c[i+1];
	size_t last_index = left->n;

	shift_right(right);

	right->key[0] = src->key[i];
	src->key[i] = left->key[last_index-1];
	left->key[last_index-1] = 0;
	/* Attach the last child to the right. */
	right->c[0] = left->c[last_index];
	left->c[last_index] = NULL;
	left->n--;
}
/*
 * The first element will be unshifted.
 * Increament of its length included.
 */
void shift_left(node_t *src)
{
	size_t *p = src->key,
	/* forward pointer */
		   *fp = p + 1,
		   *end = p + src->n - 1;
	
	while (p != end)
	{
		*p = *fp;
		p++;
		fp++;
	}
	*p = 0;
	src->n--;

	/* If it is an internal node */
	if (src->leaf == false)
	{
		node_t **p = src->c,
			   **fp = p + 1,
			   **end = p + src->n;
		while (p != end)
		{
			*p = *fp;
			p++;
			fp++;
		}
		*p = NULL;
	}
}
/*
 * The first element will be shifted. Thus empty.
 * Decrement of its length included.
 */
void shift_right(node_t *src)
{
	size_t *start = src->key,
	/* backward pointer */
		   *p = start + src->n - 1,
		   *bp = p - 1;
	
	while (p != start)
	{
		*bp = *p;
		p--;
		bp--;
	}
	*p = 0;
	src->n++;

	/* If it is an internal node */
	if (src->leaf == false)
	{
		node_t **start = src->c,
			   **p = start + src->n,
			   **bp = p - 1;
		while (p != start)
		{
			*p = *bp;
			p--;
			bp--;
		}
		*p = NULL;
	}
}

void free_btree(btree_t *src)
{
	free_all_node(src->root);
}
void free_all_node(node_t *src)
{
	if (!src->leaf)
	{
		size_t len = src->n;
		for (size_t i = 0; i < len; i++)
		{
			free_all_node(src->c[i]);
		}
	}
	free(src->key);
	free(src->c);
}

/****************************************/

#define SELECT(xor,a,b) (queue_t*)((unsigned long)(xor) ^ (unsigned long)(a) ^ (unsigned long)(b))
void print_btree(btree_t *src)
{
	queue_t line1 = { NULL, NULL },
			line2 = { NULL, NULL };
	if (src->root == NULL)
	{
		puts("No data in the tree.");
		return;
	}
	enqueue(&line1, src->root);
	while(line1.head || line2.head)
	{
		queue_t *current_line = line1.head ? &line1 : &line2;
		queue_t *next_line = SELECT(current_line, &line1, &line2);

		while(current_line->head)
		{
			node_t *target = dequeue(current_line);
			size_t i = 0;
			for (i = 0; i < BTREE_ORDER-1; i++)
			{
				if (target->c[i])
					enqueue(next_line, target->c[i]);
				printf("%d ", target->key[i]);
			}
			if (target->c[i])
				enqueue(next_line, target->c[i]);
		}
		putchar('\n');
	}
}
qdata_t *make_qdata(node_t *src)
{
	qdata_t *new = (qdata_t *)calloc(1, sizeof(qdata_t));
	new->next = NULL;
	new->node_ptr = src;

	return new;
}
void enqueue(queue_t *src, node_t *data)
{
	if(src->head)
	{
		qdata_t *new = make_qdata(data);
		src->tail->next = new;
		src->tail = new;
	}
	else
	{
		src->head = make_qdata(data);
		src->tail = src->head;
	}
}
node_t *dequeue(queue_t *src)
{
	qdata_t *del = src->head;
	node_t *ret = del->node_ptr;

	src->head = del->next;
	free(del);

	return ret;
}