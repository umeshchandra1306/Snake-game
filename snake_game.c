#include <gtk/gtk.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/* Game Constants */
#define GRID_COLS      25
#define GRID_ROWS      25
#define CELL_SIZE      24
#define BORDER_PAD     12

#define WINDOW_W  (GRID_COLS * CELL_SIZE + BORDER_PAD * 2)
#define WINDOW_H  (GRID_ROWS * CELL_SIZE + BORDER_PAD * 2 + 60)

#define MAX_SNAKE   (GRID_COLS * GRID_ROWS)
#define INITIAL_LEN  4
#define TICK_MS      140   /* milliseconds per game tick */

/*  Direction Enum  */
typedef enum { DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT } Direction;

/*  Point Struct  */
typedef struct { int x, y; } Point;

/*  Game State  */
typedef struct {
    Point     body[MAX_SNAKE];
    int       length;
    Direction dir;
    Direction next_dir;   /* buffered direction from keypress */
    Point     food;
    int       score;
    int       high_score;
    gboolean  running;
    gboolean  game_over;
    gboolean  paused;
} GameState;

/*  Globals  */
static GameState  gs;
static GtkWidget *canvas;
static guint      timer_id = 0;

/*  Prototypes  */
static void       game_init        (void);
static void       place_food       (void);
static gboolean   game_tick        (gpointer data);
static gboolean   on_draw          (GtkWidget *widget, cairo_t *cr, gpointer data);
static gboolean   on_key_press     (GtkWidget *widget, GdkEventKey *event, gpointer data);
static void       draw_rounded_rect(cairo_t *cr, double x, double y,
                                    double w, double h, double r);