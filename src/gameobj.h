#ifndef GAME_OBJ_H
#define GAME_OBJ_H

#include <stddef.h>

typedef enum direction_t { LEFT, RIGHT, UP, DOWN } Direction;

// struct should be defined in .h not in .c
// so other .c files can "see" the struct def
typedef struct snake_t {
    size_t len;
    int *x, *y;
    int *head_x, *head_y;
} Snake;

typedef struct food_t {
    int x, y;
} Food;

Snake *snake_init(int x, int y);
Food *food_init(int x, int y);

void snake_eat(Snake *s);
void snake_move(Snake *s, Direction d);

#endif
