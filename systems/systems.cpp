#include "systems.h"


using PD = Pokitto::Display;

void renderNode(position_t pos) {
    PD::color = rand() % (15);
    PD::drawRectangle(pos.x, pos.y, 10, 10);
}

void renderAll() {
    // for (auto i = 0; i != data.size(); i++) {

    //     entity_t entity = data.at(i);
    //     // vector < componentEntry_t > ::iterator view_it = find_if(entity.components.begin(), entity.components.end(), [](componentEntry_t & component) {
    //     //     return component.type == VIEW;
    //     // });

    //     // if (view_it == entity.components.end()) continue;

    //     // componentEntry_t componentEntry = * view_it;
    //     // view_t view = *(view_t*)(componentEntry.component);

    //     // if (view.renderType == JUNCTION) {
    //     //     vector < componentEntry_t > ::iterator it = find_if(entity.components.begin(), entity.components.end(), [](componentEntry_t & component) {
    //     //         return component.type == POS;
    //     //     });
    //     //     if (it == entity.components.end()) continue;
    //     //     componentEntry_t componentEntryPos = entity.components.at(0) ; //* it;
    //     //     position_t pos = *(position_t *)(componentEntryPos.component) ;

    //     //     renderNode( pos );
    //     // }

    //     componentEntry_t componentEntryPos = entity.components.at(0); //* it;
    //     position_t pos = * (position_t * )(componentEntryPos.component);

    //     renderNode(pos);
    // }
    renderNode(*(position_t *)(vEntities.at(0).components.at(0).component));
    renderNode(*(position_t *)(vEntities.at(1).components.at(0).component));
    
}