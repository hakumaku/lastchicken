#ifndef AVLTREE_H
#define AVLTREE_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <wchar.h>
#include <locale.h>

typedef struct avltree_node AVLNode;

#define USE_SUCCESSOR

void avl_insert(AVLNode **src, int new_key);
void avl_delete(AVLNode **src, int key_to_del);
void destroy_tree(AVLNode *root);

void print_tree(AVLNode *src);

#endif
