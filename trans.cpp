#include "mogicTower.h"
#include <cassert>
#include "helpers.h"

int trans(Status& stat, GraphNode* target)
{
#ifdef DEBUG
    assert(stat.cur == target || stat.cur->next.find(target) != stat.cur->next.end());
#endif
    if (target->empty)
    {
        stat.cur = target;
        return -1;
    }

    MapObj type = target->getType();

    if (isMonster(type))
    {
        if (!stat.player.fight(type))
            return 0;

        stat.cur = target;
        stat.player.blockCount++;
        stat.player.moveTo(target->getPos());
        target->empty = true;
        
        return 1;
    }

    if (isDoor(type))
    {
        if (!stat.player.getKeyCount(keyType(type)))
            return 0;
        stat.player.useKey(keyType(type));
        stat.cur = target;
        stat.player.blockCount++;
        stat.player.moveTo(target->getPos());
        target->empty = true;

        return 2;
    }

#ifdef DEBUG
    assert(type == safeBlock);
#endif

    stat.cur = target;
    stat.player.acquire(target->obj);
    stat.player.blockCount += target->blockCount;
    stat.player.moveTo(target->getPos());
    target->empty = true;
    return 3;
}
