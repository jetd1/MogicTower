#define DEBUG

#include <iostream>
#include <vector>
#include "mogic.h"
#include "damage.h"

using namespace std;

Tower mogicTower;

struct node {
	int x, y;
	vector<node*> next;
};
node* head = NULL;

void readTower()
{
    if (freopen("input.txt", "r", stdin) == nullptr)
        cout << "打开input.txt失败，将从stdin中读取输入";

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
	head->x = mogicTower.initialPlayerInfo.getPOS.x;
	head->y = mogicTower.initialPlayerInfo.getPOS.y;
	makeTree(head);
    PAUSE;
}
