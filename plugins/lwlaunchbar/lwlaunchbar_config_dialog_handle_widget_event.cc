

#include "lwlaunchbar_config_dialog.hpp"
#include "lwlaunchbar_config_dialog_refresh_widget_status.hpp"

#include "lwlaunchbar_config_dialog_handle_widget_event.hpp"

void handle_dialog_event_defined_view_list_store_row_inserted(
    GtkTreeModel *self,
    GtkTreePath *path,
    GtkTreeIter *iter,
    gpointer user_data)
{
    GtkWidget *dlg = (GtkWidget *)user_data;
    GtkWidget *defined_view = NULL;
    GtkWidget *button_up = NULL;
    GtkWidget *button_down = NULL;
    {
        lwlaunchbar_preferences_widget_struct *widget_data_pointer =
            (lwlaunchbar_preferences_widget_struct *)g_object_get_data(
                G_OBJECT(dlg),
                "lwlaunchbar_widget_data");
        defined_view = widget_data_pointer->defined_view;
        button_up = widget_data_pointer->button_up;
        button_down = widget_data_pointer->button_down;
    }

    refresh_widget_data_button_up(GTK_TREE_VIEW(defined_view), button_up);
    refresh_widget_data_button_down(GTK_TREE_VIEW(defined_view), button_down);
}

void handle_dialog_event_defined_view_list_store_row_deleted(
    GtkTreeModel *self,
    GtkTreePath *path,
    gpointer user_data)
{
    GtkWidget *dlg = (GtkWidget *)user_data;
    GtkWidget *defined_view = NULL;
    GtkWidget *button_up = NULL;
    GtkWidget *button_down = NULL;
    {
        lwlaunchbar_preferences_widget_struct *widget_data_pointer =
            (lwlaunchbar_preferences_widget_struct *)g_object_get_data(
                G_OBJECT(dlg),
                "lwlaunchbar_widget_data");
        defined_view = widget_data_pointer->defined_view;
        button_up = widget_data_pointer->button_up;
        button_down = widget_data_pointer->button_down;
    }

    refresh_widget_data_button_up(GTK_TREE_VIEW(defined_view), button_up);
    refresh_widget_data_button_down(GTK_TREE_VIEW(defined_view), button_down);
}

void handle_dialog_event_defined_view_list_store_rows_reordered(
    GtkTreeModel *self,
    GtkTreePath *path,
    GtkTreeIter *iter,
    gpointer new_order,
    gpointer user_data)
{
    GtkWidget *dlg = (GtkWidget *)user_data;
    GtkWidget *defined_view = NULL;
    GtkWidget *button_up = NULL;
    GtkWidget *button_down = NULL;
    {
        lwlaunchbar_preferences_widget_struct *widget_data_pointer =
            (lwlaunchbar_preferences_widget_struct *)g_object_get_data(
                G_OBJECT(dlg),
                "lwlaunchbar_widget_data");
        defined_view = widget_data_pointer->defined_view;
        button_up = widget_data_pointer->button_up;
        button_down = widget_data_pointer->button_down;
    }

    refresh_widget_data_button_up(GTK_TREE_VIEW(defined_view), button_up);
    refresh_widget_data_button_down(GTK_TREE_VIEW(defined_view), button_down);
}
