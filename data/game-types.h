#pragma once

#include <Pokitto.h>

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
    uint8_t pos;
};
