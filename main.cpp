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
    initStore() ;

    PC::begin();

    while (PC::isRunning())
    {
        if (!PC::update())
            continue;

        uint32_t time = PC::getTime();
        runSystems(time);
    }

    return 0;
}