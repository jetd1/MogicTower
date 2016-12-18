#include "debug.h"
#include "mogicTower.h"
#include <iomanip>

#ifdef DEBUG
void dbg_compareStatus(const Status& a, const Status& b)
{
    size_t sizeA = a.nodeContainer.size();
    size_t sizeB = b.nodeContainer.size();
    if (!(sizeA == sizeB && a.player == b.player && a.curIdx == b.curIdx))
        throw runtime_error("Corrupted Status!");

    auto& nA = a.nodeContainer;
    auto& nB = b.nodeContainer;

    if (nA.size() != nB.size())
        throw runtime_error("Corrupted Status!");

    for (size_t i = 0; i < sizeA; i++)
        if (!(nA[i] == nB[i]))
            throw runtime_error("Corrupted Status!");
}

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


void Tower::dbg_print()
{
    for (int i = 0; i < MAP_LENGTH; ++i)
    {
        for (int j = 0; j < MAP_WIDTH; ++j)
            cout << setw(2) << mapContent[i][j] << ' ';
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