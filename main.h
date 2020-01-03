#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdbool.h>

// To define the number of vehicles
#define N 12

// To define the number of each color for semaphores
#define green 10
#define red 12
#define yellow 14

struct privata {
    sem_t macchina;
    int xposition, yposition, blocked;
    char startingposition;
    bool turn;
} ;

struct condivisa {
    sem_t mutex;
    struct privata vehicle[N];
    int colorSemaphoreEO, colorSemaphoreNS, num_macchine;
} cond;

// To init cars
void initStruct (struct condivisa *c);

// To move car
void carMove (struct condivisa *c, int num_car);

// To check the color of the semaphore before passing
void checkSemaphore (struct condivisa *c, int num_car);

// To check if there are some cars blocked
void checkCarsBlocked(int colorEO, int colorNS, struct condivisa *c);

