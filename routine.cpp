#include "mogicTower.h"
#include "routine.h"
#include <cassert>
#include "init.h"
#include "helpers.h"
#include "damage.h"


bool isEnd(const Status &stat) //判断结束，在搜索完之后调用
{
	//有boss且boss已被访问或再也不能访问任何一个邻接怪或邻接门
	auto adj = stat.getNode().adj;
	for(auto itr = adj.begin(); itr != adj.end(); ++itr)
	{
		//if((*itr)->getType() == boss && (*itr)->empty)
		//{
		//	ret = true;
		//	break;
		//}
        auto type = stat.getNode(*itr).getType();
        if (isMonster(type))
		{
			int damage = getDamage(stat.player, globalMogicTower.monsterInfo[type]);
			if (damage != 999999999 && damage > 0)
				return false;
		}
		if(isKey(type))
		{
			if (stat.player.getKeyCount(type) > 0)
				return false;
		}
	}
	return true;
}

string getRoute(const Status& stat, GraphNode* choice)
{
#ifdef DEBUG
    assert(stat.getNode().adj.find(choice->getIndex()) != stat.getNode().adj.end());
#endif
    return "w";
}

void moveTo(int targetIdx, Status& stat, bool update)
{
    GraphNode& target = stat.getNode(targetIdx);
#ifdef DEBUG
    assert(!target.empty);
#endif

    MapObj type = target.getType();
    if (type == safeBlock)
    {
        auto& player = globalMogicTower.player;
        Position tPos = target.getPos();
        player.acquire(target.obj);
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
        Position tPos = target.getPos();
        assert(player.fight(type));
        player.moveTo(tPos);
        globalMogicTower.mapContent[tPos.x][tPos.y] = road;
        for (auto itr = target.adj.begin(); itr != target.adj.end(); ++itr)
            if (stat.getNode(*itr).getType() == safeBlock && !target.empty)
                moveTo(*itr, stat, false);
    }
    else if (isDoor(type))
    {
        auto& player = globalMogicTower.player;
        Position tPos = target.getPos();
        player.useKey(keyType(type));
        player.moveTo(tPos);
        globalMogicTower.mapContent[tPos.x][tPos.y] = road;
        for (auto itr = target.adj.begin(); itr != target.adj.end(); ++itr)
            if (stat.getNode(*itr).getType() == safeBlock && !target.empty)
                moveTo(*itr, stat, false);
    }
    else
        throw runtime_error("Invalid Target!");

    if (update)
        stat = getStatus(globalMogicTower);
}