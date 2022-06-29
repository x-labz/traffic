#pragma once

#include <Pokitto.h>

#define PATH_WIDTH 10
#define HALF_PATH_WIDTH PATH_WIDTH / 2
#define CAR_SPEED 28
#define LANE_OFFSET 1
#define CAR_SIZE 2
#define GENERATE_INTERVAL 1000

#define CAR_GAP 2

//  __attribute__((packed))

enum dirEnum
{
    HORIZONTAL,
    VERTICAL
};

enum junctionType
{
    TURN_BACK,
    NONE
};

struct junction_t
{
    uint8_t x;
    uint8_t y;
    unsigned int dir : 1;
    unsigned int type : 7;
} __attribute__((packed));

struct generator_t
{
    uint8_t junctionId;
    uint8_t pathId;
    uint32_t last_gen_ts;
    int8_t lastId;
} __attribute__((packed));

struct path_t
{
    uint8_t nodes[2];
    uint8_t _dir;
} __attribute__((packed));

struct car_t
{
    bool isActive;
    bool isStopped;
    unsigned int dir : 1;
    unsigned int path : 6;
    uint16_t pos;
    int8_t precedingId;
} __attribute__((packed));
