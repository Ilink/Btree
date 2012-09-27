#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "main.h"
#include "btree.h"
#include "page.h"
#include "test.h"

int main(int argc, char **argv){

	int test_vals[] = {1,2,3,4,5,6, NULL};
	page_node* p = make_test_page(test_vals);

}