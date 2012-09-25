#include "page.h"
#include "tree.h"
#include "test.h"
#include <stdio.h>
#include <stdlib.h>

page* make_test_page(int *values){
	page* p = (page*) malloc(sizeof(page));
	p->head = NULL; p->tail = NULL;

	for(; *values != NULL; values++){
		printf("making node with value: %i\n", *values);
		node* n = (node*) malloc(sizeof(node));

		n->val = *values;
		n->ext = 1;
		insert_into_page(p, n);
	}

	page_node* iter = p->tail;
	do {
		node* n = iter->n->val;
		printf("val: %i", iter->n->val);
		iter = iter->next;
	} while(iter != NULL);

	// page_node* pn = (page_node *) malloc(sizeof(page_node));
	return p;
}
