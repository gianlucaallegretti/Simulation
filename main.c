#include "main.h"
#include "graphics.c"

void initCars (struct cars_t *c) {

    sem_init (&c->mutex, 0, 1);

    for (int i = 0; i < N; i++){
        // To initialize the car in a random lane
        int firstLanes[4] = {210, 235, 260, 285};
        int secondLanes[4] = {310, 335, 360, 385};
        int index = rand() % 4;

       
        // Initializing N/4 cars for each direction
        if (i < N/4){
       
            c->vehicle[i].startingposition = 'N';
            c->vehicle[i].xposition = firstLanes[index]; // 210
            c->vehicle[i].yposition = 10;
        }
        else if (i < N/2){

            c->vehicle[i].startingposition = 'W';
            c->vehicle[i].xposition = 590;
            c->vehicle[i].yposition =firstLanes[index]; // 210
        }
        else if (i < (N/4)*3){

            c->vehicle[i].startingposition = 'E';
            c->vehicle[i].xposition = 10;
            c->vehicle[i].yposition = secondLanes[index]; // 310
        }
        else if (i < N){

            c->vehicle[i].startingposition = 'S';
            c->vehicle[i].xposition = secondLanes[index]; // 310
            c->vehicle[i].yposition = 590;
        }

        // All semaphores initialized to 0
        sem_init (&c->vehicle[i].macchina, 0, 0);
        // No vehicles blocked at the beginning
        c->vehicle[i].blocked = 0;

       
        // Drawing the car like a circlefill
        circlefill(screen, c->vehicle[i].xposition, c->vehicle[i].yposition, 5, 14);
    }
}


// NEVER BLOCKING
void carMove(struct cars_t *c, int num_car){
   
    // Setting new position of the car
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

}


// NEVER BLOCKING
void changeColor (int colorEO, int colorNS, struct cars_t *c){

    for (int i = 0; i < N; i++){
        if (c->vehicle[i].startingposition == 'E' || c->vehicle[i].startingposition == 'W')
            c->vehicle[i].color = colorEO;

        if (c->vehicle[i].startingposition == 'N' || c->vehicle[i].startingposition == 'S')
            c->vehicle[i].color = colorNS;
    }
}


// POTENTIALLY BLOCKING
void checkSemaphore (struct cars_t *c, int num_car){

    // It will block the car if it's red and near the semaphore
    if (c->vehicle[num_car].color == red){
        // WEST
        if ((c->vehicle[num_car].xposition <= 420) && (c->vehicle[num_car].xposition > 410) && c->vehicle[num_car].startingposition == 'W') {
            c->vehicle[num_car].blocked = 1;
            sem_wait(&c->vehicle[num_car].macchina);
        }

        // EAST
        if ((c->vehicle[num_car].xposition >= 180) && (c->vehicle[num_car].xposition < 190) && c->vehicle[num_car].startingposition == 'E') {
            c->vehicle[num_car].blocked = 1;
            sem_wait(&c->vehicle[num_car].macchina);
        }

        // NORTH
        if ((c->vehicle[num_car].yposition >= 180) && (c->vehicle[num_car].yposition < 190) && c->vehicle[num_car].startingposition == 'N') {
            c->vehicle[num_car].blocked = 1;
            sem_wait(&c->vehicle[num_car].macchina);
        }

        // SOUTH
        if ((c->vehicle[num_car].yposition <= 420) && (c->vehicle[num_car].yposition > 410) && c->vehicle[num_car].startingposition == 'S') {
            c->vehicle[num_car].blocked = 1;
            sem_wait(&c->vehicle[num_car].macchina);
        }
    }
}


// NEVER BLOCKING
void checkCarsBlocked (int colorEO, int colorNS, struct cars_t *c){

    // Check of the color and if a vehicle is blocked or not
    if (colorEO == green) {
        for (int i = 0; i < N; i++){
            if (c->vehicle[i].blocked == 1 && (c->vehicle[i].startingposition == 'W' || c->vehicle[i].startingposition == 'E')) {
                sem_post(&c->vehicle[i].macchina);
            }
        }
    }

   
    if (colorNS == green){
        for (int i = 0; i < N; i++){
            if (c->vehicle[i].blocked == 1 && (c->vehicle[i].startingposition == 'N' || c->vehicle[i].startingposition == 'S')) {
                sem_post(&c->vehicle[i].macchina);
            }
        }
    }
}





////////////// THREAD ///////////////

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
    // Two array for the color of the semaphores
    int color_EO[2] = {green, red};
    int color_NS[2] = {red, green};

   
    for (;;){
        if (i == 2){
            i = 0;
        }

        EOSemaphore (color_EO[i]);
        NSSemaphore (color_NS[i]);
        changeColor (color_EO[i], color_NS[i], &cars);
        checkCarsBlocked (color_EO[i], color_NS[i], &cars);

        i++;
        sleep(15);
    }
}

void * grafico (void * arg){

    for (;;){
        sleep(1);
        drawGraphics();
        drawLines();
        drawCars(&cars);
    }
}


int main(){

    initGraphics();
    drawGraphics();
    drawLines();

    pthread_t car_thread, semaphore_thread, graphic_thread;
    pthread_attr_t attr;

   
    int id = 0;
    srand(time(NULL));

    pthread_attr_init(&attr);
    initCars(&cars);

    // N thread cars
    for (int i = 0; i < N; i++){
        pthread_create (&car_thread, &attr, macchina, (void *)(__intptr_t)id);
        id++;
    }

    // 1 thread semaphore
    pthread_create (&semaphore_thread, &attr, semaforo, NULL);

    // 1 thread graphics
    pthread_create (&graphic_thread, &attr, grafico, NULL);
   
    install_keyboard();
    int k = 0;
    // The program will close when ESC is clicked
    do{
        if (keypressed()){
            k = readkey() >> 8;
        }

    } while (k != KEY_ESC);
}

