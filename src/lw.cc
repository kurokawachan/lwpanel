
#include "lw.hpp"

// Description
//
// Check if Desktop Entry Files have "Icon" key
// https://wiki.archlinux.org/title/Desktop_entries#Common_image_formats
//
// Note
//
// The files here are .desktop extension files and they might not have "Icons" key
//
// Parameters and Return value
//
// Files and their corresponding "Icon" values
//
// Example
//
// desktop_id "firefox-esr.desktop" "vlc.desktop" "com.gexperts.Tilix.desktop"
// result "firefox-esr" "vlc" "com.gexperts.Tilix"
//
bool get_desktop_icon_string(const std::string &desktop_id, std::string &result)
{
    result = "";
    GDesktopAppInfo *desktop_app_info = g_desktop_app_info_new(desktop_id.c_str());
    if (nullptr == desktop_app_info)
    {
        return false;
    }
    bool has_key = g_desktop_app_info_has_key(desktop_app_info, "Icon");
    if (!has_key)
    {
        g_object_unref(desktop_app_info);
        return false;
    }

    std::string icon_str;
    {
        char *icon_str_p = g_desktop_app_info_get_string(desktop_app_info, "Icon");
        icon_str = std::string(icon_str_p);
        g_free(icon_str_p);
        g_object_unref(desktop_app_info);
    }
    result = icon_str;
    return true;
}

// Description
//
// Check if a certain icon has a scalable format available
// https://docs.gtk.org/gtk3/method.IconTheme.get_icon_sizes.html
//
bool does_icon_size_has_scalable(const std::string &icon_name)
{
    GdkScreen *screen = gdk_screen_get_default();
    GtkIconTheme *gtk_icon_theme = gtk_icon_theme_get_for_screen(screen);

    gint *int_array = gtk_icon_theme_get_icon_sizes(gtk_icon_theme, icon_name.c_str());
    {
        gint *it = int_array;
        while ((*it) != 0)
        {
            {
                if (-1 == *it)
                {
                    g_free(int_array);
                    return true;
                }
            }
            it++;
        }
    }
    g_free(int_array);
    return false;
}

// Note
//
// The return value should be freed using
//
// g_object_unref()
//
GdkPixbuf *get_icon_get_scalable(const std::string &icon_name, const int &size)
{
    GdkScreen *screen = gdk_screen_get_default();
    GtkIconTheme *gtk_icon_theme = gtk_icon_theme_get_for_screen(screen);

    GdkPixbuf *pixbuf = NULL;

    {
        GtkIconInfo *gtk_icon_info = gtk_icon_theme_lookup_icon_for_scale(
            gtk_icon_theme,
            icon_name.c_str(),
            size,
            1, // scale
            GtkIconLookupFlags(
                GTK_ICON_LOOKUP_FORCE_SVG |
                GTK_ICON_LOOKUP_FORCE_SIZE));
        {
            // Debug
            // printf("%s\n",gtk_icon_info_get_filename(gtk_icon_info));

            GError *error = NULL;
            pixbuf = gtk_icon_info_load_icon(gtk_icon_info, &error);
            if (error != NULL)
            {
                std::cout << error->message << std::endl;
                g_error_free(error);

                std::cout << "warning it should not be here" << std::endl;
                std::abort();
            }
        }
        g_object_unref(gtk_icon_info);
    }

    return pixbuf;
}

// Description
//
// Get the largest size for a certain
// icon if there is no scalable format available
//
int get_largest_icon_size_no_scalable(const std::string &icon_name)
{
    int result = 0;
    GdkScreen *screen = gdk_screen_get_default();
    GtkIconTheme *gtk_icon_theme = gtk_icon_theme_get_for_screen(screen);

    gint *int_array = gtk_icon_theme_get_icon_sizes(gtk_icon_theme, icon_name.c_str());
    {
        gint *it = int_array;
        while ((*it) != 0)
        {
            {
                if (result < *it)
                {
                    result = *it;
                }
            }
            it++;
        }
    }
    g_free(int_array);

    return result;
}

// Note
//
// The return value should be freed using
//
// g_object_unref()
//
GdkPixbuf *get_icon_no_scalable(const std::string &icon_name, int size)
{
    GdkScreen *screen = gdk_screen_get_default();
    GtkIconTheme *gtk_icon_theme = gtk_icon_theme_get_for_screen(screen);

    GdkPixbuf *pixbuf = NULL;
    {
        GtkIconInfo *gtk_icon_info = gtk_icon_theme_lookup_icon_for_scale(
            gtk_icon_theme,
            icon_name.c_str(),
            size,
            1, // scale
            GTK_ICON_LOOKUP_GENERIC_FALLBACK);
        {
            // Debug
            // printf("%s\n",gtk_icon_info_get_filename(gtk_icon_info));

            GError *error = NULL;
            pixbuf = gtk_icon_info_load_icon(gtk_icon_info, &error);
            if (error != NULL)
            {
                std::cout << error->message << std::endl;
                g_error_free(error);

                std::cout << "warning it should not be here" << std::endl;
                std::abort();
            }
        }
        g_object_unref(gtk_icon_info);
    }
    return pixbuf;
}

//
// We are assuming we have a valid icon_string from
//         bool has_icon_string = get_desktop_icon_string(desktop_id,icon_string);
// this function is expected to be called inside
//
//         get_largest_desktop_icon(const std::string &desktop_id)
//
//
// Note
//
// The return value should be freed using
//
// g_object_unref()
//
GdkPixbuf *get_largest_desktop_icon_with_icon_name(const std::string &icon_name)
{
    GdkPixbuf *pixbuf = NULL;
    {
        if (does_icon_size_has_scalable(icon_name))
        {
            pixbuf = get_icon_get_scalable(icon_name, LWPANEL_SCALABLE_ICON_MAXIMUM_SIZE);
        }
        else
        {
            int size = get_largest_icon_size_no_scalable(icon_name);
            pixbuf = get_icon_no_scalable(icon_name, size);
        }
    }

    return pixbuf;
}

// Note
//
// The return value should be freed using
//
// g_object_unref()
//
GdkPixbuf *get_largest_desktop_icon_with_icon_filename(const std::string &icon_filename)
{
    GdkPixbuf *pixbuf = NULL;
    {
        GError *error = NULL;

        pixbuf = gdk_pixbuf_new_from_file(icon_filename.c_str(), &error);
        if (error != NULL)
        {
            std::cout << error->message << std::endl;
            g_error_free(error);

            std::cout << "warning it should not be here" << std::endl;
            std::abort();
        }
    }

    return pixbuf;
}

// Note
//
// The return value should be freed using
//
// g_object_unref()
//
GdkPixbuf *get_largest_desktop_icon(const std::string &desktop_id)
{
    std::string icon_string;
    bool has_icon_string = get_desktop_icon_string(desktop_id, icon_string);
    if (!has_icon_string)
    {
        return NULL;
    }

    GdkPixbuf *pixbuf = NULL;
    {
        // We are not sure if the icon_string is using an absolute path or not
        // So we look for an "/" at the beginning of the string
        std::size_t found = icon_string.rfind('/', 0);

        // https://specifications.freedesktop.org/desktop-entry/latest/recognized-keys.html
        //
        // Icon to display in file manager, menus, etc. If the name is
        // an absolute path, the given file will be used. If the name
        // is not an absolute path, the algorithm described in the
        // Icon Theme Specification will be used to locate the icon.

        // this is using icon_name
        if (found == std::string::npos)
        {
            pixbuf = get_largest_desktop_icon_with_icon_name(icon_string);
        }
        else
        {
            // this is using absolute path
            pixbuf = get_largest_desktop_icon_with_icon_filename(icon_string);
        }
    }

    return pixbuf;
}

// Return value
//
// The data is owned by the called function.
//
GtkWidget *get_icon_as_gtk_image_using_gdkpixbuf(
    const int logical_size,
    const gint scale,
    const GdkPixbuf *pixbuf_largest)
{
    g_return_val_if_fail(logical_size > 0, NULL);
    g_return_val_if_fail(scale > 0, NULL);
    g_return_val_if_fail(GDK_IS_PIXBUF(pixbuf_largest), NULL);

    if (nullptr == pixbuf_largest)
    {
        return NULL;
    }
    int real_size = logical_size * scale;

    GtkWidget *image = NULL;
    {
        GdkPixbuf *pixbuf_real = gdk_pixbuf_scale_simple(pixbuf_largest, real_size, real_size, GDK_INTERP_HYPER);
        {
            cairo_surface_t *surface = gdk_cairo_surface_create_from_pixbuf(
                pixbuf_real,
                scale,
                NULL);
            {
                image = gtk_image_new_from_surface(surface);
            }
            cairo_surface_destroy(surface);
        }
        g_object_unref(pixbuf_real);
    }
    return image;
}

// Return value
//
// The data is owned by the called function.
//
GtkWidget *get_largest_desktop_icon_as_gtk_image(LXPanel *panel, const std::string &desktop_id)
{
    GtkWidget *panel_widget = GTK_WIDGET(panel);
    GdkWindow *gdk_window = gtk_widget_get_window(panel_widget);
    gint scale = gdk_window_get_scale_factor(gdk_window);

    int logical_size = panel_get_icon_size(panel);

    GtkWidget *image = NULL;
    {
        GdkPixbuf *pixbuf_largest = get_largest_desktop_icon(desktop_id);
        {
            image = get_icon_as_gtk_image_using_gdkpixbuf(logical_size, scale, pixbuf_largest);
        }
        g_object_unref(pixbuf_largest);
    }
    return image;
}

// Return value
//
// The data is owned by the called function.
//
GtkWidget *get_largest_desktop_icon_as_gtk_image_using_icon_name(LXPanel *panel, const std::string &icon_name)
{
    GtkWidget *panel_widget = GTK_WIDGET(panel);
    GdkWindow *gdk_window = gtk_widget_get_window(panel_widget);
    gint scale = gdk_window_get_scale_factor(gdk_window);

    int logical_size = panel_get_icon_size(panel);

    GtkWidget *image = NULL;
    {
        GdkPixbuf *pixbuf_largest = get_largest_desktop_icon_with_icon_name(icon_name);
        {
            image = get_icon_as_gtk_image_using_gdkpixbuf(logical_size, scale, pixbuf_largest);
        }
        g_object_unref(pixbuf_largest);
    }
    return image;
}
