
#ifndef LW_HPP_ /* Include guard */
#define LW_HPP_

#include <gio/gdesktopappinfo.h>
#include "plugin.h"

const int LWPANEL_SCALABLE_ICON_MAXIMUM_SIZE = 256 * 4;

// ***************************************************************
// Below is C++ only function ************************************
// ***************************************************************
#ifdef __cplusplus

#include <iostream>

template <typename T>
void GDestroyNotify_template_for_delete_operator(gpointer data)
{
    T *T_data_pointer = (T *)data;
    delete T_data_pointer;
}

GtkWidget *get_largest_desktop_icon_as_gtk_image(LXPanel *panel, const std::string &desktop_id);
GtkWidget *get_largest_desktop_icon_as_gtk_image_using_icon_name(LXPanel *panel, const std::string &icon_name);

#endif
// ***************************************************************
// Above is C++ only function ************************************
// ***************************************************************

// ***************************************************************
// Below is C function *******************************************
// ***************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

    GtkWidget *lwpanel_icon_new_from_icon_name(LXPanel *panel, const gchar *icon_name);
    void lwpanel_icon_set_from_icon_name(GtkImage *icon, LXPanel *panel, const gchar *icon_name);

#ifdef __cplusplus
}
#endif
// ***************************************************************
// Above is C function *******************************************
// ***************************************************************

#endif // LW_HPP_
