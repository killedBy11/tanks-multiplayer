//
// Created by Antoniu Ficard on 27.10.2022.
//

#include <stdlib.h>
#include "physics.h"

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

ForceLinear *addForceLinear(ForceLinear *f1, ForceLinear *f2) {
    Vector *computedVector = addVector(f1->vector, f2->vector);

    ForceLinear *result = createForceLinear(computedVector);

    return result;
}

ForceRotational *addForceRotational(ForceRotational *f1, ForceRotational *f2) {
    int computedAngularVelocity = f1->angularVelocity + f2->angularVelocity;

    ForceRotational *result = createForceRotational(computedAngularVelocity);

    return result;
}

