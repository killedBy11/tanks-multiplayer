//
// Created by Antoniu Ficard on 27.10.2022.
//

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "geometry.h"

Point *createPoint(int x, int y) {
    Point *p = (Point *) malloc(sizeof(Point));

    if (NULL == p) {
        return NULL;
    }

    p->x = x;
    p->y = y;
    p->type = POINT;

    return p;
}

Vector *createVector(float i, float j) {
    Vector *v = (Vector *) malloc(sizeof(Vector));

    if (NULL == v) {
        return NULL;
    }

    v->i = i;
    v->j = j;
    v->type = VECTOR;

    return v;
}

void freePoint(Point **p) {
    free(*p);
    *p = NULL;
}

void freeVector(Vector **v) {
    free(*v);
    *v = NULL;
}

Vector *addVector(Vector *v1, Vector *v2) {
    float computedVersorI = v1->i + v2->i;
    float computedVersorJ = v1->j + v2->j;

    Vector *result = createVector(computedVersorI, computedVersorJ);

    return result;
}

Point *rotatePoint(Point *p, float radians) {
    float sine = sinf(radians);
    float cosine = cosf(radians);

    int newPointX = (int) roundf(cosine * p->x - sine * p->y);
    int newPointY = (int) roundf(sine * p->x + cosine * p->y);

    return createPoint(newPointX, newPointY);
}


float absoluteValue(float x) {
    if (x < 0) {
        return -x;
    }
    return x;
}

float degreesToRadians(unsigned short int angle) {
    return ((float) angle * (float) PI) / 180;
}

Vector *createVectorByAngle(float angle, float value) {
    register float i = sinf(angle) * value;
    register float j = cosf(angle) * value;

    return createVector(i, -j);
}

unsigned short int addDegrees(short int angle1, short int angle2) {
    register int unprocessedResult = (int) angle1 + (int) angle2;

    if (unprocessedResult >= 0 && unprocessedResult < TOTAL_RADIUS) {
        return (unsigned short int) unprocessedResult;
    }

    while (unprocessedResult >= 360) {
        unprocessedResult -= 360;
    }

    while (unprocessedResult < 0) {
        unprocessedResult += 360;
    }

    return (unsigned short int) unprocessedResult;
}
