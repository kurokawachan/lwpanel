
#include <iostream>
#include <functional>
#include "lw.hpp"
#include "lwpanel_button.hpp"

class lwbutton_instance_data_struct
{
  public:
    LXPanel *panel = NULL;
    const std::string icon_name;
    const std::string tooltip_text;
    std::function<lwpanel_button_callback> button_press_callback;
    std::function<lwpanel_button_callback> button_release_callback;
};

gboolean button_enter_notify_event(GtkWidget *self, GdkEventCrossing *event, gpointer user_data)
{
    GtkStyleContext *style_context = gtk_widget_get_style_context(self);
    gtk_style_context_add_class(style_context, "button_highlight");
    // Debug
    // printf("%s\n", "button_enter_notify_event");

    // TRUE to stop other handlers from being invoked for the event.
    // FALSE to propagate the event further.
    return false;
}

gboolean button_leave_notify_event(GtkWidget *self, GdkEventCrossing *event, gpointer user_data)
{
    GtkStyleContext *style_context = gtk_widget_get_style_context(self);
    gtk_style_context_remove_class(style_context, "button_highlight");
    // Debug
    // printf("%s\n", "button_leave_notify_event");

    // TRUE to stop other handlers from being invoked for the event.
    // FALSE to propagate the event further.
    return false;
}

gboolean button_press_event(GtkWidget *self, GdkEventButton *event, gpointer user_data)
{
    GtkStyleContext *style_context = gtk_widget_get_style_context(self);
    gtk_style_context_add_class(style_context, "button_pressed");
    // Debug
    // printf("%s\n", "button_press_event");
    // printf("%d\n", event->button);

    // We only care for left button in this function
    // so we should return false if it is not left button
    //
    // We might receive the event for right-click
    // however we should not handle it
    // as if we do handle that and return true
    // the panel would not be able to show the right click Context menu
    //
    // the panel should handle the right click
    //
    if (event->button != 1)
    {
        return false;
    }

    // https://docs.gtk.org/gdk3/struct.EventButton.html
    // We would return if it is double click
    if (event->type != GDK_BUTTON_PRESS)
    {
        return false;
    }

    {
        lwbutton_instance_data_struct *lwbutton_instance_data_pointer =
            (lwbutton_instance_data_struct *)g_object_get_qdata(
                G_OBJECT(self),
                g_quark_from_string("button_event_box"));
        if (lwbutton_instance_data_pointer->button_press_callback != NULL)
        {
            lwbutton_instance_data_pointer->button_press_callback(self, event, user_data);
        }
    }

    // TRUE to stop other handlers from being invoked for the event.
    // FALSE to propagate the event further.
    return false;
}

gboolean button_release_event(GtkWidget *self, GdkEventButton *event, gpointer user_data)
{
    GtkStyleContext *style_context = gtk_widget_get_style_context(self);
    gtk_style_context_remove_class(style_context, "button_pressed");
    // Debug
    // printf("%s\n", "button_release_event");

    {
        lwbutton_instance_data_struct *lwbutton_instance_data_pointer =
            (lwbutton_instance_data_struct *)g_object_get_qdata(
                G_OBJECT(self),
                g_quark_from_string("button_event_box"));
        if (lwbutton_instance_data_pointer->button_release_callback != NULL)
        {
            lwbutton_instance_data_pointer->button_release_callback(self, event, user_data);
        }
    }

    // TRUE to stop other handlers from being invoked for the event.
    // FALSE to propagate the event further.
    return false;
}
GtkWidget *lwpanel_button_new(
    LXPanel *panel,
    const char *icon_name,
    const gchar *tooltip_text,
    std::function<lwpanel_button_callback> button_press_callback,
    std::function<lwpanel_button_callback> button_release_callback)
{
    GtkWidget *button_event_box = gtk_event_box_new();
    {
        lwbutton_instance_data_struct *lwbutton_instance_data_pointer =
            new lwbutton_instance_data_struct{
                .panel = panel,
                .icon_name = std::string(icon_name),
                .tooltip_text = std::string(tooltip_text),
                .button_press_callback = button_press_callback,
                .button_release_callback = button_release_callback,
            };
        g_object_set_qdata_full(
            G_OBJECT(button_event_box),
            g_quark_from_string("button_event_box"),
            lwbutton_instance_data_pointer,
            GDestroyNotify_template_for_delete_operator<lwbutton_instance_data_struct>);
    }

    GtkWidget *image = get_largest_desktop_icon_as_gtk_image_using_icon_name(
        panel,
        icon_name);

    gtk_container_add(GTK_CONTAINER(button_event_box), image);

    gtk_widget_set_name(GTK_WIDGET(button_event_box), "button_event_box");
    gtk_widget_set_name(GTK_WIDGET(image), "button_image");

    // make sure it all receive the widget events
    gtk_widget_add_events(
        GTK_WIDGET(button_event_box),
        GDK_ENTER_NOTIFY_MASK | GDK_LEAVE_NOTIFY_MASK);
    g_signal_connect(
        G_OBJECT(button_event_box), "enter-notify-event",
        G_CALLBACK(button_enter_notify_event), NULL);
    g_signal_connect(
        G_OBJECT(button_event_box), "leave-notify-event",
        G_CALLBACK(button_leave_notify_event), NULL);

    {
        GtkCssProvider *css_provider = gtk_css_provider_new();
        {
            GError *error = NULL;
            gboolean result = gtk_css_provider_load_from_data(
                css_provider,
                ".button_highlight #button_image{"
                "background-color:rgba(255,255,255,255);"
                "}"
                ".button_pressed #button_image{"
                "background-color:rgba(200,200,200,255);"
                "}",
                -1, &error);

            if (error != NULL)
            {
                std::cout << error->message << std::endl;
                g_error_free(error);

                std::cout << "warning it should not be here" << std::endl;
                std::abort();
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
                GTK_STYLE_PROVIDER_PRIORITY_USER);
        }
        g_object_unref(css_provider);
    }
    {
        // g_object_set_qdata_full(
        // 	G_OBJECT(button_event_box),
        // 	g_quark_from_string("button_event_box"),
        // 	desktop_app_info, g_object_unref);

        {
            gtk_widget_set_tooltip_text(button_event_box, tooltip_text);

            g_signal_connect(
                G_OBJECT(button_event_box), "button-press-event",
                G_CALLBACK(button_press_event), NULL);
            g_signal_connect(
                G_OBJECT(button_event_box), "button-release-event",
                G_CALLBACK(button_release_event), NULL);
        }
    }

    return button_event_box;
}
