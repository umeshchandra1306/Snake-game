#include "snake.h"


gboolean on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer data)
 {
    (void)widget;  
    (void)data;

    switch (event->keyval)
     {
        case GDK_KEY_Up:
        case GDK_KEY_w:
        case GDK_KEY_W:
            gs.next_dir = DIR_UP;
            break;

        case GDK_KEY_Down:
        case GDK_KEY_s:
        case GDK_KEY_S:
            gs.next_dir = DIR_DOWN;
            break;

        case GDK_KEY_Left:
        case GDK_KEY_a:
        case GDK_KEY_A:
            gs.next_dir = DIR_LEFT;
            break;

        case GDK_KEY_Right:
        case GDK_KEY_d:
        case GDK_KEY_D:
            gs.next_dir = DIR_RIGHT;
            break;

        case GDK_KEY_p:
        case GDK_KEY_P:
            if (!gs.game_over) 
            {
                gs.paused = !gs.paused; 
                gtk_widget_queue_draw(canvas);
            }
            break;

        case GDK_KEY_r:
        case GDK_KEY_R: 
        {
            int saved_hi = gs.high_score;  
            game_init();                   
            gs.high_score = saved_hi;      
            break;
        }
        case GDK_KEY_q:
        case GDK_KEY_Q:
        case GDK_KEY_Escape:
            gtk_main_quit();
            break;
        default:
            break;
    }
    return TRUE;  
}
