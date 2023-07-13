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

Point *rotatePoint(Point *p, radians_t radians) {
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

radians_t degreesToRadians(degrees_t angle) {
    return ((float) angle * 2 * (float) PI) / TOTAL_RADIUS;
}

Vector *createVectorByAngle(radians_t angle, float value) {
    register float i = sinf(angle) * value;
    register float j = cosf(angle) * value;

    return createVector(i, -j);
}

degrees_t addDegrees(degrees_t angle1, degrees_t angle2) {
    register int unprocessedResult = (int) angle1 + (int) angle2;

    if (unprocessedResult >= 0 && unprocessedResult < TOTAL_RADIUS) {
        return (degrees_t) unprocessedResult;
    }

    while (unprocessedResult >= 360) {
        unprocessedResult -= 360;
    }

    while (unprocessedResult < 0) {
        unprocessedResult += 360;
    }

    return (degrees_t) unprocessedResult;
}

float getDotProduct(Vector *v1, Vector *v2) {
    return v1->i * v2->i + v1->j * v2->j;
}

float distance(Point *point1, Point *point2) {
    if (NULL == point1 || NULL == point2) {
        return -1;
    }

    return (float) sqrt(
            (point1->x - point2->x) * (point1->x - point2->x) + (point1->y - point2->y) * (point1->y - point2->y));
}

Point_f *createPoint_f(float x, float y) {
    Point_f *p = (Point_f *) malloc(sizeof(Point_f));
    if (NULL == p) {
        return NULL;
    }

    p->x = x;
    p->y = y;
    p->type = POINT_F;

    return (Point_f *) p;
}

void freePoint_f(Point_f **p) {
    free(*p);
    *p = NULL;
}

Point_f *createPoint_fFromPoint(Point point) {
    Point_f *p = (Point_f *) (Point *) malloc(sizeof(Point_f));
    if (NULL == p) {
        return NULL;
    }

    p->x = (float) point.x;
    p->y = (float) point.y;
    p->type = POINT_F;

    return (Point_f *) p;
}

Point_f *rotatePoint_f(Point_f *p, radians_t radians) {
    float sine = sinf(radians);
    float cosine = cosf(radians);

    float newPointX = cosine * p->x - sine * p->y;
    float newPointY = sine * p->x + cosine * p->y;

    return createPoint_f(newPointX, newPointY);
}

float distancef(Point_f *point1, Point_f *point2) {
    if (NULL == point1 || NULL == point2) {
        return -1;
    }

    return (float) sqrtf(
            (point1->x - point2->x) * (point1->x - point2->x) + (point1->y - point2->y) * (point1->y - point2->y));
}

Point *createPointFromPoint_f(Point_f point) {
    Point *p = (Point *) malloc(sizeof(Point));
    if (NULL == p) {
        return NULL;
    }

    p->x = (int) point.x;
    p->y = (int) point.y;

    return (Point *) p;
}
