#pragma once

enum language {
    LANG_EN,
    LANG_RO
};

enum translation {
    GAME_TITLE,
    BTN_PLAY,
    BTN_SETTINGS,
    BTN_HELP,
    BTN_QUIT,

    PLAY_TEXT,
    BTN_SINGLEPLAYER,
    BTN_SINGLEPLAYER_PLUS,
    BTN_MULTIPLAYER,
    BTN_AI,

    SETTINGS_TEXT,
    SETTING_LANG,
    SETTING_MUSIC,
    SETTING_SOUND,

    LABEL1,
    LABEL2,
    
    INPUT_ERR_POPUP,

    SP_WIN_POPUP,
    MP_TIE_POPUP,
    MP_P1_WIN_POPUP,
    MP_P2_WIN_POPUP,

    END_TRANSLATIONS
};

extern const char* lang_en[END_TRANSLATIONS];
extern const char* lang_ro[END_TRANSLATIONS];

language tl_get_lang();
void tl_set_lang(bool english);
void tl_switch_lang();
const char* tl_get_text(translation text);