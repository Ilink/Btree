#ifndef BTREE_H
#define BTREE_H

#include "page.h"

typedef struct {
	page *root;
	int height; // todo: set this value
} tree;

// Forward Declarations
int insert(node *n, tree *t);
node* find(int needle);
tree* prepare_tree();

#endif