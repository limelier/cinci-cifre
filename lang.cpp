#include "lang.h"

language tl_lang = LANG_EN;

void tl_set_lang(language lang) {
    tl_lang = lang;
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