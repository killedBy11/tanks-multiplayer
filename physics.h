//
// Created by Antoniu Ficard on 27.10.2022.
//

#ifndef GRAPHICSTEST_PHYSICS_H
#define GRAPHICSTEST_PHYSICS_H
#define ASPECT_RATIO 60

#include "tigr.h"

typedef struct {
    int x;
    int y;
    int heading;
    float sizeCoefficient;
    float dragCoefficient;
    int mass;
} Tank;

typedef struct {
    int x;
    int y;
    int r;
    float dragCoefficient;
    int mass;
} Projectile;

typedef struct {
    int i;
    int j;
} ForceLinear;

typedef struct {
    int w;
} ForceRotational;

typedef enum {
    ROTATIONAL, LINEAR
} ForceType;

/// Functions

// gets a tank as a parameter and draws it on the screen given as parameter
int drawTank(Tigr *bmp, Tank t);

// gets a projectile as a parameter and draws it on the screen given as parameter
int drawProjectile(Tigr *bmp, Projectile p);


#endif //GRAPHICSTEST_PHYSICS_H
