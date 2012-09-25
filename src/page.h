#ifndef PAGE_H
#define PAGE_H


typedef struct {
	int val;
	int ext; // The external database location
} node;

/*
@page_node
Node for the doubly-linked list used by Page.
*/
typedef struct page_node page_node;
struct page_node {
	page_node *prev;
	page_node *next;
	node *n;
};

typedef struct {
	page_node *head;
	page_node *tail;
} page;

// typedef struct page_node page;

int insert_into_page(page *p, node *n);

#endif