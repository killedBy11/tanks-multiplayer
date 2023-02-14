//
// Created by Antoniu Ficard on 27.10.2022.
//

#include <stdlib.h>
#include "graphics.h"
#include "geometry.h"
#include "tigr.h"

int drawTank(Tigr *bmp, Tank *t, TPixel color) {
    if (NULL == t) {
        return -1;
    }

    Point *corners[4] = {NULL, NULL, NULL, NULL};
    Point *nozzle = NULL;

    int x, y;
    // compute nozzle tip coordinates

    x = 0;
    y = -(int) (1.5 * t->base.sizeCoefficient);

    nozzle = createPoint(x, y);

    if (NULL == nozzle) {
        return -1;
    }

    // rotate the points according to the heading
    float rotation = (float) (t->base.heading * 2 * PI / TOTAL_RADIUS);

    Point *aux = rotatePoint(nozzle, rotation);

    if (NULL == aux) {
        freePoint(&nozzle);
        return -1;
    }

    freePoint(&nozzle);
    nozzle = aux;
    nozzle->x += (int) t->base.location->x;
    nozzle->y += (int) t->base.location->y;

    if (0 > computeTankCorners(t, corners)) {
        freePoint(&nozzle);
        return -1;
    }

    // draw lines that make up the tank
    tigrLine(bmp, (int) t->base.location->x, (int) t->base.location->y, nozzle->x, nozzle->y, color);
    tigrLine(bmp, corners[3]->x, corners[3]->y, corners[0]->x, corners[0]->y, color);
    for (int i = 0; i < 3; ++i) {
        tigrLine(bmp, corners[i]->x, corners[i]->y, corners[i + 1]->x, corners[i + 1]->y, color);
    }

    // clean up memory
    freePoint(&nozzle);

    for (int i = 0; i < 4; ++i) {
        freePoint(&corners[i]);
    }
    return 0;
}

int drawProjectile(Tigr *bmp, Projectile *p, TPixel color) {
    if (NULL == p) {
        return -1;
    }

    tigrCircle(bmp, (int) p->base.location->x, (int) p->base.location->y, p->base.sizeCoefficient, color);
    return 0;
}

int drawVector(Tigr *bmp, Vector *v, Point *anchor, TPixel color) {
    if (NULL == v || NULL == anchor) {
        return -1;
    }

    tigrLine(bmp, anchor->x, anchor->y, anchor->x + (int) (v->i * 100), anchor->y + (int) (v->j * 100),
             color);
    return 0;
}
