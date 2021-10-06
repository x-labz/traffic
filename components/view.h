#pragma once 

#include <Pokitto.h>

enum renderTypes { JUNCTION };

struct view_t {
    uint16_t entityID;
    renderTypes renderType;
};

view_t fView(uint16_t entityID, renderTypes renderType);