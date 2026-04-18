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

    // Background Window
    cairo_set_source_rgb(cr, 0.08, 0.09, 0.12);
    cairo_paint(cr);

    // Header
    cairo_set_source_rgb(cr, 0.10, 0.12, 0.17);
    cairo_rectangle(cr, 0, 0, W, 55);
    cairo_fill(cr);

    // Title name
    cairo_select_font_face(cr, "Monospace", CAIRO_FONT_SLANT_NORMAL, 
                            CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr, 20);
    cairo_set_source_rgb(cr, 0.35, 0.90, 0.45);
    cairo_move_to(cr, BORDER_PAD, 36);
    cairo_show_text(cr, "SNAKE GAME");

    // Current Score Display
    char score[64];    
    snprintf(score, sizeof(score), "SCORE: %d", gs.score);
    cairo_set_font_size(cr, 14);
    cairo_set_source_rgb(cr, 0.85, 0.85, 0.85);
    cairo_text_extents(cr, score, &te);
    cairo_move_to(cr, W/2 - te.width/2, 34);
    cairo_show_text(cr, score);

    // High Score Display
    char hi_score[64];
    snprintf(hi_score, sizeof(hi_score), "BEST: %d", gs.high_score);
    cairo_text_extents(cr,hi_score, &te);
    cairo_set_source_rgb(cr, 0.70, 0.55, 0.90); // purple
    cairo_move_to(cr, W - BORDER_PAD - te.width, 34);
    cairo_show_text(cr, hi_score);

    // Grid Background

    draw_rounded_rect(cr, gx - 2, gy - 2, gw + 4, gh + 4, 6);
    cairo_set_source_rgb(cr, 0.13, 0.16, 0.22); // dark blue-grey
    cairo_fill(cr);

    // Grid lines
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

    // Food
    double fx = gx + gs.food.x * CELL_SIZE + 2;
    double fy = gy + gs.food.y * CELL_SIZE + 2;
    double fs = CELL_SIZE - 4;

    //glow effect - not done - not preferred

    draw_rounded_rect(cr, fx, fy, fs, fs, fs/2);
    cairo_set_source_rgb(cr, 0.95, 0.25, 0.30);
    cairo_fill(cr);

    // Snake Body
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

        // Eyes on head
        if (i == 0) {
        
            double ex1, ey1, ex2, ey2;
            double ew = sw * 0.18;  

            switch (gs.dir) {
                case DIR_RIGHT:
                    ex1 = sx + sw*0.72; ey1 = sy + sw*0.25;
                    ex2 = sx + sw*0.72; ey2 = sy + sw*0.65;
                    break;
                case DIR_LEFT:
                    ex1 = sx + sw*0.12; ey1 = sy + sw*0.25;
                    ex2 = sx + sw*0.12; ey2 = sy + sw*0.65;
                    break;
                case DIR_UP:
                    ex1 = sx + sw*0.25; ey1 = sy + sw*0.12;
                    ex2 = sx + sw*0.65; ey2 = sy + sw*0.12;
                    break;
                default: 
                    ex1 = sx + sw*0.25; ey1 = sy + sw*0.75;
                    ex2 = sx + sw*0.65; ey2 = sy + sw*0.75;
                    break;
            }

            // Dark eye base 
            cairo_set_source_rgb(cr, 0.05, 0.05, 0.05);
            cairo_arc(cr, ex1, ey1, ew, 0, 2*G_PI); cairo_fill(cr);
            cairo_arc(cr, ex2, ey2, ew, 0, 2*G_PI); cairo_fill(cr);

            // White pupil 
            cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
            cairo_arc(cr, ex1 + ew*0.3, ey1 - ew*0.3, ew*0.4, 0, 2*G_PI);
            cairo_fill(cr);
            cairo_arc(cr, ex2 + ew*0.3, ey2 - ew*0.3, ew*0.4, 0, 2*G_PI);
            cairo_fill(cr);
        }
    }
    if (gs.paused && !gs.game_over) {
        cairo_set_source_rgba(cr, 0, 0, 0, 0.55);
        cairo_rectangle(cr, gx, gy, gw, gh);
        cairo_fill(cr);

        cairo_select_font_face(cr, "Monospace",
                               CAIRO_FONT_SLANT_NORMAL,
                               CAIRO_FONT_WEIGHT_BOLD);
        cairo_set_font_size(cr, 30);
        cairo_set_source_rgb(cr, 0.95, 0.85, 0.25);  /* Yellow */
        const char *pt = "PAUSED";
        cairo_text_extents(cr, pt, &te);
        cairo_move_to(cr, gx + gw/2 - te.width/2,
                          gy + gh/2 + te.height/2);
        cairo_show_text(cr, pt);

        cairo_set_font_size(cr, 13);
        cairo_set_source_rgb(cr, 0.75, 0.75, 0.75);
        const char *hint = "Press P to resume";
        cairo_text_extents(cr, hint, &te);
        cairo_move_to(cr, gx + gw/2 - te.width/2,
                          gy + gh/2 + te.height/2 + 30);
        cairo_show_text(cr, hint);
    }
 
    if (gs.game_over) {
        cairo_set_source_rgba(cr, 0.0, 0.0, 0.0, 0.65);
        cairo_rectangle(cr, gx, gy, gw, gh);
        cairo_fill(cr);

        draw_rounded_rect(cr, gx + gw/2 - 120,
                              gy + gh/2 - 65, 240, 130, 12);
        cairo_set_source_rgba(cr, 0.12, 0.14, 0.20, 0.96);
        cairo_fill(cr);

        draw_rounded_rect(cr, gx + gw/2 - 120,
                              gy + gh/2 - 65, 240, 130, 12);
        cairo_set_source_rgba(cr, 0.90, 0.25, 0.30, 0.9);
        cairo_set_line_width(cr, 2);
        cairo_stroke(cr);

        cairo_select_font_face(cr, "Monospace",
                               CAIRO_FONT_SLANT_NORMAL,
                               CAIRO_FONT_WEIGHT_BOLD);
        cairo_set_font_size(cr, 26);
        cairo_set_source_rgb(cr, 0.95, 0.25, 0.30);
        const char *go = "GAME OVER";
        cairo_text_extents(cr, go, &te);
        cairo_move_to(cr, gx + gw/2 - te.width/2, gy + gh/2 - 20);
        cairo_show_text(cr, go);

        char fs_buf[64];
        snprintf(fs_buf, sizeof(fs_buf), "Score: %d", gs.score);
        cairo_set_font_size(cr, 14);
        cairo_set_source_rgb(cr, 0.85, 0.85, 0.85);
        cairo_text_extents(cr, fs_buf, &te);
        cairo_move_to(cr, gx + gw/2 - te.width/2, gy + gh/2 + 8);
        cairo_show_text(cr, fs_buf);

        cairo_set_font_size(cr, 12);
        cairo_set_source_rgb(cr, 0.55, 0.80, 0.55);
        const char *restart = "Press R to play again";
        cairo_text_extents(cr, restart, &te);
        cairo_move_to(cr, gx + gw/2 - te.width/2, gy + gh/2 + 34);
        cairo_show_text(cr, restart);
    }
    if (!gs.game_over) {
        cairo_set_font_size(cr, 10);
        cairo_set_source_rgba(cr, 0.45, 0.45, 0.55, 0.8);
        const char *hint =
            "Arrow Keys / WASD  ·  P = Pause  ·  R = Restart  ·  Q = Quit";
        cairo_text_extents(cr, hint, &te);
        cairo_move_to(cr, W/2 - te.width/2, H - 6);
        cairo_show_text(cr, hint);
    }

    return FALSE;
    }