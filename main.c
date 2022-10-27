#include "tigr.h"


int main(int argc, char *argv[]) {
    Tigr *screen = tigrWindow(320, 240, "Tanks", 0);
    while (!tigrClosed(screen))
    {
        tigrClear(screen, tigrRGB(0x00, 0x00, 0x00));
        tigrUpdate(screen);
    }
    tigrFree(screen);
    return 0;
}