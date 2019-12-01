#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

// To define the number of vehicles
#define N 11

// To define the number of each color for semaphores
#define green 10
#define red 12

struct privata {
    sem_t macchina;
    int xposition, yposition, blocked;
    char startingposition;
} ;

struct cars_t {
    sem_t mutex;
    struct privata vehicle[N];
} cars;

// To init cars
void initCars (struct cars_t *c);

// To move car
void carMove (struct cars_t *c, int numero_macchina);

// To check the color of the semaphore before passing
void checkSemaphore (struct cars_t *c, int numero_macchine);

// To check if there are some cars blocked on east-west
void checkCarsBlockedEO(int color, struct cars_t *c);

// To check if there are some cars blocked on north-south
void checkCarsBlockedNS(int color, struct cars_t *c);

