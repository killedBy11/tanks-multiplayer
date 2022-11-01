//
// Created by Antoniu Ficard on 27.10.2022.
//

#include <stdlib.h>
#include <math.h>
#include "graphics.h"
#include "geometry.h"
#include "tigr.h"

int computeTankCorners(Tank* t, Point* corners[4]) {
    // compute corner coordinates
    int x;
    int y;

    const int signX[] = {-1, 1, 1, -1};
    const int signY[] = {-1, -1, 1, 1};
    for (int i = 0; i < 4; ++i) {
        x = (int)(sin(TANK_ASPECT_RATIO * PI / TOTAL_RADIUS) * t->base.sizeCoefficient * signX[i]);
        y = (int)(cos(TANK_ASPECT_RATIO * PI / TOTAL_RADIUS) * t->base.sizeCoefficient * signY[i]);

        corners[i] = createPoint(x, y);

        if (NULL == corners[i]) {
            for (int j = 0; j < i; ++j) {
                freePoint(&corners[j]);
            }

            return -1;
        }
    }

    // rotate the points according to the heading
    float rotation = t->base.heading * 2 * PI / TOTAL_RADIUS;

    for (int i = 0; i < 4; ++i) {
        Point* aux = rotatePoint(corners[i], rotation);

        if (NULL == aux) {
            for (int i = 0; i < 4; ++i) {
                freePoint(&corners[i]);
            }

            return -1;
        }

        freePoint(&corners[i]);
        corners[i] = aux;
        corners[i]->x += t->base.location->x;
        corners[i]->y += t->base.location->y;
    }

    return 0;
}

int drawTank(Tigr *bmp, Tank* t) {
    Point* corners[4] = {NULL, NULL, NULL, NULL};
    Point* nozzle = NULL;

    int x, y;
    // compute nozzle tip coordinates

    x = 0;
    y = -(int)(1.5 * t->base.sizeCoefficient);

    nozzle = createPoint(x, y);

    if (NULL == nozzle) {
        return -1;
    }

    // rotate the points according to the heading
    float rotation = t->base.heading * 2 * PI / TOTAL_RADIUS;

    Point* aux = rotatePoint(nozzle, rotation);

    if (NULL == aux) {
        freePoint(&nozzle);
        return -1;
    }

    freePoint(&nozzle);
    nozzle = aux;
    nozzle->x += t->base.location->x;
    nozzle->y += t->base.location->y;

    if(0 > computeTankCorners(t, corners)) {
        freePoint(&nozzle);
        return -1;
    }

    // draw lines that make up the tank
    tigrLine(bmp, t->base.location->x, t->base.location->y, nozzle->x, nozzle->y, LINE_COLOR);
    tigrLine(bmp, corners[3]->x, corners[3]->y, corners[0]->x, corners[0]->y, LINE_COLOR);
    for (int i = 0; i < 3; ++i) {
        tigrLine(bmp, corners[i]->x, corners[i]->y, corners[i + 1]->x, corners[i + 1]->y, LINE_COLOR);
    }

    // clean up memory
    freePoint(&nozzle);

    for (int i = 0; i < 4; ++i) {
        freePoint(&corners[i]);
    }
    return 0;
}

int drawProjectile(Tigr *bmp, Projectile* p) {
    return -1;
}