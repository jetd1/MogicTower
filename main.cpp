#define DEBUG

#include <iostream>
#include <queue>
#include "mogic.h"
#include "damage.h"
#include "init.h"

using namespace std;

int main()
{
    const Tower & mogicTower = readTower();
    const Status& initialStatus = getInitialStatus(mogicTower);

    PAUSE;
}

