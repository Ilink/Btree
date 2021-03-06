#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "main.h"
#include "btree.h"
#include "page.h"
#include "test.h"

int main(int argc, char **argv){

	page_node* p;
	int test_vals[] = {1,2,3,4,5,6, NULL};
	// p = make_test_page(test_vals);

	int test_vals_unsorted[] = {4,3,1,9,6,10,	12,15,17,20,30,40,50,100, NULL};
	// p = make_sorted_test_page(test_vals_unsorted);
	// test_split_page(p);

	tree *t = make_test_tree(test_vals_unsorted);
	

	print_tree(t);
}