#include "mogicTower.h"
#include "damage.h"
#include <cassert>
#include "helpers.h"

bool PlayerInfo::operator==(const PlayerInfo& o) const
{
    return hp == o.hp && atk == o.atk && def == o.def &&
        mdef == o.mdef && keys[0] == o.keys[0] &&
        keys[1] == o.keys[1] && pos == o.pos && 
        blockCount == o.blockCount;
}

int PlayerInfo::getKeyCount(MapObj o) const
{
#ifdef DEBUG
    assert(isKey(o));
#endif
    return keys[o - yellowKey];
}

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

void PlayerInfo::useKey(MapObj keyType)
{
#ifdef DEBUG
    assert(isKey(keyType));
    assert(getKeyCount(keyType) > 0);
#endif
    keys[keyType - yellowKey]--;
}

//bool PlayerInfo::fight1(const GraphNode* monster)
//{
//#ifdef DEBUG
//    assert(isMonster(monster->getType()));
//    assert(monster->next.size() <= 4);
//#endif
//    int dmg = getDamage(*this, globalMogicTower.monsterInfo.at(monster->getType()));
//    if (hp > dmg)
//    {
//        for (auto itr = monster->next.begin(); itr != monster->next.end(); ++itr)
//            acquire((*itr)->obj), (*itr)->empty = true;
//        hp -= dmg;
//        return true;
//    }
//    return false;
//}

bool PlayerInfo::fight(MapObj monster)
{
#ifdef DEBUG
    assert(isMonster(monster));
#endif
    int dmg = getDamage(*this, globalMogicTower.monsterInfo.at(monster));
    if (hp > dmg)
    {
        hp -= dmg;
        return true;
    }
    return false;
}

bool GraphNode::operator==(const GraphNode& o) const
{
    return index == o.index && empty == o.empty;
}

Status::Status(const Status& other)
{
    //assert(false);
    player = other.player;
    nodeContainer = other.nodeContainer;
    cur = &nodeContainer[other.cur->getIndex()];
    size_t nodeCount = nodeContainer.size();
    for (size_t i = 0; i < nodeCount; ++i)
        nodeContainer[i].fatherStat = this;
}

const Status& Status::operator=(const Status& other)
{
    //assert(false);
    player = other.player;
    nodeContainer = other.nodeContainer;
    cur = &nodeContainer[other.cur->getIndex()];
    size_t nodeCount = nodeContainer.size();
    for (size_t i = 0; i < nodeCount; ++i)
        nodeContainer[i].fatherStat = this;

    return *this;
}
