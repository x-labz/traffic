#include <Pokitto.h>
#include <LibLog>
#include "init_ecs.h"
#include "systems/systems.h"
#include <global_store.h>

using PC = Pokitto::Core;
using PD = Pokitto::Display;
using PB = Pokitto::Buttons;

template <typename entity_search_t>
int16_t findEntity(entity_search_t *collection, uint16_t size, /*entity_search_t&&*/ std::function<bool(entity_search_t)> itterator)
{
    uint16_t i = 0;

    if (size < 1)
        return -1;

    do
    {
        if (itterator(collection[i]))
        {
            return i;
        }
        i++;
    } while (i != size);

    return -1;
}

int main()
{

    PD::persistence = true;
    PD::invisiblecolor = 0;

    initEcs();

    uint16_t size = SIZE(entities);

    LOG("started \n");

    int16_t idx = findEntity(componentsPos, SIZE(componentsPos), [](position_t item) -> bool
                             { return item.entityID == 2; });

    LOG("item idx:", idx);

    PC::begin();

    while (PC::isRunning())
    {
        if (!PC::update())
            continue;

        runSystems(entities, size);
    }

    return 0;
}