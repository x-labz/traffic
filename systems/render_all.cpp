#include "render_all.h"
#include <LibLog>
#include "components/view.h"
#include "components/junction.h"

#include "utils/collections.h"

using PD = Pokitto::Display;

void renderNode(uint16_t id)
{
    position_t pos;
    bool success = findEntity(
        globals.componentsPos,
        SIZE(globals.componentsPos), &pos, (std::function<bool(position_t)>)[id](position_t item)->bool { return item.entityID == id; });
    if (!success)
    {
        LOG("can't find pos:", id, "\n");
        return;
    }
    junction_t junc;
    success = findEntity(
        globals.componentsJunction,
        SIZE(globals.componentsJunction), &junc, (std::function<bool(junction_t)>)[id](junction_t item)->bool { return item.entityID == id; });
    if (!success)
    {
        LOG("can't find junction:", id, "\n");
        return;
    }

    PD::color = 1;
    PD::fillRectangle(pos.x, pos.y, junc.width, junc.width);
}

void renderPath(uint16_t id)
{
    path_t path;
    bool success = findEntity(
        globals.componentsPath,
        SIZE(globals.componentsPath), &path, (std::function<bool(path_t)>)[id](path_t item)->bool { return item.entityID == id; });
    if (!success)
    {
        LOG("can't find path:", id, "\n");
        return;
    }

    uint16_t startID = path.start;
    uint16_t endID = path.end;
    // LOG("start:", startID, ", end:", endID,"w:", width, "\n");

    junction_t junc;
    success = findEntity(
        globals.componentsJunction,
        SIZE(globals.componentsJunction), &junc, (std::function<bool(junction_t)>)[startID](junction_t item)->bool { return item.entityID == startID; });
    if (!success)
    {
        LOG("can't find junction:", id, "\n");
        return;
    }

    position_t startPos;
    position_t endPos;
    int16_t width = junc.width;
    success = findEntity(
        globals.componentsPos,
        SIZE(globals.componentsPos), &startPos, (std::function<bool(position_t)>)[startID](position_t item)->bool { return item.entityID == startID; });
    if (!success)
    {
        LOG("can't find start pos:", id, "\n");
        return;
    }
    success = findEntity(
        globals.componentsPos,
        SIZE(globals.componentsPos), &endPos, (std::function<bool(position_t)>)[endID](position_t item)->bool { return item.entityID == endID; });
    if (!success)
    {
        LOG("can't find end pos:", id, "\n");
        return;
    }

    int16_t startX = startPos.x < endPos.x ? startPos.x : endPos.x;
    int16_t startY = startPos.y < endPos.y ? startPos.y : endPos.y;

    int w_x = abs(startPos.x - endPos.x);
    int w_y = abs(startPos.y - endPos.y);

    bool isHorizontal = startPos.y == endPos.y;

    PD::color = 2;
    // LOG("start:", startPos_p->x," ", startPos_p->y, ", end:", endPos_p->x," ", endPos_p->y, "w:", width, "rX:",revX, " ", revY, "\n");
    if (isHorizontal)
    {
        PD::fillRect(startX + width, startY, w_x - width, width);
    }
    else
    {
        PD::fillRect(startX, startY + width, width, w_y - width);
    }
}

void renderCar(uint16_t id)
{

    position_t pos;
    bool success = findEntity(
        globals.componentsPos,
        SIZE(globals.componentsPos), &pos, (std::function<bool(position_t)>)[id](position_t item)->bool { return item.entityID == id; });
    if (!success)
    {
        LOG("can't find car pos:", id, "\n");
        return;
    }

    PD::color = 3;
    PD::fillRect(pos.x, pos.y, 10, 5);
}

void renderAll()
{
    // LOG("\n");
    for (uint16_t id = 1; id <= globals.entityCount; id++)
    {
        view_t view;
        bool success = findEntity(
            globals.componentsView,
            SIZE(globals.componentsView), &view, (std::function<bool(view_t)>)[id](view_t item)->bool { return item.entityID == id; });
        if (!success)
        {
            LOG("view not found:", id, "\n");
            continue;
        }

        uint32_t viewType = view.renderType;
        // LOG("view found:", id, ",", view.renderType, " ");

        switch (viewType)
        {
        case JUNCTION_RENDERER:
        {
            renderNode(id);
            break;
        }
        case PATH_RENDER:
        {
            renderPath(id);
            break;
        }
        case CAR_RENDER:
        {
            // LOG("CAR:", id, "\n");
            renderCar(id);
        }
        }
    }
}