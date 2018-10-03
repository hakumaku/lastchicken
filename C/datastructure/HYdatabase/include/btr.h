#ifndef __BTR_H__
#define __BTR_H__

#include <stddef.h>

struct btr_header;
struct btr_node;
struct btr_leaf;
struct record;

struct btr_header *btr_init(size_t order);
/*
 * insert(public)
 *		-> insert_into_leaf (static)
 *			-> insert_node
 *			-> insert_node_after_splitting
 *		-> insert_into_leaf_after_splitting (static)
 *			-> insert_node
 *			-> insert_node_after_splitting
 */
/* Need return? */
struct btr_node *btr_insert(struct btr_header *tree, struct record *data);

#endif /* __BTR_H__ */

