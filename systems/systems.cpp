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

            if (generator->lastId >= 0)
            {
                car_t *last_car_p = &(globals.cars[generator->lastId]);
                int32_t dist = abs((last_car_p->pos >> 8) - (pos >> 8));
                if (dist <= CAR_SIZE + CAR_GAP)
                {
                    continue;
                }
            }

            //   LOG(" GEN:", i, " CAR id:", id, " dir:", dir, " len:", len, " pos:", pos );
            globals.cars[id] = {
                true,
                false,
                dir > 0 ? 1 : 0,   // dir
                generator->pathId, // path
                pos,               // pos
                generator->lastId  // preceding
            };
            generator->lastId = id;
        }
    }
}

void moveCars(uint32_t time)
{
    for (uint8_t i = 0; i != SIZE(globals.cars); i++)
    {
        car_t car = globals.cars[i];
        if (!car.isActive || car.isStopped)
            continue;

        uint8_t path_lenght = getPathLenght(&(globals.paths[car.path]));
        int32_t value = car.pos;
        value += (car.dir ? 1 : -1) * CAR_SPEED * (time >> 1);
        if (value > 256 * (path_lenght - PATH_WIDTH) && car.dir)
        {
            value = 256 * (path_lenght - PATH_WIDTH);
        }

        if (value < (PATH_WIDTH << 8) && !car.dir)
        {
            value = (PATH_WIDTH << 8);
        }

        globals.cars[i].pos = value;
        globals.cars[i].dir = car.dir;
    }
}

void stopCars(void)
{
    for (uint8_t i = 0; i != SIZE(globals.cars); i++)
    {
        car_t *car = &(globals.cars[i]);
        if (!car->isActive)
            continue;

        int32_t value = car->pos;
        path_t *path_p = &(globals.paths[car->path]);
        uint8_t path_lenght = getPathLenght(path_p);
        if (value == 256 * (path_lenght - PATH_WIDTH) || value == (PATH_WIDTH << 8))
        {
            car->isStopped = true;
            continue;
        }

        if (car->precedingId < 0)
            continue;

        car_t *precedingCar = &(globals.cars[car->precedingId]);
        if (!precedingCar->isStopped)
            continue;

        int32_t dist = abs((car->pos >> 8) - (precedingCar->pos >> 8));
        // LOG(" dist ", dist, " car ", (car->pos >> 8), " pre ",(precedingCar->pos >> 8), " id ", i , " pre ", car->precedingId);
        if (dist < CAR_SIZE + CAR_GAP)
        {
            car->isStopped = true;
            car->pos = precedingCar->pos + (CAR_SIZE + CAR_GAP << 8) * (car->dir ? -1 : 1);
        }
    }
}

void changePath(void)
{
    // for (uint8_t i = 0; i != SIZE(globals.cars); i++)
    // {
    //     car_t *car = &(globals.cars[i]);
    //     if (!car->isActive)
    //         continue;

    //     int32_t value = car->pos;
    //     if (value == 256 * (path_lenght) || value == 0)
    //     {
    //         path_t *path_p = &(globals.paths[car->path]);
    //         uint8_t junction_id = path_p->nodes[value == 0 ? 0 : 1];

    //         path_t *paths[3];
    //         uint8_t poi = 0;
    //         for (uint8_t i = 0; i < PATH_CNT; i++)
    //         {
    //             path_t *path = &(globals.paths[i]) if ((path->nodes[0] == junction_id || path->nodes[1] == junction_id) && car->path != i)
    //             {
    //                 paths[poi] = path;
    //                 poi++;
    //             }
    //         }
    //     }
    // }
}

void runSystems(uint32_t ts)
{
    uint32_t time = ts - globals.last_ts;
    generateCars(ts);
    moveCars(time);
    stopCars();
    renderAll();
}