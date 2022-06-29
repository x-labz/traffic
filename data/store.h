#pragma once

#include "game-types.h"

#define SIZE(_Array) (sizeof(_Array) / sizeof(_Array[0]))
#define JUNCTION_CNT 3
#define PATH_CNT 2
#define GEN_CTN 2

struct global_t
{
    uint32_t last_ts;
    junction_t junctions[8];
    generator_t generators[4];
    path_t paths[8];
    car_t cars[64];
};

void initStore(uint32_t ts);

extern global_t globals;