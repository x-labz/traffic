#pragma once

#include <Pokitto.h>
#include "components/pos.h"
#include "components/view.h"
#include "global_store.h"

void renderNode(uint16_t id);
void renderPath(uint16_t id);
void renderCar(uint16_t id);

void renderAll();
