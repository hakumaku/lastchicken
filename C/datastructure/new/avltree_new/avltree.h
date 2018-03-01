#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include <stdbool.h>

typedef struct avl_tree AvlTree;

AvlTree *init_avltree();
void avl_insert(AvlTree *src, int k);
void avl_delete(AvlTree *src, int k);
void avl_destroy(AvlTree *src);
void avl_print(AvlTree *src);

