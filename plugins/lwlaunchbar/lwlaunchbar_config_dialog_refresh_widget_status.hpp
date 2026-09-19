

#ifndef LWLAUNCHBAR_CONFIG_DIALOG_REFRESH_WIDGET_STATUS_HPP /* Include guard */
#define LWLAUNCHBAR_CONFIG_DIALOG_REFRESH_WIDGET_STATUS_HPP

#include <gtk/gtk.h>

void refresh_widget_data_button_add(GtkTreeView *tree_view, gpointer user_data);
void refresh_widget_data_button_remove(GtkTreeView *defined_view, gpointer user_data);

void refresh_widget_data_button_up(GtkTreeView *defined_view, gpointer user_data);
void refresh_widget_data_button_down(GtkTreeView *defined_view, gpointer user_data);

void refresh_widget_data_label_menu_app_exec(GtkTreeView *tree_view, gpointer user_data);
void refresh_widget_data_label_def_app_exec(GtkTreeView *defined_view, gpointer user_data);

#endif // LWLAUNCHBAR_CONFIG_DIALOG_REFRESH_WIDGET_STATUS_HPP
