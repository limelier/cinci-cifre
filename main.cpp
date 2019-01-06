#include <iostream>
#include <stdlib.h>
#include "graphical_game.h"

#include "CLI_game.h"
using namespace std;

int main() {
    initwindow(800,600);
    setactivepage(1);
    setvisualpage(1);
    srand(time(nullptr));

    SPGameLoop();

    getch();
    closegraph();

    return 0;
}
