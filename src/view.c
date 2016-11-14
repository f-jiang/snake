#include "view.h"

#include <stdlib.h>     // malloc(), free()
#include <stdbool.h>     // malloc(), free()
#include <string.h>     // memcpy()
//#include <ncurses.h>  // temp
#include "main.h"       // MAP_WIDTH, MAP_HEIGHT

// TODO:
// - add support for multiple |Snake| and |Food| objects

#define WIN_WIDTH        (MAP_WIDTH + 2)
#define WIN_HEIGHT       (MAP_HEIGHT + 2)
#define WIN_X            ((COLS - WIN_HEIGHT) / 2)
#define WIN_Y            ((LINES - WIN_WIDTH) / 2)

static struct s_graphics_t {
    const Snake *s;
    Snake s_prev;
    char head, body;
    char dhead, dbody;
    bool remove;
} sg;

static struct f_graphics_t {
    const Food *f;
    char look;
    bool remove;
} fg;

/*static*/ WINDOW *win; // temp

static void draw(int y, int x, char c) {
    mvwaddch(win, (WIN_HEIGHT - 1) - (y + 1), x + 1, c);
}

void view_init(void) {
    initscr();
    noecho();
    curs_set(0);
    refresh();

    win = newwin(WIN_HEIGHT, WIN_WIDTH, WIN_Y, WIN_X);

    box(win, 0, 0);
    wrefresh(win);
}

void view_end(void) {
    delwin(win);
    endwin();
}

void view_add_s(Snake *s, char head, char body, char dhead, char dbody) {
    sg.s = s;

    sg.s_prev = *s;
    sg.s_prev.x = malloc(sizeof(*(sg.s_prev.x)) * sg.s_prev.len);
    sg.s_prev.y = malloc(sizeof(*(sg.s_prev.y)) * sg.s_prev.len);
    memcpy(sg.s_prev.x, s->x, sizeof(*(sg.s_prev.x)) * sg.s_prev.len);
    memcpy(sg.s_prev.y, s->y, sizeof(*(sg.s_prev.y)) * sg.s_prev.len);
    sg.s_prev.head_x = sg.s_prev.x;
    sg.s_prev.head_y = sg.s_prev.y;

    sg.head = head;
    sg.body = body;
    sg.dhead = dhead;
    sg.dbody = dbody;
    sg.remove = false;
}

void view_add_f(Food *f, char look) {
    fg.f = f;
    fg.look = look;
    fg.remove = false;
}

void view_rm_s(Snake *s) {
    sg.remove = true;
}

void view_rm_f(Food *f) {
    fg.remove = true;
}

void view_update(void) {
    //mvwprintw(win, 0, 0, "cur len: %d   prev len: %d", sg.s->len, sg.s_prev.len);
    int i;

    if (fg.remove) {
        draw(fg.f->y, fg.f->x, ' ');
        fg.f = NULL;    // temp
        fg.remove = false;
    } else {
        draw(fg.f->y, fg.f->x, fg.f->eaten ? ' ' : fg.look);
    }

    for (i = 0; i < sg.s_prev.len; i++) {
//        mvwprintw(win, i, 0, "\n                     ");
//        mvwprintw(win, i, 0, "\r%d: %d %d", i + 1, sg.s_prev.x[i], sg.s_prev.y[i]);
        draw(sg.s_prev.y[i], sg.s_prev.x[i], ' ');
    }

    if (sg.remove) {
        sg.s = NULL;    // temp
        sg.remove = false;
    } else {
        if (sg.s->alive) {
//            mvwprintw(win, 0, 0, "\n                     ");
//            mvwprintw(win, 0, 0, "\r%d: %d %d", 1, sg.s->x[0], sg.s->y[0]);
            draw(*(sg.s->head_y), *(sg.s->head_x), sg.head);
            for (i = 1; i < sg.s->len; i++) {
//                mvwprintw(win, i, 0, "\n                     ");
//                mvwprintw(win, i, 0, "\r%d: %d %d", i + 1, sg.s->x[i], sg.s->y[i]);
                draw(sg.s->y[i], sg.s->x[i], sg.body);
            }
        } else {
            draw(*(sg.s->head_y), *(sg.s->head_x), sg.dhead);
            for (i = 1; i < sg.s->len; i++) {
                draw(sg.s->y[i], sg.s->x[i], sg.dbody);
            }
        }

        free(sg.s_prev.x);
        free(sg.s_prev.y);
        sg.s_prev = *(sg.s);
        sg.s_prev.x = malloc(sizeof(*(sg.s_prev.x)) * sg.s_prev.len);
        sg.s_prev.y = malloc(sizeof(*(sg.s_prev.y)) * sg.s_prev.len);
        memcpy(sg.s_prev.x, sg.s->x, sizeof(*(sg.s_prev.x)) * sg.s_prev.len);
        memcpy(sg.s_prev.y, sg.s->y, sizeof(*(sg.s_prev.y)) * sg.s_prev.len);
        sg.s_prev.head_x = sg.s_prev.x;
        sg.s_prev.head_y = sg.s_prev.y;
    }

    wrefresh(win);
}

