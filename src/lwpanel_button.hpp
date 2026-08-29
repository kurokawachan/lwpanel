#ifndef LWPANEL_BUTTON_HPP_ /* Include guard */
#define LWPANEL_BUTTON_HPP_

#include <iostream>
#include <functional>

#include <gio/gdesktopappinfo.h>

#include "plugin.h"

typedef gboolean lwpanel_button_callback(GtkWidget *self, GdkEventButton *event, gpointer user_data);

GtkWidget *lwpanel_button_new(
    LXPanel *panel,
    const char *icon_name,
    const gchar *tooltip_text,
    std::function<lwpanel_button_callback> button_press_callback,
    std::function<lwpanel_button_callback> button_release_callback);

#endif // LWPANEL_BUTTON_HPP_
