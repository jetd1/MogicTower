#include "mogicTower.h"
#include <cassert>
#include "helpers.h"

int trans(Status& stat, int targetIdx)
{
#ifdef DEBUG
    assert(stat.getNodePtr()->adj.find(targetIdx) != stat.getNodePtr()->adj.end());
#endif
    GraphNode& target = stat.getNode(targetIdx);
    if (target.empty)
    {
        stat.curIdx = targetIdx;
        return -1;
    }

    MapObj type = target.getType();

    if (isMonster(type))
    {
        if (!stat.player.fight(type))
            return 0;

        stat.curIdx = targetIdx;
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
        stat.curIdx = targetIdx;
        stat.player.blockCount++;
        stat.player.moveTo(target.getPos());
        target.empty = true;

        return 2;
    }

#ifdef DEBUG
    assert(type == safeBlock);
#endif

    stat.curIdx = targetIdx;
    stat.player.acquire(target.obj);
    stat.player.blockCount += target.blockCount;
    stat.player.moveTo(target.getPos());
    target.empty = true;
    return 3;
}

bool canTrans(const Status& stat, int targetIdx)
{
#ifdef DEBUG
    assert(!stat.getNode(targetIdx).empty);
    assert(stat.getNode().adj.find(targetIdx) != stat.getNode().adj.end());
#endif
    const GraphNode& target = stat.getNode(targetIdx);

    MapObj type = target.getType();

    if (isMonster(type))
        return stat.player.canBeat(type);

    if (isDoor(type))
        return stat.player.getKeyCount(keyType(type)) > 0;
           

#ifdef DEBUG
    assert(type == safeBlock);
#endif

    return true;
}