#ifndef __AI_H
#define __AI_H
#include "mogicTower.h"

int Achilles(const Status& stat, int depth);

void initDefaultDepth(const Status& stat);

namespace AIprof
{
    extern int DEFAULT_DEPTH;
    extern double lastSearchTime;
    extern bool lastSearchTrivial;
    extern int MAX_DEPTH;
}

#endif

