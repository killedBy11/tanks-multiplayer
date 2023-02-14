//
// Created by Antoniu Ficard on 02.11.2022.
//

#include "controls.h"
#include "flags.h"
#include "graphics.h"

void rotationalForceGenerationCycle(Tigr *bmp, Tank *t, float deltaTime, int8_t *flags) {
    ForceRotational *rotationalFriction = generateRotationalFriction(&t->base);

    ForceRotational *force = createForceRotational(0);

    if (tigrKeyHeld(bmp, 'A')) {
        freeForceRotational(&force);
        force = createForceRotational(-0.3f);
    } else if (tigrKeyHeld(bmp, 'D')) {
        freeForceRotational(&force);
        force = createForceRotational(0.3f);
    }

    ForceRotational *resultRotational = addForceRotational(force, rotationalFriction);

    applyForceRotational(&t->base, resultRotational, deltaTime);
}

void linearForceGenerationCycle(Tigr *bmp, Tank *t, float deltaTime, int8_t *flags) {
    Point *anchor = createPointFromPoint_f(*t->base.location);
    ForceLinear *friction = generateLinearFriction(&t->base);

    if (DISPLAY_FORCES_DECOMPOSED == flags[DISPLAY_FORCES_FLAG]) {
        drawVector(bmp, friction->vector, anchor, tigrRGB(0xFF, 0x00, 0x00));
    }

    Vector *v = createVector(0, 0);
    ForceLinear *f = createForceLinear(v);

    if (tigrKeyHeld(bmp, 'W')) {
        freeForceLinear(&f);

        v = createVectorByAngle(degreesToRadians(t->base.heading), 0.5f);
        f = createForceLinear(v);
    } else if (tigrKeyHeld(bmp, 'S')) {
        freeForceLinear(&f);

        v = createVectorByAngle(degreesToRadians(t->base.heading), -0.35f);
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