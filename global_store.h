#pragma once

#define SIZE(_Array) (sizeof(_Array) / sizeof(_Array[0]))

#define MAX_ENT 35
#define MAX_POS 35
#define MAX_VIEW 35
#define MAX_JUNCTION 10
#define MAX_PATH 10

#include "components/pos.h"
#include "components/view.h"
#include "components/junction.h"
#include "components/path.h"

struct genPointers
{
    uint16_t entity_p;
    uint16_t position_p;
    uint16_t view_p;
    uint16_t junction_p;
    uint16_t path_p;
};

struct global_t
{
    uint8_t junctionWidth;
    uint16_t entityCount;
    position_t componentsPos[MAX_POS];
    view_t componentsView[MAX_VIEW];
    junction_t componentsJunction[MAX_JUNCTION];
    path_t componentsPath[MAX_PATH];
};

extern global_t globals;
