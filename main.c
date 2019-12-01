#include "graphics.c"
#include "main.h"

void initCars (struct cars_t *c) {
    sem_init (&c->mutex, 0, 1);

    for (int i = 0; i < N; i++){
        // Initializing all the different position that a car can have
        int ypos[8] = {210, 235, 260, 285, 310, 335, 360, 385};
        int xpos[8] = {210, 235, 260, 285, 310, 335, 360, 385};
        int index = rand() % 8;

        // All semaphores initialized to 0
        sem_init (&c->vehicle[i].macchina, 0, 0);
        c->vehicle[i].blocked = 0;

        
        // For west and east initialization of the cars
        // WEST
        if (ypos[index] == 210 || ypos[index] == 235 || ypos[index] == 260 || ypos[index] == 285){
            c->vehicle[i].startingposition = 'W';
            c->vehicle[i].xposition = 590;
            c->vehicle[i].yposition = ypos[index];
        }
        // EAST
        else if (ypos[index] == 310 || ypos[index] == 335 || ypos[index] == 360 || ypos[index] == 385){
            c->vehicle[i].startingposition = 'E';
            c->vehicle[i].xposition = 10;
            c->vehicle[i].yposition = ypos[index];
        }

        

        
        // For north and south initialization of the cars
        // NORTH
        else if (xpos[index] == 210 || xpos[index] == 235 || xpos[index] == 260 || xpos[index] == 285){
            c->vehicle[i].startingposition = 'N';
            c->vehicle[i].xposition = xpos[index];
            c->vehicle[i].yposition = 10;
        }
        // SOUTH
        else if (xpos[index] == 310 || xpos[index] == 335 || xpos[index] == 360 || xpos[index] == 385){
            c->vehicle[i].startingposition = 'S';
            c->vehicle[i].xposition = xpos[index];
            c->vehicle[i].yposition = 500;
        }

        
        // Drawing the car like a circlefill
        circlefill(screen, c->vehicle[i].xposition, c->vehicle[i].yposition, 5, 14);
    }
    // No cars blocked
    c->cars_blocked = 0;
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

// POTENTIALLY BLOCKING (if semaphore color == red -> block)
void checkSemaphore (struct cars_t *c, int num_car){

    // Coming from WEST
    if ((c->vehicle[num_car].xposition <= 420) && (c->vehicle[num_car].xposition > 410) && c->vehicle[num_car].startingposition == 'W') {
        c->cars_blocked++;
        c->vehicle[num_car].blocked = 1;
        sem_wait(&c->vehicle[num_car].macchina);
    }

    
    // Coming from EAST
    if ((c->vehicle[num_car].xposition >= 180) && (c->vehicle[num_car].xposition < 190) && c->vehicle[num_car].startingposition == 'E') {
        c->cars_blocked++;
        c->vehicle[num_car].blocked = 1;
        sem_wait(&c->vehicle[num_car].macchina);
    }

    
    // Coming from NORTH
    if ((c->vehicle[num_car].yposition > 180) && (c->vehicle[num_car].yposition <= 190) && c->vehicle[num_car].startingposition == 'N') {
        c->cars_blocked++;
        c->vehicle[num_car].blocked = 1;
        sem_wait(&c->vehicle[num_car].macchina);
    }

    
    // Coming from SOUTH
    if ((c->vehicle[num_car].yposition <= 420) && (c->vehicle[num_car].yposition > 410) && c->vehicle[num_car].startingposition == 'S') {
        c->cars_blocked++;
        c->vehicle[num_car].blocked = 1;
        sem_wait(&c->vehicle[num_car].macchina);
    }
}

// To check if a car finished its way
void checkEnd (struct cars_t *c, int num_car){

    if (c->vehicle[num_car].xposition < 0) {
        printf("Car %d finished.\n", num_car);
    }
}

// To check if there's some car blocked
void checkCarsBlocked (int color, struct cars_t *c){

    if (color == green && c->cars_blocked > 0) {
        for (int i = 0; i < N; i++){
            if (c->vehicle[i].blocked == 1) {
                sem_post(&c->vehicle[i].macchina);
                c->cars_blocked--;
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
        checkEnd(&cars, num_car);
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

        EastSemaphore (color_EO[i]);
        SouthSemaphore (color_NS[i]);
        WestSemaphore (color_EO[i]);
        NorthSemaphore (color_NS[i]);
        checkCarsBlocked (color_EO[i], &cars);
        checkCarsBlocked (color_NS[i], &cars);

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