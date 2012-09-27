#ifndef PAGE_H
#define PAGE_H
#include <stdbool.h>


typedef struct {
	int val;
	int ext; // The external database location
} node;

/*
@page_node
Node for the doubly-linked list used by Page.
*/
typedef struct page_node page_node;
typedef struct page page;
struct page_node {
	page_node *prev;
	page_node *next;
	page *child;
	page *parent;
	node *n;
};

struct page {
	page_node *head;
	page_node *tail;
	int num_page_nodes;
};


// Forward Declarations
int insert_into_page(page *p, node *n);
int remove_page_node(page_node *n);
bool is_full(page *p);

#endif