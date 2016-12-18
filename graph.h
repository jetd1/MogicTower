#ifndef __GRAPH_H
#define __GRAPH_H

#include "mogicTower.h"

int traverseMap(Tower& mogicTower);

GraphNode *buildGraph(const Tower& mogicTower, const Position& curPos, int colorCount,
                      vector<GraphNode>& nodeContainer);


#endif

