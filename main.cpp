#include <iostream>
#include <stdlib.h>
#include "graphical_game.h"
using namespace std;

int main() {
    initwindow(800,600);

    SPGameLoop();

    // permutation perm;
    // stack <int> s;
    // s.push(1);
    // s.push(2);
    // s.push(3);
    // s.push(4);
    // s.push(5);
    // perm = permFromStack(s);

    getch();
    closegraph();

    return 0;
}
