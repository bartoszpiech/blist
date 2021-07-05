#include <stdio.h>

#include "blist.h"

#define FALSE	0
#define TRUE	1

int test_new_empty_list() {
	blist_t *list = blist_new();
	return list->size;
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
	test(0, test_new_empty_list(), "test new empty list");
}

