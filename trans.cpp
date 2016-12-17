#include "mogicTower.h"
#include <cassert>

bool trans(Status& stat, GraphNode* target)
{
#ifdef DEBUG
    assert(stat.head == target || stat.head->next.find(target) == stat.head->next.end());
#endif
     
}