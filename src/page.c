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

	// Only insert below maximum threshold
	if((p->num_page_nodes + 1) <= 5){
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
	return 0;
}

/*
@insert_into_page_sorted
Inserts a node into a page, maintaining ascending order
All b-tree nodes are arranged this way.

This might have some duplicate code from insert_into_page
but it shouldn't really be a big deal since it's all pretty 
standard linked-list type stuff.

I guess the checks could go in another function shared by both...
*/
int insert_into_page_sorted(page *p, node *n){
	page_node *new_page_node = (page_node*) malloc(sizeof (page_node));
	new_page_node->n = n;
	new_page_node->next = NULL;
	new_page_node->prev = NULL;
	page_node *tail_temp = p->tail;

	// Only insert below maximum threshold
	if((p->num_page_nodes + 1) <= 5){
		if(p->tail == NULL && p->head == NULL){
			printf("empty list\n");
			// no need to compare here
			p->tail = new_page_node;
		} else if(p->head == NULL){
			printf("no head\n");
			if(p->tail->n->val > n->val){
				p->head = new_page_node;
			} else { // swap head and tail
				p->head = p->tail;
				p->head = new_page_node;
			}
			p->tail->next = p->head;
			p->head->prev = p->tail;
		} else {
			printf("list has head and tail\n");
			// insert in order, within the current list
			// this could use a binary search

			page_node *iter = p->tail;
			while(iter != NULL){
				if(n->val < iter->n->val){
					iter->prev = 
					break;
				}
				iter = iter->next;
			}

			// p->head->next = new_page_node;
			// new_page_node->next = NULL;
			// new_page_node->prev = p->head;
			// p->head = new_page_node;
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