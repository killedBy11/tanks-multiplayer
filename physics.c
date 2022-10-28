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

Projectile *createProjectile(Point *location, float radius, float dragCoefficient, unsigned int mass,
                             unsigned short health) {
    Projectile *p = (Projectile *) malloc(sizeof(Projectile));

    if (NULL == p) {
        return NULL;
    }

    p->base.location = location;
    p->base.sizeCoefficient = radius;
    p->base.dragCoefficient = dragCoefficient;
    p->base.mass = mass;
    p->base.health = health;
    p->base.linearVelocity.i = 0;
    p->base.linearVelocity.j = 0;
    p->base.angularVelocity = 0;
    p->type = PROJECTILE;

    return p;
}

ForceLinear *createForceLinear(Vector *vector) {
    ForceLinear *f = (ForceLinear *) malloc(sizeof(ForceLinear));

    if (NULL == f) {
        return NULL;
    }

    f->vector = vector;
    f->force = LINEAR;

    return f;
}

ForceRotational *createForceRotational(float torque) {
    ForceRotational *f = (ForceRotational *) malloc(sizeof(ForceRotational));

    if (NULL == f) {
        return NULL;
    }

    f->torque = torque;
    f->force = ROTATIONAL;
    return f;
}

void freeTank(Tank **t) {
    freePoint(&(*t)->base.location);
    free(*t);
    *t = NULL;
}

void freeProjectile(Projectile **p) {
    freePoint(&(*p)->base.location);
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
    int computedAngularVelocity = f1->torque + f2->torque;

    ForceRotational *result = createForceRotational(computedAngularVelocity);

    return result;
}

void destroyPhysicalObject(void **object, enum PhysicalObjectType type) {
    switch (type) {
        case TANK:
            freeTank((Tank **) object);
            break;
        case PROJECTILE:
            freeProjectile((Projectile **) object);
            break;
        default:
            break;
    }
}

void applyDamage(void **object, enum PhysicalObjectType type, unsigned short int damage) {
    switch (type) {
        case TANK: {
            Tank **t = (Tank **) object;
            if ((*t)->base.health <= damage) {
                destroyPhysicalObject(object, TANK);
            } else {
                (*t)->base.health -= damage;
            }
            break;
        }
        case PROJECTILE: {
            Projectile **p = (Projectile **) object;
            if ((*p)->base.health <= damage) {
                destroyPhysicalObject(object, PROJECTILE);
            } else {
                (*p)->base.health -= damage;
            }
            break;
        }
        default:
            break;
    }
}

ForceLinear *generateLinearFriction(PhysicalObject *object) {
    Vector *frictionDirection = createVector(
            -1 * AIR_DENSITY * object->sizeCoefficient * (float) object->mass * object->dragCoefficient *
            object->linearVelocity.i *
            object->linearVelocity.i / 2,
            -1 * AIR_DENSITY * object->sizeCoefficient * (float) object->mass * object->dragCoefficient *
            object->linearVelocity.j *
            object->linearVelocity.j / 2);

    if (NULL == frictionDirection) {
        return NULL;
    }

    ForceLinear *result = createForceLinear(frictionDirection);
    return result;
}

ForceRotational *generateRotationalFriction(PhysicalObject *object) {
    ForceRotational *result = createForceRotational(
            -1 * AIR_DENSITY * object->sizeCoefficient * (float) object->mass * object->dragCoefficient *
            object->angularVelocity *
            object->angularVelocity / 2);
    return result;
}

