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
	n->val = 555555;

	// random val
	node* n2 = (node*) malloc(sizeof(node));
	n2->val = 123;

	insert_into_page(t->root, n);
	insert_into_page(t->root, n2);

	printf("sentinel: %i and next: %i\n", t->root->start->n->val, t->root->start->next->n->val);
	return t;
}

/*
@insert
Returns true or false on success/failure (respectively)
=> Node *n is a pointer to a filled-out node struct
=> Page *p is a pointer to a potential target page
The function will iterate over the tree (from the root) until it
finds an appropriate page to put the node

For testing purposes, page size and max children are both 5
*/
int insert(node *n, tree *t){
	if(t->root == NULL){
		prepare_tree(t);
	}
	search_and_insert(t->root, n);
	// _insert(n, t->root, t);
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
	page_node *iter = p->start;
	// this pretty much happens in a new tree w/ an empty root
	if(is_sentinel(iter)){ // todo: does this need a leaf check?
		printf("Nothing but sentinel\n");
		// we only have a sentinel (representing smaller than all values)
		insert_into_page(p, n);
		printf("val inserted into page: %i\n",n->val);
		return 1;
	}

	// printf("comparing val(%i) with iter (%i) and iter, next(%i)\n", 
	// 		n->val, iter->n->val, iter->next->n->val);

	while(iter != NULL){
		// Found spot for value: x < needle < y
		// printf("comparing val(%i) with iter (%i) and iter, next(%i)\n", 
		// 	n->val, iter->n->val, iter->next->n->val);
		if(n->val > iter->n->val && iter->next != NULL && n->val < iter->next->n->val){
			if(iter->child != NULL){
				// Continue down the tree until we arrive at a leaf
				printf("visiting the child");
				iter = iter->child->end;
			} else {
				// Insertion into a leaf
				// Only a leaf will have no children

				// this is a bit less efficient because it iterates over the list instead of just re-arranging the pointers here
				// todo: re-arrange pointers either by function or manually
				insert_into_page(p, n);
				iter = iter->next;

				// if(page_is_full(page *p)){
				if(page_is_full(p)){
					printf("page full\n");
					// perform recursive split operation
				} else {
					printf("page not full\n");
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