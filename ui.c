#include "snake.h"

void draw_rounded_rect(cairo_t *cr, double x, double y, double w, double h, double r){
    cairo_new_sub_path(cr);
    cairo_arc(cr, x + w - r, y + r, r, -G_PI/2, 0);
    cairo_arc(cr, x + w - r, y + h + r, r, 0, G_PI/2);
    cairo_arc(cr, x + r, y + h - r, r, G_PI/2, G_PI);
    cairo_arc(cr, x + r, y + r, r, G_PI, 3*G_PI/2);
    cairo_close_path(cr);
}

gboolean on_draw(GtkWidget *widget, cairo_t *cr, gpointer data){
    (void)widget; (void)data;

    int W = WINDOW_W;
    int H = WINDOW_H;

    double gx = BORDER_PAD;
    double gy = 55 + BORDER_PAD/2;
    double gw = GRID_COLS*CELL_SIZE;
    double gh = GRID_ROWS*CELL_SIZE;

    cairo_text_extents_t te;

    // WINDOW BACKGROUND
    cairo_set_source_rgb(cr, 0.08, 0.09, 0.12);
    cairo_paint(cr);

    // HEADER BAR
    cairo_set_source_rgb(cr, 0.10, 0.12, 0.17);
    cairo_rectangle(cr, 0, 0, W, 55);
    cairo_fill(cr);

    // TITLE NAME
    cairo_select_font_face(cr, "Monospace", CAIRO_FONT_SLANT_NORMAL, 
                            CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr, 20);
    cairo_set_source_rgb(cr, 0.35, 0.90, 0.45);
    cairo_move_to(cr, BORDER_PAD, 36);
    cairo_show_text(cr, "SNAKE GAME");

    // CURRENT SCORE DISPLAY
    char score[64];    
    snprintf(score, sizeof(score), "SCORE: %d", gs.score);
    cairo_set_font_size(cr, 14);
    cairo_set_source_rgb(cr, 0.85, 0.85, 0.85);
    cairo_text_extents(cr, score, &te);
    cairo_move_to(cr, W/2 - te.width/2, 34);
    cairo_show_text(cr, score);

    // HIGH SCORE DISPLAY
    char hi_score[64];
    snprintf(hi_score, sizeof(hi_score), "BEST: %d", gs.high_score);
    cairo_text_extents(cr,hi_score, &te);
    cairo_set_source_rgb(cr, 0.70, 0.55, 0.90); // purple
    cairo_move_to(cr, W - BORDER_PAD - te.width, 34);
    cairo_show_text(cr, hi_score);

    // GRID BACKGROUND

    draw_rounded_rect(cr, gx - 2, gy - 2, gw + 4, gh + 4, 6);
    cairo_set_source_rgb(cr, 0.13, 0.16, 0.22); // dark blue-grey
    cairo_fill(cr);

    // GRID LINES
    cairo_set_line_width(cr, 0.4);
    cairo_set_source_rgba(cr, 1.0, 1.0, 1.0, 0.04);
    for (int c = 0; c <= GRID_COLS; c++) {
        cairo_move_to(cr, gx + c * CELL_SIZE, gy);
        cairo_line_to(cr, gx + c * CELL_SIZE, gy + gh);
    }
    for (int r = 0; r <= GRID_ROWS; r++) {
        cairo_move_to(cr, gx, gy + r * CELL_SIZE);
        cairo_line_to(cr, gx + gw, gy + r * CELL_SIZE);
    }
    cairo_stroke(cr);

    // FOOD
    double fx = gx + gs.food.x * CELL_SIZE + 2;
    double fy = gy + gs.food.y * CELL_SIZE + 2;
    double fs = CELL_SIZE - 4;

    //glow effect - not done - not preferred

    draw_rounded_rect(cr, fx, fy, fs, fs, fs/2);
    cairo_set_source_rgb(cr, 0.95, 0.25, 0.30);
    cairo_fill(cr);

    // SNAKE BODY
    for (int i = gs.length - 1; i >= 0; i--)
    {
        double sx = gx + gs.body[i].x * CELL_SIZE + 1.5;
        double sy = gy + gs.body[i].y * CELL_SIZE + 1.5;
        double sw = CELL_SIZE - 3;

        double t = (gs.length > 1)? (double)(gs.length - 1 - i)/(gs.length -1):0.0;

        if (i=0) // head part
        {
            cairo_set_source_rgb(cr, 0.25, 0.92, 0.42);
        }
        else{
            double r = 0.15 + (1 - t) * 0.20;
            double g = 0.75 - t * 0.30;
            double b = 0.35 + t * 0.20;
            cairo_set_source_rgb(cr, r, g, b);
        }
        
        draw_rounded_rect(cr, sx, sy, sw, sw, (i == 0) ? 6 : 4);
        cairo_fill(cr);

        // EYES ON HEAD

        
    }
    
    
}