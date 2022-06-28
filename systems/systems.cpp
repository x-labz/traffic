#include "systems.h"
#include <LibLog>
#include "render_all.h"
#include "data/store.h"
#include "data/selectors.h"

void moveCars(uint32_t time)
{
    // LOG("delta:", time) ;
    for (uint8_t i = 0; i != SIZE(globals.cars); i++)
    {
        car_t car = globals.cars[i];
        if (!car.isActive)
            continue;

        uint8_t path_lenght = getPathLenght(&(globals.paths[car.path]));
        int32_t value = car.pos;
        value += (car.dir ? 1 : -1) * CAR_SPEED * (time>>1);
        if (value > 256 * (path_lenght))
        {
            value = 256 * (path_lenght);
            car.dir = !car.dir;
            value -= 1;
        }

        if (value < 0)
        {
            value = 0;
        }

        globals.cars[i].pos = value;
        globals.cars[i].dir = car.dir;
    }
}

void runSystems(uint32_t time)
{
    moveCars(time);
    renderAll();
}