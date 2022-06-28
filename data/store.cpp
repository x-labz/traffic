#include "store.h"
#include "../utils/init-utils.h"

global_t globals;

void initStore()
{


    globals.junctions[0] = {10, 10, 0};
    globals.junctions[1] = {10, 100, 0};
    globals.junctions[2] = {100, 10, 0};

    globals.paths[0] = {
        {0, 1},
        getDir(globals.junctions[0], globals.junctions[1])};

    globals.paths[1] = {
        {0, 2},
        getDir(globals.junctions[0], globals.junctions[2])};

    globals.cars[0] = {
        true,
        VERTICAL,
        0,
        0
    };
}