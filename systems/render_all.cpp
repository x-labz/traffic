#include "render_all.h"
#include <LibLog>
#include "components/view.h"

using PD = Pokitto::Display;

void renderNode(position_t pos) {
    //  LOG( "pos:", pos.x, ",", pos.y , "\n" ) ;
    PD::color = 1;
    PD::drawRectangle(pos.x, pos.y, 10, 10);
}

void renderAll( entity_t * items, uint32_t size ) {
    
    for (uint16_t i = 0; i != size; i++) {
        uint32_t volatile entityID = items[i].entityID ;
        // LOG( i,":", entityID , "\n" ) ;
        if ( entityID == 0 ) continue ;
        // 
        // LOG( "rendering:", entityID, "\n" ) ;
        entity_t entity = items[i] ;
        uint32_t viewType = ((view_t*)entity.components[VIEW])->renderType  ;
        // LOG( "view Type:", viewType, "\n" ) ;
        switch (viewType) {
            case JUNCTION: {
                renderNode(*((position_t*)entity.components[POS])) ;
                break;
            }
        }
    }

    
}