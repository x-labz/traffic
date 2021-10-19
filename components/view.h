#pragma once

#include <Pokitto.h>

enum renderTypes
{
    JUNCTION_RENDERER,
    PATH_RENDER,
    CAR_RENDER
};

struct view_t
{
    uint16_t entityID;
    renderTypes renderType;
};

view_t fView(uint16_t entityID, renderTypes renderType);