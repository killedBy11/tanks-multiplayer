//
// Created by antoniu on 13.07.2023.
//

#ifndef GRAPHICSTEST_PHYSICAL_OBJECT_DAMAGE_H
#define GRAPHICSTEST_PHYSICAL_OBJECT_DAMAGE_H

#include "physics.h"
#include "tank.h"
#include "projectile.h"
#include "../measurement_units.h"

// apply damage to a physical object and subtract the damage from the health of the physical object or destroy if the damage is too high
int applyDamage(void **object, enum PhysicalObjectType type, percentage_t damage);

#endif //GRAPHICSTEST_PHYSICAL_OBJECT_DAMAGE_H
