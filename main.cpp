#include <iostream>
#include <string>
#include "route.h"
#include "AI.h"
#include <cassert>
#include <fstream>
#include <ctime>

using namespace std;

int main()
{
    Status mainStatus;
    mainStatus.init();

    ofstream fout("output.txt");

    if (!fout)
        throw runtime_error("Cannot create output.txt");

	string s = getRoute(mainStatus, mainStatus.curIdx);
	fout << s;

    initDefaultDepth(mainStatus);

    cout << "Initial Node Count: \t" << mainStatus.nodeContainer.size() - 1 << endl;
	cout << "Init Path: \t\t" << s << endl << endl;


    while (mainStatus.hasNext())
    {
        cout << "Posible Choices Count:\t" << mainStatus.getNode().adj.size() << endl;

        int depth = AIprof::DEFAULT_DEPTH;
        int choiceIdx = Achilles(mainStatus, depth);
        if (choiceIdx == 0)
            break;

        while (AIprof::lastSearchTime < 4 && depth < AIprof::DEFAULT_DEPTH + 5)
            choiceIdx = Achilles(mainStatus, ++depth);


#ifdef DEBUG
        if (choiceIdx == 0)
            throw runtime_error("Search returns no choice!");
#endif
        auto choice = mainStatus.getNodePtr(choiceIdx);
        cout << "Choice: \t" << choice->getPos().x <<
            " " << choice->getPos().y << endl;

        s = getRoute(mainStatus, choiceIdx);

        cout << "Path: \t" << s << endl << endl;

        fout << s;

        mainStatus.moveTo(choiceIdx);

#ifdef DEBUG
        //globalMogicTower.dbg_print();
#endif

        //PAUSE;
    }
    fout << endl;
    fout.close();

    cout << "Time Cost: \t" << double(clock()) / CLOCKS_PER_SEC << endl;
    mainStatus.print();
    cout << endl << "output.txt successfully created, press any key to auto-simulate..." << endl;
    PAUSE;

#ifndef __linux__
    (void) system("mota.exe");
#else
    (void) system("wine ../mota.exe");
#endif
}



