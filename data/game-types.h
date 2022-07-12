#pragma once

#include <Pokitto.h>

#define PATH_WIDTH 11
#define HALF_PATH_WIDTH PATH_WIDTH / 2
#define CAR_SPEED 10
#define LANE_OFFSET 2
#define CAR_SIZE 2
#define GENERATE_INTERVAL_PX 25
#define PATH_END_HIGH(len) ((len - HALF_PATH_WIDTH - CAR_SIZE) << 8)
#define PATH_END_LOW (HALF_PATH_WIDTH << 8)

#define CAR_GAP 2

struct dir_t
{
    int x : 4;
    int y : 4;
} __attribute__((packed));

struct junction_t
{
    uint8_t x;
    uint8_t y;
} __attribute__((packed));

struct generator_t
{
    int8_t dir;
    uint8_t pathId;
} __attribute__((packed));

struct drain_t
{
    uint8_t path_id;
    int8_t dir;
} __attribute__((packed));

struct turn_back_t
{
    uint8_t path_id;
    int8_t dir;
} __attribute__((packed));

struct path_t
{
    uint8_t nodes[2];
    dir_t _dir;
    uint8_t _len;
    int8_t min_id;
    int8_t max_id;
} __attribute__((packed));

struct car_t
{
    bool isActive;
    bool isStopped;
    int dir : 2;
    unsigned int path;
    int16_t pos;
    int8_t precedingId;
} __attribute__((packed));
