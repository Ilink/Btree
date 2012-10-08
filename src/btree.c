#include <stdbool.h>
#include <stdio.h>
#include <glib.h>

#include "page.h"
#include "btree.h"

/*
@prepare_tree
This is helpful because the btree pages must start
with a sentinel node representing the lowest
value in the tree.
*/
tree* prepare_tree(tree *t){
	// page* p = (page*) malloc(sizeof(page));
	page* p = make_page();
	printf("making page: \n");
	print_page(p);
	t->root = p;
	// node* n = (node*) malloc(sizeof(node));
	// n->val = NULL;
	// insert_into_page(t->root, n);
	return t;
}

int inbetween(int val, page_node* iter){
	if(iter->next != NULL){
		return val > iter->n->val 
			&& val < iter->next->n->val;
	} else {
		return val > iter->n->val && iter->next == NULL;
	}
	return 0;

	// return((n->val > iter->n->val && iter->next != NULL && n->val < iter->next->n->val)
	// 	|| (n->val > iter->n->val && iter->next == NULL))
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
	search_and_insert(t, t->root, n);
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
int search_and_insert(tree *t, page* p, node *n){
	page_node *iter = p->start;

	// this pretty much happens in a new tree w/ an empty root
	if(only_sentinel(p) || p->num_page_nodes == 1){ // broken, this isnt ever firing
		printf("Nothing but sentinel\n");
		insert_into_page(p, n);
		print_page(p);
		return 1;
	}

	page *current_page = p;
	while(iter != NULL){
		// Found spot for value: x < needle < y
		// if(n->val > iter->n->val && iter->next != NULL && n->val < iter->next->n->val){
		// if((n->val > iter->n->val && iter->next != NULL && n->val < iter->next->n->val)
		// 	|| (n->val > iter->n->val && iter->next == NULL)){

		printf("trying again\n");
		// if(inbetween(n->val, iter->n->val, iter->next->n->val)){
		if(inbetween(n->val, iter)){
			printf("test\n");
			print_page(current_page);
			printf("test after\n");
			if(iter == NULL){
				printf("iter = null\n");
			} else {
				printf("iter != null\n");
			}
			printf("after\n");
			if(iter->child != NULL){
				// print_page(iter->child);
				// Continue down the tree until we arrive at a leaf
				// printf("visiting the child of %i\n", iter->n->val);
				iter = iter->child->end;
				current_page = iter->child;
			} else {
				// Insertion into a leaf
				// Only a leaf will have no children

				// this is a bit less efficient because it iterates over the list instead of just re-arranging the pointers here
				// todo: re-arrange pointers either by function or manually
				printf("inserting at leaf\n");
				insert_node_into_page_sorted(current_page, n);
				print_page(current_page);
				iter = iter->next;

				if(page_is_full(current_page)){
					printf("page full\n");
					recursive_split(t, current_page, U);
					print_tree_bfs(t);
				}
			}
		}
		
		iter = iter->next;
	}
}

int is_overflow(page *p, int max_size){
	return p->num_page_nodes > max_size;
}

/*
@insert_sentinel_child
Should probably go within page.c
I suppose be careful here, since it overwrites the 
current child
*/
void insert_sentinel_child(page *p, page *child){
	p->start->child = child;
}


/*
Let's make this the only place where we decide
whether or not to split the page based upon max size.

@recursive_split
Begins at a specific page and splits the page.
Takes the middle node from the split result and adds
it to the parent page.
If the parent overflows, the operation continues recursively.
If the root must be split, a new root node is created.
The sentinel node within the new root points to the orphan nodes.
The next slot belongs to the middle split result.

[*][Middle]
 |	     \
[1,2,3]  [4,5,6]
*/
int recursive_split(tree *t, page *p, int max_size){
	if(page_is_full(p)){
		printf("starting split\n");
		page_node *middle;
		/*
		page is root (if parent is null)
			=> split and make new root
		page isn't root (has parent)
			=> split and check if parent has overflowed
		*/

		middle = split_page(p);
		// check if parent has or will overflow

		// We are at the root
		if(p->parent == NULL){
			printf("splitting the root\n");
			// page *new_root = (page*) malloc(sizeof(page));
			page *new_root = make_page();

			t->root = new_root;
			/*
				middle node inserted into new root
				set the remaining former page as the sentinel's child
			*/
			insert_sentinel_child(new_root, p);
			insert_pn_into_page(new_root, middle);
		} else { // at a leaf
			printf("splitting a leaf\n");
			insert_pnode_into_page_sorted(p->parent, middle);
			recursive_split(t, p->parent, max_size);
		}
		printf("done splitting\n");
	} else {
		printf("done splitting\n");
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

void _print_tree(page *p){
	page_node *iter = p->start;
	
	while(iter != NULL){
		print_page(p);
		if(iter->child != NULL){
			_print_tree(iter->child);
		}
		iter = iter->next;
	}
}

void print_tree(tree* t){
	page_node *iter = t->root; // skip the sentinel

	_print_tree(t->root);

	// printf("Root:");
	// print_page(iter);
	// // printf("\n");

	// iter = t->root->start->child;

	// printf("Sent child:");
	// print_page(iter);


	// iter = t->root->start->next->child;
	// print_page(iter);

	// iter = t->root->start->child->start->child;
	// print_page(iter);

}

// BFS search
void print_tree_bfs(tree* t){
	printf("\n====Tree===\n");
	int num_per_level = 1;

	int remaining = 0;
	GQueue* queue = g_queue_new();
	g_queue_push_tail(queue, (gpointer) t->root);
	
	page* current_page;
	while(current_page = (page*) g_queue_pop_head(queue)){
		num_per_level--;

		page_node* iter = current_page->start;
		printf("\n[");
		
		while(iter != NULL){
			printf("%i,", iter->n->val);
			
			if(iter->child != NULL){
				num_per_level++;
				g_queue_push_tail(queue, (gpointer) iter->child);
			}
			
			iter = iter->next;
		}
		remaining = num_per_level;

		printf("]");
	}
	printf("\n\n===========\n");
}


void print_page(page* p){
	page_node *iter = p->start;
	// printf("number of nodes: %i\n", p->num_page_nodes);
	printf("[");
	while(iter != NULL){
		printf("%i,", iter->n->val);
		iter = iter->next;
	}
	printf("]\n");
}
