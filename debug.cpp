#include "mogicTower.h"

#ifdef DEBUG
#include "debug.h"
#include <iomanip>

void dbg_printSize()
{
    cout << "sizeof MapObj " << sizeof(MapObj) << endl;
    cout << "sizeof Position " << sizeof(Position) << endl;
    cout << "sizeof PlayerInfo " << sizeof(PlayerInfo) << endl;
    cout << "sizeof Monster " << sizeof(Monster) << endl;
    cout << "sizeof Tower " << sizeof(Tower) << endl;
    cout << "sizeof GraphNode " << sizeof(GraphNode) << endl;
    cout << "sizeof Status " << sizeof(Status) << endl;
}


void Status::dbg_print()
{
    for (int i = 0; i < MAP_LENGTH; ++i)
    {
        for (int j = 0; j < MAP_WIDTH; ++j)
            cout << setw(2) << mogicTower.mapContent[i][j] << ' ';
        cout << endl;
    }
    cout << "HP: \t" << player.getHP() << endl;
    cout << "ATK:\t" << player.getATK() << endl;
    cout << "DEF:\t" << player.getDEF() << endl;
    cout << "MDEF:\t" << player.getMDEF() << endl;
    cout << "YK:\t" << player.getKeyCount(yellowKey) << endl;
    cout << "BK:\t" << player.getKeyCount(blueKey) << endl;
    cout << "RK:\t" << player.getKeyCount(redKey) << endl;
}
#endif