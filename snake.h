#ifndef SNAKE_H   
#define SNAKE_H

#include <gtk/gtk.h>   
#include <stdlib.h>    
#include <time.h>      
#include <string.h>    


#define GRID_COLS   25          
#define GRID_ROWS   25          
#define CELL_SIZE   24         
#define BORDER_PAD  12

/* Derived window dimensions  */
#define WINDOW_W  (GRID_COLS * CELL_SIZE + BORDER_PAD * 2)
#define WINDOW_H  (GRID_ROWS * CELL_SIZE + BORDER_PAD * 2 + 60)

//    GAME BEHAVIOUR CONSTANTS

#define MAX_SNAKE    (GRID_COLS * GRID_ROWS)  
#define INITIAL_LEN  4                        
#define TICK_MS      140                      
#define SCORE_PER_FOOD 10                     

/* DIRECTION ENUM */
typedef enum {
    DIR_UP,     
    DIR_DOWN,   
    DIR_LEFT,   
    DIR_RIGHT   
} Direction;

/* POINT STRUCT */
typedef struct {
    int x;   /* Column index  */
    int y;   /* Row index   */
} Point;

/* GAME STATE STRUCT */
typedef struct {
    Point     body[MAX_SNAKE]; 
    int       length;          
    Direction dir;             
    Direction next_dir;        
    Point     food;            
    int       score;           
    int       high_score;      
    gboolean  running;         
    gboolean  game_over;       
    gboolean  paused;          /
} GameState;

/* GLOBAL VARIABLE DECLARATIONS */
extern GameState  gs;       
extern GtkWidget *canvas;   
extern guint      timer_id; 

/* 
   FUNCTION PROTOTYPES
   Declarations of all functions defined across modules.
    */

/*   structs.c   */
void game_init(void);
void place_food(void);

/*  logic.c   */
gboolean game_tick(gpointer data);

/*   ui.c   */
gboolean on_draw(GtkWidget *widget, cairo_t *cr, gpointer data);
void     draw_rounded_rect(cairo_t *cr, double x, double y,
                            double w, double h, double r);

/*  input.c   */
gboolean on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer data);

#endif /* SNAKE_H */