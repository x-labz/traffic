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
    PC::begin();

    PD::persistence = true;
    PD::invisiblecolor = 0;
   
    PD::color = 13;
    PD::fillRect(0, 0, 219, 175);

    for (uint8_t i = 0; i != 16; i++)
    {
        PD::color = i;
        PD::fillRect(10 + 12 * i, 150, 10, 10);
    }

    LOG("started \n");
    uint32_t ts = PC::getTime();
    initStore(ts);

    
    srand(time(0));
    while (PC::isRunning())
    {
        if (!PC::update())
            continue;

        ts = PC::getTime();
        runSystems(ts);
        globals.last_ts = ts;
    }

    return 0;
}