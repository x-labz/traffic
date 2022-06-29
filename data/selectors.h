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

int8_t getPathDir(junction_t * j1, junction_t * j2)
{
    int8_t x_dir = (j1->x - j2->x);
    int8_t y_dir = (j1->y - j2->y);
    int8_t dir = (x_dir == 0 ? y_dir : x_dir);
    return dir >= 0 ? 1 : -1;
}

uint8_t getInactiveCar(void)
{
    uint8_t result;
    for (uint8_t i = 0; i < SIZE(globals.cars); i++)
    {
        if (!globals.cars[i].isActive)
        {
            result = i;
            break;
        }
    }
    return result;
}
