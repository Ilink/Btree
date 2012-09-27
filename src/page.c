#include "page.h"
#include <stdio.h>
#include <stdlib.h>


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
	page_node *tail_temp = p->tail;

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
	// p->tail = new_page_node;
	// new_page_node->prev = tail_temp;

	return 1;
}

int remove_page_node(page_node *n){
	page_node *next = n->next;
	page_node *prev = n->prev;

	prev->next = next;
	next->prev = prev;

	// Free could go here
}