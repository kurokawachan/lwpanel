#include <iostream>

#include <gtk/gtk.h>
#include <glib/gi18n.h>

#include "plugin.h"

#include "lw.hpp"
#include "lwlaunchbar_config_dialog.hpp"

#include "lwlaunchbar_widget.hpp"

/* Plugin constructor. */
static GtkWidget *lwlaunchbar_constructor(LXPanel *panel, config_setting_t *settings)
{
    if (!settings)
    {
        return NULL;
    }

    GtkWidget *content_holder = gtk_event_box_new();
    gtk_widget_set_has_window(content_holder, FALSE);
    {
        lwlaunchbar_instance_data_struct *lwlaunchbar_data_pointer = new lwlaunchbar_instance_data_struct{
            .settings = settings,
            .panel = panel,
        };
        // delete lwlaunchbar_data_pointer;
        g_object_set_data_full(
            G_OBJECT(content_holder),
            "lwlaunchbar_data",
            lwlaunchbar_data_pointer,
            GDestroyNotify_template_for_delete_operator<lwlaunchbar_instance_data_struct>);
    }

    GtkWidget *content = lwlaunchbar_widget_constructor(panel, settings);
    gtk_container_add(GTK_CONTAINER(content_holder), content);
    gtk_widget_show_all(content_holder);

    /* Show the widget and return. */
    return content_holder;
}

/* Callback when panel configuration changes. */
static void lwlaunchbar_reconfigure(LXPanel *panel, GtkWidget *instance)
{
    g_debug("%s", "lwlaunchbar_reconfigure");
    if (!instance)
    {
        std::cout << "warning it should not be here" << std::endl;
        std::abort();
    }
    update_content(instance);
}

/* Plugin descriptor. */
LXPanelPluginInit lxpanel_static_plugin_lwlaunchbar = {
    .name = N_("lwlaunchbar"),
    .description = N_("Add a lwlaunchbar to the panel"),

    .new_instance = lwlaunchbar_constructor,
    .config = lwlaunchbar_config,
    .reconfigure = lwlaunchbar_reconfigure,
    .expand_available = TRUE,
    .expand_default = false,
};
