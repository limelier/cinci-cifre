#include <iostream>
#include <stdlib.h>
#include "graphical_game.h"
using namespace std;

int main() {
    initwindow(800,600);

    inputPermutation2();

    getch();
    closegraph();

    return 0;
}
