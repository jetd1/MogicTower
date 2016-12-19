#include <iostream>
#include <string>
#include "init.h"
#include "routine.h"
#include "AI.h"
#include <cassert>
#include <fstream>
#include <ctime>

using namespace std;

int main()
{
    Status mainStatus;
    initStatus(mainStatus);

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

        int choiceIdx = Achilles(mainStatus);
        if (choiceIdx == 0)
            break;

#ifdef DEBUG
        if (choiceIdx == 0)
            throw runtime_error("Search returns no choice!");
        auto choice = mainStatus.getNodePtr(choiceIdx);
        cout << "choice: " << choice->getPos().x <<
            " " << choice->getPos().y << endl;
#endif
        s = getRoute(mainStatus, choiceIdx);

#ifdef DEBUG
        cout << s << endl;
#endif
        fout << s;

        moveTo(choiceIdx, mainStatus);

#ifdef DEBUG
        //globalMogicTower.dbg_print();
#endif

        //PAUSE;
    }
    fout << endl;
    fout.close();

    cout << "Time Cost: \t" << double(clock()) / CLOCKS_PER_SEC << endl;
    mainStatus.print();
    cout << endl << "Quiting" << endl;
    PAUSE;
    

    system("mota.exe");
}



