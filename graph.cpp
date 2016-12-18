#include "graph.h"
#include "helpers.h"


static void colorize(Tower& mogicTower, int x, int y, const int color)
{
    auto& colorMap = mogicTower.colorMap;
    if (colorMap[x][y] != 0)
        return;
    auto& map = mogicTower.mapContent;
    colorMap[x][y] = color;
    for (int i = 0; i < 4; i++)
    {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (!isInRange(nx, ny))
            continue;
        if (map[nx][ny] == wall)
            continue;
        if (isMonster(mogicTower, nx, ny))
            continue;
        if (isDoor(mogicTower, nx, ny))
            continue;
        colorize(mogicTower, nx, ny, color);
    }
}

int traverseMap(Tower& mogicTower)
{
    int color = 0;
    auto& colorMap = mogicTower.colorMap;
    auto& map = mogicTower.mapContent;
    for (int i = 0; i < MAP_LENGTH; ++i)
        for (int j = 0; j < MAP_WIDTH; ++j)
        {
            if (map[i][j] == wall)
                continue;
            if (colorMap[i][j] != 0)
                continue;
            if (isMonster(mogicTower, i, j) || isDoor(mogicTower, i, j))
            {
                colorMap[i][j] = ++color;
                continue;
            }
            colorize(mogicTower, i, j, ++color);
        }
    return color;
}

int buildGraph(const Tower& mogicTower, const Position& curPos, int colorCount, Status* statp)
{
    vector<GraphNode *> nodes(colorCount);
    auto& map = mogicTower.mapContent;
    auto& colorMap = mogicTower.colorMap;
    auto& container = statp->nodeContainer;

    for (int i = 0; i < colorCount; ++i)
        nodes[i] = nullptr;

    for (int i = 0; i < MAP_LENGTH; ++i)
        for (int j = 0; j < MAP_WIDTH; ++j)
        {
            if (map[i][j] == wall)
                continue;
            if (nodes[colorMap[i][j]] == nullptr)
            { // 该颜色没有建结点
                MapObj type;
                if (map[i][j] == road || isItem(mogicTower, i, j))
                    type = safeBlock; // road和物品都是safeBlock
                else
                    type = map[i][j]; // 门,怪物
                container[colorMap[i][j]] = GraphNode(statp, colorMap[i][j], i, j, type);
                nodes[colorMap[i][j]] = &container[colorMap[i][j]];
            }
            else
                nodes[colorMap[i][j]]->blockCount++;

            if (isItem(mogicTower, i, j)) // 记录结点里的物品
                nodes[colorMap[i][j]]->obj.push_back(map[i][j]);
        }

    for (int i = 0; i < MAP_LENGTH; ++i)
        for (int j = 0; j < MAP_WIDTH; ++j)
        {
            if (map[i][j] == wall)
                continue;
            for (int k = 0; k < 4; ++k)
            {
                int nx = i + dx[k];
                int ny = j + dy[k];
                if (!isInRange(nx, ny))
                    continue;
                if (map[nx][ny] == wall)
                    continue;
                if (colorMap[i][j] != colorMap[nx][ny])
                    if (nodes[colorMap[i][j]]->adj.find(colorMap[nx][ny]) == nodes[colorMap[i][j]]->adj.end())
                        nodes[colorMap[i][j]]->adj.insert(colorMap[nx][ny]);

            }
        }
    return colorMap[curPos.x][curPos.y];
}