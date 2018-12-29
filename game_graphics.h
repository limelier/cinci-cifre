#pragma once
#include <winbgim.h>
#include "base_dependencies.h"
#include "graphical_game.h"
#include <string.h>

// PARAMETERS

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

const int DIGIT_TILE_HEIGHT = 35;
const int DIGIT_TILE_WIDTH = 25;
const int TILE_SHADOW_HGT = 3;
const int DIGIT_TEXT_SIZE = 4;
const int LABEL_TEXT_SIZE = 2;
const int GUESS_HEIGHT = 42;
const int DIGIT_CORNER_RADIUS = 3;
const int PERM_DIGIT_SPACING = 1;
const int GUESSLIST_PADDING = 5;
const int RESULT_DIGIT_MARGIN = 25;
const int GUESS_DIVIDER = 15;
const int HEADER_PADDING = 5;
const int GAMEPANEL_PADDING = 10;
const int HEADER_TOP = 50;
const int GAMEPANEL_DIVIDER = 10;

const char LABEL1[] = "fixed";
const char LABEL2[] = "moved";


// COLORS

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
#define NORMAL_DIGIT_BG1 _BLUE
#define HIDDEN_DIGIT_BG1 _RED
#define GREYED_BACKING _DK_BLUEGRAY
#define NORMAL_BACKING _DK_BLUE
#define GREYED_BACKGROUND _BLUEGRAY
#define NORMAL_BACKGROUND _BLUE

// BASE FUNCTIONS

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


// currently behaves oddly in corners. usage postponed.
void drawFilledRoundedRect(int left, int top, int right, int bottom, int radius) {
    int left_inner = left + radius;
    int right_inner = right - radius;
    int top_inner = top + radius;
    int bottom_inner = bottom - radius;

    drawFilledRect(left, top_inner, right, bottom_inner);
    drawFilledRect(left_inner, top, right_inner, bottom);
    fillellipse(left_inner, top_inner, radius, radius);
    fillellipse(left_inner, bottom_inner, radius, radius);
    fillellipse(right_inner, top_inner, radius, radius);
    fillellipse(right_inner, bottom_inner, radius, radius);
}

void drawCenteredText(int x, int y, char text[], RGB_color fg, RGB_color bg, int text_size) {
    setcolor(RGB(fg.r, fg.g, fg.b));
    setbkcolor(RGB(bg.r, bg.g, bg.b));

    settextstyle(COMPLEX_FONT, HORIZ_DIR, text_size);
    x -= textwidth(text) / 2;
    y -= textheight(text) / 2;
    outtextxy(x, y, text);
}

// BUTTONS

struct button_graphics {
    RGB_color bg = _WHITE;
    RGB_color bg_hover = _BLACK;
    RGB_color fg = _BLACK;
    RGB_color fg_hover = _WHITE;
    char text[100] = "untitled button";
    int fontsize = 2;
};

struct button {
    int key = 0;

    int left = 0;
    int right = 0;
    int top = 0;
    int bottom = 0;

    bool hover = false;

    button_graphics graph;
};


void drawButton(button btn) {
    RGB_color bg_color = btn.hover ? btn.graph.bg_hover : btn.graph.bg;
    RGB_color fg_color = btn.hover ? btn.graph.fg_hover : btn.graph.fg;

    setcolor(RGB(bg_color.r, bg_color.g, bg_color.b));
    setfillstyle(1, RGB(bg_color.r, bg_color.g, bg_color.b));
    drawFilledRect(btn.left, btn.top, btn.right, btn.bottom);

    setcolor(RGB(fg_color.r, fg_color.g, fg_color.b));
    setbkcolor(RGB(bg_color.r, bg_color.g, bg_color.b));
    settextstyle(COMPLEX_FONT, HORIZ_DIR, btn.graph.fontsize);
    int center_x = (btn.left + btn.right) / 2;
    int center_y = (btn.top + btn.bottom) / 2;
    drawCenteredText(center_x, center_y, btn.graph.text, fg_color, bg_color, btn.graph.fontsize);
}

// GAME FUNCTIONS

void drawDigit(int left, int top, unsigned short num, bool greyed_out) {
    RGB_color bg_color1;
    if (greyed_out == true) {
        bg_color1 = GREYED_OUT_DIGIT_BG1;
    }
    else {
        bg_color1 = NORMAL_DIGIT_BG1;
    }

    int bottom = top + DIGIT_TILE_HEIGHT;
    int right = left + DIGIT_TILE_WIDTH;

    setcolor(RGB(bg_color1.r, bg_color1.g, bg_color1.b));
    setfillstyle(1, RGB(bg_color1.r, bg_color1.g, bg_color1.b));
    drawFilledRect(left, top, right, bottom);

    char text[2];
    text[0] = (char)num + '0';
    text[1] = '\0';

    setcolor(RGB(_BLACK.r, _BLACK.g, _BLACK.b));
    setbkcolor(RGB(bg_color1.r, bg_color1.g, bg_color1.b));

    settextstyle(COMPLEX_FONT, HORIZ_DIR, DIGIT_TEXT_SIZE);
    
    outtextxy(left + 2, top + 2, text);
}

void drawHiddenDigit(int left, int top) {
    RGB_color bg_color1;
    bg_color1 = HIDDEN_DIGIT_BG1;

    int bottom = top + DIGIT_TILE_HEIGHT;
    int right = left + DIGIT_TILE_WIDTH;

    setcolor(RGB(bg_color1.r, bg_color1.g, bg_color1.b));
    setfillstyle(1, RGB(bg_color1.r, bg_color1.g, bg_color1.b));
    drawFilledRect(left, top, right, bottom);

    setcolor(RGB(_BLACK.r, _BLACK.g, _BLACK.b));
    line(left + 1, top + 1, right - 1, bottom - 1);
    line(right - 1, top + 1, left + 1, bottom - 1);
}

void drawPerm(int left, int top, permutation perm, bool greyed_out) {
    int crt_left = left;
    for (int i = 0; i < PERM_LEN; i++) {
        // the 1 isn't a magic number it's just needed to avoid overlap i swear don't hurt me
        crt_left = left + (DIGIT_TILE_WIDTH + 1 + PERM_DIGIT_SPACING) * i;
        drawDigit(crt_left, top, perm.digit[i], greyed_out);
    }
}

void drawHiddenPerm(int left, int top) {
    int crt_left = left;
    for (int i = 0; i < PERM_LEN; i++) {
        crt_left = left + (DIGIT_TILE_WIDTH + 1 + PERM_DIGIT_SPACING) * i;
        drawHiddenDigit(crt_left, top);
    }
}

void drawResult(int left, int top, result res, bool greyed_out) {
    drawDigit(left + RESULT_DIGIT_MARGIN, top, res.fixed, greyed_out);
    drawDigit(left + DIGIT_TILE_WIDTH + 1 + 3 * RESULT_DIGIT_MARGIN, top, res.moved, greyed_out);
}

void drawGuess(int left, int top, permutation guess, result res, bool greyed_out) {
    drawPerm(left, top, guess, greyed_out);
    int result_offset = PERM_LEN * (DIGIT_TILE_WIDTH + PERM_DIGIT_SPACING) + GUESS_DIVIDER;
    drawResult(left + result_offset, top, res, greyed_out);
}

void drawLabel(int x, int y, char text[], bool greyed_out) {
    // prints labels, centered on x and y
    RGB_color bg_color1;
    if (greyed_out == true) 
        bg_color1 = GREYED_BACKING;
    else 
        bg_color1 = NORMAL_BACKING;

    drawCenteredText(x, y, text, _BLACK, bg_color1, LABEL_TEXT_SIZE);
}

int guessListWidth() {
    // there are 2 result values. always.
    int guesslist_width = 0;
    guesslist_width += PERM_LEN * (DIGIT_TILE_WIDTH + PERM_DIGIT_SPACING);
    guesslist_width += GUESS_DIVIDER;
    guesslist_width += 2 * DIGIT_TILE_WIDTH;
    guesslist_width += 4 * RESULT_DIGIT_MARGIN;
    return guesslist_width;
}

int guessListHeight(guesslist list) {
    return list.num * GUESS_HEIGHT;
}

void drawPanelHeader(int left, int top , bool greyed_out) {
    int right = left + guessListWidth() + 2 * GUESSLIST_PADDING;
    int bottom = top + DIGIT_TILE_HEIGHT + 2 * HEADER_PADDING;

    RGB_color bg_color;
    if (greyed_out == true) 
        bg_color = GREYED_BACKING;
    else bg_color = NORMAL_BACKING;
    setcolor(RGB(bg_color.r, bg_color.g, bg_color.b));
    setfillstyle(1, RGB(bg_color.r, bg_color.g, bg_color.b));
    drawFilledRect(left, top, right, bottom);

    drawHiddenPerm(left + GUESSLIST_PADDING, top + HEADER_PADDING);

    // label printing zone!
    int label_x = left, label_y = top;
    label_x += GUESSLIST_PADDING + PERM_LEN * (DIGIT_TILE_WIDTH + PERM_DIGIT_SPACING);
    label_x += GUESS_DIVIDER + RESULT_DIGIT_MARGIN + DIGIT_TILE_WIDTH / 2;
    label_y += HEADER_PADDING + DIGIT_TILE_HEIGHT / 2;

    char current_label[30];
    
    strcpy(current_label, LABEL1);
    drawLabel(label_x, label_y, current_label, greyed_out);

    label_x += 2 * RESULT_DIGIT_MARGIN + DIGIT_TILE_WIDTH;
    strcpy(current_label, LABEL2);
    drawLabel(label_x, label_y, current_label, greyed_out);
}

void drawGuessList(int left, int top, guesslist list, bool greyed_out) {

    int right = left + guessListWidth() + 2 * GUESSLIST_PADDING;
    int bottom = top + guessListHeight(list) + GUESSLIST_PADDING;

    RGB_color bg_color;
    if (greyed_out == true) 
        bg_color = GREYED_BACKING;
    else bg_color = NORMAL_BACKING;
    setcolor(RGB(bg_color.r, bg_color.g, bg_color.b));
    setfillstyle(1, RGB(bg_color.r, bg_color.g, bg_color.b));
    drawFilledRect(left, top, right, bottom);

    int curr_top = top + GUESSLIST_PADDING;

    guessnode *node = list.last;
    for (unsigned int i = 0; i < list.num; i++) {
        drawGuess(left + GUESSLIST_PADDING , curr_top, node->perm, node->res, greyed_out);
        curr_top += GUESS_HEIGHT;
        node = node->prev;
    }
}

void drawGamePanel (int left, game_panel game) {
    bool greyed_out = !game.active;

    int right = left + guessListWidth() + 2 * GUESSLIST_PADDING + 2 * GAMEPANEL_PADDING;
    RGB_color bg_color;
    if (greyed_out == true) 
        bg_color = GREYED_BACKGROUND;
    else bg_color = NORMAL_BACKGROUND;
    setcolor(RGB(bg_color.r, bg_color.g, bg_color.b));
    setfillstyle(1, RGB(bg_color.r, bg_color.g, bg_color.b));
    drawFilledRect(left, 1, right, WINDOW_HEIGHT);

    drawPanelHeader(left + GAMEPANEL_PADDING, HEADER_TOP, greyed_out);
    int guesslist_top = HEADER_TOP + DIGIT_TILE_HEIGHT + 2 * HEADER_PADDING + GAMEPANEL_DIVIDER;
    drawGuessList(left + GAMEPANEL_PADDING, guesslist_top, game.list, greyed_out);
}

