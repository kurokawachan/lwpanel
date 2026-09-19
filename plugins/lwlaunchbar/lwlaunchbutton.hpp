
#ifndef LWLAUNCHBUTTON_HPP /* Include guard */
#define LWLAUNCHBUTTON_HPP

#include <string>

#include <gtk/gtk.h>

#include "plugin.h"

GtkWidget *lwlaunchbutton_new(LXPanel *panel, const std::string &desktop_id);

#endif // LWLAUNCHBUTTON_HPP
