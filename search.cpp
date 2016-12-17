#include "mogic.h"
#include "mogicTower.h"
#include "search.h"
#include <vector>

extern Tower globalMogicTower;

// TODO: Finish This Shit
int search(const Status& stat, int depth)
{
    if (depth == MAX_DEPTH)
        return eval(stat);

    auto& next = stat.head->next;
    size_t nextCount = next.size();
    for (size_t i = 0; i < nextCount; ++i)
    {
        
    }
    

    return 0;
}

struct door_key {	//全局性的钥匙和门
	int ykey, bkey, rkey;
	int ydoor, bdoor, rdoor;
	door_key() {
		ykey = bkey = rkey = 0;
		ydoor = bdoor = rdoor = 0;
		auto map = globalMogicTower.mapContent;
		for (int i = 0; i < MAP_LENGTH; i++) {
			for (int j = 0; j < MAP_WIDTH; j++) {
				switch (map[i][j]) {
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
	int blockDelta = stat.head->blockCount;
	int yellow_key = stat.player.getY_KEY();
	int blue_key = stat.player.getB_KEY();
	int red_key = stat.player.getR_KEY();
	door_key *dk = new door_key();
	int all


    return result;
}