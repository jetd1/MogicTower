#include "mogicTower.h"
#include "damage.h"
#include <cassert>
#include <cstring>
#include <fstream>
#include "helpers.h"
#include "graph.h"

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
            case yellowBottle:
                hp += Tower::buff[5];
                break;
            case greenBottle:
                hp += Tower::buff[6];
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

bool PlayerInfo::canBeat(MapObj monster) const
{
#ifdef DEBUG
    assert(isMonster(monster));
#endif
    int dmg = getDamage(*this, Tower::monsterInfo.at(monster));
    return hp > dmg;
}

int Tower::buff[7];

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
}

const Status& Status::operator=(const Status& other)
{
    player = other.player;
    nodeContainer = other.nodeContainer;
    curIdx = other.curIdx;
    bossIdx = other.bossIdx;
    mogicTower = other.mogicTower;

    return *this;
}

bool Status::bossDead() const
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

bool Status::hasNext() const
{
    const auto& adj = getNode().adj;
    if (bossDead())
        return false;
    for (auto idx : adj)
    {
        MapObj type = nodeContainer[idx].getType();
#ifdef DEBUG
        assert(type != safeBlock);
#endif
        if (isMonster(type))
            if (player.canBeat(type))
                return true;

        if (isDoor(type))
            if (player.getKeyCount(keyType(type)) > 0)
                return true;
    }
    return false;
}

void Status::moveTo(int targetIdx, bool updateFlag)
{
    GraphNode& target = nodeContainer[targetIdx];
#ifdef DEBUG
    assert(!target.empty);
#endif

    MapObj type = target.getType();
    auto& map = mogicTower.mapContent;

    if (type == safeBlock)
    {
        Position tPos = target.getPos();
        player.acquire(target.obj);
        player.moveTo(tPos);

        auto& colorMap = mogicTower.colorMap;
        int tColor = colorMap[tPos.x][tPos.y];
        for (int i = 0; i < MAP_LENGTH; ++i)
            for (int j = 0; j < MAP_WIDTH; ++j)
                if (colorMap[i][j] == tColor)
                    map[i][j] = road;
    }
    else if (isMonster(type))
    {
        Position tPos = target.getPos();
        assert(player.fight(type));
        player.moveTo(tPos);
        map[tPos.x][tPos.y] = road;
        if (type != boss)
            for (auto itr = target.adj.begin(); itr != target.adj.end(); ++itr)
                if (getNode(*itr).getType() == safeBlock && !target.empty)
                    moveTo(*itr, false);
        player.moveTo(tPos);
    }
    else if (isDoor(type))
    {
        Position tPos = target.getPos();
        player.useKey(keyType(type));
        player.moveTo(tPos);
        map[tPos.x][tPos.y] = road;
        for (auto itr = target.adj.begin(); itr != target.adj.end(); ++itr)
            if (getNode(*itr).getType() == safeBlock && !target.empty)
                moveTo(*itr, false);
        player.moveTo(tPos);
    }
    else
        throw runtime_error("Invalid Target!");

    if (updateFlag)
        update();
}

const Status& Status::update()
{
    Position curPos = player.getPos();

    auto& colorMap = mogicTower.colorMap;
    memset(colorMap, 0, sizeof(colorMap));
    int colorCount = traverseMap(mogicTower) + 1;

    nodeContainer.resize(size_t(colorCount));

    curIdx = buildGraph(mogicTower, curPos, colorCount, this);

    bool flag = false;
    for (const auto& node: nodeContainer)
        if (node.getType() == boss)
        {
            bossIdx = node.getIndex(), flag = true;
            break;
        }
    if (!flag)
        bossIdx = 0;

#ifdef DEBUG
    assert(getNodePtr()->getType() == safeBlock);
#endif

    return *this;
}

const Status& Status::init()
{
    readInitStatus();
    update();
    player.blockCount = 0;
    Position originalPositon = player.getPos();
    moveTo(curIdx);
    player.moveTo(originalPositon);
    getNode().pos = originalPositon;

    return *this;
}

const Status& Status::readInitStatus()
{
    ifstream fin("input.txt");
    if (!fin)
    {
        cout << "无法打开input.txt，将从stdin读入..." << endl;
        int ign;
        cin >> ign >> ign >> ign;

        for (size_t i = 0; i < MAP_LENGTH; ++i)
            for (size_t j = 0; j < MAP_LENGTH; ++j)
                cin >> mogicTower.mapContent[i][j];

        for (size_t i = 0; i < 7; i++)
            cin >> mogicTower.buff[i];

        int monsterTypeCount;
        cin >> monsterTypeCount;
        while (monsterTypeCount--)
        {
            MapObj key;
            Monster tmpMon;
            cin >> key >> tmpMon;
            mogicTower.monsterInfo[key] = tmpMon;
        }

        cin >> player;
    }
    else
    {
        int ign;
        fin >> ign >> ign >> ign;

        for (size_t i = 0; i < MAP_LENGTH; ++i)
            for (size_t j = 0; j < MAP_LENGTH; ++j)
                fin >> mogicTower.mapContent[i][j];

        for (size_t i = 0; i < 5; i++)
            fin >> mogicTower.buff[i];

        int monsterTypeCount;
        fin >> monsterTypeCount;
        while (monsterTypeCount--)
        {
            MapObj key;
            Monster tmpMon;
            fin >> key >> tmpMon;
            mogicTower.monsterInfo[key] = tmpMon;
        }

        fin >> player;
    }

    return *this;
}

