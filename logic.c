#include "snake.h"
/*move → check collisions → eat food → redraw*/
gboolean game_tick(gpointer data) {
    (void)data;  
    if (!gs.running || gs.game_over || gs.paused)
        return G_SOURCE_CONTINUE;

    //   STEP 1 — Apply buffered direction
       
    Direction nd = gs.next_dir;

    if ((nd == DIR_UP    && gs.dir != DIR_DOWN)  ||
        (nd == DIR_DOWN  && gs.dir != DIR_UP)    ||
        (nd == DIR_LEFT  && gs.dir != DIR_RIGHT) ||
        (nd == DIR_RIGHT && gs.dir != DIR_LEFT)) {
        gs.dir = nd;  /* Safe to apply — not a reversal */
    }

    //   STEP 2 — Calculate new head position
     //  Start from the current head 
    Point new_head = gs.body[0]; 

    switch (gs.dir) {
        case DIR_UP:    new_head.y--; break;  // y decreases going up    
        case DIR_DOWN:  new_head.y++; break;  // y increases going down  
        case DIR_LEFT:  new_head.x--; break;  // x decreases going left  
        case DIR_RIGHT: new_head.x++; break;  // x increases going right 
    }

    // STEP 3 — Wall collision detection
       
        
    if (new_head.x < 0 || new_head.x >= GRID_COLS ||
        new_head.y < 0 || new_head.y >= GRID_ROWS) {

        // Snake hit a wall — game over 
        gs.game_over = TRUE;

        if (gs.score > gs.high_score)
            gs.high_score = gs.score;

        gtk_widget_queue_draw(canvas);
        return G_SOURCE_CONTINUE;
    }

     
    //   STEP 4 — Self collision detection
 
    for (int i = 0; i < gs.length - 1; i++) {
        if (gs.body[i].x == new_head.x &&
            gs.body[i].y == new_head.y) {

            // Snake bit itself — game over 
            gs.game_over = TRUE;

            if (gs.score > gs.high_score)
                gs.high_score = gs.score;

            gtk_widget_queue_draw(canvas);
            return G_SOURCE_CONTINUE;
        }
    }

    
    //   STEP 5 — Check if snake eats food

    gboolean ate = (new_head.x == gs.food.x &&
                    new_head.y == gs.food.y);

    
    //   STEP 6 — Move the snake body

    if (!ate) {
       
        memmove(&gs.body[1], &gs.body[0],
                (gs.length - 1) * sizeof(Point));
    } else {
        // Snake ate food — grow by one segment.
          
        if (gs.length < MAX_SNAKE) {
            memmove(&gs.body[1], &gs.body[0],
                    gs.length * sizeof(Point));
            gs.length++;              // Snake is now one longer  
        }
        gs.score += SCORE_PER_FOOD;   // Add points               
        place_food();                
    }

    // Place the new head at position 0 
    gs.body[0] = new_head;

 
      // STEP 7 — Request a redraw of the canvas
     //  GTK will call on_draw() (in ui.c) to repaint the screen.
      
    gtk_widget_queue_draw(canvas);

    return G_SOURCE_CONTINUE;  // Keep the timer firing 
}
