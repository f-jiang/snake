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

    *(s->x) = x;
    *(s->y) = y;

    s->head_x = s->x;
    s->head_y = s->y;

    s->last_x = *(s->x);
    s->last_y = *(s->y);

    s->dir = NONE;
    
    return s;
}

Food *food_init(int x, int y) {
    Food *f = malloc(sizeof(*f));
    f->x = x;
    f->y = y;
    return f;
}

// can only grow once per movement
void snake_grow(Snake * const s) {
    if (*(s->x + s->len - 1) != s->last_x || *(s->y + s->len - 1) != s->last_y) {
        s->len++;
        int *x1 = realloc(s->x, s->len * sizeof(*x1)); 
        int *y1 = realloc(s->y, s->len * sizeof(*y1)); 

        if (x1 && y1) {
            s->head_x = s->x = x1;
            s->head_y = s->y = y1;
            *(s->x + s->len - 1) = s->last_x;
            *(s->y + s->len - 1) = s->last_y;
        } else {
            free(x1);
            free(y1);
        }
    }
}

void snake_move(Snake * const s, Direction d) {
    if (~d != s->dir) { // snake can't move "backward"
        int x = *(s->head_x);
        int y = *(s->head_y);

        switch (d) {
            case LEFT:
                x -= 1;
                break;
            case RIGHT:
                x += 1;
                break;
            case UP:
                y += 1;
                break;
            case DOWN:
                y -= 1;
                break;
            default:
                return;
        }

        int i = s->len - 1;
        s->last_x = *(s->x + i);
        s->last_y = *(s->y + i);
        for ( ; i > 0; i--) {
            *(s->x + i) = *(s->x + i - 1);
            *(s->y + i) = *(s->y + i - 1);
        }
        *(s->x) = x;
        *(s->y) = y;

        s->dir = d;
    }
}

