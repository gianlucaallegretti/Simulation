#include "graphics.h"

// XWIN and YWIN must be the same
#define XWIN 600
#define YWIN 600

// To init allegro
void initGraphics(){
    allegro_init();
    set_color_depth(8);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, XWIN, YWIN, 0, 0);
}

// To draw graphics
void drawGraphics(){ 
    clear_to_color(screen, 2);
    rectfill(screen, XWIN/2 - 100, 0, (XWIN/2)+ 100, YWIN-1, 8);
    rectfill(screen, 0, (YWIN/2) - 100, XWIN-1, (YWIN/2) + 100, 8);
}

// To draw cars
void drawCars(struct condivisa *c){
    for (int i = 0; i < N; i++){
    // Drawing car in new position
    circlefill(screen, c->vehicle[i].xposition, c->vehicle[i].yposition, 5, 14);

    // Re-drawing semaphores
    if (c->vehicle[i].startingposition == 'E' || c->vehicle[i].startingposition == 'W')
        EOSemaphore(c->colorSemaphoreEO);
    else
        NSSemaphore(c->colorSemaphoreNS);
    }
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

    // To draw which direction cars can take
    rectfill(screen, XWIN/2 - 140, 335, XWIN/2 - 130, 340, 15);
    triangle(screen, XWIN/2 - 130, 333, XWIN/2 - 130, 342, XWIN/2 -120, 337.5, 15);
    rectfill(screen, XWIN/2 - 140, 360, XWIN/2 - 130, 365, 15);
    triangle(screen, XWIN/2 - 130, 358, XWIN/2 - 130, 367, XWIN/2 -120, 362.5, 15);

    rectfill(screen, YWIN/2 + 140, 218, YWIN/2 + 125, 220, 15);
    rectfill(screen, YWIN/2 + 125, 216, YWIN/2 + 125, 218, 15);
    triangle(screen, YWIN/2 + 120, 216, YWIN/2 + 130, 216, YWIN/2 + 125, 207, 15);

    rectfill(screen, YWIN/2 + 140, 282, YWIN/2 + 125, 284, 15);
    rectfill(screen, YWIN/2 + 125, 284, YWIN/2 + 125, 286, 15);
    triangle(screen, YWIN/2 + 120, 286, YWIN/2 + 130, 286, YWIN/2 + 125, 295, 15);


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

    // To draw which direction cars can take
    rectfill(screen, 430, 235, 440, 240, 15);
    triangle(screen, 430, 233, 430, 242, 420, 237.5, 15);
    rectfill(screen, 430, 260, 440, 265, 15);
    triangle(screen, 430, 258, 430, 267, 420, 262.5, 15);

    rectfill(screen, YWIN/2 - 140, 318, YWIN/2 - 125, 320, 15);
    rectfill(screen, YWIN/2 - 125, 316, YWIN/2 - 125, 318, 15);
    triangle(screen, YWIN/2 - 120, 316, YWIN/2 - 130, 316, YWIN/2 - 125, 307, 15);

    rectfill(screen, YWIN/2 - 140, 382, YWIN/2 - 125, 384, 15);
    rectfill(screen, YWIN/2 - 125, 384, YWIN/2 - 125, 386, 15);
    triangle(screen, YWIN/2 - 120, 386, YWIN/2 - 130, 386, YWIN/2 - 125, 395, 15);

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

    // To draw which direction cars can take
    rectfill(screen, 235, YWIN/2 - 140, 240, YWIN/2 - 130, 15);
    triangle(screen, 233, YWIN/2 - 130, 242, YWIN/2 - 130, 237.5, YWIN/2 - 120, 15);
    rectfill(screen, 260, YWIN/2 - 140, 265, YWIN/2 - 130, 15);
    triangle(screen, 258, YWIN/2 - 130, 267, YWIN/2 - 130, 262.5, YWIN/2 - 120, 15);
    
    rectfill(screen, 218, YWIN/2 - 140, 220, YWIN/2 - 125, 15);
    rectfill(screen, 216, YWIN/2 - 125, 218, YWIN/2 - 125, 15);
    triangle(screen, 216, YWIN/2 - 120, 216, YWIN/2 - 130, 207, YWIN/2 - 125, 15);

    rectfill(screen, 284, YWIN/2 - 140, 286, YWIN/2 - 125, 15);
    rectfill(screen, 286, YWIN/2 - 125, 288, YWIN/2 - 125, 15);
    triangle(screen, 288, YWIN/2 - 120, 288, YWIN/2 - 130, 297, YWIN/2 - 125, 15);


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

    // To draw which direction cars can take
    rectfill(screen, 335, 430, 340, 440, 15);
    triangle(screen, 333, 430, 342, 430, 337.5, 420, 15);
    rectfill(screen, 360, 430, 365, 440, 15);
    triangle(screen, 358, 430, 367, 430, 362.5, 420, 15);

    rectfill(screen, 318, YWIN/2 + 140, 320, YWIN/2 + 125, 15);
    rectfill(screen, 316, YWIN/2 + 125, 318, YWIN/2 + 125, 15);
    triangle(screen, 316, YWIN/2 + 120, 316, YWIN/2 + 130, 307, YWIN/2 + 125, 15);

    rectfill(screen, 384, YWIN/2 + 140, 386, YWIN/2 + 125, 15);
    rectfill(screen, 386, YWIN/2 + 125, 388, YWIN/2 + 125, 15);
    triangle(screen, 388, YWIN/2 + 120, 388, YWIN/2 + 130, 397, YWIN/2 + 125, 15);

}

// passing the color to east-west semaphore
void EOSemaphore(int color){
    rectfill(screen, 400, 205, 410, 220, color);
    rectfill(screen, 400, 230, 410, 245, color);
    rectfill(screen, 400, 255, 410, 270, color);
    rectfill(screen, 400, 280, 410, 295, color);

    rectfill(screen, 190, 305, 200, 320, color);
    rectfill(screen, 190, 330, 200, 345, color);
    rectfill(screen, 190, 355, 200, 370, color);
    rectfill(screen, 190, 380, 200, 395, color);
}

// passing the color to north-south semaphore
void NSSemaphore(int color){
    rectfill(screen, 205, 190, 220, 200, color);
    rectfill(screen, 230, 190, 245, 200, color);
    rectfill(screen, 255, 190, 270, 200, color);
    rectfill(screen, 280, 190, 295, 200, color);

    rectfill(screen, 305, 400, 320, 410, color);
    rectfill(screen, 330, 400, 345, 410, color);
    rectfill(screen, 355, 400, 370, 410, color);
    rectfill(screen, 380, 400, 395, 410, color);
}
