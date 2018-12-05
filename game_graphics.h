#pragma once
#include <winbgim.h>

const int DIGIT_TILE_SIZE = 20;

struct RGB_color {
    int r;
    int g;
    int b;
};

const RGB_color _WHITE {255, 255, 255};

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

void drawDisabledDigit(int left, int top, unsigned short num) {
    int bottom = top + DIGIT_TILE_SIZE;
    int right = left + DIGIT_TILE_SIZE;
    setcolor(RGB(_WHITE.r, _WHITE.g, _WHITE.b));
    setfillstyle(1, RGB(_WHITE.r, _WHITE.g, _WHITE.b));
    drawFilledRect(left, top, right, bottom);
}