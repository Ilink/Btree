#ifndef BTREE_H
#define BTREE_H

#include "page.h"

const int U = 5; // this size is temporary

typedef struct {
	page *root;
} tree;

// Forward Declarations
int insert(node *n, tree *t);
node* find(int needle);

#endif