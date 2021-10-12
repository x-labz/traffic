#include "render_all.h"
#include <LibLog>
#include "components/view.h"
#include "components/width.h"
#include "entities/entities.h"


using PD = Pokitto::Display;

void renderNode(position_t * pos_p, width_t * width_p) {
    //  LOG( "pos:", pos.x, ",", pos.y , "\n" ) ;
    PD::color = 1;
    PD::fillRectangle(pos_p->x, pos_p->y, width_p->width, width_p->width);
}

void renderPath(int16_t start_x, int16_t start_y, int16_t w_x, int16_t w_y ) {
    PD::color = 2;
    PD::fillRect(start_x, start_y, w_x  , w_y);
}

void renderCar(int16_t start_x, int16_t start_y) {
    PD::color = 3;
    PD::fillRect(start_x, start_y, 10  , 5);
}

void renderAll(entity_t * items, uint32_t size) {

    for (uint16_t i = 0; i != size; i++) {
        uint32_t volatile entityID = items[i].entityID;
        // LOG( i,":", entityID , "\n" ) ;
        if (entityID == 0) continue;
        // 
        // LOG( "rendering:", entityID, "\n" ) ;
        entity_t entity = items[i];
        uint32_t viewType = ((view_t * ) entity.components[VIEW]) ->renderType;
        // LOG( "view Type:", viewType, "\n" ) ;
        switch (viewType) {
            case JUNCTION:
                {
                    renderNode((position_t * ) entity.components[POS], (width_t * ) entity.components[WIDTH]);
                    break;
                }
            case PATH_RENDER:
                {
                    
                    uint16_t startID = ((path_t * ) entity.components[PATH]) ->start;
                    uint16_t endID = ((path_t * ) entity.components[PATH]) ->end;
                    // LOG("start:", startID, ", end:", endID,"w:", width, "\n");
                    position_t * startPos_p = nullptr;
                    position_t * endPos_p = nullptr;
                    int16_t width = 0 ;
                    for (uint32_t i = 0; i != SIZE(entities); i++) {
                        if (entities[i].entityID == startID) {
                            startPos_p = (position_t * )(entities[i].components[POS]);
                            width = ((width_t * ) entities[i].components[WIDTH])->width ;
                        }
                        if (entities[i].entityID == endID) endPos_p = (position_t * )(entities[i].components[POS]);
                    }
                    if (startPos_p == nullptr || endPos_p == nullptr) {
                        LOG("node not found\n");
                        break;
                    }
                     
                    int16_t startX = startPos_p->x < endPos_p->x ? startPos_p->x : endPos_p->x ;
                    int16_t startY = startPos_p->y < endPos_p->y ? startPos_p->y : endPos_p->y ;
                    
                    int w_x = abs(startPos_p->x - endPos_p->x);
                    int w_y = abs(startPos_p->y - endPos_p->y);
                    
                    bool isHorizontal = startPos_p->y == endPos_p->y ;
                    
                    // LOG("start:", startPos_p->x," ", startPos_p->y, ", end:", endPos_p->x," ", endPos_p->y, "w:", width, "rX:",revX, " ", revY, "\n");
                    if ( isHorizontal ){
                        renderPath(startX + width, startY , w_x - width ,  width  );
                    }
                    else {
                        renderPath(startX , startY + width ,  width , w_y -  width  );
                        // LOG("start:", startX," ", startY, ", w:", w," ",  width,  "\n");
                    }
                    break;
                }
            case CAR_RENDER: {
                position_t * pos = (position_t * )entity.components[POS] ;
                renderCar(pos->x, pos->y) ;
            }
        }
    }


}