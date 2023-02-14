//
// Created by Antoniu Ficard on 14.02.2023.
//

#ifndef GRAPHICSTEST_FLAGS_H
#define GRAPHICSTEST_FLAGS_H

#include <stdint.h>

#define FLAG_COUNT 1
#define DISPLAY_FORCES_FLAG 0
#define DISPLAY_NO_FORCES 0
#define DISPLAY_ALL_FORCES 1
#define DISPLAY_FORCES_DECOMPOSED 2

struct {
    int8_t flag;
    int8_t value;
} typedef flag;

#endif //GRAPHICSTEST_FLAGS_H
