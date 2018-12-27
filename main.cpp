#include <iostream>
#include "game_graphics.h"
#include "graphical_game.h"
using namespace std;

// void testLoop() {
//     srand(time(NULL));
//     game_panel game;
//     game.base_perm = RandomPermutationGenerator();

//     for (int i = 0; i < 12; i++) {
//         guessnode *node;
//         node = new guessnode;
//         node->perm = RandomPermutationGenerator();
//         node->res = comparePermutations(game.base_perm, node->perm);
//         guesslistPush(game.list, node);
//     }

//     game.active = 1;
//     drawGamePanel(20, game);
// }


int main() {
    initwindow(800,600);

    // drawLabel(200, 200, "fixed", false);
    SPGameLoop();

    getch();
    closegraph();

    return 0;
}
