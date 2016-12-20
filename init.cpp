#include "helpers.h"
#include "init.h"
#include "graph.h"
#include <queue>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include "routine.h"

static const Status& readInitStatus(Status& stat)
{
    ifstream fin("input.txt");
    if (!fin)
    {
        cout << "无法打开input.txt，将从stdin读入..." << endl;
        int ign;
        cin >> ign >> ign >> ign;

        for (size_t i = 0; i < MAP_LENGTH; ++i)
            for (size_t j = 0; j < MAP_LENGTH; ++j)
                cin >> stat.mogicTower.mapContent[i][j];

        for (size_t i = 0; i < 5; i++)
            cin >> stat.mogicTower.buff[i];

        int monsterTypeCount;
        cin >> monsterTypeCount;
        while (monsterTypeCount--)
        {
            MapObj key;
            Monster tmpMon;
            cin >> key >> tmpMon;
            stat.mogicTower.monsterInfo[key] = tmpMon;
        }

        cin >> stat.player;
    }
    else
    {
        int ign;
        fin >> ign >> ign >> ign;

        for (size_t i = 0; i < MAP_LENGTH; ++i)
            for (size_t j = 0; j < MAP_LENGTH; ++j)
                fin >> stat.mogicTower.mapContent[i][j];

        for (size_t i = 0; i < 5; i++)
            fin >> stat.mogicTower.buff[i];

        int monsterTypeCount;
        fin >> monsterTypeCount;
        while (monsterTypeCount--)
        {
            MapObj key;
            Monster tmpMon;
            fin >> key >> tmpMon;
            stat.mogicTower.monsterInfo[key] = tmpMon;
        }

        fin >> stat.player;
    }

    return stat;
}


const Status& updateStatus(Status& stat)
{
    Position curPos = stat.player.getPos();

    auto& colorMap = stat.mogicTower.colorMap;
    memset(colorMap, 0, sizeof(colorMap));
    int colorCount = traverseMap(stat.mogicTower) + 1;

    stat.nodeContainer.resize(size_t(colorCount));

    stat.curIdx = buildGraph(stat.mogicTower, curPos, colorCount, &stat);

    bool flag = false;
    for (const auto& node: stat.nodeContainer)
        if (node.getType() == boss)
        {
            stat.bossIdx = node.getIndex(), flag = true;
            break;
        }
    if (!flag)
        stat.bossIdx = 0;
    stat.player = stat.player;

#ifdef DEBUG
    assert(stat.getNodePtr()->getType() == safeBlock);
#endif

    return stat;
}

const Status& initStatus(Status& stat)
{
    readInitStatus(stat);
    updateStatus(stat);
    stat.player.blockCount = 0;
    Position originalPositon =stat.player.getPos();
    moveTo(stat.curIdx, stat);
    stat.player.moveTo(originalPositon);
	stat.getNode().pos = originalPositon;

    return stat;
}
