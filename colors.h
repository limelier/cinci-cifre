#include <winbgim.h>

struct RGB_color {
    int r;
    int g;
    int b;
};


// COLOR VALUES

const RGB_color _BLUE {62, 165, 245};
const RGB_color _DK_BLUE {21, 101, 192};
const RGB_color _BLUEGRAY {120, 144, 156};
const RGB_color _DK_BLUEGRAY {55, 71, 79};
const RGB_color _RED {239, 83, 80};
const RGB_color _DK_RED {183, 28, 28};

const RGB_color _WHITE {225, 225, 225};
const RGB_color _BLACK {25, 25, 25};
const RGB_color _GREY {100, 100, 100};


// COLOR ASSIGNMENTS

    // game panel
#define GREYED_OUT_DIGIT_BG1 _BLUEGRAY
#define NORMAL_DIGIT_BG1 _BLUE
#define HIDDEN_DIGIT_BG1 _RED

#define GREYED_BACKING _DK_BLUEGRAY
#define NORMAL_BACKING _DK_BLUE
#define GREYED_BACKGROUND _BLUEGRAY
#define NORMAL_BACKGROUND _BLUE

    // input dialog
#define INP_BACKING _DK_BLUEGRAY

#define INP_NUMPANEL _BLACK
#define INP_NUMPANEL_TEXT _WHITE

#define INP_BUTTON_BG _BLUEGRAY
#define INP_BUTTON_FG _BLACK
#define INP_BUTTON_BG_HOVER _BLUE
#define INP_BUTTON_FG_HOVER _BLACK

    // menu
#define TITLE_FG _RED
#define MENU_BG _BLACK

#define MENU_BUTTON_BG _BLUEGRAY
#define MENU_BUTTON_FG _BLACK
#define MENU_BUTTON_BG_HOVER _BLUE
#define MENU_BUTTON_FG_HOVER _BLACK

    // play menu
#define PLAY_FG _WHITE
#define PLAY_BG _BLACK

    // popups
#define POPUP_BG _RED
#define POPUP_FG _BLACK


// FUNCTIONS

void setcolorRGB(RGB_color color) {
    setcolor(RGB(color.r, color.g, color.b));
}

void setbkcolorRGB(RGB_color color) {
    setbkcolor(RGB(color.r, color.g, color.b));
}

void setfillstyleFlatRGB(RGB_color color) {
    setfillstyle(1, RGB(color.r, color.g, color.b));
}