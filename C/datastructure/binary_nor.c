/*
 * Non recursive Binary tree
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node *left;
	struct node *right;
}node_t;

#define STACK_SIZE	255
typedef struct stack {
	node_t *node_ptr[STACK_SIZE];
	unsigned size;
}stack_t;

/* For print_binary_tree */
typedef struct qdata {
	node_t *node_ptr;
	struct qdata *next;
}qdata_t;

typedef struct queue {
	qdata_t *head;
	qdata_t *tail;
}queue_t;

node_t *make_node(int value);
void free_binary_tree(node_t *src);
void insert_key(node_t *root, int key);
void delete_key(node_t *root, int key);
node_t *search_key(node_t *src, int key);
node_t *search_prev_min(node_t *src);
node_t *search_prev_max(node_t *src);


/* Printing set */
void print_binary_tree(node_t *root);
qdata_t *make_qdata(node_t *src);
void enqueue(queue_t *src, node_t *data);
node_t *dequeue(queue_t *src);

int main(void)
{
	node_t *root = make_node(50);
	insert_key(root, 30);
	insert_key(root, 80);
	insert_key(root, 15);
	insert_key(root, 45);
	insert_key(root, 65);
	insert_key(root, 95);
	insert_key(root, 7);
	insert_key(root, 18);
	insert_key(root, 37);
	insert_key(root, 48);
	insert_key(root, 57);
	insert_key(root, 70);
	insert_key(root, 85);
	insert_key(root, 100);

	print_binary_tree(root);

	delete_key(root, 80);
	print_binary_tree(root);

	delete_key(root, 95);
	print_binary_tree(root);

	delete_key(root, 37);
	print_binary_tree(root);

	free_binary_tree(root);

	return 0;
}

node_t *make_node(int value)
{
	node_t *new = (node_t *)calloc(1, sizeof(node_t));
	new->left = NULL;
	new->right = NULL;
	new->key = value;

	return new;
}
void free_binary_tree(node_t *src)
{
	if(src)
	{
		free_binary_tree(src->left);
		free_binary_tree(src->right);
		free(src);
	}
}
node_t *search_key(node_t *src, int key)
{
	node_t *target = src;
	node_t **next = NULL;

	while(target && target->key != key)
	{
		next = &(target->left);
		if(target->key < key)
			next = &(target->right);

		target = *next;
	}
	/*
	 * if target == NULL, it returns NULL
	 * otherwise it has found one, returns the node.
	 */
	return target;
}
node_t *search_prev_min(node_t *src)
{
	node_t *prev = src;
	while(src->left)
	{
		prev = src;
		src = src->left;
	}
	return prev;
}
node_t *search_prev_max(node_t *src)
{
	node_t *prev = src;
	while(src->right)
	{
		prev = src;
		src = src->right;
	}
	return prev;
}
/* Assumes the root is not empty. */
void insert_key(node_t *root, int key)
{
	node_t *temp = root;
	node_t **next = NULL;

	while(temp)
	{
		next = &(temp->left);
		if(temp->key < key)
			next = &(temp->right);

		temp = *next;
	}
	*next = make_node(key);
}
void delete_key(node_t *root, int key)
{
	node_t *src = root;
	node_t **next = NULL;

	while(src && src->key != key)
	{
		next = &(src->left);
		if(src->key < key)
			next = &(src->right);

		src = *next;
	}
	/* There is no matching key */
	if(!src)
		return;

	int mask1 = src->left ? 2 : 0;
	int mask2 = src->right ? 1 : 0;
	int node_type = mask1 | mask2;
	node_t *temp = src;
	node_t *prev = NULL;

	switch (node_type)
	{
		/* When it is a leaf node. */
		case 0:
			*next = NULL;
			break;
		/* When it has a right child node only. */
		case 1:
			*next = temp->right;
			break;
		/* When it has a left child node only. */
		case 2:
			*next = temp->left;
			break;
		/* When it has two nodes. */
		case 3:
			/*
			 * There are two strategies:
			 * one is to find min value in the right,
			 * the other is to find max value in the left.
			 */
			/* 'prev' can be a leaf node. */
			// prev = search_prev_min(temp->right);
			// temp = prev;
			// if(prev->left)
			// {
			// 	temp = prev->left;
			// 	prev->left = NULL;
			// }
			// else
			// 	src->right = NULL;
			prev = search_prev_max(temp->left);
			temp = prev;
			if(prev->right)
			{
				temp = prev->right;
				prev->right = NULL;
			}
			else
				src->left = NULL;
			/*
			 * It actually assigns a suitable key,
			 * and deletes another node.
			 */
			src->key = temp->key;

			break;
	}
	free(temp);

}

#define SELECT(xor,a,b) (queue_t*)((unsigned long)(xor) ^ (unsigned long)(a) ^ (unsigned long)(b))
void print_binary_tree(node_t *root)
{
	/* Enqueue & Dequeue nodes to print */
	queue_t line1 = { NULL, NULL };
	queue_t line2 = { NULL, NULL };
	enqueue(&line1, root);
	/* While neither line1 nor line2 is empty. */
	while(line1.head || line2.head)
	{
		queue_t *current_line = line1.head ? &line1 : &line2;
		queue_t *next_line = SELECT(current_line,&line1,&line2);

		/* While current_line is not empty. */
		while(current_line->head)
		{
			node_t *target = dequeue(current_line);

			if(target->left)
				enqueue(next_line, target->left);
			if(target->right)
				enqueue(next_line, target->right);

			printf("%d ", target->key);
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
