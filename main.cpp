#define DEBUG

#include <iostream>
#include <vector>
#include <cstring>
#include <stack>
#include <queue>
#include "mogic.h"
#include "damage.h"

using namespace std;

Tower mogicTower;

const int HP_Multiple = 5;
const int ATK_Multiple = 4;
const int DEF_Multiple = 7;
const int MDEF_Multiple = 6;

/* 0123:上下左右 */
const int dx[4] = { -1,1,0,0 };
const int dy[4] = { 0,0,-1,1 };
/* 魔塔重构图节点结构 */
struct node 
{
    bool valid;         /* 访问该节点后将valid设为false */
    Position pos;       /* 该节点的坐标 */
    MapObj type;        /* 该节点类型（门或怪物） */
	vector<node*> next; /* 子节点列表 */
    vector<MapObj> obj; /* 节点物品列表 */
    int blockCount;     /* 该节点增加的连通块计数 */
};
node* head = nullptr;

int evalCurrentStatus(const node &status);

int been[MAP_LENGTH][MAP_WIDTH];
void readTower()
{
    if (freopen("input.txt", "r", stdin) == nullptr)
        cout << "打开input.txt失败，将从stdin中读取输入" << endl;

    int ign;;
    cin >> ign >> ign >> ign;

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
}
bool isMonster(int x, int y) {
	if ((mogicTower.mapContent[x][y] >= 51 && mogicTower.mapContent[x][y] <= 70) || mogicTower.mapContent[x][y] == boss)
		return true;
	return false;
}
bool isDoor(int x, int y) {
	if (mogicTower.mapContent[x][y] >= 31 && mogicTower.mapContent[x][y] <= 33)
		return true;
	return false;
}
bool isItem(int x, int y) {
	if (mogicTower.mapContent[x][y] >= 21 && mogicTower.mapContent[x][y] <= 28)
		return true;
	return false;
}
void searchArea(node* cur) {	//搜索cur结点整个所在封闭区域
	int x, y;
	cur->blockCount = 0;
	auto& map = mogicTower.mapContent;
	queue<Position> q;
	q.push(cur->pos);
	cur->type = map[cur->pos.x][cur->pos.y];
	while (!q.empty()) {
		x = q.front().x;
		y = q.front().y;
		for (int i = 0; i < 4; i++) {
			if (been[x + dx[i]][y + dy[i]])	//去过了
				continue;
			if (map[x + dx[i]][y + dy[i]] == wall)	//墙
				continue;
			if (isMonster(x + dx[i], y + dy[i]) || isDoor(x + dx[i], y + dy[i])) {	//怪物或门
				node* temp = new node();
				temp->pos.x = x + dx[i];
				temp->pos.y = y + dy[i];
				cur->next.push_back(temp);
				been[x + dx[i]][y + dy[i]] = 1;
				continue;
			}
			if (isItem(x + dx[i], y + dy[i])) {	//物品
				cur->obj.push_back(mogicTower.mapContent[x + dx[i]][y + dy[i]]);
				been[x + dx[i]][y + dy[i]] = 1;
				Position temp;
				temp.x = x + dx[i];
				temp.y = y + dy[i];
				q.push(temp);
				cur->blockCount++;
				continue;
			}
			if (map[x + dx[i]][y + dy[i]] == road) {	//道路
				been[x + dx[i]][y + dy[i]] = 1;
				Position temp;
				temp.x = x + dx[i];
				temp.y = y + dy[i];
				q.push(temp);
				cur->blockCount++;
				continue;
			}
			cout << "Error" << endl;
			PAUSE;
		}
		q.pop();
	}
	for (int i = 0; i < (int)cur->next.size(); i++)
		searchArea(cur->next[i]);
}
int main()
{
    readTower();
	head = new node();
    head->pos = mogicTower.initialPlayerInfo.getPos();
	memset(been, 0, sizeof(been));
	been[head->pos.x][head->pos.y] = 1;
	searchArea(head);
	head->type = player;
    PAUSE;
}


int evalCurrentStatus(const node &status)
{
	int tmpRank = 0;
	tmpRank += status.player->getATK() * ATK_Multiple;
	tmpRank += status.player->getHP() * HP_Multiple;
	tmpRank += status.player->getDEF() * DEF_Multiple;
	tmpRank += status.player->getMDEF() * MDEF_Multiple;
	
	/* TODO: 对player所在位置连通性对权值的影响 */
	return tmpRank;
}