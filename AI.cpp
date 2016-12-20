#include "AI.h"
#include "mogicTower.h"
#include "search.h"
#include <thread>
#include <algorithm>

using namespace AIprof;

int AIprof::DEFAULT_DEPTH;
int AIprof::MAX_DEPTH;
double AIprof::lastSearchTime = 0;
bool AIprof::lastSearchTrivial = true;


int Achilles(const Status& stat, int depth)
{
    clock_t startTime = clock();

    MAX_DEPTH = depth;

    const auto& adjList = stat.getNode().adj;
    auto adjCount = adjList.size();
    int choice;

    if (adjCount == 0)
        choice = 0, lastSearchTrivial = true;
    else if (adjCount == 1)
        choice = *adjList.begin(), lastSearchTrivial = true;
    else if (adjCount == 2)
    {
        int t1Choice, t2Choice;
        int ret1, ret2;
        set<int> s1, s2;
        set<int>::const_iterator itr = adjList.begin();

        s1.insert(*itr);
        s2.insert(*(++itr));


        cout << "Searching, depth = " << MAX_DEPTH << endl;

        thread t1(::search, ref(stat), 0, ref(s1), ref(t1Choice), ref(ret1));
        thread t2(::search, ref(stat), 0, ref(s2), ref(t2Choice), ref(ret2));
        t1.join(), t2.join();
        choice = ret1 > ret2 ? t1Choice : t2Choice;
        lastSearchTrivial = false;
    }
    else if (adjCount == 3)
    {
        int t1Choice, t2Choice, t3Choice;
        int ret1, ret2, ret3;
        set<int> s1, s2, s3;
        set<int>::const_iterator itr = adjList.begin();

        s1.insert(*itr);
        s2.insert(*(++itr));
        s3.insert(*(++itr));


        cout << "Searching, depth = " << MAX_DEPTH << endl;

        thread t1(::search, ref(stat), 0, ref(s1), ref(t1Choice), ref(ret1));
        thread t2(::search, ref(stat), 0, ref(s2), ref(t2Choice), ref(ret2));
        thread t3(::search, ref(stat), 0, ref(s3), ref(t3Choice), ref(ret3));
        t1.join(), t2.join(), t3.join();
        int ma = max(ret1, max(ret2, ret3));

        if (ma == ret3)
            choice = t3Choice;
        else if (ma == ret2)
            choice = t2Choice;
        else
            choice = t1Choice;
        lastSearchTrivial = false;
    }
    else
    {
        int t1Choice, t2Choice, t3Choice, t4Choice;
        int ret1, ret2, ret3, ret4;
        set<int> s1, s2, s3, s4;
        set<int>::const_iterator itr = adjList.begin();
        set<int>::const_iterator end = adjList.end();
        size_t idx = 0;

        while (idx <= adjCount / 4)
            s1.insert(*(itr++)), ++idx;
        while (idx <= adjCount / 2)
            s2.insert(*(itr++)), ++idx;
        while (idx <= 3 * adjCount / 4)
            s3.insert(*(itr++)), ++idx;
        while (itr != end)
            s4.insert(*(itr++));


        cout << "Searching, Depth = " << MAX_DEPTH << endl;

        thread t1(::search, ref(stat), 0, ref(s1), ref(t1Choice), ref(ret1));
        thread t2(::search, ref(stat), 0, ref(s2), ref(t2Choice), ref(ret2));
        thread t3(::search, ref(stat), 0, ref(s3), ref(t3Choice), ref(ret3));
        thread t4(::search, ref(stat), 0, ref(s4), ref(t4Choice), ref(ret4));
        t1.join(), t2.join(), t3.join(), t4.join();
        int ma = max(ret1, max(ret2, max(ret3, ret4)));
        if (ma == ret4)
            choice = t4Choice;
        else if (ma == ret3)
            choice = t3Choice;
        else if (ma == ret2)
            choice = t2Choice;
        else
            choice = t1Choice;
        lastSearchTrivial = false;
    }

    lastSearchTime = double(clock() - startTime) / CLOCKS_PER_SEC;
    return choice;
}

void initDefaultDepth(const Status& stat)
{
    size_t nodeCount = stat.nodeContainer.size() - 1;

    size_t ma = 0, total = 0;
    for (const auto& node : stat.nodeContainer)
        ma = max(ma, node.adj.size()), total += node.adj.size();

    double averageAdjCount = double(total) / nodeCount;

    cout << "Average Adjacency: \t" << averageAdjCount << endl;
    cout << "Max Adjacency: \t\t" << ma << endl;

    DEFAULT_DEPTH = 6;

    if (ma <= 3)
    {
        if (averageAdjCount <= 1.955)
            DEFAULT_DEPTH = 14;
        else if (averageAdjCount <= 1.980)
            DEFAULT_DEPTH = 10;
        else if (averageAdjCount <= 2.000)
            DEFAULT_DEPTH = 8;
    }
    else if (ma == 4)
    {
        if (averageAdjCount <= 2)
        {
            if (nodeCount <= 33)
                DEFAULT_DEPTH = 11;
            else if (nodeCount <= 36)
                DEFAULT_DEPTH = 10;
            else if (nodeCount <= 40)
                DEFAULT_DEPTH = 9;
            else if (nodeCount <= 49)
                DEFAULT_DEPTH = 8;
        }
    }
    else if (ma == 5)
    {
        if (averageAdjCount < 2.20 || nodeCount <= 49)
            DEFAULT_DEPTH = 7;
    }
    else if (stat.getRemainDoorCount(yellowDoor) > stat.getRemainKeyCount(yellowKey) ||
        stat.getRemainDoorCount(blueDoor) > stat.getRemainKeyCount(blueKey) ||
        stat.getRemainDoorCount(redDoor) > stat.getRemainKeyCount(redKey))
        DEFAULT_DEPTH = 10;

    MAX_DEPTH = DEFAULT_DEPTH;
}