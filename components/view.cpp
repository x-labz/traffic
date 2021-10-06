#include "view.h"

view_t fView(uint16_t entityID, renderTypes renderType){
    view_t item = { entityID , renderType } ;
    return item;
};