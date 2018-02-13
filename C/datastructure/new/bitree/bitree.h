#ifndef BITREE_H

#define BITREE_H
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include <stdbool.h>

#define USE_SUCCESSOR

typedef struct binarytree_node BiTrNode;

int bitr_insert(BiTrNode **src, int new_key);
int bitr_delete(BiTrNode **src, int key_to_del);
BiTrNode *bitr_search(BiTrNode *src, int key_to_find);
void destroy_tree(BiTrNode *root);

void print_tree(BiTrNode *root);

#endif
