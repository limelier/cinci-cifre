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

    // testing
    // slide_switch ssw;
    // ssw.x = 300;
    // ssw.y = 200;
    // drawSSwitch(ssw);
    // while(true) {
    //     SSwitchLoopStep(ssw);

    //     if (ismouseclick(WM_LBUTTONDOWN)) {
    //         if (ssw.hover)
    //             SSwitchFlick(ssw);
    //         clearmouseclick(WM_LBUTTONDOWN);
    //     }
    // }
    // getch();
    
    AIGameLoop();

    game();

    closegraph();

    return 0;
}
