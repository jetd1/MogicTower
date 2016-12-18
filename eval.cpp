#include "eval.h"
#include "helpers.h"
#include "damage.h"
extern Tower globalMogicTower;
/*应该没啥用。。因为是静态的，我需要动态的*/
/*struct door_key	
{
    int ykey, bkey, rkey;
    int ydoor, bdoor, rdoor;
    door_key()
    {
        ykey = bkey = rkey = 0;
        ydoor = bdoor = rdoor = 0;
        auto map = globalMogicTower.mapContent;
        for (int i = 0; i < MAP_LENGTH; i++)
            for (int j = 0; j < MAP_WIDTH; j++)
                switch (map[i][j])
                {
                    case yellowDoor:
                        ++ydoor; break;
                    case blueDoor:
                        ++bdoor; break;
                    case redDoor:
                        ++rdoor; break;
                    case yellowKey:
                        ++ykey; break;
                    case blueKey:
                        ++bkey; break;
                    case redKey:
                        ++rkey; break;
                    default:
                        break;
                }
    }
};*/

inline long long cmpMonster(const Status& stat) {	//当前状态玩家与所有怪物交战的伤害总和（不管这个怪物打没打过）
	auto map = globalMogicTower.mapContent;
	long long sumDamage = 0;
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
    int result = 0;
	/* 指导思想：魔防>物防>物攻>钥匙>HP */
    int blood = stat.player.getHP();
    int attack = stat.player.getATK();
    int defend = stat.player.getDEF();
    int defend_m = stat.player.getMDEF();
    int yellow_key = stat.player.getKeyCount(yellowKey);
    int blue_key = stat.player.getKeyCount(blueKey);
    int red_key = stat.player.getKeyCount(redKey);
	//int yellow_door =
	/*未完成的这部分是剩下的三种门与钥匙的差值，这三个差值也是参数*/
	/*（如果能动态维护还剩多少门的情况下）*/
	result -= cmpMonster(stat) * 100 / blood;	//没有测试，现在不知道这个数是不是稳定在一个量级上，再调
	result += defend_m * 500;
	result += defend * 300;
	result += attack * 250;
	/*暂时写到这，想增加内容为关于钥匙与剩下的门之间的比率换算的权重*/
    return result;
}