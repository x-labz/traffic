#pragma once

#include "global_store.h"
#include "components/pos.h"
#include "components/view.h"
#include "components/junction.h"
#include "init_ecs.h"

void initJunctions(genPointers *poi);
void initPaths(genPointers *poi);
void initCars(genPointers *poi);