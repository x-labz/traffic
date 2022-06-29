#pragma once

#include <Pokitto.h>

#define PATH_WIDTH 10
#define HALF_PATH_WIDTH PATH_WIDTH / 2
#define CAR_SPEED 8
#define LANE_OFFSET 1
#define CAR_SIZE 2
#define GENERATE_INTERVAL 500

enum dirEnum
{
    HORIZONTAL,
    VERTICAL
};

enum junctionType
{
    GENERATOR,
    DRAIN,
    TURN_BACK,
    NONE
};

struct junction_t
{
    uint8_t x;
    uint8_t y;
    unsigned int dir : 1;
    unsigned int type : 7;
};

struct  generator_t
{
    uint8_t junctionId;
    uint8_t pathId;
    uint32_t last_gen_ts;
};


struct path_t
{
    uint8_t nodes[2];
    uint8_t _dir;
    uin8_t stop_low;
    uin8_t stop_high;
};

struct car_t
{
    bool isActive;
    unsigned int dir : 1;
    unsigned int path : 6;
    uint16_t pos;
};
