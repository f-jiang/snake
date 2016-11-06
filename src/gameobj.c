#include "gameobj.h"

#include <stdlib.h>

Snake *snake_init(int x, int y) {
    Snake *s = malloc(sizeof(*s) + 2 * sizeof(int));
    s->len = 1;

    s->x = (int *) (s + 1);
    s->y = (int *) (s + 1) + 1;
    *(s->x) = x;
    *(s->y) = y;

    s->head_x = s->x;
    s->head_y = s->y;
    return s;
}

Food *food_init(int x, int y) {
    Food *f = malloc(sizeof(*f));
    f->x = x;
    f->y = y;
    return f;
}

