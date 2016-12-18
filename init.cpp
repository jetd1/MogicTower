#include "helpers.h"
#include "init.h"
#include "graph.h"
#include <queue>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include "routine.h"

const Tower& readTower(Tower& mogicTower)
{
    ifstream fin("input.txt");
    if (!fin)
    {
        cout << "无法打开input.txt，正在退出..." << endl;
        exit(-1);
    }

    int ign;
    fin >> ign >> ign >> ign;

    for (size_t i = 0; i < MAP_LENGTH; ++i)
        for (size_t j = 0; j < MAP_LENGTH; ++j)
            fin >> mogicTower.mapContent[i][j];

    for (size_t i = 0; i < 5; i++)
        fin >> mogicTower.buff[i];

    int monsterTypeCount;
    fin >> monsterTypeCount;
    while (monsterTypeCount--)
    {
        MapObj key;
        Monster tmpMon;
        fin >> key >> tmpMon;
        mogicTower.monsterInfo[key] = tmpMon;
    }

    fin >> mogicTower.player;

    return mogicTower;
}


Status getStatus(Tower& mogicTower)
{
    Position curPos = mogicTower.player.getPos();

    auto& colorMap = mogicTower.colorMap;
    memset(colorMap, 0, sizeof(colorMap));
    int colorCount = traverseMap(mogicTower) + 1;

    Status stat;
    stat.nodeContainer.resize(colorCount);

    stat.cur = buildGraph(mogicTower, curPos, colorCount, &stat);
    stat.player = mogicTower.player;

#ifdef DEBUG
    assert(stat.cur->getType() == safeBlock);
#endif

    return stat;
}

Status initStatus(Tower& mogicTower)
{
    Status&& stat = getStatus(mogicTower);
    stat.player.blockCount = 0;
    moveTo(stat.cur->getIndex(), stat);

    return stat;
}
