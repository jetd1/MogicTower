#ifndef __GRAPH_H
#define __GRAPH_H

#include "mogicTower.h"

int traverseMap(Tower& mogicTower);

int buildGraph(const Tower& mogicTower, const Position& curPos, int colorCount,
                      Status* statp);


#endif

