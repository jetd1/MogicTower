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

void moveTo(const GraphNode* target, Status& mogicTower)
{
#ifdef DEBUG
    assert(!target->empty);
#endif

    MapObj type = target->getType();
    if (type == safeBlock)
    {

    }
    else if (isMonster(type))
    {
        auto& player = globalMogicTower.player;
        Position tPos = target->getPos();
        assert(player.fight(target->getType()));
        player.moveTo(tPos);
        globalMogicTower.mapContent[tPos.x][tPos.y] = road;

    }
    else if (isDoor(type))
    {

    }
    else
        throw runtime_error("Invalid Target!");

    mogicTower = getStatus(globalMogicTower);
}