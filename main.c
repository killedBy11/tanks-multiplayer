#include "graphics/tigr.h"
#include "graphics/graphics.h"
#include "physics/physics.h"
#include "controls/controls.h"
#include "flags.h"
#include "measurement_units.h"

#include <time.h>
#include <stdlib.h>
#include <string.h>


flag processArgument(char *arg);

int8_t *computeFlags(int argc, char *argv[]);

void game(int8_t *flags);

int main(int argc, char *argv[]) {
    int8_t *flags = computeFlags(argc, argv);
    game(flags);
    return 0;
}

flag processArgument(char *arg) {
    char *argName = strtok(arg, "=");
    char *argValue = strtok(NULL, "=");

    if (NULL == argName) {
        exit(1);
    }

    flag result = {-1, 0};

    if (0 == strcmp(argName, "--display-forces")) {
        int value = atoi(argValue);
        result.flag = DISPLAY_FORCES_FLAG;

        switch (value) {
            case 1: {
                result.value = DISPLAY_ALL_FORCES;
                break;
            }
            case 2: {
                result.value = DISPLAY_FORCES_DECOMPOSED;
                break;
            }
            default: {
                result.value = DISPLAY_NO_FORCES;
                break;
            }
        }
    }

    return result;
}

int8_t *computeFlags(int argc, char *argv[]) {
    int8_t *result = (int8_t *) malloc(sizeof(int8_t) * FLAG_COUNT);

    if (result == NULL) {
        exit(1);
    }

    for (register int i = 0; i < FLAG_COUNT; ++i) {
        result[i] = 0;
    }

    for (register int i = 1; i < argc; ++i) {
        flag f = processArgument(argv[i]);
        if (-1 != f.flag) {
            result[f.flag] = f.value;
        }
    }

    return result;
}

void game(int8_t *flags) {
    Tigr *screen = tigrWindow(1024, 768, "Tanks", 0);

    struct timespec start;
    clock_gettime(CLOCK_REALTIME, &start);

    Point_f *location1 = createPoint_f(100, 700);
    Point_f *location2 = createPoint_f(200, 700);
    Tank *t1 = createTank(location1, 0, 35, 0.2f, 1000, MAX_HEALTH);
    Tank *t2 = createTank(location2, 0, 35, 0.2f, 1000, MAX_HEALTH);


    while (!tigrClosed(screen)) {
        tigrClear(screen, tigrRGB(0x00, 0x00, 0x00));
        struct timespec finish;
        clock_gettime(CLOCK_REALTIME, &finish);
        millisecond_t deltaTime = (millisecond_t) ((double) (finish.tv_sec - start.tv_sec) * 1000 +
                                   (double) (finish.tv_nsec - start.tv_nsec) / 1000000);

        rotationalForceGenerationCycle(screen, t1, deltaTime, flags);
        linearForceGenerationCycle(screen, t1, deltaTime, flags);

        updatePosition(&t1->base, deltaTime);


        drawTank(screen, t1, tigrRGB(0xFF, 0xFF, 0xFF));
        drawTank(screen, t2, tigrRGB(0xFF, 0xFF, 0xFF));

        start = finish;

        tigrUpdate(screen);
    }
    tigrFree(screen);
}