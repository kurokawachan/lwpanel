

#ifndef LWLAUNCHBAR_WIDGET_HPP /* Include guard */
#define LWLAUNCHBAR_WIDGET_HPP

#include <gtk/gtk.h>

#include "plugin.h"

// This is created and destroyed according to lwlaunchbar instance
class lwlaunchbar_instance_data_struct
{
  public:
    config_setting_t *settings = NULL;
    LXPanel *panel = NULL;
};

void set_value_for_setting_using_lwlaunchbar_instance(const GtkWidget *instance, LXPanel *&panel, config_setting_t *&settings);

GtkWidget *lwlaunchbar_widget_constructor(LXPanel *panel, config_setting_t *settings);

void update_content(GtkWidget *content_holder);

#endif // LWLAUNCHBAR_WIDGET_HPP
