//
// Created by Antoniu Ficard on 27.10.2022.
//

#include "physics.h"
#include "geometry.h"

//#define TANK_ASPECT_RATIO 60
#define LINE_COLOR tigrRGB(0xFF, 0xFF, 0xFF)
#define BACKGROUND_COLOR tigrRGB(0x00, 0x00, 0x00)

// Functions

// gets a tank as a parameter and draws it on the screen given as parameter
int drawTank(Tigr *bmp, Tank *t);

// gets a projectile as a parameter and draws it on the screen given as parameter
int drawProjectile(Tigr *bmp, Projectile *p);
