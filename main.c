#include "tigr.h"
#include "graphics.h"
#include "physics.h"
#include "controls.h"
#include <time.h>

int main(int argc, char *argv[]) {
    Tigr *screen = tigrWindow(1024, 768, "Tanks", 0);

    struct timespec start;
    clock_gettime(CLOCK_REALTIME, &start);

    Point *location = createPoint(100, 700);
    Tank *t = createTank(location, 0, 35, 0.2, 1000, MAX_HEALTH);

    while (!tigrClosed(screen)) {
        tigrClear(screen, BACKGROUND_COLOR);
        struct timespec finish;
        clock_gettime(CLOCK_REALTIME, &finish);
        float deltaTime = (float) ((double) (finish.tv_sec - start.tv_sec) * 1000 +
                                   (double) (finish.tv_nsec - start.tv_nsec) / 1000000);

        rotationalForceGenerationCycle(screen, t, deltaTime);
        linearForceGenerationCycle(screen, t, deltaTime);

        updatePosition(&t->base, deltaTime);


        drawTank(screen, t);

        start = finish;

        tigrUpdate(screen);
    }
    tigrFree(screen);
    return 0;
}