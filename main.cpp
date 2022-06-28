#include <Pokitto.h>
#include <LibLog>

#include <data/store.h>
#include <systems/systems.h>

using PC = Pokitto::Core;
using PD = Pokitto::Display;
using PB = Pokitto::Buttons;
// using PS = Pokitto::Sound ;

int main()
{
    // PS::ampEnable(1);

    PD::persistence = true;
    PD::invisiblecolor = 0;

    LOG("started \n");
    initStore();
    uint32_t ts = PC::getTime();

    PC::begin();

    while (PC::isRunning())
    {
        if (!PC::update())
            continue;

        ts = PC::getTime();
        runSystems(ts- globals.last_ts);
        globals.last_ts = ts;
    }
    
    return 0;
}