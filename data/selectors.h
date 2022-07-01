#pragma once

#include <LibLog>
#include "store.h"

int8_t get1DimDir(dir_t dir)
{
    return dir.x == 0 ? dir.y : dir.x;
}

direction_t getLeftPath(direction_t props)
{
    
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
