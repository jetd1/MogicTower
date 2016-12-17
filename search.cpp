#include "mogic.h"
#include "mogicTower.h"
#include "search.h"
#include "trans.h"
#include "eval.h"
#include "trans.h"
#include <vector>

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