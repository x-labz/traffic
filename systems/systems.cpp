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

            bool isReversed = path->nodes[0] != generator->junctionId;
            int8_t dir = (path->_dir.x == 0 ? path->_dir.y : path->_dir.x) * (isReversed ? -1 : 1);
            uint8_t len = path->_len;
            uint16_t pos = isReversed ? (len - 1) << 8 : 0;

            if (generator->lastId >= 0)
            {
                car_t *last_car_p = &(globals.cars[generator->lastId]);
                int32_t dist = abs((last_car_p->pos >> 8) - (pos >> 8));
                if (dist <= CAR_SIZE + CAR_GAP)
                {
                    continue;
                }
            }

            // LOG(" GEN:", i, " CAR id:", id, " dir:", dir, " len:", len, " pos:", pos);
            globals.cars[id] = {
                true,
                false,
                dir,               // dir
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

        uint8_t path_lenght = globals.paths[car.path]._len;
        int32_t value = car.pos;
        value += car.dir * CAR_SPEED * (time >> 1);
        if (value > PATH_END_HIGH(path_lenght) && car.dir == 1)
        {
            value = PATH_END_HIGH(path_lenght);
        }

        if (value < PATH_END_LOW && car.dir == -1)
        {
            value = PATH_END_LOW;
        }

        globals.cars[i].pos = value;
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
        uint8_t path_lenght = path_p->_len;
        if (value == PATH_END_HIGH(path_lenght) || value == PATH_END_LOW)
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
        // LOG(" dist ", dist, " car ", (car->pos >> 8), " pre pos ", (precedingCar->pos >> 8), " id ", i, " pre ", car->precedingId, "\n");
        if (dist < CAR_SIZE + CAR_GAP)
        {
            car->isStopped = true;
            car->pos = precedingCar->pos - (((CAR_SIZE + CAR_GAP) << 8) * car->dir);
        }
    }
}

void changePath(void)
{
    for (uint8_t i = 0; i != SIZE(globals.cars); i++)
    {
        car_t *car = &(globals.cars[i]);
        if (!car->isActive)
            continue;

        path_t *path_p = &(globals.paths[car->path]);
        int32_t value = car->pos;
        uint8_t path_length = path_p->_len;
        if (value == PATH_END_HIGH(path_length) || value == PATH_END_LOW)
        {

            uint8_t junction_id = path_p->nodes[value == 0 ? 0 : 1];
            // direction_t path_props = getPathProperties(junction_id, car->path);

            int8_t path_forward_id = -1;
            int8_t path_left_id = -1;

            direction_t left_path_props = getLeftPath(path_props);
            for (uint8_t i = 0; i < PATH_CNT; i++)
            {
                path_t *path = &(globals.paths[i]);
                if ((path->nodes[0] == junction_id || path->nodes[1] == junction_id) && car->path != i)
                {
                    if (path->_dir == path_p->_dir)
                    {
                        path_forward_id = i;
                    }
                    direction_t this_path_props = getPathProperties(junction_id, i);
                    if (this_path_props.dir == left_path_props.dir && this_path_props.horizontal_vertical == left_path_props.horizontal_vertical)
                    {
                        path_left_id = i;
                    }
                }
            }
            if (path_forward_id == -1 && path_left_id == -1)
            {
                continue;
            }
            int8_t next_path_id;
            if (path_forward_id != -1 && path_left_id != -1)
            {
                uint8_t choice = rand() % 2;
                next_path_id = choice ? path_forward_id : path_left_id;
            }
            if (path_forward_id == -1 && path_left_id != -1)
            {
                next_path_id = path_left_id;
            }
            if (path_forward_id != -1 && path_left_id == -1)
            {
                next_path_id = path_forward_id;
            }

            // globals.paths[car->path].
            car->path = next_path_id;
            // car->pos =
        }
    }
}

void runSystems(uint32_t ts)
{
    uint32_t time = ts - globals.last_ts;
    generateCars(ts);
    moveCars(time);
    stopCars();
    renderAll();
}