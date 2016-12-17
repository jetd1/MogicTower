#include <iostream>
#include <queue>
#include "mogic.h"
#include "damage.h"
#include "init.h"

using namespace std;

Tower globalMogicTower;

int main()
{
    globalMogicTower = readTower();
    const Status& initialStatus = getInitialStatus(globalMogicTower);

    cout << "Quiting" << endl;
    PAUSE;
}

