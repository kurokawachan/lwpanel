

#include <iostream>

#include <gtk/gtk.h>

#include "lw.hpp"

#include "lwlaunchbutton.hpp"

static gboolean launch_button_enter_notify_event(GtkWidget *self, GdkEventCrossing *event, gpointer user_data)
{
    GtkStyleContext *style_context = gtk_widget_get_style_context(self);
    gtk_style_context_add_class(style_context, "button_highlight");

    // Debug
    // printf("%s\n", "launch_button_enter_notify_event");

    // TRUE to stop other handlers from being invoked for the event.
    // FALSE to propagate the event further.
    return false;
}

static gboolean launch_button_leave_notify_event(GtkWidget *self, GdkEventCrossing *event, gpointer user_data)
{
    GtkStyleContext *style_context = gtk_widget_get_style_context(self);
    gtk_style_context_remove_class(style_context, "button_highlight");

    // Debug
    // printf("%s\n", "launch_button_leave_notify_event");

    // TRUE to stop other handlers from being invoked for the event.
    // FALSE to propagate the event further.
    return false;
}

static gboolean launch_button_button_press_event(GtkWidget *self, GdkEventButton *event, gpointer user_data)
{
    // Debug
    // printf("%s\n", "launch_button_button_press_event");
    // printf("%d\n", event->button);

    // we would return if it is not left button
    // panel would handle the right click
    if (event->button != 1)
    {
        return false;
    }

    // https://docs.gtk.org/gdk3/struct.EventButton.html
    // we would return if it is double click
    if (event->type != GDK_BUTTON_PRESS)
    {
        return false;
    }

    GDesktopAppInfo *desktop_app_info = (GDesktopAppInfo *)user_data;
    {
        // There is a bug/issue
        // When g_app_info_launch is trying to Activate
        // there are more than one way to do it. One way is using dbus, another way is something like fork
        //
        // It might be using dbus to Activate if the desktop file ask it to. DBusActivatable=true
        // And the specifications for dbus does not have a way to set environment variables
        // https://specifications.freedesktop.org/desktop-entry/latest/dbus.html
        // We only have desktop-startup-id and activation-token
        //
        // So, if we use g_app_launch_context_setenv, it might be ignored and all
        // https://wiki.archlinux.org/title/Systemd/User#Environment_variables
        // We might have to use ~/.config/environment.d/ to set environment variables

        // GdkAppLaunchContext *context = gdk_display_get_app_launch_context(gdk_display_get_default());
        // debug
        // {
        // 	char **str_array = g_app_launch_context_get_environment(G_APP_LAUNCH_CONTEXT(context));
        // 	char *str = NULL;
        // 	for (int i = 0; *(str_array + i); i++)
        // 	{
        // 		str = *(str_array + i);
        // 		printf("%s\n", str);
        // 	}
        // 	free(str_array);
        // }
        // {
        // 	g_app_launch_context_setenv(G_APP_LAUNCH_CONTEXT(context), "GDK_SCALE", "2");
        // }
        {
            GError *error = NULL;
            // gboolean result = g_app_info_launch_uris(
            gboolean result = g_app_info_launch(
                G_APP_INFO(desktop_app_info),
                NULL,
                // G_APP_LAUNCH_CONTEXT(context),
                NULL,
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
        // g_object_unref(context);
    }
    // TRUE to stop other handlers from being invoked for the event.
    // FALSE to propagate the event further.
    return false;
}

static gboolean launch_button_button_release_event(GtkWidget *self, GdkEventButton *event, gpointer user_data)
{
    // Debug
    // printf("%s\n", "launch_button_button_release_event");

    // TRUE to stop other handlers from being invoked for the event.
    // FALSE to propagate the event further.
    return false;
}

GtkWidget *lwlaunchbutton_new(LXPanel *panel, const std::string &desktop_id)
{
    // Debug
    // GtkWidget * image = get_largest_desktop_icon_as_gtk_image(panel,"org.gnome.Evince.desktop");
    GtkWidget *image = get_largest_desktop_icon_as_gtk_image(panel, desktop_id);

    GtkWidget *launch_button_event_box = gtk_event_box_new();

    gtk_container_add(GTK_CONTAINER(launch_button_event_box), image);

    gtk_widget_set_name(GTK_WIDGET(launch_button_event_box), "launch_button_event_box");
    gtk_widget_set_name(GTK_WIDGET(image), "launch_button_image");

    // make sure it all receive the widget events
    gtk_widget_add_events(
        GTK_WIDGET(launch_button_event_box),
        GDK_ENTER_NOTIFY_MASK | GDK_LEAVE_NOTIFY_MASK);
    g_signal_connect(
        G_OBJECT(launch_button_event_box), "enter-notify-event",
        G_CALLBACK(launch_button_enter_notify_event), NULL);
    g_signal_connect(
        G_OBJECT(launch_button_event_box), "leave-notify-event",
        G_CALLBACK(launch_button_leave_notify_event), NULL);

    {
        GtkCssProvider *css_provider = gtk_css_provider_new();
        {
            GError *error = NULL;
            gboolean result = gtk_css_provider_load_from_data(
                css_provider,
                ".button_highlight #launch_button_image{"
                "background-color:rgba(255,255,255,255);"
                "}",
                -1, &error);

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

            // The return value is deprecated and FALSE will only be returned
            // for backwards compatibility reasons
            if (result == false)
            {
                std::cout << "warning it should not be here" << std::endl;
                std::abort();
            }

            GtkStyleContext *style_context = gtk_widget_get_style_context(GTK_WIDGET(image));
            gtk_style_context_add_provider(
                style_context,
                GTK_STYLE_PROVIDER(css_provider),
                GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
        }
        g_object_unref(css_provider);
    }
    {
        GDesktopAppInfo *desktop_app_info = g_desktop_app_info_new(desktop_id.c_str());
        g_object_set_qdata_full(
            G_OBJECT(launch_button_event_box),
            g_quark_from_string("GDesktopAppInfo"),
            desktop_app_info, g_object_unref);

        {
            // Debug
            // This shows the difference between "display_name" and "name" and "generic_name"
            //
            // Firefox ESR Web Browser
            // Deluge BitTorrent Client
            // std::cout << g_app_info_get_display_name(G_APP_INFO(desktop_app_info)) << std::endl;
            // Firefox ESR
            // Deluge
            // std::cout << g_app_info_get_name(G_APP_INFO(desktop_app_info)) << std::endl;
            // Web Browser
            // BitTorrent Client
            // std::cout << g_desktop_app_info_get_generic_name(desktop_app_info) << std::endl;

            gtk_widget_set_tooltip_text(
                launch_button_event_box,
                g_app_info_get_display_name(G_APP_INFO(desktop_app_info)));

            g_signal_connect(
                G_OBJECT(launch_button_event_box), "button-press-event",
                G_CALLBACK(launch_button_button_press_event), desktop_app_info);
            g_signal_connect(
                G_OBJECT(launch_button_event_box), "button-release-event",
                G_CALLBACK(launch_button_button_release_event), desktop_app_info);
        }
    }

    return launch_button_event_box;
}
