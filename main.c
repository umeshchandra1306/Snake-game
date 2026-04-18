#include "snake.h"

// globals
GameState gs;
GtkWidget *canvas;
guint timer_id = 0;

int main(int argc, char *argv[])
{

    srand((unsigned)time(NULL));
    gtk_init(&argc, &argv);

    // main window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Snake Game — GTK3");
    gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_W, WINDOW_H);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // canva setup
    canvas = gtk_drawing_area_new();
    gtk_widget_set_size_request(canvas, WINDOW_W, WINDOW_H);
    gtk_container_add(GTK_CONTAINER(window), canvas);

    g_signal_connect(canvas, "draw", G_CALLBACK(on_draw), NULL);

    gtk_widget_add_events(window, GDK_KEY_PRESS_MASK);
    g_signal_connect(window, "key-press-event", G_CALLBACK(on_key_press), NULL);

    game_init();

    timer_id = g_timeout_add(TICK_MS, game_tick, NULL);

    gtk_widget_show_all(window);

    gtk_main();

    if (timer_id)
        g_source_remove(timer_id);

    return 0;
}
