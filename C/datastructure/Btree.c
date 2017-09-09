/*
 * B-tree
 *
 * A B-tree is a rooted tree(whose root is T.root) having the
 * following properties:
 *
 * 1) Every node x has the following attributes:
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
 * 2) Each internal node.x also contains (x.n + 1) pointers
 * ,which means it has one greater number of pointers than its length,
 * x.c[1], x.c[2], ... x.c[n+1] to its children. Leaf nodes have
 * no children, and so their c[i] attributes are undefined.
 *
 * 3)The keys x.key[i] separate the ranges of keys stored in each subtree:
 * if k[i] is any key stored in the subtree with root x.c[i], then
 * k[1] <= x.key[1] <= k[2] <= x.key[2] <= ... <= x.key[n] <= k[n]
 *
 * 4) All leaves have the same depth, which is the tree's height h.
 *
 * 5) Nodes have lower and upper bounds on the number of keys
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
 * (BTREE_MERGE, BTREE_DELETE)
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* the degree of B-tree: 2t */
#define BTREE_DEGREE 5
/* the minimum number of keys: t-1 */
#define BTREE_KEY_MIN_COUNT (((BTREE_DEGREE+1)>>1) - 1)
/* the maximum number of keys: 2t-1 */
#define BTREE_KEY_MAX_COUNT (BTREE_DEGREE - 1)

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
void split_btree(node_t *src, size_t i);
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

node_t *allocate_node()
{
	node_t *new = (node_t *)calloc(1, sizeof(node_t));
	new->n = 0;
	new->key = (size_t *)calloc(BTREE_KEY_MAX_COUNT, sizeof(size_t));
	new->c = (node_t **)calloc(BTREE_DEGREE, sizeof(node_t *));
	new->leaf = false;
	return new;
}

void insert_btree(btree_t *src, size_t key)
{
	node_t *r = src->root;
	/* If it is full. */
	if (r->n == BTREE_KEY_MAX_COUNT)
	{
		node_t *s = allocate_node();
		src->root = s;
		s->c[0] = r;
		split_btree(s, 0);
		r = s;
	}
	insert_nonfull_btree(r, key);
}
void insert_nonfull_btree(node_t *src, size_t key)
{
	/* 'i' is initialized here. */
	size_t i = src->n - 1;
	size_t *src_key = src->key;
	if (src->leaf)
	{
		/* similar to 'Insertion Sort' */
		while(i != (size_t)-1 && key < src_key[i])
		{
			src_key[i+1] = src_key[i];
			i--;
		}
		src_key[i+1] = key;
		src->n++;
		// DISK_WRITE(src);
	}
	/* 'src->leaf != false' guarantees that it has children. */
	else
	{
		/* Ascertain where to split. */
		while(i != (size_t)-1 && key < src_key[i])
		{
			i--;
		}
		/*
		 * If you pass 'i' without increament of itself,
		 * the implement should deal with spliting the left child.
		 */
		i++;
		// DISK_READ(src.c[i]);
		if (src->c[i]->n == BTREE_KEY_MAX_COUNT)
		{
			split_btree(src, i);
			/*
			 * The median key of its right child
			 * which has been promoted.
			 * If the key is smaller than that,
			 * it will go left, maintaining its value.
			 * Otherwise, it will go right, added one.
			 */
			if (key > src->key[i])
			{
				i++;
			}
		}
		insert_nonfull_btree(src->c[i], key);
	}
}
/*
 * pre-condition:
 *           [ src ]
 *       [  src->c[i]  ]
 *
 * post-condition:
 *           [ src ]
 * [left(old)]     [right(old)]
 */
void split_btree(node_t *src, size_t i)
{
	/*
	 * To beautify its output,
	 * it will assign 0 or null to deleted keys or pointers.
	 * In real practice, it is not essential.
	 */
	node_t *left = src->c[i],
		   *right = allocate_node();
	unsigned t = BTREE_KEY_MIN_COUNT;

	/* Shift right to get a space for the new key. */
	for (size_t j = src->n; j > i; j--)
	{
		size_t k = j-1;
		src->key[k] = src->key[k-1];
		src->c[j] = src->c[j-1];
	}
	/* Move the median key to its parent. */
	src->key[i] = left->key[t];
	left->key[t] = 0;
	src->c[i+1] = right;
	src->n++;

	/* Copy its status and length. */
	right->leaf = left->leaf;
	left->n = t;
	right->n = t-1;
	/*
	 * Copy keys.
	 * left:  key[0], key[1], ..., key[t-1]
	 * median: key[t]
	 * right: key[t+1], key[t+2], ..., key[2t-2]
	 * (Since it is 0-based, the end of index is 2t-2.)
	 * (Note: it is not copying the median key.
	 * Thus, the boudnary should be 't-1', not 't'.)
	 */
	for (size_t j = 0; j < t-1; j++)
	{
		size_t ri = t+1;
		right->key[j] = left->key[j+ri];
		left->key[j+ri] = 0;
	}
	/*
	 * Copy pointers if it is an internal node.
	 * left:  0, 1, ..., t
	 * right: t+1, t+2, ..., 2t-1
	 * (Since it is 0-based, the end of index is 2t-1.)
	 */
	if (!right->leaf)
	{
		size_t ri = t+1;
		for (size_t j = 0; j < ri; j++)
		{
			right->c[j] = left->c[j+ri];
			left->c[j+ri] = NULL;
		}
	}
	// DISK_WRITE(y);
	// DISK_WRITE(z);
	// DISK_WRITE(src);
}

void free_btree(btree_t *src)
{
	free_all_node(src->root);
}
void free_all_node(node_t *src)
{
	size_t len = src->n;
	for (size_t i = 0; i < len; i++)
	{
		free_all_node(src->c[i]);
	}
	free(src->key);
	free(src->c);
}

#define SELECT(xor,a,b) (queue_t*)((unsigned long)(xor) ^ (unsigned long)(a) ^ (unsigned long)(b))
void print_btree(btree_t *src)
{
	/* Enqueue & Dequeue nodes to print */
	queue_t line1 = { NULL, NULL },
			line2 = { NULL, NULL };
	enqueue(&line1, src->root);
	/* While neither line1 nor line2 is empty. */
	while(line1.head || line2.head)
	{
		queue_t *current_line = line1.head ? &line1 : &line2;
		queue_t *next_line = SELECT(current_line, &line1, &line2);

		/* While current_line is not empty. */
		while(current_line->head)
		{
			node_t *target = dequeue(current_line);
			/* Need to be changed. */
			size_t i = 0;
			for (i = 0; i < BTREE_DEGREE-1; i++)
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