

#include <iostream>

#include "plugin.h"

#include "lw.hpp"

#include "lwlaunchbar_widget.hpp"
#include "lwlaunchbar_config_dialog_app_view.hpp"
#include "lwlaunchbar_config_dialog_refresh_widget_status.hpp"
#include "lwlaunchbar_config_dialog_handle_widget_event.hpp"
#include "lwlaunchbar_config_dialog_handle_user_event.hpp"

#include "lwlaunchbar_config_dialog.hpp"

//
// "GMenuTreeItemType" is "typedef enum"
// So we do not need to free it
// TODO
// assert the input is valid
//
GMenuTreeItemType get_model_item_menu_type(GtkTreeModel *model, GtkTreeIter *iter)
{
    GMenuTreeItemType type = GMENU_TREE_ITEM_INVALID;
    {
        GValue value = G_VALUE_INIT;
        gtk_tree_model_get_value(model, iter, 0, &value);
        {
            type = (GMenuTreeItemType)g_value_get_int(&value);
        }
        g_value_unset(&value);
    }
    return type;
}

// Note
//
// The return value should be freed using
//
// g_free()
//
// TODO
// assert the input is valid
//
char *get_model_item_icon_name(GtkTreeModel *model, GtkTreeIter *iter)
{
    char *result = NULL;
    {
        GValue value = G_VALUE_INIT;
        gtk_tree_model_get_value(model, iter, 1, &value);
        {
            const char *icon_name = g_value_get_string(&value);
            result = g_strdup(icon_name);
        }
        g_value_unset(&value);
    }
    return result;
}

// Note
//
// The return value should be freed using
//
// g_free()
//
// TODO
// assert the input is valid
//
char *get_model_item_name(GtkTreeModel *model, GtkTreeIter *iter)
{
    char *result = NULL;
    {
        GValue value = G_VALUE_INIT;
        gtk_tree_model_get_value(model, iter, 2, &value);
        {
            const char *name = g_value_get_string(&value);
            result = g_strdup(name);
        }
        g_value_unset(&value);
    }
    return result;
}

// Note
//
// The return value should be freed using
//
// g_free()
//
// TODO
// assert the input is valid
//
char *get_model_item_desktop_id(GtkTreeModel *model, GtkTreeIter *iter)
{
    char *result = NULL;
    {
        GValue value = G_VALUE_INIT;
        gtk_tree_model_get_value(model, iter, 3, &value);
        {
            const char *desktop_id = g_value_get_string(&value);
            result = g_strdup(desktop_id);
        }
        g_value_unset(&value);
    }
    return result;
}

//
// The depth should always be 1
//
int get_indices(GtkTreeModel *model, GtkTreeIter *iter)
{
    int result = 0;

    GtkTreePath *path = gtk_tree_model_get_path(model, iter);
    {
        gint depth = gtk_tree_path_get_depth(path);
        if (depth != 1)
        {
            std::cout << "warning it should not be here" << std::endl;
            std::abort();
        }
        // This value should not be freed
        gint *array = gtk_tree_path_get_indices(path);
        result = array[0];
    }
    gtk_tree_path_free(path);

    return result;
}

void save_data(GtkWidget *dlg)
{
    GtkWidget *defined_view = NULL;
    GtkWidget *instance = NULL;
    {
        lwlaunchbar_preferences_widget_struct *widget_data_pointer =
            (lwlaunchbar_preferences_widget_struct *)g_object_get_data(
                G_OBJECT(dlg),
                "lwlaunchbar_widget_data");
        defined_view = widget_data_pointer->defined_view;
        instance = widget_data_pointer->instance;
    }

    config_setting_t *settings = NULL;
    LXPanel *panel = NULL;
    {
        set_value_for_setting_using_lwlaunchbar_instance(instance, panel, settings);
    }
    {
        config_setting_remove(settings, "");
        config_setting_add(settings, "", PANEL_CONF_TYPE_LIST);
    }

    GtkListStore *list_store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(defined_view)));
    GtkTreeIter iter;

    gboolean has_value = false;

    has_value = gtk_tree_model_get_iter_first(GTK_TREE_MODEL(list_store), &iter);
    while (has_value)
    {
        {
            char *desktop_id = get_model_item_desktop_id(GTK_TREE_MODEL(list_store), &iter);
            {
                // std::cout << desktop_id << std::endl;
                {
                    config_setting_t *button_item = config_group_add_subgroup(settings, "Button");
                    {
                        config_group_set_string(button_item, "id", desktop_id);
                    }
                    // TODO not sure why we need to use this
                    // config_setting_destroy(button_item);
                }
            }
            g_free(desktop_id);
        }
        has_value = gtk_tree_model_iter_next(GTK_TREE_MODEL(list_store), &iter);
    }
    lxpanel_config_save(panel);
}

void read_config_settings_into_defined_view(GtkWidget *instance, GtkWidget *defined_view)
{
    GtkListStore *list_store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(defined_view)));
    config_setting_t *config_settings = NULL;
    {
        LXPanel *panel = NULL;
        config_setting_t *settings = NULL;
        {
            set_value_for_setting_using_lwlaunchbar_instance(instance, panel, settings);
        }
        config_settings = config_setting_get_member(settings, "");
    }

    {
        int i = 0;
        config_setting_t *item = config_setting_get_elem(config_settings, i);
        while (item != NULL)
        {
            {
                if (strcmp(config_setting_get_name(item), "Button") != 0)
                {
                    std::cout << "warning it should not be here" << std::endl;
                    std::abort();
                }
                const char *id = NULL;
                bool result = config_setting_lookup_string(item, "id", &id);
                if (result != true)
                {
                    std::cout << "warning it should not be here" << std::endl;
                    std::abort();
                }
                {
                    GDesktopAppInfo *desktop_app_info = g_desktop_app_info_new(id);

                    char *icon_str_p = g_desktop_app_info_get_string(desktop_app_info, "Icon");
                    {
                        // The returned data is owned by the instance.
                        const char *name = g_app_info_get_name(G_APP_INFO(desktop_app_info));
                        GtkTreeIter iter;
                        gtk_list_store_append(GTK_LIST_STORE(list_store), &iter);
                        gtk_list_store_set(
                            GTK_LIST_STORE(list_store),
                            &iter,
                            0, GMENU_TREE_ITEM_ENTRY,
                            1, icon_str_p,
                            2, name,
                            3, id,
                            -1);
                    }
                    g_free(icon_str_p);

                    g_object_unref(desktop_app_info);
                }
            }
            i++;
            item = config_setting_get_elem(config_settings, i);
        }
    }
}

/* Callback when panel configuration changes. */
GtkWidget *lwlaunchbar_config(LXPanel *panel, GtkWidget *instance)
{
    GtkBuilder *builder = gtk_builder_new();
    {
        std::string ui_file_name;
        {
            char *filename = g_build_filename(PACKAGE_UI_DIR, "lwlaunchbar.glade", NULL);
            {
                ui_file_name = std::string(filename);
            }
            g_free(filename);
        }
        GError *error = NULL;
        guint result = gtk_builder_add_from_file(
            builder,
            ui_file_name.c_str(),
            &error);
        if (error != NULL)
        {
            std::cout << error->message << std::endl;
            // printf("%s\n", error->message);
            g_error_free(error);

            std::cout << "warning it should not be here" << std::endl;
            std::abort();
            // printf("%s\n", "warning it should not be here");
            // exit(1);
        }
        // A positive value on success, 0 if an error occurred.
        if (result == 0)
        {
            std::cout << "warning it should not be here" << std::endl;
            std::abort();
        }
    }
    GtkWidget *dlg = (GtkWidget *)gtk_builder_get_object(builder, "dlg");
    {

        GtkWidget *defined_view = (GtkWidget *)gtk_builder_get_object(builder, "defined_view");
        read_config_settings_into_defined_view(instance, defined_view);

        GtkWidget *tree_view = gtk_tree_view_new();
        setup_tree_view_column(tree_view);

        {
            lwlaunchbar_preferences_widget_struct *widget_data_pointer = new lwlaunchbar_preferences_widget_struct{
                .button_add = (GtkWidget *)gtk_builder_get_object(builder, "button_add"),
                .button_remove = (GtkWidget *)gtk_builder_get_object(builder, "button_remove"),
                .button_up = (GtkWidget *)gtk_builder_get_object(builder, "button_up"),
                .button_down = (GtkWidget *)gtk_builder_get_object(builder, "button_down"),
                .defined_view = (GtkWidget *)gtk_builder_get_object(builder, "defined_view"),
                .tree_view = tree_view,
                .instance = instance,
            };
            // delete widget_data_pointer;
            g_object_set_data_full(
                G_OBJECT(dlg),
                "lwlaunchbar_widget_data",
                widget_data_pointer,
                GDestroyNotify_template_for_delete_operator<lwlaunchbar_preferences_widget_struct>);
        }

        // Refresh the status of widget
        {
            GtkWidget *button_add = (GtkWidget *)gtk_builder_get_object(builder, "button_add");
            refresh_widget_data_button_add(GTK_TREE_VIEW(tree_view), button_add);
            g_signal_connect(tree_view, "cursor-changed", G_CALLBACK(refresh_widget_data_button_add), button_add);
        }
        {
            GtkWidget *defined_view = (GtkWidget *)gtk_builder_get_object(builder, "defined_view");
            GtkWidget *button_remove = (GtkWidget *)gtk_builder_get_object(builder, "button_remove");
            refresh_widget_data_button_remove(GTK_TREE_VIEW(defined_view), button_remove);
            g_signal_connect(defined_view, "cursor-changed", G_CALLBACK(refresh_widget_data_button_remove), button_remove);
        }
        {
            GtkWidget *defined_view = (GtkWidget *)gtk_builder_get_object(builder, "defined_view");
            GtkWidget *button_up = (GtkWidget *)gtk_builder_get_object(builder, "button_up");
            refresh_widget_data_button_up(GTK_TREE_VIEW(defined_view), button_up);
            g_signal_connect(defined_view, "cursor-changed", G_CALLBACK(refresh_widget_data_button_up), button_up);
        }

        {
            GtkWidget *defined_view = (GtkWidget *)gtk_builder_get_object(builder, "defined_view");
            GtkWidget *button_down = (GtkWidget *)gtk_builder_get_object(builder, "button_down");
            refresh_widget_data_button_down(GTK_TREE_VIEW(defined_view), button_down);
            g_signal_connect(defined_view, "cursor-changed", G_CALLBACK(refresh_widget_data_button_down), button_down);
        }

        // handle_widget_event
        {
            GtkWidget *defined_view = (GtkWidget *)gtk_builder_get_object(builder, "defined_view");
            GtkListStore *list_store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(defined_view)));
            g_signal_connect(list_store, "row-inserted", G_CALLBACK(handle_dialog_event_defined_view_list_store_row_inserted), dlg);
            g_signal_connect(list_store, "row-deleted", G_CALLBACK(handle_dialog_event_defined_view_list_store_row_deleted), dlg);
            g_signal_connect(list_store, "rows-reordered", G_CALLBACK(handle_dialog_event_defined_view_list_store_rows_reordered), dlg);
        }

        {
            GtkWidget *label_menu_app_exec = (GtkWidget *)gtk_builder_get_object(builder, "label_menu_app_exec");
            refresh_widget_data_label_menu_app_exec(GTK_TREE_VIEW(tree_view), label_menu_app_exec);
            g_signal_connect(tree_view, "cursor-changed", G_CALLBACK(refresh_widget_data_label_menu_app_exec), label_menu_app_exec);
        }
        {
            GtkWidget *defined_view = (GtkWidget *)gtk_builder_get_object(builder, "defined_view");
            GtkWidget *label_def_app_exec = (GtkWidget *)gtk_builder_get_object(builder, "label_def_app_exec");
            refresh_widget_data_label_def_app_exec(GTK_TREE_VIEW(defined_view), label_def_app_exec);
            g_signal_connect(defined_view, "cursor-changed", G_CALLBACK(refresh_widget_data_label_def_app_exec), label_def_app_exec);
        }

        // handle_user_event

        {
            GtkWidget *button_add = (GtkWidget *)gtk_builder_get_object(builder, "button_add");
            g_signal_connect(button_add, "clicked", G_CALLBACK(handle_dialog_event_button_add_clicked), dlg);
        }
        {
            GtkWidget *button_remove = (GtkWidget *)gtk_builder_get_object(builder, "button_remove");
            g_signal_connect(button_remove, "clicked", G_CALLBACK(handle_dialog_event_button_remove_clicked), dlg);
        }
        {
            g_signal_connect(tree_view, "row-activated", G_CALLBACK(handle_dialog_event_tree_view_row_activated), dlg);
        }
        {
            g_signal_connect(defined_view, "row-activated", G_CALLBACK(handle_dialog_event_defined_view_row_activated), dlg);
        }
        {
            GtkWidget *button_up = (GtkWidget *)gtk_builder_get_object(builder, "button_up");
            g_signal_connect(button_up, "clicked", G_CALLBACK(handle_dialog_event_button_up_clicked), dlg);
        }
        {
            GtkWidget *button_down = (GtkWidget *)gtk_builder_get_object(builder, "button_down");
            g_signal_connect(button_down, "clicked", G_CALLBACK(handle_dialog_event_button_down_clicked), dlg);
        }

        {
            setup_tree_store(tree_view);
            load_data_into_tree_store(tree_view);
        }
        GtkWidget *menu_view_window = (GtkWidget *)gtk_builder_get_object(builder, "menu_view_window");
        // gtk_container_add(GTK_CONTAINER(menu_view_window), menu_view);
        gtk_container_add(GTK_CONTAINER(menu_view_window), tree_view);
        gtk_widget_show_all(dlg);
    }
    g_object_unref(builder);
    return dlg;
}
