//
// Created by Antoniu Ficard on 27.10.2022.
//

#include "../physics/physics.h"
#include "../physics/tank.h"
#include "../physics/projectile.h"
#include "../geometry/geometry.h"
#include "../measurement_units.h"

// Functions

// gets a tank as a parameter and draws it on the screen given as parameter
int drawTank(Tigr *bmp, Tank *t, TPixel color);

// gets a projectile as a parameter and draws it on the screen given as parameter
int drawProjectile(Tigr *bmp, Projectile *p, TPixel color);

// gets a vector and a point and draws the vector on the screen, anchored to the point received as a parameter
// input: bmp - the bitmap on which to draw
//        v - the vector to be drawn
//        anchor - the point that the vector will be anchored on, the base on the vector will be drawn on the this point
int drawVector(Tigr *bmp, Vector *v, Point *anchor, TPixel color);