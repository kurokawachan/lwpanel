
#ifndef LW_HPP_ /* Include guard */
#define LW_HPP_

#include <iostream>

#include <gio/gdesktopappinfo.h>

#include "plugin.h"

template <typename T>
void GDestroyNotify_template_for_delete_operator(gpointer data)
{
    T *T_data_pointer = (T *)data;
    delete T_data_pointer;
}

const int LWPANEL_SCALABLE_ICON_MAXIMUM_SIZE = 256 * 4;

GtkWidget *get_largest_desktop_icon_as_gtk_image(LXPanel *panel, const std::string &desktop_id);
GtkWidget *get_largest_desktop_icon_as_gtk_image_using_icon_name(LXPanel *panel, const std::string &icon_name);
#endif // LW_HPP_
