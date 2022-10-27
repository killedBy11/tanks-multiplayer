//
// Created by Antoniu Ficard on 27.10.2022.
//

#ifndef GRAPHICSTEST_PHYSICS_H
#define GRAPHICSTEST_PHYSICS_H
#define ASPECT_RATIO 60

#include "tigr.h"

typedef enum {
    TANK, PROJECTILE, FORCE
} ObjectType;

typedef enum {
    ROTATIONAL, LINEAR
} ForceType;


typedef struct {
    int x;
    int y;
    int heading;
    float sizeCoefficient;
    float dragCoefficient;
    int mass;
    ObjectType type;
} Tank;

typedef struct {
    int x;
    int y;
    int r;
    float dragCoefficient;
    int mass;
    ObjectType type;
} Projectile;

typedef struct {
    int i;
    int j;
    ObjectType type;
    ForceType force;
} ForceLinear;

typedef struct {
    int w;
    ObjectType type;
    ForceType force;
} ForceRotational;

/// Functions

#endif //GRAPHICSTEST_PHYSICS_H
