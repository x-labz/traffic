#include "data/store.h"
#include "render_all.h"
#include <LibLog>

using PD = Pokitto::Display;

void renderJunction(junction_t junction)
{

    // PD::color = 1;
    // PD::drawRect(junction.x - HALF_PATH_WIDTH, junction.y - HALF_PATH_WIDTH, PATH_WIDTH, PATH_WIDTH);
}

void renderPath(path_t path)
{
    PD::color = 9;
    junction_t j1 = globals.junctions[path.nodes[0]];
    junction_t j2 = globals.junctions[path.nodes[1]];

    if (path._dir.x != 0)
    {
        PD::fillRect(j1.x - HALF_PATH_WIDTH, j1.y - HALF_PATH_WIDTH, j2.x - j1.x + PATH_WIDTH, PATH_WIDTH);
        uint8_t len = j2.x - j1.x - PATH_WIDTH;
        for (uint8_t i = 0; i < (len / 10); i++)
        {
            PD::color = 4;
            PD::drawRow(HALF_PATH_WIDTH + j1.x + i * 10, HALF_PATH_WIDTH + j1.x + i * 10 + 4, j1.y);
        }
    }
    else
    {
        PD::fillRect(j1.x - HALF_PATH_WIDTH, j1.y - HALF_PATH_WIDTH, PATH_WIDTH, j2.y - j1.y + PATH_WIDTH);
        uint8_t len = j2.y - j1.y - PATH_WIDTH;
        for (uint8_t i = 0; i < (len / 10); i++)
        {
            PD::color = 4;
            PD::drawColumn(j1.x, HALF_PATH_WIDTH + j1.y + i * 10, HALF_PATH_WIDTH + j1.y + i * 10 + 4);
        }
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
    if (j1.x == j2.x)
    {
        int16_t offset = (car.dir == 1 ? -LANE_OFFSET - CAR_SIZE : LANE_OFFSET);

        startY += pos;
        startX += offset;
    }
    else
    {
        int16_t offset = (car.dir == 1 ? LANE_OFFSET : -LANE_OFFSET);
        startX += pos;
        startY += offset;
    }

    PD::color = 8;
    PD::fillRect(startX, startY, CAR_SIZE + 1, CAR_SIZE);
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