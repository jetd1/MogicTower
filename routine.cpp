#include "routine.h"
#include <cassert>


bool isEnd(const Status &stat)
{
	return false;
}

string getRoute(const Status& stat, GraphNode* choice)
{
#ifdef DEBUG
    assert(stat.cur->next.find(choice) != stat.cur->next.end());
#endif
    return "w";
}

void moveTo(const GraphNode* target, Tower& mogicTower)
{
    
}