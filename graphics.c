#include <allegro.h>
#include <stdio.h>
// XWIN and YWIN must be the same
#define XWIN 600
#define YWIN 600

// To draw graphics and init allegro
void drawGraphics(){
    allegro_init();
    set_color_depth(8);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, XWIN, YWIN, 0, 0);
    clear_to_color(screen, 2);
    rectfill(screen, XWIN/2 - 100, 0, (XWIN/2)+ 100, YWIN-1, 8);
    rectfill(screen, 0, (YWIN/2) - 100, XWIN-1, (YWIN/2) + 100, 8);
}

// To draw road lines
void drawLines(){
    // WEST POSITION
    int i = 0;
    for (i = 0; i <= 160; i=i+10){
        rectfill(screen, i, 224, i+5, 226, 15);
        rectfill(screen, i, 249, i+5, 251, 15);
        rectfill(screen, i, 274, i+5, 276, 15);
    }

    // to make it continue when it's near semaphore
    rectfill(screen, XWIN/2 - 140, 224, XWIN/2 - 100, 226, 15);
    rectfill(screen, XWIN/2 - 140, 249, XWIN/2 - 100, 251, 15);
    rectfill(screen, XWIN/2 - 140, 274, XWIN/2 - 100, 276, 15);
    // Line to separate 2 different way to go (right-left/left-right)
    rectfill(screen, 0, YWIN/2 -1, XWIN/2 - 100, YWIN/2 + 1, 15);
    
    // Other side
    for(i = 0; i <= 160; i+=10){
        rectfill(screen, i, 324, i+5, 326, 15);
        rectfill(screen, i, 349, i+5, 351, 15);
        rectfill(screen, i, 374, i+5, 376, 15);
    }

    rectfill(screen, XWIN/2 - 140, 324, XWIN/2 - 100, 326, 15);
    rectfill(screen, XWIN/2 - 140, 349, XWIN/2 - 100, 351, 15);
    rectfill(screen, XWIN/2 - 140, 374, XWIN/2 - 100, 376, 15);



    // EAST POSITION
    for (i = 440; i <= 600; i=i+10){
        rectfill(screen, i, 224, i+5, 226, 15);
        rectfill(screen, i, 249, i+5, 251, 15);
        rectfill(screen, i, 274, i+5, 276, 15);
    }

    // to make it continue when it's near semaphore
    rectfill(screen, 400, 224, 440, 226, 15);
    rectfill(screen, 400, 249, 440, 251, 15);
    rectfill(screen, 400, 274, 440, 276, 15);
    // Line to separate 2 different way to go (right-left/left-right)
    rectfill(screen, 400, YWIN/2 - 1, XWIN, YWIN/2 +1, 15);
    
    // Other side
    for(i = 440; i <= 600; i+=10){
        rectfill(screen, i, 324, i+5, 326, 15);
        rectfill(screen, i, 349, i+5, 351, 15);
        rectfill(screen, i, 374, i+5, 376, 15);
    }

    rectfill(screen, 400, 324, 440, 326, 15);
    rectfill(screen, 400, 349, 440, 351, 15);
    rectfill(screen, 400, 374, 440, 376, 15);



    // NORTH POSITION
    for (i = 0; i <= 160; i=i+10){
        rectfill(screen, 224, i, 226, i+5, 15);
        rectfill(screen, 249, i, 251, i+5, 15);
        rectfill(screen, 274, i, 276, i+5, 15);
    }

    // to make it continue when it's near semaphore
    rectfill(screen, 224, YWIN/2 - 140, 226, YWIN/2 - 100, 15);
    rectfill(screen, 249, YWIN/2 - 140, 251, YWIN/2 - 100, 15);
    rectfill(screen, 274, YWIN/2 - 140, 276, YWIN/2 - 100, 15);
    // Line to separate 2 different way to go (right-left/left-right)
    rectfill(screen, XWIN/2 - 1, 0, XWIN/2 + 1, YWIN/2 - 100, 15);
    
    // Other side
    for(i = 0; i <= 160; i+=10){
        rectfill(screen, 324, i, 326, i+5, 15);
        rectfill(screen, 349, i, 351, i+5, 15);
        rectfill(screen, 374, i, 376, i+5, 15);
    }

    rectfill(screen, 324, YWIN/2 - 140, 326, YWIN/2 - 100, 15);
    rectfill(screen, 349, YWIN/2 - 140, 351, YWIN/2 - 100, 15);
    rectfill(screen, 374, YWIN/2 - 140, 376, YWIN/2 - 100, 15);



    // SOUTH POSITION
    for (i = 440; i <= 600; i=i+10){
        rectfill(screen, 224, i, 226, i+5, 15);
        rectfill(screen, 249, i, 251, i+5, 15);
        rectfill(screen, 274, i, 276, i+5, 15);
    }

    // to make it continue when it's near semaphore
    rectfill(screen, 224, 400, 226, 440, 15);
    rectfill(screen, 249, 400, 251, 440, 15);
    rectfill(screen, 274, 400, 276, 440, 15);
    // Line to separate 2 different way to go (right-left/left-right)
    rectfill(screen, XWIN/2 - 1, 400, XWIN/2 + 1, YWIN, 15);
    
    // Other side
    for(i = 440; i <= 600; i+=10){
        rectfill(screen, 324, i, 326, i+5, 15);
        rectfill(screen, 349, i, 351, i+5, 15);
        rectfill(screen, 374, i, 376, i+5, 15);
    }

    rectfill(screen, 324, 400, 326, 440, 15);
    rectfill(screen, 349, 400, 351, 440, 15);
    rectfill(screen, 374, 400, 376, 440, 15);
}

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