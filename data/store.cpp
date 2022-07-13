#include "store.h"

#include "../utils/utils.h"

global_t globals;

path_t genPath(uint8_t j1_id, uint8_t j2_id)
{
    junction_t *j1 = &(globals.junctions[j1_id]);
    junction_t *j2 = &(globals.junctions[j2_id]);

    dir_t dir = {getSgn(j2->x - j1->x),
                 getSgn(j2->y - j1->y)};
    uint8_t len = j1->x == j2->x ? j2->y - j1->y : j2->x - j1->x;

    return {{j1_id, j2_id}, dir, len, -1, -1};
}

// path nodes always defined from top to bottom, or left to right
void initStore(uint32_t ts)
{

    globals.junctions[0] = {100, 0};
    globals.junctions[1] = {100, 100};
    globals.junctions[2] = {100, 170};
    globals.junctions[3] = {0, 100};

    // globals.junctions[4] = {60, 20};

    globals.generators[0] = {1, 0};
    // globals.generators[1] = {1, 0, 0, -1};

    globals.paths[0] = genPath(0, 1);
    globals.paths[1] = genPath(1, 2);
    globals.paths[2] = genPath(3, 1);

    // globals.paths[3] = genPath(1, 4);

    globals.drains[0] = {1, 1};
}