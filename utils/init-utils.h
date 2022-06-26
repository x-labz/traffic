#pragma once

#include "data/game-types.h"

uint8_t getDir(junction_t j1, junction_t j2) {
    if (j1.x == j2.x) return VERTICAL;
    return HORIZONTAL ;
}