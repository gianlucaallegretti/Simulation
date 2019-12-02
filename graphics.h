#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdlib.h>
#include <allegro.h>

// XWIN and YWIN must be the same
#define XWIN 600
#define YWIN 600

// To define the number of each color for semaphores
#define green 10
#define red 12

// For the color of the semaphores
void EOSemaphore(int color);
void NSSemaphore(int color);