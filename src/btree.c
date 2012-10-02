#include <stdbool.h>
#include <stdio.h>

#include "page.h"
#include "btree.h"

/*
@prepare_tree
This is helpful because the btree pages must start
with a sentinel node representing the lowest
value in the tree.
*/
tree* prepare_tree(tree *t){
	// tree* t = (tree*) malloc(sizeof(tree));
	page* p = (page*) mallc(sizeof(page));
	t->root = p;
	node* n = (node*) malloc(sizeof(node));
	n->val = NULL;
	insert_into_page(p, n);
	return t;
}

/*
@insert
Returns true or false on success/failure (respectively)
=> Node *n is a pointer to a filled-out node struct
=> Page *p is a pointer to a potential target page
The function will iterate over the tree (from the root) until it
finds an appropriate page to put the node

This is the public version which mostly just finds a home for the node
The 'private' version actually does the inserting/searching/splitting/hard work.

For testing purposes, page size and max children are both 5
*/
int insert(node *n, tree *t){
	if(t->root == NULL){
		prepare_tree(t);
	}
	_insert(n, t->root, t);
}

/*
@_insert
Private-ish version of insert.
*/
int _insert(node *n, page_node *p, tree *t){
	/*
	
	*/
}

page_node* search_in_page(page* p, int val){
	page_node *iter = p->head;
	/*
	look for value in this page
	if the value is not found, look in child
		-> visit the child of the first node which is larger than search value
	*/
}

/*
@find
Finds a node within the tree, starting at the root
This is the public-facing wrapper of _find.
In order to perform recursion, it needs to know the actual page_node
Keeping the recursive-centric part hidden makes for a simpler interface.
See '_find'
*/
node* find(int needle){

}

/*
@_find
Private version of find. Suitable for recursive operations.
*/
node* _find(page_node *p, int needle){

}