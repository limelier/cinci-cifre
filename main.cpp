#include <iostream>
#include "game_graphics.h"

using namespace std;

int main() {

    initwindow(800,600);
    
    drawDisabledDigit(200, 200, 4);
    
    getch();
    closegraph();
    return 0;
}
