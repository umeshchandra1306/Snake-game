 #include "snake.h"

void game_init() {

    memset(&gs, 0, sizeof(gs));

    gs.length = INITIAL_LEN; 

    gs.dir      = DIR_RIGHT;  
    gs.next_dir = DIR_RIGHT;  

    int cx = GRID_COLS / 2;  
    int cy = GRID_ROWS / 2;  

    for (int i = 0; i < gs.length; i++) {
        gs.body[i].x = cx - i;  
        gs.body[i].y = cy;       
    }

    place_food();
   
    gs.running   = TRUE;   
    gs.game_over = FALSE;  
    gs.paused    = FALSE;  
    gs.score     = 0;      

}

void place_food(void) {

    while (1) { 
        int hx = rand() % GRID_COLS;  
        int hy = rand() % GRID_ROWS;  

        gboolean on_snake = FALSE;

        for (int i = 0; i < gs.length; i++) {
            if (gs.body[i].x == hx && gs.body[i].y == hy) {
                on_snake = TRUE;  
                break;
            }
        }

        if (!on_snake) {
            gs.food.x = hx;
            gs.food.y = hy;
            return; 
        }

      
    }
}
