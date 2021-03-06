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
	page* p = make_page();
	printf("making page: \n");
	print_page(p);
	t->root = p;
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

int belongs_on_sent(int val, page* p){
	// printf("%i < %i ?\n", val, p->start->next);
	if(p->start != NULL){
		return val < p->start->next->n->val;
	} 
	return 0;
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
// this could be sped up with a skip list instead of a linkedlist
int search_and_insert(tree *t, page* p, node *n){
	page_node *iter = p->start;

	// this pretty much happens in a new tree w/ an empty root
	if(only_sentinel(p) || p->num_page_nodes == 1){
		printf("Nothing but sentinel\n");
		insert_into_page(p, n);
		print_page(p);
		return 1;
	}

	if(belongs_on_sent(n->val, p)){ // value belongs on sent
		printf("goes on sent for page\t");
		print_page(p);
	}

	page *current_page = p;
	while(iter != NULL){
		// Found spot for value: x < needle < y
		if(inbetween(n->val, iter) || belongs_on_sent(n->val, current_page)){
			if(iter->child != NULL){
				// Continue down the tree until we arrive at a leaf

				printf("visiting the child of %i on page: \n", iter->n->val);
				print_page(iter->child);
				current_page = iter->child;
				iter = iter->child->start;
			} else {
				// Insertion into a leaf
				// Only a leaf will have no children

				printf("inserting %i into page\n", n->val);
				insert_node_into_page_sorted(current_page, n);
				print_page(current_page);
				
				if(page_is_full(current_page)){
					printf("page full\n");
					recursive_split(t, current_page, U);
					print_tree(t);
				} else {
					printf("page not full, liar: %i\n", current_page->num_page_nodes);
				}
				return 1; // we are done searching since we reached the leaf
			}
		} else {
			iter = iter->next;
		}		
	}
}

int is_overflow(page *p, int max_size){
	return p->num_page_nodes >= max_size;
}

/*
@insert_sentinel_child
Should probably go within page.c
I suppose be careful here, since it overwrites the 
current child
*/
void insert_sentinel_child(page *p, page *child){
	p->start->child = child;
	child->parent_page = p;
	child->parent = p->start;
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

		printf("is root: %i\n", p->parent == NULL);
		printf("is root: %i\n", p->parent_page == NULL);

		printf("segfault here\n");
		middle = split_page(p);

		// We are at the root
		if(p->parent_page == NULL){
			printf("splitting the root\n");
			page *new_root = make_page();

			t->root = new_root;
			insert_sentinel_child(new_root, p);
			insert_pn_into_page(new_root, middle);
		} else { // at a leaf
			printf("splitting a leaf\n");
			printf("p->parent_page %i\n", p->parent_page);
			printf("parent null: %i\n", p->parent_page == NULL); // looks like p->parent_page is null
			print_page(p->parent_page);
			insert_pnode_into_page_sorted(p->parent_page, middle); // p->parent is a page_node, so is middle
			recursive_split(t, p->parent_page, max_size);
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

// BFS search
void print_tree(tree* t){
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
	printf("[");
	while(iter != NULL){
		printf("%i,", iter->n->val);
		iter = iter->next;
	}
	printf("]\n");
}
