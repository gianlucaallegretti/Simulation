#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <allegro.h>

// To define the number of vehicles
#define N 16

// To define the dimension of the cars
#define dimension_car 5

int firstLanes[4] = {210, 235, 260, 285};
int secondLanes[4] = {310, 335, 360, 385};

struct privata {
    sem_t macchina;
    int xposition, yposition, blocked;
    char startingposition;
    bool turn, finished;
} ;

struct condivisa {
    sem_t mutex;
    struct privata vehicle[N];
    int colorSemaphoreEO, colorSemaphoreNS;
} cond;

// To init cars
void initStruct (struct condivisa *c);

// To start again cars
void carStart (struct condivisa *c, int num_car);

// To turn cars
void carTurn (struct condivisa *c, int num_car);

// To move car
void carMove (struct condivisa *c, int num_car);

// To check the color of the semaphore before passing
void checkSemaphore (struct condivisa *c, int num_car);

// To check if there are some cars blocked
void checkCarsBlocked(struct condivisa *c);

// To check if cars finished
void carFinish (struct condivisa *c, int num_car);

// To change color of the semaphore
void changeColor (int colorEO, int colorNS, struct condivisa *c);


