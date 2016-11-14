#ifndef VIEW_H
#define VIEW_H

#include "gameobj.h"
#include <ncurses.h>    // temp

WINDOW *win;    // temp

void view_init();
void view_end();

void view_add_s(Snake *s, char head, char body, char dhead, char dbody);
void view_add_f(Food *f, char look);
void view_rm_s(Snake *s);
void view_rm_f(Food *f);

void view_update();

#endif
