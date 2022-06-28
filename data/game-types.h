#pragma once

#include <Pokitto.h>

#define PATH_WIDTH 10 
#define HALF_PATH_WIDTH PATH_WIDTH/2
#define CAR_SPEED 8
#define LANE_OFFSET 1
#define CAR_SIZE 2

enum dirEnum
{
    HORIZONTAL,
    VERTICAL
};

struct junction_t
{
    uint8_t x;
    uint8_t y;
    uint8_t dir;
};

struct path_t
{
    uint8_t nodes[2];
    uint8_t _dir;
};

struct car_t
{
    bool isActive;
    unsigned int dir:1;
    unsigned int path:6;
    uint16_t pos;
};
