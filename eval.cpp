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
					temp = 1000;
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
	result -= cmpMonster(stat) * 100 / blood;
	result += defend_m * 500;
	result += defend * 300;
	result += attack * 250;
    return result;
}