#include "bintree.h"

int main(int argc, const char *argv[])
{
	BinTree *tree = init_bintree();

	bin_insert(tree, 16);
	bin_insert(tree, 8);
	bin_insert(tree, 24);
	bin_insert(tree, 4);
	bin_insert(tree, 12);
	bin_insert(tree, 20);
	bin_insert(tree, 28);
	bin_insert(tree, 2);
	bin_insert(tree, 6);
	bin_insert(tree, 10);
	bin_insert(tree, 14);
	bin_insert(tree, 18);
	bin_insert(tree, 22);
	bin_insert(tree, 26);
	bin_insert(tree, 30);
	bin_insert(tree, 1);
	bin_insert(tree, 3);
	bin_insert(tree, 5);
	bin_insert(tree, 7);
	bin_insert(tree, 9);
	bin_insert(tree, 11);
	bin_insert(tree, 13);
	bin_insert(tree, 15);
	bin_insert(tree, 17);
	bin_insert(tree, 19);
	bin_insert(tree, 21);
	bin_insert(tree, 23);
	bin_insert(tree, 25);
	bin_insert(tree, 27);
	bin_insert(tree, 29);
	bin_insert(tree, 31);
	bin_print(tree);

	wprintf(L"Deleting a node(16) with full child.\n");
	bin_delete(tree, 16);
	bin_print(tree);

	wprintf(L"Deleting a leaf node(11).\n");
	bin_delete(tree, 11);
	bin_print(tree);

	wprintf(L"Deleting a leaf node(21).\n");
	bin_delete(tree, 21);
	bin_print(tree);

	wprintf(L"Deleting a node(10) with left child.\n");
	bin_delete(tree, 10);
	bin_print(tree);

	wprintf(L"Deleting a node(22) with right child.\n");
	bin_delete(tree, 22);
	bin_print(tree);

	wprintf(L"No key(60) found.\n");
	bin_delete(tree, 60);
	bin_print(tree);

	wprintf(L"Deleting 16.\n");
	bin_delete(tree, 16);
	bin_print(tree);
	wprintf(L"Deleting 8.\n");
	bin_delete(tree, 8);
	bin_print(tree);
	wprintf(L"Deleting 24.\n");
	bin_delete(tree, 24);
	bin_print(tree);
	wprintf(L"Deleting 4.\n");
	bin_delete(tree, 4);
	bin_print(tree);
	wprintf(L"Deleting 12.\n");
	bin_delete(tree, 12);
	bin_print(tree);
	wprintf(L"Deleting 20.\n");
	bin_delete(tree, 20);
	bin_print(tree);
	wprintf(L"Deleting 28.\n");
	bin_delete(tree, 28);
	bin_print(tree);
	wprintf(L"Deleting 2.\n");
	bin_delete(tree, 2);
	bin_print(tree);
	wprintf(L"Deleting 6.\n");
	bin_delete(tree, 6);
	bin_print(tree);
	wprintf(L"Deleting 10.\n");
	bin_delete(tree, 10);
	bin_print(tree);
	wprintf(L"Deleting 14.\n");
	bin_delete(tree, 14);
	bin_print(tree);
	wprintf(L"Deleting 18.\n");
	bin_delete(tree, 18);
	bin_print(tree);
	wprintf(L"Deleting 22.\n");
	bin_delete(tree, 22);
	bin_print(tree);
	wprintf(L"Deleting 26.\n");
	bin_delete(tree, 26);
	bin_print(tree);
	wprintf(L"Deleting 30.\n");
	bin_delete(tree, 30);
	bin_print(tree);
	wprintf(L"Deleting 1.\n");
	bin_delete(tree, 1);
	bin_print(tree);
	wprintf(L"Deleting 3.\n");
	bin_delete(tree, 3);
	bin_print(tree);
	wprintf(L"Deleting 5.\n");
	bin_delete(tree, 5);
	bin_print(tree);
	wprintf(L"Deleting 7.\n");
	bin_delete(tree, 7);
	bin_print(tree);
	wprintf(L"Deleting 9.\n");
	bin_delete(tree, 9);
	bin_print(tree);
	wprintf(L"Deleting 11.\n");
	bin_delete(tree, 11);
	bin_print(tree);
	wprintf(L"Deleting 13.\n");
	bin_delete(tree, 13);
	bin_print(tree);
	wprintf(L"Deleting 15.\n");
	bin_delete(tree, 15);
	bin_print(tree);
	wprintf(L"Deleting 17.\n");
	bin_delete(tree, 17);
	bin_print(tree);
	wprintf(L"Deleting 19.\n");
	bin_delete(tree, 19);
	bin_print(tree);
	wprintf(L"Deleting 21.\n");
	bin_delete(tree, 21);
	bin_print(tree);
	wprintf(L"Deleting 23.\n");
	bin_delete(tree, 23);
	bin_print(tree);
	wprintf(L"Deleting 25.\n");
	bin_delete(tree, 25);
	bin_print(tree);
	wprintf(L"Deleting 27.\n");
	bin_delete(tree, 27);
	bin_print(tree);
	wprintf(L"Deleting 29.\n");
	bin_delete(tree, 29);
	bin_print(tree);
	wprintf(L"Deleting 31.\n");
	bin_delete(tree, 31);
	bin_print(tree);
	/*
	*/
	bin_destroy(tree);

	return 0;
}

