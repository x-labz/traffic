#pragma once

#include "game-types.h"

#define SIZE(_Array) (sizeof(_Array) / sizeof(_Array[0]))
#define JUNCTION_CNT 3
#define PATH_CNT 2
#define GEN_CTN 1
#define DRAIN_CNT 1

struct global_t
{
    uint32_t last_ts;
    junction_t junctions[JUNCTION_CNT];
    generator_t generators[GEN_CTN];
    path_t paths[PATH_CNT];
    car_t cars[64];
    drain_t drains[DRAIN_CNT];
};

void initStore(uint32_t ts);

extern global_t globals;