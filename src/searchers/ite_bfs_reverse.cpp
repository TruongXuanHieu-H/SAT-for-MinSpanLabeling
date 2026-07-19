#include "ite_bfs_reverse.h"
#include "../global_data.h"

#include "assert.h"
#include <iostream>

struct Segment
{
    int left, right;
};

IteBFSReverse::IteBFSReverse(GlobalData &data) : Iteration(data)
{
    label_search_order = create_label_search_order();
    std::cout << "c [Main] Search order:";
    for (const auto &width : label_search_order)
    {
        std::cout << " " << width;
    }
    std::cout << ".\n";
}

IteBFSReverse::~IteBFSReverse() {}

std::deque<int> IteBFSReverse::create_label_search_order()
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

        if (mid < current.right)
            dq.push_back({mid + 1, current.right});
        if (current.left < mid)
            dq.push_back({current.left, mid - 1});
    }

    return order_result;
}