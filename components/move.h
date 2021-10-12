#pragma once 

#include <Pokitto.h>


struct move_t {
    uint16_t entityID;
    int16_t acceleration ;
    int16_t velocity;
    int16_t dir;
};

