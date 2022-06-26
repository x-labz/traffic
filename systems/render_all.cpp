#include "data/store.h"
#include "render_all.h"
#include <LibLog>

using PD = Pokitto::Display;

void renderJunction(junction_t junction)
{

    PD::color = 1;
    PD::fillRectangle(junction.x, junction.y, PATH_WIDTH, PATH_WIDTH);
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
        PD::fillRect(j1.x, j1.y, j2.x - j1.x + PATH_WIDTH, PATH_WIDTH);
    }
    else
    {
        if (j1.y > j2.y)
        {
            junction_t temp = j1;
            j1 = j2;
            j2 = temp;
        }
        PD::fillRect(j1.x, j1.y, PATH_WIDTH, j2.y - j1.y + PATH_WIDTH);
    }
}

void renderCar(uint16_t id)
{

    PD::color = 3;
    // PD::fillRect(pos.x, pos.y, 10, 5);
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

    
}