

#ifndef LWLAUNCHBAR_CONFIG_DIALOG_APP_VIEW_HPP /* Include guard */
#define LWLAUNCHBAR_CONFIG_DIALOG_APP_VIEW_HPP

#include <gtk/gtk.h>

void setup_tree_view_column(GtkWidget *tree_view);
void setup_tree_store(GtkWidget *tree_view);
void load_data_into_tree_store(GtkWidget *tree_view);

#endif // LWLAUNCHBAR_CONFIG_DIALOG_APP_VIEW_HPP
