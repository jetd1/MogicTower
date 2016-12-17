#include "helpers.h"
#include "init.h"
#include "graph.h"
#include <queue>
#include <fstream>
#include <cassert>

const Tower& readTower(Tower& mogicTower)
{
    ifstream fin("input.txt");
    if (!fin)
    {
        cout << "打开input.txt失败，退出中..." << endl;
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


Status getStatus(const Tower& mogicTower)
{
    Position curPos = mogicTower.player.getPos();

    int colorMap[MAP_LENGTH][MAP_WIDTH];
    memset(colorMap, 0, sizeof(colorMap));

    int colorCount = traverseMap(mogicTower, colorMap) + 1;

    Status stat;
    stat.nodeContainer.resize(colorCount);

    stat.cur = buildGraph(mogicTower, curPos, colorCount, colorMap, stat.nodeContainer);
    stat.player = mogicTower.player;

    /* 先取走最初节点的所有物品并标记为空 */
#ifdef DEBUG
    assert(stat.cur->getType() == safeBlock);
#endif

    stat.cur->empty = true;
    stat.blockCount += stat.cur->blockCount;
    stat.player.acquire(stat.cur->obj);

    return stat;
}
