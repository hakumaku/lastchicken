#ifndef AVLTREE_H
#define AVLTREE_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <wchar.h>
#include <locale.h>

typedef struct avltree AVLTree;

#define USE_SUCCESSOR

void avl_insert(AVLTree *src, int new_key);
void avl_delete(AVLTree *src, int key_to_del);
void destroy_tree(AVLTree *src);

void print_tree(AVLTree *src);

#endif
