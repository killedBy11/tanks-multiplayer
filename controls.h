//
// Created by Antoniu Ficard on 02.11.2022.
//

#ifndef GRAPHICSTEST_CONTROLS_H
#define GRAPHICSTEST_CONTROLS_H

#include "physics.h"
#include "tigr.h"
#include "geometry.h"

#define FORWARD_KEY 'W'
#define BACKWARD_KEY 'S'
#define ROTATE_LEFT_KEY 'A'
#define ROTATE_RIGHT_KEY 'D'
#define SHOOT_KEY TK_SPACE

// read inputs from the keyboard, generate the affiliate rotational forces and apply them to the object
void rotationalForceGenerationCycle(Tigr *bmp, Tank *t, float deltaTime);

// read inputs from the keyboard, generate the affiliate linear forces and apply them to the object
void linearForceGenerationCycle(Tigr *bmp, Tank *t, float deltaTime);

#endif //GRAPHICSTEST_CONTROLS_H
