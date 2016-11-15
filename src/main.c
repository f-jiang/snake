#include <unistd.h>
#include <ncurses.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>       /* for setitimer */
#include <unistd.h>     /* for pause */
#include <signal.h>     /* for signal */
#include <stdlib.h>

#include "main.h"
#include "gameobj.h"
#include "view.h"

//#include <time.h>

// 00, 01, 10, 11, 100
// (UP ^ 0x03) == DOWN
// (LEFT ^ 0x03)  == RIGHT
enum direction_t { UP, LEFT, RIGHT, DOWN, NONE };
char *dir_names[5] = { "up", "left", "right", "down", "none" };

int MAP_WIDTH;
int MAP_HEIGHT;

static struct itimerval it_val;
static int interval = 100;
static Snake *s = NULL;
static Food *f = NULL;
static int difficulty = 0;
static int score = 0;
static enum direction_t dir = NONE;
static enum direction_t dir_prev = NONE;
static int s_x = 0;
static int s_y = 0;

static int rand_int(int min, int max) {
    static bool ready = false;
    time_t t;

    if (!ready) {
        srand((unsigned) time(&t));
        ready = true;
    }

    return rand() % (max - min) + min;
}

static void timer_update(void) {
    it_val.it_value.tv_sec = interval / 1000;
    it_val.it_value.tv_usec = (interval * 1000) % 1000000;
    it_val.it_interval = it_val.it_value;

    if (setitimer(ITIMER_REAL, &it_val, NULL) == -1) {
      perror("error calling setitimer()");
      exit(1);
    }
}

static void timer_stop(void) {
    if (setitimer(ITIMER_REAL, NULL, NULL) == -1) {
      perror("error calling setitimer()");
      exit(1);
    }
}

static void loop(void) {
    if (dir == NONE) {
        dir = rand_int(0, 4);
    } else if (dir_prev != NONE && s->len > 1 && (dir ^ 0x03) == dir_prev) {
        dir = dir_prev;
    }

    switch (dir) {
        case UP:
            s_y++;
            break;
        case LEFT:
            s_x--;
            break;
        case RIGHT:
            s_x++;
            break;
        case DOWN:
            s_y--;
            break;
    }

    if (s_x > MAP_WIDTH - 1) {
        s_x = 0;
    } else if (s_x < 0) {
        s_x = MAP_WIDTH - 1;
    }

    if (s_y > MAP_HEIGHT - 1) {
        s_y = 0;
    } else if (s_y < 0) {
        s_y = MAP_HEIGHT - 1;
    }

    dir_prev = dir;

    if (s_x == f->x && s_y == f->y) {
        snake_grow(s);
        score++;        // temp
        difficulty++;   // temp
        interval--;     // temp
        view_rm_f(f);
        f->eaten = true;
    } else if (snake_touching(s, s_x, s_y)) {
        s->alive = false;
    }

    snake_move_to(s, s_x, s_y);
    view_update();
    timer_update();

    if (f->eaten) {
        food_del(&f);
        f = food_init(rand() % MAP_WIDTH, rand() % MAP_HEIGHT);
        view_add_f(f, '$');
    }
}

int main(int argc, char *argv[]) {
    MAP_WIDTH = 40;     // TODO init with command line args
    MAP_HEIGHT = 40;

    if (signal(SIGALRM, (void (*)(int)) loop) == SIG_ERR) {
      perror("Unable to catch SIGALRM");
      exit(1);
    }
    timer_update();

    s_x = rand_int(0, MAP_WIDTH);
    s_y = rand_int(0, MAP_HEIGHT);
    s = snake_init(s_x, s_y);
    f = food_init(rand() % MAP_WIDTH, rand() % MAP_HEIGHT);
    view_init();
    view_add_s(s, 'o', '*', '^', 'x');
    view_add_f(f, '$');
    view_update();

    keypad(stdscr, TRUE);
    int ch;
    while (s->alive) {
        ch = getch();
        switch (ch) {
            case KEY_LEFT:
                dir = LEFT;
                break;
            case KEY_RIGHT:
                dir = RIGHT;
                break;
            case KEY_UP:
                dir = UP;
                break;
            case KEY_DOWN:
                dir = DOWN;
                break;
            default:
                break;
        }

        view_update();
    }

    //timer_stop();

    view_rm_s(s);
    view_rm_f(f);

    snake_del(&s);
    food_del(&f);

    view_end();
    return 0;
}
