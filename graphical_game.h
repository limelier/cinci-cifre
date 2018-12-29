#pragma once

#include "base_dependencies.h"
#include "rares_depends.h"
#include "game_graphics.h"

// temporary
#include "CLI_game.h"

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

bool isButtonPressed (button btn); // todo

permutation inputPermutation2() {
    permutation input;
    bool perm_complete = false;

    // drawInputDialog();

    while (perm_complete == false) {
        // drawInputDialog();
        // < look for key hits 0-9
        // << if pressed, and not complete, add character
        // < look for button hits: enter, erase and clear
        // << if enter: 
        // <<< if complete:
        // <<<< if correct: perm_complete = true, input the perm, then erase all characters
        // <<<< if incorrect: display relevant error message
        // <<< if incomplete: display relevant error message
        // << if erase & not empty: erase one character
        // << if clear & not empty: erase all characters
    }

    return input;
}

void SPGameLoop() {
    game_panel game;

    // after these instructions, base_perm has the base permutation in it
    game.base_perm = RandomPermutationGenerator();
    ///

    permutation input;
    while (game.has_been_won == false) {
        setbkcolor(BLACK);
        cleardevice();

        drawGamePanel(300, game);

        // after these instructions, input has the guess in it
        input = inputPermutation();
        ///

        guesslistPush(game.list, makeGuess(game.base_perm, input));

        // todo: being able to win
    }
}



// todo: reverse-singleplayer, AI proof of concept

// todo: 2 player 