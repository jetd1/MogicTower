#include "mogicTower.h"
#include "helpers.h"
#include <cassert>
#include "damage.h"

extern Tower globalMogicTower;

void PlayerInfo::acquire(vector<MapObj>& objList)
{
    while (!objList.empty())
    {
        MapObj cur = objList.back();
        objList.pop_back();

        switch (cur)
        {
            case yellowKey:
            case blueKey:
            case redKey:
                ++keys[cur - yellowKey];
                break;
            case redDiamond:
                atk += globalMogicTower.buff[0];
                break;
            case blueDiamond:
                def += globalMogicTower.buff[1];
                break;
            case greenDiamond:
                mdef += globalMogicTower.buff[2];
                break;
            case smallBottle:
                hp += globalMogicTower.buff[3];
                break;
            case largeBottle:
                hp += globalMogicTower.buff[4];
                break;
        }
    }
}

void PlayerInfo::fight(MapObj monsterType)
{
#ifdef DEBUG
    assert(isMonster(monsterType));
#endif
    int dmg = getDamage(*this, globalMogicTower.monsterInfo.at(monster51));
    hp -= dmg;
}