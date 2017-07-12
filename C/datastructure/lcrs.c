/*
 * Left Child Right Siblings
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	struct node *prnt;
	struct node *left;
	struct node *right;
	int key;
} node_t;

typedef struct {
	node_t *data;
}heap_t;

heap_t *init_heap();
node_t *make_node(int input_key);
void free_heap(node_t *src);
node_t *insert_node(node_t *heap, int key);


int main(void)
{
	return 0;
}
heap_t *init_heap()
{
	heap_t *new = (heap_t *)calloc(1, sizeof(heap_t));
	return new;
}
node_t *make_node(int input_key)
{
	node_t *new = (node_t *)calloc(1, sizeof(node_t));
	new->prnt = NULL;
	new->left = NULL;
	new->right = NULL;
	new->key = input_key;

	return new;
}
void free_heap(node_t *src)
{

}
node_t *insert_node(node_t *heap, int key)
{
	node_t *new = make_node(key);
	node_t *node = heap;
	while(node && node->key > key)
	{
		node = node->left;
	}
	return heap;
}
