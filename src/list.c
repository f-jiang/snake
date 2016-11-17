#include "list.h"

#include <stdbool.h>    // bool
#include <stdlib.h>     // malloc(), free()
#include <string.h>     // memcpy()

struct node_t {
    void *val;
    struct node_t *next, *prev;
};

struct linked_list_t {
    size_t len;
    size_t elem_size;
    struct node_t *front, *back;
}; 

static struct node_t *get_node(const list * const l, size_t index) {
    struct node_t *n = NULL;
    size_t i;    

    if (index < l->len / 2) {
        n = l->front;
        for (i = 0; i < index; i++) {
            n = n->next;
        }
    } else if (index < l->len) {
        n = l->back;
        for (i = l->len - 1; i > index; i--) {
            n = n->prev;
        }
    }

    return n;   // NULL iff |index| is out of bounds
}

static void node_del(struct node_t *n) {
    free(n->val);
    free(n);
}

list *list_init(size_t elem_size) {
    struct linked_list_t *l = malloc(sizeof(*l));
    l->len = 0;
    l->elem_size = elem_size;
    l->front = l->back = NULL;
    return l;
}

void list_del(list **l) {
    struct node_t *cur = (*l)->front;

    while ((*l)->len-- > 0) {
        (*l)->front = (*l)->front->next;
        node_del(cur);
        cur = (*l)->front;
    }

    free(*l);
    *l = NULL;
}

size_t list_get_len(const list * const l) {
    return l->len;
}

void list_set(list * const l, size_t index, void *val) {
    struct node_t *n = get_node(l, index);

    if (n) {    // |index| is within bounds
        memcpy(n->val, val, l->elem_size);
    }
}

void *list_get(const list * const l, size_t index) {
    return get_node(l, index)->val;
}

void *list_front(const list * const l) {
    return list_get(l, 0);
}

void *list_back(const list * const l) {
    return list_get(l, l->len - 1);
}

void list_insert(list * const l, size_t index, void *val) {
    struct node_t *n = malloc(sizeof(*n));
    n->val = malloc(l->elem_size);
    memcpy(n->val, val, l->elem_size);

    if (l->len == 0) {
        n->next = n->prev = NULL;
        l->front = l->back = n; 
    } else if (index == 0) {
        n->next = l->front;
        n->prev = NULL;
        l->front = n->next->prev = n;
    } else if (index == l->len) {
        n->next = NULL;
        n->prev = l->back;
        l->back = n->prev->next = n;
    } else {
        struct node_t *cur = get_node(l, index);
        n->next = cur;
        n->prev = cur->prev;
        n->prev->next = n->next->prev = n;
    }

    l->len++;
}

void list_remove(list * const l, size_t index) {
    struct node_t *n = get_node(l, index);

    if (n) {    // |index| is within bounds
        if (l->len == 1) {
            l->front = l->back = NULL;
        } else if (index == 0) {
            l->front = n->next;
        } else if (index == l->len - 1) {
            l->back = n->prev;
        } else {
            n->next->prev = n->prev;
            n->prev->next = n->next;
        }

        node_del(n);
        l->len--;
    } 
} 

void list_push_front(list * const l, void *val) {
    list_insert(l, 0, val);
}

void list_pop_front(list * const l) {
    list_remove(l, 0);
}

void list_push_back(list * const l, void *val) {
    // we are inserting after the last elem (ie. at index |l->len|)
    list_insert(l, l->len, val);
}

void list_pop_back(list * const l) {
    list_remove(l, l->len - 1);
}

