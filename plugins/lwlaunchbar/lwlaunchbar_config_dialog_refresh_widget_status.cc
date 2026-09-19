

// TODO fix me
#define GMENU_I_KNOW_THIS_IS_UNSTABLE
#include <gmenu-tree.h>

#include "lwlaunchbar_config_dialog.hpp"

#include "lwlaunchbar_config_dialog_refresh_widget_status.hpp"

//
// This is used by "add" button and "remove" button
//
static void refresh_widget_data_button(GtkTreeView *tree_view, GtkWidget *button)
{
    // The returned data is owned by the instance.
    GtkTreeSelection *selection = gtk_tree_view_get_selection(tree_view);

    GtkTreeModel *model = NULL;
    GtkTreeIter iter;
    // "model"
    // The returned data is owned by the instance.
    // "iter"
    // The returned data is owned by the instance.
    gboolean is_selected = gtk_tree_selection_get_selected(selection, &model, &iter);

    if (is_selected == false)
    {
        gtk_widget_set_sensitive(button, false);
        return;
    }

    // "GMenuTreeItemType" is "typedef enum"
    GMenuTreeItemType type = get_model_item_menu_type(model, &iter);
    if (type != GMENU_TREE_ITEM_ENTRY)
    {
        gtk_widget_set_sensitive(button, false);
        return;
    }
    gtk_widget_set_sensitive(button, true);
    return;
}

//
// Refresh the status of "add" button sensitive or not
//
// https://docs.gtk.org/gtk3/method.Widget.set_sensitive.html
// A widget is sensitive if the user can interact with it.
//
void refresh_widget_data_button_add(GtkTreeView *tree_view, gpointer user_data)
{
    GtkWidget *button_add = (GtkWidget *)user_data;
    refresh_widget_data_button(tree_view, button_add);
}

//
// Refresh the status of "remove" button sensitive or not
//
// https://docs.gtk.org/gtk3/method.Widget.set_sensitive.html
// A widget is sensitive if the user can interact with it.
//
void refresh_widget_data_button_remove(GtkTreeView *defined_view, gpointer user_data)
{
    GtkWidget *button_remove = (GtkWidget *)user_data;
    refresh_widget_data_button(defined_view, button_remove);
}

//
// Refresh the status of "up" button sensitive or not
//
// https://docs.gtk.org/gtk3/method.Widget.set_sensitive.html
// A widget is sensitive if the user can interact with it.
//
void refresh_widget_data_button_up(GtkTreeView *defined_view, gpointer user_data)
{
    GtkWidget *button_up = (GtkWidget *)user_data;

    // The returned data is owned by the instance.
    GtkTreeSelection *selection = gtk_tree_view_get_selection(defined_view);

    GtkTreeModel *model = NULL;
    GtkTreeIter iter;
    // "model"
    // The returned data is owned by the instance.
    // "iter"
    // The returned data is owned by the instance.
    gboolean is_selected = gtk_tree_selection_get_selected(selection, &model, &iter);
    if (is_selected == false)
    {
        gtk_widget_set_sensitive(button_up, false);
        return;
    }

    // gint number_of_item = gtk_tree_model_iter_n_children(model, NULL);
    gint index = get_indices(model, &iter);

    if (index == 0)
    {
        gtk_widget_set_sensitive(button_up, false);
        return;
    }

    gtk_widget_set_sensitive(button_up, true);
    return;
}

//
// Refresh the status of "down" button sensitive or not
//
// https://docs.gtk.org/gtk3/method.Widget.set_sensitive.html
// A widget is sensitive if the user can interact with it.
//
void refresh_widget_data_button_down(GtkTreeView *defined_view, gpointer user_data)
{
    GtkWidget *button_down = (GtkWidget *)user_data;

    // The returned data is owned by the instance.
    GtkTreeSelection *selection = gtk_tree_view_get_selection(defined_view);

    GtkTreeModel *model = NULL;
    GtkTreeIter iter;
    // "model"
    // The returned data is owned by the instance.
    // "iter"
    // The returned data is owned by the instance.
    gboolean is_selected = gtk_tree_selection_get_selected(selection, &model, &iter);
    if (is_selected == false)
    {
        gtk_widget_set_sensitive(button_down, false);
        return;
    }

    gint number_of_item = gtk_tree_model_iter_n_children(model, NULL);
    gint index = get_indices(model, &iter);

    if (index == (number_of_item - 1))
    {
        gtk_widget_set_sensitive(button_down, false);
        return;
    }

    gtk_widget_set_sensitive(button_down, true);
    return;
}

//
// Use desktop_id to get the description of the app
//
static const std::string get_app_info_description(const std::string &desktop_id)
{
    std::string result;
    GDesktopAppInfo *app_info = g_desktop_app_info_new(desktop_id.c_str());
    {
        // The returned data is owned by the instance
        const char *str = g_app_info_get_description(G_APP_INFO(app_info));
        if (str == NULL)
        {
            result = std::string("");
        }
        else
        {
            result = std::string(g_app_info_get_description(G_APP_INFO(app_info)));
        }
    }
    g_object_unref(app_info);
    return result;
}

//
// Refresh the label_widget to show the description
// of the selected application in the tree view
//
static void refresh_widget_data_label(GtkTreeView *tree_view, gpointer user_data)
{
    GtkWidget *label_widget = (GtkWidget *)user_data;

    // The returned data is owned by the instance.
    GtkTreeSelection *selection = gtk_tree_view_get_selection(tree_view);

    GtkTreeModel *model = NULL;
    GtkTreeIter iter;
    // "model"
    // The returned data is owned by the instance.
    // "iter"
    // The returned data is owned by the instance.
    gboolean is_selected = gtk_tree_selection_get_selected(selection, &model, &iter);

    if (is_selected == false)
    {
        gtk_widget_set_visible(label_widget, false);
        return;
    }

    // "GMenuTreeItemType" is "typedef enum"
    GMenuTreeItemType type = get_model_item_menu_type(model, &iter);
    if (type != GMENU_TREE_ITEM_ENTRY)
    {
        gtk_widget_set_visible(label_widget, false);
        return;
    }

    std::string description;
    {
        char *desktop_id = get_model_item_desktop_id(model, &iter);
        description = get_app_info_description(desktop_id);
        g_free(desktop_id);
    }
    {
        // markup
        {
            const char *format = "<span style=\"italic\">\%s</span>";
            char *markup = g_markup_printf_escaped(format, description.c_str());
            {
                gtk_label_set_markup(GTK_LABEL(label_widget), markup);
            }
            g_free(markup);
        }
        // tooltip
        gtk_widget_set_tooltip_text(label_widget, description.c_str());
    }

    gtk_widget_set_visible(label_widget, true);
    return;
}

void refresh_widget_data_label_menu_app_exec(GtkTreeView *tree_view, gpointer user_data)
{
    GtkWidget *label_menu_app_exec = (GtkWidget *)user_data;
    refresh_widget_data_label(tree_view, label_menu_app_exec);
}

void refresh_widget_data_label_def_app_exec(GtkTreeView *defined_view, gpointer user_data)
{
    GtkWidget *label_def_app_exec = (GtkWidget *)user_data;
    refresh_widget_data_label(defined_view, label_def_app_exec);
}
