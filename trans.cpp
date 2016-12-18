#include "mogicTower.h"
#include <cassert>
#include "helpers.h"

int trans(Status& stat, int targetIdx)
{
#ifdef DEBUG
    assert(stat.cur->getIndex() == targetIdx || stat.cur->adj.find(targetIdx) != stat.cur->adj.end());
#endif
    GraphNode& target = stat.getNode(targetIdx);
    if (target.empty)
    {
        stat.cur = stat.getNodePtr(targetIdx);
        return -1;
    }

    MapObj type = target.getType();

    if (isMonster(type))
    {
        if (!stat.player.fight(type))
            return 0;

        stat.cur = stat.getNodePtr(targetIdx);
        stat.player.blockCount++;
        stat.player.moveTo(target.getPos());
        target.empty = true;
        
        return 1;
    }

    if (isDoor(type))
    {
        if (!stat.player.getKeyCount(keyType(type)))
            return 0;
        stat.player.useKey(keyType(type));
        stat.cur = stat.getNodePtr(targetIdx);
        stat.player.blockCount++;
        stat.player.moveTo(target.getPos());
        target.empty = true;

        return 2;
    }

#ifdef DEBUG
    assert(type == safeBlock);
#endif

    stat.cur = stat.getNodePtr(targetIdx);
    stat.player.acquire(target.obj);
    stat.player.blockCount += target.blockCount;
    stat.player.moveTo(target.getPos());
    target.empty = true;
    return 3;
}
