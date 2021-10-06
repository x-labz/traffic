#include <Pokitto.h>
#include <LibLog>
#include "init_ecs.h"
#include "systems/systems.h"
#include <global_store.h>


using PC = Pokitto::Core;
using PD = Pokitto::Display;
using PB = Pokitto::Buttons;


int main() {

    PD::persistence = true;
    PD::invisiblecolor = 0;
    initEcs();

    LOG("started \n");

    LOG(( * ((position_t * )(entities[0].components[POS]))).y, "\n");
    LOG(( * ((position_t * )(entities[1].components[POS]))).y, "\n");


    PC::begin();

    while (PC::isRunning()) {
        if (!PC::update())
            continue;
        //  renderAll(  );

        // LOG(( * ((position_t * )(entities[0].components[0]))).y, "\n");
        // LOG(( * ((position_t * )(entities[1].components[0]))).y, "\n");

        PD::color = rand() % (15);
        position_t * pos = (position_t * )(entities[0].components[0]);
        PD::drawRectangle(pos->x, pos->y, 10, 10);

        PD::color = rand() % (15);
        pos = (position_t * )(entities[1].components[0]);
        PD::drawRectangle(pos->x, pos->y, 10, 10);
    }

    return 0;
}