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

	printf("number of nodes inserted: %i\n", p->num_page_nodes);

	return p;
}

page* make_sorted_test_page(int *values){
	page* p = (page*) malloc(sizeof(page));
	p->head = NULL; p->tail = NULL; p->num_page_nodes = 0;

	for(; *values != NULL; values++){
		// printf("making node with value: %i\n", *values);
		node* n = (node*) malloc(sizeof(node));

		n->val = *values;
		n->ext = 1;
		insert_node_into_page_sorted(p, n);
		page_node* iter = p->tail;
		printf("current list: \t");
		do {
			node* n = iter->n->val;
			printf("%i\t", iter->n->val);
			iter = iter->next;
		} while(iter != NULL);
		printf("\n");
	}

	printf("\nnumber of nodes inserted: %i\n", p->num_page_nodes);
	return p;
}

tree* make_test_tree(int *values){
	tree* t = (tree*) malloc(sizeof(tree));
	t = prepare_tree(t);
	
	for(; *values != NULL; values++){
		node *n = (node*) malloc(sizeof(node));
		n->val = *values;
		n->ext = 1;
		printf("%i\n",*values);
		insert(n, t);
	}
}