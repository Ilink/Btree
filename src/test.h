#ifndef TEST_H
#define TEST_H

page* make_test_page(int *values);
page* make_sorted_test_page(int *values);
tree* make_test_tree(int *values);
page_node* test_split_page(page* p);

#endif