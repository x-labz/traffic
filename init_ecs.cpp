#include "init_ecs.h"

void initEcs(void)
{

    globals.junctionWidth = 20;

    genPointers poi = {0, 0, 0, 0, 0};

    initJunctions(&poi);
    initPaths(&poi);

    initCars(&poi);

    globals.entityCount = poi.entity_p - 1;

    LOG("POI:", poi.entity_p, "\n");
    LOG(poi.position_p, "\n");
    LOG(poi.view_p, "\n");
    LOG(poi.junction_p, "\n");
    LOG(poi.path_p, "\n");

    LOG("SIZES:", sizeof(globals.componentsPos), ",", sizeof(globals.componentsView), ",", sizeof(globals.componentsJunction), ",", sizeof(globals.componentsPath), "\n");
}