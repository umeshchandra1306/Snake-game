#ifndef SNAKE_H
#define SNAKE_H

#include <gtk/gtk.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/* grid settings */
#define GRID_COLS 30
#define GRID_ROWS 30

/* size of each box */
#define CELL_SIZE 24

/* space around game */
#define BORDER_PAD 12

/* window size (calculated from grid) */
#define WINDOW_W (GRID_COLS * CELL_SIZE + BORDER_PAD * 2)
#define WINDOW_H (GRID_ROWS * CELL_SIZE + BORDER_PAD * 2 + 60)

/* game settings */
#define MAX_SNAKE (GRID_COLS * GRID_ROWS)
#define INITIAL_LEN 4
#define TICK_MS 140
#define SCORE_PER_FOOD 10

/* direction of snake */
typedef enum {
    DIR_UP,
    DIR_DOWN,
    DIR_LEFT,
    DIR_RIGHT
} Direction;

/* simple point (x, y) */
typedef struct {
    int x;
    int y;
} Point;

/* main game data */
typedef struct {

    Point body[MAX_SNAKE];  
    int length;             

    Direction dir;           
    Direction next_dir;     

    Point food;             

    int score;
    int high_score;

    gboolean running;       
    gboolean game_over;     
    gboolean paused;         

} GameState;

/* global variables */
extern GameState gs;
extern GtkWidget *canvas;
extern guint timer_id;

/* functions */

/* start / reset game */
void game_init(void);

/* create food randomly */
void place_food(void);

/* game loop */
gboolean game_tick(gpointer data);

/* draw everything */
gboolean on_draw(GtkWidget *widget, cairo_t *cr, gpointer data);

/* small helper for UI */
void draw_rounded_rect(cairo_t *cr, double x, double y,
                          double w, double h, double r);
/* keyboard input */
gboolean on_key_press(GtkWidget *widget,
    GdkEventKey *event,
    gpointer data);
#endif