

#include <iostream>

#include "lwlaunchbutton.hpp"

#include "lwlaunchbar_widget.hpp"

// Set the value for "panel" and "settings" using lwlaunchbar instance
void set_value_for_setting_using_lwlaunchbar_instance(
    const GtkWidget *instance,
    LXPanel *&panel,
    config_setting_t *&settings)
{
    g_return_if_fail(instance != NULL);
    {
        lwlaunchbar_instance_data_struct *lwlaunchbar_data_pointer =
            (lwlaunchbar_instance_data_struct *)g_object_get_data(
                G_OBJECT(instance),
                "lwlaunchbar_data");
        panel = lwlaunchbar_data_pointer->panel;
        settings = lwlaunchbar_data_pointer->settings;
    }
}

/* Widget constructor. */
GtkWidget *lwlaunchbar_widget_constructor(LXPanel *panel, config_setting_t *settings)
{
    if (!settings)
    {
        return NULL;
    }
    GtkWidget *lwlaunchbar_widget = panel_box_container_new(panel, 0);

    config_setting_t *config_settings = config_setting_get_member(settings, "");

    // int length = config_setting_length(settings);
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
                GtkWidget *launch_button = lwlaunchbutton_new(panel, id);
                gtk_box_pack_start(GTK_BOX(lwlaunchbar_widget), launch_button, false, false, 0);
            }
        }
        i++;
        item = config_setting_get_elem(config_settings, i);
    }

    // {
    // 	GtkWidget *launch_button = lwlaunchbutton_new(panel, "org.gnome.DiskUtility.desktop");
    // 	gtk_box_pack_start(GTK_BOX(instance), launch_button, false, false, 0);
    // }

    gtk_widget_show_all(lwlaunchbar_widget);

    /* Show the widget and return. */
    return lwlaunchbar_widget;
}

void update_content(GtkWidget *content_holder)
{
    LXPanel *panel = NULL;
    config_setting_t *settings = NULL;
    {
        set_value_for_setting_using_lwlaunchbar_instance(content_holder, panel, settings);
    }

    GtkWidget *content_before_update = gtk_bin_get_child(GTK_BIN(content_holder));
    GtkWidget *new_content = lwlaunchbar_widget_constructor(panel, settings);

    // g_object_ref(content_before_update);
    // gtk_container_remove(GTK_CONTAINER(content_holder), content_before_update);

    // https://docs.gtk.org/gtk3/method.Container.remove.html
    // If you don’t want to use widget again it’s usually more efficient
    // to simply destroy it directly using gtk_widget_destroy() since this will
    // remove it from the container and help break any circular reference count cycles.
    gtk_widget_destroy(content_before_update);
    gtk_container_add(GTK_CONTAINER(content_holder), new_content);

    gtk_widget_show_all(content_holder);
}
