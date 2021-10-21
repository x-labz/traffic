#include <Pokitto.h>
#include <LibLog>
#include "init_ecs.h"
#include "systems/systems.h"
#include <global_store.h>

#include "utils/collections.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;
using PB = Pokitto::Buttons;
// using PS = Pokitto::Sound ;

int main()
{
    // PS::ampEnable(1);

    PD::persistence = true;
    PD::invisiblecolor = 0;

    initEcs();

    uint16_t pos_size = SIZE(globals.componentsPos);

    LOG("started \n");
    LOG("pos size :", pos_size, "\n");

    position_t result;
    bool success = findEntity(
        globals.componentsPos, SIZE(globals.componentsPos), &result, (std::function<bool(position_t)>)[](position_t item)->bool { return item.entityID == 2; });

    LOG("item success:", success, "\n");
    if (success)
    {
        LOG(result.x, "\n");
    }

    LOG("END");

    PC::begin();

    while (PC::isRunning())
    {
        if (!PC::update())
            continue;

        runSystems();
    }

    return 0;
}