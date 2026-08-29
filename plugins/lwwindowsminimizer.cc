#include <iostream>

// #include <X11/Xlib-xcb.h>
// #include <xcb/xcb_ewmh.h>

#include <glib/gi18n.h>
// #include <gdk/gdkx.h>

#include "plugin.h"
#include "misc.h"
#include "lw.hpp"
#include "lwpanel_button.hpp"

// The creation and destruction of this data structure are synchronized to
// the creation and destruction of the lwwindowsminimizer instance
class lwwindowsminimizer_instance_data_struct
{
  public:
    config_setting_t *settings = nullptr;
    LXPanel *panel = nullptr;
};

gboolean do_work(GtkWidget *widget, GdkEventButton *event, gpointer user_data)
{
    // Debug
    // printf("%s\n", "do_work");

    GdkScreen *screen = gtk_widget_get_screen(widget);
    Screen *xscreen = GDK_SCREEN_XSCREEN(screen);
    GdkAtom atom = gdk_atom_intern("_NET_SHOWING_DESKTOP", FALSE);
    gboolean result = gdk_x11_screen_supports_net_wm_hint(screen, atom);
    if (result == false)
    {
        std::cout << "The system does not support _NET_SHOWING_DESKTOP" << std::endl;
        return false;
    }
    else
    {
        // GdkDisplay *gdk_display = gdk_display_get_default();
        // Display *dpy = GDK_DISPLAY_XDISPLAY(gdk_display);
        // Window root_window = DefaultRootWindow(dpy);
        // xcb_connection_t *xcb_connection = XGetXCBConnection(dpy);
        // xcb_ewmh_connection_t xcb_ewmh_connection;
        // {

        // 	{
        // 		xcb_intern_atom_cookie_t *cookie = xcb_ewmh_init_atoms(
        // 			xcb_connection,
        // 			&xcb_ewmh_connection);
        // 		xcb_generic_error_t *error = NULL;
        // 		int result = xcb_ewmh_init_atoms_replies(&xcb_ewmh_connection, cookie, &error);
        // 		// 1 success
        // 		if (result != 1)
        // 		{
        // 			std::cout << "warning it should not be here" << std::endl;
        // 			std::abort();
        // 		}
        // 	}
        // 	xcb_get_property_cookie_t cookie=xcb_ewmh_get_showing_desktop(
        // 			&xcb_ewmh_connection,
        //                                        0);
        // 	uint8_t is_showing =xcb_ewmh_get_showing_desktop(
        // }
        // xcb_ewmh_connection_wipe(&xcb_ewmh_connection);

        bool is_showing = false;
        guint32 *result = (guint32 *)get_xaproperty(
            RootWindowOfScreen(xscreen),
            a_NET_SHOWING_DESKTOP,
            XA_CARDINAL,
            NULL);
        if (result)
        {
            is_showing = *result;
            XFree(result);
        }
        Xclimsgx(
            xscreen,
            RootWindowOfScreen(xscreen),
            a_NET_SHOWING_DESKTOP,
            !is_showing, 0, 0, 0, 0);

        // WnckHandle *wnck_handle = wnck_handle_new(WNCK_CLIENT_TYPE_PAGER);
        // {
        // 	// WnckScreen *wnck_screen = wnck_handle_get_default_screen(wnck_handle);
        // 	GdkWindow *gdk_window = gtk_widget_get_window(widget);
        // 	Window x11_window = gdk_x11_window_get_xid(gdk_window);
        // 	WnckWindow * wnck_window = wnck_handle_get_window(wnck_handle ,x11_window);
        // 	WnckScreen *wnck_screen = wnck_window_get_screen(wnck_window);

        // 	printf("%s %d\n", "wnck_screen", wnck_screen);
        // 	gboolean is_showing = wnck_screen_get_showing_desktop(wnck_screen);

        // 	std::cout << is_showing << std::endl;
        // 	if (is_showing)
        // 	{
        // 		wnck_screen_toggle_showing_desktop(wnck_screen, false);
        // 	}
        // 	else
        // 	{
        // 		wnck_screen_toggle_showing_desktop(wnck_screen, true);
        // 	}
        // }
        // g_object_unref(wnck_handle);
        return false;
    }
}

/* Widget constructor. */
GtkWidget *lwwindowsminimizer_widget_constructor(LXPanel *panel, config_setting_t *settings)
{
    if (!settings)
    {
        return NULL;
    }
    GtkWidget *lwwindowsminimizer_widget =
        lwpanel_button_new(
            panel,
            "gnome-window-manager",
            "lwwindowsminimizer_widget",
            do_work,
            NULL);

    // gtk_widget_set_has_window(lwwindowsminimizer_widget, FALSE);
    // // GtkWidget *sep;

    // config_setting_t *config_settings = config_setting_get_member(settings, "");

    // // int length = config_setting_length(settings);
    // int i = 0;
    // config_setting_t *item = config_setting_get_elem(config_settings, i);
    // while (item != NULL)
    // {
    // 	{
    // 		if (strcmp(config_setting_get_name(item), "Button") != 0)
    // 		{
    // 			std::cout << "warning it should not be here" << std::endl;
    // 			std::abort();
    // 		}
    // 		const char *id = NULL;
    // 		bool result = config_setting_lookup_string(item, "id", &id);
    // 		if (result != true)
    // 		{
    // 			std::cout << "warning it should not be here" << std::endl;
    // 			std::abort();
    // 		}
    // 		{
    // 			GtkWidget *launch_button = lwlaunchbutton_new(panel, id);
    // 			gtk_box_pack_start(GTK_BOX(lwwindowsminimizer_widget), launch_button, false, false, 0);
    // 		}
    // 	}
    // 	i++;
    // 	item = config_setting_get_elem(config_settings, i);
    // }

    // {
    // 	GtkWidget *launch_button = lwlaunchbutton_new(panel, "org.gnome.DiskUtility.desktop");
    // 	gtk_box_pack_start(GTK_BOX(instance), launch_button, false, false, 0);
    // }

    gtk_widget_show_all(lwwindowsminimizer_widget);

    /* Show the widget and return. */
    return lwwindowsminimizer_widget;
}

/* Plugin constructor. */
static GtkWidget *lwwindowsminimizer_constructor(LXPanel *panel, config_setting_t *settings)
{
    if (!settings)
    {
        return NULL;
    }

    GtkWidget *content_holder = gtk_event_box_new();
    gtk_widget_set_has_window(content_holder, FALSE);
    {
        lwwindowsminimizer_instance_data_struct *lwwindowsminimizer_data_pointer =
            new lwwindowsminimizer_instance_data_struct{
                .settings = settings,
                .panel = panel,
            };
        // auto delete the data when "content_holder" is destroyed
        // delete lwwindowsminimizer_data_pointer;
        g_object_set_data_full(
            G_OBJECT(content_holder),
            "lwwindowsminimizer_data",
            lwwindowsminimizer_data_pointer,
            GDestroyNotify_template_for_delete_operator<lwwindowsminimizer_instance_data_struct>);
    }

    GtkWidget *content = lwwindowsminimizer_widget_constructor(panel, settings);
    gtk_container_add(GTK_CONTAINER(content_holder), content);
    gtk_widget_show_all(content_holder);

    /* Show the widget and return. */
    return content_holder;
}

/* Plugin descriptor. */
LXPanelPluginInit lxpanel_static_plugin_lwwindowsminimizer = {
    .name = N_("LW Windows Minimizer"),
    .description = N_("Minimize all windows"),

    .new_instance = lwwindowsminimizer_constructor,
    // .config = lwwindowsminimizer_config,
    // .reconfigure = lwwindowsminimizer_reconfigure,
    // .expand_available = TRUE,
    // .expand_default = false,
};
