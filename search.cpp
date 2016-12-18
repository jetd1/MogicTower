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
int search(Status& stat, int depth, int &bestChoice)
{
    if (depth == MAX_DEPTH)
        return eval(stat);

    //PlayerInfo backupPlayer = stat.player;
    //GraphNode* originalPos = stat.cur;
    int maxVal = 0;

    auto& adj = stat.cur->adj;
    vector<int> adjVector;
    for (auto itr = adj.begin(); itr != adj.end(); ++itr)
        adjVector.push_back(*itr);
    size_t adjCount = adjVector.size();
    for (size_t i = 0; i < adjCount; ++i)
    {
        int p = adjVector[i];
        //bool isEmpty = (*itr)->empty;
        const Tower backUpTower = globalMogicTower;
        const Status backUpStatus = stat;
        if (trans(stat, p))
        {
            int curVal = search(stat, depth + 1, p);
            if (maxVal < curVal)
            {
                maxVal = curVal;
                if (depth == 0)
                    bestChoice = p;
            }
            globalMogicTower = backUpTower;
            stat = backUpStatus;
            //restore(stat, isEmpty, backupPlayer, originalPos);
        }

    }

    return maxVal;
}

