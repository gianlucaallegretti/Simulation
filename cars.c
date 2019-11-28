#include <allegro.h>
#include <stdio.h>
#include <time.h>
// XWIN and YWIN must be the same
#define XWIN 600
#define YWIN 600

// Cars will choose their position in a random lane
// East position
void drawCarsEast(){
    srand(time(NULL));
    int eastPosition[4] = {310, 335, 360, 385};
    int randomIndex = rand() % 4;
    int randomValue = eastPosition[randomIndex];

    circlefill(screen, 5, randomValue, 5, 14);
}

// North position
void drawCarsNorth(){
    srand(time(NULL));
    int eastPosition[4] = {210, 235, 260, 285};
    int randomIndex = rand() % 4;
    int randomValue = eastPosition[randomIndex];

    circlefill(screen, randomValue, 5, 5, 14);
}

// West position
void drawCarsWest(){
    srand(time(NULL));
    int eastPosition[4] = {210, 235, 260, 285};
    int randomIndex = rand() % 4;
    int randomValue = eastPosition[randomIndex];

    circlefill(screen, YWIN-6, randomValue, 5, 14);
}

// South position
void drawCarsSouth(){
    srand(time(NULL));
    int eastPosition[4] = {310, 335, 360, 385};
    int randomIndex = rand() % 4;
    int randomValue = eastPosition[randomIndex];

    circlefill(screen, randomValue, XWIN - 6, 5, 14);
}