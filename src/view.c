#include "view.h"

#include <stdlib.h>     // malloc(), free()
#include <stdbool.h>
#include <string.h>     // memcpy()
#include <stddef.h>     // size_t
#include <ncurses.h>

#include "main.h"       // MAP_WIDTH, MAP_HEIGHT

#define WIN_WIDTH        (MAP_WIDTH + 2)
#define WIN_HEIGHT       (MAP_HEIGHT + 2)
#define WIN_X            ((COLS - WIN_WIDTH) / 2)
#define WIN_Y            ((LINES - WIN_HEIGHT) / 2)

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

static WINDOW *win;

static bool new_score, new_msg;
static char *score, *msg;
static size_t score_len, msg_len, prev_msg_len;

static void draw(int y, int x, char c) {
    mvwaddch(win, (WIN_HEIGHT - 1) - (y + 1), x + 1, c);
}

static void snake_draw(const Snake *s, bool clear) {
    char head, body;

    if (clear) { 
        head = body = ' ';
    } else if (s->alive) {
        head = sg.head;
        body = sg.body;
    } else {
        head = sg.dhead;
        body = sg.dbody;
    }

    draw(*(s->head_y), *(s->head_x), head);

    int i;
    for (i = 1; i < s->len; i++) {
        draw(s->y[i], s->x[i], body);
    }
}

static void food_draw(const Food *f, bool clear) {
    draw(fg.f->y, fg.f->x, (fg.f->eaten || clear) ? ' ' : fg.look);
}

static void s_prev_update(const Snake *s) {
    free(sg.s_prev.x);
    free(sg.s_prev.y);

    sg.s_prev = *s;
    sg.s_prev.x = malloc(sizeof(*(sg.s_prev.x)) * sg.s_prev.len);
    sg.s_prev.y = malloc(sizeof(*(sg.s_prev.y)) * sg.s_prev.len);
    memcpy(sg.s_prev.x, s->x, sizeof(*(sg.s_prev.x)) * sg.s_prev.len);
    memcpy(sg.s_prev.y, s->y, sizeof(*(sg.s_prev.y)) * sg.s_prev.len);
    sg.s_prev.head_x = sg.s_prev.x;
    sg.s_prev.head_y = sg.s_prev.y;
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

    s_prev_update(s);

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

void view_print_score(int val) {
    char buffer[5];
    new_score = true;
    score_len = sprintf(buffer, "%d", val);
    score = buffer;
}

void view_print_ctr(char *str) {
    new_msg = true;
    prev_msg_len = msg_len;
    msg_len = strlen(str);
    msg = str;
}

void view_update(void) {
    if (fg.remove) {
        food_draw(fg.f, true);

        fg.f = NULL;
        fg.remove = false;
    } else if (fg.f) {
        food_draw(fg.f, false);
    }

    if (sg.remove) {
        snake_draw(sg.s, true);

        free(sg.s_prev.x);
        free(sg.s_prev.y);
        sg.s = NULL;
        sg.remove = false;
    } else if (sg.s) {
        snake_draw(&sg.s_prev, true);
        snake_draw(sg.s, false);

        s_prev_update(sg.s);
    }

//    if (new_score) {
//        new_score = false;
//        // BUG printing random chars instead of actual score
//        mvwaddnstr(win, 0, WIN_WIDTH - score_len, score, score_len);
//    }

    if (new_msg) {
        new_msg = false;

        // TODO dynamic string of length |prev_msg_len|
        mvwaddnstr(win, WIN_HEIGHT / 2, (WIN_WIDTH - prev_msg_len) / 2, "                                ", prev_msg_len);

        mvwaddnstr(win, WIN_HEIGHT / 2, (WIN_WIDTH - msg_len) / 2, msg, msg_len);
    }

    wrefresh(win);
}

