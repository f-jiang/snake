#ifndef GAME_OBJ_H
#define GAME_OBJ_H

#include <stddef.h>

// 00, 01, 10, 11, 100
// ~UP == DOWN
// ~LEFT == RIGHT
typedef enum direction_t { UP = 0, LEFT, RIGHT, DOWN, NONE } Direction;

// struct should be defined in .h not in .c
// so other .c files can "see" the struct def
typedef struct snake_t {
    size_t len;
    int *x, *y;
    int *head_x, *head_y;
    int last_x, last_y;
    Direction dir;
} Snake;

typedef struct food_t {
    int x, y;
} Food;

Snake *snake_init(int x, int y);
Food *food_init(int x, int y);

void snake_grow(Snake * const s);
void snake_move(Snake * const s, Direction d);

#endif
