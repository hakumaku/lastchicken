#include "bitree.h"

int main(int argc, const char *argv[])
{
	BiTrNode *root = NULL;

	bitr_insert(&root, 16);
	bitr_insert(&root, 8);
	bitr_insert(&root, 24);
	bitr_insert(&root, 4);
	bitr_insert(&root, 12);
	bitr_insert(&root, 20);
	bitr_insert(&root, 28);
	bitr_insert(&root, 2);
	bitr_insert(&root, 6);
	bitr_insert(&root, 10);
	bitr_insert(&root, 14);
	bitr_insert(&root, 18);
	bitr_insert(&root, 22);
	bitr_insert(&root, 26);
	bitr_insert(&root, 30);
	bitr_insert(&root, 1);
	bitr_insert(&root, 3);
	bitr_insert(&root, 5);
	bitr_insert(&root, 7);
	bitr_insert(&root, 9);
	bitr_insert(&root, 11);
	bitr_insert(&root, 13);
	bitr_insert(&root, 15);
	bitr_insert(&root, 17);
	bitr_insert(&root, 19);
	bitr_insert(&root, 21);
	bitr_insert(&root, 23);
	bitr_insert(&root, 25);
	bitr_insert(&root, 27);
	bitr_insert(&root, 29);
	bitr_insert(&root, 31);
	print_tree(root);

	wprintf(L"Deleting a node(16) with full child.\n");
	bitr_delete(&root, 16);
	print_tree(root);

	wprintf(L"Deleting a leaf node(11).\n");
	bitr_delete(&root, 11);
	print_tree(root);

	wprintf(L"Deleting a leaf node(21).\n");
	bitr_delete(&root, 21);
	print_tree(root);

	wprintf(L"Deleting a node(10) with left child.\n");
	bitr_delete(&root, 10);
	print_tree(root);

	wprintf(L"Deleting a node(22) with right child.\n");
	bitr_delete(&root, 22);
	print_tree(root);

	wprintf(L"No key(60) found.\n");
	bitr_delete(&root, 60);
	print_tree(root);

	destroy_tree(root);

	return 0;
}

