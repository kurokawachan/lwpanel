project(
    'lxpanel',
    'c',
    default_options: ['prefix=/usr/'],
    meson_version: '>=1.11.0',
    version: '0.11.1',
)

# top_srcdir = meson.project_source_root()

PACKAGE_NAME = meson.project_name()
install_subdir_package_name = meson.project_name()
PACKAGE_NAME = 'lxpanel'
GETTEXT_PACKAGE = 'lxpanel'
# message(PACKAGE_NAME)

VERSION_MAJOR = '0'
VERSION_MINOR = '11'
VERSION_MICRO = '1'

PACKAGE_VERSION = '0.11.1'
PACKAGE_BUGREPORT = 'http://lxde.org/'
PACKAGE_URL = ''


ENABLE_MENU_CACHE = true
BUILD_PLUGIN_LOADER = true



# For debian it should be '/usr/'
# meson configure -Dprefix=/usr/
# '/usr'
prefix = get_option('prefix')

# 'include'
includedir = get_option('includedir')

# For debian it should be 'share'
# 'share'
datadir = get_option('datadir')

# '/etc'
sysconfdir = get_option('sysconfdir')



# When this repo was previously built by makefile
# sometimes 'libdir' would be '/usr/lib/x86_64-linux-gnu/'
# While right now, it would mean 'lib/x86_64-linux-gnu'
# So we have a comment here
# libdir = '/usr/lib/x86_64-linux-gnu/'

# PLUGIN_DIR_NAME = 'plugins'
# PACKAGE_LIB_DIR = '/usr/lib/x86_64-linux-gnu/'
libdir = get_option('libdir')



# It looks like meson does not have 'exec_prefix'
# https://github.com/mesonbuild/meson/issues/364
exec_prefix = prefix
# bindir = exec_prefix / get_option('bindir')
# target_install_bindir = exec_prefix / get_option('bindir')





# localedir = 'share/locale'
localedir = get_option('localedir')








# '/usr/bin'
target_install_bindir = prefix / get_option('bindir')



# '/usr/lib/x86_64-linux-gnu/'
target_install_libdir = prefix / get_option('libdir')
# '/usr/lib/x86_64-linux-gnu/lxpanel/'
target_install_libdir_project_dir = prefix / get_option('libdir') / PACKAGE_NAME
# '/usr/lib/x86_64-linux-gnu/lxpanel/plugins/'
target_install_libdir_project_dir_plugin_dir = prefix / get_option('libdir') / PACKAGE_NAME / 'plugins'



# '/usr/include'
target_install_includedir = prefix / includedir / PACKAGE_NAME
# '/usr/include/lxpanel'
target_install_includedir_project_dir = prefix / includedir / PACKAGE_NAME



# '/etc/xdg/lxpanel'
target_install_sysconfdir_xdg_project_dir = sysconfdir / 'xdg' / PACKAGE_NAME



# '/usr/share'
target_install_datadir = prefix / get_option('datadir')
# '/usr/share/lxpanel'
target_install_datadir_project_dir = prefix / datadir / install_subdir_package_name
# '/usr/share/lxpanel/ui'
target_install_datadir_project_dir_ui_dir = prefix / datadir / install_subdir_package_name / 'ui'

# '/usr/share/lxpanel/images'
target_install_datadir_project_dir_images_dir = prefix / datadir / install_subdir_package_name / 'images'
# '/usr/share/lxpanel/images/xkb-flags'
target_install_datadir_project_dir_images_dir_xkbflags_dir = prefix / datadir / install_subdir_package_name / 'images' / 'xkb-flags'
# '/usr/share/lxpanel/images/xkb-flags-cust'
target_install_datadir_project_dir_images_dir_xkbflagscust_dir = prefix / datadir / install_subdir_package_name / 'images' / 'xkb-flags-cust'


# '/usr/share/lxpanel/xkeyboardconfig'
target_install_datadir_project_dir_xkeyboardconfig_dir = prefix / datadir / install_subdir_package_name / 'xkeyboardconfig'



# '/usr/share/locale'
target_install_localedir = prefix / get_option('localedir')





add_project_arguments(
    '-DGETTEXT_PACKAGE="@0@"'.format(GETTEXT_PACKAGE),
    language: 'c',
)




gtk_module = dependency('gtk+-3.0')
GTK_LIBS = gtk_module




# libfm-gtk3
cc = meson.get_compiler('c')
lib_fm_gtk3 = dependency('libfm-gtk3', version: '>= 1.2.0')
# libiw-dev
iw_dep = cc.find_library('iw', required: true)
# libc6-dev
lm_dep = cc.find_library('m', required: true)

pkg_modules = [lib_fm_gtk3, dependency('libwnck-3.0')]

MENU_CACHE_LIBS = [
    dependency('libmenu-cache'),
    dependency('glib-2.0'),
]

pkg_modules += [
    dependency('gio-unix-2.0'),
    dependency('gthread-2.0'),
    dependency('gmodule-2.0'),
]
PACKAGE_LIBS = [
    pkg_modules,
    MENU_CACHE_LIBS,
    # dependency('libfm'), # TODO if we don't add this, it seems does not affect anything
]




# 'keybinder-3.0'
keybinder_module = dependency('keybinder-3.0')
KEYBINDER_LIBS = keybinder_module



X11_LIBS = dependency('x11')







# Generate 'src/panel.h' ********************************************
# data below ********************************************************
src_panel_h_conf_data = configuration_data()
src_panel_h_conf_data.set('VERSION_MAJOR', VERSION_MAJOR)
src_panel_h_conf_data.set('VERSION_MINOR', VERSION_MINOR)
src_panel_h_conf_data.set('VERSION_MICRO', VERSION_MICRO)
src_panel_h = configure_file(
    configuration: src_panel_h_conf_data,
    input: 'src/panel.h.in',
    # This file was originally generated at 'src/panel.h'
    # However, as the meson would like to put all
    # the generated files inside the build directory
    # This file would be generated inside the build dir
    output: 'panel.h',
    # install_dir: target_install_includedir_project_dir,
)
# data before *******************************************************
# Generate 'src/panel.h' ********************************************









# Generate 'config.h' ***********************************************
# data below ********************************************************
cc = meson.get_compiler('c')
config_h_conf_data = configuration_data()
# TODO
# Not sure what to do
# # /* Define to disable using ALSA in 'volume' plugin. */
# config_h_conf_data.set('DISABLE_ALSA', 1)
# # /* Disable menu related routines */
# config_h_conf_data.set('DISABLE_MENU', 1)
# # /* Disable plugin loading */
# config_h_conf_data.set('DISABLE_PLUGINS_LOADING', 1)
# TODO
# we should know if ENABLE_NLS
config_h_conf_data.set('ENABLE_NLS', 1)
config_h_conf_data.set('GETTEXT_PACKAGE', '"@0@"'.format(GETTEXT_PACKAGE))
if cc.has_header('alsa/asoundlib.h')
    config_h_conf_data.set('HAVE_ALSA_ASOUNDLIB_H', 1)
endif
if cc.has_function('bind_textdomain_codeset')
    config_h_conf_data.set('HAVE_BIND_TEXTDOMAIN_CODESET', 1)
endif
if cc.has_function('bzero')
    config_h_conf_data.set('HAVE_BZERO', 1)
endif
# Mac OS X function
# config_h_conf_data.set('HAVE_CFLOCALECOPYCURRENT', 1)
# config_h_conf_data.set('HAVE_CFPREFERENCESCOPYAPPVALUE', 1)
if cc.has_function('dcgettext')
    config_h_conf_data.set('HAVE_DCGETTEXT', 1)
endif
if cc.has_header('dlfcn.h')
    config_h_conf_data.set('HAVE_DLFCN_H', 1)
endif
if cc.has_function('gettext')
    config_h_conf_data.set('HAVE_GETTEXT', 1)
endif
if cc.has_header('inttypes.h')
    config_h_conf_data.set('HAVE_INTTYPES_H', 1)
endif
# Define if your <locale.h> file defines LC_MESSAGES
if cc.has_define('LC_MESSAGES', prefix: '#include <locale.h>')
    config_h_conf_data.set('HAVE_LC_MESSAGES', 1)
endif

# TODO
# As we have migrated to meson, we are able to check
# if we have the header files. However, we are not
# sure why in the 'config.h' generated by makefile
# from 'config.h.in' does not have this line.
#
# Generated by makefile
# /* #undef HAVE_LINUX_SOUNDCARD_H */
#
# Generated by meson
# #define HAVE_LINUX_SOUNDCARD_H 1
#
# not sure what was done in the makefile config.h
if cc.has_header('linux/soundcard.h')
    config_h_conf_data.set('HAVE_LINUX_SOUNDCARD_H', 1)
endif

if cc.has_header('locale.h')
    config_h_conf_data.set('HAVE_LOCALE_H', 1)
endif
if cc.has_function('malloc')
    config_h_conf_data.set('HAVE_MALLOC', 1)
endif
if cc.has_function('memset')
    config_h_conf_data.set('HAVE_MEMSET', 1)
endif
# if cc.has_function('menu_cache_dir_list_children')
if cc.has_function(
    'menu_cache_dir_list_children',
    dependencies: dependency('libmenu-cache'),
)
    config_h_conf_data.set('HAVE_MENU_CACHE_DIR_LIST_CHILDREN', 1)
endif
if cc.has_function('mkdir')
    config_h_conf_data.set('HAVE_MKDIR', 1)
endif
if cc.has_function('setlocale')
    config_h_conf_data.set('HAVE_SETLOCALE', 1)
endif
#
# https://www.manpagez.com/info/autoconf/autoconf-2.64/autoconf_49.php
# From AC_FUNC_STAT
# These macros are obsolescent, as no current systems have the bug.
# New programs need not use these macros
#
# config_h_conf_data.set('HAVE_STAT_EMPTY_STRING_BUG', 1)
#
if cc.has_header('stdint.h')
    config_h_conf_data.set('HAVE_STDINT_H', 1)
endif
if cc.has_header('stdio.h')
    config_h_conf_data.set('HAVE_STDIO_H', 1)
endif
if cc.has_header('stdlib.h')
    config_h_conf_data.set('HAVE_STDLIB_H', 1)
endif
if cc.has_function('strchr')
    config_h_conf_data.set('HAVE_STRCHR', 1)
endif
if cc.has_function('strftime')
    config_h_conf_data.set('HAVE_STRFTIME', 1)
endif
if cc.has_header('strings.h')
    config_h_conf_data.set('HAVE_STRINGS_H', 1)
endif
if cc.has_header('string.h')
    config_h_conf_data.set('HAVE_STRING_H', 1)
endif
# TODO
# As we have migrated to meson, we are able to check
# if we have the header files. However, we are not
# sure why in the 'config.h' generated by makefile
# from 'config.h.in' does not have this line.
#
# Generated by makefile
# /* #undef HAVE_SYS_SOUNDCARD_H */
#
# Generated by meson
# #define HAVE_SYS_SOUNDCARD_H 1
#
if cc.has_header('sys/soundcard.h')
    config_h_conf_data.set('HAVE_SYS_SOUNDCARD_H', 1)
endif
if cc.has_header('sys/stat.h')
    config_h_conf_data.set('HAVE_SYS_STAT_H', 1)
endif
if cc.has_header('sys/time.h')
    config_h_conf_data.set('HAVE_SYS_TIME_H', 1)
endif
if cc.has_header('sys/types.h')
    config_h_conf_data.set('HAVE_SYS_TYPES_H', 1)
endif
if cc.has_header('sys/wait.h')
    config_h_conf_data.set('HAVE_SYS_WAIT_H', 1)
endif
if cc.has_header('unistd.h')
    config_h_conf_data.set('HAVE_UNISTD_H', 1)
endif
# /* Define to 1 if `lstat' dereferences a symlink specified with a trailing slash. */
# From AC_FUNC_LSTAT_FOLLOWS_SLASHED_SYMLINK
config_h_conf_data.set('LSTAT_FOLLOWS_SLASHED_SYMLINK', 1)
# /* Define to the sub-directory where libtool stores uninstalled libraries. */
config_h_conf_data.set('LT_OBJDIR', '".libs/"')
config_h_conf_data.set('PACKAGE', '"@0@"'.format(PACKAGE_NAME))
config_h_conf_data.set('PACKAGE_BUGREPORT', '"@0@"'.format(PACKAGE_BUGREPORT))
config_h_conf_data.set('PACKAGE_NAME', '"@0@"'.format(PACKAGE_NAME))
config_h_conf_data.set(
    'PACKAGE_STRING',
    '"@0@ @1@"'.format(PACKAGE_NAME, PACKAGE_VERSION),
)
config_h_conf_data.set('PACKAGE_TARNAME', '"@0@"'.format(PACKAGE_NAME))
config_h_conf_data.set('PACKAGE_URL', '"@0@"'.format(PACKAGE_URL))
config_h_conf_data.set('PACKAGE_VERSION', '"@0@"'.format(PACKAGE_VERSION))
# As of 2026.7 no source code use this
# data below *********************************************************
# from AC_TYPE_SIGNAL
config_h_conf_data.set('RETSIGTYPE', 'void')
# From AC_HEADER_STDC
config_h_conf_data.set('STDC_HEADERS', 1)
# From AC_STRUCT_TM
# config_h_conf_data.set('TM_IN_SYS_TIME', 1)
# data above *********************************************************

config_h_conf_data.set('VERSION', '"@0@"'.format(PACKAGE_VERSION))

# From AC_C_CONST
# config_h_conf_data.set('const', 1)
# From AC_C_INLINE
# config_h_conf_data.set('inline', 1)
# From AC_FUNC_MALLOC
# config_h_conf_data.set('malloc', 1)

config_h = configure_file(
    input: 'config.h.meson.in',
    # This file was originally generated at 'config.h'
    # However, as the meson would like to put all
    # the generated files inside the build directory
    # This file would be generated inside the build dir
    output: 'config.h',
    configuration: config_h_conf_data,
)
# data before *******************************************************
# Generate 'config.h' ***********************************************








# liblxpanel_la below ******************************************************

#     -I$(top_srcdir) \
#     -DPACKAGE_LIB_DIR=\""$(target_install_libdir)"\" \
#     -DPACKAGE_DATA_DIR=\""$(target_install_datadir)/lxpanel"\" \
#     -DPACKAGE_UI_DIR=\""$(target_install_datadir)/lxpanel/ui"\" \
#     -DPACKAGE_BIN_DIR=\""$(target_install_bindir)"\" \
#     -DPACKAGE_LOCALE_DIR=\""target_install_datadir/locale"\" \
#     $(GTK_CFLAGS) \
#     $(PACKAGE_CFLAGS) \
#     $(KEYBINDER_CFLAGS) \
#     $(G_CAST_CHECKS)

lxpanel_CPPFLAGS = [
    '-DPACKAGE_LIB_DIR="@0@"'.format(target_install_libdir),
    '-DPACKAGE_DATA_DIR="@0@"'.format(target_install_datadir_project_dir),
    '-DPACKAGE_UI_DIR="@0@"'.format(target_install_datadir_project_dir_ui_dir),
    '-DPACKAGE_BIN_DIR="@0@"'.format(target_install_bindir),
    '-DPACKAGE_LOCALE_DIR="@0@"'.format(target_install_localedir),
    # TODO fix it
    '-DHAVE_CONFIG_H',
    # TODO I don't know how to add the following
    #     $(GTK_CFLAGS) \
    #     $(PACKAGE_CFLAGS) \
    #     $(KEYBINDER_CFLAGS) \
    #     $(G_CAST_CHECKS)
]

liblxpanel_la_SOURCES = [
    'src/misc.c',
    'src/configurator.c',
    'src/dbg.c',
    'src/ev.c',
    'src/icon-grid.c',
    'src/panel.c',
    'src/panel-plugin-move.c',
    'src/plugin.c',
    'src/conf.c',
    'src/space.c',
    'src/input-button.c',
]


# The manual for the following
# Link mode is in this link
# https://www.gnu.org/software/libtool/manual/html_node/Link-mode.html
# liblxpanel_la_LDFLAGS = \
# 	-no-undefined \
# 	-version-info 0:0:0


liblxpanel_la = shared_library(
    'lxpanel',
    sources: liblxpanel_la_SOURCES,
    c_args: lxpanel_CPPFLAGS,
    link_args: [
        # In meson, b_lundef is default true
        # and does not allow undefined symbols when linking
        # '-no-undefined',
        # '-version-info 0:0:0',
],
    version: '0.0.0',
    dependencies: [
        GTK_LIBS,
        PACKAGE_LIBS,
        KEYBINDER_LIBS,
        X11_LIBS,
    ],
    install: true,
    install_dir: target_install_libdir_project_dir,
    install_tag: 'lxpanel',
)

# liblxpanel_la above ******************************************************






# libbuiltin_plugins_a below ***********************************************

libbuiltin_plugins_sources = [
    'plugins/dclock.c',
    'plugins/dirmenu.c',
    'plugins/launchtaskbar.c',
    'plugins/task-button.c',
    'plugins/launch-button.c',
    'plugins/pager.c',
    'plugins/separator.c',
    'plugins/tray.c',
    'plugins/wincmd.c',
]
if (ENABLE_MENU_CACHE == true)
    # MENU_SOURCES = 'plugins/menu.c'
    libbuiltin_plugins_sources += 'plugins/menu.c'
endif





# AM_LDFLAGS = \
# 	-module -avoid-version -shared -export-dynamic \
# 	-no-undefined -rpath $(libdir)/lxpanel/plugins \
# 	$(top_builddir)/src/liblxpanel.la \
# 	$(GTK_LIBS) \
# 	$(PACKAGE_LIBS)



libbuiltin_plugins_a = static_library(
    'libbuiltin_plugins.a',
    include_directories: ['src/'],
    sources: libbuiltin_plugins_sources,
    c_args: [
        '-DPACKAGE_DATA_DIR="@0@"'.format(target_install_datadir_project_dir),
        '-DPACKAGE_UI_DIR="@0@"'.format(
            target_install_datadir_project_dir_ui_dir,
        ),
        '-DPACKAGE_LOCALE_DIR="@0@"'.format(target_install_localedir),
    ],
    link_with: [liblxpanel_la],
    link_args: [
        '-module -avoid-version',
        '-shared',
        '--export-dynamic',
        '--no-undefined',
            # '$(top_builddir)/src/liblxpanel.la',
            # '-rpath @0@/lxpanel/plugins'.format(target_install_libdir),
    ],
    install_rpath: target_install_libdir_project_dir_plugin_dir,
    dependencies: [
        GTK_LIBS,
        PACKAGE_LIBS,
    ],
)



# libbuiltin_plugins_a above ***********************************************



# lxpanel below ************************************************************

lxpanel_include_HEADERS = [
    'src/plugin.h',
    # 'src/panel.h',
    # This file was originally generated by makefile
    # from 'src/panel.h.in'
    # When migrating to meson, this file would be generated
    # inside the build dir. So the filename would be different
    src_panel_h,
    'src/misc.h',
    'src/icon-grid.h',
    'src/conf.h',
]





lxpanel_SOURCES = [
    'src/icon-grid-old.c',
    'src/bg.c',
    'src/gtk-run.c',
    'src/main.c',
]

if (ENABLE_MENU_CACHE == true)
    # MENU_SOURCES = './src/menu-policy.c'
    lxpanel_SOURCES += 'src/menu-policy.c'
endif




# TODO
# In meson executable() there is arg named 'export_dynamic'
# Not sure if we should migrate it using that
lxpanel_LDFLAGS = ''
if (BUILD_PLUGIN_LOADER == true)
    lxpanel_LDFLAGS = '-export-dynamic'
endif



lxpanel = executable(
    'lxpanel',
    sources: [lxpanel_SOURCES, lxpanel_include_HEADERS],
    c_args: lxpanel_CPPFLAGS,
    link_with: [
        liblxpanel_la,
        libbuiltin_plugins_a,
    ],
    link_args: lxpanel_LDFLAGS,
    dependencies: [
        GTK_LIBS,
        PACKAGE_LIBS,
        KEYBINDER_LIBS,
        X11_LIBS,
    ],
    install: true,
    # install_dir: '/usr/bin/',
    install_dir: target_install_bindir,
    install_rpath: target_install_libdir_project_dir,
    install_tag: 'lxpanel',
)


# lxpanel above ************************************************************


# lxpanelctl below *********************************************************


lxpanelctl_SOURCES = [
    'src/lxpanelctl.c',
    'src/lxpanelctl.h',
]

lxpanelctl = executable(
    'lxpanelctl',
    sources: lxpanelctl_SOURCES,
    dependencies: [
        X11_LIBS,
    ],
    install: true,
    # install_dir: '/usr/bin/',
    install_dir: target_install_bindir,
    install_tag: 'lxpanel',
)


# lxpanelctl above *********************************************************





# batt_la below ************************************************************
batt_la_SOURCES = [
    'plugins/batt/batt.c',
    'plugins/batt/batt_sys.c',
]
# batt_la_CFLAGS = '-I$(srcdir)/batt'

batt_la = shared_library(
    # '/lxpanel/plugins/batt',
    'batt',
    name_prefix: '',  # get rid of 'lib' prefix
    build_subdir: 'build_subdir_plugins_subdir',
    include_directories: [
        '.',
        'src/',
    ],
    sources: [
        batt_la_SOURCES,
    ],
    link_with: [liblxpanel_la],
    dependencies: [
        GTK_LIBS,
    ],
    install: true,
    install_dir: target_install_libdir_project_dir_plugin_dir,
    install_tag: 'lxpanel',
)

# batt_la above ************************************************************




# cpu_la below *************************************************************
cpu_la_SOURCES = 'plugins/cpu/cpu.c'

cpu_la = shared_library(
    # '/lxpanel/plugins/cpu',
    'cpu',
    name_prefix: '',  # get rid of 'lib' prefix
    build_subdir: 'build_subdir_plugins_subdir',
    include_directories: [
        '.',
        'src/',
    ],
    sources: [cpu_la_SOURCES],
    link_with: [liblxpanel_la],
    dependencies: [
        GTK_LIBS,
    ],
    install: true,
    install_dir: target_install_libdir_project_dir_plugin_dir,
    install_tag: 'lxpanel',
)

# cpu_la above *************************************************************




# cpufreq_la below *********************************************************
cpufreq_la_SOURCES = 'plugins/cpufreq/cpufreq.c'

cpufreq_la = shared_library(
    # '/lxpanel/plugins/cpufreq',
    'cpufreq',
    name_prefix: '',  # get rid of 'lib' prefix
    build_subdir: 'build_subdir_plugins_subdir',
    include_directories: [
        '.',
        'src/',
    ],
    sources: [cpufreq_la_SOURCES],
    link_with: [liblxpanel_la],
    dependencies: [
        GTK_LIBS,
    ],
    install: true,
    install_dir: target_install_libdir_project_dir_plugin_dir,
    install_tag: 'lxpanel',
)
# cpufreq_la above *********************************************************




# deskno_la below **********************************************************
deskno_la_SOURCES = 'plugins/deskno/deskno.c'

deskno_la = shared_library(
    # '/lxpanel/plugins/deskno',
    'deskno',
    name_prefix: '',  # get rid of 'lib' prefix
    build_subdir: 'build_subdir_plugins_subdir',
    include_directories: [
        '.',
        'src/',
    ],
    sources: [deskno_la_SOURCES],
    link_with: [liblxpanel_la],
    dependencies: [
        GTK_LIBS,
    ],
    install: true,
    install_dir: target_install_libdir_project_dir_plugin_dir,
    install_tag: 'lxpanel',
)
# deskno_la above **********************************************************






# indicator_la below *******************************************************
# TODO not sure why debian does not build this file
# https://packages.debian.org/bookworm/amd64/lxpanel/filelist
# https://packages.debian.org/trixie/amd64/lxpanel/filelist
# indicator_la_SOURCES = 'plugins/indicator/indicator.c'
#
# # indicator_la_CFLAGS = \
# #         -DINDICATOR_DIR=\""$(INDICATORDIR)"\" \
# #         -DINDICATOR_ICONS_DIR=\""$(INDICATORICONSDIR)"\" \
# #         $(APPLET_CFLAGS)
# indicator_la_LIBADD = $(APPLET_LIBS)
#
# indicator_la = shared_library('/lxpanel/plugins/indicator',
#   # name_prefix: '' , # get rid of 'lib' prefix
#   include_directories: ['src/'],
#   sources:[indicator_la_SOURCES],
#   link_with: [
#     liblxpanel_la
#     ],
#   dependencies:[
#     GTK_LIBS,
#     ],
#   )

# indicator_la above *******************************************************






# kbled_la below ***********************************************************
kbled_la_SOURCES = 'plugins/kbled/kbled.c'
# kbled_la_LIBADD = $(X11_LIBS)

kbled_la = shared_library(
    # '/lxpanel/plugins/kbled',
    'kbled',
    name_prefix: '',  # get rid of 'lib' prefix
    build_subdir: 'build_subdir_plugins_subdir',
    include_directories: [
        '.',
        'src/',
    ],
    sources: [kbled_la_SOURCES],
    link_with: [liblxpanel_la],
    dependencies: [
        GTK_LIBS,
        X11_LIBS,
    ],
    install: true,
    install_dir: target_install_libdir_project_dir_plugin_dir,
    install_tag: 'lxpanel',
)
# kbled_la above ***********************************************************






# monitors_la below ********************************************************
monitors_la_SOURCES = 'plugins/monitors/monitors.c'

monitors_la = shared_library(
    # '/lxpanel/plugins/monitors',
    'monitors',
    name_prefix: '',  # get rid of 'lib' prefix
    build_subdir: 'build_subdir_plugins_subdir',
    include_directories: [
        '.',
        'src/',
    ],
    sources: [monitors_la_SOURCES],
    link_with: [liblxpanel_la],
    dependencies: [
        GTK_LIBS,
        lib_fm_gtk3,
    ],
    install: true,
    install_dir: target_install_libdir_project_dir_plugin_dir,
    install_tag: 'lxpanel',
)
# monitors_la above ********************************************************





# netstat_la below *********************************************************
netstat_la_SOURCES = [
    'plugins/netstat/netstat.c',
    'plugins/netstat/devproc.c',
    'plugins/netstat/statusicon.c',
    'plugins/netstat/wireless.c',
    'plugins/netstat/lxnm_client.c',
    'plugins/netstat/passwd_gui.c',
]
# netstat_la_CFLAGS = '-I$(srcdir)/netstat'
# netstat_la_LIBADD = '-liw'
netstat_la = shared_library(
    # '/lxpanel/plugins/netstat',
    'netstat',
    name_prefix: '',  # get rid of 'lib' prefix
    build_subdir: 'build_subdir_plugins_subdir',
    include_directories: [
        '.',
        'src/',
    ],
    sources: [netstat_la_SOURCES],
    link_args: [
        # https://github.com/HewlettPackard/wireless-tools/issues/4
        # '-liw',  # TODO not sure why libiw-dev has no pkg-config file
        # '-lm',
],
    link_with: [liblxpanel_la],
    dependencies: [
        GTK_LIBS,
        iw_dep,
        lm_dep,
    ],
    install: true,
    install_dir: target_install_libdir_project_dir_plugin_dir,
    install_tag: 'lxpanel',
)

# netstat_la above *********************************************************




# netstatus_la below *******************************************************
netstatus_la_SOURCES = [
    'plugins/netstatus/netstatus.c',
    'plugins/netstatus/netstatus-dialog.c',
    'plugins/netstatus/netstatus-enums.c',
    'plugins/netstatus/netstatus-icon.c',
    'plugins/netstatus/netstatus-iface.c',
    'plugins/netstatus/netstatus-sysdeps.c',
    'plugins/netstatus/netstatus-util.c',
]
netstatus_la_CFLAGS = [
    # '-I$(srcdir)/netstatus',
    '-DPACKAGE_UI_DIR="@0@"'.format(target_install_datadir_project_dir_ui_dir),
]
netstatus_la = shared_library(
    # '/lxpanel/plugins/netstatus',
    'netstatus',
    name_prefix: '',  # get rid of 'lib' prefix
    build_subdir: 'build_subdir_plugins_subdir',
    include_directories: [
        '.',
        'src/',
    ],
    sources: [netstatus_la_SOURCES],
    c_args: netstatus_la_CFLAGS,
    link_with: [liblxpanel_la],
    link_args: [
        # '-lm',
],
    dependencies: [
        GTK_LIBS,
        lib_fm_gtk3,
        lm_dep,
    ],
    install: true,
    install_dir: target_install_libdir_project_dir_plugin_dir,
    install_tag: 'lxpanel',
)
# netstatus_la above *******************************************************



# thermal_la below *********************************************************

thermal_la_SOURCES = 'plugins/thermal/thermal.c'

thermal_la = shared_library(
    # '/lxpanel/plugins/thermal',
    'thermal',
    name_prefix: '',  # get rid of 'lib' prefix
    build_subdir: 'build_subdir_plugins_subdir',
    include_directories: [
        '.',
        'src/',
    ],
    sources: [thermal_la_SOURCES],
    link_with: [
        liblxpanel_la,
    ],
    dependencies: [
        GTK_LIBS,
    ],
    install: true,
    install_dir: target_install_libdir_project_dir_plugin_dir,
    install_tag: 'lxpanel',
)
# thermal_la above *********************************************************




# volume_la below **********************************************************

volume_la_SOURCES = 'plugins/volumealsa/volumealsa.c'
# volume_la  = static_library('volume.la',
# volume_la  = library('volume',
# volume_la  = shared_library('volume',
volume_la = shared_library(
    # '/lxpanel/plugins/volume',
    'volume',
    name_prefix: '',  # get rid of 'lib' prefix
    # build_subdir :'lxpanel/plugins' ,
    build_subdir: 'build_subdir_plugins_subdir',
    # install_dir :'lxpanel/plugins/' ,
    # name_prefix: '' , # get rid of 'lib' prefix
    include_directories: [
        '.',
        'src/',
    ],
    sources: [volume_la_SOURCES],
    c_args: [],
    link_with: [
        liblxpanel_la,
    ],
    link_args: [
        # '-lm',
],
    dependencies: [
        GTK_LIBS,
        dependency('alsa'),  # volume_la_LIBADD = '-lasound'
        lib_fm_gtk3,
        lm_dep,
    ],
    install: true,
    install_dir: target_install_libdir_project_dir_plugin_dir,
    install_tag: 'lxpanel',
)

# volume_la above **********************************************************







# weather_la above *********************************************************
# TODO fix bug before do meson
weather_la_SOURCES = [
    'plugins/weather/logutil.c',
    'plugins/weather/httputil.c',
    'plugins/weather/openweathermap.c',
    'plugins/weather/location.c',
    'plugins/weather/forecast.c',
    'plugins/weather/weatherwidget.c',
    'plugins/weather/weather.c',
]
weather_la_CFLAGS = [
    # '-I$(srcdir)/weather',
    # '$(LIBXML2_CFLAGS)',
    # '$(CURL_CFLAGS)',
    # TODO fix it
    '-DHAVE_CONFIG_H',
]
# weather_la_LIBADD = \
#         $(LIBXML2_LIBS) \
#         $(CURL_LIBS)
weather_la = shared_library(
    # '/lxpanel/plugins/weather',
    'weather',
    name_prefix: '',  # get rid of 'lib' prefix
    build_subdir: 'build_subdir_plugins_subdir',
    include_directories: [
        '.',
        'src/',
    ],
    sources: [weather_la_SOURCES],
    c_args: weather_la_CFLAGS,
    link_with: [liblxpanel_la],
    dependencies: [
        GTK_LIBS,
        dependency('libxml-2.0'),
        dependency('libcurl'),
    ],
    install: true,
    install_dir: target_install_libdir_project_dir_plugin_dir,
    install_tag: 'lxpanel',
)

# weather_la above *********************************************************






# xkb_la below *************************************************************
xkb_la_CFLAGS = [
    # '-I$(srcdir)/xkb',
    '-DFLAGSDIR="@0@"'.format(
        target_install_datadir_project_dir_images_dir_xkbflags_dir,
    ),
    '-DFLAGSCUSTDIR="@0@"'.format(
        target_install_datadir_project_dir_images_dir_xkbflagscust_dir,
    ),
    '-DXKBCONFDIR="@0@"'.format(
        target_install_datadir_project_dir_xkeyboardconfig_dir,
    ),
]
xkb_la_SOURCES = [
    'plugins/xkb/xkb-plugin.c',
    'plugins/xkb/xkb.c',
]
# xkb_la_LIBADD = $(X11_LIBS)

# xkeyboardconfigdir=$(target_install_datadir)/lxpanel/xkeyboardconfig
# xkeyboardconfig_DATA = \
#         xkb/xkeyboardconfig/models.cfg \
#         xkb/xkeyboardconfig/layouts.cfg \
#         xkb/xkeyboardconfig/toggle.cfg

xkb_la = shared_library(
    # '/lxpanel/plugins/xkb',
    'xkb',
    name_prefix: '',  # get rid of 'lib' prefix
    build_subdir: 'build_subdir_plugins_subdir',
    include_directories: [
        '.',
        'src/',
    ],
    sources: [xkb_la_SOURCES],
    c_args: xkb_la_CFLAGS,
    link_with: [
        liblxpanel_la,
    ],
    dependencies: [
        GTK_LIBS,
        X11_LIBS,
    ],
    install: true,
    install_dir: target_install_libdir_project_dir_plugin_dir,
    install_tag: 'lxpanel',
)
# xkb_la above *************************************************************


# man below *********************************************************
install_man(
    [
        'man/lxpanel.1',
        'man/lxpanelctl.1',
    ],
    install_tag: 'lxpanel',
)
# man above *********************************************************




# '/usr/share/apport/package-hooks/source_lxpanel.py' ****************
# data below *********************************************************
install_data(
    'debian/local/source_lxpanel.py',
    # install_dir: '/usr/share/apport/package-hooks/',
    install_dir: prefix / 'share/apport/package-hooks/',
    install_tag: 'lxpanel-data',
)
# data above *********************************************************
# '/usr/share/apport/package-hooks/source_lxpanel.py' ****************



# '/usr/share/doc/lxpanel-data/copyright' ****************************
# data below *********************************************************
install_data(
    'debian/copyright',
    # install_dir: '/usr/share/doc/lxpanel-data/copyright',
    install_dir: prefix / 'share/doc/lxpanel-data/copyright',
    install_tag: 'lxpanel-data',
)
# data above *********************************************************
# '/usr/share/doc/lxpanel-data/copyright' ****************************





# '/usr/share/lintian/overrides/lxpanel' *****************************
# data below *********************************************************
install_data(
    'debian/lxpanel.lintian-overrides',
    rename: 'lxpanel',
    # install_dir: '/usr/share/lintian/overrides/',
    install_dir: prefix / 'share/lintian/overrides/',
    install_tag: 'lxpanel',
)
# data above *********************************************************
# '/usr/share/lintian/overrides/lxpanel' *****************************


# '/usr/share/man/man5/lxpanel.hints.5.gz' **************************
# man below *********************************************************
install_man(
    [
        'debian/manpages/lxpanel.hints.5',
    ],
    install_tag: 'lxpanel',
)
# man above *********************************************************
# '/usr/share/man/man5/lxpanel.hints.5.gz' **************************


# data below *********************************************************
install_data(
    'debian/desktop/lxde-x-terminal-emulator.desktop',
    # install_dir: '/usr/share/applications/',
    install_dir: prefix / 'share/applications/',
    install_tag: 'lxpanel',
)
install_data(
    'debian/desktop/lxde-x-www-browser.desktop',
    # install_dir: '/usr/share/applications/',
    install_dir: prefix / 'share/applications/',
    install_tag: 'lxpanel',
)
# data above *********************************************************









# data below *********************************************************
# gettext ************************************************************

subdir('po')

# gettext ************************************************************
# data above *********************************************************



# data below *********************************************************
install_data(
    [
        'data/images/background.png',
        'data/images/capslock-off.png',
        'data/images/capslock-on.png',
        'data/images/clock.png',
        'data/images/cpufreq.png',
        'data/images/file-manager.png',
        'data/images/gnome-fs-desktop.png',
        'data/images/gnome-logout.png',
        'data/images/mute.png',
        'data/images/my-computer.png',
        'data/images/network-error.png',
        'data/images/network-idle.png',
        'data/images/network-offline.png',
        'data/images/network-receive.png',
        'data/images/network-transmit-receive.png',
        'data/images/network-transmit.png',
        'data/images/network-wireless-signal-excellent.png',
        'data/images/network-wireless-signal-good.png',
        'data/images/network-wireless-signal-ok.png',
        'data/images/network-wireless-signal-weak.png',
        'data/images/ns-bothrs.png',
        'data/images/ns-connected.png',
        'data/images/ns-disconnect.png',
        'data/images/ns-lock.png',
        'data/images/ns-problem.png',
        'data/images/ns-recvdata.png',
        'data/images/ns-senddata.png',
        'data/images/numlock-off.png',
        'data/images/numlock-on.png',
        'data/images/scrllock-off.png',
        'data/images/scrllock-on.png',
        'data/images/stock_volume.png',
        'data/images/volume-high.png',
        'data/images/volume-low.png',
        'data/images/volume-medium.png',
        'data/images/volume.png',
        'data/images/window-manager.png',
    ],
    # install_dir: '/usr/share/lxpanel/images/',
    install_dir: target_install_datadir_project_dir_images_dir,
    install_tag: 'lxpanel-data',
)
# data above *********************************************************




# data below *********************************************************
install_data(
    [
        'plugins/xkb/flags/af.png',
        'plugins/xkb/flags/al.png',
        'plugins/xkb/flags/am.png',
        'plugins/xkb/flags/ara.png',
        'plugins/xkb/flags/at.png',
        'plugins/xkb/flags/au.png',
        'plugins/xkb/flags/az.png',
        'plugins/xkb/flags/ba.png',
        'plugins/xkb/flags/bd.png',
        'plugins/xkb/flags/be.png',
        'plugins/xkb/flags/bg.png',
        'plugins/xkb/flags/br.png',
        'plugins/xkb/flags/bt.png',
        'plugins/xkb/flags/bw.png',
        'plugins/xkb/flags/by.png',
        'plugins/xkb/flags/ca.png',
        'plugins/xkb/flags/cd.png',
        'plugins/xkb/flags/ch.png',
        'plugins/xkb/flags/cm.png',
        'plugins/xkb/flags/cn.png',
        'plugins/xkb/flags/cz.png',
        'plugins/xkb/flags/de.png',
        'plugins/xkb/flags/dk.png',
        'plugins/xkb/flags/dz.png',
        'plugins/xkb/flags/ee.png',
        'plugins/xkb/flags/eg.png',
        'plugins/xkb/flags/epo.png',
        'plugins/xkb/flags/es.png',
        'plugins/xkb/flags/et.png',
        'plugins/xkb/flags/fi.png',
        'plugins/xkb/flags/fo.png',
        'plugins/xkb/flags/fr.png',
        'plugins/xkb/flags/gb.png',
        'plugins/xkb/flags/ge.png',
        'plugins/xkb/flags/gh.png',
        'plugins/xkb/flags/gn.png',
        'plugins/xkb/flags/gr.png',
        'plugins/xkb/flags/hr.png',
        'plugins/xkb/flags/hu.png',
        'plugins/xkb/flags/id.png',
        'plugins/xkb/flags/ie.png',
        'plugins/xkb/flags/il.png',
        'plugins/xkb/flags/in.png',
        'plugins/xkb/flags/iq.png',
        'plugins/xkb/flags/ir.png',
        'plugins/xkb/flags/is.png',
        'plugins/xkb/flags/it.png',
        'plugins/xkb/flags/jp.png',
        'plugins/xkb/flags/ke.png',
        'plugins/xkb/flags/kg.png',
        'plugins/xkb/flags/kh.png',
        'plugins/xkb/flags/kr.png',
        'plugins/xkb/flags/kz.png',
        'plugins/xkb/flags/la.png',
        'plugins/xkb/flags/latam.png',
        'plugins/xkb/flags/lk.png',
        'plugins/xkb/flags/lt.png',
        'plugins/xkb/flags/lv.png',
        'plugins/xkb/flags/ma.png',
        'plugins/xkb/flags/md.png',
        'plugins/xkb/flags/me.png',
        'plugins/xkb/flags/mk.png',
        'plugins/xkb/flags/ml.png',
        'plugins/xkb/flags/mm.png',
        'plugins/xkb/flags/mn.png',
        'plugins/xkb/flags/mt.png',
        'plugins/xkb/flags/mv.png',
        'plugins/xkb/flags/my.png',
        'plugins/xkb/flags/ng.png',
        'plugins/xkb/flags/nl.png',
        'plugins/xkb/flags/no.png',
        'plugins/xkb/flags/np.png',
        'plugins/xkb/flags/nz.png',
        'plugins/xkb/flags/ph.png',
        'plugins/xkb/flags/pk.png',
        'plugins/xkb/flags/pl.png',
        'plugins/xkb/flags/pt.png',
        'plugins/xkb/flags/ro.png',
        'plugins/xkb/flags/rs.png',
        'plugins/xkb/flags/ru.png',
        'plugins/xkb/flags/se.png',
        'plugins/xkb/flags/si.png',
        'plugins/xkb/flags/sk.png',
        'plugins/xkb/flags/sn.png',
        'plugins/xkb/flags/sy.png',
        'plugins/xkb/flags/tg.png',
        'plugins/xkb/flags/th.png',
        'plugins/xkb/flags/tj.png',
        'plugins/xkb/flags/tm.png',
        'plugins/xkb/flags/tr.png',
        'plugins/xkb/flags/tw.png',
        'plugins/xkb/flags/tz.png',
        'plugins/xkb/flags/ua.png',
        'plugins/xkb/flags/us.png',
        'plugins/xkb/flags/uz.png',
        'plugins/xkb/flags/vn.png',
        'plugins/xkb/flags/za.png',
    ],
    follow_symlinks: true,
    # install_dir: '/usr/share/lxpanel/images/xkb-flags/',
    install_dir: target_install_datadir_project_dir_images_dir_xkbflags_dir,
    install_tag: 'lxpanel-data',
)
# data above *********************************************************



# data below *********************************************************
install_data(
    [
        'data/ui/launchtaskbar.glade',
    ],
    rename: 'launchtaskbar.ui',
    # install_dir: '/usr/share/lxpanel/ui/',
    install_dir: target_install_datadir_project_dir_ui_dir,
    install_tag: 'lxpanel-data',
)
install_data(
    [
        'data/ui/netstatus.glade',
    ],
    rename: 'netstatus.ui',
    # install_dir: '/usr/share/lxpanel/ui/',
    install_dir: target_install_datadir_project_dir_ui_dir,
    install_tag: 'lxpanel-data',
)
install_data(
    [
        'data/ui/panel-pref.glade',
    ],
    rename: 'panel-pref.ui',
    # install_dir: '/usr/share/lxpanel/ui/',
    install_dir: target_install_datadir_project_dir_ui_dir,
    install_tag: 'lxpanel-data',
)
# data above *********************************************************



# data below *********************************************************
install_data(
    [
        'plugins/xkb/xkeyboardconfig/layouts.cfg',
        'plugins/xkb/xkeyboardconfig/models.cfg',
        'plugins/xkb/xkeyboardconfig/toggle.cfg',
    ],
    # install_dir: '/usr/share/lxpanel/xkeyboardconfig/',
    install_dir: prefix / datadir / install_subdir_package_name / 'xkeyboardconfig',
    install_tag: 'lxpanel-data',
)
# data above *********************************************************





# Generate 'data/default/panels/panel' ******************************
# data below ********************************************************
data_default_panels_panel_conf_data = configuration_data()
data_default_panels_panel_conf_data.set('prefix', prefix)
data_default_panels_panel = configure_file(
    configuration: data_default_panels_panel_conf_data,
    input: 'data/default/panels/panel.in',
    # This file was originally generated
    # at 'data/default/panels/panel'
    # However, as the meson would like to put all
    # the generated files inside the build directory
    # This file would be generated inside the build dir
    output: 'panel',
)
# data before *******************************************************
# Generate 'data/default/panels/panel' ******************************





# Generate 'data/two_panels/panels/bottom' **************************
# data below ********************************************************
data_two_panels_panels_bottom_conf_data = configuration_data()
data_two_panels_panels_bottom_conf_data.set('prefix', prefix)
data_two_panels_panels_bottom = configure_file(
    configuration: data_two_panels_panels_bottom_conf_data,
    input: 'data/two_panels/panels/bottom.in',
    # This file was originally generated
    # at 'data/two_panels/panels/bottom'
    # However, as the meson would like to put all
    # the generated files inside the build directory
    # This file would be generated inside the build dir
    output: 'bottom',
)
# data before *******************************************************
# Generate 'data/two_panels/panels/bottom' **************************











# Generate 'data/two_panels/panels/top' *****************************
# data below ********************************************************
data_two_panels_panels_top_conf_data = configuration_data()
data_two_panels_panels_top_conf_data.set('prefix', prefix)
data_two_panels_panels_top = configure_file(
    configuration: data_two_panels_panels_top_conf_data,
    input: 'data/two_panels/panels/top.in',
    # This file was originally generated
    # at 'data/two_panels/panels/top'
    # However, as the meson would like to put all
    # the generated files inside the build directory
    # This file would be generated inside the build dir
    output: 'top',
)
# data before *******************************************************
# Generate 'data/two_panels/panels/top' *****************************







# data below *********************************************************
install_data(
    'data/default/config',
    install_dir: target_install_sysconfdir_xdg_project_dir / 'default',
    install_tag: 'lxpanel',
)
install_data(
    data_default_panels_panel,
    install_dir: target_install_sysconfdir_xdg_project_dir / 'default' / 'panels',
    install_tag: 'lxpanel',
)
install_data(
    'data/two_panels/config',
    install_dir: target_install_sysconfdir_xdg_project_dir / 'two_panels',
    install_tag: 'lxpanel',
)
install_data(
    data_two_panels_panels_bottom,
    install_dir: target_install_sysconfdir_xdg_project_dir / 'two_panels' / 'panels',
    install_tag: 'lxpanel',
)
install_data(
    data_two_panels_panels_top,
    install_dir: target_install_sysconfdir_xdg_project_dir / 'two_panels' / 'panels',
    install_tag: 'lxpanel',
)
# data above *********************************************************




# Install some files to target_install_includedir_project_dir *******
# data below ********************************************************
# install_headers(
#     'src/conf.h',
#     # install_dir: target_install_includedir_project_dir,
#     subdir: 'lxpanel',
#     install_tag: 'lxpanel-dev',
# )
install_data(
    'src/conf.h',
    install_dir: target_install_includedir_project_dir,
    install_tag: 'lxpanel-dev',
)
install_data(
    'src/icon-grid.h',
    install_dir: target_install_includedir_project_dir,
    install_tag: 'lxpanel-dev',
)
install_data(
    'src/misc.h',
    install_dir: target_install_includedir_project_dir,
    install_tag: 'lxpanel-dev',
)
install_data(
    src_panel_h,
    install_dir: target_install_includedir_project_dir,
    install_tag: 'lxpanel-dev',
)
install_data(
    'src/plugin.h',
    install_dir: target_install_includedir_project_dir,
    install_tag: 'lxpanel-dev',
)
# data before *******************************************************
# Install some files to target_install_includedir_project_dir *******




# TODO meson has another way to generate pkgconfig file
# Generate 'lxpanel.pc' *********************************************
# data below ********************************************************
lxpanel_pc_conf_data = configuration_data()
lxpanel_pc_conf_data.set('prefix', prefix)
lxpanel_pc_conf_data.set('exec_prefix', '${prefix}')
lxpanel_pc_conf_data.set('libdir', '${prefix}/lib/x86_64-linux-gnu')
lxpanel_pc_conf_data.set('includedir', '${prefix}/include')
lxpanel_pc_conf_data.set('gtk_module', 'gtk+-3.0')
lxpanel_pc_conf_data.set('VERSION', '@0@'.format(PACKAGE_VERSION))
lxpanel_pc = configure_file(
    configuration: lxpanel_pc_conf_data,
    input: 'lxpanel.pc.in',
    # This file was originally generated
    # at 'lxpanel.pc'
    # However, as the meson would like to put all
    # the generated files inside the build directory
    # This file would be generated inside the build dir
    output: 'lxpanel.pc',
)
# data before *******************************************************
# Generate 'lxpanel.pc' *********************************************




# data below ********************************************************
install_data(
    lxpanel_pc,
    # install_dir: '/usr/lib/x86_64-linux-gnu/pkgconfig/',
    install_dir: prefix / 'lib/x86_64-linux-gnu/pkgconfig/',
    install_tag: 'lxpanel-dev',
)
# data before *******************************************************





