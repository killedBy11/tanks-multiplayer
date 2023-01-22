//
// Created by Antoniu Ficard on 27.10.2022.
//

#ifndef GRAPHICSTEST_PHYSICS_H
#define GRAPHICSTEST_PHYSICS_H

#include "tigr.h"
#include "geometry.h"

#define MAX_HEALTH 100
#define AIR_DENSITY 1.204
#define TANK_ASPECT_RATIO 60


enum PhysicalObjectType {
    TANK, PROJECTILE
};

enum ForceType {
    ROTATIONAL, LINEAR
};

typedef struct {
    Point *location;
    float dragCoefficient;
    float sizeCoefficient;
    unsigned int mass;
    unsigned short int health;
    unsigned short int heading;
    Vector linearVelocity;
    float angularVelocity;
} PhysicalObject;

typedef struct {
    PhysicalObject base;
    enum PhysicalObjectType type;
} Tank;

typedef struct {
    PhysicalObject base;
    enum PhysicalObjectType type;
} Projectile;

typedef struct {
    Vector *vector;
    enum ForceType force;
} ForceLinear;

typedef struct {
    float torque;
    enum ForceType force;
} ForceRotational;

/// Functions

// constructors for structs defined above

// allocate space in memory for a Tank object and initialise
Tank *
createTank(Point *location, unsigned short int heading, float sizeCoefficient, float dragCoefficient, unsigned int mass,
           unsigned short int health);

// allocate space in memory for a Projectile object and initialise
Projectile *createProjectile(Point *location, float radius, float dragCoefficient, unsigned int mass,
                             unsigned short int health);

// allocate space in memory for a ForceLinear object and initialise
ForceLinear *createForceLinear(Vector *vector);

// allocate space in memory for a ForceRotational object and initialise
ForceRotational *createForceRotational(float torque);

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

// generate a linear friction force for a given physical object
ForceLinear *generateLinearFriction(PhysicalObject *object);

// generate a rotational friction force for a given physical object
ForceRotational *generateRotationalFriction(PhysicalObject *object);

// functions that apply on physical objects

// apply damage to a physical object and subtract the damage from the health of the physical object or destroy if the damage is too high
void applyDamage(void **object, enum PhysicalObjectType type, unsigned short int damage);

// apply a given linear force object to a physical object and update its velocity
// input: object - PhysicalObject*, pointer to property base of a physical object
//        force - ForceLinear*, pointer to a force object to be applied
//        deltaTime - time difference in nanoseconds from last update
int applyForceLinear(PhysicalObject *object, ForceLinear *force, float deltaTime);

// apply a given rotational force object to a physical object and update its velocity
// input: object - PhysicalObject*, pointer to property base of a physical object
//        force - ForceRotational*, pointer to a force object to be applied
//        deltaTime - time difference in nanoseconds from last update
int applyForceRotational(PhysicalObject *object, ForceRotational *force, float deltaTime);

// updates an object's position relative to its past position, using the velocity properties, after a given time
// input: object - PhysicalObject*, pointer to property base of a physical object
//        deltaTime - time difference in nanoseconds from last update
int updatePosition(PhysicalObject *object, float deltaTime);


// calculates the corner points of the Tank object given as a parameter, and allocates new Points in the corners array for
// input: t - Tank *, the object for which the corners must be calculated
//        corners - Point* [4], array of 4 Point pointers. The array must contain only NULL, as the pointers will be overwritten by the function
// output: corners as a parameter, pointer array from input
//         return: -1 if there is an error, 0 if calculation was successful
int computeTankCorners(Tank *t, Point *corners[4]);


//checks if two tanks are colliding
//input: tank1- pointer to one tank
//       tank2 -pointer to other tank
//output: returns:  1 if the given tanks are penetrating
//                  0 if the given tanks are NOT penetrating
//                  -1 (error) if at least one of the given tanks is NULL
//                  -2 if encountered error with memory allocation
int checkTanksCollision(Tank* tank1, Tank* tank2);

#endif //GRAPHICSTEST_PHYSICS_H
