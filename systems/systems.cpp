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

            int8_t id = getInactiveCar();

            if (id == -1)
                continue;

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

        uint8_t path_length = globals.paths[car.path]._len;
        int32_t value = car.pos;
        value += car.dir * CAR_SPEED * (time >> 1);
        if (value > PATH_END_HIGH(path_length) && car.dir == 1)
        {
            value = PATH_END_HIGH(path_length);
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
        uint8_t path_length = path_p->_len;
        if (value == PATH_END_HIGH(path_length) || value == PATH_END_LOW)
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

void delIdFromGen(uint8_t id)
{
    for (uint8_t i = 0; i < GEN_CTN; i++)
    {
        generator_t *generator = &(globals.generators[i]);
        if (generator->lastId == id)
        {
            generator->lastId = -1;
        }
    }
}

int8_t findLastCarIdOnPath(uint8_t path_id, int8_t dir)
{
    uint32_t pos_max = 0;
    int8_t id_max = -1, id_min = -1;
    uint32_t pos_min = 1024 << 8;
    for (uint8_t car_id = 0; car_id != SIZE(globals.cars); car_id++)
    {
        car_t *car = &(globals.cars[car_id]);
        if (!car->isActive || car->path != path_id)
            continue;

        if (car->pos > pos_max)
        {
            pos_max = car->pos;
            id_max = car_id;
        }
        if (car->pos < pos_min)
        {
            pos_min = car->pos;
            id_min = car_id;
        }
    }
    return dir == -1 ? id_max : id_min;
}

dir_t reverseDir(dir_t dir)
{
    return {dir.x * -1, dir.y * -1};
}

void changePath(void)
{
    for (uint8_t i = 0; i != SIZE(globals.cars); i++)
    {
        car_t *car = &(globals.cars[i]);
        if (!car->isActive)
            continue;

        path_t *car_path_p = &(globals.paths[car->path]);
        int32_t value = car->pos;
        uint8_t path_length = car_path_p->_len;
        if (value == PATH_END_HIGH(path_length) || value == PATH_END_LOW)
        {
            uint8_t junction_id = car_path_p->nodes[value == PATH_END_LOW ? 0 : 1];

            int8_t car_dir = car->dir;
            int8_t next_car_dir;

            int8_t path_forward_id = -1;
            int8_t path_left_id = -1;

            dir_t car_path_dir = car_path_p->_dir;
            dir_t left_path_dir = getLeftPathDir(car_dir == -1 ? reverseDir(car_path_dir) : car_path_dir);
            for (uint8_t i = 0; i < PATH_CNT; i++)
            {
                path_t *path = &(globals.paths[i]);
                if ((path->nodes[0] == junction_id || path->nodes[1] == junction_id) && car->path != i)
                {
                    if (abs(path->_dir.x) == abs(car_path_p->_dir.x) && abs(path->_dir.y) == abs(car_path_p->_dir.y))
                    {
                        path_forward_id = i;
                        next_car_dir = car_dir;
                    }

                    if (abs(path->_dir.x) == abs(left_path_dir.x) && abs(path->_dir.y) == abs(left_path_dir.y))
                    {
                        path_left_id = i;
                        next_car_dir = left_path_dir.x == -1 || left_path_dir.y == -1 ? -1 : 1;
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

            path_t next_path = globals.paths[next_path_id];
            int8_t lastCarId = findLastCarIdOnPath(next_path_id, next_car_dir);

            int32_t lastCarPos = -1;
            if (lastCarId > -1)
            {
                lastCarPos = globals.cars[lastCarId].pos;
            }
            if (next_car_dir == -1 && lastCarId != -1 && lastCarPos >= ((next_path._len - PATH_WIDTH) << 8))
            {
                // LOG("dir -1 \n");
                continue;
            }
            if (next_car_dir == 1 && lastCarId != -1 && lastCarPos <= ((PATH_WIDTH) << 8))
            {
                // LOG("dir 1 ", i, " lastid: ", lastCarId, " last pos: ", lastCarPos, " next path id: ", next_path_id, " \n");
                continue;
            }

            car->precedingId = lastCarId;
            car->isStopped = false;
            car->dir = next_car_dir;
            car->path = next_path_id;
            car->pos = next_car_dir == 1 ? (HALF_PATH_WIDTH << 8) : (next_path._len - HALF_PATH_WIDTH) << 8;
            delIdFromGen(i);

            // LOG("CH ", i, " dir: ", car->dir, " pos: ", car->pos >> 8, " pre: ", car->precedingId, "\n");
        }
    }
}

void runSystems(uint32_t ts)
{
    uint32_t time = ts - globals.last_ts;
    generateCars(ts);
    moveCars(time);
    stopCars();
    changePath();
    renderAll();
}