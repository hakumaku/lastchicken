#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BTREE_DEGREE	11
#define BTREE_MAX_CHILD BTREE_DEGREE
#define BTREE_MIN_CHILD (BTREE_MAX_CHILD>>1)
#define BTREE_MAX_KEYS	(BTREE_DEGREE-1)
#define BTREE_MIN_KEYS	(BTREE_MAX_KEYS>>1)
#define SPLIT_LENGTH	(BTREE_MIN_KEYS + !(BTREE_DEGREE & 1))
#define MERGE_LENGTH	SPLIT_LENGTH

typedef struct btree_node
{
	struct btree_node *child[BTREE_DEGREE];
	size_t keys[BTREE_MAX_KEYS];
	size_t n;
	unsigned char leaf;
} BtreeNode;

BtreeNode *create_node(size_t new_key);
void insert(BtreeNode *src, size_t new_key, int *flag);
BtreeNode *leaf_split(BtreeNode *src, size_t new_key);
BtreeNode *nonleaf_split(BtreeNode *src, size_t new_key);
BtreeNode *leaf_merge(BtreeNode *src, size_t pos);

void print_array(size_t *arr, size_t len);
void print_node(BtreeNode *src);

void init_dummy_keys(BtreeNode *src);
void init_dummy_child(BtreeNode *src);

int main(int argc, const char *argv[])
{
	BtreeNode *foo = (BtreeNode *)calloc(1, sizeof(BtreeNode));
	BtreeNode *bar = (BtreeNode *)calloc(1, sizeof(BtreeNode));
	BtreeNode *spam = NULL;

	init_dummy_keys(foo);
	init_dummy_child(foo);
	foo->leaf = false;

	bar = leaf_split(foo, 49);

	puts("foo");
	print_node(foo);
	puts("bar");
	print_node(bar);

	// bar->child[0] = new;
	// bar->child[1] = foo;

	// leaf_merge(bar, 0);
	// puts("n1");
	// print_node(new);
	// puts("n2");
	// print_node(foo);

	return 0;
}

void insert(BtreeNode *src, size_t new_key, int *flag)
{
	if (!src->leaf)
	{
		size_t *keys = src->keys;
		size_t len = src->n;
		size_t pos = 0;

		while (pos < len && *keys < new_key)
		{
			pos++;
			keys++;
		}

		printf("Go one level deeper at: %ld\n", pos);
		insert(src->child[pos], new_key, flag);

		if (1)
		{
			/* Do sth */
		}
	}
	else
	{
		/* full or nonfull */
		if (src->n != BTREE_MAX_KEYS)
		{
			size_t pos = src->n - 1;
			size_t *p = src->keys + src->n;
			size_t *q = p - 1;

			while (src->keys < q)
			{
				*p = *q;
				p--;
				q--;
				pos--;
			}
			*q = new_key;
			src->n++;

			printf("New key insertion at: %ld\n", pos);
		}
		else
		{
			BtreeNode *new = leaf_split(src, new_key);
			printf("Split has occured at: %ld\n", (long int)1);
		}
	}
}
/*
 * There exists three cases:
 *
 * Odd degree:
 * 1 2 3 4 5 6 NIL
 *       ^      ^
 *      min(3) max(6)
 * (0-based)
 *
 * 1)
 * n 1 2 [3] 4 5 6 -> 3 goes up.
 * 1 n 2 [3] 4 5 6 -> 3 goes up.
 * 1 2 n [3] 4 5 6 -> 3 goes up.
 *
 * 2)
 * 1 2 3 [n] 4 5 6 -> n goes up.
 *
 * 3)
 * 1 2 3 [4] n 5 6 -> 4 goes up.
 * 1 2 3 [4] 5 n 6 -> 4 goes up.
 * 1 2 3 [4] 5 6 n -> 4 goes up.
 *
 * Even degree:
 * 1 2 3 4 5 6 7 NIL
 *       ^        ^
 *      min(3)   max(7)
 * (0-based)
 *
 * 1)
 * n 1 2 [3] 4 5 6 7 -> 3 goes up.
 * 1 n 2 [3] 4 5 6 7 -> 3 goes up.
 * 1 2 n [3] 4 5 6 7 -> 3 goes up.
 *
 * 2)
 * 1 2 3 [n] 4 5 6 7 -> n goes up.
 *
 * 3)
 * 1 2 3 [4] n 5 6 7 -> 4 goes up.
 * 1 2 3 [4] 5 n 6 7 -> 4 goes up.
 * 1 2 3 [4] 5 6 n 7 -> 4 goes up.
 * 1 2 3 [4] 5 6 7 n -> 4 goes up.
 *
 */
BtreeNode *leaf_split(BtreeNode *restrict src, size_t new_key)
{
	BtreeNode *sibling = (BtreeNode *)calloc(1, sizeof(BtreeNode));
	size_t median = 0;

	if (new_key < src->keys[BTREE_MIN_KEYS-1])
	{
		median = src->keys[BTREE_MIN_KEYS-1];

		size_t *end = src->keys - 1;
		size_t *k1 = src->keys + BTREE_MIN_KEYS - 1;
		size_t *k2 = k1 - 1;

		while (end < k2 && new_key < *k2)
		{
			*k1 = *k2;
			k1--;
			k2--;
		}
		*k1 = new_key;

		size_t *sib_keys = sibling->keys;
		end = src->keys + BTREE_MAX_KEYS;
		k1 = src->keys + BTREE_MIN_KEYS;

		while (k1 < end)
		{
			*sib_keys = *k1;
			*k1 = 0;
			sib_keys++;
			k1++;
		}
	}
	else if (src->keys[BTREE_MIN_KEYS] < new_key)
	{
		median = src->keys[BTREE_MIN_KEYS];

		size_t *end = src->keys + BTREE_MAX_KEYS;
		size_t *k1 = src->keys + BTREE_MIN_KEYS;
		size_t *k2 = k1 + 1;

		while (k2 < end && *k2 < new_key)
		{
			*k1 = *k2;
			k1++;
			k2++;
		}
		*k1 = new_key;

		size_t *sib_keys = sibling->keys;
		end = src->keys + BTREE_MAX_KEYS;
		k1 = src->keys + BTREE_MIN_KEYS;

		while (k1 < end)
		{
			*sib_keys = *k1;
			*k1 = 0;
			sib_keys++;
			k1++;
		}
	}
	else
	{
		median = new_key;

		size_t *sib_keys = sibling->keys;
		size_t *k1 = src->keys + BTREE_MIN_KEYS;
		size_t *end = src->keys + BTREE_MAX_KEYS;

		while (k1 < end)
		{
			*sib_keys = *k1;
			*k1 =  0;
			sib_keys++;
			k1++;
		}
	}
	src->n = BTREE_MIN_KEYS;
	sibling->n = SPLIT_LENGTH;

	if (src->leaf == false)
	{
		BtreeNode **child = src->child + BTREE_MIN_CHILD;
		BtreeNode **end = src->child + BTREE_MAX_CHILD;
		BtreeNode **sib_child = sibling->child;

		while (child < end)
		{
			*sib_child = *child;
			*child = NULL;
			child++;
			sib_child++;
		}
	}

	return sibling;
}
BtreeNode *leaf_merge(BtreeNode *src, size_t pos)
{
	size_t *left_keys = src->child[pos]->keys + BTREE_MIN_KEYS;
	size_t *right_keys = src->child[pos+1]->keys;
	size_t *end = right_keys + MERGE_LENGTH;

	while (right_keys < end)
	{
		*left_keys = *right_keys;
		left_keys++;
		right_keys++;
	}
	src->child[pos]->n = BTREE_MAX_KEYS;

	free(src->child[pos+1]);
	src->child[pos+1] = NULL;
}

void print_array(size_t *arr, size_t len)
{
	size_t i = 0;

	putchar('{');
	while (i < len-1)
	{
		printf("%ld, ", arr[i]);
		i++;
	}
	printf("%ld}\n", arr[i]);
}
void print_node(BtreeNode *src)
{
	if (src == NULL)
	{
		printf("Empty Node.\n");
	}

	char *leaf[] = {"leaf", "internal"};
	size_t *keys = src->keys;
	BtreeNode **child = src->child;

	printf("%s\n  %s\n  %s%ld\n  %s",
			"BtreeNode:", leaf[src->leaf], "length: ", src->n, "keys: {");
	while (keys < src->keys + BTREE_MAX_KEYS - 1)
	{
		printf("%ld, ", *keys);
		keys++;
	}
	printf("%ld}\n", *keys);


	printf("  %s", "child: {");
	while (child < src->child + BTREE_MAX_CHILD - 1)
	{
		printf("%p, ", *child);
		child++;
	}
	printf("%p}\n", *child);

}
void init_dummy_keys(BtreeNode *src)
{
	size_t *keys = src->keys;
	size_t *end = keys + BTREE_MAX_KEYS;
	size_t dummy_value = 10;

	while (keys < end)
	{
		*keys = dummy_value;
		dummy_value += 10;
		keys++;
	}
}
void init_dummy_child(BtreeNode *src)
{
	BtreeNode **child = src->child;
	BtreeNode **end = child + BTREE_MAX_CHILD;
	BtreeNode *dummy_value = (BtreeNode *)0xab;

	while (child < end)
	{
		*child = dummy_value;
		dummy_value += 0xab;
		child++;
	}
}

