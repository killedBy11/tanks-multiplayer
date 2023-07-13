//
// Created by Antoniu Ficard on 02.11.2022.
//

#ifndef GRAPHICSTEST_CONTROLS_H
#define GRAPHICSTEST_CONTROLS_H

#include <stdint.h>
#include "../physics/physics.h"
#include "../graphics/tigr.h"
#include "../geometry/geometry.h"

#define FORWARD_KEY 'W'
#define BACKWARD_KEY 'S'
#define ROTATE_LEFT_KEY 'A'
#define ROTATE_RIGHT_KEY 'D'
#define SHOOT_KEY TK_SPACE

#define ROTATION_KEY_TORQUE 0.3f
#define FORWARD_KEY_FORCE 0.5f
#define BACKWARD_KEY_FORCE 0.35f

// read inputs from the keyboard, generate the affiliate rotational forces and apply them to the object
void rotationalForceGenerationCycle(Tigr *bmp, Tank *t, millisecond_t deltaTime, int8_t *flags);

// read inputs from the keyboard, generate the affiliate linear forces and apply them to the object
void linearForceGenerationCycle(Tigr *bmp, Tank *t, millisecond_t deltaTime, int8_t *flags);

#endif //GRAPHICSTEST_CONTROLS_H
