//
// Created by antoniu on 13.07.2023.
//

#ifndef GRAPHICSTEST_PROJECTILE_H
#define GRAPHICSTEST_PROJECTILE_H

#include "physics.h"

typedef struct {
    PhysicalObject base;
    enum PhysicalObjectType type;
} Projectile;

// allocate space in memory for a Projectile object and initialise
Projectile *createProjectile(Point_f *location, float radius, float dragCoefficient, unsigned int mass,
                             unsigned short int health);


// deallocate memory for a Projectile and the Point within it
// input: gets the address of the pointer that stores the Projectile
// output: sets the pointer given as a parameter to NULL
void freeProjectile(Projectile **p);

#endif //GRAPHICSTEST_PROJECTILE_H
