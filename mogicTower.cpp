#include "mogicTower.h"
#include "damage.h"

void PlayerInfo::acquire(const vector<MapObj>& objList)
{
    size_t objCount = objList.size();
    for (size_t i = 0; i < objCount; ++i)
    {
        MapObj cur = objList[i];

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

bool PlayerInfo::fight(MapObj monsterType)
{
#ifdef DEBUG
    assert(isMonster(monsterType));
#endif
    int dmg = getDamage(*this, globalMogicTower.monsterInfo.at(monsterType));
    if (hp > dmg)
    {
        hp -= dmg;
        return true;
    }
    return false;
}