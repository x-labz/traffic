#include "systems.h"
#include <LibLog>
#include "render_all.h"
#include "data/store.h"
#include "data/selectors.h"
#include "data/game-types.h"

void generateCars()
{
    for (uint8_t i = 0; i < GEN_CTN; i++)
    {
        generator_t *generator = &(globals.generators[i]);
        path_t *path = &(globals.paths[generator->pathId]);

        int8_t last_car_id = generator->dir == 1 ? path->min_id : path->max_id;

        int16_t dist = (99 << 8);
        if (last_car_id >= 0)
        {
            int16_t last_car_pos = globals.cars[last_car_id].pos;
            dist = generator->dir == 1 ? last_car_pos : (path->_len << 8) - last_car_pos;
            // LOG("last car id:", last_car_id, " pos: ", last_car_pos, " dist:", dist, "\n");
        }
        if (dist < 0)
            LOG("neg dist ", i, dist);

        if (dist > GENERATE_INTERVAL_PX << 8)
        {
            int8_t id = getInactiveCar();

            if (id == -1)
                continue;

            bool isReversed = generator->dir == -1;
            // int8_t dir = (path->_dir.x == 0 ? path->_dir.y : path->_dir.x) * (isReversed ? -1 : 1);
            uint8_t len = path->_len;
            uint16_t pos = isReversed ? (len - 1) << 8 : 0;

            LOG(" GEN:", i, " CAR id:", id, " path:", generator->pathId, " len:", len, " pos:", pos, "\n");
            globals.cars[id] = {
                true,              // isActive
                false,             // isStopped
                generator->dir,    // dir
                generator->pathId, // path
                pos,               // pos
                last_car_id        // preceding
            };

            if (generator->dir == 1)
            {
                path->min_id = id;
            }
            else
            {
                path->max_id = id;
            }
        }
    }
}

void moveCars(uint32_t time)
{
    for (uint8_t i = 0; i != SIZE(globals.cars); i++)
    {
        car_t *car = &(globals.cars[i]);
        if (!car->isActive || car->isStopped)
            continue;

        uint8_t path_length = globals.paths[car->path]._len;
        // LOG("-Move ", "car:", i, " path:", car.path);
        int32_t value = car->pos;
        value += car->dir * CAR_SPEED * (time >> 1);
        if (value > PATH_END_HIGH(path_length) && car->dir == 1)
        {
            value = PATH_END_HIGH(path_length);
            car->isStopped = true;
            LOG("move stopped at:", value, " car id: ", i, "\n");
        }

        if (value < PATH_END_LOW && car->dir == -1)
        {
            value = PATH_END_LOW;
            car->isStopped = true;
            LOG("move stopped at:", value, " car id: ", i, "\n");
        }

        globals.cars[i].pos = value;
    }
}

void stopCars(void)
{
    for (uint8_t i = 0; i != SIZE(globals.cars); i++)
    {
        car_t *car = &(globals.cars[i]);
        if (!car->isActive || car->isStopped)
            continue;

        int32_t value = car->pos;
        path_t *path_p = &(globals.paths[car->path]);
        uint8_t path_length = path_p->_len;

        if (car->precedingId < 0)
            continue;

        car_t *precedingCar = &(globals.cars[car->precedingId]);
        // if (!precedingCar->isStopped)
        //     continue;

        path_t *preceding_car_path = &(globals.paths[precedingCar->path]);
        int32_t preceding_car_dist_from_end = precedingCar->dir == 1 ? precedingCar->pos : ((preceding_car_path->_len << 8) - precedingCar->pos);
        if (precedingCar->path != car->path && precedingCar->isStopped && preceding_car_dist_from_end < (HALF_PATH_WIDTH << 8))
        {
            LOG("preceding path diff ", precedingCar->path, " ", car->path, "\n");
            car->isStopped = true;
        }

        int32_t dist = abs((car->pos >> 8) - (precedingCar->pos >> 8));
        // LOG(" dist ", dist, " car ", (car->pos >> 8), " pre pos ", (precedingCar->pos >> 8), " id ", i, " pre ", car->precedingId, "\n");
        if (dist < CAR_SIZE + CAR_GAP && precedingCar->path == car->path)
        {
            car->isStopped = true;
            car->pos = precedingCar->pos - (((CAR_SIZE + CAR_GAP) << 8) * car->dir);
            LOG("CAR stopped at:", car->pos, " car id: ", i, "\n");
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
        if (!car->isActive || !car->isStopped)
            continue;

        path_t *car_path_p = &(globals.paths[car->path]);
        int32_t value = car->pos;
        uint8_t orig_path_id = car->path;
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
            // LOG("LEFT path dir:", left_path_dir.x, " ", left_path_dir.y, "\n");
            for (uint8_t path_i = 0; path_i < PATH_CNT; path_i++)
            {
                path_t *path = &(globals.paths[path_i]);
                if ((path->nodes[0] == junction_id || path->nodes[1] == junction_id) && car->path != path_i)
                {
                    dir_t path_dir = path->nodes[1] == junction_id ? reverseDir(path->_dir) : path->_dir;
                    LOG("path dir:", path_dir.x, " ", path_dir.y, " - ");

                    if (path_dir.x == car_path_p->_dir.x && path_dir.y == car_path_p->_dir.y)
                    {
                        path_forward_id = path_i;
                    }

                    if (path_dir.x == left_path_dir.x && path_dir.y == left_path_dir.y)
                    {
                        path_left_id = path_i;
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
                next_car_dir = choice ? car_dir : (left_path_dir.x == -1 || left_path_dir.y == -1 ? -1 : 1);
                LOG("CH choice:", choice, "\n");
            }
            if (path_forward_id == -1 && path_left_id != -1)
            {
                next_path_id = path_left_id;
                next_car_dir = left_path_dir.x == -1 || left_path_dir.y == -1 ? -1 : 1;
                LOG("CH choice: left", "\n");
            }
            if (path_forward_id != -1 && path_left_id == -1)
            {
                next_path_id = path_forward_id;
                next_car_dir = car_dir;
                LOG("CH choice: fw", "\n");
            }

            path_t *next_path = &(globals.paths[next_path_id]);
            int8_t lastCarId = next_car_dir == 1 ? next_path->min_id : next_path->max_id;

            int32_t lastCarPos = -1;
            if (lastCarId > -1)
            {
                lastCarPos = globals.cars[lastCarId].pos;
            }
            if (next_car_dir == -1 && lastCarId != -1 && lastCarPos >= ((next_path->_len - HALF_PATH_WIDTH) << 8))
            {
                LOG("dir = -1, last car pos: ", lastCarPos >> 8, " \n");
                continue;
            }
            if (next_car_dir == 1 && lastCarId != -1 && lastCarPos <= ((HALF_PATH_WIDTH) << 8))
            {
                LOG("dir = 1, last car pos: ", lastCarPos >> 8, " \n");
                continue;
            }

            car->precedingId = lastCarId;
            car->isStopped = false;
            car->dir = next_car_dir;
            car->path = next_path_id;
            if (next_path_id == path_forward_id)
            {
                car->pos = next_car_dir == 1 ? (-HALF_PATH_WIDTH * 256) : (next_path->_len + HALF_PATH_WIDTH) << 8;
            }
            else
            {
                car->pos = next_car_dir == 1 ? (HALF_PATH_WIDTH << 8) : (next_path->_len - HALF_PATH_WIDTH) << 8;
            }
            if (next_car_dir == 1)
            {
                next_path->min_id = i;
            }
            else
            {
                next_path->max_id = i;
            }
            if (car_path_p->min_id == i)
            {
                car_path_p->min_id = findLastCarIdOnPath(orig_path_id, car_dir);
            }
            if (car_path_p->max_id == i)
            {
                car_path_p->max_id = findLastCarIdOnPath(orig_path_id, car_dir);
            }

            LOG("CH ", i, " dir: ", car->dir, " pos: ", car->pos >> 8, " pre: ", car->precedingId, "\n");
        }
    }
}

void recycleCars()
{
    for (uint8_t car_i = 0; car_i != SIZE(globals.cars); car_i++)
    {
        car_t *car_p = &(globals.cars[car_i]);
        if (!car_p->isActive || !car_p->isStopped)
            continue;

        for (uint8_t drain_i = 0; drain_i < DRAIN_CNT; drain_i++)
        {
            drain_t *drain_p = &(globals.drains[drain_i]);
            // LOG("drainn check ", car_i, "dir: ", drain_p->dir, car_p->dir, " path id:", car_p->path, drain_p->path_id);
            if (car_p->path == drain_p->path_id && drain_p->dir == car_p->dir)
            {
                car_p->isActive = false;
                LOG("drain ", car_i, '\n');
            }
        }
    }
}

void runSystems(uint32_t ts)
{
    uint32_t time = ts - globals.last_ts;
    generateCars();
    moveCars(time);
    stopCars();
    changePath();
    recycleCars();
    renderAll();
}