#include "init_ecs.h"

void initEcs(void) {

    genPointers poi = { 0, 0 ,0 , 0, 0 } ;

    uint16_t size = SIZE(entities);
    for (uint16_t i = 0; i != size; i++) {
        entity_t e = {
            0,
            {}
        };
        entities[i] = e;
    }

    initJunctions(&poi) ;
    initPaths(&poi);
    
    LOG("POI:", poi.entity_p ,"\n") ;
    LOG( poi.position_p ,"\n") ;
    LOG( poi.view_p ,"\n") ;
    LOG( poi.width_p ,"\n") ;
    LOG( poi.path_p ,"\n") ;

   
}