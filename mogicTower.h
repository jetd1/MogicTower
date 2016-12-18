#ifndef __MOGIC_TOWER_H
#define __MOGIC_TOWER_H

#include "mogic.h"
#include <iostream>
#include <map>
#include <set>
#include <vector>

class GraphNode;
struct Tower;

/* 记录地图信息的枚举结构 */
enum MapObj
{
    safeBlock = 0,

    road = 10,
    wall,

    yellowKey = 21,
    blueKey,
    redKey,
    redDiamond,
    blueDiamond,
    greenDiamond,
    smallBottle,
    largeBottle,

    yellowDoor = 31,
    blueDoor,
    redDoor,

    monster51 = 51,
    monster52,
    monster53,
    monster54,
    monster55,
    monster56,
    monster57,
    monster58,
    monster59,
    monster60,
    monster61,
    monster62,
    monster63,
    monster64,
    monster65,
    monster66,
    monster67,
    monster68,
    monster69,
    monster70,

    boss = 99
};

/* 方便直接读入枚举值的函数 */
inline istream& operator >> (istream& in, MapObj& m)
{
    int tmp;
    in >> tmp;
    m = MapObj(tmp);
    return in;
}

struct Position
{
    int x, y;

    Position(int _x = 0, int _y = 0): x(_x), y(_y) {}
    bool operator==(const Position& o)const { return x == o.x && y == o.y; }
	bool operator<(const Position& o)const { return x == o.x ? y < o.y : x < o.x; }
};

/* 记录玩家信息的数据结构 */
struct PlayerInfo
{
private:
    int hp;         /* 血量 */
    int atk;        /* 攻击 */
    int def;        /* 防御 */
    int mdef;       /* 魔防 */

    int keys[3];    /* 各钥匙数目 */

    Position pos;   /* 位置 */

public:
    int blockCount; /* 当前总的连通块计数 */

    PlayerInfo() { hp = atk = def = mdef = keys[0] = keys[1] = keys[2] = pos.x = pos.y = blockCount = 0; }
    friend istream& operator >> (istream& in, PlayerInfo& m)
    {
        in >> m.hp >> m.atk >> m.def >> m.mdef >> m.pos.x >> m.pos.y;
        return in;
    }
    bool operator==(const PlayerInfo& o)const;

    int getATK() const { return atk; }
    int getDEF() const { return def; }
    int getMDEF() const { return mdef; }
    int getHP() const { return hp; }
    const Position& getPos() const { return pos; }
    int getKeyCount(MapObj o) const;
    bool fight(MapObj monster);
    bool canBeat(MapObj monster)const;
    //bool PlayerInfo::fight1(const GraphNode* monster);
    void acquire(const vector<MapObj>& objList);
    void moveTo(const Position& _pos) { pos = _pos; }
    void useKey(MapObj keyType);
};

/* 记录怪物信息的数据结构 */
class Monster
{
private:
    int hp;     /* 血量 */
    int atk;    /* 攻击力 */
    int def;    /* 防御力 */
    int spe;    /* 特效 */

public:
    Monster() {}
    Monster(int _hp, int _atk, int _def, int _spe)
    {
        hp = _hp, atk = _atk, def = _def, spe = _spe;
    }

    friend istream& operator >> (istream& in, Monster& m)
    {
        in >> m.hp >> m.atk >> m.def >> m.spe;
        return in;
    }

    int getATK() const { return atk; }
    int getDEF() const { return def; }
    int getSPE() const { return spe; }
    int getHP() const { return hp; }
};

/*全局记录塔信息的数据结构 */
struct Tower
{
    /* 楼层地图大小和楼层数，当前固定为1 * 13 * 13 */
    //int height;
    //int len, wid;

    /* 用枚举记录地图内容 */
    MapObj mapContent[MAP_LENGTH][MAP_WIDTH];
    /* 当前的染色图，方便地图重构 */
    int colorMap[MAP_LENGTH][MAP_WIDTH]; 

    /* 记录各加成值 */
    int buff[5];

    /* 记录怪物数据 */
    map<MapObj, Monster> monsterInfo;

    /* 记录玩家数据 */
    PlayerInfo player;
#ifdef DEBUG
    void dbg_print();
#endif
};

/* 魔塔重构图节点结构 */
class GraphNode
{
private:
    int index;              /* 该节点索引值（最初被染的颜色） */
    Position pos;           /* 该节点的坐标 */
    MapObj type;            /* 该节点类型 */
    
public:
    bool empty;             /* 访问该节点后将empty设为true */
    int blockCount;         /* 该节点增加的连通块计数 */
    set<int> adj;           /* 邻接节点索引列表 */
    vector<MapObj> obj;     /* 节点物品列表 */
    Status* fatherStat;

    //GraphNode() { empty = true; }
    GraphNode(Status* father = nullptr): empty(true), fatherStat(father) {}
    GraphNode(Status* father, int _idx, int _x, int _y, MapObj _type):
    fatherStat(father), index(_idx),  pos(_x, _y), type(_type), empty(false), blockCount(1) {}
    MapObj getType()const { return type; }
    int getIndex()const { return index; }
    const Position& getPos()const { return pos; }
    bool operator==(const GraphNode& o)const;
};

/* 状态转移结构 */
struct Status
{
    int curIdx;
    PlayerInfo player;

    vector<GraphNode> nodeContainer;

    Status(): curIdx(0), player(), nodeContainer() {}
    Status(const Status& other);
    const Status& operator=(const Status& other);
    GraphNode& getNode(int index = 0) { return index ? nodeContainer[index] : nodeContainer[curIdx]; }
    const GraphNode& getNode(int index = 0)const { return index ? nodeContainer[index] : nodeContainer[curIdx]; }
    GraphNode* getNodePtr(int index = 0) { return index ? &nodeContainer[index] : &nodeContainer[curIdx]; }
};


extern Tower globalMogicTower;

#endif

