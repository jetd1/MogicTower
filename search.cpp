#include "mogic.h"
#include "mogicTower.h"
#include "search.h"
#include <vector>

// TODO: Finish This Shit
int search(const Status& stat, int depth)
{
    if (depth == MAX_DEPTH)
        return eval(stat);

    auto& next = stat.head->next;
    size_t nextCount = next.size();
    for (size_t i = 0; i < nextCount; ++i)
    {
        
    }
    

    return 0;
}

int eval(const Status& stat)
{
    //int tmpRank = 0;
    //tmpRank += stat.player->getATK() * ATK_Multiple;
    //tmpRank += stat.player->getHP() * HP_Multiple;
    //tmpRank += stat.player->getDEF() * DEF_Multiple;
    //tmpRank += stat.player->getMDEF() * MDEF_Multiple;

    ///* TODO: 对player所在位置连通性对权值的影响 */
    //return tmpRank;

    return 0;
}