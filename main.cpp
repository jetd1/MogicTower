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

        int choiceIdx = 0;
        int ret = search(mainStatus, 0, choiceIdx);

#ifdef DEBUG
        if (choiceIdx == 0)
            throw runtime_error("Search returns no choice!");
        auto choice = mainStatus.getNodePtr(choiceIdx);
        cout << "choice: " << choice->getPos().x <<
            " " << choice->getPos().y << endl;
        cout << "eval: " << ret << endl;
        dbg_compareStatus(ori, mainStatus);
#endif

        cout << getRoute(mainStatus, choiceIdx);
        moveTo(choiceIdx, mainStatus);

#ifdef DEBUG
        //globalMogicTower.dbg_print();
#endif

        PAUSE;
    }

    cout << endl << "Quiting" << endl;
    PAUSE;
}



