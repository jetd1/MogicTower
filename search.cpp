#include "mogic.h"
#include "mogicTower.h"
#include <vector>


/* 魔塔重构图节点结构 */
struct node
{
    bool valid;         /* 访问该节点后将valid设为false */
    Position pos;       /* 该节点的坐标 */
    MapObj type;        /* 该节点类型（门或怪物） */
    vector<node*> next; /* 子节点列表 */
    vector<MapObj> obj; /* 节点物品列表 */
    int blockCount;     /* 该节点增加的连通块计数 */
};

typedef node* Status;

int eval(const Status& stat);
void trans(const Status& cur, const Status& target);
void restore();

int search(const Status& stat, int depth)
{
    if (depth == MAX_DEPTH)
        return eval(stat);

    size_t nodeCount = stat->next.size();
    for (size_t i = 0; i < nodeCount; ++i)
    {
        Status& cur = stat->next[i];
        trans(stat, cur);
        search(cur, depth + 1);
        restore();
    }


}