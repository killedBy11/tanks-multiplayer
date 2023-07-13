//
// Created by Antoniu Ficard on 02.11.2022.
//

#include <stdio.h>
#include "controls.h"
#include "../flags.h"
#include "../graphics/graphics.h"
#include "../measurement_units.h"

void rotationalForceGenerationCycle(Tigr *bmp, Tank *t, millisecond_t deltaTime, int8_t *flags) {
    ForceRotational *rotationalFriction = generateRotationalFriction(&t->base);

    ForceRotational *force = createForceRotational(0);

    if (tigrKeyHeld(bmp, ROTATE_LEFT_KEY)) {
        freeForceRotational(&force);
        force = createForceRotational(-ROTATION_KEY_TORQUE);
    } else if (tigrKeyHeld(bmp, ROTATE_RIGHT_KEY)) {
        freeForceRotational(&force);
        force = createForceRotational(ROTATION_KEY_TORQUE);
    }

    ForceRotational *resultRotational = addForceRotational(force, rotationalFriction);

    applyForceRotational(&t->base, resultRotational, deltaTime);
}

void linearForceGenerationCycle(Tigr *bmp, Tank *t, millisecond_t deltaTime, int8_t *flags) {
    Point *anchor = createPointFromPoint_f(*t->base.location);
    ForceLinear *friction = generateLinearFriction(&t->base);

    if (DISPLAY_FORCES_DECOMPOSED == flags[DISPLAY_FORCES_FLAG]) {
        drawVector(bmp, friction->vector, anchor, tigrRGB(0xFF, 0x00, 0x00));
    }

    Vector *v = createVector(0, 0);
    ForceLinear *f = createForceLinear(v);

    if (tigrKeyHeld(bmp, FORWARD_KEY)) {
        freeForceLinear(&f);

        v = createVectorByAngle(degreesToRadians(t->base.heading), FORWARD_KEY_FORCE);
        f = createForceLinear(v);
    } else if (tigrKeyHeld(bmp, BACKWARD_KEY)) {
        freeForceLinear(&f);

        v = createVectorByAngle(degreesToRadians(t->base.heading), -BACKWARD_KEY_FORCE);
        f = createForceLinear(v);
    }

    if (DISPLAY_FORCES_DECOMPOSED == flags[DISPLAY_FORCES_FLAG]) {
        drawVector(bmp, f->vector, anchor, tigrRGB(0xFF, 0x00, 0x00));
    }

    ForceLinear *result = addForceLinear(friction, f);

    if (DISPLAY_ALL_FORCES == flags[DISPLAY_FORCES_FLAG]) {
        drawVector(bmp, result->vector, anchor, tigrRGB(0x00, 0xFF, 0x00));
    }

    freePoint(&anchor);
    applyForceLinear(&t->base, result, deltaTime);
}