#include "debug.h"
#include "mogicTower.h"

void dbg_compareStatus(const Status& a, const Status& b)
{
    size_t sizeA = a.nodeContainer.size();
    size_t sizeB = b.nodeContainer.size();
    if (!(sizeA == sizeB && a.player == b.player &&
          a.blockCount == b.blockCount && a.cur == b.cur))
        throw runtime_error("Corrupted Status!");
    //if (a.nodeContainer == b.nodeContainer)
    //    throw runtime_error("Corrupted Status!");

    auto& nA = a.nodeContainer;
    auto& nB = b.nodeContainer;

    for (size_t i = 0; i < sizeA; i++)
        if (!(nA[i] == nB[i]))
            throw runtime_error("Corrupted Status!");
}