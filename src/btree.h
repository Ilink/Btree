#ifndef BTREE_H
#define BTREE_H

#include "page.h"

typedef struct tree_node tree_node;
struct tree_node {
	tree_node *children[50];
	tree_node *parent;
	page_node *pn;
};

#endif