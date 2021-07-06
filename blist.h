#ifndef BLIST_H
#define BLIST_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct bnode_t {
	void *value;
	struct bnode_t *prev;
	struct bnode_t *next;
} bnode_t;

typedef struct {
	unsigned int size;
	bnode_t *head;
	bnode_t *tail;
} blist_t;

int bnode_init(bnode_t *node, void *val);
bnode_t *bnode_new(void *val);

void bnode_destroy(bnode_t *node);
void bnode_delete(bnode_t *node);

int blist_init(blist_t *list);
blist_t *blist_new();

void blist_destroy(blist_t *list);
void blist_delete(blist_t *list);

void blist_prepend(blist_t *list, void *val);
void blist_append(blist_t *list, void *val);
void *blist_pop(blist_t *list, int index);

//int blist_index(blist_t 

#ifdef __cplusplus
}
#endif

#endif

