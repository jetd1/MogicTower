#include "eval.h"
#include "helpers.h"
#include "damage.h"
#include "route.h"
#include <climits>

inline int cmpMonster(const Status& stat)
{
    auto& monsterInfo = Tower::monsterInfo;
    int damageSum = 0;
    for (const auto& node: stat.nodeContainer)
    {
        auto type = node.getType();
        if (isMonster(type))
        {
            int temp = getDamage(stat.player, monsterInfo.at(type));
            if (temp == 999999999)
                temp = 10000;
            damageSum += temp;
        }
    }
    return damageSum;
}

int eval(const Status& stat)
{
    if (stat.bossDead())
        return INT_MAX / 2 + stat.player.getHP() * 20;

    int result = 0;

    if (!stat.hasNext())
    {
        int monsterCount = 0;
        for (const auto& node: stat.nodeContainer)
            monsterCount += isMonster(node.getType());
        result -= monsterCount * 10000;
    }


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

    result -= cmpMonster(stat) * 1000 / blood;
    result -= (remain_yellow_door - (remain_yellow_key / 2 + yellow_key)) * 5000;
    result -= (remain_blue_door - (remain_blue_key / 2 + blue_key)) * 10000;
    result -= (remain_red_door - (remain_red_key / 2 + red_key)) * 15000;
    result += defend_m * 2000;
    result += defend * 2500;
    result += attack * 1500;

    return result;
}