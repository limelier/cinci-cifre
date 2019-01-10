#include "lang.h"

language tl_lang;

language tl_get_lang() {
    return tl_lang;
}

void tl_set_lang(bool english) {
    if (english)
        tl_lang = LANG_EN;
    else
        tl_lang = LANG_RO;
}

void tl_switch_lang() {
    if (tl_lang == LANG_EN) 
        tl_lang = LANG_RO;
    else tl_lang = LANG_EN;
}

const char* tl_get_text(translation text) {
    switch (tl_lang) {
        case LANG_RO:
            return lang_ro[text];
        case LANG_EN:
        default:
            return lang_en[text];
    }
}