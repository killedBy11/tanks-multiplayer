//
// Created by Antoniu Ficard on 27.10.2022.
//

#ifndef GRAPHICSTEST_PHYSICS_H
#define GRAPHICSTEST_PHYSICS_H

#include "../graphics/tigr.h"
#include "../geometry/geometry.h"
#include "../measurement_units.h"

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
    Point_f *location;
    float dragCoefficient;
    float sizeCoefficient;
    integer_kilograms_t mass;
    percentage_t health;
    degrees_t heading;
    Vector linearVelocity;
    degrees_per_millisecond_t angularVelocity;
} PhysicalObject;

typedef struct {
    Vector *vector;
    enum ForceType force;
} ForceLinear;

typedef struct {
    kilonewton_meters_t torque;
    enum ForceType force;
} ForceRotational;

/// Functions

// constructors for structs defined above

// allocate space in memory for a ForceLinear object and initialise
ForceLinear *createForceLinear(Vector *vector);

// allocate space in memory for a ForceRotational object and initialise
ForceRotational *createForceRotational(kilonewton_meters_t torque);

// destructors that go recursively for the structs defined above

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

// apply a given linear force object to a physical object and update its velocity
// input: object - PhysicalObject*, pointer to property base of a physical object
//        force - ForceLinear*, pointer to a force object to be applied
//        deltaTime - time difference in nanoseconds from last update
int applyForceLinear(PhysicalObject *object, ForceLinear *force, millisecond_t deltaTime);

// apply a given rotational force object to a physical object and update its velocity
// input: object - PhysicalObject*, pointer to property base of a physical object
//        force - ForceRotational*, pointer to a force object to be applied
//        deltaTime - time difference in nanoseconds from last update
int applyForceRotational(PhysicalObject *object, ForceRotational *force, millisecond_t deltaTime);

// updates an object's position relative to its past position, using the velocity properties, after a given time
// input: object - PhysicalObject*, pointer to property base of a physical object
//        deltaTime - time difference in nanoseconds from last update
int updatePosition(PhysicalObject *object, millisecond_t deltaTime);
#endif //GRAPHICSTEST_PHYSICS_H
