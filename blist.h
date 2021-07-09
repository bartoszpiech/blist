#ifndef BLIST_H
#define BLIST_H

#ifdef __cplusplus
extern "C" {
#endif

#define blist_foreach(l) for(bnode_t *iterator = l->head; iterator != NULL;\
			iterator = iterator->next)

typedef void (*free_function)(void *);

typedef struct bnode_t {
	void *value;
	struct bnode_t *prev;
	struct bnode_t *next;
} bnode_t;

typedef struct {
	unsigned int size;
	bnode_t *head;
	bnode_t *tail;
	free_function free_fn;
} blist_t;

int bnode_init(bnode_t *node, void *val);
bnode_t *bnode_new(void *val);

void bnode_destroy(bnode_t *node);
void bnode_delete(bnode_t *node);

int blist_init(blist_t *list, free_function free_fn);
blist_t *blist_new(free_function free_fn);

void blist_destroy(blist_t *list);
void blist_delete(blist_t *list);

void blist_prepend(blist_t *list, void *val);
void blist_append(blist_t *list, void *val);
void blist_insert(blist_t *list, void *val, int index);
void *blist_pop(blist_t *list, int index);

int blist_index(blist_t *list, void *val);

#ifdef __cplusplus
}
#endif

#endif

