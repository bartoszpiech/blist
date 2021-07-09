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
		fprintf(stderr, "\x1b[31mError: could not create new node\x1b[0m\n");
		exit(1);
	}
	if (bnode_init(node, val)) {
		fprintf(stderr, "\x1b[31mError: could not init a new node\x1b[0m\n");
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

int blist_init(blist_t *list, free_function free_fn) {
	list->size = 0;
	list->head = NULL;
	list->tail = NULL;
	list->free_fn = free_fn;
	return 0;
}

blist_t *blist_new(free_function free_fn) {
	blist_t *list;
	if ((list = malloc(sizeof(blist_t))) == NULL) {
		fprintf(stderr, "\x1b[31mError: could not create new list\x1b[0m\n");
		exit(1);
	}
	if (blist_init(list, free_fn)) {
		fprintf(stderr, "\x1b[31mError: could not init a new list\x1b[0m\n");
		exit(1);
	}
	return list;
}

void blist_destroy(blist_t *list) {	// assuming that nodes are dynamically
	bnode_t *current = list->head;		// allocated
	while (list->head != NULL) {
		current = list->head;
		list->head = current->next;
		if (list->free_fn) {
			list->free_fn(current->value);
		}
		bnode_delete(current);
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

void blist_insert(blist_t *list, void *val, int index) {
	if (index == -1) {
		index = list->size;
	}
	if (index <= 0) {
		blist_prepend(list, val);
	} else if (index >= list->size) {
		blist_append(list, val);
	} else {
		bnode_t *node = bnode_new(val);
		bnode_t *tmp = list->head;
		for (int i = index; i > 0; i--) {
			tmp = tmp->next;
		}
		tmp->prev->next = node;
		node->prev = tmp->prev;
		node->next = tmp;
		tmp->prev = node;
		list->size++;
	}
}

void *blist_pop(blist_t *list, int index) {
	if (index == -1) {
		index = list->size - 1;
	}
	if (index > list->size) {
		fprintf(stderr,
				"\x1b[31mError: could not pop, index out of range\x1b[0m\n");
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

int blist_index(blist_t *list, void *val) {
	int index = 0;
	blist_foreach (list) {
		if (iterator->value == val) {
			return index;
		}
		index++;
	}
	return -1;
}
