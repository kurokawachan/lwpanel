

#include <iostream>

#include "lwlaunchbar_config_dialog.hpp"
#include "lwlaunchbar_config_dialog_modify_data.hpp"
#include "lwlaunchbar_widget.hpp"

#include "lwlaunchbar_config_dialog_handle_user_event.hpp"

void handle_dialog_event_button_add_clicked(GtkButton *button_add, gpointer user_data)
{
    GtkWidget *dlg = (GtkWidget *)user_data;
    GtkWidget *tree_view = NULL;
    GtkWidget *defined_view = NULL;
    GtkWidget *content_holder = NULL;
    {
        lwlaunchbar_preferences_widget_struct *widget_data_pointer =
            (lwlaunchbar_preferences_widget_struct *)g_object_get_data(
                G_OBJECT(dlg),
                "lwlaunchbar_widget_data");

        tree_view = widget_data_pointer->tree_view;
        defined_view = widget_data_pointer->defined_view;
        content_holder = widget_data_pointer->instance;
    }

    add_data_from_right_to_left(GTK_TREE_VIEW(tree_view), GTK_TREE_VIEW(defined_view));

    g_debug("handle_dialog_event_button_add_clicked");
    save_data(dlg);
    update_content(content_holder);
}

void handle_dialog_event_button_remove_clicked(GtkButton *button_remove, gpointer user_data)
{
    GtkWidget *dlg = (GtkWidget *)user_data;
    GtkWidget *defined_view = NULL;
    GtkWidget *content_holder = NULL;
    {
        lwlaunchbar_preferences_widget_struct *widget_data_pointer =
            (lwlaunchbar_preferences_widget_struct *)g_object_get_data(
                G_OBJECT(dlg),
                "lwlaunchbar_widget_data");
        defined_view = widget_data_pointer->defined_view;
        content_holder = widget_data_pointer->instance;
    }

    remove_data_from_left_view(GTK_TREE_VIEW(defined_view));

    g_debug("handle_dialog_event_button_remove_clicked");
    save_data(dlg);
    update_content(content_holder);
}

void handle_dialog_event_tree_view_row_activated(
    GtkTreeView *tree_view,
    GtkTreePath *path,
    GtkTreeViewColumn *column,
    gpointer user_data)
{
    GtkWidget *dlg = (GtkWidget *)user_data;
    GtkWidget *defined_view = NULL;
    GtkWidget *content_holder = NULL;
    {
        lwlaunchbar_preferences_widget_struct *widget_data_pointer =
            (lwlaunchbar_preferences_widget_struct *)g_object_get_data(
                G_OBJECT(dlg),
                "lwlaunchbar_widget_data");
        defined_view = widget_data_pointer->defined_view;
        content_holder = widget_data_pointer->instance;
    }

    add_data_from_right_to_left(GTK_TREE_VIEW(tree_view), GTK_TREE_VIEW(defined_view));

    g_debug("handle_dialog_event_tree_view_row_activated");
    save_data(dlg);
    update_content(content_holder);
}

void handle_dialog_event_defined_view_row_activated(
    GtkTreeView *defined_view,
    GtkTreePath *path,
    GtkTreeViewColumn *column,
    gpointer user_data)
{
    GtkWidget *dlg = (GtkWidget *)user_data;
    GtkWidget *content_holder = NULL;
    {
        lwlaunchbar_preferences_widget_struct *widget_data_pointer =
            (lwlaunchbar_preferences_widget_struct *)g_object_get_data(
                G_OBJECT(dlg),
                "lwlaunchbar_widget_data");
        content_holder = widget_data_pointer->instance;
    }

    remove_data_from_left_view(GTK_TREE_VIEW(defined_view));

    g_debug("handle_dialog_event_defined_view_row_activated");
    save_data(dlg);
    update_content(content_holder);
}

void handle_dialog_event_button_up_clicked(
    GtkButton *button_up,
    gpointer user_data)
{
    GtkWidget *dlg = (GtkWidget *)user_data;
    GtkWidget *defined_view = NULL;
    GtkWidget *content_holder = NULL;
    {
        lwlaunchbar_preferences_widget_struct *widget_data_pointer =
            (lwlaunchbar_preferences_widget_struct *)g_object_get_data(
                G_OBJECT(dlg),
                "lwlaunchbar_widget_data");
        defined_view = widget_data_pointer->defined_view;
        content_holder = widget_data_pointer->instance;
    }

    move_data_up_by_one_for_left_view(GTK_TREE_VIEW(defined_view));

    g_debug("handle_dialog_event_button_up_clicked");
    save_data(dlg);
    update_content(content_holder);
}

void handle_dialog_event_button_down_clicked(
    GtkButton *button_down,
    gpointer user_data)
{
    GtkWidget *dlg = (GtkWidget *)user_data;
    GtkWidget *defined_view = NULL;
    GtkWidget *content_holder = NULL;
    {
        lwlaunchbar_preferences_widget_struct *widget_data_pointer =
            (lwlaunchbar_preferences_widget_struct *)g_object_get_data(
                G_OBJECT(dlg),
                "lwlaunchbar_widget_data");
        defined_view = widget_data_pointer->defined_view;
        content_holder = widget_data_pointer->instance;
    }

    move_data_down_by_one_for_left_view(GTK_TREE_VIEW(defined_view));

    g_debug("handle_dialog_event_button_down_clicked");
    save_data(dlg);
    update_content(content_holder);
}
