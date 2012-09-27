#include <stdbool.h>
#include <stdio.h>

#include "page.h"
#include "btree.h"


/*
@insert
Returns true or false on success/failure (respectively)
=> Node *n is a pointer to a filled-out node struct
=> Page *p is a pointer to a potential target page
The function will iterate over the tree (from the root) until it
finds an appropriate page to put the node

This is the public version which mostly just finds a home for the node
The private version actually does the inserting into the linked list.

For testing purposes, page size and max children are both 5
*/
int insert(node *n, tree *t){
	/*
	if root is empty, make a page
	*/
	if(t->root == NULL){
		page p;
		t->root = &p;
	}
	page *current_page = t->root;

	/*
	insert into page if it is not full (maintain order):

	while not null & new val > current val
		move forward in list
	*/
	insert_into_page

	/*
	if page is full, split it
	the median value goes in the parent
		which may cause a split in the parent
	the left and right go in the children, maintaining order (how?)
	*/
}

/*
@_insert
Private-ish version of insert.
*/
int _insert(node *n, page_node *p){

}

/*
@find
Finds a node within the tree, starting at the root
This is the public-facing wrapper of _find.
In order to perform recursion, it needs to know the actual page_node
Keeping this hidden makes for a simpler interface.
*/
node* find(int needle){

}

/*
@_find
Private version of find. Suitable for recursive operations.
*/
node* _find(page_node *p, int needle){

}