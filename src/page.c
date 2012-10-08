#include "page.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const int U = 6; // this size is temporary

/*
This is unused for now.
It's too complex for what I have now

In order to specify the binary files, I would need
to specify where they live. Easier if I do not have to do that yet
*/
page_node* load_page(){

}

page_node* make_page_node(){
	page_node *new_page_node = (page_node*) malloc(sizeof (page_node));
	new_page_node->n = NULL;
	new_page_node->next = NULL;
	new_page_node->prev = NULL;
	new_page_node->child = NULL;
	return new_page_node;
}

/*
@insert_into_page
Inserts a node (n) after the page (p)
Returns true / false
*/
int insert_into_page(page *p, node *n){
	page_node *new_page_node = make_page_node();
	new_page_node->n = n;

	if(p->start == NULL && p->end == NULL){
		// printf("empty list\n");
		p->start = new_page_node;
	} else if(p->end == NULL){
		// printf("no end\n");
		p->start->next = new_page_node;
		p->end = new_page_node;
		new_page_node->prev = p->start;
	} else {
		// printf("list has end and start\n");
		p->end->next = new_page_node;
		new_page_node->next = NULL;
		new_page_node->prev = p->end;
		p->end = new_page_node;
	}
	
	p->num_page_nodes++;
	return 1;
}

/*
@insert_pn_into_page
Inserts a page node into the page. Unsorted.
Returns true / false
*/
int insert_pn_into_page(page *p, page_node *pn){
	pn->next = NULL;
	pn->prev = NULL;
	if(pn->child != NULL){
		printf("assigning parent page\n");
		pn->child->parent_page = p;
	} else {
		printf("no child page\n");
	}

	if(p->start == NULL && p->end == NULL){
		// printf("empty list\n");
		p->start = pn;
	} else if(p->end == NULL){
		// printf("no end\n");
		p->start->next = pn;
		p->end = pn;
		pn->prev = p->start;
	} else {
		// printf("list has end and start\n");
		p->end->next = pn;
		pn->next = NULL;
		pn->prev = p->end;
		p->end = pn;
	}
	
	p->num_page_nodes++;
	return 1;
}

/*
@insert_node_into_page_sorted
Inserts a node into a page, maintaining ascending order
All b-tree nodes are arranged this way.

This might have some duplicate code from insert_into_page
but it shouldn't really be a big deal since it's all pretty 
standard linked-list type stuff.

This needs to be a binary search instead.
*/
int insert_node_into_page_sorted(page *p, node *n){
	page_node *new_page_node = make_page_node();
	new_page_node->n = n;
	new_page_node->next = NULL;
	new_page_node->prev = NULL;

	int insert_successful = insert_pnode_into_page_sorted(p, new_page_node);
	return insert_successful;
}

int insert_pnode_into_page_sorted(page *p, page_node *new_page_node){
	if(new_page_node->child != NULL){
		new_page_node->child->parent_page = p;
	}
	if(p->start == NULL && p->end == NULL){
		printf("seg1\n");

		// printf("empty list\n");
		p->start = new_page_node;
	} else if(p->end == NULL){
		printf("seg1\n");
		// printf("no end\n");
		if(p->start->n->val < new_page_node->n->val){
			// printf("start < val");
			p->end = new_page_node;
		} else { // swap end and start
			// printf("val < start: val is new start!");
			p->end = p->start;
			p->start = new_page_node;
		}
		p->start->next = p->end;
		p->end->prev = p->start;
	} else { // insert in order; end and start are all setup
		printf("seg2\n");
		// todo: is this the most efficient way? could i use binary search?	
		page_node *iter = p->start;
		for(int i = 0; iter != NULL; i++) {
			// printf("iter (%i) val: %i\n", i, iter->n->val);
			if(new_page_node->n->val < iter->n->val){
				if(iter->prev == NULL){ // we're at the start
					// printf("insertng at start\n");
					iter->prev = new_page_node;
					new_page_node->next = iter;
					p->start = new_page_node;
				} else { // we're in the middle-ish
					// printf("inserting in middle-ish\n");
					iter->prev->next = new_page_node;
					new_page_node->prev = iter->prev;
					new_page_node->next = iter;
					iter->prev = new_page_node;
				}
				break;
			}
			iter = iter->next;
		}
		// The value is larger than all the values in the list
		// Therefore, we must insert after the last node
		if(iter == NULL){
			// printf("inserting at end\n");
			p->end->next = new_page_node;
			new_page_node->next = NULL;
			new_page_node->prev = p->end;
			p->end = new_page_node;
		}
		
		p->num_page_nodes++;
		return 1;
	}
	
	return 0;
}

page_node* search_in_page(int val, page* p){
	
}

int only_sentinel(page* p){
	if(p != NULL)
		return p->start->next == NULL;
	else return 0;
}

/*
Find page with smallest larger value
EG:
	p => [1,3,6,10,20]
	needle => 8
	Would find 10, not 20.

I think this could be sped up with more of a binary
search approach. But i will worry about that later.
	=> chop until value stops being larger, is smaller
	=> then go up the list until the larger value is found

Assumes the list (the page) is in sorted order.
*/
page_node* search_page_ceil(int val, page* p){
	page_node *iter = p->end;
	while(iter != NULL){
		if(iter->n->val > val){
			return iter;
		}
		iter = iter->next;
	}
	return false;
}

void create_split_page(page* p, page_node* start, page_node* end){
	p->start->next = start;
	p->end = end;
}

/*
@split_page
Breaks a page into two pages, down the middle.
The middle node is returned, with the new page 
attached as its child.

Page_node is returned instead of page.
The page_node is generally inserted into another,
existing page. This is just the way b-trees are constructed.
*/
page_node* split_page(page* p){
	// page *split = (page*) malloc(sizeof(page));
	printf("\n--------splitting page-----\n\n");
	page *split = make_page();
	int center = ceil(p->num_page_nodes / 2);
	page_node *iter = p->start;
	page_node *center_node;
	for(int i = 0; iter != NULL; i++){
		if(i == center){
			center_node = iter;
			
			// theoretically, the list could be small enough that this causes
			// a segfault...fix
			iter = iter->next;
		
			// since the b-tree has these in sorted order
			// we just need to break off part of it
			create_split_page(split, iter, p->end);

			p->end = center_node->prev;
			center_node->prev->next = NULL;
			center_node->prev = NULL;

			center_node->child = split;
			split->parent = center_node;

			break;
		}
		iter = iter->next;
	}
	printf("center: %i\n", center_node->n->val);
	printf("child of split: ");
	print_page(center_node->child);
	printf("left page: ");
	print_page(p);
	printf("\n-----------------------\n");
	return center_node;
}

int remove_page_node(page_node *n){
	page_node *next = n->next;
	page_node *prev = n->prev;

	prev->next = next;
	next->prev = prev;

	// Free could go here?
}

int page_is_full(page *p){
	return p->num_page_nodes > U;
}

// Returns an empty page
// This is so we never forget to add the sentinel node
page* make_page(){
	page* p = (page*) malloc(sizeof(page));
	p->end = NULL; p->start = NULL; p->num_page_nodes = 0;
	node *n = (node*) malloc(sizeof(node));
	n->val = NULL;
	insert_into_page(p, n);
	return p;
}
