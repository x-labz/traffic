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
    LOG("components", vPosition.size());

    position_t test = * (position_t * )(vEntities.at(0).components.at(0).component);
    LOG("test:", test.x);

    PC::begin();

    while (PC::isRunning()) {
        if (!PC::update())
            continue;
        // renderAll(  );
        PD::color = rand() % (15);
        position_t pos = *(position_t *)(vEntities.at(0).components.at(0).component) ;
        PD::drawRectangle(pos.x, pos.y, 10, 10);
        
        pos = *(position_t *)(vEntities.at(1).components.at(0).component);
        PD::drawRectangle(pos.x, pos.y, 10, 10);
    }

    return 0;
}