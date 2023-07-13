//
// Created by antoniu on 13.07.2023.
//
#include <stdlib.h>

#include "physical_object_damage.h"


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

int applyDamage(void **object, enum PhysicalObjectType type, percentage_t damage) {
    if (NULL == object || NULL == *object) {
        return -1;
    }

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
    return 0;
}