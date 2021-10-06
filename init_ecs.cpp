
#include "init_ecs.h"
#include "components/pos.h"
#include <global_store.h>
#include "entities/entities.h"
#include <LibLog>

void initEcs(void) {

    entity_t e1 = {
        1,
        {}
    };

    position_t p1 = fPosition(1, 10, 20);

    LOG(  p1.x  , "\n" ) ;
    view_t v1 = fView(1, JUNCTION);

    vPosition.push_back(p1);
    vViews.push_back(v1);

    componentEntry_t cEp1 = {
        POS,
        (void*)(&p1)
    };
    LOG( (*(position_t *)(cEp1.component)).x  , "\n" ) ;
    componentEntry_t cEv1 = {
        VIEW,
        (void*)(&v1)
    };

    e1.components.push_back(cEp1);
    e1.components.push_back(cEv1);
    vEntities.push_back(e1);
    
    position_t test = *(position_t *)(vEntities.at(0).components.at(0).component);
    LOG("test:", test.x ) ;
    // ---------------

    entity_t e2 = {
        2,
        {}
    };

    position_t p2 = fPosition(2, 30, 40);
    view_t v2 = fView(2, JUNCTION);

    vPosition.push_back(p2);
    vViews.push_back(v2);

    componentEntry_t cEp2 = {
        POS,
        (void*)(&p2)
    };
    componentEntry_t cEv2 = {
        VIEW,
        (void*)(&v2)
    };

    e2.components.push_back(cEp2);
    e2.components.push_back(cEv2);
    vEntities.push_back(e2);
    
    return;
}