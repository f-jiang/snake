#include <unistd.h>
#include <ncurses.h>
#include <stdio.h>

#include "gameobj.h"

// 00, 01, 10, 11, 100
// ~UP == DOWN
// ~LEFT == RIGHT
typedef enum direction_t { UP = 0, LEFT, RIGHT, DOWN, NONE } Direction;

int main(int argc, char *argv[]) {
//    Snake *s = snake_init(10, 10);
//    printf("*x: %d  *y: %d\n", *(s->x), *(s->y));
//    printf("*head_x: %d  *head_y: %d\n", *(s->head_x), *(s->head_y));
//    printf("x == head_x: %d  y == head_y: %d\n", s->x == s->head_x, s->y == s->head_y);
//
//    int i = 0; 
//    
//    for (i = 0; i < s->len; i++) {
//        printf("p%d: (%d, %d) ", i + 1, *((s->x) + i), *((s->y) + i));
//    }
//    puts("\n");
//    snake_grow(s);
//    snake_move(s, DOWN);
//
//    for (i = 0; i < s->len; i++) {
//        printf("p%d: (%d, %d) ", i + 1, *((s->x) + i), *((s->y) + i));
//    }
//    puts("\n");
//    snake_grow(s);
//    snake_move(s, LEFT);
//
//    for (i = 0; i < s->len; i++) {
//        printf("p%d: (%d, %d) ", i + 1, *((s->x) + i), *((s->y) + i));
//    }

// gameobj changes to make:
// snake_move params change to s, x, y
// remove head
// move direction enum here[?]
// - snake needs direction to prevent turning backkwards
// - main needs direction to 
/*
    init game object snake
    init food
    init difficulty, score, x, y
    init atefood=false, nofood = true, gameover = false
    
    loop:
        if nofood is true:
            if atefood true:
                *clear* food
                free(food);
                atefood = false
            *draw* food in random x, y
            within bounds, not on snake or walls
            ** on high difficulty, place close to snake
            nofood = false

        if gameover *draw* rekt snake and break
        else *draw* normal snake 

        check for keyboard press:
            take latest press as the one used
            if dir changed, set new dir
            else leave as is
        sleep: decrease duration as difficulty increases
        calculate new x, y based on dir from above:
            if edge of map, get opposite edge

        snake_move(s, x, y)     // will have to modify implementation

        if food found (x y of snake equals x y of food):
            grow snake
            increase difficulty
            *clear* current food in next loop (atefood = true)
            *draw* new food in next loop (nofood = true)
        
        if collide with self or wall:
            snake dies
            gameover = true

    *clear snake and food*
    *display* game over graphics
*/
    return 0;
}

