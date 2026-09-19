

#ifndef LWLAUNCHBAR_CONFIG_DIALOG_HANDLE_USER_EVENT_HPP /* Include guard */
#define LWLAUNCHBAR_CONFIG_DIALOG_HANDLE_USER_EVENT_HPP

#include <gtk/gtk.h>

void handle_dialog_event_button_add_clicked(GtkButton *button_add, gpointer user_data);
void handle_dialog_event_button_remove_clicked(GtkButton *button_remove, gpointer user_data);
void handle_dialog_event_tree_view_row_activated(GtkTreeView *tree_view, GtkTreePath *path, GtkTreeViewColumn *column, gpointer user_data);
void handle_dialog_event_defined_view_row_activated(GtkTreeView *defined_view, GtkTreePath *path, GtkTreeViewColumn *column, gpointer user_data);
void handle_dialog_event_button_up_clicked(GtkButton *button_up, gpointer user_data);
void handle_dialog_event_button_down_clicked(GtkButton *button_down, gpointer user_data);

#endif // LWLAUNCHBAR_CONFIG_DIALOG_HANDLE_USER_EVENT_HPP
