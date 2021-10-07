#pragma once 

#include <Pokitto.h>
#include "components/pos.h"
#include "components/view.h"
#include "global_store.h"


void renderNode(position_t pos); 

void runSystems( entity_t * , uint16_t size ) ;
 