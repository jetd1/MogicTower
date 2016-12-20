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
    for (auto cur: objList)
        switch (cur)
        {
            case yellowKey:
            case blueKey:
            case redKey:
                ++keys[cur - yellowKey];
                break;
            case redDiamond:
                atk += Tower::buff[0];
                break;
            case blueDiamond:
                def += Tower::buff[1];
                break;
            case greenDiamond:
                mdef += Tower::buff[2];
                break;
            case smallBottle:
                hp += Tower::buff[3];
                break;
            case largeBottle:
                hp += Tower::buff[4];
                break;
            default:
                throw invalid_argument("Invalid obj type!");
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

bool PlayerInfo::fight(MapObj monster)
{
#ifdef DEBUG
    assert(isMonster(monster));
#endif
    int dmg = getDamage(*this, Tower::monsterInfo.at(monster));
    if (hp > dmg)
    {
        hp -= dmg;
        return true;
    }
    return false;
}

bool PlayerInfo::canBeat(MapObj monster)const
{
#ifdef DEBUG
    assert(isMonster(monster));
#endif
    int dmg = getDamage(*this, Tower::monsterInfo.at(monster));
    return hp > dmg;
}

int Tower::buff[5];

map<MapObj, Monster> Tower::monsterInfo;

bool GraphNode::operator==(const GraphNode& o) const
{
    return index == o.index && empty == o.empty;
}

Status::Status(const Status& other)
{
    player = other.player;
    nodeContainer = other.nodeContainer;
    curIdx = other.curIdx;
    bossIdx = other.bossIdx;
    mogicTower = other.mogicTower;
    size_t nodeCount = nodeContainer.size();
}

const Status& Status::operator=(const Status& other)
{
    player = other.player;
    nodeContainer = other.nodeContainer;
    curIdx = other.curIdx;
    bossIdx = other.bossIdx;
    mogicTower = other.mogicTower;
    size_t nodeCount = nodeContainer.size();

    return *this;
}

bool Status::bossDead()const
{
    return bossIdx == 0;
}

void Status::print() const
{
    cout << "Boss Dead: \t" << boolalpha << bossDead() << endl;
    cout << "HP: \t" << player.getHP() << endl;
    cout << "ATK:\t" << player.getATK() << endl;
    cout << "DEF:\t" << player.getDEF() << endl;
    cout << "MDEF:\t" << player.getMDEF() << endl;
    cout << "YK: \t" << player.getKeyCount(yellowKey) << endl;
    cout << "BK: \t" << player.getKeyCount(blueKey) << endl;
    cout << "RK: \t" << player.getKeyCount(redKey) << endl;
}

int Status::getRemainDoorCount(MapObj doorType) const
{
#ifdef DEBUG
    assert(isDoor(doorType));
#endif
    int cnt = 0;
    for (const auto& node: nodeContainer)
        cnt += node.getType() == doorType;
    return cnt;
}

int Status::getRemainKeyCount(MapObj keyType) const
{
#ifdef DEBUG
    assert(isKey(keyType));
#endif
    int cnt = 0;
    for (const auto& node : nodeContainer)
        cnt += node.getType() == keyType;
    return cnt;
}