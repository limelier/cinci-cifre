#include <iostream>
#include "game_graphics.h"

using namespace std;

int main() {

    initwindow(800,600);
    
    drawEnabledDigit(200, 200, 4);
    drawEnabledDigit(200 + DIGIT_TILE_WIDTH + 3, 200, 5);
    
    getch();
    closegraph();
    return 0;
}
