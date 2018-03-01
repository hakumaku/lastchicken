#include "avltree.h"

int main(int argc, const char *argv[])
{
	AvlTree *root = init_avltree();

	for (int i = 1; i < 32; i++)
	{
		avl_insert(root, i);
		avl_print(root);
	}


	return 0;
}

