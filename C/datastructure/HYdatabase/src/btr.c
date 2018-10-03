#include "btr.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/******************************************************************************/
#define malloc_handler(ptr, size) do { \
	ptr = malloc(size); \
	if (!ptr) { \
		fprintf(stderr, "In function '%s' at %s (line: %d) ", \
			__FUNCTION__, __FILE__, __LINE__); \
		perror(""); \
		exit(EXIT_FAILURE); \
	} \
} while (0)

#define BTR_ORDER 4
#define BTR_MAX_ORDER (BTR_ORDER << 1)

#define btr_parent(n) ((struct btr_node *)(n->parent & ~3))
/* To test if it is a parent of a leaf node. */
#define btr_is_last(n) (n->parent & 1)
#define btr_set_last(n) (n->parent |= 1)
#define btr_is_root(n) (btr_parent(n) == NULL)

#define max_order(o) (o << 1)
#define max_fanout(o) (max_order(o)+1)
#define split_point(o) ((size_t)((o+1)>>1))
/******************************************************************************/
/*
 * B+ Tree header.
 * Not only it contains a tree,
 * but other configuration that is required to build a tree.
 */
struct btr_header
{
	struct btr_node *root;
	unsigned order;
};

/* internal node. */
struct btr_node
{
	unsigned long parent;
	/* child can be either 'struct internal_page' or 'struct leaf_page' */
	void **child;
	int64_t *key;
	size_t count;
};

/* leaf node */
struct btr_leaf
{
	struct btr_node *parent;
	struct btr_leaf *prev;
	struct btr_leaf *next;
	struct record **data;
	int64_t *key;
	size_t count;
};

/*
 * Record is a pair of (key, value)
 * of 120 bytes.
 */
struct record
{
	/* 8 bytes */
	int64_t key;
	/* 120 bytes */
	int value;
};
/******************************************************************************/
static inline struct btr_node *create_btr_node(size_t order);
static inline void free_btr_node(struct btr_node *node);
static inline struct btr_leaf *create_btr_leaf(size_t order);
static inline void free_btr_leaf(struct btr_leaf *node);

/*
 * Searching method used in insert.
 */
static inline int binary_search(int64_t *key, size_t count, int64_t v);
static inline int brute_search(int64_t *key, size_t count, int64_t v);
static inline size_t binary_range_search(int64_t *key, size_t count, int64_t v);
static inline size_t brute_range_search(int64_t *key, size_t count, int64_t v);

static struct btr_leaf *btr_get_leaf(struct btr_node *root, int64_t key);
static struct record *btr_get_record(struct btr_leaf *leaf, int64_t key);

// struct btr_header *btr_init(size_t order);
// struct btr_node *btr_insert(struct btr_header *tree, struct record *data);
/******************************************************************************/
static inline struct btr_node *create_btr_node(size_t order)
{
	struct btr_node *new = NULL;
	malloc_handler(new, sizeof(*new));
	new->parent = 0;
	malloc_handler(new->child, sizeof(*new->child) * max_fanout(order));
	malloc_handler(new->key, sizeof(*new->child) * max_order(order));
	new->count = 0;

	return new;
}

static inline void free_btr_node(struct btr_node *node)
{
	free(node->child);
	free(node->key);
	free(node);
}

static inline struct btr_leaf *create_btr_leaf(size_t order)
{
	struct btr_leaf *new = NULL;
	malloc_handler(new, sizeof(*new));
	new->parent = NULL;
	new->prev = NULL;
	new->next = NULL;
	malloc_handler(new->data, sizeof(*new->data) * max_order(order));
	malloc_handler(new->key, sizeof(*new->key) * max_order(order));
	new->count = 0;

	return new;
}

static inline void free_btr_leaf(struct btr_leaf *node)
{
	free(node->data);
	free(node->key);
	free(node);
}

/*
 * Find a exact matching value in key.
 * Returns -1 when there is none.
 */
static inline int binary_search(int64_t *key, size_t count, int64_t v)
{
	size_t p = 0;
	size_t r = count-1;
	size_t q = (p+r) >> 1;
	size_t last = r;

	while (true)
	{
		if (key[q] == v)
		{
			break;
		}

		if (q == 0 || q == last)
		{
			q = -1;
			break;
		}

		if (key[q] < v)
		{
			p = q+1;
		}
		else
		{
			r = q-1;
		}

		q = (p+r) >> 1;
	}

	return q;
}

static inline int brute_search(int64_t *key, size_t count, int64_t v)
{
	size_t i = 0;

	while (count && key[i] <= v)
	{
		i++;
		count--;
	}

	return i;
}

/*
 * Find a value between two sequential keys in key.
 * Returns non-negative value.
 */
static inline size_t binary_range_search(int64_t *key, size_t count, int64_t v)
{
	size_t p = 0;
	size_t r = count-1;
	size_t q = (p+r) >> 1;
	size_t last = r;

	while (q != 0 && q != last)
	{
		if (key[q] <= v && v < key[q+1])
		{
			break;
		}

		if (v < key[q])
		{
			r = q-1;
		}
		else
		{
			p = q+1;
		}

		q = (p+r) >> 1;
	}

	return q;
}

/*
 * Identical to brute_search function.
 */
static inline size_t brute_range_search(int64_t *key, size_t count, int64_t v)
{
	size_t i = 0;

	while (count && key[i] <= v)
	{
		i++;
		count--;
	}

	return i;
}

/*
 * Returns a leaf node that might contain a matching key.
 */
static struct btr_leaf *btr_get_leaf(struct btr_node *root, int64_t key)
{
	struct btr_node *page = root;
	size_t i = 0;

	/* Empty tree */
	if (page == NULL)
	{
		return NULL;
	}

	while (true)
	{
		/* Locate the index. */
		i = binary_range_search(page->key, page->count, key);

		/* The next node is a leaf, break. */
		if (btr_is_last(page))
		{
			break;
		}

		/* Get into the next page. */
		page = (struct btr_node *)(page->child[i]);
	}

	return (struct btr_leaf *)(page->child[i]);
}

/*
 * Returns a record node with the key in a leaf node,
 * or NULL when there is none.
 */
static struct record *btr_get_record(struct btr_leaf *leaf, int64_t key)
{
	int i = binary_search(leaf->key, leaf->count, key);

	return i == -1 ? NULL : leaf->data[i];
}

struct btr_header *btr_init(size_t order)
{

	struct btr_header *new = NULL;
	malloc_handler(new, sizeof(*new));
	new->root = NULL;
	new->order = order;

	return new;
}

/*
 * When to create a record?
 */
struct btr_node *btr_insert(struct btr_header *tree, struct record *data)
{
	struct btr_node *root = tree->root;
	size_t order = tree->order;

	/* A new tree */
	if (root == NULL)
	{
		tree->root = create_btr_node(order);
		return NULL;
	}

	/* Prevent from creating duplicate keys. */
	int64_t k = data->key;
	struct btr_leaf *leaf = btr_get_leaf(root, k);

	if (btr_get_record(leaf, k))
	{
		return NULL;
	}

	/* leaf is full, requiring splitting. */
	if (leaf->count == max_order(order))
	{
	}
	/* Simple insertion. */
	else
	{
		/* WORKING HERE. */
		/* Another binary range search??? */
		int64_t *key = leaf->key;
		struct record **data = leaf->data;
		size_t count = leaf->count;
		size_t q = binary_range_search(key, count, k);
		int64_t *pos = key + q;

		key += count;
		data += count;

		while (1)
		{
		}
	}
}

