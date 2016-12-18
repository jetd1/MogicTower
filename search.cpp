#include "mogic.h"
#include "mogicTower.h"
#include "search.h"
#include "trans.h"
#include "eval.h"
#include "trans.h"
#include <vector>


static void restore(Status& stat, bool isEmpty, PlayerInfo backupPlayer, int originalIdx)
{
    stat.player = backupPlayer;
    stat.getNodePtr()->empty = isEmpty;
    stat.curIdx = originalIdx;
}


int search(Status& stat, int depth, int &bestChoice)
{
    if (depth == MAX_DEPTH || isEnd(stat))
        return eval(stat);

    //PlayerInfo backupPlayer = stat.player;
    //GraphNode* originalPos = stat.cur;
    int maxVal = INT_MIN;

    const Tower backUpTower = globalMogicTower;
    const Status backUpStatus = stat;

    auto& adj = stat.getNodePtr()->adj;
    vector<int> adjVector;
    for (auto itr = adj.begin(); itr != adj.end(); ++itr)
        adjVector.push_back(*itr);
    size_t adjCount = adjVector.size();

    for (size_t i = 0; i < adjCount; ++i)
    {
        int p = adjVector[i];
        //bool isEmpty = (*itr)->empty;

        if (canTrans(stat, p))
        {
            moveTo(p, stat);
            int curVal = search(stat, depth + 1, p);
			if (maxVal < curVal) {
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
