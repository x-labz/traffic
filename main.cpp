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
    
    uint16_t size = SIZE( entities ) ;

    LOG("started \n");

    PC::begin();

    while (PC::isRunning()) {
        if (!PC::update())
            continue;


        runSystems( entities, size );
    }

    return 0;
}