//
// Created by Antoniu Ficard on 27.10.2022.
//

#include <stdlib.h>
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

Vector *createVector(int i, int j) {
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
    int computedVersorI = v1->i + v2->i;
    int computedVersorJ = v1->j + v2->j;

    Vector *result = createVector(computedVersorI, computedVersorJ);

    return result;
}