#ifndef __SEARCH_H
#define __SEARCH_H

#include "mogicTower.h"

int search(const Status& stat, int depth, const set<int>& choiceList, int &bestChoice, int &ret);

#endif

