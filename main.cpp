#include <iostream>
#include "init.h"
#include "routine.h"
#include "search.h"

using namespace std;

Tower globalMogicTower;

int main()
{
    readTower(globalMogicTower);
    Status mainStatus = getInitialStatus(globalMogicTower);
    while (!isEnd(mainStatus))
    {
#ifdef DEBUG
        Status ori = mainStatus;
#endif
        GraphNode* originalNode = mainStatus.cur;
        GraphNode* p = nullptr;
        search(mainStatus, 0, p);
#ifdef DEBUG
        dbg_compareStatus(ori, mainStatus);
#endif
        cout << p << endl;
        //moveTo(p, mainStatus);
    }

    cout << "Quiting" << endl;
    PAUSE;
}



