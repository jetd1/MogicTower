#ifndef __SEARCH_H
#define __SEARCH_H

#include "mogicTower.h"


int eval(const Status& stat);
void trans(const Status& cur, const Status& target);
void restore();

#endif

