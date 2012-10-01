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

	int insert_successful = insert_into_page_sorted(current_page, n);

	if(insert_successful){
		return 1;
	} else { // page is full
		page_node* middle = split_page(p);
		
		/*
		insert new node into parent
		check overflow
		recurse if overflow
		else return
		*/
	}

	/*
	if page is not full, call insert_into_page_sorted
		-> that function automatically checks if page is full
	if page is a leaf, split the page
	if page is not a leaf, look for the first value greater than the new value
		-> visit that node's children and repeat above steps

	i guess that means this is a recursive operation
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