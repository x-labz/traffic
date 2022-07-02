#pragma once

#include <LibLog>
#include "store.h"

int8_t get1DimDir(dir_t dir)
{
    return dir.x == 0 ? dir.y : dir.x;
}

dir_t getLeftPathDir(dir_t props)
{
    if (props.x == 0 && props.y == 1)
        return {-1, 0};
    if (props.x == -1 && props.y == 0)
        return {0, -1};
    if (props.x == 0 && props.y == -1)
        return {1, 0};
    if (props.x == 1 && props.y == 0)
        return {0, 1};
    LOG("invalid direction ", props.x, props.y, "\n");
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
