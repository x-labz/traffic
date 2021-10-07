#pragma once  


#define SIZE(_Array) (sizeof(_Array) / sizeof(_Array[0]))

#define MAX_ENT 10
#define MAX_POS 10
#define MAX_VIEW 10

#include "components/pos.h"
#include "components/view.h"
#include "entities/entities.h"

struct genPointers {
    uint16_t entity_p;
    uint16_t position_p;
    uint16_t view_p;
} ;

extern entity_t entities[MAX_ENT] ;
extern position_t componentsPos[MAX_POS] ;
extern view_t componentsView[MAX_VIEW] ;