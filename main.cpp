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
    }

    cout << endl << "Quiting" << endl;
    PAUSE;
}



