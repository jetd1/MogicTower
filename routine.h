#ifndef __ROUTINE_H
#define __ROUTINE_H

#include "mogicTower.h"


bool isEnd(const Status& stat);

//计算单连通块内遍历路径
string getRoute(Status& stat, int idx);

void moveTo(int targetIdx, Status& stat, bool update = true);

#endif

