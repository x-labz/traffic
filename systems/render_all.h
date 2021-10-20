#pragma once

#include <Pokitto.h>
#include "components/pos.h"
#include "components/view.h"
#include "global_store.h"

void renderNode(position_t pos);
void renderPath(int16_t start_x, int16_t start_y, int16_t end_x, int16_t end_y);

void renderAll();
