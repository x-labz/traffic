
#include "init_ecs.h"
#include "components/pos.h"
#include <global_store.h>
#include "entities/entities.h"
#include <LibLog>

void initEcs(void) {

    position_t p1 = fPosition(1, 10, 23);

    LOG(  p1.x  , "\n" ) ;
    view_t v1 = fView(1, JUNCTION);

    componentsPos[0] = p1;
    componentsView[0] = v1 ;

    entity_t e1 = {
        1,
        {}
    };
    e1.components[POS] = &p1;
    e1.components[VIEW] = &v1;

    entities[0] = e1 ;
    
    LOG( (*((position_t *)(entities[0].components[POS]))).y ,"\n" ) ;
    
    // ---------------

    position_t p2 = fPosition(2, 40, 50);

    view_t v2 = fView(2, JUNCTION);

    componentsPos[1] = p2;
    componentsView[1] = v2 ;

    entity_t e2 = {
        2,
        {}
    };
    e2.components[POS] = &p2;
    e2.components[VIEW] = &v2;

    entities[1] = e2 ;
    
    LOG( (*((position_t *)(entities[1].components[POS]))).y ,"\n" ) ;
}