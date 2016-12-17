#include "mogicTower.h"
#include <cassert>

Status& trans(Status& stat, GraphNode* target)
{
#ifdef DEBUG
    assert(stat.head == target || stat.head->next.find(target) == stat.head->next.end());
#endif
    return stat;
}