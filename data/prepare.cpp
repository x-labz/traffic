#include <data/prepare.h>

#define ROAD_WIDTH 25

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
        width_t width = { id, ROAD_WIDTH }  ;

        componentsPos[poi->position_p] = p;
        componentsView[poi->view_p] = v;
        componentsWidth[poi->width_p] = width ;

        entity_t e = {
            id,
            {}
        };
        e.components[POS] = & componentsPos[poi->position_p];
        e.components[VIEW] = & componentsView[poi->view_p];
        e.components[WIDTH] = & componentsWidth[poi->width_p] ;

        entities[id] = e;
        
        poi->entity_p++;
        poi->position_p++;
        poi->view_p++;
        poi->width_p++;
    }

}

void initPaths(genPointers * poi) {

    uint16_t paths[] = {
        1,
        2,
        
        2,
        3,
        
        1,
        4 
    };

    for (uint16_t i = 0; i < SIZE(paths); i+=2) {
        
        uint16_t id = poi->entity_p +1 ;
        
        path_t path = { id, paths[i], paths[i+1] } ;
        view_t v = fView(id, PATH_RENDER);

        componentsPath[poi->path_p] = path;
        componentsView[poi->view_p] = v;

        entity_t e = {
            id,
            {}
        };
        e.components[PATH] = & componentsPath[poi->path_p];
        e.components[VIEW] = & componentsView[poi->view_p];

        entities[id] = e;
        
        poi->entity_p++;
        poi->path_p++;
        poi->view_p++;
    }

}