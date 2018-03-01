#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <wchar.h>
#include <locale.h>

typedef struct binary_tree BinTree;

BinTree *init_bintree(void);
void bin_insert(BinTree *src, int k);
void bin_delete(BinTree *src, int k);
void bin_print(BinTree *src);
void bin_destroy(BinTree *src);

