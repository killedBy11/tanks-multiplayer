#include "tigr.h"
#include "graphics.h"
#include "physics.h"
#include "controls.h"
#include <time.h>
#include <stdio.h>


int main(int argc, char *argv[]) {

//    Tigr *screen = tigrWindow(1024, 768, "Tanks", 0);
//
//    struct timespec start;
//    clock_gettime(CLOCK_REALTIME, &start);
//
//    Point *location1 = createPoint(100, 700);
//    Point *location2 = createPoint(200, 700);
//    Tank *t1 = createTank(location1, 0, 35, 0.2, 1000, MAX_HEALTH);
//    Tank *t2 = createTank(location2, 0, 35, 0.2, 1000, MAX_HEALTH);
//
//
//    while (!tigrClosed(screen)) {
//        tigrClear(screen, BACKGROUND_COLOR);
//        struct timespec finish;
//        clock_gettime(CLOCK_REALTIME, &finish);
//        float deltaTime = (float) ((double) (finish.tv_sec - start.tv_sec) * 1000 +
//                                   (double) (finish.tv_nsec - start.tv_nsec) / 1000000);
//
//        rotationalForceGenerationCycle(screen, t1, deltaTime);
//        linearForceGenerationCycle(screen, t1, deltaTime);
//
//        updatePosition(&t1->base, deltaTime);
//
//
//        drawTank(screen, t1);
//        drawTank(screen, t2);
//
//        start = finish;
//
//        tigrUpdate(screen);
//    }
//    tigrFree(screen);
    Point *location1 = createPoint(60, 40);
    Point *location2 = createPoint(35, 40);
    Tank *t1 = createTank(location1, 0, 35, 0.2, 1000, MAX_HEALTH);
    Tank *t2 = createTank(location2, 0, 35, 0.2, 1000, MAX_HEALTH);
    printf("%d", checkTanksCollision(t1,t2));
    return 0;
}