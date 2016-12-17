#ifndef __INIT_H
#define __INIT_H

#include "mogicTower.h"

const Tower& readTower();

//搜索cur结点整个所在封闭区域
void searchArea(const Tower& mogicTower, GraphNode* cur, int been[MAP_LENGTH][MAP_WIDTH]);

const Status& getInitialStatus(const Tower& mogicTower);

#endif