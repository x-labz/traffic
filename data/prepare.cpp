#include <data/prepare.h>

void initJunctions(genPointers *poi)
{
    const uint16_t junc[] = {
        10,
        10,

        180,
        10,

        10,
        120,

        180,
        120,

        0,
        10};

    for (uint16_t i = 0; i < SIZE(junc); i += 2)
    {
        uint16_t id = poi->entity_p + 1;
        position_t p = fPosition(id, junc[i], junc[i + 1]);
        view_t v = fView(id, JUNCTION_RENDERER);
        junction_t junction = {id, globals.junctionWidth};

        globals.componentsPos[poi->position_p] = p;
        globals.componentsView[poi->view_p] = v;
        globals.componentsJunction[poi->junction_p] = junction;

        poi->entity_p++;
        poi->position_p++;
        poi->view_p++;
        poi->junction_p++;
    }
}

void initPaths(genPointers *poi)
{

    const uint16_t paths[] = {
        1,
        2,

        2,
        4,

        3,
        1,

        5,
        1};

    for (uint16_t i = 0; i < SIZE(paths); i += 2)
    {

        uint16_t id = poi->entity_p + 1;

        path_t path = {id, paths[i], paths[i + 1]};
        view_t v = fView(id, PATH_RENDER);

        globals.componentsPath[poi->path_p] = path;
        globals.componentsView[poi->view_p] = v;

        poi->entity_p++;
        poi->path_p++;
        poi->view_p++;
    }
}

void initCars(genPointers *poi)
{
    uint16_t id = poi->entity_p + 1;

    position_t p = fPosition(id, 50, 50);
    view_t v = fView(id, CAR_RENDER);

    globals.componentsPos[poi->position_p] = p;
    globals.componentsView[poi->view_p] = v;

    poi->entity_p++;
    poi->position_p++;
    poi->view_p++;
}