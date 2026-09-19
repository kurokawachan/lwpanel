

#include <iostream>

#include "lwlaunchbar_config_dialog.hpp"

#include "lwlaunchbar_config_dialog_modify_data.hpp"

void add_data_from_right_to_left(GtkTreeView *tree_view_right, GtkTreeView *tree_view_left)
{
    GtkTreeSelection *selection_left = gtk_tree_view_get_selection(tree_view_left);
    GtkTreeSelection *selection_right = gtk_tree_view_get_selection(tree_view_right);

    GtkTreeModel *model_right = NULL;
    GtkTreeIter iter_right;
    gboolean is_selected_right = gtk_tree_selection_get_selected(
        selection_right,
        &model_right,
        &iter_right);
    if (!is_selected_right)
    {
        return;
    }
    GMenuTreeItemType type_right = get_model_item_menu_type(model_right, &iter_right);
    if (type_right != GMENU_TREE_ITEM_ENTRY)
    {
        return;
    }
    char *icon_name = get_model_item_icon_name(model_right, &iter_right);
    char *name = get_model_item_name(model_right, &iter_right);
    char *desktop_id = get_model_item_desktop_id(model_right, &iter_right);
    {
        GtkTreeModel *model_left = NULL;
        GtkTreeIter iter_left;
        gboolean is_selected_left = gtk_tree_selection_get_selected(
            selection_left,
            &model_left,
            &iter_left);
        // if we don't have gtk_list_store_append
        // we would have
        // assertion 'iter_is_valid (sibling, list_store)' failed
        if (is_selected_left == true)
        {
            GtkTreeIter iter;
            gtk_list_store_insert_after(GTK_LIST_STORE(model_left), &iter, &iter_left);
            gtk_list_store_set(
                GTK_LIST_STORE(model_left),
                &iter,
                0, type_right,
                1, icon_name,
                2, name,
                3, desktop_id,
                -1);
        }
        else
        {
            GtkTreeIter iter;
            gtk_list_store_append(GTK_LIST_STORE(model_left), &iter);
            gtk_list_store_set(
                GTK_LIST_STORE(model_left),
                &iter,
                0, type_right,
                1, icon_name,
                2, name,
                3, desktop_id,
                -1);
        }
    }
    g_free(desktop_id);
    g_free(name);
    g_free(icon_name);
}

void remove_data_from_left_view(GtkTreeView *defined_view)
{
    GtkTreeSelection *selection = gtk_tree_view_get_selection(defined_view);

    GtkTreeModel *model = NULL;
    GtkTreeIter iter;
    gboolean is_selected = gtk_tree_selection_get_selected(
        selection,
        &model,
        &iter);
    if (!is_selected)
    {
        return;
    }
    GMenuTreeItemType type = get_model_item_menu_type(model, &iter);
    if (type != GMENU_TREE_ITEM_ENTRY)
    {
        return;
    }
    gtk_list_store_remove(GTK_LIST_STORE(model), &iter);
}

void move_data_up_by_one_for_left_view(GtkTreeView *defined_view)
{
    GtkTreeSelection *selection = gtk_tree_view_get_selection(defined_view);

    GtkTreeModel *model = NULL;
    GtkTreeIter iter;
    gboolean is_selected = gtk_tree_selection_get_selected(
        selection,
        &model,
        &iter);
    if (!is_selected)
    {
        return;
    }

    // gint number_of_item = gtk_tree_model_iter_n_children(model, NULL);
    gint index = get_indices(model, &iter);
    if (index == 0)
    {
        return;
    }

    GtkTreeIter iter_one_before;
    gboolean result = gtk_tree_model_iter_nth_child(model, &iter_one_before, NULL, index - 1);
    if (!result)
    {
        std::cout << "warning it should not be here" << std::endl;
        std::abort();
    }

    gtk_list_store_swap(GTK_LIST_STORE(model), &iter_one_before, &iter);
}

void move_data_down_by_one_for_left_view(GtkTreeView *defined_view)
{
    GtkTreeSelection *selection = gtk_tree_view_get_selection(defined_view);

    GtkTreeModel *model = NULL;
    GtkTreeIter iter;
    gboolean is_selected = gtk_tree_selection_get_selected(
        selection,
        &model,
        &iter);
    if (!is_selected)
    {
        return;
    }

    gint number_of_item = gtk_tree_model_iter_n_children(model, NULL);
    gint index = get_indices(model, &iter);
    if (index == (number_of_item - 1))
    {
        return;
    }

    GtkTreeIter iter_one_after;
    gboolean result = gtk_tree_model_iter_nth_child(model, &iter_one_after, NULL, index + 1);
    if (!result)
    {
        std::cout << "warning it should not be here" << std::endl;
        std::abort();
    }

    gtk_list_store_swap(GTK_LIST_STORE(model), &iter_one_after, &iter);
}
