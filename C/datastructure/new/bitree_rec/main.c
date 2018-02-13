#include <stdio.h>
#include "bitree_rec.h"

int main(int argc, const char *argv[])
{
	BiTrNode *root = NULL;

	root = bitr_insert(root, 16);
	root = bitr_insert(root, 8);
	root = bitr_insert(root, 24);
	root = bitr_insert(root, 4);
	root = bitr_insert(root, 12);
	root = bitr_insert(root, 20);
	root = bitr_insert(root, 28);
	root = bitr_insert(root, 2);
	root = bitr_insert(root, 6);
	root = bitr_insert(root, 10);
	root = bitr_insert(root, 14);
	root = bitr_insert(root, 18);
	root = bitr_insert(root, 22);
	root = bitr_insert(root, 26);
	root = bitr_insert(root, 30);
	root = bitr_insert(root, 1);
	root = bitr_insert(root, 3);
	root = bitr_insert(root, 5);
	root = bitr_insert(root, 7);
	root = bitr_insert(root, 9);
	root = bitr_insert(root, 11);
	root = bitr_insert(root, 13);
	root = bitr_insert(root, 15);
	root = bitr_insert(root, 17);
	root = bitr_insert(root, 19);
	root = bitr_insert(root, 21);
	root = bitr_insert(root, 23);
	root = bitr_insert(root, 25);
	root = bitr_insert(root, 27);
	root = bitr_insert(root, 29);
	root = bitr_insert(root, 31);
	print_tree(root);

	wprintf(L"Deleting a node(16) with full child.\n");
	root = bitr_delete(root, 16);
	print_tree(root);

	wprintf(L"Deleting a leaf node(11).\n");
	root = bitr_delete(root, 11);
	print_tree(root);

	wprintf(L"Deleting a leaf node(21).\n");
	root = bitr_delete(root, 21);
	print_tree(root);

	wprintf(L"Deleting a node(10) with left child.\n");
	root = bitr_delete(root, 10);
	print_tree(root);

	wprintf(L"Deleting a node(22) with right child.\n");
	root = bitr_delete(root, 22);
	print_tree(root);

	wprintf(L"No key(60) found.\n");
	root = bitr_delete(root, 60);
	print_tree(root);

	destroy_tree(root);

	return 0;
}

