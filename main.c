#include "tigr.h"
#include "graphics.h"
#include "physics.h"
#include <time.h>


int main(int argc, char *argv[]) {
    Tigr *screen = tigrWindow(1024, 768, "Tanks", 0);
    struct timespec now;
    clock_gettime(CLOCK_REALTIME, &now);
    while (!tigrClosed(screen))
    {
        tigrClear(screen, BACKGROUND_COLOR);
        Point* location = createPoint(100, 100);
        Tank* t = createTank(location, 0, 35, 1, 1, MAX_HEALTH);
        drawTank(screen, t);

        freeTank(&t);

        location = createPoint(200, 100);

        Projectile* p = createProjectile(location, 2, 1, 1, MAX_HEALTH);

        drawProjectile(screen, p);

        freeProjectile(&p);
        tigrUpdate(screen);
    }
    tigrFree(screen);
    return 0;
}