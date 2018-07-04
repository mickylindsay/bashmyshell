#include <stdlib.h>

#include "list.h"

struct list {
  list_node_t *head;
  list_node_t *tail;
  int size;
  void (*free)(void *);
};

struct list_node{
  void *value;
  list_node_t *next;
};

static list_node_t *get_node(list_t *list, int index);

void list_create(list_t **out, void (*free_node)(void *)){
  list_t *list = (list_t *)calloc(1, sizeof(list_t));
  list->free = free_node;
  *out = list;
  
}

void list_destroy(list_t *list){
  if(list){
    list_clear(list);
    free(list);
  }
}

int list_size(list_t *list){
  return (list) ? list->size : 0;
}

void list_append(list_t *list, void *element){
  if(list)
    list_add(list, element, list->size);
}

void list_prepend(list_t *list, void *element){
  list_add(list, element, 0);
}

void list_add(list_t *list, void *element, int index){
  if(list && element && index >= 0 && index <= list->size){
    list_node_t *node = (list_node_t *) calloc(1, sizeof(list_node_t));
    node->value = element;
    if(index == 0){
      node->next = list->head;
      list->head = node;
      if(list->size == 0)
	list->tail = node;
    }else{
      list_node_t *prev = get_node(list, index - 1);
      node->next = prev->next;
      prev->next = node;
      if(index == list->size)
	list->tail = node;
    }
    list->size++;
  }
}

void list_remove_head(list_t *list){
  if(list){
    if(list->head){
      list_node_t *next = list->head->next;
      if(list->free)
	list->free(list->head->value);
      list->head->value = NULL;
      free(list->head);
      list->head = next;
      list->size--;
    }
  }
}

void list_remove_tail(list_t *list){
  if(list)
    list_remove_element(list, list->size - 1);
}

void list_remove_element(list_t *list, int index){
  if(index < 0 || index >= list->size || list->head == NULL) 
    return;
  
  if(index == 0){
    list_remove_head(list);
  }

  list_node_t *prev = get_node(list, index - 1);
  list_node_t *next = prev->next->next;
  if(index == list->size - 1)
    list->tail = prev;
  if(list->free)
    list->free(prev->next->value);
  prev->next->value = NULL;
  free(prev->next);
  prev->next = next;
  list->size--;
}

void list_clear(list_t *list){
	while(list->size > 0)
	  list_remove_head(list);
}

void *list_head(list_t *list){
	return (list && list->head) ? list->head->value : NULL;
}

void *list_tail(list_t *list){
	return (list && list->tail) ? list->tail->value : NULL;
}

void *list_element(list_t *list, int index){
	return get_node(list, index)->value;
}


void list_foreach(list_t *list, void (*fun)(const void *)){
	list_node_t *node = list->head;
	do{
		fun(node->value);
		node = node->next;
	}while(node);
}

static list_node_t *get_node(list_t *list, int index){
	list_node_t *node = NULL;
	if(list && index >= 0 && index < list->size){
		node = list->head;
		while(index > 0 && node){
			node = node->next;
			index--;
		}
	}
	return node;
}
