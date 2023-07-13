//
// Created by antoniu on 13.07.2023.
//

#ifndef GRAPHICSTEST_TANK_H
#define GRAPHICSTEST_TANK_H

#include "physics.h"

typedef struct {
    PhysicalObject base;
    enum PhysicalObjectType type;
} Tank;


// allocate space in memory for a Tank object and initialise
Tank *
createTank(Point_f *location, degrees_t heading, float sizeCoefficient, float dragCoefficient,
           integer_kilograms_t mass,
           unsigned short int health);


// deallocate memory for a Tank and the Point within it
// input: gets the address of the pointer that stores the Tank
// output: sets the pointer given as a parameter to NULL
void freeTank(Tank **t);


// calculates the corner points of the Tank object given as a parameter, and allocates new Points in the corners array for
// input: t - Tank *, the object for which the corners must be calculated
//        corners - Point_f* [4], array of 4 Point pointers. The array must contain only NULL, as the pointers will be overwritten by the function
// output: corners as a parameter, pointer array from input
//         return: -1 if there is an error, 0 if calculation was successful
int computeTankCorners_f(Tank *t, Point_f *corners[4]);


// calculates the corner points of the Tank object given as a parameter, and allocates new Points in the corners array for
// input: t - Tank *, the object for which the corners must be calculated
//        corners - Point* [4], array of 4 Point pointers. The array must contain only NULL, as the pointers will be overwritten by the function
// output: corners as a parameter, pointer array from input
//         return: -1 if there is an error, 0 if calculation was successful
int computeTankCorners(Tank *t, Point *corners[4]);


// checks if two tanks are colliding
// input: tank1 - pointer to one tank
//        tank2 - pointer to other tank
// output: returns:  1 if the given tanks are penetrating
//                   0 if the given tanks are NOT penetrating
//                  -1 (error) if at least one of the given tanks is NULL
//                  -2 if encountered error with memory allocation
int checkTanksCollision(Tank *tank1, Tank *tank2);


// gets the angle relative to the tanks forward axis at which the tank other hit tank origin. the tanks must collide before calling this function
// input: origin - pointer to one tank
//        other  - pointer to another tank
// output: returns: 0 <= number < 2pi - the angle of the projection from the origin tank center to the point of collision on its edge, given in radians.
//                  -1 if the tanks are not colliding or the input pointers are invalid
float getTankCollisionAngle(Tank *origin, Tank *other);


// checks whether a projectile hit a tank
// input: tank - pointer to a tank
//        projectile - pointer to a projectile
// output: returns: 1 - if projectile collides with tank
//                  0 - if projectile does not collide with tank
//                  -1 - error with input pointers
//int checkTankProjectileCollision(Tank *tank, Projectile *projectile);

// if the two given tanks are colliding, then the velocity of tank1 is altered so that the kinetic energy transfers on impact from tank2
// input: tank1 - pointer to a tank
//        tank2 - pointer to another tank
// output: alters the velocity of each tank accordingly, modifying the values at the given pointers
//         returns: 0 - if the alteration was done succesfully
//                  -1 - if the tanks are not colliding
//                  -2 - if the pointers are not valid
int transferKineticEnergy(Tank *tank1, Tank *tank2);

#endif //GRAPHICSTEST_TANK_H
