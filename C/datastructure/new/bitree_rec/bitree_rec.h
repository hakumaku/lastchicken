#ifndef BITREE_REC_H

#define BITREE_REC_H
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>

#define USE_SUCCESSOR

typedef struct binarytree_node BiTrNode;

BiTrNode *bitr_insert(BiTrNode *src, int new_key);
BiTrNode *bitr_delete(BiTrNode *src, int key_to_del);
BiTrNode *bitr_search(BiTrNode *src, int key_to_find);
void destroy_tree(BiTrNode *root);

void print_tree(BiTrNode *root);

#endif
