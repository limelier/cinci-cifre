#pragma once
#include <winbgim.h>
#include "base_dependencies.h"

// CONSTANTS

const int DIGIT_TILE_HEIGHT = 35;
const int DIGIT_TILE_WIDTH = 25;
const int TILE_SHADOW_HGT = 3;
const int DIGIT_TEXT_SIZE = 4;
const int GUESS_HEIGHT = 42;

struct RGB_color {
    int r;
    int g;
    int b;
};

const RGB_color _BLUE {62, 165, 245};
const RGB_color _DK_BLUE {21, 101, 192};
const RGB_color _BLUEGRAY {120, 144, 156};
const RGB_color _DK_BLUEGRAY {55, 71, 79};
const RGB_color _RED {239, 83, 80};
const RGB_color _DK_RED {183, 28, 28};

const RGB_color _WHITE {225, 225, 225};
const RGB_color _BLACK {25, 25, 25};
const RGB_color _GREY {100, 100, 100};

#define GREYED_OUT_DIGIT_BG1 _BLUEGRAY
#define GREYED_OUT_DIGIT_BG2 _DK_BLUEGRAY
#define NORMAL_DIGIT_BG1 _BLUE
#define NORMAL_DIGIT_BG2 _DK_BLUE
#define HIDDEN_DIGIT_BG1 _RED
#define HIDDEN_DIGIT_BG2 _DK_RED

// FUNCTIONS

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

void drawDigit(int left, int top, unsigned short num, bool greyed_out) {
    RGB_color bg_color1, bg_color2;
    if (greyed_out == true) {
        bg_color1 = GREYED_OUT_DIGIT_BG1;
        bg_color2 = GREYED_OUT_DIGIT_BG2;
    }
    else {
        bg_color1 = NORMAL_DIGIT_BG1;
        bg_color2 = NORMAL_DIGIT_BG2;
    }

    int bottom = top + DIGIT_TILE_HEIGHT;
    int right = left + DIGIT_TILE_WIDTH;

    setcolor(RGB(bg_color1.r, bg_color1.g, bg_color1.b));
    setfillstyle(1, RGB(bg_color1.r, bg_color1.g, bg_color1.b));
    drawFilledRect(left, top, right, bottom);

    setcolor(RGB(bg_color2.r, bg_color2.g, bg_color2.b));
    setfillstyle(1, RGB(bg_color2.r, bg_color2.g, bg_color2.b));
    drawFilledRect(left, bottom + 1, right, bottom + TILE_SHADOW_HGT);

    char text[2];
    text[0] = (char)num + '0';
    text[1] = '\0';

    setcolor(RGB(_BLACK.r, _BLACK.g, _BLACK.b));
    setbkcolor(RGB(bg_color1.r, bg_color1.g, bg_color1.b));

    settextstyle(COMPLEX_FONT, HORIZ_DIR, DIGIT_TEXT_SIZE);
    
    outtextxy(left + 2, top + 2, text);
}

void drawHiddenDigit(int left, int top) {
    RGB_color bg_color1, bg_color2;
    bg_color1 = HIDDEN_DIGIT_BG1;
    bg_color2 = HIDDEN_DIGIT_BG2;

    int bottom = top + DIGIT_TILE_HEIGHT;
    int right = left + DIGIT_TILE_WIDTH;

    setcolor(RGB(bg_color1.r, bg_color1.g, bg_color1.b));
    setfillstyle(1, RGB(bg_color1.r, bg_color1.g, bg_color1.b));
    drawFilledRect(left, top, right, bottom);

    setcolor(RGB(bg_color2.r, bg_color2.g, bg_color2.b));
    setfillstyle(1, RGB(bg_color2.r, bg_color2.g, bg_color2.b));
    drawFilledRect(left, bottom + 1, right, bottom + TILE_SHADOW_HGT);

    setcolor(RGB(_BLACK.r, _BLACK.g, _BLACK.b));
    line(left + 1, top + 1, right - 1, bottom - 1);
    line(right - 1, top + 1, left + 1, bottom - 1);
}

void drawPerm(int left, int top, permutation perm, bool greyed_out) {
    for (int i = 0; i < PERM_LEN; i++) {
        drawDigit(left + (DIGIT_TILE_WIDTH + 2) * i, top, perm.digit[i], greyed_out);
    }
}

void drawHiddenPerm(int left, int top) {
    for (int i = 0; i < PERM_LEN; i++) {
        drawHiddenDigit(left + (DIGIT_TILE_WIDTH + 2) * i, top);
    }
}

void drawResult(int left, int top, result res, bool greyed_out) {
    drawDigit(left, top, res.fixed, greyed_out);
    drawDigit(left + DIGIT_TILE_WIDTH + 6, top, res.moved, greyed_out);
}

void drawGuess(int left, int top, permutation guess, result res, bool greyed_out) {
    drawPerm(left, top, guess, greyed_out);
    int result_offset = 5 * DIGIT_TILE_WIDTH + 20;
    drawResult(left + result_offset, top, res, greyed_out);
}

void drawGuessList(int left, int top, guesslist list, bool greyed_out) {
    guessnode *node = list.first;
    int curr_top = top;

    for (int i = 0; i < list.num; i++) {
        drawGuess(left, curr_top, node->perm, node->res, greyed_out);
        curr_top += GUESS_HEIGHT;
        node = node->next;
    }
}