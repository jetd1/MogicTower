#include "mogicTower.h"
#include <cassert>
#include "helpers.h"

int trans(Status& stat, GraphNode* target)
{
#ifdef DEBUG
    assert(stat.head == target || stat.head->next.find(target) == stat.head->next.end());
#endif
    if (target->empty)
    {
        stat.head = target;
        return -1;
    }

    MapObj type = target->type;

    if (isMonster(type))
    {
        if (!stat.player.fight(type))
            return 0;
        stat.head = target;
        stat.player.acquire(target->obj);
        target->empty = true;
        return 1;
    }

    if (isDoor(type))
    {
        if (!stat.player.getKeyCount(doorType(type)))
            return 0;
        stat.head = target;
        stat.player.acquire(target->obj);
        target->empty = true;
        return 2;
    }

#ifdef DEBUG
    assert(type == safeBlock);
#endif

    stat.head = target;
    stat.player.acquire(target->obj);
    target->empty = true;
    return 3;
}
