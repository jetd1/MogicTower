#ifndef __GRAPH_H
#define __GRAPH_H

#include "mogicTower.h"

int traverseMap(const Tower& mogicTower, int colorMap[MAP_LENGTH][MAP_WIDTH]);

GraphNode *buildGraph(const Tower& mogicTower, const Position& headpos, int colorCount,
                      int colorMap[MAP_LENGTH][MAP_WIDTH], vector<GraphNode>& nodeContainer);


#endif

