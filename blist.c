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
	//node->value = NULL;	// MEMLEAK PROBABLE
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

void blist_destroy(blist_t *list) {	// assuming that nodes are dynamically
	bnode_t *tmp = list->head;		// allocated
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


void blist_prepend(blist_t *list, void *val) {
	bnode_t *node = bnode_new(val);
	if (list->head == NULL) {
		list->head = node;
		list->tail = node;
	} else {
		list->head->prev = node;
		node->next = list->head;
		list->head = node;
	}
	list->size++;
}

void blist_append(blist_t *list, void *val) {
	bnode_t *node = bnode_new(val);
	if (list->head == NULL) {
		list->head = node;
		list->tail = node;
	} else {
		list->tail->next = node;
		node->prev = list->tail;
		list->tail = node;
	}
	list->size++;
}

/*
 * size 3, index 2 ok
 * size 3, index 3 not ok
 */
void *blist_pop(blist_t *list, int index) {
	if (index == -1) {
		index = list->size - 1;
	}
	if (index > list->size) {
		fprintf(stderr, "Error: could not pop, index > list size\n");
		return NULL;
	}
	bnode_t *node = list->head;
	while(index > 0) {
		node = node->next;
		index--;
	}
	if (node == list->head || node == list->tail) {
		if (node == list->head) {
			list->head = list->head->next;
			if (list->head != NULL) {
				list->head->prev = NULL;
			}
		}
		if (node == list->tail) {
			list->tail = list->tail->prev;
			if (list->tail != NULL) {
				list->tail->next = NULL;
			}
		}
	} else {
		node->next->prev = node->prev;
		node->prev->next = node->next;
	}
	void *result = node->value;
	list->size--;
	bnode_delete(node);
	return result;
}

/*
void *blist_pop(blist_t *list, int index) {
	if (index == -1) {
		index = list->size;
	}
	if (
	bnode_t *node = list->head;
	while (node && index-1) {
		printf("DUPA\n");
		node = node->next;
		index--;
	}
	if(node == NULL) {
		return NULL;
	}
	list->size--;
	void *result = node->value;
	node->prev->next = node->next;
	node->next->prev = node->prev;
	return result;
}
*/
