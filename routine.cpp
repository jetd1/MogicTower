#include "routine.h"
#include <cassert>


bool isEnd(const Status &stat)
{
	return true;
}

string getRoute(const Status& stat, const GraphNode* choice)
{
#ifdef DEBUG
    assert(stat.head->next.find(choice) != stat.head->next.end());
#endif
    return "w";
}

void moveTo(const GraphNode, Tower& mogicTower)
{
    
}