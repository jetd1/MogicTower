#include "mogic.h"
#include "mogicTower.h"
#include "search.h"
#include <vector>

// TODO: Finish This Shit
int search(const Status& stat, int depth, GraphNode* &bestChoice)
{
    if (depth == MAX_DEPTH)
        return eval(stat);

	bool isempty = stat.head->empty;
	PlayerInfo backupPlayer = stat.player;
	int maxVal = 0;
	GraphNode *p;

    auto& next = stat.head->next;
	for (auto itr = next.begin(); itr != next.end(); ++itr) {
		if (trans(stat, *itr)) {
			int curVal = search(stat, depth + 1, p);
			if (maxVal < curVal) {
				maxVal = curVal;
				bestChoice = p;
			}
			restore(stat, isempty, backupPlayer);
		}

	}
    

    return maxVal;
}

struct door_key {	//È«¾ÖÓÐ
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
	int yellow_key = stat.player.getKeyCount(yellowKey);
	int blue_key = stat.player.getKeyCount(blueKey);
	int red_key = stat.player.getKeyCount(redKey);



    return result;
}