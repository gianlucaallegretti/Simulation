#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdlib.h>
#include <allegro.h>
#include "graphics.c"

#define N 5
// To define the number of each color for semaphores
#define green 10
#define yellow 14
#define red 12

#define XWIN 600
#define YWIN 600

struct cars_t {
    sem_t mutex, macchina;
    int xposition, yposition;
} cars;

void init_cars (struct cars_t *c) {
    sem_init (&c->mutex, 0, 1);
    sem_init (&c->macchina, 0, 0);

    c->xposition = 5;
    c->yposition = 5;
}

void *macchina (void *arg){
    int prova = 0;
}

void *semaforo (void *arg){

    int i = 0;
    int color_EO[2] = {green, red};
    int color_NS[2] = {red, green};
    for (;;){
        if (i == 2){
            i = 0;
        }

        EastSemaphore(color_EO[i]);
        WestSemaphore(color_EO[i]);
        NorthSemaphore(color_NS[i]);
        SouthSemaphore(color_NS[i]);
        i++;
        sleep(10);
    }
}

int main(){

    drawGraphics();
    drawLines();

    pthread_t macchinina, semaforino;
    pthread_attr_t attr;
    
    int id = 0;
    srand(time(NULL));

    pthread_attr_init(&attr);
    init_cars(&cars);

    // N thread cars
    for (int i = 0; i < N; i++){
        pthread_create (&macchinina, &attr, macchina, (void *)(__intptr_t)id);
        id++;
    }

    // 1 thread semaforo
    pthread_create (&semaforino, &attr, semaforo, NULL);
    
    install_keyboard();
    int k = 0;
    do{
        if (keypressed()){
            k = readkey() >> 8;
        }

    } while (k != KEY_ESC);
}