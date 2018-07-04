#ifndef _DEMI_LIST_H
#define _DEMI_LIST_H

typedef struct list list_t;
typedef struct list_node list_node_t;

void list_create(list_t **, void (*)(void *));
void list_destroy(list_t *);

//info
int list_size(list_t *);

//adding
void list_append(list_t *, void *);
void list_prepend(list_t *, void *);
void list_add(list_t *, void *, int);

//removing
void list_remove_head(list_t *);
void list_remove_tail(list_t *);
void list_remove_element(list_t *, int);
void list_clear(list_t *);

//getting
void *list_head(list_t *);
void *list_tail(list_t *);
void *list_element(list_t *, int);

void list_foreach(list_t *, void (*)(const void *));

#endif
