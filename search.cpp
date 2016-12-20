#include "mogic.h"
#include "mogicTower.h"
#include "search.h"
#include "eval.h"
#include "helpers.h"
#include <climits>
#include <cassert>
#include "AI.h"

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

int search(const Status& stat, int depth, const set<int>& choiceList, int &bestChoice, int &ret)
{
    if (depth == AIprof::MAX_DEPTH || !stat.hasNext())
        return eval(stat) - depth;

    int maxVal = INT_MIN;

    for (auto p: choiceList)
    {
        if (canTrans(stat, p))
        {
            Status tmpStatus = stat;
            tmpStatus.moveTo(p);
            int curVal = search(tmpStatus, depth + 1, tmpStatus.getNode().adj, p, ret);
			if (maxVal < curVal) 
            {
                maxVal = curVal;
                if (depth == 0)
                    bestChoice = p;
            }
        }

    }

    return ret = maxVal;
}
