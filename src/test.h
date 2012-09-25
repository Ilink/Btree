#ifndef TEST_H
#define TEST_H

page* make_test_page(int *values);

typedef struct tree_node tree_node;
struct tree_node {
	tree_node[] children;
	tree_node *parent;
	page_node *pn;
};

#endif