#include <gtk/gtk.h>
#include <gtk-layer-shell.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

static GtkWidget *clock_label;
static GtkWidget *window;

static gboolean update_clock(gpointer data) {
    time_t now = time(NULL);
    struct tm *timeinfo = localtime(&now);
    char time_str[10];
    strftime(time_str, sizeof(time_str), "%H:%M", timeinfo);
    gtk_label_set_text(GTK_LABEL(clock_label), time_str);
    return TRUE;
}

static void on_start_button_clicked(GtkWidget *widget, gpointer data) {
    system("wofi --show drun &");
}

static gboolean on_window_key_press(GtkWidget *widget, GdkEventKey *event, gpointer data) {
    if (event->keyval == GDK_KEY_super_l || event->keyval == GDK_KEY_super_r) {
        system("wofi --show drun &");
        return TRUE;
    }
    return FALSE;
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Daniel Taskbar");
    gtk_window_set_keep_below(GTK_WINDOW(window), TRUE);
    gtk_window_set_decorated(GTK_WINDOW(window), FALSE);
    gtk_window_set_default_size(GTK_WINDOW(window), 1920, 30);

    gtk_layer_init_for_window(GTK_WINDOW(window));
    gtk_layer_set_layer(GTK_WINDOW(window), GTK_LAYER_SHELL_LAYER_BOTTOM);
    gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_BOTTOM, TRUE);
    gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_LEFT, TRUE);
    gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_RIGHT, TRUE);
    gtk_layer_set_exclusive_zone(GTK_WINDOW(window), 30);

    GtkCssProvider *css_provider = gtk_css_provider_new();
    const char *css_data =
        "window {"
        "  background: linear-gradient(to bottom, #0078d4 0%, #1084d7 50%, #0a66bb 100%);"
        "  margin: 0;"
        "  padding: 0;"
        "}"
        "#start-button {"
        "  background: #00aa00;"
        "  color: white;"
        "  font-style: italic;"
        "  font-weight: bold;"
        "  font-size: 12px;"
        "  border: 1px solid #007700;"
        "  border-radius: 0px;"
        "  padding: 2px 8px;"
        "  margin: 3px 0px 0px 2px;"
        "}"
        "#start-button:hover {"
        "  background: #00cc00;"
        "}"
        "#start-button:active {"
        "  background: #008800;"
        "}"
        "#clock-label {"
        "  color: white;"
        "  font-size: 11px;"
        "  font-family: 'MS Sans Serif', 'Arial', sans-serif;"
        "  background: #1f5ba0;"
        "  padding: 0px 4px;"
        "  margin-right: 2px;"
        "}"
        "#tray-area {"
        "  background: #1f5ba0;"
        "  margin-right: 0px;"
        "  padding-right: 2px;"
        "}";

    gtk_css_provider_load_from_data(css_provider, css_data, -1, NULL);

    GdkScreen *screen = gdk_screen_get_default();
    gtk_style_context_add_provider_for_screen(screen, 
        GTK_STYLE_PROVIDER(css_provider), 
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_container_set_border_width(GTK_CONTAINER(main_box), 0);

    GtkWidget *start_button = gtk_button_new_with_label("Start");
    gtk_widget_set_name(start_button, "start-button");
    g_signal_connect(start_button, "clicked", G_CALLBACK(on_start_button_clicked), NULL);
    gtk_box_pack_start(GTK_BOX(main_box), start_button, FALSE, FALSE, 0);

    GtkWidget *spacer = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(main_box), spacer, TRUE, TRUE, 0);

    GtkWidget *tray_area = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_name(tray_area, "tray-area");

    clock_label = gtk_label_new("");
    gtk_widget_set_name(clock_label, "clock-label");
    gtk_box_pack_end(GTK_BOX(tray_area), clock_label, FALSE, FALSE, 0);

    gtk_box_pack_end(GTK_BOX(main_box), tray_area, FALSE, FALSE, 0);

    gtk_container_add(GTK_CONTAINER(window), main_box);

    g_signal_connect(window, "key-press-event", G_CALLBACK(on_window_key_press), NULL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    update_clock(NULL);
    g_timeout_add_seconds(1, update_clock, NULL);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
