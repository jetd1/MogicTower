#include "mogic.h"
#include "mogicTower.h"
#include "search.h"
#include "trans.h"
#include "eval.h"


static void restore(Status& stat, bool isEmpty, PlayerInfo backupPlayer, GraphNode* originalPos)
{
    stat.player = backupPlayer;
    stat.cur->empty = isEmpty;
    stat.cur = originalPos;
}

// TODO: 实现Empty节点不算层数(需要记录回溯)
int search(Status& stat, int depth, GraphNode* &bestChoice)
{
    if (depth == MAX_DEPTH)
        return eval(stat);

    PlayerInfo backupPlayer = stat.player;
    GraphNode* originalPos = stat.cur;
    int maxVal = 0;

    auto& next = stat.cur->next;
    for (auto itr = next.begin(); itr != next.end(); ++itr)
    {
        GraphNode *p = *itr;
        bool isEmpty = (*itr)->empty;
        if (trans(stat, *itr))
        {
            int curVal = search(stat, depth + 1, p);
            if (maxVal < curVal)
            {
                maxVal = curVal;
                if (depth == 0)
                    bestChoice = p;
            }
            restore(stat, isEmpty, backupPlayer, originalPos);
        }

    }

    return maxVal;
}

