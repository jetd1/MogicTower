#include "mogicTower.h"
#include "routine.h"
#include <cassert>
#include "init.h"
#include "helpers.h"


bool isEnd(const Status &stat)
{
	return false;
}

string getRoute(const Status& stat, GraphNode* choice)
{
#ifdef DEBUG
    assert(stat.cur->next.find(choice) != stat.cur->next.end());
#endif
    return "w";
}

void moveTo(const GraphNode* target, Status& stat, bool update)
{
#ifdef DEBUG
    assert(!target->empty);
#endif

    MapObj type = target->getType();
    if (type == safeBlock)
    {
        auto& player = globalMogicTower.player;
        Position tPos = target->getPos();
        player.acquire(target->obj);
        player.moveTo(tPos);

        auto& colorMap = globalMogicTower.colorMap;
        auto& map = globalMogicTower.mapContent;
        int tColor = colorMap[tPos.x][tPos.y];
        for (int i = 0; i < MAP_LENGTH; ++i)
            for (int j = 0; j < MAP_WIDTH; ++j)
                if (colorMap[i][j] == tColor)
                    map[i][j] = road;
    }
    else if (isMonster(type))
    {
        auto& player = globalMogicTower.player;
        Position tPos = target->getPos();
        assert(player.fight(type));
        player.moveTo(tPos);
        globalMogicTower.mapContent[tPos.x][tPos.y] = road;
        for (auto itr = target->next.begin(); itr != target->next.end(); ++itr)
            if ((*itr)->getType() == safeBlock && !target->empty)
                moveTo(*itr, stat, false);
    }
    else if (isDoor(type))
    {
        auto& player = globalMogicTower.player;
        Position tPos = target->getPos();
        player.useKey(keyType(type));
        player.moveTo(tPos);
        globalMogicTower.mapContent[tPos.x][tPos.y] = road;
        for (auto itr = target->next.begin(); itr != target->next.end(); ++itr)
            if ((*itr)->getType() == safeBlock && !target->empty)
                moveTo(*itr, stat, false);
    }
    else
        throw runtime_error("Invalid Target!");

    if (update)
        stat = getStatus(globalMogicTower);
}