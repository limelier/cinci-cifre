#include <iostream>
#include <winbgim.h>
#include "CLI_game.h"

using namespace std;

int main() {
    // gameLoop();

    initwindow(800,600);
    int x = 400, y = 300, r; 
    for (r = 25; r <= 125; r += 20)
        circle(x, y, r);

    getch();
    closegraph();
    return 0;
}
