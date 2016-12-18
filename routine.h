#ifndef __ROUTINE_H
#define __ROUTINE_H

#include "mogicTower.h"


bool isEnd(const Status& stat);

string getRouteFromSrcToDest(Position src, Position dest);

string getRoute(Status& stat, int idx);

void moveTo(int targetIdx, Status& stat, bool update = true);

#endif

