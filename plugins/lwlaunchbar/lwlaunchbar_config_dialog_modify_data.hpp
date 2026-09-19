

#ifndef LWLAUNCHBAR_CONFIG_DIALOG_MODIFY_DATA_HPP /* Include guard */
#define LWLAUNCHBAR_CONFIG_DIALOG_MODIFY_DATA_HPP

#include <gtk/gtk.h>

void add_data_from_right_to_left(GtkTreeView *tree_view_right, GtkTreeView *tree_view_left);
void remove_data_from_left_view(GtkTreeView *defined_view);
void move_data_up_by_one_for_left_view(GtkTreeView *defined_view);
void move_data_down_by_one_for_left_view(GtkTreeView *defined_view);

#endif // LWLAUNCHBAR_CONFIG_DIALOG_MODIFY_DATA_HPP
