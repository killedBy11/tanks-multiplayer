//
// Created by Antoniu Ficard on 27.10.2022.
//

#include <stdlib.h>
#include "physics.h"

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

Tank *
createTank(Point *location, unsigned short heading, float sizeCoefficient, float dragCoefficient, unsigned int mass,
           unsigned short health) {
    Tank *t = (Tank *) malloc(sizeof(Tank));

    if (NULL == t) {
        return NULL;
    }

    t->location = location;
    t->heading = heading;
    t->sizeCoefficient = sizeCoefficient;
    t->dragCoefficient = dragCoefficient;
    t->mass = mass;
    t->health = health;
    t->type = TANK;

    return t;
}

Projectile *createProjectile(Point *location, unsigned short radius, float dragCoefficient, unsigned int mass,
                             unsigned short health) {
    Projectile *p = (Projectile *) malloc(sizeof(Projectile));

    if (NULL == p) {
        return NULL;
    }

    p->location = location;
    p->radius = radius;
    p->dragCoefficient = dragCoefficient;
    p->mass = mass;
    p->health = health;
    p->type = PROJECTILE;

    return p;
}

ForceLinear *createForceLinear(Vector *vector) {
    ForceLinear *f = (ForceLinear *) malloc(sizeof(ForceLinear));

    if (NULL == f) {
        return NULL;
    }

    f->vector = vector;
    f->type = FORCE;
    f->force = LINEAR;

    return f;
}

ForceRotational *createForceRotational(int angularVelocity) {
    ForceRotational *f = (ForceRotational *) malloc(sizeof(ForceRotational));

    if (NULL == f) {
        return NULL;
    }

    f->angularVelocity = angularVelocity;
    f->type = FORCE;
    f->force = ROTATIONAL;

    return f;
}

void freePoint(Point **p) {
    free(*p);
    *p = NULL;
}

void freeVector(Vector **v) {
    free(*v);
    *v = NULL;
}

void freeTank(Tank **t) {
    freePoint(&(*t)->location);
    free(*t);
    *t = NULL;
}

void freeProjectile(Projectile **p) {
    freePoint(&(*p)->location);
    free(*p);
    *p = NULL;
}

void freeForceLinear(ForceLinear **f) {
    freeVector(&(*f)->vector);
    free(*f);
    *f = NULL;
}

void freeForceRotational(ForceRotational **f) {
    free(*f);
    *f = NULL;
}
