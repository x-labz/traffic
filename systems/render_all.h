#pragma once

#include <Pokitto.h>
#include "../data/game-types.h"

#define PATH_WIDTH 10 

void renderJunction(junction_t junction);
void renderPath(path_t path);
void renderCar(uint16_t id);

void renderAll();
