//
// Created by Antoniu Ficard on 27.10.2022.
//

#include <stdlib.h>
#include "physics.h"
#include <math.h>
#include <float.h>

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
    register float computedAngularVelocity = f1->torque + f2->torque;

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

int applyForceLinear(PhysicalObject *object, ForceLinear *force, float deltaTime) {
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

int applyForceRotational(PhysicalObject *object, ForceRotational *force, float deltaTime) {
    register float appliedVelocity = force->torque / (float) object->mass * deltaTime;

    object->angularVelocity += appliedVelocity;
    return 0;
}

int updatePosition(PhysicalObject *object, float deltaTime) {
    register Point *newLocation = createPoint(object->location->x + (int) (object->linearVelocity.i * deltaTime),
                                              object->location->y + (int) (object->linearVelocity.j * deltaTime));

    if (NULL == newLocation) {
        return -1;
    }

    freePoint(&object->location);
    object->location = newLocation;

    object->heading = addDegrees((short int) object->heading, (short int) (object->angularVelocity * deltaTime));

    return 0;
}

int computeTankCorners(Tank *t, Point *corners[4]) {
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
    float rotation = t->base.heading * 2 * PI / TOTAL_RADIUS;

    for (int i = 0; i < 4; ++i) {
        Point *aux = rotatePoint(corners[i], rotation);

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

void projectVertices(Point **tankCorners, Vector *axis, float *minimum, float *maximum) {
    *minimum = 999999999;
    *maximum = -999999999;
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
                                         Point **cornersTank1, Point **cornersTank2) {

    //deallocate the memory for minimums and maximums.
    free(minTank1);
    free(maxTank1);
    free(minTank2);
    free(maxTank2);

    //deallocate the memory used for tanks corners.
    for (int i = 0; i < 4; ++i) {
        freePoint(&cornersTank1[i]);
        freePoint(&cornersTank2[i]);
    }
    free(cornersTank1);
    free(cornersTank2);
}

int checkTanksCollision(Tank *tank1, Tank *tank2) {
    if (tank1 == NULL || tank2 == NULL) {
        return -1;
    }

    Point **cornersTank1 = (Point **) malloc(4 * sizeof(Point *));
    Point **cornersTank2 = (Point **) malloc(4 * sizeof(Point *));
    for (int i = 0; i < 4; i++) {
        cornersTank1[i] = NULL;
        cornersTank2[i] = NULL;
    }

    if (computeTankCorners(tank1, cornersTank1) < 0) {
        free(cornersTank1);
        return -2;
    }
    if (computeTankCorners(tank2, cornersTank2) < 0) {
        free(cornersTank2);
        return -2;
    }


    float *minTank1 = (float *) malloc(sizeof(float));
    float *maxTank1 = (float *) malloc(sizeof(float));
    float *minTank2 = (float *) malloc(sizeof(float));
    float *maxTank2 = (float *) malloc(sizeof(float));

    for (int i = 0; i < 4; i++) {
        //loop over tank1 corners
        Point *point1 = cornersTank1[i];
        Point *point2 = cornersTank1[(i + 1) % 4];

        Vector *edgeDirection = createVector((float) (point2->x - point1->x), (float) (point2->y -
                                                                                       point1->y));//edgeDirection from edge represented by point1 point2
        Vector *perpendicularOnEdge = createVector((-1) * edgeDirection->j,
                                                   edgeDirection->i);//perpendicular vector on edge represented by point1 point2

        projectVertices(cornersTank1, perpendicularOnEdge, minTank1, maxTank1);
        projectVertices(cornersTank2, perpendicularOnEdge, minTank2, maxTank2);
        if (*minTank1 >= *maxTank2 || *minTank2 >= *maxTank1) {
            deallocateMemoryUsedInTankCollision(minTank1,maxTank1,minTank2,maxTank2,cornersTank1,cornersTank2);
            return 0;
        }
    }
    for (int i = 0; i < 4; i++) {
        //loop over tank2 corners
        Point *point1 = cornersTank2[i];
        Point *point2 = cornersTank2[(i + 1) % 4];

        Vector *edgeDirection = createVector((float) (point2->x - point1->x), (float) (point2->y -
                                                                                       point2->x));//edgeDirection from edge represented by point1 point2
        Vector *perpendicularOnEdge = createVector((-1) * edgeDirection->j,
                                                   edgeDirection->i);//perpendicular vector on edge represented by point1 point2

        projectVertices(cornersTank1, perpendicularOnEdge, minTank1, maxTank1);
        projectVertices(cornersTank2, perpendicularOnEdge, minTank2, maxTank2);
        if (*minTank1 >= *maxTank2 || *minTank2 >= *maxTank1) {
            deallocateMemoryUsedInTankCollision(minTank1,maxTank1,minTank2,maxTank2,cornersTank1,cornersTank2);
            return 0;
        }
    }

    deallocateMemoryUsedInTankCollision(minTank1,maxTank1,minTank2,maxTank2,cornersTank1,cornersTank2);
    return 1;
}

