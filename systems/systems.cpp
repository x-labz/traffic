#include "systems.h"
// #include <LibLog>
#include "render_all.h"
#include "data/store.h"

void moveCars(uint32_t time) {
    for (uint8_t i = 0; i != SIZE(globals.cars); i++)
    {
        car_t car = globals.cars[i];
        if (!car.isActive)
            continue;

        uint16_t value = car.pos ;
        value += 1 ;
        if(value > 128) {
            value = 128;
        }
        globals.cars[i].pos = (uint8_t)value ;
    }
}

void runSystems(uint32_t time)
{
    moveCars(time) ;
    renderAll();
}