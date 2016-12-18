#ifndef __GRAPH_H
#define __GRAPH_H

#include "mogicTower.h"

//遍历图并染色
int traverseMap(Tower& mogicTower);

//将地图转换成图，添加节点的必要信息
int buildGraph(const Tower& mogicTower, const Position& curPos, int colorCount,
                      Status* statp);


#endif

