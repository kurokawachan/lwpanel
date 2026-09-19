

#include <iostream>

#include <glib/gi18n.h>

// TODO fix me
#define GMENU_I_KNOW_THIS_IS_UNSTABLE
#include <gmenu-tree.h>

#include "lwlaunchbar_config_dialog.hpp"

#include "lwlaunchbar_config_dialog_app_view.hpp"

static gboolean tree_view_row_separator_func(
    GtkTreeModel *model,
    GtkTreeIter *iter,
    gpointer data)
{
    GMenuTreeItemType type = get_model_item_menu_type(model, iter);
    if (type == GMENU_TREE_ITEM_SEPARATOR)
    {
        return true;
    }
    return false;
}

void setup_tree_view_column(GtkWidget *tree_view)
{
    GtkCellRenderer *renderer = NULL;
    GtkTreeViewColumn *column = gtk_tree_view_column_new();
    gtk_tree_view_column_set_title(column, _("Installed Applications"));

    renderer = gtk_cell_renderer_pixbuf_new();
    gtk_tree_view_column_pack_start(column, renderer, FALSE);
    gtk_tree_view_column_add_attribute(column, renderer, "icon-name", 1);

    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_column_pack_start(column, renderer, TRUE);
    gtk_tree_view_column_add_attribute(column, renderer, "text", 2);

    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
    gtk_tree_view_set_row_separator_func(
        GTK_TREE_VIEW(tree_view),
        tree_view_row_separator_func,
        NULL,
        NULL);
}

// Note
//
// The return value should be freed using
//
// g_free()
//
static char *get_icon_string_for_menu_directory(GMenuTreeDirectory *menu_tree_directory)
{
    const char *file_path = gmenu_tree_directory_get_desktop_file_path(menu_tree_directory);
    if (!file_path)
    {
        return NULL;
    }

    gchar *icon_str_p = NULL;
    {
        GKeyFile *key_file = g_key_file_new();
        {
            GError *error = NULL;
            gboolean result = g_key_file_load_from_file(
                key_file,
                file_path,
                G_KEY_FILE_NONE,
                &error);
            if (error != NULL)
            {
                std::cout << error->message << std::endl;
                g_error_free(error);

                std::cout << "warning it should not be here" << std::endl;
                std::abort();
            }
            if (result == false)
            {
                std::cout << "warning it should not be here" << std::endl;
                std::abort();
            }
        }
        {
            GError *error = NULL;
            icon_str_p = g_key_file_get_string(
                key_file,
                "Desktop Entry",
                "Icon",
                &error);
            if (error != NULL)
            {
                std::cout << error->message << std::endl;
                g_error_free(error);

                std::cout << "warning it should not be here" << std::endl;
                std::abort();
            }
        }
        g_key_file_unref(key_file);
    }
    return icon_str_p;
}

static void tranverse_gmenu(GtkTreeStore *tree_store, GtkTreeIter *parent_node, GMenuTreeDirectory *menu_tree_directory)
{
    GMenuTreeIter *menu_tree_iter = gmenu_tree_directory_iter(menu_tree_directory);
    {
        GMenuTreeItemType type = gmenu_tree_iter_next(menu_tree_iter);
        while (type != GMENU_TREE_ITEM_INVALID)
        {
            {
                if (type == GMENU_TREE_ITEM_DIRECTORY)
                {
                    GMenuTreeDirectory *item = gmenu_tree_iter_get_directory(menu_tree_iter);
                    {
                        // printf("%s\n", "gmenu_tree_directory_get_name(item)");
                        // printf("%s\n", gmenu_tree_directory_get_name(item) ? gmenu_tree_directory_get_name(item) : "");
                        // printf("%s\n", "gmenu_tree_directory_get_desktop_file_path(item)");
                        // printf("%s\n", gmenu_tree_directory_get_desktop_file_path(item) ? gmenu_tree_directory_get_desktop_file_path(item) : "");

                        gchar *icon_str_p = get_icon_string_for_menu_directory(item);
                        {
                            GtkTreeIter iter;
                            gtk_tree_store_append(tree_store, &iter, parent_node);
                            gtk_tree_store_set(
                                tree_store,
                                &iter,
                                0, type,
                                1, icon_str_p,
                                2, gmenu_tree_directory_get_name(item),
                                -1);

                            tranverse_gmenu(tree_store, &iter, item);
                        }
                        g_free(icon_str_p);
                    }
                    gmenu_tree_item_unref(item);
                }
                if (type == GMENU_TREE_ITEM_ENTRY)
                {
                    GMenuTreeEntry *item = gmenu_tree_iter_get_entry(menu_tree_iter);
                    {
                        // Returns: (transfer none): The #GDesktopAppInfo for this entry
                        // https://gitlab.gnome.org/GNOME/gnome-menus/-/blob/afcadab260b65fe0a15d6993f13add1f6b5c58fb/libmenu/gmenu-tree.c#L1253
                        GDesktopAppInfo *app_info = gmenu_tree_entry_get_app_info(item);
                        // printf("%x\n", app_info);
                        // printf("%s\n", "g_app_info_get_name(G_APP_INFO(app_info))");
                        // printf("%s\n", g_app_info_get_name(G_APP_INFO(app_info)) ? g_app_info_get_name(G_APP_INFO(app_info)) : "");
                        {
                            GtkTreeIter iter;
                            gtk_tree_store_append(tree_store, &iter, parent_node);
                            gtk_tree_store_set(
                                tree_store,
                                &iter,
                                0, type,
                                1, g_desktop_app_info_get_string(app_info, "Icon"),
                                2, g_app_info_get_name(G_APP_INFO(app_info)),
                                3, g_app_info_get_id(G_APP_INFO(app_info)),
                                -1);
                        }
                        // we do not need to free it
                        // g_object_unref(app_info);
                    }
                    gmenu_tree_item_unref(item);
                }
                if (type == GMENU_TREE_ITEM_SEPARATOR)
                {
                    GMenuTreeSeparator *item = gmenu_tree_iter_get_separator(menu_tree_iter);
                    {
                        // printf("%s\n", "GMENU_TREE_ITEM_SEPARATOR");
                        GtkTreeIter iter;
                        gtk_tree_store_append(tree_store, &iter, parent_node);
                        gtk_tree_store_set(
                            tree_store,
                            &iter,
                            0, type,
                            -1);
                    }
                    gmenu_tree_item_unref(item);
                }
                if (type == GMENU_TREE_ITEM_HEADER)
                {
                    GMenuTreeHeader *item = gmenu_tree_iter_get_header(menu_tree_iter);
                    {
                        g_debug("%s\n", "GMENU_TREE_ITEM_HEADER");
                    }
                    gmenu_tree_item_unref(item);
                }
                if (type == GMENU_TREE_ITEM_ALIAS)
                {
                    GMenuTreeAlias *item = gmenu_tree_iter_get_alias(menu_tree_iter);
                    {
                        g_debug("%s\n", "GMENU_TREE_ITEM_ALIAS");
                    }
                    gmenu_tree_item_unref(item);
                }
            }
            type = gmenu_tree_iter_next(menu_tree_iter);
        }
    }
    gmenu_tree_iter_unref(menu_tree_iter);
}

void setup_tree_store(GtkWidget *tree_view)
{

    GtkTreeStore *tree_store = gtk_tree_store_new(
        4,
        // G_TYPE_ENUM
        // The reason we do not use G_TYPE_ENUM
        // it is an abstract type to be used as base class for your enums
        // must implement it as a GObject type
        // https://discourse.gnome.org/t/enum-in-my-application/3385
        G_TYPE_INT,    // menu_cache_item_get_type(item)
        G_TYPE_STRING, // menu_cache_item_get_icon(item)
        G_TYPE_STRING, // menu_cache_item_get_name(item)
        G_TYPE_STRING  // menu_cache_item_get_id(item)
    );
    {
        gtk_tree_view_set_model(GTK_TREE_VIEW(tree_view), GTK_TREE_MODEL(tree_store));
    }
    g_object_unref(tree_store);
}

void load_data_into_tree_store(GtkWidget *tree_view)
{
    // The returned data is owned by the instance.
    GtkTreeStore *tree_store = GTK_TREE_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(tree_view)));

    {
        // GMenuTree *menu_tree = gmenu_tree_new_for_path(
        // "lxde-applications.menu",
        // "/etc/xdg/menus/lxde-applications.menu",
        // GMENU_TREE_FLAGS_NONE);
        GMenuTree *menu_tree = gmenu_tree_new(
            // "applications.menu",
            "lxde-applications.menu",
            GMenuTreeFlags(
                int(GMENU_TREE_FLAGS_INCLUDE_EXCLUDED) |
                int(GMENU_TREE_FLAGS_INCLUDE_NODISPLAY) |
                int(GMENU_TREE_FLAGS_INCLUDE_UNALLOCATED) |
                int(GMENU_TREE_FLAGS_SHOW_EMPTY) |
                int(GMENU_TREE_FLAGS_SHOW_ALL_SEPARATORS)));
        {
            {
                GError *error = NULL;
                gboolean result = gmenu_tree_load_sync(menu_tree, &error);
                if (error != NULL)
                {
                    std::cout << error->message << std::endl;
                    g_error_free(error);

                    std::cout << "warning it should not be here" << std::endl;
                    std::abort();
                }
                if (result == false)
                {
                    std::cout << "warning it should not be here" << std::endl;
                    std::abort();
                }
            }
            GMenuTreeDirectory *menu_tree_directory = gmenu_tree_get_root_directory(menu_tree);

            tranverse_gmenu(tree_store, NULL, menu_tree_directory);

            gmenu_tree_item_unref(menu_tree_directory);
        }
        g_object_unref(menu_tree);
    }
}
