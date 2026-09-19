

#ifndef LWLAUNCHBAR_CONFIG_DIALOG_HANDLE_WIDGET_EVENT_HPP /* Include guard */
#define LWLAUNCHBAR_CONFIG_DIALOG_HANDLE_WIDGET_EVENT_HPP

#include <gtk/gtk.h>

void handle_dialog_event_defined_view_list_store_row_inserted(GtkTreeModel *self, GtkTreePath *path, GtkTreeIter *iter, gpointer user_data);

void handle_dialog_event_defined_view_list_store_row_deleted(GtkTreeModel *self, GtkTreePath *path, gpointer user_data);
void handle_dialog_event_defined_view_list_store_rows_reordered(GtkTreeModel *self, GtkTreePath *path, GtkTreeIter *iter, gpointer new_order, gpointer user_data);

#endif // LWLAUNCHBAR_CONFIG_DIALOG_HANDLE_WIDGET_EVENT_HPP
