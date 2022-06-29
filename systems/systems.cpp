#include "systems.h"
#include <LibLog>
#include "render_all.h"
#include "data/store.h"
#include "data/selectors.h"
#include "data/game-types.h"

void generateCars(uint32_t ts)
{
    for (uint8_t i = 0; i < GEN_CTN; i++)
    {
        generator_t *generator = &(globals.generators[i]);

        if (ts > generator->last_gen_ts + GENERATE_INTERVAL)
        {
            generator->last_gen_ts = ts;

            uint8_t id = getInactiveCar();

            path_t *path = &(globals.paths[generator->pathId]);

            junction_t *j1 = &(globals.junctions[generator->junctionId]);
            junction_t *j2 = &(globals.junctions[path->nodes[path->nodes[0] == generator->junctionId ? 1 : 0]]);

            int8_t dir = getPathDir(j1, j2);
            uint8_t len = getPathLenght(path);
            uint16_t pos = dir == 1 ? 0 : (len - 1) << 8;
            //   LOG(" GEN:", i, " CAR id:", id, " dir:", dir, " len:", len, " pos:", pos );
            globals.cars[id] = {
                true,
                dir > 0 ? 1 : 0,   // dir
                generator->pathId, // path
                pos};              // pos
        }
    }
}

void moveCars(uint32_t time)
{
    for (uint8_t i = 0; i != SIZE(globals.cars); i++)
    {
        car_t car = globals.cars[i];
        if (!car.isActive)
            continue;

        uint8_t path_lenght = getPathLenght(&(globals.paths[car.path]));
        int32_t value = car.pos;
        value += (car.dir ? 1 : -1) * CAR_SPEED * (time >> 1);
        if (value > 256 * (path_lenght))
        {
            value = 256 * (path_lenght);
        }

        if (value < 0)
        {
            value = 0;
        }

        globals.cars[i].pos = value;
        globals.cars[i].dir = car.dir;
    }
}

void runSystems(uint32_t ts)
{
    uint32_t time = ts - globals.last_ts;
    generateCars(ts);
    moveCars(time);
    renderAll();
}