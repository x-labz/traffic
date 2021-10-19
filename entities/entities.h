#pragma once

#include <Pokitto.h>

#define COMPONENTS_NUM 10

enum componentTypes
{
    POS,
    VIEW,
    JUNCTION,
    PATH
};

struct entity_t
{
    uint16_t entityID;
    void *components[COMPONENTS_NUM];
};
