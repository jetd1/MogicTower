#include "eval.h"
#include "helpers.h"
#include "damage.h"
#include <climits>

extern Tower globalMogicTower;
inline int cmpMonster(const Status& stat) {
	auto map = globalMogicTower.mapContent;
	int sumDamage = 0;
	for (int i = 0; i < MAP_LENGTH; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			if (isMonster(map[i][j])) {
				int temp = getDamage(stat.player, globalMogicTower.monsterInfo[map[i][j]]);
				if (temp == 999999999)
					temp = 10000;
				sumDamage += temp;
			}
		}
	}
	return sumDamage;
}
int eval(const Status& stat)
{
	if (stat.bossDead())
		return INT_MAX;
    int result = 0;
    int blood = stat.player.getHP();
    int attack = stat.player.getATK();
    int defend = stat.player.getDEF();
    int defend_m = stat.player.getMDEF();
    int yellow_key = stat.player.getKeyCount(yellowKey);
    int blue_key = stat.player.getKeyCount(blueKey);
    int red_key = stat.player.getKeyCount(redKey);
	int remain_yellow_door = stat.getRemainDoorCount(yellowDoor);
	int remain_blue_door = stat.getRemainDoorCount(blueDoor);
	int remain_red_door = stat.getRemainDoorCount(redDoor);
	int remain_yellow_key = stat.getRemainKeyCount(yellowKey);
	int remain_blue_key = stat.getRemainKeyCount(blueKey);
	int remain_red_key = stat.getRemainKeyCount(redKey);
	result -= cmpMonster(stat) * 100 / blood;
	result -= (remain_yellow_door - (remain_yellow_key / 2 + yellow_key)) * 500;
	result -= (remain_blue_door - (remain_blue_key / 2 + blue_key)) * 1000;
	result -= (remain_red_door - (remain_red_key / 2 + red_key)) * 1500;
	result += defend_m * 1000;
	result += defend * 800;
	result += attack * 300;
    return result;
}