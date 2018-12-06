#include <iostream>
#include "game_graphics.h"
#include "CLI_game.h"

using namespace std;

int main() {

    initwindow(800,600);
    
    permutation perm1 = inputPermutation(); // todo make file input
    permutation perm2 = inputPermutation();

    drawPerm(200, 200, perm1, true);
    drawPerm(200, 250, perm2, false);
    drawHiddenPerm(200, 300);
    
    getch();
    closegraph();
    return 0;
}
