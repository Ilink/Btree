#include "page.h"
#include <stdio.h>
#include <stdlib.h>

const int U = 5; // this size is temporary

/*
This is unused for now.
It's too complex for what I have now

In order to specify the binary files, I would need
to specify where they live. Easier if I do not have to do that yet
*/
page_node* load_page(){

}

/*
@insert_into_page
Inserts a node (n) after the page (p)
*/
int insert_into_page(page *p, node *n){
	page_node *new_page_node = (page_node*) malloc(sizeof (page_node));
	new_page_node->n = n;
	new_page_node->next = NULL;
	new_page_node->prev = NULL;
	page_node *tail_temp = p->tail;

	// Only insert below maximum threshold +1
	// +1 because it should be allowed to overflow before being split
	if((p->num_page_nodes + 1) <= U){
		if(p->tail == NULL && p->head == NULL){
			printf("empty list\n");
			p->tail = new_page_node;
		} else if(p->head == NULL){
			printf("no head\n");
			p->tail->next = new_page_node;
			p->head = new_page_node;
			new_page_node->prev = p->tail;
		} else {
			printf("list has head and tail\n");
			p->head->next = new_page_node;
			new_page_node->next = NULL;
			new_page_node->prev = p->head;
			p->head = new_page_node;
		}
		
		p->num_page_nodes++;
		return 1;
	}

	// Allows detection of overflow
	// Tree may decide to split the page if it overflows

	// i sense an off-by-one error...
	if(p->num_page_nodes == U) {
		return 0;
	}
	return 1;
}

/*
@split_page
Breaks a page into two pages, down the middle.
The middle node is returned, with the new page 
attached as its child.
*/
page_node* split_page(page* p){
	/*
	while not at center, advance
	take center node
	after center, accumulate nodes in new list
	center node -> child = accumulated list
	accumulate list -> parent = center node
	return center node
	*/
}

/*
@insert_into_page_sorted
Inserts a node into a page, maintaining ascending order
All b-tree nodes are arranged this way.

This might have some duplicate code from insert_into_page
but it shouldn't really be a big deal since it's all pretty 
standard linked-list type stuff.

This needs to be a binary search instead.
*/
int insert_into_page_sorted(page *p, node *n){
	page_node *new_page_node = (page_node*) malloc(sizeof (page_node));
	new_page_node->n = n;
	new_page_node->next = NULL;
	new_page_node->prev = NULL;
	page_node *tail_temp = p->tail;

	// Only insert below maximum threshold
	if((p->num_page_nodes + 1) <= 5){ //todo: un-hardcode this value
		
		// It is very simple to deal with empty/one-node lists
		if(p->tail == NULL && p->head == NULL){
			printf("empty list\n");
			p->tail = new_page_node;
		} else if(p->head == NULL){
			printf("no head\n");
			if(p->tail->n->val < n->val){
				printf("tail < val");
				p->head = new_page_node;
			} else { // swap head and tail
				printf("val < tail: val is new tail!");
				p->head = p->tail;
				p->tail = new_page_node;
			}
			p->tail->next = p->head;
			p->head->prev = p->tail;
		} else { // insert in order; head and tail are all setup
			// todo: is this the most efficient way? could i use binary search?	
			page_node *iter = p->tail;
			for(int i = 0; iter != NULL; i++) {
				printf("iter (%i) val: %i\n", i, iter->n->val);
				if(n->val < iter->n->val){
					if(iter->prev == NULL){ // we're at the start
						printf("insertng at start\n");
						iter->prev = new_page_node;
						new_page_node->next = iter;
						p->tail = new_page_node;
					} else { // we're in the middle-ish
						printf("inserting in middle-ish\n");
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
				printf("inserting at end\n");
				p->head->next = new_page_node;
				new_page_node->next = NULL;
				new_page_node->prev = p->head;
				p->head = new_page_node;
			}
		}
		p->num_page_nodes++;
		return 1;
	}
	// Allows detection of overflow
	// Tree may decide to split the page if it overflows
	return 0;
}

int remove_page_node(page_node *n){
	page_node *next = n->next;
	page_node *prev = n->prev;

	prev->next = next;
	next->prev = prev;

	// Free could go here
}