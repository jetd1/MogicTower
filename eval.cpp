#include "eval.h"

struct door_key
{	//全局性的钥匙和门
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
};

int eval(const Status& stat)
{
    int result = 0;

    int blood = stat.player.getHP();
    int attack = stat.player.getATK();
    int defend = stat.player.getDEF();
    int defend_m = stat.player.getMDEF();
    int blockDelta = stat.cur->blockCount;
    int yellow_key = stat.player.getKeyCount(yellowKey);
    int blue_key = stat.player.getKeyCount(blueKey);
    int red_key = stat.player.getKeyCount(redKey);
    door_key *dk = new door_key();

    //int yellow_door = stat.
    /*这部分是剩下的三种门与钥匙的差值，这三个差值也是参数*/

    //result += blood;
    result += attack * 10;
    result += defend * 8;
    result += defend_m * 8;
    result += blockDelta;
    result += yellow_key * 20;
    result += blue_key * 20;
    result += red_key * 20;

    return result;
}