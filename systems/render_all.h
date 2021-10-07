#pragma once 

#include <Pokitto.h>
#include "components/pos.h"
#include "components/view.h"
#include "global_store.h"
#include "entities/entities.h"  

void renderNode(position_t pos); 

void renderAll( entity_t * items, uint32_t size ) ;
 