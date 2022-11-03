//
// Created by Antoniu Ficard on 02.11.2022.
//

#include "controls.h"

void rotationalForceGenerationCycle(Tigr *bmp, Tank *t, float deltaTime) {
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

void linearForceGenerationCycle(Tigr *bmp, Tank *t, float deltaTime) {
    ForceLinear *friction = generateLinearFriction(&t->base);

    Vector *v = createVector(0, 0);
    ForceLinear *f = createForceLinear(v);

    if (tigrKeyHeld(bmp, 'W')) {
        freeForceLinear(&f);

        v = createVectorByAngle(degreesToRadians(t->base.heading), 0.5f);
        f = createForceLinear(v);
    } else if (tigrKeyHeld(bmp, 'S')) {
        freeForceLinear(&f);

        v = createVectorByAngle(degreesToRadians(t->base.heading), -0.25f);
        f = createForceLinear(v);
    }

    ForceLinear *result = addForceLinear(friction, f);

    applyForceLinear(&t->base, result, deltaTime);
}