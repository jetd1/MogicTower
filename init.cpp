#include "mogicTower.h"
#include "helpers.h"
#include "init.h"
#include <queue>
#include <cassert>

const Tower& readTower()
{
    if (freopen("input.txt", "r", stdin) == nullptr)
        cout << "打开input.txt失败，将从stdin中读取输入" << endl;

    int ign;
    cin >> ign >> ign >> ign;

    static Tower mogicTower;

    for (size_t i = 0; i < MAP_LENGTH; ++i)
        for (size_t j = 0; j < MAP_LENGTH; ++j)
            cin >> mogicTower.mapContent[i][j];

    for (size_t i = 0; i < 5; i++)
        cin >> mogicTower.buff[i];

    int monsterTypeCount;
    cin >> monsterTypeCount;
    while (monsterTypeCount--)
    {
        MapObj key;
        Monster tmpMon;
        cin >> key >> tmpMon;
        mogicTower.monsterInfo[key] = tmpMon;
    }

    cin >> mogicTower.initialPlayerInfo;

    return  mogicTower;
}

//搜索cur结点整个所在封闭区域
//static void searchArea(const Tower& mogicTower, GraphNode* cur, int been[MAP_LENGTH][MAP_WIDTH])
//{
//    int x, y;
//    cur->blockCount = 0;
//    auto& map = mogicTower.mapContent;
//
//    queue<Position> q;
//    q.push(cur->pos);
//    cur->type = map[cur->pos.x][cur->pos.y];
//    while (!q.empty())
//    {
//        x = q.front().x;
//        y = q.front().y;
//        for (int i = 0; i < 4; i++)
//        {
//            int nx = x + dx[i];
//            int ny = y + dy[i];
//
//            if (been[nx][ny])	//去过了
//                continue;
//            if (map[nx][ny] == wall)	//墙
//                continue;
//            if (isMonster(mogicTower, nx, ny) || isDoor(mogicTower, nx, ny)) //怪物或门
//            {
//                GraphNode* temp = new GraphNode();
//                temp->pos.x = nx, temp->pos.y = ny;
//                cur->next.push_back(temp);
//                been[nx][ny] = true;
//                continue;
//            }
//            if (isItem(mogicTower, nx, ny)) //物品
//            {	
//                cur->obj.push_back(mogicTower.mapContent[nx][ny]);
//                been[nx][ny] = true;
//                Position temp(nx, ny);
//                q.push(temp);
//                cur->blockCount++;
//                continue;
//            }
//            if (map[nx][ny] == road) //道路
//            {	
//                been[nx][ny] = true;
//                Position temp(nx, ny);
//                q.push(temp);
//                cur->blockCount++;
//                continue;
//            }
//            assert(false);
//        }
//        q.pop();
//    }
//    for (size_t i = 0; i < cur->next.size(); i++)
//        searchArea(mogicTower, cur->next[i], been);
//}

static void colorize(const Tower& mogicTower, int x, int y, const int color, int been[MAP_LENGTH][MAP_WIDTH])
{
    if (been[x][y] != 0)
        return;
    auto& map = mogicTower.mapContent;
    been[x][y] = color;
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
        colorize(mogicTower, nx, ny, color, been);
    }
}

static void traverseMap(const Tower& mogicTower, int been[MAP_LENGTH][MAP_WIDTH])
{
    int color = 0;
    auto& map = mogicTower.mapContent;
    for (int i = 0; i < MAP_LENGTH; ++i)
        for (int j = 0; j < MAP_WIDTH; ++j)
        {
            if (map[i][j] == wall)
                continue;
            if (been[i][j] != 0)
                continue;
            if (isMonster(mogicTower, i, j) || isDoor(mogicTower, i, j))
            {
                been[i][j] = ++color;
                continue;
            }
            colorize(mogicTower, i, j, ++color, been);
        }

	for (int i = 0; i < MAP_LENGTH; ++i) {
		for (int j = 0; j < MAP_WIDTH; ++j) {
			cout << been[i][j] << " ";
		}
		cout << endl;
	}
}

static GraphNode *buildGraph(const Tower& mogicTower, const Position headpos, int been[MAP_LENGTH][MAP_WIDTH]) {
	const int MAX_COLOR = 169;
	static GraphNode *nodes[MAX_COLOR]; // nodes[k]记录颜色为k的块对应的结点

	auto& map = mogicTower.mapContent;

	for (int i = 0; i < MAX_COLOR; ++i)
		nodes[i] = NULL;

	for (int i = 0; i < MAP_LENGTH; ++i)
		for (int j = 0; j < MAP_WIDTH; ++j) {
			if (map[i][j] == wall)
				continue;
			if (nodes[been[i][j]] == NULL) { // 该颜色没有建结点
				nodes[been[i][j]] = new GraphNode;
				nodes[been[i][j]]->pos.x = i; nodes[been[i][j]]->pos.y = j;
				nodes[been[i][j]]->blockCount = 1;

				if (map[i][j] == player || map[i][j] == road || isItem(mogicTower, i, j)) 
					nodes[been[i][j]]->type = safeblock; // road和物品都是safeblock
				else
					nodes[been[i][j]]->type = map[i][j]; // 门,怪物

			}
			else {
				nodes[been[i][j]]->blockCount++;
			}

			if (isItem(mogicTower, i, j)) { // 记录结点里的物品
				nodes[been[i][j]]->obj.push_back(map[i][j]);
			}
		}

	for (int i = 0; i < MAP_LENGTH; ++i)
		for (int j = 0; j < MAP_WIDTH; ++j) {
			if (map[i][j] == wall)
				continue;
			for (int k = 0; k < 4; ++k) {
				int nx = i + dx[k];
				int ny = j + dy[k];
				if (!isInRange(nx, ny))
					continue;
				if (map[nx][ny] == wall)
					continue;
				if (been[i][j] != been[nx][ny])
					if (nodes[been[i][j]]->next.find(nodes[been[nx][ny]]) == nodes[been[i][j]]->next.end())
						nodes[been[i][j]]->next.insert(nodes[been[nx][ny]]);
				
			}
		}
	return nodes[been[headpos.x][headpos.y]];
}


const Status& getInitialStatus(const Tower& mogicTower)
{
    GraphNode* head = nullptr;

//    head = new GraphNode();
//   head->pos = mogicTower.initialPlayerInfo.getPos();
	Position headpos = mogicTower.initialPlayerInfo.getPos();

    static int been[MAP_LENGTH][MAP_WIDTH];
    memset(been, 0, sizeof(been));

    traverseMap(mogicTower, been);
    //searchArea(mogicTower, head, been);
	head = buildGraph(mogicTower, headpos, been);
    head->type = player;

    static Status stat;
    stat.head = head;
    stat.player = mogicTower.initialPlayerInfo;

    return stat;
}
