#pragma once 

#include <Pokitto.h>

enum componentTypes { POS, VIEW };

struct componentEntry_t {
    componentTypes type ;
    void * component ;
};

struct entity_t {
    uint16_t entityID;
    vector < componentEntry_t > components;
};


