





i18n = import('i18n')
# define GETTEXT_PACKAGE
# We should move all 'add_project_arguments' to the front of the 'meson.build' file
# If we don't, we might get error
#
# ERROR: Tried to use 'add_project_arguments' after a build target has been declared
#
# add_project_arguments('-DGETTEXT_PACKAGE="lxpanel"', language: 'c')
#
i18n.gettext(
    GETTEXT_PACKAGE,
    preset: 'glib',
    args: [
        '--files-from=' + join_paths(
            meson.project_source_root(),
            './po/POTFILES.meson',
        ),
        '--debug',
    ],
    install: true,
    # TODO ask meson maintainer about this
    # Something is wrong with meson i18n.gettext
    # Even if I set this arg, when I run
    #
    # meson compile --verbose lxpanel-pot
    # meson compile --verbose lxpanel-update-po
    #
    # there is still error being reported, asking for
    # a 'LINGUAS' file to be stored at subdir 'po'
    #
    # languages: [
    #     'af',
    #     'ar',
    #     'be',
    #     'bg',
    #     'bn_IN',
    #     'bn',
    #     'ca',
    #     'cs',
    #     'da',
    #     'de',
    #     'el',
    #     'en_GB',
    #     'es',
    #     'et',
    #     'eu',
    #     'fa',
    #     'fi',
    #     'fo',
    #     'fr',
    #     'frp',
    #     'gl',
    #     'he',
    #     'hr',
    #     'hu',
    #     'id',
    #     'is',
    #     'it',
    #     'ja',
    #     'ka',
    #     'kk',
    #     'km',
    #     'ko',
    #     'lg',
    #     'lt',
    #     'lv',
    #     'ml',
    #     'ms',
    #     'nb',
    #     'nl',
    #     'nn',
    #     'pa',
    #     'pl',
    #     'ps',
    #     'pt_BR',
    #     'pt',
    #     'ro',
    #     'ru',
    #     'sk',
    #     'sl',
    #     'sr@latin',
    #     'sr',
    #     'sv',
    #     'te',
    #     'th',
    #     'tr',
    #     'tt_RU',
    #     'ug',
    #     'uk',
    #     'ur_PK',
    #     'ur',
    #     'vi',
    #     'zh_CN',
    #     'zh_HK',
    #     'zh_TW',
    # ],
)








