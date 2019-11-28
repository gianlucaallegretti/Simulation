#include "graphics.c"
#include "cars.c"
#include "semaphore.c"
#include <stdio.h>

#define green 10
#define yellow 14
#define red 12

int main (int argc, char **argv){

    int k = 0;

    // To draw graphics
    drawGraphics();    

    // To draw lines in the road
    drawLines();

    // To draw cars
    drawCarsEast();
    drawCarsNorth();
    drawCarsSouth();
    drawCarsWest();


    int color [3] = {green, yellow, red};
    for (int i = 0; ; i ++){
        if (i == 3) {
            i = 0;
            }
        int realcolor = color[i];

        EastSemaphore(realcolor);
        NorthSemaphore(realcolor);
        WestSemaphore(realcolor);
        SouthSemaphore(realcolor);
        sleep(3);
    }

    // when ESC is clicked, the app will be closed
    install_keyboard();
    do{
        if (keypressed()){
            k = readkey() >> 8;
        }
    } while (k != KEY_ESC);
}
