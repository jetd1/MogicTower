#include "mogic.h"
#include "mogicTower.h"
#include "search.h"
#include "eval.h"
#include "routine.h"
#include "helpers.h"
#include <climits>

static bool canTrans(const Status& stat, int targetIdx)
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
