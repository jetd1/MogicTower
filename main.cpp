#include <iostream>
#include <string>
#include "init.h"
#include "routine.h"
#include "search.h"

using namespace std;

Tower globalMogicTower;


int main()
{
    readTower(globalMogicTower);
#ifdef DEBUG
    dbg_printSize();
#endif
    Status mainStatus = getStatus(globalMogicTower);
    while (!isEnd(mainStatus))
    {
#ifdef DEBUG
        Status ori = mainStatus;
#endif
        GraphNode* choice = nullptr;
        int ret = search(mainStatus, 0, choice);
#ifdef DEBUG
        cout << ret << endl;
        dbg_compareStatus(ori, mainStatus);
#endif
        cout << getRoute(mainStatus, choice);
        moveTo(choice, mainStatus);
        PAUSE;
    }

    cout << endl << "Quiting" << endl;
    PAUSE;
}



