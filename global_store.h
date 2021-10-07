#pragma once  

#define SIZE(_Array) (sizeof(_Array) / sizeof(_Array[0]))

#define MAX_ENT 10
#define MAX_POS 10
#define MAX_VIEW 10
#define MAX_WIDTH 10
#define MAX_PATH 10

#include "components/pos.h"
#include "components/view.h"
#include "components/width.h"
#include "components/path.h"
#include "entities/entities.h"

struct genPointers {
    uint16_t entity_p;
    uint16_t position_p;
    uint16_t view_p;
    uint16_t width_p;
    uint16_t path_p;
} ;

extern entity_t entities[MAX_ENT] ;
extern position_t componentsPos[MAX_POS] ;
extern view_t componentsView[MAX_VIEW] ;
extern width_t componentsWidth[MAX_WIDTH] ;
extern path_t componentsPath[MAX_PATH] ;