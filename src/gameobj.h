#ifndef GAME_OBJ_H
#define GAME_OBJ_H

#include <stddef.h>
#include <stdbool.h>

// struct should be defined in .h not in .c
// so other .c files can "see" the struct def
typedef struct snake_t {
    size_t len;
    int *x, *y;
    int *head_x, *head_y;
    bool alive;
} Snake;

typedef struct food_t {
    int x, y;
    bool eaten;
} Food;

Snake *snake_init(int x, int y);
Food *food_init(int x, int y);

void snake_del(Snake **s);
void food_del(Food **f);

void snake_grow(Snake * const s);
void snake_move_to(Snake * const s, int x, int y);
bool snake_touching(Snake * const s, int x, int y);

#endif

