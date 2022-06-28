#pragma once

#include "store.h"

uint8_t getPathLenght(path_t *path)
{

    junction_t j1 = globals.junctions[path->nodes[0]];
    junction_t j2 = globals.junctions[path->nodes[1]];

    uint8_t x_len = abs(j1.x - j2.x);
    uint8_t y_len = abs(j1.y - j2.y);
    uint8_t len = x_len > 0 ? x_len : y_len;
    return len;
}

