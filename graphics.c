#include "graphics.h"

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
    circlefill(screen, c->vehicle[i].xposition, c->vehicle[i].yposition, dimension_car, yellow);

    // Drawing semaphores
    if (c->vehicle[i].startingposition == 'E' || c->vehicle[i].startingposition == 'W')
        EOSemaphore(c->colorSemaphoreEO);
    else
        NSSemaphore(c->colorSemaphoreNS);
    }
}


// To change the color of the semaphore
void changeColor (int colorEO, int colorNS, struct condivisa *c){

    sem_wait(&c->mutex);
    c->colorSemaphoreEO = colorEO;
    c->colorSemaphoreNS = colorNS;
    sem_post(&c->mutex);
}

// To draw road lines
void drawLines(){
    // WEST POSITION
    int i = 0;
    for (i = 0; i <= 160; i=i+10){
        rectfill(screen, i, 224, i+5, 226, white);
        rectfill(screen, i, 249, i+5, 251, white);
        rectfill(screen, i, 274, i+5, 276, white);
    }

    // to make it continue when it's near semaphore
    rectfill(screen, XWIN/2 - 140, 224, XWIN/2 - 100, 226, white);
    rectfill(screen, XWIN/2 - 140, 249, XWIN/2 - 100, 251, white);
    rectfill(screen, XWIN/2 - 140, 274, XWIN/2 - 100, 276, white);
    // Line to separate 2 different way to go (right-left/left-right)
    rectfill(screen, 0, YWIN/2 -1, XWIN/2 - 100, YWIN/2 + 1, white);

    
    // Other side
    for(i = 0; i <= 160; i+=10){
        rectfill(screen, i, 324, i+5, 326, white);
        rectfill(screen, i, 349, i+5, 351, white);
        rectfill(screen, i, 374, i+5, 376, white);
    }

    rectfill(screen, XWIN/2 - 140, 324, XWIN/2 - 100, 326, white);
    rectfill(screen, XWIN/2 - 140, 349, XWIN/2 - 100, 351, white);
    rectfill(screen, XWIN/2 - 140, 374, XWIN/2 - 100, 376, white);

    // To draw which direction cars can take
    rectfill(screen, XWIN/2 - 140, 335, XWIN/2 - 130, 340, white);
    triangle(screen, XWIN/2 - 130, 333, XWIN/2 - 130, 342, XWIN/2 -120, 337.5, white);
    rectfill(screen, XWIN/2 - 140, 360, XWIN/2 - 130, 365, white);
    triangle(screen, XWIN/2 - 130, 358, XWIN/2 - 130, 367, XWIN/2 -120, 362.5, white);

    rectfill(screen, XWIN/2 + 140, 218, XWIN/2 + 125, (YWIN/3) + 20, white);
    rectfill(screen, XWIN/2 + 125, 216, XWIN/2 + 125, 218, white);
    triangle(screen, XWIN/2 + 120, 216, XWIN/2 + 130, 216, XWIN/2 + 125, 207, white);

    rectfill(screen, XWIN/2 + 140, 282, XWIN/2 + 125, 284, white);
    rectfill(screen, XWIN/2 + 125, 284, XWIN/2 + 125, 286, white);
    triangle(screen, XWIN/2 + 120, 286, XWIN/2 + 130, 286, XWIN/2 + 125, 295, white);


    // EAST POSITION
    for (i = 440; i <= 600; i=i+10){
        rectfill(screen, i, 224, i+5, 226, white);
        rectfill(screen, i, 249, i+5, 251, white);
        rectfill(screen, i, 274, i+5, 276, white);
    }

    // to make it continue when it's near semaphore
    rectfill(screen, (XWIN/3)*2, 224, (XWIN/3)*2 + 40, 226, white);
    rectfill(screen, (XWIN/3)*2, 249, (XWIN/3)*2 + 40, 251, white);
    rectfill(screen, (XWIN/3)*2, 274, (XWIN/3)*2 + 40, 276, white);
    // Line to separate 2 different way to go (right-left/left-right)
    rectfill(screen, (XWIN/3)*2, YWIN/2 - 1, XWIN, YWIN/2 +1, white);

    
    // Other side
    for(i = 440; i <= 600; i+=10){
        rectfill(screen, i, 324, i+5, 326, white);
        rectfill(screen, i, 349, i+5, 351, white);
        rectfill(screen, i, 374, i+5, 376, white);
    }

    rectfill(screen, (XWIN/3)*2, 324, (XWIN/3)*2 + 40, 326, white);
    rectfill(screen, (XWIN/3)*2, 349, (XWIN/3)*2 + 40, 351, white);
    rectfill(screen, (XWIN/3)*2, 374, (XWIN/3)*2 + 40, 376, white);

    // To draw which direction cars can take
    rectfill(screen, (XWIN/3)*2 + 30, 235, (XWIN/3)*2 + 40, 240, white);
    triangle(screen, (XWIN/3)*2 + 30, 233, (XWIN/3)*2 + 30, 242, (XWIN/3)*2 + 20, 237.5, white);
    rectfill(screen, (XWIN/3)*2 + 30, 260, (XWIN/3)*2 + 40, 265, white);
    triangle(screen, (XWIN/3)*2 + 30, 258, (XWIN/3)*2 + 30, 267, (XWIN/3)*2 + 20, 262.5, white);

    rectfill(screen, XWIN/2 - 140, 318, XWIN/2 - 125, 320, white);
    rectfill(screen, XWIN/2 - 125, 316, XWIN/2 - 125, 318, white);
    triangle(screen, XWIN/2 - 120, 316, XWIN/2 - 130, 316, XWIN/2 - 125, 307, white);

    rectfill(screen, XWIN/2 - 140, 382, XWIN/2 - 125, 384, white);
    rectfill(screen, XWIN/2 - 125, 384, XWIN/2 - 125, 386, white);
    triangle(screen, XWIN/2 - 120, 386, XWIN/2 - 130, 386, XWIN/2 - 125, 395, white);

    // NORTH POSITION
    for (i = 0; i <= 160; i=i+10){
        rectfill(screen, 224, i, 226, i+5, white);
        rectfill(screen, 249, i, 251, i+5, white);
        rectfill(screen, 274, i, 276, i+5, white);
    }

    // to make it continue when it's near semaphore
    rectfill(screen, 224, YWIN/2 - 140, 226, YWIN/2 - 100, white);
    rectfill(screen, 249, YWIN/2 - 140, 251, YWIN/2 - 100, white);
    rectfill(screen, 274, YWIN/2 - 140, 276, YWIN/2 - 100, white);
    // Line to separate 2 different way to go (right-left/left-right)
    rectfill(screen, XWIN/2 - 1, 0, XWIN/2 + 1, YWIN/2 - 100, white);

    
    // Other side
    for(i = 0; i <= 160; i+=10){
        rectfill(screen, 324, i, 326, i+5, white);
        rectfill(screen, 349, i, 351, i+5, white);
        rectfill(screen, 374, i, 376, i+5, white);
    }

    rectfill(screen, 324, YWIN/2 - 140, 326, YWIN/2 - 100, white);
    rectfill(screen, 349, YWIN/2 - 140, 351, YWIN/2 - 100, white);
    rectfill(screen, 374, YWIN/2 - 140, 376, YWIN/2 - 100, white);

    // To draw which direction cars can take
    rectfill(screen, 235, YWIN/2 - 140, 240, YWIN/2 - 130, white);
    triangle(screen, 233, YWIN/2 - 130, 242, YWIN/2 - 130, 237.5, YWIN/2 - 120, white);
    rectfill(screen, 260, YWIN/2 - 140, 265, YWIN/2 - 130, white);
    triangle(screen, 258, YWIN/2 - 130, 267, YWIN/2 - 130, 262.5, YWIN/2 - 120, white);

    
    rectfill(screen, 218, YWIN/2 - 140, (XWIN/3) + 20, YWIN/2 - 125, white);
    rectfill(screen, 216, YWIN/2 - 125, 218, YWIN/2 - 125, white);
    triangle(screen, 216, YWIN/2 - 120, 216, YWIN/2 - 130, 207, YWIN/2 - 125, white);

    rectfill(screen, 284, YWIN/2 - 140, 286, YWIN/2 - 125, white);
    rectfill(screen, 286, YWIN/2 - 125, 288, YWIN/2 - 125, white);
    triangle(screen, 288, YWIN/2 - 120, 288, YWIN/2 - 130, 297, YWIN/2 - 125, white);


    // SOUTH POSITION
    for (i = 440; i <= 600; i=i+10){
        rectfill(screen, 224, i, 226, i+5, white);
        rectfill(screen, 249, i, 251, i+5, white);
        rectfill(screen, 274, i, 276, i+5, white);
    }

    // to make it continue when it's near semaphore
    rectfill(screen, 224, (YWIN/3)*2, 226, (YWIN/3)*2 + 40, white);
    rectfill(screen, 249, (YWIN/3)*2, 251, (YWIN/3)*2 + 40, white);
    rectfill(screen, 274, (YWIN/3)*2, 276, (YWIN/3)*2 + 40, white);
    // Line to separate 2 different way to go (right-left/left-right)
    rectfill(screen, XWIN/2 - 1, (YWIN/3)*2, XWIN/2 + 1, YWIN, white);

    
    // Other side
    for(i = 440; i <= 600; i+=10){
        rectfill(screen, 324, i, 326, i+5, white);
        rectfill(screen, 349, i, 351, i+5, white);
        rectfill(screen, 374, i, 376, i+5, white);
    }

    rectfill(screen, 324, (YWIN/3)*2, 326, (YWIN/3)*2 + 40, white);
    rectfill(screen, 349, (YWIN/3)*2, 351, (YWIN/3)*2 + 40, white);
    rectfill(screen, 374, (YWIN/3)*2, 376, (YWIN/3)*2 + 40, white);

    // To draw which direction cars can take
    rectfill(screen, 335, (YWIN/3)*2 + 30, 340, (YWIN/3)*2 + 40, white);
    triangle(screen, 333, (YWIN/3)*2 + 30, 342, (YWIN/3)*2 + 30, 337.5, (YWIN/3)*2 + 20, white);
    rectfill(screen, 360, (YWIN/3)*2 + 30, 365, (YWIN/3)*2 + 40, white);
    triangle(screen, 358, (YWIN/3)*2 + 30, 367, (YWIN/3)*2 + 30, 362.5, (YWIN/3)*2 + 20, white);

    rectfill(screen, 318, YWIN/2 + 140, 320, YWIN/2 + 125, white);
    rectfill(screen, 316, YWIN/2 + 125, 318, YWIN/2 + 125, white);
    triangle(screen, 316, YWIN/2 + 120, 316, YWIN/2 + 130, 307, YWIN/2 + 125, white);

    rectfill(screen, 384, YWIN/2 + 140, 386, YWIN/2 + 125, white);
    rectfill(screen, 386, YWIN/2 + 125, 388, YWIN/2 + 125, white);
    triangle(screen, 388, YWIN/2 + 120, 388, YWIN/2 + 130, 397, YWIN/2 + 125, white);

}

// passing the color to east-west semaphore
void EOSemaphore(int color){
    rectfill(screen, (XWIN/3)*2, (YWIN/3) + 5, (XWIN/3)*2 + 10, (YWIN/3) + 20, color);
    rectfill(screen, (XWIN/3)*2, 230, (XWIN/3)*2 + 10, 245, color);
    rectfill(screen, (XWIN/3)*2, 255, (XWIN/3)*2 + 10, 270, color);
    rectfill(screen, (XWIN/3)*2, 280, (XWIN/3)*2 + 10, 295, color);

    rectfill(screen, (XWIN/3) - 10, 305, (XWIN/3), 320, color);
    rectfill(screen, (XWIN/3) - 10, 330, (XWIN/3), 345, color);
    rectfill(screen, (XWIN/3) - 10, 355, (XWIN/3), 370, color);
    rectfill(screen, (XWIN/3) - 10, 380, (XWIN/3), 395, color);
}

// passing the color to north-south semaphore
void NSSemaphore(int color){
    rectfill(screen, (XWIN/3) + 5, (YWIN/3) - 10, (XWIN/3) + 20, (YWIN/3), color);
    rectfill(screen, 230, (YWIN/3) - 10, 245, (YWIN/3), color);
    rectfill(screen, 255, (YWIN/3) - 10, 270, (YWIN/3), color);
    rectfill(screen, 280, (YWIN/3) - 10, 295, (YWIN/3), color);

    rectfill(screen, 305, (YWIN/3)*2, 320, (YWIN/3)*2 + 10, color);
    rectfill(screen, 330, (YWIN/3)*2, 345, (YWIN/3)*2 + 10, color);
    rectfill(screen, 355, (YWIN/3)*2, 370, (YWIN/3)*2 + 10, color);
    rectfill(screen, 380, (YWIN/3)*2, 395, (YWIN/3)*2 + 10, color);
}