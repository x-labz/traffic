#include "data/store.h"
#include "render_all.h"
#include <LibLog>

using PD = Pokitto::Display;

void renderJunction(junction_t junction)
{

    PD::color = 1;
    PD::drawRect(junction.x - HALF_PATH_WIDTH, junction.y - HALF_PATH_WIDTH, PATH_WIDTH, PATH_WIDTH);
}

void renderPath(path_t path)
{
    PD::color = 2;
    junction_t j1 = globals.junctions[path.nodes[0]];
    junction_t j2 = globals.junctions[path.nodes[1]];

    if (path._dir == HORIZONTAL)
    {
        if (j1.x > j2.x)
        {
            junction_t temp = j1;
            j1 = j2;
            j2 = temp;
        }
        PD::fillRect(j1.x - HALF_PATH_WIDTH, j1.y - HALF_PATH_WIDTH, j2.x - j1.x + PATH_WIDTH, PATH_WIDTH);
    }
    else
    {
        if (j1.y > j2.y)
        {
            junction_t temp = j1;
            j1 = j2;
            j2 = temp;
        }
        PD::fillRect(j1.x - HALF_PATH_WIDTH, j1.y - HALF_PATH_WIDTH, PATH_WIDTH, j2.y - j1.y + PATH_WIDTH);
    }
}

void renderCar(car_t car)
{
    path_t path = globals.paths[car.path];
    junction_t j1 = globals.junctions[path.nodes[0]];
    junction_t j2 = globals.junctions[path.nodes[1]];

    uint32_t pos = (car.pos) >> 8;
    uint8_t startX = j1.x > j2.x ? j2.x : j1.x;
    uint8_t startY = j1.y > j2.y ? j2.y : j1.y;
    int16_t offset = (car.dir ? -LANE_OFFSET - CAR_SIZE :  LANE_OFFSET) ;
    if (j1.x == j2.x)
    {
        startY += pos;
        startX += offset  ;
    }
    else
    {
        startX += pos;
        startY += offset ;
    }

    PD::color = 3;
    PD::fillRect(startX , startY , CAR_SIZE, CAR_SIZE);
}

void renderAll()
{
    for (uint8_t i = 0; i != PATH_CNT; i++)
    {
        renderPath(globals.paths[i]);
    }

    for (uint8_t i = 0; i != JUNCTION_CNT; i++)
    {
        renderJunction(globals.junctions[i]);
    }

    for (uint8_t i = 0; i != SIZE(globals.cars); i++)
    {
        car_t car = globals.cars[i];
        if (!car.isActive)
            continue;

        renderCar(car);
    }
}