#include <iostream>
#include "init.h"
#include "routine.h"
#include "search.h"

using namespace std;

Tower globalMogicTower;

int main()
{
    globalMogicTower = readTower();
    Status mainStatus = getInitialStatus(globalMogicTower);
    //while (!isEnd(mainStatus))
    {
        GraphNode* p = nullptr;
        search(mainStatus, 0, p);
        cout << p << endl;
        //moveTo(p);
    }

    cout << "Quiting" << endl;
    PAUSE;
}

