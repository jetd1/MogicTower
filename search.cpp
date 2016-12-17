#include "mogic.h"
#include "mogicTower.h"
#include "search.h"
#include "trans.h"
#include <vector>

extern Tower globalMogicTower;


void restore(Status& stat, bool isempty, PlayerInfo backupPlayer, GraphNode* original_head) {
	stat.player = backupPlayer;
	stat.head->empty = isempty;
	stat.head = original_head;

}


// TODO: Finish This Shit
int search(Status& stat, int depth, GraphNode* &bestChoice)
{
    if (depth == MAX_DEPTH)
        return eval(stat);

	PlayerInfo backupPlayer = stat.player;
    GraphNode* original_head = stat.head;
	int maxVal = 0;
	GraphNode *p;

    auto& next = stat.head->next;
	for (auto itr = next.begin(); itr != next.end(); ++itr) {
		bool isempty = (*itr)->empty;
		if (trans(stat, *itr)) {
			int curVal = search(stat, depth + 1, p);
			if (maxVal < curVal) {
				maxVal = curVal;
				bestChoice = p;
			}
			restore(stat, isempty, backupPlayer, original_head);
		}
        
    }
    
    return maxVal;
}

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
	int blockDelta = stat.head->blockCount;
	int yellow_key = stat.player.getKeyCount(yellowKey);
	int blue_key = stat.player.getKeyCount(blueKey);
	int red_key = stat.player.getKeyCount(redKey);
	door_key *dk = new door_key();
    int all;
	//int yellow_door = stat.
	/*这部分是剩下的三种门与钥匙的差值，这三个差值也是参数*/

    result += blood;

    return result;
}