#include "graphics.c"
#include "main.h"

void initCars (struct cars_t *c) {

    // Initiliazing mutex
    sem_init (&c->mutex, 0, 1);

    for (int i = 0; i < N; i++){
        
        // Initializing 4 cars for each direction
        if (i < 4){
            int xpos[4] = {210, 235, 260, 285};
            int index = rand() % 4;

            
            c->vehicle[i].startingposition = 'N';
            c->vehicle[i].xposition = xpos[index];
            c->vehicle[i].yposition = 10;
        }
        else if (i < 8){
            int ypos[4] = {210, 235, 260, 285};
            int index = rand() % 4;

            
            c->vehicle[i].startingposition = 'W';
            c->vehicle[i].xposition = 590;
            c->vehicle[i].yposition =ypos[index];
        }
        else if (i < 12){
            int ypos[4] = {310, 335, 360, 385};
            int index = rand() % 4;

            
            c->vehicle[i].startingposition = 'E';
            c->vehicle[i].xposition = 10;
            c->vehicle[i].yposition = ypos[index];
        }
        else if (i < 16){
            int xpos[4] = {310, 335, 360, 385};
            int index = rand() % 4;

            
            c->vehicle[i].startingposition = 'S';
            c->vehicle[i].xposition = xpos[index];
            c->vehicle[i].yposition = 450;
        }

        // All semaphores initialized to 0
        sem_init (&c->vehicle[i].macchina, 0, 0);
        c->vehicle[i].blocked = 0;
        
        // Drawing the car like a circlefill
        circlefill(screen, c->vehicle[i].xposition, c->vehicle[i].yposition, 5, 14);
    }
}


// NEVER BLOCKING
void carMove(struct cars_t *c, int num_car){

    // Deleting the all position of the car
    circlefill(screen, c->vehicle[num_car].xposition, c->vehicle[num_car].yposition, 5, 8);

    
    // Setting the new position of the car
    // WEST
    if (c->vehicle[num_car].startingposition == 'W'){
        c->vehicle[num_car].xposition -= 10;
    }
    // EAST
    else if (c->vehicle[num_car].startingposition == 'E'){
        c->vehicle[num_car].xposition += 10;
    }
    // NORTH
    else if (c->vehicle[num_car].startingposition == 'N'){
        c->vehicle[num_car].yposition += 10;
    }
    // SOUTH
    else if (c->vehicle[num_car].startingposition == 'S'){
        c->vehicle[num_car].yposition -= 10;
    }
    // drawing
    circlefill(screen, c->vehicle[num_car].xposition, c->vehicle[num_car].yposition, 5, 14);
}


// POTENTIALLY BLOCKING
void checkSemaphore (struct cars_t *c, int num_car){

    // Coming from WEST
    if ((c->vehicle[num_car].xposition <= 420) && (c->vehicle[num_car].xposition > 410) && c->vehicle[num_car].startingposition == 'W') {
        c->vehicle[num_car].blocked = 1;
        sem_wait(&c->vehicle[num_car].macchina);
    }

    
    // Coming from EAST
    if ((c->vehicle[num_car].xposition >= 180) && (c->vehicle[num_car].xposition < 190) && c->vehicle[num_car].startingposition == 'E') {
        c->vehicle[num_car].blocked = 1;
        sem_wait(&c->vehicle[num_car].macchina);
    }

    
    // Coming from NORTH
    if ((c->vehicle[num_car].yposition >= 180) && (c->vehicle[num_car].yposition < 190) && c->vehicle[num_car].startingposition == 'N') {
        c->vehicle[num_car].blocked = 1;
        sem_wait(&c->vehicle[num_car].macchina);
    }

    
    // Coming from SOUTH
    if ((c->vehicle[num_car].yposition <= 420) && (c->vehicle[num_car].yposition > 410) && c->vehicle[num_car].startingposition == 'S') {
        c->vehicle[num_car].blocked = 1;
        sem_wait(&c->vehicle[num_car].macchina);
    }
}


// To check if there's some car blocked on east-west direction
void checkCarsBlockedEO (int color, struct cars_t *c){

    if (color == green) {
        for (int i = 0; i < N; i++){
            if (c->vehicle[i].blocked == 1 && (c->vehicle[i].startingposition == 'W' || c->vehicle[i].startingposition == 'E')) {
                sem_post(&c->vehicle[i].macchina);
            }
        }
    }
}


// To check if there's some car blocked on north-south direction
void checkCarsBlockedNS (int color, struct cars_t *c){

    if (color == green) {
        for (int i = 0; i < N; i++){
            if (c->vehicle[i].blocked == 1 && (c->vehicle[i].startingposition == 'N' || c->vehicle[i].startingposition == 'S')) {
                sem_post(&c->vehicle[i].macchina);
            }
        }
    }
}




/////////////// THREAD ///////////////

void *macchina (void *arg){

    int num_car;
    num_car = (intptr_t) arg;

    for (;;){
        carMove(&cars, num_car);
        checkSemaphore(&cars, num_car);
        sleep(1);
    }
}

void *semaforo (void *arg){

    int i = 0;
    int color_EO[2] = {green, red};
    int color_NS[2] = {red, green};
    for (;;){
        if (i == 2){
            i = 0;
        }

        EOSemaphore (color_EO[i]);
        NSSemaphore (color_NS[i]);
        checkCarsBlockedEO (color_EO[i], &cars);
        checkCarsBlockedNS (color_NS[i], &cars);

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
    initCars(&cars);

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