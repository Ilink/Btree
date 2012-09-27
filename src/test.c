#include "page.h"
#include "btree.h"
#include "test.h"
#include <stdio.h>
#include <stdlib.h>

page* make_test_page(int *values){
	page* p = (page*) malloc(sizeof(page));
	p->head = NULL; p->tail = NULL; p->num_page_nodes = 0;

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

	printf("number of nodes inserted: %i", p->num_page_nodes);

	return p;
}
