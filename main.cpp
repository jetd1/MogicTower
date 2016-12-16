#define DEBUG

#include <iostream>
#include <vector>
#include "mogic.h"
#include "damage.h"

using namespace std;

Tower mogicTower;

const int HP_Multiple = 5;
const int ATK_Multiple = 4;
const int DEF_Multiple = 7;
const int MDEF_Multiple = 6;
int evalCurrentStatus(const node &status);

/* 魔塔重构图节点结构 */
struct node 
{
    bool valid;         /* 访问该节点后将valid设为false */
    Position pos;       /* 该节点的坐标 */
    MapObj type;        /* 该节点类型（门或怪物） */
	vector<node*> next; /* 子节点列表 */
    vector<MapObj> obj; /* 节点物品列表 */
	Player *player;		/* 当前节点处玩家自身状态 */
    int blockCount;     /* 该节点增加的连通块计数 */
};
node* head = nullptr;

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

bool isMonster(int x, int y) {	//暂时不加boss
	if (mogicTower.mapContent[x][y] >= 51 && mogicTower.mapContent[x][y] <= 70)
		return true;
	return false;
}
bool isDoor(int x, int y) {
	if (mogicTower.mapContent[x][y] >= 31 && mogicTower.mapContent[x][y] <= 33)
		return true;
	return false;
}
void makeTree(node* cur) {
	//if()
}

int main()
{
    readTower();
	head = new node();
    head->pos = mogicTower.initialPlayerInfo.getPos();
	makeTree(head);
    PAUSE;
}


int evalCurrentStatus(const node &status)
{
	int tmpRank = 0;
	tmpRank += status.player->getATK() * ATK_Multiple;
	tmpRank += status.player->getHP() * HP_Multiple;
	tmpRank += status.player->getDEF() * DEF_Multiple;
	tmpRank += status.player->getMDEF() * MDEF_Multiple;
	
	/*to do: 对player所在位置连通性对权值的影响*/
	return tmpRank;
}