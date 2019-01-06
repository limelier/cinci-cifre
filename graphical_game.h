#pragma once

#include "base_dependencies.h"
#include "rares_depends.h"
#include <string.h>
#include <winbgim.h>
#include <stack> // needs to go.

// PARAMETERS
#include "game_consts.h"
// COLORS
#include "colors.h"

// BASIC DRAW FUNCTIONS

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

    setcolorRGB(bg_color);
    setfillstyleFlatRGB(bg_color);
    drawFilledRect(btn.left, btn.top, btn.right, btn.bottom);

    setcolorRGB(fg_color);
    setbkcolorRGB(bg_color);
    settextstyle(COMPLEX_FONT, HORIZ_DIR, btn.graph.fontsize);
    int center_x = (btn.left + btn.right) / 2;
    int center_y = (btn.top + btn.bottom) / 2;
    drawCenteredText(center_x, center_y, btn.graph.text, fg_color, bg_color, btn.graph.fontsize);
}

// GAME FUNCTIONS

void drawDigit(int left, int top, unsigned short num, bool greyed_out) {
    RGB_color bg_color;
    if (greyed_out == true) {
        bg_color = GREYED_OUT_DIGIT_BG1;
    }
    else {
        bg_color = NORMAL_DIGIT_BG1;
    }

    int bottom = top + DIGIT_TILE_HEIGHT;
    int right = left + DIGIT_TILE_WIDTH;

    setcolorRGB(bg_color);
    setfillstyleFlatRGB(bg_color);
    drawFilledRect(left, top, right, bottom);

    char text[2];
    text[0] = (char)num + '0';
    text[1] = '\0';

    setcolorRGB(_BLACK);
    setbkcolorRGB(bg_color);

    settextstyle(COMPLEX_FONT, HORIZ_DIR, DIGIT_TEXT_SIZE);

    outtextxy(left + 2, top + 2, text);
}

void drawHiddenDigit(int left, int top) {
    RGB_color bg_color;
    bg_color = HIDDEN_DIGIT_BG1;

    int bottom = top + DIGIT_TILE_HEIGHT;
    int right = left + DIGIT_TILE_WIDTH;

    setcolorRGB(bg_color);
    setfillstyleFlatRGB(bg_color);
    drawFilledRect(left, top, right, bottom);

    setcolorRGB(_BLACK);
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
    RGB_color bg_color;
    if (greyed_out == true)
        bg_color = GREYED_BACKING;
    else
        bg_color = NORMAL_BACKING;

    drawCenteredText(x, y, text, _BLACK, bg_color, LABEL_TEXT_SIZE);
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
    setcolorRGB(bg_color);
    setfillstyleFlatRGB(bg_color);
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
    setcolorRGB(bg_color);
    setfillstyleFlatRGB(bg_color);
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
    setcolorRGB(bg_color);
    setfillstyleFlatRGB(bg_color);
    drawFilledRect(left, 1, right, WINDOW_HEIGHT);

    drawPanelHeader(left + GAMEPANEL_PADDING, HEADER_TOP, greyed_out);
    int guesslist_top = HEADER_TOP + DIGIT_TILE_HEIGHT + 2 * HEADER_PADDING + GAMEPANEL_DIVIDER;
    drawGuessList(left + GAMEPANEL_PADDING, guesslist_top, game.list, greyed_out);
}

void guesslistPop (guesslist &list) {
    list.num--;

    guessnode *p;
    p = list.last;
    list.last = list.last->prev;
    list.last->next = nullptr;
    delete p;
}

void guesslistPush (guesslist &list, guessnode *node) {
    if (list.num == GUESSLIST_LEN)
        guesslistPop(list);

    if (list.num == 0) {
        list.first = node;
        list.last = node;
        list.num = 1;
    }
    else {
        list.num++;
        node->next = list.first;
        list.first->prev = node;
        list.first = node;
    }
}

guessnode *makeGuess (permutation base_perm, permutation perm) {
    guessnode *node;
    node = new guessnode;
    node->perm = perm;
    node->res = comparePermutations(base_perm, perm);
    return node;
}

void buttonLoopStep(button &btn) {
    bool hover;

    if (mousex() >= btn.left &&
        mousex() <= btn.right &&
        mousey() >= btn.top &&
        mousey() <= btn.bottom)
        hover = true;
    else
        hover = false;

    if (hover != btn.hover) {
        btn.hover = hover;
        drawButton(btn);
    }
}

void drawInputBacking() {
    setcolorRGB(INP_BACKING);
    setfillstyleFlatRGB(INP_BACKING);
    drawFilledRect(1, INP_BOX_TOP, WINDOW_WIDTH, INP_BOX_BOTTOM);
}

void drawInputNumpanel() {
    setcolorRGB(INP_NUMPANEL);
    setfillstyleFlatRGB(INP_NUMPANEL);
    int bottom = INP_BOX_BOTTOM - INP_BOX_VERT_PADDING;
    int top = INP_BOX_TOP + INP_BOX_VERT_PADDING;
    int left = INP_BOX_HORIZ_PADDING;
    int right = WINDOW_WIDTH - INP_BOX_HORIZ_PADDING;
    right -= ENTER_BTN_WIDTH + C_BTN_WIDTH + CE_BTN_WIDTH;
    right -= 3 * INP_BOX_SPACING;
    drawFilledRect(left, top, right, bottom);
}

void drawInputStack(stack <int> input_stack) {
    stack <int> reverse_input_stack;
    char text[PERM_LEN + 1] = "     ";

    while (input_stack.empty() == false) {
        text[input_stack.size() - 1] = input_stack.top() + '0';
        input_stack.pop();
    }

    int top = INP_BOX_TOP + INP_BOX_VERT_PADDING;
    int bottom = INP_BOX_BOTTOM - INP_BOX_VERT_PADDING;
    int left = INP_BOX_HORIZ_PADDING;

    setcolorRGB(INP_NUMPANEL_TEXT);
    setbkcolorRGB(INP_NUMPANEL);
    settextstyle(COMPLEX_FONT, HORIZ_DIR, INP_NUMPANEL_FONTSIZE);
    top = (top + bottom - textheight(text)) / 2;
    outtextxy(left + 20, top + 2, text);
}

permutation permFromStack(stack <int> s) {
    permutation perm;
    int digit = 0;

    if (s.size() != PERM_LEN) {
        throw "Stack isn't the right height.";
        perm.is_valid = false;
    }

    perm.is_valid = true;
    for (int i = 4; i >= 0; i--) {
        digit = s.top();
        s.pop();
        perm.digit[i] = digit;
        if (perm.digit_used[digit] == true)
            perm.is_valid = false;
        else
            perm.digit_used[digit] = true;
    }

    return perm;
}

void drawMultiCenteredText(int x, int y, char text[], RGB_color fg, RGB_color bg, int fontsize) {
    char chunk[200];
    int length = strlen(text);
    int lines = 1;

    for (int i = 0; i < length; i++) {
        if (text[i] == '\n')
            lines++;
    }

    settextstyle(COMPLEX_FONT, HORIZ_DIR, fontsize);
    int line_height = textheight(text);
    line_height += TEXT_LINE_SPACING;

    int line_y;
    line_y = y - (lines / 2) * line_height;
    if (lines % 2 == 0)
        line_y += line_height / 2;

    int j = 0;
    int i;
    for (i = 0; i < length; i++) {
        if (text[i] == '\n') {
            strncpy(chunk, text + j, i - j);
            chunk[i - j] = '\0';
            drawCenteredText(x, line_y, chunk, fg, bg, fontsize);
            line_y += line_height;
            j = i + 1;
        }
    }

    strncpy(chunk, text + j, i - j);
    chunk[i - j] = '\0';
    drawCenteredText(x, line_y, chunk, fg, bg, fontsize);


}

void drawPopup (int width, int height, int fontsize, char text[]) { // todo: proper multi-line formatting
    setcolorRGB(POPUP_BG);
    setfillstyleFlatRGB(POPUP_BG);
    int x = WINDOW_WIDTH / 2;
    int y = WINDOW_HEIGHT / 2;
    drawFilledRect(x - width / 2, y - height / 2, x + width / 2, y + height / 2);
    drawMultiCenteredText(x, y, text, POPUP_FG, POPUP_BG, fontsize);
}

void popup (int width, int height, int fontsize, char text[]) {
    setactivepage(2);
    setbkcolorRGB(_BLACK);
    cleardevice();
    drawPopup (width, height, fontsize, text);
    setvisualpage(2);

    getch();
    setactivepage(1);
    setvisualpage(1);
}

permutation inputPermutation2() {
    permutation input;
    bool perm_complete = false;
    stack <int> input_stack;

    int inp_box_bottom = WINDOW_HEIGHT - INP_BOX_BOTTOM_MARGIN;
    int inp_box_top = inp_box_bottom - INP_BOX_HEIGHT;

    // button initialization. i hate everything about this part.
    button btn_enter;
    btn_enter.right = WINDOW_WIDTH - INP_BOX_HORIZ_PADDING;
    btn_enter.left = btn_enter.right - ENTER_BTN_WIDTH;
    btn_enter.top = inp_box_top + INP_BOX_VERT_PADDING;
    btn_enter.bottom = inp_box_bottom - INP_BOX_VERT_PADDING;
    strcpy(btn_enter.graph.text, "Enter");
    btn_enter.graph.bg = INP_BUTTON_BG;
    btn_enter.graph.fg = INP_BUTTON_FG;
    btn_enter.graph.bg_hover = INP_BUTTON_BG_HOVER;
    btn_enter.graph.fg_hover = INP_BUTTON_FG_HOVER;

    button btn_CE;
    btn_CE.right = btn_enter.left - INP_BOX_SPACING;
    btn_CE.left = btn_CE.right - CE_BTN_WIDTH;
    btn_CE.top = inp_box_top + INP_BOX_VERT_PADDING;
    btn_CE.bottom = inp_box_bottom - INP_BOX_VERT_PADDING;
    strcpy(btn_CE.graph.text, "CE");
    btn_CE.graph.bg = INP_BUTTON_BG;
    btn_CE.graph.fg = INP_BUTTON_FG;
    btn_CE.graph.bg_hover = INP_BUTTON_BG_HOVER;
    btn_CE.graph.fg_hover = INP_BUTTON_FG_HOVER;

    button btn_C;
    btn_C.right = btn_CE.left - INP_BOX_SPACING;
    btn_C.left = btn_C.right - C_BTN_WIDTH;
    btn_C.top = inp_box_top + INP_BOX_VERT_PADDING;
    btn_C.bottom = inp_box_bottom - INP_BOX_VERT_PADDING;
    strcpy(btn_C.graph.text, "C");
    btn_C.graph.bg = INP_BUTTON_BG;
    btn_C.graph.fg = INP_BUTTON_FG;
    btn_C.graph.bg_hover = INP_BUTTON_BG_HOVER;
    btn_C.graph.fg_hover = INP_BUTTON_FG_HOVER;

    // draw input dialog
    drawInputBacking();
    drawInputNumpanel();
    drawInputStack(input_stack);
    drawButton(btn_enter);
    drawButton(btn_C);
    drawButton(btn_CE);

    bool input_stack_changed = false;
    while (perm_complete == false) {
        if (input_stack_changed) {
            drawInputNumpanel();
            drawInputStack(input_stack);
            input_stack_changed = false;
        }
        buttonLoopStep(btn_enter);
        buttonLoopStep(btn_CE);
        buttonLoopStep(btn_C);
        
        // look for digit key hits
        if (kbhit()) {
            char key = getch();
            if (key >= '0' && key <= '9')
                if (input_stack.size() < PERM_LEN) {
                    input_stack.push(key - '0');
                    input_stack_changed = true;
                }
        }
        // look for button hits: enter, C and CE
        if (ismouseclick(WM_LBUTTONDOWN)) {
            if (btn_C.hover && !input_stack.empty()) {
                input_stack.pop();
                input_stack_changed = true;
            }
            else if (btn_CE.hover && !input_stack.empty()) {
                while (!input_stack.empty())
                    input_stack.pop();
                input_stack_changed = true;
            }
            else if (btn_enter.hover && input_stack.size() == PERM_LEN) {
                input = permFromStack(input_stack);
                if (input.is_valid == true)
                    perm_complete = true;
                else {
                    char popup_text[200];
                    strcpy(popup_text, INPUT_ERR_POPUP);
                    popup(INPUT_ERR_POPUP_W, INPUT_ERR_POPUP_H, INPUT_ERR_POPUP_FONTSIZE, popup_text);
                    while (!input_stack.empty())
                        input_stack.pop();
                    input_stack_changed = true;
                }

            }
            clearmouseclick(WM_LBUTTONDOWN);
        }
    }

    return input;
}

int gamePanelWidth() {
    int width = 0;
    width += guessListWidth();
    width += 2 * GUESSLIST_PADDING;
    width += 2 * GAMEPANEL_PADDING;
    return width;
}

void SPGameLoop(bool help) {
    game_panel game;
    setbkcolorRGB(_BLACK);
    cleardevice();

    int game_left = (WINDOW_WIDTH - gamePanelWidth()) / 2;

    if (help) 
        game.base_perm = inputPermutation2();
    else
        game.base_perm = RandomPermutationGenerator();

    permutation input;
    while (game.has_been_won == false) {
        setbkcolorRGB(_BLACK);
        cleardevice();

        drawGamePanel(game_left, game);

        input = inputPermutation2();

        guesslistPush(game.list, makeGuess(game.base_perm, input));

        if (game.list.first->res.fixed == 5) // doesn't work, fix
            game.has_been_won = true;
    }

    char popup_text[200];
    strcpy(popup_text, SP_WIN_POPUP);
    popup(SP_WIN_POPUP_W, SP_WIN_POPUP_H, SP_WIN_POPUP_FONTSIZE, popup_text);
    cleardevice();
}

button initMenuButton(int index, const char text[]) {
    // THE MENU ALWAYS HAS A MAXIMUM OF FOUR BUTTONS
    button btn;

    btn.left = (WINDOW_WIDTH - MENU_BTN_W) / 2;
    btn.right = btn.left + MENU_BTN_W;
    
    btn.top = MENU_OFFSET + index * (MENU_BTN_H + MENU_BTN_SPACING);
    btn.bottom = btn.top + MENU_BTN_H;

    strcpy(btn.graph.text, text);
    btn.graph.fontsize = MENU_BUTTON_FONTSIZE;
    btn.graph.bg = MENU_BUTTON_BG;
    btn.graph.fg = MENU_BUTTON_FG;
    btn.graph.bg_hover = MENU_BUTTON_BG_HOVER;
    btn.graph.fg_hover = MENU_BUTTON_FG_HOVER;

    return btn;
}

void drawGameTitle() {
    char title[100];
    strcpy(title, GAME_TITLE);
    drawCenteredText(WINDOW_WIDTH / 2, MENU_OFFSET / 2, title, TITLE_FG, MENU_BG, TITLE_FONTSIZE);
}

void playMenu() {
    setbkcolorRGB(MENU_BG);
    cleardevice();

    char text[200];
    strcpy(text, PLAY_TEXT);
    drawCenteredText(WINDOW_WIDTH / 2, MENU_OFFSET / 2, text, PLAY_FG, PLAY_BG, PLAY_FONTSIZE);

    button btn_SP = initMenuButton(0, BTN_SINGLEPLAYER);
    button btn_SPP = initMenuButton(1, BTN_SINGLEPLAYER_PLUS);
    button btn_MP = initMenuButton(2, BTN_MULTIPLAYER);
    button btn_AI = initMenuButton(3, BTN_AI);

    drawButton(btn_SP);
    drawButton(btn_SPP);
    drawButton(btn_MP);
    drawButton(btn_AI);

    bool game_selected = false;
    while (!game_selected) {
        buttonLoopStep(btn_SP);
        buttonLoopStep(btn_SPP);
        buttonLoopStep(btn_MP);
        buttonLoopStep(btn_AI);

        if (ismouseclick(WM_LBUTTONDOWN)) {
            clearmouseclick(WM_LBUTTONDOWN);
            if (btn_SP.hover) {
                SPGameLoop(false);
                game_selected = true;
            }
            if (btn_SPP.hover) {
                SPGameLoop(true);
                game_selected = true;
            }
        }
    }
}

void game() {
    button btn_play = initMenuButton(0, BTN_PLAY);
    button btn_settings = initMenuButton(1, BTN_SETTINGS);
    button btn_help = initMenuButton(2, BTN_HELP);
    button btn_quit = initMenuButton(3, BTN_QUIT);

    bool menu_landing = true;
    while (true) {
        if (menu_landing) {
            setbkcolorRGB(MENU_BG);
            cleardevice();
            drawGameTitle();

            drawButton(btn_play);
            drawButton(btn_settings);
            drawButton(btn_help);
            drawButton(btn_quit);    

            menu_landing = false;
        }
        
        buttonLoopStep(btn_play);
        buttonLoopStep(btn_settings);
        buttonLoopStep(btn_help);
        buttonLoopStep(btn_quit);

        if (ismouseclick(WM_LBUTTONDOWN)) {
            clearmouseclick(WM_LBUTTONDOWN);
            if (btn_play.hover) {
                playMenu();
                menu_landing = true;
            }

            if (btn_quit.hover) {
                break;
            }
        }
    }
}

// todo: reverse-singleplayer, AI proof of concept

// todo: 2 player
