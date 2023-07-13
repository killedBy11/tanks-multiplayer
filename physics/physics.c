//
// Created by Antoniu Ficard on 27.10.2022.
//

#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <stdio.h>

#include "physics.h"

ForceLinear *createForceLinear(Vector *vector) {
    ForceLinear *f = (ForceLinear *) malloc(sizeof(ForceLinear));

    if (NULL == f) {
        return NULL;
    }

    f->vector = vector;
    f->force = LINEAR;

    return f;
}

ForceRotational *createForceRotational(kilonewton_meters_t torque) {
    ForceRotational *f = (ForceRotational *) malloc(sizeof(ForceRotational));

    if (NULL == f) {
        return NULL;
    }

    f->torque = torque;
    f->force = ROTATIONAL;
    return f;
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
    register float computedAngularVelocity = f1->torque + f2->torque;

    ForceRotational *result = createForceRotational(computedAngularVelocity);

    return result;
}

ForceLinear *generateLinearFriction(PhysicalObject *object) {
    Vector *frictionDirection = createVector(
            -1 * AIR_DENSITY * object->sizeCoefficient / 100 * (float) object->mass * object->dragCoefficient *
            absoluteValue(object->linearVelocity.i) *
            object->linearVelocity.i / 2,
            -1 * AIR_DENSITY * object->sizeCoefficient / 100 * (float) object->mass * object->dragCoefficient *
            absoluteValue(object->linearVelocity.j) *
            object->linearVelocity.j / 2);

    if (NULL == frictionDirection) {
        return NULL;
    }

    ForceLinear *result = createForceLinear(frictionDirection);
    return result;
}

ForceRotational *generateRotationalFriction(PhysicalObject *object) {
    register ForceRotational *result = createForceRotational(
            -1 * AIR_DENSITY * object->sizeCoefficient / 100 * (float) object->mass * object->dragCoefficient *
            absoluteValue(object->angularVelocity) *
            object->angularVelocity / 2);
    return result;
}

int applyForceLinear(PhysicalObject *object, ForceLinear *force, millisecond_t deltaTime) {
    Vector *appliedVelocity = createVector(force->vector->i / (float) object->mass * deltaTime,
                                           force->vector->j / (float) object->mass * deltaTime);

    if (NULL == appliedVelocity) {
        return -1;
    }

    Vector *newVelocity = addVector(&object->linearVelocity, appliedVelocity);

    freeVector(&appliedVelocity);

    if (NULL == newVelocity) {
        return -1;
    }

    object->linearVelocity = *newVelocity;
    freeVector(&newVelocity);

    return 0;
}

int applyForceRotational(PhysicalObject *object, ForceRotational *force, millisecond_t deltaTime) {
    register float appliedVelocity = force->torque / (float) object->mass * deltaTime;

    object->angularVelocity += appliedVelocity;
    return 0;
}

int updatePosition(PhysicalObject *object, millisecond_t deltaTime) {
    register Point_f *newLocation = createPoint_f(object->location->x + object->linearVelocity.i * deltaTime,
                                                  object->location->y + object->linearVelocity.j * deltaTime);

    if (NULL == newLocation) {
        return -1;
    }

    freePoint_f(&object->location);
    object->location = newLocation;

    object->heading = addDegrees((short int) object->heading, (short int) (object->angularVelocity * deltaTime));

    return 0;
}

