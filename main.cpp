#include <iostream>
#include <string>
#include "init.h"
#include "routine.h"
#include "search.h"
#include <cassert>

using namespace std;

Tower globalMogicTower;


int main()
{
    readTower(globalMogicTower);

    Status mainStatus = initStatus(globalMogicTower);

    while (!isEnd(mainStatus))
    {
#ifdef DEBUG
        Status ori = mainStatus;
#endif


        GraphNode* choice = nullptr;
        int ret = search(mainStatus, 0, choice);


#ifdef DEBUG
        assert(choice != nullptr);
        cout << "choice: " << choice->getPos().x <<
            " " << choice->getPos().y << endl;
        cout << "eval: " << ret << endl;
        dbg_compareStatus(ori, mainStatus);
#endif


        cout << getRoute(mainStatus, choice);
        moveTo(choice, mainStatus);

#ifdef DEBUG
        globalMogicTower.dbg_print();
#endif

        PAUSE;
    }

    cout << endl << "Quiting" << endl;
    PAUSE;
}



