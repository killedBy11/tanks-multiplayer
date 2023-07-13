//
// Created by antoniu on 13.07.2023.
//

#include <stdlib.h>

#include "projectile.h"

Projectile *createProjectile(Point_f *location, float radius, float dragCoefficient, integer_kilograms_t mass,
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

void freeProjectile(Projectile **p) {
    freePoint_f(&(*p)->base.location);
    free(*p);
    *p = NULL;
}