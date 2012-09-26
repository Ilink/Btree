#ifndef BTREE_H
#define BTREE_H

#include "page.h"

typedef struct tree_node tree_node;
typedef const int U = 5; // this size is temporary
struct tree_node {
	page *child;
	page *parent;
};

typedef struct {
	page *root;
} tree;

// Forward Declarations
int insert(node *n, tree *t);
node* find(int needle);

#endif