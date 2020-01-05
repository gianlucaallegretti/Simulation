#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdlib.h>
#include <allegro.h>

// To define the length of the screen
#define XWIN 600
#define YWIN 600

// To define the number of each color for semaphores
#define green 10
#define red 12
#define yellow 14
#define white 15

// To init allegro and graphics
void initGraphics();

// To draw graphics
void drawGraphics();

// To draw cars
void drawCars(struct condivisa *c);

// To change color of semaphore
void changeColor (int colorEO, int colorNS, struct condivisa *c);

// For the color of the semaphores
void EOSemaphore(int colorEO);
void NSSemaphore(int colorNS);

// To draw lines in the graphic
void drawLines();