#include "avltree.h"

#define LOOP_NUM	7

int main(int argc, const char *argv[])
{
	AvlTree *root = init_avltree();

	for (int i = 1; i < LOOP_NUM; i++)
	{
		avl_insert(root, i);
		avl_print(root);
	}
	wprintf(L"Deletion...\n");

	/*
	avl_insert(root, 80);
	avl_print(root);
	avl_insert(root, 60);
	avl_print(root);
	avl_insert(root, 40);
	avl_print(root);
	avl_insert(root, 20);
	avl_print(root);
	avl_insert(root, 10);
	avl_print(root);
	avl_insert(root, 45);
	avl_print(root);
	*/

	for (int i = 1; i < LOOP_NUM; i++)
	{
		avl_delete(root, i);
		avl_print(root);
	}

	avl_destroy(root);

	return 0;
}

