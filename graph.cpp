#include "graph.h"
#include "helpers.h"


static void colorize(const Tower& mogicTower, int x, int y, const int color, int colorMap[MAP_LENGTH][MAP_WIDTH])
{
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
        colorize(mogicTower, nx, ny, color, colorMap);
    }
}

int traverseMap(const Tower& mogicTower, int colorMap[MAP_LENGTH][MAP_WIDTH])
{
    int color = 0;
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
            colorize(mogicTower, i, j, ++color, colorMap);
        }
    return color;
}

GraphNode *buildGraph(const Tower& mogicTower, const Position& curPos, int colorCount, int colorMap[MAP_LENGTH][MAP_WIDTH], vector<GraphNode>& nodeContainer)
{
    static vector<GraphNode *> nodes(colorCount);
    auto& map = mogicTower.mapContent;

    for (int i = 0; i < colorCount; ++i)
        nodes[i] = nullptr;

    for (int i = 0; i < MAP_LENGTH; ++i)
        for (int j = 0; j < MAP_WIDTH; ++j)
        {
            if (map[i][j] == wall)
                continue;
            if (nodes[colorMap[i][j]] == nullptr)
            { // 该颜色没有建结点
                nodes[colorMap[i][j]] = &nodeContainer[colorMap[i][j]];
                nodes[colorMap[i][j]]->index = colorMap[i][j];
                nodes[colorMap[i][j]]->empty = false;
                nodes[colorMap[i][j]]->pos.x = i; nodes[colorMap[i][j]]->pos.y = j;
                nodes[colorMap[i][j]]->blockCount = 1;

                if (map[i][j] == road || isItem(mogicTower, i, j))
                    nodes[colorMap[i][j]]->type = safeBlock; // road和物品都是safeblock
                else
                    nodes[colorMap[i][j]]->type = map[i][j]; // 门,怪物
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
                    if (nodes[colorMap[i][j]]->next.find(nodes[colorMap[nx][ny]]) == nodes[colorMap[i][j]]->next.end())
                        nodes[colorMap[i][j]]->next.insert(nodes[colorMap[nx][ny]]);

            }
        }
    return nodes[colorMap[curPos.x][curPos.y]];
}