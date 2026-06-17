#include "ite_bfs.h"
#include "../global_data.h"

#include "assert.h"
#include <iostream>

struct Segment
{
    int left, right;
};

IteBFS::IteBFS(GlobalData &data) : Iteration(data)
{
    label_search_order = create_label_search_order();
    std::cout << "c [Main] Search order:";
    for (const auto &width : label_search_order)
    {
        std::cout << " " << width;
    }
    std::cout << ".\n";
}

IteBFS::~IteBFS() {}

std::deque<int> IteBFS::create_label_search_order()
{
    std::deque<int> order_result;

    assert(global_data.lower_bound <= global_data.upper_bound);

    std::deque<Segment> dq;
    dq.push_back({global_data.lower_bound, global_data.upper_bound});

    while (!dq.empty())
    {
        Segment current = dq.front();
        dq.pop_front();

        int mid = (current.left + current.right) / 2;
        order_result.push_back(mid);

        if (current.left < mid)
            dq.push_back({current.left, mid - 1});
        if (mid < current.right)
            dq.push_back({mid + 1, current.right});
    }

    return order_result;
}