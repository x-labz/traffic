#include <data/prepare.h>



void initJunctions(genPointers * poi) {

    uint16_t junc[] = {
        10,
        10,
        
        200,
        10,
        
        10,
        120,
        
        200,
        120
    };

    for (uint16_t i = 0; i < SIZE(junc); i+=2) {
        
        uint16_t id = poi->entity_p +1 ;
        
        position_t p = fPosition( id, junc[i], junc[i+1]);


        view_t v = fView(id, JUNCTION);

        componentsPos[id] = p;
        componentsView[id] = v;

        entity_t e = {
            id,
            {}
        };
        e.components[POS] = & componentsPos[id];
        e.components[VIEW] = & componentsView[id];

        entities[id] = e;
        
        poi->entity_p++;
    }

}