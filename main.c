#include "snake.h"

GameState gs;
GtkWidget *canvas;
guint timer_id = 0;

int main(int argc, char *argv[])
{

    srand((unsigned)time(NULL));
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_window_set_title(GTK_WINDOW(window), "Snake Game — GTK3");

    gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_W, WINDOW_H);

    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // updated
}
