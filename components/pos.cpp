#include "pos.h"

position_t fPosition(uint16_t entityID, int16_t x, int16_t y){
    position_t item = { entityID , x , y } ;
    return item;
};