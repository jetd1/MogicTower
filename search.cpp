#include "mogic.h"
#include "mogicTower.h"
#include "search.h"
#include <vector>

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

struct door_key {	//ȫ����
	int ykey, bkey, rkey;
	int ydoor, bdoor, rdoor;
	init
};
int getYellowDoor() {
	for(int )
}
int getBlueDoor() {

}
int getRedDoor() {

}
int getYellowKey() {

}
int getBlueKey() {

}
int getRedKey() {

}

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



    return result;
}