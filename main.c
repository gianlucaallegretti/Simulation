#include "main.h"
#include "graphics.c"

// To initialize the struct the first time
void initStruct (struct condivisa *c) {

    sem_init (&c->mutex, 0, 1);
   
    for (int i = 0; i < N; i++){

        // Initializing N/4 cars for each direction
        if (i < N/4){
          
            c->vehicle[i].startingposition = 'N';
            c->vehicle[i].xposition = firstLanes[i];
            c->vehicle[i].yposition = 0;
        }
        else if (i < N/2){

            c->vehicle[i].startingposition = 'E';
            c->vehicle[i].xposition = XWIN;
            c->vehicle[i].yposition =firstLanes[i - N/4];              
        }
        else if (i < (N/4)*3){

            c->vehicle[i].startingposition = 'W';
            c->vehicle[i].xposition = 0;
            c->vehicle[i].yposition = secondLanes[i - N/2];
        }
        else if (i < N){
              
            c->vehicle[i].startingposition = 'S';
            c->vehicle[i].xposition = secondLanes[i - (N/4)*3];
            c->vehicle[i].yposition = YWIN;
        }

        // All semaphores initialized to 0
        sem_init (&c->vehicle[i].macchina, 0, 0);
        // No vehicles blocked at the beginning
        c->vehicle[i].blocked = 0;
        c->vehicle[i].turn = false;
        c->vehicle[i].finished = false;
   
        // Drawing the car like a circlefill
        circlefill(screen, c->vehicle[i].xposition, c->vehicle[i].yposition, dimension_car, yellow);
    }
}


// NEVER BLOCKING
void carStart (struct condivisa *c, int num_car){

    // If the vehicle finished, it will start again
    if (c->vehicle[num_car].finished == true){

        if (num_car < N/4){
             
            c->vehicle[num_car].startingposition = 'N';
            c->vehicle[num_car].xposition = firstLanes[num_car];
            c->vehicle[num_car].yposition = 0;
        }
        else if (num_car < N/2){

            c->vehicle[num_car].startingposition = 'E';
            c->vehicle[num_car].xposition = XWIN;
            c->vehicle[num_car].yposition =firstLanes[num_car - N/4];                 
        }
        else if (num_car < (N/4)*3){
            
            c->vehicle[num_car].startingposition = 'W';
            c->vehicle[num_car].xposition = 0;
            c->vehicle[num_car].yposition = secondLanes[num_car - N/2];
        }
        else if (num_car < N){
                  
            c->vehicle[num_car].startingposition = 'S';
            c->vehicle[num_car].xposition = secondLanes[num_car - (N/4)*3];
            c->vehicle[num_car].yposition = YWIN;
        }

        sem_init (&c->vehicle[num_car].macchina, 0, 0);
        c->vehicle[num_car].blocked = 0;
        c->vehicle[num_car].turn = false;
        c->vehicle[num_car].finished = false;
        
        // Drawing the car like a circlefill
        circlefill(screen, c->vehicle[num_car].xposition, c->vehicle[num_car].yposition, dimension_car, yellow);
    }
}


// NEVER BLOCKING
void carTurn (struct condivisa *c, int num_car){
   
    if (c->vehicle[num_car].turn == false){

        // To change if it's coming from south
        if (c->vehicle[num_car].startingposition == 'S' && c->vehicle[num_car].xposition == 385 && c->vehicle[num_car].yposition == 390){
            c->vehicle[num_car].startingposition = 'W';
            c->vehicle[num_car].turn = true;
        }

        if (c->vehicle[num_car].startingposition == 'S' && c->vehicle[num_car].xposition == 310 && c->vehicle[num_car].yposition == 290){
            c->vehicle[num_car].startingposition = 'E';
            c->vehicle[num_car].turn = true;
        }

        // To change if it's coming from north
        if (c->vehicle[num_car].startingposition == 'N' && c->vehicle[num_car].xposition == 210 && c->vehicle[num_car].yposition == 210){
            c->vehicle[num_car].startingposition = 'E';
            c->vehicle[num_car].turn = true;
        }

        if (c->vehicle[num_car].startingposition == 'N' && c->vehicle[num_car].xposition == 285 && c->vehicle[num_car].yposition == 310){
            c->vehicle[num_car].startingposition = 'W';
            c->vehicle[num_car].turn = true;
        }

        // To change if it's coming from east
        if (c->vehicle[num_car].startingposition == 'E' && c->vehicle[num_car].xposition == 390 && c->vehicle[num_car].yposition == 210){
            c->vehicle[num_car].startingposition = 'S';
            c->vehicle[num_car].turn = true;
        }

        if (c->vehicle[num_car].startingposition == 'E' && c->vehicle[num_car].xposition == 290 && c->vehicle[num_car].yposition == 285){
            c->vehicle[num_car].startingposition = 'N';
            c->vehicle[num_car].turn = true;
        }

        // To change if it's coming from west
        if (c->vehicle[num_car].startingposition == 'W' && c->vehicle[num_car].xposition == 310 && c->vehicle[num_car].yposition == 310){
            c->vehicle[num_car].startingposition = 'S';
            c->vehicle[num_car].turn = true;
        }

        if (c->vehicle[num_car].startingposition == 'W' && c->vehicle[num_car].xposition == 210 && c->vehicle[num_car].yposition == 385){
            c->vehicle[num_car].startingposition = 'N';
            c->vehicle[num_car].turn = true;
        }
   }
}


// NEVER BLOCKING
void carMove(struct condivisa *c, int num_car){

    // Setting new position of the car
    // WEST
    if (c->vehicle[num_car].startingposition == 'W')
        c->vehicle[num_car].xposition += 10;

    // EAST
    else if (c->vehicle[num_car].startingposition == 'E')
        c->vehicle[num_car].xposition -= 10;

    // NORTH
    else if (c->vehicle[num_car].startingposition == 'N')
        c->vehicle[num_car].yposition += 10;

    // SOUTH
    else if (c->vehicle[num_car].startingposition == 'S')
        c->vehicle[num_car].yposition -= 10;
}


// POTENTIALLY BLOCKING
void checkSemaphore (struct condivisa *c, int num_car){

    sem_wait(&c->mutex);
    // It will block the car if it's red and near the semaphore
    if (c->colorSemaphoreEO == red && (c->vehicle[num_car].startingposition == 'W' || c->vehicle[num_car].startingposition == 'E')){
        sem_post(&c->mutex);

        // WEST
        if ((c->vehicle[num_car].xposition <= (XWIN/3)*2 + 20) && (c->vehicle[num_car].xposition > (XWIN/3)*2 + 10) && c->vehicle[num_car].startingposition == 'E') {
            c->vehicle[num_car].blocked = 1;
            sem_wait(&c->vehicle[num_car].macchina);
        }

        // EAST
        if ((c->vehicle[num_car].xposition >= XWIN/3 - 20) && (c->vehicle[num_car].xposition < XWIN/3 - 10) && c->vehicle[num_car].startingposition == 'W') {
            c->vehicle[num_car].blocked = 1;
            sem_wait(&c->vehicle[num_car].macchina);
        }
    }
    else
        sem_post(&c->mutex);

   
    sem_wait(&c->mutex);
    if (c->colorSemaphoreNS == red && (c->vehicle[num_car].startingposition == 'N' || c->vehicle[num_car].startingposition == 'S')){
        sem_post(&c->mutex);

        // NORTH
        if ((c->vehicle[num_car].yposition >= YWIN/3 - 20) && (c->vehicle[num_car].yposition < YWIN/3 - 10) && c->vehicle[num_car].startingposition == 'N') {
            c->vehicle[num_car].blocked = 1;
            sem_wait(&c->vehicle[num_car].macchina);
        }

        // SOUTH
        if ((c->vehicle[num_car].yposition <= (YWIN/3)*2 + 20) && (c->vehicle[num_car].yposition > (YWIN/3)*2 + 10) && c->vehicle[num_car].startingposition == 'S') {
            c->vehicle[num_car].blocked = 1;
            sem_wait(&c->vehicle[num_car].macchina);
        }
    }
    else
        sem_post(&c->mutex);
}


// NEVER BLOCKING
void checkCarsBlocked (struct condivisa *c){

    sem_wait(&c->mutex);
    // Check of the color and if a vehicle is blocked or not
    if (c->colorSemaphoreEO == green) {
        sem_post(&c->mutex);

        
        for (int i = 0; i < N; i++){
            if (c->vehicle[i].blocked == 1 && (c->vehicle[i].startingposition == 'W' || c->vehicle[i].startingposition == 'E')) {
                sem_post(&c->vehicle[i].macchina);
            }
        }
    }
    else
        sem_post(&c->mutex);

    sem_wait(&c->mutex);
    if (c->colorSemaphoreNS == green){
        sem_post(&c->mutex);

        for (int i = 0; i < N; i++){
            if (c->vehicle[i].blocked == 1 && (c->vehicle[i].startingposition == 'N' || c->vehicle[i].startingposition == 'S')) {
                sem_post(&c->vehicle[i].macchina);
            }
        }
    }
    else
        sem_post(&c->mutex);
}


// NEVER BLOCKING
void carFinish (struct condivisa *c, int num_car){

    // If it doesn't finish, it will check the position
    if (c->vehicle[num_car].finished == false) {

        if (c->vehicle[num_car].xposition >= XWIN)
            c->vehicle[num_car].finished = true;
    
        if (c->vehicle[num_car].xposition <= 0)
            c->vehicle[num_car].finished = true;
   
        if (c->vehicle[num_car].yposition >= YWIN)
            c->vehicle[num_car].finished = true;

        if (c->vehicle[num_car].yposition <= 0)
            c->vehicle[num_car].finished = true;
    }
}







////////////// THREAD ///////////////

void *macchina (void *arg){

    int num_car;
    num_car = (intptr_t) arg;

    for (;;){
        usleep(500000);
        carStart(&cond, num_car);
        carTurn(&cond, num_car);
        carMove(&cond, num_car);
        checkSemaphore(&cond, num_car);
        checkCarsBlocked(&cond);
        carFinish(&cond, num_car);
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
        changeColor (color_EO[i], color_NS[i], &cond);

        i++;
        sleep(20);
    }
}


void * grafico (void * arg){

    for (;;){
        sleep(1);
        drawGraphics();
        drawLines();
        drawCars(&cond);
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
    initStruct(&cond);

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