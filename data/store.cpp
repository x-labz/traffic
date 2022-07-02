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

    return {{j1_id, j2_id}, dir, len};
}

// path nodes always defined from top to bottom, or left to right
void initStore(uint32_t ts)
{

    globals.junctions[0] = {10, 10, NONE};
    globals.junctions[1] = {10, 100, NONE};
    globals.junctions[2] = {100, 10, NONE};
    globals.junctions[3] = {100, 100, NONE};
    globals.junctions[4] = {150, 10, NONE};

    globals.generators[0] = {0, 0, 0, -1};
    globals.generators[1] = {1, 0, 0, -1};

    globals.paths[0] = genPath(0, 1);
    globals.paths[1] = genPath(0, 2);
    globals.paths[2] = genPath(2, 3);
    globals.paths[3] = genPath(2, 4);
}