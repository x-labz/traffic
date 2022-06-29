#include "store.h"
#include "../utils/init-utils.h"
#include "data/selectors.h"

global_t globals;

void initStore(uint32_t ts)
{

    globals.junctions[0] = {10, 10, 0, NONE};
    globals.junctions[1] = {10, 100, 0, NONE};
    globals.junctions[2] = {100, 10, 0, NONE};

    globals.generators[0] = {0, 0, ts};
    globals.generators[1] = {1, 0, ts};

    globals.paths[0] = {
        {0, 1},
        getDir(globals.junctions[0], globals.junctions[1]),
        0,
        0};

    globals.paths[1] = {
        {0, 2},
        getDir(globals.junctions[0], globals.junctions[2]),
        0,
        0};

    for (uin8_t i = 0; i < PATH_CNT; i++)
    {
        globals.paths[i].stop_high = getPathLenght(&(globals.paths[i]))
    }
}