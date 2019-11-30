#include <allegro.h>
#include <stdio.h>
// XWIN and YWIN must be the same
#define XWIN 600
#define YWIN 600

// To define the number of each color for semaphores
#define green 10
#define red 12

int color;

void DrawGraphics();

void DrawLines();

void EastSemaphore(color);
void NorthSemaphore(color);
void WestSemaphore(color);
void SouthSemaphore(color);