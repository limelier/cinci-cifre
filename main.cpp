#include <iostream>
#include "game_graphics.h"
#include "CLI_game.h"

using namespace std;

int main() {

    initwindow(800,600);

    permutation perm1 = debugInputPermutation();
    permutation perm2 = debugInputPermutation();

    drawPerm(200, 200, perm1, false);
    drawHiddenPerm(200, 300);
    
    result res = comparePermutations(perm1, perm2);
    drawGuess(200, 250, perm2, res, true);
    
    getch();
    closegraph();
    return 0;
}
