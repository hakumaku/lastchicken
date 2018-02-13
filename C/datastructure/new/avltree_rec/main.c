#include "avltree_rec.h"

int main(int argc, const char *argv[])
{
	AVLNode *root = NULL;

	for (int i = 1; i < 32; i++)
	{
		avl_insert(&root, i);
	}

	for (int i = 1; i < 32; i++)
	{
		avl_delete(&root, i);
		print_tree(root);
	}

	destroy_tree(root);

	return 0;
}

