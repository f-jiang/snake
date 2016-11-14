#include "gameobj.h"

#include <stdlib.h>

// C struct "hack"
// if realloc'ing s->x and s->y, would have to realloc entire struct as well
// Snake *s = malloc(sizeof(*s) + 2 * sizeof(int));
// s->len = 1;
//
// s->x = (int *) (s + 1);
// s->y = (int *) (s + 1) + 1;
Snake *snake_init(int x, int y) {
    Snake *s = malloc(sizeof(*s));

    s->len = 1;
    s->x = malloc(s->len * sizeof(*(s->x)));
    s->y = malloc(s->len * sizeof(*(s->y)));
    s->head_x = s->x;
    s->head_y = s->y;
    s->alive = true;

    s->x[0] = x;
    s->y[0] = y;

    return s;
}

Food *food_init(int x, int y) {
    Food *f = malloc(sizeof(*f));
    f->x = x;
    f->y = y;
    f->eaten = false;
    return f;
}

void snake_del(Snake **s) {
    free((*s)->x);
    free((*s)->y);
    free(*s);
    *s = NULL;
}

void food_del(Food **f) {
    free(*f);
    *f = NULL;
}

// can only grow once per movement
void snake_grow(Snake * const s) {
    s->len++;
    int *x1 = realloc(s->x, s->len * sizeof(*x1));
    int *y1 = realloc(s->y, s->len * sizeof(*y1));

    if (x1 && y1) {
        s->head_x = s->x = x1;
        s->head_y = s->y = y1;
    } else if (!x1) {
        s->len--;
        free(x1);
    } else if (!y1) {
        s->len--;
        free(y1);
    } else {
        s->len--;
        free(x1);
        free(y1);
    }
}

void snake_move_to(Snake * const s, int x, int y) {
    int i = s->len - 1;

    for ( ; i > 0; i--) {
        s->x[i] = s->x[i - 1];
        s->y[i] = s->y[i - 1];
    }

    s->x[0] = x;
    s->y[0] = y;
}

