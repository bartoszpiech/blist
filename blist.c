#include <stdio.h>
#include <stdlib.h>

#include "blist.h"

int bnode_init(bnode_t *node, void *val) {
	node->value = val;
	node->prev = NULL;
	node->next = NULL;
	return 0;
}

bnode_t *bnode_new(void *val) {
	bnode_t *node;
	if ((node = malloc(sizeof(bnode_t))) == NULL) {
		fprintf(stderr, "Error: could not create new node\n");
		exit(1);
	}
	if (bnode_init(node, val)) {
		fprintf(stderr, "Error: could not init a new node\n");
		exit(1);
	}
	return node;
}

void bnode_destroy(bnode_t *node) {
	node->value = NULL;	// MEMLEAK PROBABLE
	node->prev = NULL;
	node->next = NULL;
}

void bnode_delete(bnode_t *node) {
	bnode_destroy(node);
	free(node);
}

int blist_init(blist_t *list) {
	list->size = 0;
	list->head = NULL;
	list->tail = NULL;
	return 0;
}

blist_t *blist_new() {
	blist_t *list;
	if ((list = malloc(sizeof(blist_t))) == NULL) {
		fprintf(stderr, "Error: could not create new list\n");
		exit(1);
	}
	if (blist_init(list)) {
		fprintf(stderr, "Error: could not init a new list\n");
		exit(1);
	}
	return list;
}

void blist_destroy(blist_t *list) {
	bnode_t *tmp = list->head;
	while (tmp != NULL) {
		bnode_t *cleaner = tmp;
		tmp = tmp->next;
		bnode_delete(cleaner);
	}
}
	
void blist_delete(blist_t *list) {
	blist_destroy(list);
	free(list);
}

