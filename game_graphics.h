#pragma once
#include <winbgim.h>

const int DIGIT_TILE_HEIGHT = 19;
const int DIGIT_TILE_WIDTH = 11;

struct RGB_color {
    int r;
    int g;
    int b;
};

const RGB_color _WHITE {255, 255, 255};
const RGB_color _BLACK {0, 0, 0};

void drawFilledRect(int left, int top, int right, int bottom) {
    int poly_points[8] = 
    {
        left, top,
        right, top,
        right, bottom,
        left, bottom
    };

    fillpoly(4, poly_points);
}

void drawEnabledDigit(int left, int top, unsigned short num) {
    int bottom = top + DIGIT_TILE_HEIGHT;
    int right = left + DIGIT_TILE_WIDTH;

    setcolor(RGB(_WHITE.r, _WHITE.g, _WHITE.b));
    setfillstyle(1, RGB(_WHITE.r, _WHITE.g, _WHITE.b));
    drawFilledRect(left, top, right, bottom);

    char text[2];
    text[0] = (char)num + '0';
    text[1] = '\0';

    setcolor(RGB(_BLACK.r, _BLACK.g, _BLACK.b));
    setbkcolor(RGB(_WHITE.r, _WHITE.g, _WHITE.b));

    /* QUARANTINE. THESE FUNCTIONS ARE EVIL AND I STILL DON'T KNOW HOW THEY WORK.
    setusercharsize(3, 1, 2, 1);
    settextstyle(EUROPEAN_FONT, HORIZ_DIR, 0);
    */
    
    outtextxy(left + 2, top + 2, text);
}