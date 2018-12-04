#include <iostream>
#include <winbgim.h>

using namespace std;

void drawFilledRect(int left, int top, int right, int bottom) {
    int poly_points[8] = 
    {
        left, top,
        right, top,
        right, bottom,
        left, bottom
    };

    fillpoly(4, poly_points);
}

int main() {

    initwindow(800,600);
    
    setcolor(COLOR(200, 200, 200));
    setfillstyle(1, COLOR(100, 100, 100));
    drawFilledRect(200, 200, 400, 300);

    getch();
    closegraph();
    return 0;
}
