#include "AI.h"
#include "mogicTower.h"
#include "search.h"
#include <thread>

int MAX_DEPTH = 12;

int Achilles(Status& stat)
{
    const auto& adjList = stat.getNode().adj;
    auto adjCount = adjList.size();

    if (adjCount == 0)
        return 0;
    if (adjCount == 1)
        return *adjList.begin();

    if (adjCount == 2)
    {
        int t1Choice, t2Choice;
        int ret1, ret2;
        set<int> s1, s2;
        set<int>::const_iterator itr = adjList.begin();

        s1.insert(*itr);
        s2.insert(*(++itr));

        thread t1(search, ref(stat), 0, ref(s1), ref(t1Choice), ref(ret1));
        thread t2(search, ref(stat), 0, ref(s2), ref(t2Choice), ref(ret2));
        t1.join(), t2.join();
        return ret1 > ret2 ? t1Choice : t2Choice;
    }

    if (adjCount == 3)
    {
        int t1Choice, t2Choice, t3Choice;
        int ret1, ret2, ret3;
        set<int> s1, s2, s3;
        set<int>::const_iterator itr = adjList.begin();

        s1.insert(*itr);
        s2.insert(*(++itr));
        s3.insert(*(++itr));

        thread t1(search, ref(stat), 0, ref(s1), ref(t1Choice), ref(ret1));
        thread t2(search, ref(stat), 0, ref(s2), ref(t2Choice), ref(ret2));
        thread t3(search, ref(stat), 0, ref(s3), ref(t3Choice), ref(ret3));
        t1.join(), t2.join(), t3.join();
        if (ret1 < ret2)
        {
            if (ret2 > ret3)
                return t2Choice;
            return t3Choice;
        }
        return ret1 > ret3 ? t1Choice : t3Choice;
    }

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

    thread t1(search, ref(stat), 0, ref(s1), ref(t1Choice), ref(ret1));
    thread t2(search, ref(stat), 0, ref(s2), ref(t2Choice), ref(ret2));
    thread t3(search, ref(stat), 0, ref(s3), ref(t3Choice), ref(ret3));
    thread t4(search, ref(stat), 0, ref(s4), ref(t4Choice), ref(ret4));
    t1.join(), t2.join(), t3.join(), t4.join();
    int ma = max(ret1, max(ret2, max(ret3, ret4)));
    if (ma == ret4)
        return t4Choice;
    if (ma == ret3)
        return t3Choice;
    if (ma == ret2)
        return t2Choice;
    return t1Choice;


}
