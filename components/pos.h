#pragma once 

#include <Pokitto.h>

struct position_t {
    uint16_t entityID;
    int16_t x;
    int16_t y;
};

position_t fPosition(uint16_t entityID, int16_t x, int16_t y);