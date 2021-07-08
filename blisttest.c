#include <stdio.h>

#include "blist.h"

#define FALSE	0
#define TRUE	1

int test_new_empty_list() {
	blist_t *list = blist_new();
	int size = list->size;
	blist_delete(list);
	return size;
}

int test_append_list() {
	blist_t *list = blist_new();
	int tmp = 5;
	blist_append(list, &tmp);
	int size = list->size;
	blist_delete(list);
	return size;
}

int test_append_multiple_list() {
	blist_t *list = blist_new();
	int a = 5;
	int b = 6;
	int c = 7;
	int d = 8;
	int e = 9;
	blist_append(list, &a);
	blist_append(list, &b);
	blist_append(list, &c);
	blist_append(list, &d);
	blist_append(list, &e);
	int size = list->size;
	blist_foreach(list) {
		printf("%d ->", *(int *)iterator->value);
	}
	blist_delete(list);
	return size;
}

int test_append_delete_from_list() {
	blist_t *list = blist_new();
	int tmp = 5;
	blist_append(list, &tmp);
	blist_pop(list, -1);
	int size = list->size;
	blist_delete(list);
	return size;
}

int test_append_delete_multiple_from_list() {
	blist_t *list = blist_new();
	int a = 5;
	int b = 6;
	int c = 7;
	blist_append(list, &a);
	blist_append(list, &b);
	blist_append(list, &c);
	blist_pop(list, -1);
	blist_pop(list, -1);
	int size = list->size;
	blist_delete(list);
	return size;
}

int test_prepend_list() {
	blist_t *list = blist_new();
	int a = 5;
	blist_prepend(list, &a);
	int size = list->size;
	blist_delete(list);
	return size;
}

int test_prepend_multiple_list() {
	blist_t *list = blist_new();
	int a = 5;
	int b = 6;
	int c = 7;
	blist_prepend(list, &a);
	blist_prepend(list, &b);
	blist_prepend(list, &c);
	blist_foreach(list) {
		printf("%d ->", *(int *)iterator->value);
	}
	int size = list->size;
	blist_delete(list);
	return size;
}

int test_pop_empty_list() {
	blist_t *list = blist_new();
	void *ptr = blist_pop(list, -1);
	if (ptr == NULL) {
		return 1;
	}
	return 0;
}

int test_insert_list() {
	blist_t *list = blist_new();
	int a = 5;
	blist_insert(list, &a, 0);
	int size = list->size;
	int *aptr = blist_pop(list, -1);
	printf("ptr = %d", *aptr);
	blist_delete(list);
	return size;
}

int test_insert_multiple_list() {
	blist_t *list = blist_new();
	int a = 5;
	int b = 6;
	int c = 7;
	blist_insert(list, &a, 0);
	blist_insert(list, &b, 1);
	blist_insert(list, &c, 1);
	int size = list->size;
	blist_delete(list);
	return size;
}

int test_insert_delete_multiple_from_list() {
	blist_t *list = blist_new();
	int a = 5;
	int b = 6;
	int c = 7;
	blist_insert(list, &a, 0);
	blist_insert(list, &b, 1);
	blist_insert(list, &c, 1);
	blist_pop(list, 0);
	blist_pop(list, 0);
	int size = list->size;
	blist_delete(list);
	return size;
}

void test(int expected, int actual, const char *test_name) {
	if (expected == actual) {
		printf("%s - \x1b[32mpassed\x1b[0m\n", test_name);
	} else {
		printf("%s - \x1b[31mfailed\x1b[0m, expected %d; actual %d\n", test_name, expected,

				actual);
	}
}

int main() {
	test(0, test_new_empty_list(),
			"test new empty list");
	test(1, test_append_list(),
			"test append single element to list");
	test(5, test_append_multiple_list(),
			"test append multiple elements to list");
	test(0, test_append_delete_from_list(),
			"test append and delete element from list");
	test(1, test_append_delete_multiple_from_list(),
			"test append and delete multiple elements from list");
	test(1, test_prepend_list(),
			"test prepend single element to list");
	test(3, test_prepend_multiple_list(),
			"test prepend multiple elements to list");
	test(1, test_pop_empty_list(),
			"test pop empty list");
	test(1, test_insert_list(),
			"test insert single element to list");
	test(3, test_insert_multiple_list(),
			"test insert multiple elements to list");
	test(1, test_insert_delete_multiple_from_list(),
			"test insert and delete multiple elements from list");
}
