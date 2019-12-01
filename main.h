#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

// To define the number of vehicles
#define N 4

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
    int cars_blocked;
} cars;

void initCars (struct cars_t *c);

void carMove (struct cars_t *c, int numero_macchina);

void checkSemaphore (struct cars_t *c, int numero_macchine);

void checkEnd (struct cars_t *c, int numero_macchina);

void checkCarsBlocked(int color, struct cars_t *c);

