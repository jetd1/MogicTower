#include "mogic.h"
#include "mogicTower.h"
#include "search.h"
#include <vector>

// TODO: Finish This Shit
int search(const Status& stat, int depth)
{
    //if (depth == MAX_DEPTH)
    //    return eval(stat);

    //size_t nodeCount = stat->next.size();
    //for (size_t i = 0; i < nodeCount; ++i)
    //{
    //    Status& cur = stat->next[i];
    //    trans(stat, cur);
    //    search(cur, depth + 1);
    //    restore();
    //}

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