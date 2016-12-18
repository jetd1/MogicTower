#include <iostream>
#include <string>
#include "init.h"
#include "routine.h"
#include "search.h"
#include <cassert>
#include <fstream>

using namespace std;

Tower globalMogicTower;


int main()
{
    readTower(globalMogicTower);

    Status mainStatus = initStatus(globalMogicTower);

    ofstream fout("output.txt");
    if (!fout)
        throw runtime_error("Cannot create output.txt");
	string s = getRoute(mainStatus, mainStatus.curIdx);
	fout << s;
#ifdef DEBUG
	cout << s << endl;
#endif

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
        string s = getRoute(mainStatus, choiceIdx);

#ifdef DEBUG
        cout << s << endl;
#endif
        fout << s;

        moveTo(choiceIdx, mainStatus);

#ifdef DEBUG
        //globalMogicTower.dbg_print();
#endif

//        PAUSE;
    }
    fout << endl;
    cout << endl << "Quiting" << endl;
    PAUSE;
}



