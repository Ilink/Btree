#include <stdbool.h>

#include "page.h"

/*
@insert
Returns true or false on success/failure (respectively)
=> Node *n is a pointer to a filled-out node struct
=> Page *p is a pointer to a potential target page
The function will iterate over the tree (from the root) until it
finds an appropriate page to put the node

This is the public version which mostly just finds a home for the node
The private version actually does the inserting into the linked list.
*/
int insert(node *n){

}

/*
@_insert
Private-ish version of insert.
*/
int _insert(page_node *p, node *n){

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