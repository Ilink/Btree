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
	page* p = (page*) malloc(sizeof(page));
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

/*
look for value in this page
if the value is not found, look in child
	-> visit the child of the first node which is larger than search value

I think that a page without a child is a leaf. We're never going to make a
new leaf level without performing split operations
so if you a find a value in the page that is like:
	3,4,6
	insert 5
	look for inbetween spot
		(found between 4 and 6)
	look at 4's children
	if 4 has no children, value is not found
	and we are close enough that we can insert at this page

*/
// todo: Let's make this a binary search later!
int search_and_insert(page* p, node *n){
	page_node *iter = p->head;
	// this pretty much happens in a new tree w/ an empty root
	if(iter->next == NULL && iter->child == NULL){ // todo: does this need a leaf check?
		// we only have a sentinel (representing smaller than all values)
		insert_into_page(p, n);
		return 1;
	}

	while(iter != NULL){
		// Found spot for value: x < needle < y
		if(n->val > iter->n->val && iter->next != NULL && n->val < iter->next){
			if(iter->child != NULL){
				iter = iter->child->head;
				break;
			} else {
				// Insertion because the value was not found in tree
				// this is a bit less efficient because it iterates over the list instead of just re-arranging the pointers here
				// todo: re-arrange pointers either by function or manually
				insert_into_page(p, n);
				// if(page_is_full(page *p)){
				if(0){
					// perform recursive split operation
				}
			}
		} else if(iter->n->val == n->val){
			return 0; // btrees do not allow repeated values
		} else {
			iter = iter->next;
		}
	}
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