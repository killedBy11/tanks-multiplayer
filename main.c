#include "tigr.h"
#include "graphics.h"
#include "physics.h"


int main(int argc, char *argv[]) {
    Tigr *screen = tigrWindow(1024, 768, "Tanks", 0);
    while (!tigrClosed(screen))
    {
        tigrClear(screen, BACKGROUND_COLOR);
        Point* location = createPoint(100, 100);
        Tank* t = createTank(location, 0, 35, 1, 1, MAX_HEALTH);
        drawTank(screen, t);
        tigrUpdate(screen);
    }
    tigrFree(screen);
    return 0;
}