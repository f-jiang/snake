#ifndef LIST_H
#define LIST_H

#include <stddef.h>     // size_t

typedef struct linked_list_t list;

list *list_init(size_t elem_size);
void list_del(list **l);

size_t list_get_len(const list * const l);

void list_set(list * const l, size_t index, void *val);
void *list_get(const list * const l, size_t index);

void *list_front(const list * const l);
void *list_back(const list * const l);

void list_insert(list * const l, size_t index, void *val);
void list_remove(list * const l, size_t index);

void list_push_front(list * const l, void *val);
void list_pop_front(list * const l);

void list_push_back(list * const l, void *val);
void list_pop_back(list * const l);

#endif
