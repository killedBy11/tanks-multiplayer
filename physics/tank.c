//
// Created by antoniu on 13.07.2023.
//

#include <stdlib.h>
#include <math.h>
#include <float.h>

#include "../measurement_units.h"
#include "tank.h"

Tank *
createTank(Point_f *location, degrees_t heading, float sizeCoefficient, float dragCoefficient, integer_kilograms_t mass,
           unsigned short health) {
    Tank *t = (Tank *) malloc(sizeof(Tank));

    if (NULL == t) {
        return NULL;
    }

    t->base.location = location;
    t->base.heading = heading;
    t->base.sizeCoefficient = sizeCoefficient;
    t->base.dragCoefficient = dragCoefficient;
    t->base.mass = mass;
    t->base.health = health;
    t->base.linearVelocity.i = 0;
    t->base.linearVelocity.j = 0;
    t->base.angularVelocity = 0;
    t->type = TANK;

    return t;
}

void freeTank(Tank **t) {
    freePoint_f(&(*t)->base.location);
    free(*t);
    *t = NULL;
}

int computeTankCorners_f(Tank *t, Point_f *corners[4]) {
    // input validation
    for (int i = 0; i < 4; ++i) {
        if (corners[i] != NULL) {
            return -1;
        }
    }

    // compute corner coordinates
    register float x;
    register float y;

    const int signX[] = {-1, 1, 1, -1};
    const int signY[] = {-1, -1, 1, 1};
    for (int i = 0; i < 4; ++i) {
        x = (float) (sin(TANK_ASPECT_RATIO * PI / TOTAL_RADIUS) * t->base.sizeCoefficient * signX[i]);
        y = (float) (cos(TANK_ASPECT_RATIO * PI / TOTAL_RADIUS) * t->base.sizeCoefficient * signY[i]);

        corners[i] = createPoint_f(x, y);

        if (NULL == corners[i]) {
            for (int j = 0; j < i; ++j) {
                freePoint_f(&corners[j]);
            }

            return -1;
        }
    }

    // rotate the points according to the heading
    radians_t rotation = degreesToRadians(t->base.heading);

    for (int i = 0; i < 4; ++i) {
        Point_f *aux = rotatePoint_f(corners[i], rotation);

        if (NULL == aux) {
            for (int j = 0; j < 4; ++j) {
                freePoint_f(&corners[j]);
            }

            return -1;
        }

        freePoint_f(&corners[i]);
        corners[i] = aux;
        corners[i]->x += t->base.location->x;
        corners[i]->y += t->base.location->y;
    }

    return 0;
}

void projectVertices(Point_f **tankCorners, Vector *axis, float *minimum, float *maximum) {
    *minimum = FLT_MAX;
    *maximum = FLT_MIN;
    for (int i = 0; i < 4; i++) {
        Vector pointVector;
        pointVector.i = tankCorners[i]->x;
        pointVector.j = tankCorners[i]->y;
        float projection = getDotProduct(&pointVector, axis);
        if (projection < *minimum)
            *minimum = projection;
        if (projection > *maximum)
            *maximum = projection;
    }
}

void deallocateMemoryUsedInTankCollision(float *minTank1, float *maxTank1, float *minTank2, float *maxTank2,
                                         Point_f **cornersTank1, Point_f **cornersTank2) {

    //deallocate the memory for minimums and maximums.
    free(minTank1);
    free(maxTank1);
    free(minTank2);
    free(maxTank2);

    //deallocate the memory used for tanks corners.
    for (int i = 0; i < 4; ++i) {
        freePoint_f(&cornersTank1[i]);
        freePoint_f(&cornersTank2[i]);
    }
    free(cornersTank1);
    free(cornersTank2);
}

int checkTanksCollision(Tank *tank1, Tank *tank2) {
    if (tank1 == NULL || tank2 == NULL) {
        return -1;
    }

    // check if distance is too great, no purpose in trying to check for collision
    float distanceBetweenTanks = distancef(tank1->base.location, tank2->base.location);
    if (distanceBetweenTanks > tank1->base.sizeCoefficient + tank2->base.sizeCoefficient) {
        return 0;
    }

    Point_f **cornersTank1 = (Point_f **) malloc(4 * sizeof(Point *));
    Point_f **cornersTank2 = (Point_f **) malloc(4 * sizeof(Point *));
    for (int i = 0; i < 4; i++) {
        cornersTank1[i] = NULL;
        cornersTank2[i] = NULL;
    }

    if (computeTankCorners_f(tank1, cornersTank1) < 0) {
        free(cornersTank1);
        return -2;
    }
    if (computeTankCorners_f(tank2, cornersTank2) < 0) {
        free(cornersTank2);
        return -2;
    }


    float *minTank1 = (float *) malloc(sizeof(float));
    float *maxTank1 = (float *) malloc(sizeof(float));
    float *minTank2 = (float *) malloc(sizeof(float));
    float *maxTank2 = (float *) malloc(sizeof(float));

    for (int i = 0; i < 4; i++) {
        //loop over tank1 corners
        Point_f *point1 = cornersTank1[i];
        Point_f *point2 = cornersTank1[(i + 1) % 4];

        Vector *edgeDirection = createVector((float) (point2->x - point1->x), (float) (point2->y -
                                                                                       point1->y));//edgeDirection from edge represented by point1 point2
        Vector *perpendicularOnEdge = createVector((-1) * edgeDirection->j,
                                                   edgeDirection->i);//perpendicular vector on edge represented by point1 point2

        projectVertices(cornersTank1, perpendicularOnEdge, minTank1, maxTank1);
        projectVertices(cornersTank2, perpendicularOnEdge, minTank2, maxTank2);
        if (*minTank1 >= *maxTank2 || *minTank2 >= *maxTank1) {
            deallocateMemoryUsedInTankCollision(minTank1, maxTank1, minTank2, maxTank2, cornersTank1, cornersTank2);
            return 0;
        }
    }
    for (int i = 0; i < 4; i++) {
        //loop over tank2 corners
        Point_f *point1 = cornersTank2[i];
        Point_f *point2 = cornersTank2[(i + 1) % 4];

        Vector *edgeDirection = createVector((float) (point2->x - point1->x), (float) (point2->y -
                                                                                       point2->x));//edgeDirection from edge represented by point1 point2
        Vector *perpendicularOnEdge = createVector((-1) * edgeDirection->j,
                                                   edgeDirection->i);//perpendicular vector on edge represented by point1 point2

        projectVertices(cornersTank1, perpendicularOnEdge, minTank1, maxTank1);
        projectVertices(cornersTank2, perpendicularOnEdge, minTank2, maxTank2);
        if (*minTank1 >= *maxTank2 || *minTank2 >= *maxTank1) {
            deallocateMemoryUsedInTankCollision(minTank1, maxTank1, minTank2, maxTank2, cornersTank1, cornersTank2);
            return 0;
        }
    }

    deallocateMemoryUsedInTankCollision(minTank1, maxTank1, minTank2, maxTank2, cornersTank1, cornersTank2);
    return 1;
}

int computeTankCorners(Tank *t, Point **corners) {
    // input validation
    for (int i = 0; i < 4; ++i) {
        if (corners[i] != NULL) {
            return -1;
        }
    }

    // compute corner coordinates
    register int x;
    register int y;

    const int signX[] = {-1, 1, 1, -1};
    const int signY[] = {-1, -1, 1, 1};
    for (int i = 0; i < 4; ++i) {
        x = (int) (sin(TANK_ASPECT_RATIO * PI / TOTAL_RADIUS) * t->base.sizeCoefficient * signX[i]);
        y = (int) (cos(TANK_ASPECT_RATIO * PI / TOTAL_RADIUS) * t->base.sizeCoefficient * signY[i]);

        corners[i] = createPoint(x, y);

        if (NULL == corners[i]) {
            for (int j = 0; j < i; ++j) {
                freePoint(&corners[j]);
            }

            return -1;
        }
    }

    // rotate the points according to the heading
    float rotation = (float) (t->base.heading * 2 * PI / TOTAL_RADIUS);

    for (int i = 0; i < 4; ++i) {
        Point *aux = rotatePoint(corners[i], rotation);

        if (NULL == aux) {
            for (int j = 0; j < 4; ++j) {
                freePoint(&corners[j]);
            }

            return -1;
        }

        freePoint(&corners[i]);
        corners[i] = aux;
        corners[i]->x += (int) t->base.location->x;
        corners[i]->y += (int) t->base.location->y;
    }

    return 0;
}