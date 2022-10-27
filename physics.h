//
// Created by Antoniu Ficard on 27.10.2022.
//

#ifndef GRAPHICSTEST_PHYSICS_H
#define GRAPHICSTEST_PHYSICS_H

#include "tigr.h"
#include "geometry.h"

#define MAX_HEALTH 100
#define MIN_HEALTH 0

typedef enum {
    TANK, PROJECTILE, FORCE
} ObjectType;

typedef enum {
    ROTATIONAL, LINEAR
} ForceType;

typedef struct {
    Point *location;
    unsigned short int heading;
    float sizeCoefficient;
    float dragCoefficient;
    unsigned int mass;
    unsigned short int health;
    ObjectType type;
} Tank;

typedef struct {
    Point *location;
    unsigned short int radius;
    float dragCoefficient;
    unsigned int mass;
    unsigned short int health;
    ObjectType type;
} Projectile;

typedef struct {
    Vector *vector;
    ObjectType type;
    ForceType force;
} ForceLinear;

typedef struct {
    int angularVelocity;
    ObjectType type;
    ForceType force;
} ForceRotational;

/// Functions

// constructors for structs defined above

// allocate space in memory for a Tank object and initialise
Tank *
createTank(Point *location, unsigned short int heading, float sizeCoefficient, float dragCoefficient, unsigned int mass,
           unsigned short int health);

// allocate space in memory for a Projectile object and initialise
Projectile *createProjectile(Point *location, unsigned short radius, float dragCoefficient, unsigned int mass,
                             unsigned short int health);

// allocate space in memory for a ForceLinear object and initialise
ForceLinear *createForceLinear(Vector *vector);

// allocate space in memory for a ForceRotational object and initialise
ForceRotational *createForceRotational(int angularVelocity);

// destructors that go recursively for the structs defined above

// deallocate memory for a Tank and the Point within it
// input: gets the address of the pointer that stores the Tank
// output: sets the pointer given as a parameter to NULL
void freeTank(Tank **t);

// deallocate memory for a Projectile and the Point within it
// input: gets the address of the pointer that stores the Projectile
// output: sets the pointer given as a parameter to NULL
void freeProjectile(Projectile **p);

// deallocate memory for a ForceLinear and the Vector within it
// input: gets the address of the pointer that stores the ForceLinear
// output: sets the pointer given as a parameter to NULL
void freeForceLinear(ForceLinear **f);

// deallocate memory for a ForceRotational
// input: gets the address of the pointer that stores the ForceRotational
// output: sets the pointer given as a parameter to NULL
void freeForceRotational(ForceRotational **f);

// functions that compute forces

// add 2 linear forces together and return a pointer to the resulting force, newly allocated
ForceLinear *addForceLinear(ForceLinear *f1, ForceLinear *f2);

// add 2 rotational forces together and return a pointer to the resulting force, newly allocated
ForceRotational *addForceRotational(ForceRotational *f1, ForceRotational *f2);

#endif //GRAPHICSTEST_PHYSICS_H
