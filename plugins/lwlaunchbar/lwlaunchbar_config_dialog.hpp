

#ifndef LWLAUNCHBAR_CONFIG_DIALOG_HPP /* Include guard */
#define LWLAUNCHBAR_CONFIG_DIALOG_HPP

#include <string>

#include <gtk/gtk.h>

// TODO fix me
#define GMENU_I_KNOW_THIS_IS_UNSTABLE
#include <gmenu-tree.h>

#include "plugin.h"

// This is created and destroyed according to lwlaunchbar Preferences dialog
class lwlaunchbar_preferences_widget_struct
{
  public:
    GtkWidget *button_add = NULL;
    GtkWidget *button_remove = NULL;
    GtkWidget *button_up = NULL;
    GtkWidget *button_down = NULL;

    GtkWidget *defined_view = NULL;
    GtkWidget *tree_view = NULL;

    GtkWidget *instance = NULL;
};

GMenuTreeItemType get_model_item_menu_type(GtkTreeModel *model, GtkTreeIter *iter);

char *get_model_item_icon_name(GtkTreeModel *model, GtkTreeIter *iter);

char *get_model_item_name(GtkTreeModel *model, GtkTreeIter *iter);

char *get_model_item_desktop_id(GtkTreeModel *model, GtkTreeIter *iter);

int get_indices(GtkTreeModel *model, GtkTreeIter *iter);

void save_data(GtkWidget *dlg);

void read_config_settings_into_defined_view(GtkWidget *instance, GtkWidget *defined_view);

GtkWidget *lwlaunchbar_config(LXPanel *panel, GtkWidget *instance);

#endif // LWLAUNCHBAR_CONFIG_DIALOG_HPP
