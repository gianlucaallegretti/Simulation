#include <allegro.h>
#include <stdio.h>

// passing the color to east semaphore
void EastSemaphore(color){
    rectfill(screen, 400, 205, 410, 220, color);
    rectfill(screen, 400, 230, 410, 245, color);
    rectfill(screen, 400, 255, 410, 270, color);
    rectfill(screen, 400, 280, 410, 295, color);
}

// passing the color to north semaphore
void NorthSemaphore(color){
    rectfill(screen, 205, 190, 220, 200, color);
    rectfill(screen, 230, 190, 245, 200, color);
    rectfill(screen, 255, 190, 270, 200, color);
    rectfill(screen, 280, 190, 295, 200, color);
}

// passing the color to west semaphore
void WestSemaphore(color){
    rectfill(screen, 190, 305, 200, 320, color);
    rectfill(screen, 190, 330, 200, 345, color);
    rectfill(screen, 190, 355, 200, 370, color);
    rectfill(screen, 190, 380, 200, 395, color);
}

// passing the color to south semaphore
void SouthSemaphore(color){
    rectfill(screen, 305, 400, 320, 410, color);
    rectfill(screen, 330, 400, 345, 410, color);
    rectfill(screen, 355, 400, 370, 410, color);
    rectfill(screen, 380, 400, 395, 410, color);
}